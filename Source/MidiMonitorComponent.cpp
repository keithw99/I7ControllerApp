/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MidiMonitorComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MidiMonitorComponent::MidiMonitorComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    midiMessagesBox_.reset (new TextEditor ("Midi Messages Box"));
    addAndMakeVisible (midiMessagesBox_.get());
    midiMessagesBox_->setMultiLine (true);
    midiMessagesBox_->setReturnKeyStartsNewLine (true);
    midiMessagesBox_->setReadOnly (true);
    midiMessagesBox_->setScrollbarsShown (true);
    midiMessagesBox_->setCaretVisible (false);
    midiMessagesBox_->setPopupMenuEnabled (true);
    midiMessagesBox_->setText (String());

    midiMessagesBox_->setBounds (47, 64, 360, 280);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    if (!connect(9099))
       AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "Connection error",
                                          "Could not connect to UDP port 9099.",
                                          "OK");
    addListener(this, "/i7/tone_type");
    //[/Constructor]
}

MidiMonitorComponent::~MidiMonitorComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    midiMessagesBox_ = nullptr;

    //[/Destructor_pre]

    midiMessagesBox_ = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MidiMonitorComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MidiMonitorComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    auto area = getLocalBounds();
    midiMessagesBox_->setBounds(area.reduced (8));
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MidiMonitorComponent::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) {
  DBG("Received MIDI message");
  postMessageToList (message, source->getName());
  //if (message.isSysEx())
  //std::cout << "MMC: got sysex" << std::endl;
}

void MidiMonitorComponent::postMessageToList (const MidiMessage& message, const String& source) {
  (new IncomingMessageCallback (this, message, source))->post();
}

void MidiMonitorComponent::addMessageToList (const MidiMessage& message, const String& source) {
  auto time = message.getTimeStamp() - startTime_;
  auto hours   = ((int) (time / 3600.0)) % 24;
  auto minutes = ((int) (time / 60.0)) % 60;
  auto seconds = ((int) time) % 60;
  auto millis  = ((int) (time * 1000.0)) % 1000;
  auto timecode = String::formatted ("%02d:%02d:%02d.%03d",
                                     hours,
                                     minutes,
                                     seconds,
                                     millis);
  auto description = formatLogEntry(message);
  String midiMessageString (timecode + "  -  " + description + " (" + source + ")");
  logMessage (midiMessageString);
}

String MidiMonitorComponent::formatLogEntry (const MidiMessage& m) {
  if (m.isNoteOn())           return "Note on "          + MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
  if (m.isNoteOff())          return "Note off "         + MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
  if (m.isProgramChange())    return "Program change "   + String (m.getProgramChangeNumber());
  if (m.isPitchWheel())       return "Pitch wheel "      + String (m.getPitchWheelValue());
  if (m.isAftertouch())       return "After touch "      + MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) +  \
": " + String (m.getAfterTouchValue());
  if (m.isChannelPressure())  return "Channel pressure " + String (m.getChannelPressureValue());
  if (m.isAllNotesOff())      return "All notes off";
  if (m.isAllSoundOff())      return "All sound off";
  if (m.isMetaEvent())        return "Meta event";
  if (m.isController()) {
    String name (MidiMessage::getControllerName (m.getControllerNumber()));
    if (name.isEmpty())
      name = "[" + String (m.getControllerNumber()) + "]";
    return "Controller " + name + ": " + String (m.getControllerValue());
  }
  if (isIntegra7(m)) {
    return Integra7SysexDebugString(m);
  }
  if (isRolandSysex(m)) {
    return RolandSysexDebugString(m);
  }
  /*
      auto sysex_data = m.getSysExData();
      int sysex_len = m.getSysExDataSize();
      if (isDT1(sysex_data)) {
        return "Roland DT1 [DeviceID = " + String(getDeviceID(sysex_data)) + "]: " + String::toHexString(sysex_data+6, sysex_l\
en - 6);
      }
      return "Roland SysEx: " + String::toHexString(m.getSysExData(), m.getSysExDataSize());
  */

  // Default.
  return String::toHexString (m.getRawData(), m.getRawDataSize());
}

void MidiMonitorComponent::logMessage (const String& m) {
  midiMessagesBox_->moveCaretToEnd();
  midiMessagesBox_->insertTextAtCaret (m + newLine);
}

void MidiMonitorComponent::oscMessageReceived(const OSCMessage& message) {
  if (message.getAddressPattern().matches("/i7/tone_type")) {
    AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
                                        "OSC Received",
                                     "Received ToneType: " + String(message[0].getInt32()),
                                        "OK");
  }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MidiMonitorComponent" componentName=""
                 parentClasses="public Component, public MidiInputCallback, private OSCReceiver, private OSCReceiver::ListenerWithOSCAddress&lt;OSCReceiver::MessageLoopCallback&gt;"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTEDITOR name="Midi Messages Box" id="ab7b227210411cca" memberName="midiMessagesBox_"
              virtualName="" explicitFocusOrder="0" pos="47 64 360 280" initialText=""
              multiline="1" retKeyStartsLine="1" readonly="1" scrollbars="1"
              caret="0" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

