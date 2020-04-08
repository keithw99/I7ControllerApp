/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "I7SysexCommunicator.h"
#include "MidiMonitorComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public Component {
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // Loads user settings if available.
    void initializeSettings();

    // Returns the default Midi input device to be used.
    MidiDeviceInfo getDefaultDevice(const Array<MidiDeviceInfo>& devices);

    // Enables and sets the active midi input device.
    void setMidiInput(int index);

    //==============================================================================
    // Your private member variables go here...
    AudioDeviceManager deviceManager_;
    ComboBox midiInputList_;
    Label midiInputListLabel_;
    int lastInputIndex_ = 0;

    I7SysexCommunicator i7Communicator_;
    MidiMonitorComponent midiMonitorComponent_;
    ApplicationProperties appProperties_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
