/*
  ==============================================================================

    I7SysexCommunicator.h
    Created: 10 Jan 2020 10:04:29pm
    Author:  keith

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "RolandSysexCommunicator.h"

#include "ParamTree.h"

class I7SysexCommunicator : public RolandSysexCommunicator {
  public:
    I7SysexCommunicator();

    
  private:
    void initializeParamTree();
    
    ParamAddrTree addrTree_;
    ValueTree paramTree_;
    ValueTree paramTemplate_;

};

String Integra7SysexDebugString(const MidiMessage& message);
