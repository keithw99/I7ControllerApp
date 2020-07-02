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
  settings_.loadUserSettings();
}

I7Controller::~I7Controller()
{
  //const String& midiInput = settings_.
  //deviceManager_.removeMidiInputDeviceCallback(currentDeviceId, &midiMonitorComponent_);
}

void I7Controller::valueTreePropertyChanged(ValueTree& t, const Identifier& property)
{
  if (t.getType() == settings::Midi) {
    if (property == settings::midi::Input) {
      setMidiInput(t.getProperty(property));
    }
  }
}

void I7Controller::setMidiInput(const String& identifier)
{
  bool deviceExists = false;
  for (const MidiDeviceInfo& mdi : MidiInput::getAvailableDevices()) {
    if (mdi.identifier == identifier) {
      deviceExists = true;
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
}

ValueTree I7Controller::getMidiSettings()
{
  return settings_.getSettingsFor(settings::Midi);
}

void I7Controller::addMidiInputCallback(MidiInputCallback* callback)
{
  const String& deviceId = getMidiSettings().getProperty(settings::midi::Input);
  deviceManager_.addMidiInputDeviceCallback(deviceId, callback);
}

void I7Controller::oscMessageReceived(const OSCMessage& messsage) {}

void I7Controller::midiInputChanged(const String& identifier) {}

void I7Controller::midiOutputChanged(const String& identifier) {}
