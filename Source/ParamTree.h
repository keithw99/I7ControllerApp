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
  static PTree getAddressTree();
};

class ParamTree {


  private:
   ValueTree root_;
};