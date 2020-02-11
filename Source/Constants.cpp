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

static ChoiceListMap buildChoiceMap() {
  return {
    {choice::SoundMode, std::make_shared<StringArray>(soundMode)},
    {choice::OffOn, std::make_shared<StringArray>(offOn)},
    {choice::MidiChannelPlusOff, std::make_shared<StringArray>(midiChannelPlusOff)},
    {choice::MidiControlSource, std::make_shared<StringArray>(midiControlSource)},
    {choice::ControlSource, std::make_shared<StringArray>(controlSource)},
    {choice::ClockSource, std::make_shared<StringArray>(clockSource)},
    {choice::AudioOutput, std::make_shared<StringArray>(audioOutput)},
  };
}

std::shared_ptr<StringArray> choice::getChoicesFor(const String& choiceListName) {
  return ChoiceFactory::choiceMap.find(choiceListName)->second;
}

const ChoiceListMap ChoiceFactory::choiceMap = buildChoiceMap();

//const ChoiceListMap choice::choiceMap = buildChoiceMap();