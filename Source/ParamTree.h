/*
  ==============================================================================

    ParamTree.h
    Created: 1 Feb 2020 12:33:58am
    Author:  keith

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include <unordered_map>

#include "ParamAddressTree.h"
#include "ParamTreeTemplate.h"

enum class TreeType {TEMPLATE, GROUP, GROUP_RANGE, PARAM, PARAM_RANGE, INVALID};

class AddressTreeBuilder {
 public:
  static PTree getAddressTree();
  
 private:
  //const static ValueTree template_;
  //static void parseTemplateNode(ValueTree t, PTree& addr_tree);
  //static void parseGroupNode(ValueTree t, PTree& addr_tree);
  //static void parseParamNode(ValueTree t, PTree& addr_tree);
  //static void parseTemplateChildren(ValueTree t, PTree& addr_tree);
  //static TreeType getType(ValueTree t);
  //static ParamAddr extractParamAddr(ValueTree t);
  //static NodeInfo buildNodeInfo(ValueTree t, TreeType tt);
  //const static std::unordered_map<String, TreeType> treeTypeIndex_;
};

class ParamTree {


  private:
   ValueTree root_;
};