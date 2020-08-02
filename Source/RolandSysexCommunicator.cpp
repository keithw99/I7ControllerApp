/*
  ==============================================================================

    RolandSysexCommunicator.cpp
    Created: 10 Jan 2020 10:05:14pm
    Author:  keith

  ==============================================================================
*/

#include "RolandSysexCommunicator.h"

/*
MidiMessage RolandSysexMessage::toMidiMessage()
{
  // Total size is:
  //   ID number (1) +
  //   Device ID (1) +
  //   Model ID (3) +
  //   Command ID (1) +
  //   Message Body (variable from getMessageBodySize()) +
  //   Checksum (1)
  int size = getMessageBodySize() + 7;
  uint8 rawData[size];

  rawData[0] = getIDNumber();
  rawData[1] = getDeviceID();
  memcpy(&rawData[2], getModelID(), 3);
  rawData[5] = getCommandID();
  memcpy(&rawData[6], getMessageBody(), getMessageBodySize());
  
  // Checksum is last byte.
  rawData[size-1] = calculateChecksum(&rawData[6], getMessageBodySize());
  return MidiMessage::createSysExMessage(&rawData, size);
}
*/

RolandSysexCommunicator::RolandSysexCommunicator(uint8 deviceID, uint8* modelID) : deviceID_(deviceID)
{
  //std::copy(modelID_, modelID_ + 3, modelID);
  std::copy(modelID, modelID + 3, modelID_);
}

void RolandSysexCommunicator::sendSysex(const uint8 commandID, const uint8 *data, const int dataSize)
{
  // Total size is:
  //   ID number (1) +
  //   Device ID (1) +
  //   Model ID (3) +
  //   Command ID (1) +
  //   Message Body (variable from getMessageBodySize()) +
  //   Checksum (1)
  int size = dataSize + 7;
  uint8 rawData[size];
  
  rawData[0] = sysexID_;
  rawData[1] = deviceID_ - 1;  // zero-based for Roland.
  //std::copy(&rawData[2], &rawData[5], modelID_);
  std::copy(modelID_, modelID_ + 3, &rawData[2]);
  rawData[5] = commandID;
  
  // Copy the message body.
  //std::copy(&rawData[6], &rawData[6] + dataSize, data);
  std::copy(&data[0], &data[0] + dataSize, &rawData[6]);
  
  // Checksum is last byte.
  rawData[size-1] = calculateChecksum(&rawData[6], dataSize);
  
  auto msg = MidiMessage::createSysExMessage(rawData, size);
  getSysexOutputDevice()->sendMessageNow(msg);
}

void RolandSysexCommunicator::sendRQ1(const uint32 address, const uint32 size)
{
  uint8 data[8];
  Unpack8Bit(address, &data[0], 4);
  Unpack8Bit(size, &data[4], 4);
  sendSysex(0x11, data, 8);
}

void RolandSysexCommunicator::sendDT1(const uint32 address, const uint8* data, const int dataSize)
{
  int size = dataSize + 4;
  uint8 body[size];
  Unpack7Bit(address, &body[0], 4);
  //std::copy(&body[4], &body[4] + dataSize, data);
  std::copy(data, data + dataSize, &body[4]);
  sendSysex(0x12, body, size);
}

void RolandSysexCommunicator::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) {
  if (!message.isSysEx()) {
    DBG ("ERROR: expected sysex, got: " + message.getDescription());
    return;
  }
  
  const uint8* sysex = message.getSysExData();
  int size = message.getSysExDataSize();
  
  if (!isRolandSysex(sysex)) {
    DBG ("ERROR: expected Roland ID (0x41), got: 0x" + String::toHexString(message.getSysExData()[0]));
    return;
  }

  if (deviceIDOf(sysex) != deviceID_ - 1) {
    DBG ("ERROR: expected device ID " + String(deviceID_) + ", got: " + String(deviceIDOf(sysex)));
    return;
  }
  
  if (size < 11) {
    DBG ("ERROR: sysex size less than DT1 minimum size 11, got: " + String(size));
    return;
  }
  
  if (!compareModelID(&sysex[2], &modelID_[2])) {
    DBG ("ERROR: unexpected model ID in sysex message");
  }
  
  if (!isDT1(sysex)) {
    DBG ("ERROR: expected DT1 message (0x12), got: " + String::toHexString(sysex[5]));
    return;
  }
  
  dt1Received(&sysex[6], &sysex[10], size - 11);
}

uint8 RolandSysexCommunicator::calculateChecksum(uint8* msg, int msgSize)
{
  int sum = 0;
  for (int i = 0; i < msgSize; ++i) {
    sum += msg[i];
  }
  return 128 - (sum & 0x7F);
}


bool isRolandSysex(const MidiMessage& message) {
  if (!message.isSysEx())
    return false;

  auto sysexPtr = message.getSysExData();
      return *sysexPtr == 0x41;
}

bool isRolandSysex(const uint8* sysexData)
{
  return sysexData[0] == 0x41;
}

bool isDT1(const uint8* sysexData) {
  return sysexData[5] == 0x12;
}    

bool isDT1(const MidiMessage& message)
{
  return isDT1(message.getSysExData());
}

uint8 deviceIDOf(const uint8* sysexData)
{
  return sysexData[1];
}

bool compareModelID(const uint8* modelID1, const uint8* modelID2)
{
  return modelID1[0] == modelID2[0] && modelID1[1] == modelID2[1] && modelID1[2] == modelID2[2];
}

bool isIntegra7(const MidiMessage& message) {
  auto sysex_data = message.getSysExData();
  return sysex_data[2] == 0 && sysex_data[3] == 0 && sysex_data[4] == 0x64;
}

String RolandSysexDebugString(const MidiMessage& message) {
  const uint8* data = message.getSysExData();
  int len = message.getSysExDataSize();
  String msg = "Roland {";
  msg += "DeviceID: " + String(deviceIDOf(data));
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
