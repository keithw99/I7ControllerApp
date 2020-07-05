/*
  ==============================================================================

    I7SysexCommunicator.cpp
    Created: 10 Jan 2020 10:04:29pm
    Author:  keith

  ==============================================================================
*/

#include "I7SysexCommunicator.h"

I7SysexCommunicator::I7SysexCommunicator() {
  initializeParamTree();
 
}

void I7SysexCommunicator::initializeParamTree() {
  //addrTree_ = AddressTreeBuilder::getAddressTree();
  // paramTemplate_ = ParamTreeTemplateBuilder::BuildTemplate();
}

String Integra7SysexDebugString(const MidiMessage& message) {
  ParamAddrTree* addrTree = AddressTreeBuilder::getAddressTree();
  const uint8* data = message.getSysExData();
  int len = message.getSysExDataSize();
  String msg = "Roland {";
  msg += "DeviceID: " + String(getDeviceID(data));
  if (isIntegra7(message)) {
    msg += ", Model: Integra-7";
  }
  if (isDT1(data)) {
    msg += ", Cmd: DT1, ";
    uint8 dt1_addr[4];
    for (int i = 0; i < 4; ++i) {
      dt1_addr[i] = data[i + 6];
    }
    uint8 dt1_data[len-10];
    for (int i = 0; i < len - 11; ++i) {
      dt1_data[i] = data[i+10];
    }
    std::vector<ParamUpdate> updates = addrTree->GetParamUpdates(dt1_addr, dt1_data, len-11);
    for (auto update : updates) {
      msg += "\n" + update.toString() + "\n";
    }    
  }
  msg += ", Addr: [" + String::toHexString(data + 6, 4)  + "]";
  msg += ", Data: [" + String::toHexString(data + 10, len - 11) + "]";

  msg += "}";
 
  return msg;
}

int I7SysexCommunicator::getPartMidiChannel(const int partNumber)
{
  // TODO: look this up from the paramTree.
  return partNumber;
}
