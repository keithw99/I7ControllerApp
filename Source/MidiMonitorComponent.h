/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "RolandSysexCommunicator.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MidiMonitorComponent  : public Component,
                              public MidiInputCallback
{
public:
    //==============================================================================
    MidiMonitorComponent ();
    ~MidiMonitorComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    class IncomingMessageCallback   : public CallbackMessage {
     public:
        IncomingMessageCallback (MidiMonitorComponent* o, const MidiMessage& m, const String& s)
           : owner (o), message (m), source (s)
        {}
        void messageCallback() override
        {
            if (owner != nullptr)
                owner->addMessageToList (message, source);
        }
        Component::SafePointer<MidiMonitorComponent> owner;
        MidiMessage message;
        String source;
    };

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override;
    void postMessageToList(const MidiMessage& message, const String& source);
    void addMessageToList(const MidiMessage& message, const String& source);
    static String formatLogEntry(const MidiMessage& m);
    void logMessage (const String& m);

    double startTime_;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TextEditor> midiMessagesBox_;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiMonitorComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

