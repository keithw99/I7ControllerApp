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
#include "MidiConstants.h"
#include "Settings.h"

class I7Controller : private I7SysexCommunicator,
                     private OSCSender,
                     private OSCReceiver,
                     private OSCReceiver::Listener<OSCReceiver::MessageLoopCallback>,
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
  ValueTree getOscSettings();
  AudioDeviceManager* getDeviceManager() { return &deviceManager_; }
  
  // Implements I7SysexCommunicator.
  //MidiOutput* getSysexOutputDevice() override;
  
  // Overrides ValueTree::Listener.
  void valueTreePropertyChanged(ValueTree& t, const Identifier& property) override;
  void valueTreeChildAdded(ValueTree& parentTree, ValueTree& child) override;
  
  // MIDI control operations.
  void setToneForPart(const int partNumber, const ToneId& toneId);
  
private:
  void initializeOsc();
  void initializeMidi();
  void resetOscDestinations();
  
  // Overrides OSCReceiver.
  void oscMessageReceived(const OSCMessage& message) override;
  
  void sendOscMessage(const OSCMessage& message);
  void midiInputChanged(const String& identifier);
  void midiOutputChanged(const String& identifier);
  void oscPortChanged(const int portNumber);
  void oscDestinationChanged();
  void oscDestinationAdded(const String& ipAddress, const int port);
  
  // Events resulting from OSC or MIDI events.
  void handleToneSelectMessage(const OSCMessage& message);
  void handleToneSelectUpdate(const int partNumber, const ToneId& toneId) override;
  
  MidiBuffer getMidiMessagesFor(const int partNumber, const ToneId& toneId, MidiBuffer& buffer);

  
  // Data members.
  AudioDeviceManager deviceManager_;
  Settings settings_;
  Array<MidiInputCallback*> midiInputCallbacks_;
  String lastMidiInputId_;
  //std::unique_ptr<MidiOutput> midiOutput_;
  int lastOscPortNumber_;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (I7Controller)
};
