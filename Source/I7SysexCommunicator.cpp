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
  addrTree_ = AddressTreeBuilder::getAddressTree();
  // paramTemplate_ = ParamTreeTemplateBuilder::BuildTemplate();
}

void I7SysexCommunicator::handleDT1(const DT1& dt1)
{
  std::vector<ParamUpdate> updates = addrTree_->GetParamUpdates(dt1.address, dt1.data, dt1.length);
  
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
