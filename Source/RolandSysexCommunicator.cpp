/*
  ==============================================================================

    RolandSysexCommunicator.cpp
    Created: 10 Jan 2020 10:05:14pm
    Author:  keith

  ==============================================================================
*/

#include "RolandSysexCommunicator.h"

void RolandSysexCommunicator::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) {
   //if (message.isSysEx()) {
   //  std::cout << "Got sysex!" << std::endl;
   //}
}

bool isRolandSysex(const MidiMessage& message) {
  if (!message.isSysEx())
    return false;

  auto sysexPtr = message.getSysExData();
      return *sysexPtr == 0x41;
}

bool isDT1(const uint8* sysex_data) {
  return sysex_data[5] == 0x12;
}    

int getDeviceID(const uint8* sysex_data) {
  return sysex_data[1] + 1; // convert from 0-based to 1-based.
}

bool isIntegra7(const MidiMessage& message) {
  auto sysex_data = message.getSysExData();
  return sysex_data[2] == 0 && sysex_data[3] == 0 && sysex_data[4] == 0x64;
}

String RolandSysexDebugString(const MidiMessage& message) {
  const uint8* data = message.getSysExData();
  int len = message.getSysExDataSize();
  String msg = "Roland {";
  msg += "DeviceID: " + String(getDeviceID(data));
  if (isIntegra7(message)) {
    msg += ", Model: Integra-7";
  }
  if (isDT1(data)) {
    msg += ", Cmd: DT1";
  }
  msg += ", Addr: [" + String::toHexString(data + 6, 4)  + "]";
  msg += ", Data: [" + String::toHexString(data + 10, len - 10) + "]";

  msg += "}";
  return msg;
}
