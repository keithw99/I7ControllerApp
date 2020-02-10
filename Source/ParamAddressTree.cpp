/*
  ==============================================================================

    ParamAddressTree.cpp
    Created: 3 Feb 2020 9:54:20pm
    Author:  keith

  ==============================================================================
*/

#include "ParamAddressTree.h"
#include "Utils.h"

/*
template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    size_t size = snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    std::unique_ptr<char[]> buf( new char[ size ] ); 
    snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}
*/

PTree::~PTree() {
  Reset();
}

PNode* PTree::visitHigh(PNode* node, ParamAddr address, ParamPath* path) {
  if (node == nullptr) {
    DBG("Traversed a NULL node!");
    return nullptr;
  }
  NodeInfo* info = node->info.get();
  if (info != nullptr) {
    path->push_back({info->getBaseDescription(), info->getIndex()});
  }
  if (address.len == 0) {
    return node;
  }
  node = node->getBase();
  uint8 nextHighNibble = (address.address >> 28) & 0x7;
  address.address <<= 4;
  address.len -= 1;
  PNode* next = node->children[nextHighNibble];
  return visitLow(next, address, path);
}

PNode* PTree::visitLow(PNode* node, ParamAddr address, ParamPath* path) {  
  if (node == nullptr) {
    DBG("Traversed a NULL node!");
    return nullptr;
  }
  NodeInfo* info = node->info.get();
  if (info != nullptr) {
    path->push_back({info->getBaseDescription(), info->getIndex()});
  }
  if (address.len == 0) {
    return node;
  }
  node = node->getBase();
  uint8 nextLowNibble = (address.address >> 28) & 0xF;
  address.address <<= 4;
  address.len -= 1;
  PNode* next = node->children[nextLowNibble];
  return visitHigh(next, address, path);
}

const NodeInfo PTree::Find(const ParamAddr& address) {
  ParamAddr copy = address;
  ParamPath unused_path;
  const NodeInfo* info = visitHigh(root_, copy, &unused_path)->info.get();
  return NodeInfo(*info);
}

NodeInfo* PTree::FindPtr(const ParamAddr& address) {
  ParamAddr copy = address;
  ParamPath unused_path;
  return visitHigh(root_, copy, &unused_path)->info.get();
}

std::shared_ptr<ParamInfo> PTree::FindParamInfo(const ParamAddr& address) {
  return FindPtr(address)->getParamInfo();
}

ParamPath PTree::GetPath(const ParamAddr& address) {
  ParamAddr copy = address;
  ParamPath path;
  visitHigh(root_, copy, &path);
  return path;
}

NodeInfo* PTree::GetNodeAndPath(const ParamAddr& address, ParamPath* path) {
  ParamAddr copy = address;
  return visitHigh(root_, copy, path)->info.get();
}

ParamPath PTree::GetPathFromBytes(uint8* addr, uint8 num_bytes) {
  return GetPath(ParamAddr(Pack8Bit(addr, num_bytes), num_bytes * 2));
}

NodeInfo* PTree::GetNodeAndPathFromBytes(uint8* addr, uint8 num_bytes, ParamPath* path)  {
  ParamAddr copy = ParamAddr(Pack8Bit(addr, num_bytes), num_bytes * 2);
  return visitHigh(root_, copy, path)->info.get();
}

void PTree::Insert(const ParamAddr& address, const NodeInfo& info) {
  ParamAddr copy = address;
  root_ = insertHigh(root_, copy, info, nullptr);
}

void PTree::InsertParam(const ParamAddr& address, std::shared_ptr<ParamInfo> param_info) {
  //NodeInfo* pnode = FindPtr(address);
  FindPtr(address)->setParamInfo(param_info);
  //NodeInfo* found = FindPtr(address);
}

void PTree::InsertGroupNode(const ParamAddr& address, const Identifier& description) {
  return Insert(address, GroupNode(description));
}

void PTree::insertIndexedNode(const ParamAddr& address, const NodeInfo& info, PNode* const base) {
  ParamAddr copy = address;
  if (base == nullptr) {
    DBG("ERROR: Cannot insert indexed node on null base!");
    return;
  }
  root_ = insertHigh(root_, copy, info, base);
  //NodeInfo* found = FindPtr(address);
}

void PTree::InsertRange(const ParamAddrRange& range,
                  const NodeType node_type,
                  const Identifier& description,
                  const Identifier& format) {
  auto addrs = range.GetAddresses();
  // Insert first (base) node.
  int i = range.start_index;
  NodeInfo info(node_type, description, i, format);
  Insert(addrs[0], NodeInfo(node_type, description, i, format));
    
  NodeInfo* base_info = FindPtr(addrs[0]);
  ParamPath unused_path;
  PNode* base_node = visitHigh(root_, addrs[0], &unused_path);

  for (auto it = addrs.begin() + 1; it != addrs.end(); it++) {
    // Insert nodes with pointer to base.
    i++;  // Increment the NodeInfo index.
    //Insert(*it, NodeInfo(base_info, i));
    insertIndexedNode(*it, NodeInfo(base_info, i), base_node);
  }
}

void PTree::InsertParamRange(const ParamAddrRange& range,
                             const Identifier& description,
                             const Identifier& format,
                             const ParamProperties& props) {
  InsertRange(range, NodeType::INDEXED_PARAM, description, format);

  // Insert ParamInfo only on the base of the range.
  ParamAddr base_addr = range.GetBaseAddr();
  std::shared_ptr<ParamInfo> pinfo = std::make_shared<ParamInfo>(ParamInfo::makeParamInfo(props));
  InsertParam(base_addr, pinfo);
}

ParamAddr PTree::InsertOffset(const ParamAddr& base_addr, const ParamAddr& offset_addr,
                  const NodeInfo& info) {
  ParamAddr offset_copy = base_addr + offset_addr;
  Insert(offset_copy, info);
  return offset_copy;
}

std::shared_ptr<ParamInfo> PTree::InsertParamOffset(const ParamAddr& base_addr,
                                                    const ParamAddr& offset_addr,
                                                    const Identifier& description,
                                                    const ParamProperties& props) {
  ParamAddr inserted = InsertOffset(base_addr, offset_addr, NodeInfo(NodeType::PARAM, description));
  NodeInfo* param_node = FindPtr(inserted);
  
  std::shared_ptr<ParamInfo> pinfo = std::make_shared<ParamInfo>(ParamInfo::makeParamInfo(props));
  param_node->setParamInfo(pinfo);  
  return pinfo;  
}

ParamAddr PTree::InsertRangeOffset(const ParamAddr& base_addr,
                                   const ParamAddrRange& offset_range,
                                   const NodeType node_type,
                                   const Identifier& description,
                                   const Identifier& format) {
  ParamAddrRange abs_range = offset_range + base_addr;
  InsertRange(abs_range, node_type, description, format);
  return abs_range.GetBaseAddr();
}

ParamAddr PTree::InsertParamRangeOffset(const ParamAddr& base_addr,
                                        const ParamAddrRange& offset_range,
                                        const Identifier& description,
                                        const Identifier& format,
                                        const ParamProperties& props) {
  ParamAddrRange abs_range = offset_range + base_addr;
  InsertParamRange(abs_range, description, format, props);
  return abs_range.GetBaseAddr();
}

bool PTree::HasData() { return root_ != nullptr; }

void PTree::Reset() { delete root_; root_ = nullptr; }

Identifier NodeInfo::getDescriptionFormat() const { 
  if (format_.isNull() && isIndexed()) {
    return base_->getDescriptionFormat();
  }
  return format_;
}

Identifier NodeInfo::getBaseDescription() const {
  if (description_.isNull() && isIndexed())
    return base_->getRawDescription();
  return description_;
}

Identifier NodeInfo::getDescription() const {
  if (isIndexed()) {
    return Identifier(string_format(getDescriptionFormat().toString().toStdString(), index_));
  }
  return description_;
}

String NodeInfo::debugString() const {
  String str = getDescription() + " (";
  str += "type:" + String(int(node_type_)) + ")";
  str += "[" + String(int(index_)) + "]";
  if (param_info_ != nullptr) {
    str += " *P*";
  }
  return str;
}

std::shared_ptr<ParamInfo> NodeInfo::getParamInfo() const {
  if (isBase()) {
    return param_info_;
  }
  return base_->getParamInfo();
}

bool NodeInfo::hasParamInfo() const {
  if (isBase()) {
    return param_info_ != nullptr;
  }
  return base_->hasParamInfo();
}

void NodeInfo::setParamInfo(std::shared_ptr<ParamInfo> param_info) {
  param_info_ = param_info;  // This should increase the reference count.
}

PNode* PTree::insertHigh(PNode* node, ParamAddr address,
                         const NodeInfo& info, PNode* const base = nullptr) {
  if (node == nullptr) {
    PNode* newNode = new PNode;
    return insertHigh(newNode, address, info, base);
  } else if (address.len == 0) {
    node->info = std::make_unique<NodeInfo>(info);
    node->range_base = base;
    return node;
  } else {
    uint8 nextHighNibble = (address.address >> 28) & 0x7;
    address.address <<= 4;
    address.len -= 1;
    node->children[nextHighNibble] = insertLow(node->children[nextHighNibble], address, info, base);
    return node;
    }
  }

PNode* PTree::insertLow(PNode* node, ParamAddr address,
                        const NodeInfo& info, PNode* const base = nullptr) {
  if (node == nullptr) {
    PNode* newNode = new PNode;
    return insertLow(newNode, address, info, base);
  } else if (address.len == 0) {
    node->info = std::make_unique<NodeInfo>(info);
    node->range_base = base;
    return node;
  } else {
    uint8 nextLowNibble = (address.address >> 28) & 0xF;
    address.address <<= 4;
    address.len -= 1;
    node->children[nextLowNibble] = insertHigh(node->children[nextLowNibble], address, info, base);
    return node;
  }
}

std::function<PNode*(PNode*, ParamAddr, const NodeInfo&)>
PTree::insertFunc(const ParamAddr& address) {
  return [&, this](PNode* pn, ParamAddr pa, const NodeInfo& ni) {
    return address.len % 2 == 0 ? this->insertHigh(pn, pa, ni) : this->insertLow(pn, pa, ni);
  };
}

std::vector<ParamUpdate>
PTree::GetParamUpdates(uint8* addr_bytes, uint8* data, int num_bytes) {
  std::vector<ParamUpdate> updates;
  int param_size = 0;
  int bytes_to_read = num_bytes;
  uint8* data_ptr = data;
  ParamAddr paddr = ParamAddr(addr_bytes);
  
  while (param_size <= bytes_to_read) {
    ParamPath path;
    NodeInfo* pn_info = GetNodeAndPath(paddr, &path);
    if (pn_info->getNodeType() != NodeType::PARAM &&
        pn_info->getNodeType() != NodeType::INDEXED_PARAM) {
      // TODO: Throw error.
      DBG("ERROR: Trying to get ParamInfo from non-param node");
      return updates;
    }

    if (!pn_info->hasParamInfo()) {
      // TODO: Throw error.
      DBG("ERROR: NodeInfo has no ParamInfo");
      return updates;
    }
   
    std::shared_ptr<ParamInfo> pinfo = pn_info->getParamInfo();
    param_size = pinfo->getByteSize();
    if (param_size > bytes_to_read) {
      // TODO: Throw error.
      DBG("ERROR: Trying to read a param with more bytes than were provided");
      return updates;
    }
    int value = pinfo->getNormalizedInt(data_ptr);
    // Increment the data pointer;
    data_ptr += param_size;  
    // Push into a ParamUpdate.
    updates.push_back(ParamUpdate{path, value, pinfo});
    // Update to the next address;
    paddr += param_size;
    bytes_to_read -= param_size;
  }
  return updates;
}
  