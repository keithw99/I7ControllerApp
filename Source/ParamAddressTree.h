/*
  ==============================================================================

    ParamAddressTree.h
    Created: 25 Jan 2020 6:05:05pm
    Author:  keith

  ==============================================================================
*/

#pragma once

#include <cstdint>
#include <functional>
#include <ios>
#include <memory>
#include <string>
//#include <deque>
#include <vector>

#include "../JuceLibraryCode/JuceHeader.h"

#include "Param.h"
#include "ParamAddress.h"

typedef uint8_t uint8;
typedef uint32_t uint32;

enum class NodeType {
  PATH,
  INDEXED_PATH,
  PARAM,
  INDEXED_PARAM,
  NIL,
};

class NodeInfo {
 public:
  NodeInfo(const NodeType node_type, const Identifier& description) :
    node_type_(node_type), description_(description) {}
  NodeInfo(
    const NodeType node_type, const Identifier& description, const int index,
    const Identifier& format) :
    node_type_(node_type), description_(description), index_(index),
    format_(format) {}
  NodeInfo(
    NodeInfo* base_info, const int index) :
      base_(base_info), index_(index), node_type_(base_info->getNodeType()) {
  }
  // Copy? constructor.
  NodeInfo(const NodeInfo& src) {
    node_type_ = src.getNodeType();
    description_ = src.getBaseDescription();
    index_ = src.getIndex();
    format_ = src.isIndexed() ? src.getDescriptionFormat() : Identifier::null;
    base_ = src.getBaseNode();
  }
  
  bool isIndexed() const { return index_ > -1; }
  bool isNull() const { return node_type_ == NodeType::NIL; }
  bool isBase() const { return base_ == nullptr; }
  bool isRangeBase() const { return isIndexed() && base_ == nullptr; }
  bool hasBase() const { return base_ != nullptr; }
  
  NodeType getNodeType() const { return node_type_; }
  NodeInfo* getBaseNode() const { return base_; }

  Identifier getDescriptionFormat() const;
  Identifier getBaseDescription() const;
  Identifier getDescription() const;

  Identifier getRawDescription() const { return description_; }
  int getIndex() const { return index_; }

  std::shared_ptr<ParamInfo> getParamInfo() const;
  bool hasParamInfo() const;
  void setParamInfo(std::shared_ptr<ParamInfo> param_info);

  String debugString() const;

 private:
  NodeType node_type_;
  int index_ = -1;
  Identifier description_ = Identifier::null;
  Identifier format_ = Identifier::null;  // for indexed nodes only.
  NodeInfo* base_ = nullptr;  // for indexed nodes only.
  std::shared_ptr<ParamInfo> param_info_;
};

inline NodeInfo GroupNode(const Identifier& description) {
  return NodeInfo(NodeType::PATH, description);
}

struct PNode {
  PNode* children[16] = {nullptr};
  std::unique_ptr<NodeInfo> info = nullptr;
  PNode* range_base = nullptr;  // for indexed nodes only.

  ~PNode() {
    for (PNode* child : children) {
      if (child != nullptr) {
        delete child;
        child = nullptr;
      }
    }
  }

  bool isIndexed() { return range_base != nullptr; }
  PNode* getBase() {
    return isIndexed() ? range_base : this;
  }
};



class ParamAddrTree : private DeletedAtShutdown {

 public:
  JUCE_DECLARE_SINGLETON(ParamAddrTree, true)
  ~ParamAddrTree();
  const NodeInfo Find(const ParamAddr& address);

  NodeInfo* FindPtr(const ParamAddr& address);

  std::shared_ptr<ParamInfo> FindParamInfo(const ParamAddr& address);

  void Insert(const ParamAddr& address, const NodeInfo& info);

  void InsertParam(const ParamAddr& address, std::shared_ptr<ParamInfo> param_info);

  void InsertGroupNode(const ParamAddr& address, const Identifier& description);

  void InsertRange(const ParamAddrRange& range,
                   const NodeType node_type,
                   const Identifier& description,
                   const Identifier& format);

  void InsertParamRange(const ParamAddrRange& range,
                        const Identifier& description,
                        const Identifier& format,
                        const ParamProperties& props);

  ParamAddr InsertOffset(const ParamAddr& base_addr, const ParamAddr& offset_addr,
                    const NodeInfo& info);

  ParamAddr InsertRangeOffset(const ParamAddr& base_addr,
                         const ParamAddrRange& offset_range,
                         const NodeType node_type,
                         const Identifier& description,
                         const Identifier& format);

  std::shared_ptr<ParamInfo> InsertParamOffset(const ParamAddr& base_addr,
                                               const ParamAddr& offset_addr,
                                               const Identifier& description,
                                               const ParamProperties& props);

  ParamAddr InsertParamRangeOffset(const ParamAddr& base_addr,
                                   const ParamAddrRange& offset_range,
                                   const Identifier& description,
                                   const Identifier& format,
                                   const ParamProperties& props);

  ParamPath GetPath(const ParamAddr& address);

  ParamPath GetPathFromBytes(uint8* addr, uint8 num_bytes);

  NodeInfo* GetNodeAndPath(const ParamAddr& address, ParamPath* path);
  
  NodeInfo* GetNodeAndPathFromBytes(uint8* addr, uint8 num_bytes, ParamPath* path);

  std::vector<ParamUpdate> GetParamUpdates(uint8* addr_bytes, uint8* data, int num_bytes);

  bool HasData();
  void Reset();

 private:
  PNode* visitHigh(PNode* node, ParamAddr address, ParamPath* path);
  PNode* visitLow(PNode* node, ParamAddr address, ParamPath* path);
  PNode* insertHigh(PNode* node, ParamAddr address, const NodeInfo& info, PNode* const base);
  PNode* insertLow(PNode* node, ParamAddr address, const NodeInfo& info, PNode* const base);
  void insertIndexedNode(const ParamAddr& address, const NodeInfo& info, PNode* const base);
  std::function<PNode*(PNode*, ParamAddr, const NodeInfo&)>
  insertFunc(const ParamAddr& address);
  
  PNode* root_ = nullptr;
};
