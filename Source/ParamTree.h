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

enum class TreeType {TEMPLATE, GROUP, GROUP_RANGE, PARAM, PARAM_RANGE, PARAM_TEXT, INVALID};

class AddressTreeBuilder {
 public:
  static ParamAddrTree* getAddressTree();

 private:
  static ParamAddrTree* instance_;
};

class ParamTree {
public:
  static ParamAddrRange extractAddrRange(ValueTree t);
  static uint32 GetAddressFromPath(const ParamPath& path);
  
private:
  ValueTree root_;
};
