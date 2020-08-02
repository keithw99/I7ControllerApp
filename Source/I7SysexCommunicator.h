/*
  ==============================================================================

    I7SysexCommunicator.h
    Created: 10 Jan 2020 10:04:29pm
    Author:  keith

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_osc/juce_osc.h"
#include "RolandSysexCommunicator.h"

#include "ParamTree.h"
#include "MidiConstants.h"

const Identifier TemporaryStudioSet { "Temporary Studio Set" };
const Identifier StudioSetPart { "Studio Set Part" };
const Identifier ToneBankSelectMSB { "Tone Bank Select MSB (CC# 0)" };
const Identifier ToneBankSelectLSB { "Tone Bank Select LSB (CC# 32)" };
const Identifier TonePC { "Tone Program Number (PC)" };


class I7SysexCommunicator : public RolandSysexCommunicator
{
public:
  I7SysexCommunicator(uint8 deviceID);
  
  void requestStudioSetParts();
  void handleStudioSetPart(const std::vector<ParamUpdate>& updates);
  void handleToneSelect(const std::vector<ParamUpdate>& updates, const int partNumber);
  virtual void handleToneSelectUpdate(const int partNumber, const ToneId& toneId) {}
  
  int getPartMidiChannel(const int partNumber);
  
  // Overrides for RolandSysexCommunicator.
  void dt1Received(const uint8* address, const uint8* data, int size) override;
  
private:
  void initializeParamTree();
    
  // Private data members.
  int rolandDeviceID_ = 17;
  ParamAddrTree* addrTree_;
  ValueTree paramTree_;
  ValueTree paramTemplate_;

};

String Integra7SysexDebugString(const MidiMessage& message);
