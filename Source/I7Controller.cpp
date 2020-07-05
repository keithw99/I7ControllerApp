/*
  ==============================================================================

    I7Controller.cpp
    Created: 13 Jun 2020 9:40:09pm
    Author:  Keith

  ==============================================================================
*/

#include "I7Controller.h"

I7Controller::I7Controller() {
  // Initialize settings.
  settings_.addListener(this, settings::Midi);
  settings_.addListener(this, settings::Osc);
  settings_.loadUserSettings();
  
  initializeOsc();
  initializeMidi();
}

I7Controller::~I7Controller()
{
  //const String& midiInput = settings_.
  //deviceManager_.removeMidiInputDeviceCallback(currentDeviceId, &midiMonitorComponent_);
  OSCReceiver::disconnect();
  deviceManager_.setDefaultMidiOutputDevice("");
}

void I7Controller::valueTreePropertyChanged(ValueTree& t, const Identifier& property)
{
  if (t.getType() == settings::Midi) {
    if (property == settings::midi::Input)
      midiInputChanged(t.getProperty(property));
    
    else if (property == settings::midi::Output)
      midiOutputChanged(t.getProperty(property));

    return;
  }
  
  if (t.getType() == settings::Osc) {
    if (property == settings::osc::ServerPort) {
      oscPortChanged(t.getProperty(property));
      return;
    }
  }
}

void I7Controller::initializeOsc()
{
  OSCReceiver::addListener(this);
  int udpPort = settings_.getSettingsFor(settings::Osc).getProperty(settings::osc::ServerPort);
  if (!OSCReceiver::connect(udpPort))
    DBG ("ERROR connecting to UDP port " + String(udpPort) );
  lastOscPortNumber_ = udpPort;

}

void I7Controller::initializeMidi()
{
  const String& midiOutputId = settings_.getSettingsFor(settings::Midi).getProperty(settings::midi::Output);
  if (midiOutputId != deviceManager_.getDefaultMidiOutputIdentifier())
    setMidiOutput(midiOutputId);
}

void I7Controller::setMidiInput(const String& identifier)
{

  bool deviceExists = false;
  for (const MidiDeviceInfo& mdi : MidiInput::getAvailableDevices()) {
    if (mdi.identifier == identifier) {
      deviceExists = true;
      break;
    }
  }
  if (!deviceExists) return;
  
  if (!deviceManager_.isMidiInputDeviceEnabled(identifier))
    deviceManager_.setMidiInputDeviceEnabled(identifier, true);
  
  deviceManager_.addMidiInputDeviceCallback(identifier, this);
}

void I7Controller::setMidiOutput(const String& identifier)
{
  deviceManager_.setDefaultMidiOutputDevice(identifier);
  DBG ("Set MIDI Output to " + deviceManager_.getDefaultMidiOutputName());
}

ValueTree I7Controller::getMidiSettings()
{
  return settings_.getSettingsFor(settings::Midi);
}

void I7Controller::addMidiInputCallback(MidiInputCallback* callback)
{
  const String& deviceId = getMidiSettings().getProperty(settings::midi::Input);
  deviceManager_.addMidiInputDeviceCallback(deviceId, callback);
  midiInputCallbacks_.add(callback);
}

void I7Controller::oscMessageReceived(const OSCMessage& message) {
  const auto& pattern = message.getAddressPattern();
  if (pattern.matches(osc::address::ToneSelect)) {
    handleToneSelectMessage(message);
  }
}

void I7Controller::midiInputChanged(const String& identifier)
{
  if (identifier == lastMidiInputId_) {
    // Nothing changed.
    return;
  }
    
  for (auto* cb : midiInputCallbacks_) {
      deviceManager_.removeMidiInputDeviceCallback(lastMidiInputId_, cb);
  }

  setMidiInput(identifier);
  
  for (auto* cb : midiInputCallbacks_) {
    deviceManager_.addMidiInputDeviceCallback(identifier, cb);
  }
  
  lastMidiInputId_ = identifier;
}

void I7Controller::midiOutputChanged(const String& identifier)
{
  if (identifier != deviceManager_.getDefaultMidiOutputIdentifier())
    setMidiOutput(identifier);
  
  

}

void I7Controller::setToneForPart(const int partNumber, const ToneId& toneId)
{
  MidiOutput* midiOut = deviceManager_.getDefaultMidiOutput();
  MidiBuffer buffer;
  getMidiMessagesFor(partNumber, toneId, buffer);
  //DBG ("buffer: ")
  midiOut->sendBlockOfMessagesNow(buffer);
}

void I7Controller::oscPortChanged(const int portNumber)
{
  if (portNumber == lastOscPortNumber_)
    return;
  
  OSCReceiver::disconnect();

  if (!OSCReceiver::connect(portNumber))
    DBG ("ERROR connecting to UDP port " + String(portNumber));
  
  lastOscPortNumber_ = portNumber;
}

MidiBuffer I7Controller::getMidiMessagesFor(const int partNumber, const ToneId& toneId, MidiBuffer& buffer)
{
  int channel = getPartMidiChannel(partNumber);

  const auto& pcid = BankSelect::getProgramChangeFor(toneId);
  buffer.addEvent(MidiMessage::controllerEvent(channel, 0, pcid.first.first), 0);  // CC 0 (MSB)
  buffer.addEvent(MidiMessage::controllerEvent(channel, 32, pcid.first.second), 0);  // CC 32 (LSB)
  buffer.addEvent(MidiMessage::programChange(channel, pcid.second), 0);
  
  return buffer;
}

void I7Controller::handleToneSelectMessage(const OSCMessage& message)
{
  if (message.size() != 4) {
    DBG ("ERROR: received invalid tone_select OSC message");
  }
  
  ToneId toneId = {
    static_cast<ToneType>(message[1].getInt32()),
    static_cast<Bank>(message[2].getInt32()),
    message[3].getInt32()
  };
  
  setToneForPart(message[0].getInt32(), toneId);
}
