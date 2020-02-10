/*
  ==============================================================================

    RolandSysexCommunicator.h
    Created: 10 Jan 2020 10:05:14pm
    Author:  keith

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class RolandSysexCommunicator : public MidiInputCallback {
  public:
    void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;
    int getDeviceID(const uint8* sysex_data) {
      std::cout << "DeviceID = " << sysex_data[1];
      return sysex_data[1];
    }
};



//namespace roland {
bool isRolandSysex(const MidiMessage& message);
bool isDT1(const uint8* sysex_data);
int getDeviceID(const uint8* sysex_data);
bool isIntegra7(const uint8* sysex_data);
String RolandSysexDebugString(const MidiMessage& message);

//}  // namespace RolandSysexMessage