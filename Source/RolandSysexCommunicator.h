/*
  ==============================================================================

    RolandSysexCommunicator.h
    Created: 10 Jan 2020 10:05:14pm
    Author:  keith

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ParamBase.h"

class RolandSysexCommunicator : public MidiInputCallback {
public:
  RolandSysexCommunicator(uint8 deviceID, uint8* modelID);

  
  MidiOutput* getSysexOutputDevice() { return sysexOutputDevice_; }
  void setSysexOutputDevice(MidiOutput* device) { sysexOutputDevice_ = device; }
  
  uint8 getRolandDeviceID() { return deviceID_; }
  void setRolandDeviceID(int deviceID) { deviceID_ = deviceID; }
  
  void sendRQ1(const uint32 address, const uint32 size);
  void sendDT1(const uint32 address, const uint8* data, const int dataSize);
  
  // Must be implemented in derived class.
  virtual void dt1Received(const uint8* address, const uint8* data, int size) = 0;
  
  // Implements MidiInputCallback.
  void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;
  
  
private:
  static uint8 calculateChecksum(uint8* msg, int msgSize);
  void sendSysex(const uint8 commandID, const uint8* data, const int dataSize);
  //void parseDT1(const MidiMessage& message, DT1* dt1);
  //virtual void handleDT1(const DT1& dt1) {}
  
  // Private data members.
  MidiOutput* sysexOutputDevice_ = nullptr;
  uint8 sysexID_ = 0x41;
  uint8 deviceID_;
  uint8 modelID_[3];
};

//namespace roland {
bool isRolandSysex(const MidiMessage& message);
bool isRolandSysex(const uint8* sysexData);

bool isDT1(const uint8* sysexData);
bool isDT1(const MidiMessage& message);

uint8 deviceIDOf(const uint8* sysex_data);
bool compareModelID(const uint8* modelID1, const uint8* modelID2);
bool isIntegra7(const MidiMessage& message);
String RolandSysexDebugString(const MidiMessage& message);

void dt1Received();

//}  // namespace RolandSysexMessage
