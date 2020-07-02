/*
  ==============================================================================

    I7Controller.h
    Created: 13 Jun 2020 9:40:09pm
    Author:  Keith

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "I7SysexCommunicator.h"
#include "Settings.h"

class I7Controller : private I7SysexCommunicator,
                     private OSCSender,
                     private OSCReceiver,
                     private OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>,
                     private ValueTree::Listener
{
  
public:
  I7Controller();
  ~I7Controller();
  void setMidiInput(const String& identifier);
  void setMidiOutput(const String& identifier);
  void addMidiInputCallback(MidiInputCallback* callback);
  
  // Public member access.
  Settings* getSettings() { return &settings_; }
  ValueTree getMidiSettings();
  AudioDeviceManager* getDeviceManager() { return &deviceManager_; }
  
  // Overrides ValueTree::Listener.
  void valueTreePropertyChanged(ValueTree& t, const Identifier& property) override;
  
  
private:
  void oscMessageReceived(const OSCMessage& message) override;
  void midiInputChanged(const String& identifier);
  void midiOutputChanged(const String& identifier);
  
  // Data members.
  AudioDeviceManager deviceManager_;
  Settings settings_;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (I7Controller)
};
