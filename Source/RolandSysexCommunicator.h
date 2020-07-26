/*
  ==============================================================================

    RolandSysexCommunicator.h
    Created: 10 Jan 2020 10:05:14pm
    Author:  keith

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct DT1 {
  uint8 address[4];
  uint8* data;
  int length;
};

class RolandSysexCommunicator : public MidiInputCallback {
  public:
    void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;
    int getDeviceID(const uint8* sysex_data) {
      std::cout << "DeviceID = " << sysex_data[1];
      return sysex_data[1];
    }
  void parseDT1(const MidiMessage& message, DT1* dt1);
  virtual void handleDT1(const DT1& dt1) {}
};

//namespace roland {
bool isRolandSysex(const MidiMessage& message);
bool isDT1(const uint8* sysex_data);
bool isDT1(const MidiMessage& message);
int getDeviceID(const uint8* sysex_data);
bool isIntegra7(const MidiMessage& message);
String RolandSysexDebugString(const MidiMessage& message);

void dt1Received();

//}  // namespace RolandSysexMessage
