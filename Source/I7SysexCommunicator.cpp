/*
  ==============================================================================

    I7SysexCommunicator.cpp
    Created: 10 Jan 2020 10:04:29pm
    Author:  keith

  ==============================================================================
*/

#include "I7SysexCommunicator.h"

uint8 i7ModelID[3] = {0x00, 0x00, 0x64};

I7SysexCommunicator::I7SysexCommunicator(uint8 deviceID) : RolandSysexCommunicator(deviceID, i7ModelID)
{
  initializeParamTree();

}

void I7SysexCommunicator::initializeParamTree() {
  addrTree_ = AddressTreeBuilder::getAddressTree();
  // paramTemplate_ = ParamTreeTemplateBuilder::BuildTemplate();
}

void I7SysexCommunicator::requestStudioSetParts()
{
  ParamPath p = {
    {"Temporary Studio Set"}, {"Studio Set Part", 1}, {"Tone Bank Select MSB (CC# 0)"}
  };
  //uint32 address = addrTree_->GetAddressFromPath(p);
  uint32 address = ParamTree::GetAddressFromPath(p);
  
  sendRQ1(address, 3);
}

void I7SysexCommunicator::dt1Received(const uint8* address, const uint8* data, int size)
{
  std::vector<ParamUpdate> updates = addrTree_->GetParamUpdates(address, data, size);
  
  if (updates.size() >= 3 &&
      updates[0].path.size() >= 2 &&
      updates[0].path[0].node_id == TemporaryStudioSet &&
      updates[0].path[1].node_id == StudioSetPart) {
    handleStudioSetPart(updates);
  }
  for (auto update : updates) {
    DBG (update.toString() + "\n");
    DBG (update.getOscAddress().toString());
  }
}

void I7SysexCommunicator::handleStudioSetPart(const std::vector<ParamUpdate>& updates)
{
  if (updates[0].path.size() == 3 &&
      updates[0].path[2].node_id == ToneBankSelectMSB) {
    int partNumber = updates[0].path[1].index;
    handleToneSelect(updates, partNumber);
  }
}

void I7SysexCommunicator::handleToneSelect(const std::vector<ParamUpdate>& updates, const int partNumber)
{
  int msb = 0, lsb = 0, pc = 0;
  for (const ParamUpdate& update : updates) {
    const Identifier& nodeId = update.path[2].node_id;
    if (nodeId == ToneBankSelectMSB) {
      msb = update.value;
      continue;
    }
    if (nodeId == ToneBankSelectLSB) {
      lsb = update.value;
      continue;
    }
    if (nodeId == TonePC) {
      pc = update.value;
      continue;
    }
  }
  ToneId tid = BankSelect::getToneIdFor({msb, lsb}, pc);
  handleToneSelectUpdate(partNumber, tid);
}

String Integra7SysexDebugString(const MidiMessage& message) {
  ParamAddrTree* addrTree = AddressTreeBuilder::getAddressTree();
  const uint8* data = message.getSysExData();
  int len = message.getSysExDataSize();
  String msg = "Roland {";
  msg += "DeviceID: " + String(deviceIDOf(data));
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
