/*
  ==============================================================================

    ParamTree.cpp
    Created: 2 Feb 2020 5:01:33am
    Author:  keith

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ParamTree.h"
//#include "Constants.h"

struct enumHash {
  template <typename T>
  std::size_t operator()(T t) const {
    return static_cast<std::size_t>(t);
  }
};

static const std::unordered_map<String, TreeType>
getTreeTypeIndexMap() {
  std::unordered_map<String, TreeType> m = {
    {tree::Template, TreeType::TEMPLATE},
    {tree::Group, TreeType::GROUP},
    {tree::GroupRange, TreeType::GROUP_RANGE},
    {tree::Parameter, TreeType::PARAM},
    {tree::ParameterRange, TreeType::PARAM_RANGE},
    {tree::TextParameter, TreeType::PARAM_TEXT},
  };
  return m;
}

static const std::unordered_map<TreeType, NodeType, enumHash>
getNodeTypeMap() {
  std::unordered_map<TreeType, NodeType, enumHash> m = {
    {TreeType::TEMPLATE, NodeType::NIL},
    {TreeType::GROUP, NodeType::PATH},
    {TreeType::GROUP_RANGE, NodeType::INDEXED_PATH},
    {TreeType::PARAM, NodeType::PARAM},
  };
  return m;
}

var getProperty(ValueTree t, String prop_name) {
 var prop = t.getProperty(prop_name);
  if (prop.isVoid()) {
    // TODO: Throw error.
    DBG("ERROR: " << prop_name << " is void.");
    return var();
  }
 return prop;
}

bool hasParamTemplate(ValueTree t) {
  return t.hasProperty(prop::param::param_template);
}

// Forward declarations.
void parseTemplateNode(ValueTree t, ParamAddrTree& addr_tree, const ParamAddr& base_addr);
TreeType getType(ValueTree t);
void parseTemplateChildren(ValueTree t, ParamAddrTree& addr_tree, const ParamAddr& base_addr);
void parseGroupNode(ValueTree t, ParamAddrTree& addr_tree, const ParamAddr& base_addr);
void parseGroupRange(ValueTree t, ParamAddrTree& addr_tree, const ParamAddr& base_addr);
void parseParamNode(ValueTree t, ParamAddrTree& addr_tree, const ParamAddr& base_addr);
void parseParamRange(ValueTree t, ParamAddrTree& addr_tree, const ParamAddr& base_addr);
void parseTextParam(ValueTree t, ParamAddrTree& addr_tree, const ParamAddr& base_addr);
ParamAddr extractAddr(ValueTree t);
ParamAddr extractParamAddr(ValueTree t);
//ParamAddrRange extractAddrRange(ValueTree t);
ParamAddrRange extractParamAddrRange(ValueTree t);
ParamAddrRange extractIntParamProperties(ValueTree t);
ParamAddrRange extractFloatParamProperties(ValueTree t);
ParamAddrRange extractChoiceParamProperties(ValueTree t);
ParamAddrRange extractAsciiParamProperties(ValueTree t);
String extractNodeDescription(ValueTree t);
bool hasParamTemplate(ValueTree t);
ParamProperties makeParamPropertiesFromTemplate(const String& param_template);

ParamAddrTree* AddressTreeBuilder::instance_;

//ParamAddrTree AddressTreeBuilder::getAddressTree() {
ParamAddrTree* AddressTreeBuilder::getAddressTree() {
  //if (instance_ == NULL) {
    //ParamAddrTree addr_tree;
    //instance_ = new ParamAddrTree();
  ValueTree t = ParamTreeTemplateBuilder::getTemplate();
  //parseTemplateNode(t.getRoot(), addr_tree, ZeroAddr());
  instance_ = ParamAddrTree::getInstance();
  parseTemplateNode(t.getRoot(), *instance_, ZeroAddr());
  //}
  //return addr_tree; 
  return instance_;
  //return instance_;
}

void parseTemplateNode(ValueTree t, ParamAddrTree& addr_tree, const ParamAddr& base_addr) {
  //DBG("parsing...");
  TreeType tt = getType(t);
  switch (tt) {
  case TreeType::TEMPLATE:
    //DBG("parsing template");
    parseTemplateChildren(t, addr_tree, base_addr);
    break;
  case TreeType::GROUP:
    //DBG("parsing group");
    parseGroupNode(t, addr_tree, base_addr);
    break;
  case TreeType::GROUP_RANGE:
    //DBG("parsing group range");
    parseGroupRange(t, addr_tree, base_addr);
    break;
  case TreeType::PARAM:
    //DBG("parsing param");
    parseParamNode(t, addr_tree, base_addr);
    //DBG("finished parseparamnode");
    break;
  case TreeType::PARAM_TEXT:
    //DBG("parsing param text");
    parseTextParam(t, addr_tree, base_addr);
    // Fallthrough intentional.
  case TreeType::PARAM_RANGE:
    //DBG("parsing param range");
    parseParamRange(t, addr_tree, base_addr);
    break;
  default:
    // TODO: Throw error.
    DBG("ERROR: Unknown Template type: " << int(tt));
    return;
  }
}

TreeType getType(ValueTree t) {
  const auto& tIndex = getTreeTypeIndexMap();
  const auto tType = t.getType().toString();
  const auto found = tIndex.find(tType);
  if (found == tIndex.end()) {
    // TODO: Throw error
    DBG("ERROR: Unknown Template type: " << tType);
    return TreeType::INVALID;
  }
  return found->second;
}

String extractNodeDescription(ValueTree t) {
  var desc = t.getProperty(prop::desc);
  if (desc.isVoid()) {
    // TODO: Throww error.
    return "";
  }
  return desc;
}

void parseGroupNode(ValueTree t, ParamAddrTree& addr_tree, const ParamAddr& base_addr) {
  //ParamAddr paddr = base_addr + extractAddr(t);
    ParamAddr paddr = extractAddr(t);
  String desc = extractNodeDescription(t);
  NodeInfo grp_node(NodeType::PATH, desc);
  ParamAddr abs_addr = addr_tree.InsertOffset(base_addr, paddr, grp_node);
  
  // Recurse into children.
  parseTemplateChildren(t, addr_tree, abs_addr);
}

ParamProperties makeParamPropertiesFromTemplate(const String& param_template) {
  return ParamProperties::fromTemplate(param_template);
}

void extractBaseParamProperties(ValueTree t, ParamProperties* props) {
  props->param_type = GetParamType(getProperty(t, prop::param::type));
  props->size = getProperty(t, prop::param::size);
}

void extractIntParamProperties(ValueTree t, ParamProperties* props) {
  props->display_min = props->min = getProperty(t, prop::param::min);
  props->display_max = props->max = getProperty(t, prop::param::max);
  
  if (t.hasProperty(prop::param::display_min))
    props->display_min = getProperty(t, prop::param::display_min);

  if (t.hasProperty(prop::param::display_max))
    props->display_max = getProperty(t, prop::param::display_max);

  if (t.hasProperty(prop::param::step))
    props->step = getProperty(t, prop::param::step);
}

void extractChoiceParamProperties(ValueTree t, ParamProperties* props) {
    extractIntParamProperties(t, props);
  String choice_list = getProperty(t, prop::param::choice_list);
  //DBG("got choice_list");
  props->choices = choice::getChoicesFor(choice_list);
  //DBG("got choices");
}

void extractFloatParamProperties(ValueTree t, ParamProperties* props) {
  int decimal_places = 1, decimal_places_max = 1;  // default if not provided.
  
  // Get min float value with decimal places.
  String dmin = getProperty(t, prop::param::display_min);
  props->display_float_min = dmin.getFloatValue();
  StringArray parts_min = StringArray::fromTokens(dmin, ".", "");
  if (parts_min.size() == 2) {
    decimal_places = parts_min[1].length();
  }

  // Get max float value and its decimal_places.
  String dmax = getProperty(t, prop::param::display_max);
  props->display_float_max = dmax.getFloatValue();
  StringArray parts_max = StringArray::fromTokens(dmax, ".", "");
  if (parts_max.size() == 2) {
    decimal_places_max = parts_max[1].length();
  }

  // Take the greater decimal places of the two.
  if (decimal_places_max > decimal_places) {
    decimal_places = decimal_places_max;
  }
  props->decimal_places = decimal_places;

  // Get the step.
  if (t.hasProperty(prop::param::step))
    props->step = getProperty(t, prop::param::step);
}

void extractAsciiParamProperties(ValueTree t, ParamProperties* props) {
  props->display_min = props->min = 32;
  props->display_max = props->max = 127;
}

ParamProperties extractParamProperties(ValueTree t) {
  if (hasParamTemplate(t)) {
    return makeParamPropertiesFromTemplate(getProperty(t, prop::param::param_template));
  }

  ParamProperties props;
  extractBaseParamProperties(t, &props);
  switch (props.param_type) {
    case ParamType::INT:
      extractIntParamProperties(t, &props);
      break;
    case ParamType::CHOICE:
      extractChoiceParamProperties(t, &props);
      break;
    case ParamType::FLOAT:
      extractIntParamProperties(t, &props);
      extractFloatParamProperties(t, &props);
      break;
    case ParamType::ASCII:
      extractAsciiParamProperties(t, &props);
      break;
    default:
      DBG("ERROR: Cannot extract param props yet");
      return ParamProperties();
  }
  return props;
}

void parseParamNode(ValueTree t, ParamAddrTree& addr_tree, const ParamAddr& base_addr) {
  //DBG("parsing param node");
  ParamAddr paddr = extractParamAddr(t);
  paddr.len = 8;
  String desc = extractNodeDescription(t);
  //DBG("desc: " + desc);
  ParamProperties props = extractParamProperties(t);
  //DBG("got props");
  addr_tree.InsertParamOffset(base_addr, paddr, desc, props);
  //DBG("parsed param node");
  //DBG("end of function");
}

void parseGroupRange(ValueTree t, ParamAddrTree& addr_tree, const ParamAddr& base_addr) {
  String desc = extractNodeDescription(t);
  ParamAddrRange prange = ParamTree::extractAddrRange(t);
  String fmt = getProperty(t, prop::fmt);
  ParamAddr range_base_addr = addr_tree.InsertRangeOffset(
    base_addr, prange, NodeType::INDEXED_PATH, desc, fmt);

  // Recurse into children.
  parseTemplateChildren(t, addr_tree, range_base_addr);
}

void parseParamRange(ValueTree t, ParamAddrTree& addr_tree, const ParamAddr& base_addr) {
  String desc = extractNodeDescription(t);
  //std::cout << "**************" << desc << "*************" << std::endl;
  ParamAddrRange prange = extractParamAddrRange(t);
  String fmt = getProperty(t, prop::fmt);
  ParamProperties props = extractParamProperties(t);
  // ParamAddr range_base_addr =
  addr_tree.InsertParamRangeOffset(base_addr, prange, desc, fmt, props);
}

void parseTextParam(ValueTree t, ParamAddrTree& addr_tree, const ParamAddr& base_addr) {
  return;
}

void parseTemplateChildren(ValueTree t, ParamAddrTree& addr_tree, const ParamAddr& base_addr) {
  int numChildren = t.getNumChildren();
  for (int i = 0; i < numChildren; ++i) {
    parseTemplateNode(t.getChild(i), addr_tree, base_addr);
  }
}

ParamAddr extractAddr(ValueTree t) {
  int addr = getProperty(t, prop::addr);
  int len = getProperty(t, prop::len);
  return ParamAddr(addr, len);
}

ParamAddr extractParamAddr(ValueTree t) {
  int addr = getProperty(t, prop::addr);
  // All params have max addr length (8 nibbles).
  return ParamAddr(addr, 8);
}

ParamAddrRange extractAddrRangeWithLength(ValueTree t, int len) {
  ParamAddr paddr1 = ParamAddr(int(getProperty(t, prop::first_addr)), len);
  uint32 addr2 = int(getProperty(t, prop::last_addr));
  int i1 = getProperty(t, prop::first_index);
  int i2 = getProperty(t, prop::last_index);
  auto prange = ParamAddrRange(paddr1, addr2, i1, i2);
  return prange;
}

//ParamAddrRange extractAddrRange(ValueTree t) {
ParamAddrRange ParamTree::extractAddrRange(ValueTree t) {
  int len = getProperty(t, prop::len);
  return extractAddrRangeWithLength(t, len);
}

ParamAddrRange extractParamAddrRange(ValueTree t) {
  auto prange = extractAddrRangeWithLength(t, 8);
  return prange;
}

uint32 ParamTree::GetAddressFromPath(const ParamPath& path)
{
  ValueTree t = ParamTreeTemplateBuilder::getTemplate();
  uint32 address = 0;
  
  for (const ParamPathElement& pe : path) {
    if (t.getChildWithName("Template").isValid()) {
      t = t.getChildWithName("Template");
    }
    t = t.getChildWithProperty(prop::desc, pe.node_id.toString());
    if (!t.isValid()) {
      DBG ("ERROR: Could not find node '" + pe.node_id.toString() + "' in address tree");
      return address;
    }
    
    // Process non-indexed node.
    if (pe.index < 0) {
      if (!t.hasProperty(prop::addr)) {
        DBG ("ERROR: expected prop 'addr' from tree node: " + t.getType().toString());
        return address;
      }
      int intAddr = t.getProperty(prop::addr);
      address |= static_cast<uint32>(intAddr);
      continue;
    }
    
    // Process indexed node.
    if (!t.hasProperty(prop::first_addr) || !t.hasProperty(prop::last_addr)) {
      DBG ("ERROR: expected prop 'first_addr' and 'last_addr' for indexed node: " + t.getType().toString());
    }
    
    ParamAddrRange prange = ParamTree::extractAddrRange(t);
    address |= prange.GetNthAddr(pe.index).address;
    
    /*
    int firstAddr = t.getProperty(prop::first_addr);
    int lastAddr = t.getProperty(prop::last_addr);
    int firstIndex = t.getProperty(prop::first_index);
    int lastIndex = t.getProperty(prop::last_index);
    
    int addrInc = (lastAddr - firstAddr) / (lastIndex - firstIndex + 1);
    int intAddr = firstAddr + pe.index * addrInc;
    address |= static_cast<uint32>(intAddr);
    */
  }
  
  return address;
}
