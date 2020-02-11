/*
  ==============================================================================

    Constants.h
    Created: 3 Feb 2020 1:10:14am
    Author:  keith

  ==============================================================================
*/

#pragma once

#include <vector>
#include <unordered_map>
#include "../JuceLibraryCode/JuceHeader.h"

namespace prop {
const String desc { "desc" };  
const String addr { "addr" };
const String len { "len" };
const String first_addr { "first_addr" };
const String last_addr { "last_addr" };
const String first_index { "first_index" };
const String last_index { "last_index" };
const String fmt { "fmt" };

namespace param {
const String size { "size" };
const String min { "min" };
const String max { "max" };
const String step { "step" };
const String display_min { "display_min" };
const String display_max { "display_max" };
const String type { "type" };
const String choice_list { "choice_list" };
}  // namespace param
}  // namespace prop

namespace paramtype {
const String int_type { "int" };
const String float_type { "float" };
const String choice { "choice" };
const String ascii { "ascii" };
}

namespace tree {
const String Template { "Template" };
const String Group { "Group" };
const String GroupRange { "GroupRange" };
const String Parameter { "Parameter" };
const String ParameterRange { "ParameterRange" };
const String TextParameter { "TextParameter" };
}  // namespace tree

typedef std::unordered_map<String, std::shared_ptr<StringArray>> ChoiceListMap;

namespace choice {
const String SoundMode { "SoundMode" };
const String OffOn { "OffOn" };
const String MidiChannelPlusOff { "MidiChannelPlusOff" };
const String MidiControlSource { "MidiControlSource" };
const String ControlSource { "ControlSource" };
const String ClockSource { "ClockSource" };
const String AudioOutput { "AudioOutput" };

extern std::shared_ptr<StringArray> getChoicesFor(const String& choiceListName);
}  // namespace choice

struct ChoiceFactory {
  static const ChoiceListMap choiceMap;
};
