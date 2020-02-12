/*
  ==============================================================================

    Constants.cpp
    Created: 7 Feb 2020 10:53:54pm
    Author:  keith

  ==============================================================================
*/

#include <unordered_map>

#include "Constants.h"
#include "Utils.h"

StringArray addArray(const StringArray& a, const StringArray& b) {
  StringArray c = a;
  c.addArray(b);
  return c;
}

StringArray addArrays(const StringArray& single) {
  return single;
}

StringArray addArrays(const StringArray& first, const StringArray& second) {
  return addArray(first, second);
}

template<typename... Args>
StringArray addArrays(const StringArray& first, Args... others) {
  return addArray(first, addArrays(others...));
}

StringArray makeRange(int min, int max) {
  StringArray r;
  for (int i = min; i <= max; ++i) {
    r.add(String(i));
  }
  return r;
}

StringArray makeRange(int min, int max, String fmt) {
  StringArray r;
  for (int i = min; i <= max; ++i) {
    r.add(String(string_format(fmt.toStdString(), i)));
  }
  return r;
}

const StringArray soundMode = {
  "STUDIO", "GM1", "GM2", "GS"
};

const StringArray offOn = {
  "OFF", "ON"
};

const StringArray midiChannelPlusOff =
  addArray(makeRange(1, 16), {"OFF"});

const StringArray midiControlSource = 
  addArrays<StringArray>(
    StringArray{"OFF"},
    makeRange(1, 31, "CC%02d"), makeRange(33, 95, "CC%02d"),
    StringArray{"BEND", "AFT"}
  );

const StringArray controlSource = {
  "SYSTEM", "STUDIO SET"
};

const StringArray clockSource = {
  "MIDI", "USB"
};

const StringArray audioOutput = {
  "SPEAKER", "PHONES"
};

const StringArray voiceReserve =
  addArrays<StringArray>(makeRange(0, 63), StringArray{"FULL"});
  
const StringArray offPartNumber =
  addArrays<StringArray>(StringArray{"OFF"}, makeRange(1, 16));

const StringArray letteredOutputs = {
  "A", "B", "C", "D"
};

const StringArray outputAssign =
  addArrays<StringArray>(letteredOutputs, makeRange(1, 8));

const StringArray partOutputAssign =
  addArrays<StringArray>(StringArray{"PART"}, outputAssign);

const StringArray chorusType = {
  "OFF", "Chorus", "Delay", "GM2 Chorus"
};

const StringArray chorusOutputSelect = {
  "MAIN", "REV", "MAIN+REV"
};

const StringArray reverbType = {
  "OFF", "Room 1", "Room 2", "Hall 1", "Hall 2", "Plate", "GM2 Reverb"
};

const StringArray roomType = {
  "ROOM1", "ROOM2", "HALL1", "HALL2",
};

const StringArray roomSize = {
  "SMALL", "MEDIUM", "LARGE"
};

const StringArray eqLowFreq = {
  "200", "400"
};

const StringArray eqMidFreq = {
  "200", "250", "315", "400", "500", "630",
  "800", "1000", "1250", "1600", "2000",
  "2500", "3150", "4000", "5000", "6300",
  "8000"
};

const StringArray eqHighFreq = {
  "2000", "4000", "8000"
};

const StringArray eqQ = {
  "0.5", "1.0", "2.0", "4.0", "8.0"
};

const StringArray monoPolyTone = {
  "MONO", "POLY", "TONE"
};

const StringArray offOnTone = {
  "OFF", "ON", "TONE"
};

const StringArray pitchBendRangeTone =
  addArrays<StringArray>(makeRange(0, 24), StringArray{"TONE"});

const StringArray midiByte = makeRange(0, 127);

const StringArray midiByteTone =
  addArrays<StringArray>(midiByte, StringArray{"TONE"});

const StringArray keyScale = {
  "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};

/*
StringArray fullKeyboardRange() {
  int i = 0;
  int octave = -1;
  StringArray keyRange;
  for (int octave = -1; octave <= 9; ++octave) {
    for (const String& key : keyScale) {
      keyRange.add(key + String(octave));
      if (i >= 127) break;
    }
  }
  return keyRange;
}
*/

StringArray fullKeyboardRange() {
  StringArray keyRange;
  for (int i = 0; i < 128; ++i) {
    keyRange.add(MidiMessage::getMidiNoteName(i, true, true, 4));
  }
  return keyRange;
}
const StringArray keyboardRange = fullKeyboardRange();

const StringArray offMute = {
  "OFF", "MUTE"
};

const StringArray scaleType = {
  "CUSTOM", "EQUAL", "JUST-MAJ", "JUST-MIN", "PYTHAGORE",
  "KIRNBERGE", "MEANTONE", "WERCKMEIS", "ARABIC"
};

const StringArray velocityCurve =
  addArrays<StringArray>(StringArray{"OFF"}, makeRange(1, 4));
  
static ChoiceListMap buildChoiceMap() {
  return {
    {choice::SoundMode, std::make_shared<StringArray>(soundMode)},
    {choice::OffOn, std::make_shared<StringArray>(offOn)},
    {choice::MidiChannelPlusOff, std::make_shared<StringArray>(midiChannelPlusOff)},
    {choice::MidiControlSource, std::make_shared<StringArray>(midiControlSource)},
    {choice::ControlSource, std::make_shared<StringArray>(controlSource)},
    {choice::ClockSource, std::make_shared<StringArray>(clockSource)},
    {choice::AudioOutput, std::make_shared<StringArray>(audioOutput)},
    {choice::VoiceReserve, std::make_shared<StringArray>(voiceReserve)},
    {choice::OffPartNumber, std::make_shared<StringArray>(offPartNumber)},
    {choice::OutputAssign, std::make_shared<StringArray>(outputAssign)},
    {choice::PartOutputAssign, std::make_shared<StringArray>(partOutputAssign)},
    {choice::ChorusType, std::make_shared<StringArray>(chorusType)},
    {choice::ChorusOutputSelect, std::make_shared<StringArray>(chorusOutputSelect)},
    {choice::ReverbType, std::make_shared<StringArray>(reverbType)},
    {choice::LetteredOutputs, std::make_shared<StringArray>(letteredOutputs)},
    {choice::RoomType, std::make_shared<StringArray>(roomType)},
    {choice::RoomSize, std::make_shared<StringArray>(roomSize)},
    {choice::EqLowFreq, std::make_shared<StringArray>(eqLowFreq)},
    {choice::EqMidFreq, std::make_shared<StringArray>(eqMidFreq)},
    {choice::EqHighFreq, std::make_shared<StringArray>(eqHighFreq)},
    {choice::EqQ, std::make_shared<StringArray>(eqQ)},
    {choice::MonoPolyTone, std::make_shared<StringArray>(monoPolyTone)},
    {choice::OffOnTone, std::make_shared<StringArray>(offOnTone)},
    {choice::PitchBendRangeTone, std::make_shared<StringArray>(pitchBendRangeTone)},
    {choice::MidiByteTone, std::make_shared<StringArray>(midiByteTone)},
    {choice::KeyScale, std::make_shared<StringArray>(keyScale)},
    {choice::KeyboardRange, std::make_shared<StringArray>(keyboardRange)},
    {choice::OffMute, std::make_shared<StringArray>(offMute)},
    {choice::ScaleType, std::make_shared<StringArray>(scaleType)},
    {choice::VelocityCurve, std::make_shared<StringArray>(velocityCurve)},
  };
}

std::shared_ptr<StringArray> choice::getChoicesFor(const String& choiceListName) {
  return ChoiceFactory::choiceMap.find(choiceListName)->second;
}

const ChoiceListMap ChoiceFactory::choiceMap = buildChoiceMap();

//const ChoiceListMap choice::choiceMap = buildChoiceMap();