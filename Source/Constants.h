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
const String param_template { "template" };
}  // namespace param
}  // namespace prop

namespace paramtype {
const String int_type { "int" };
const String float_type { "float" };
const String choice { "choice" };
const String ascii { "ascii" };
}

namespace paramtemplate {
const String MidiByte { "MidiByte" };  // int 0-127, size 1
const String SignedMidiByte { "SignedMidiByte" };  // int 1-127 (-63-63), size 1
const String Pan { "Pan" };  // int -64-63, size 1
const String CoarseTune { "CoarseTune" };  // int 16-112 (-48-48), size 1
const String FineTune { "FineTune" };  // int 14-114 (-50-50), size 1
const String OctaveShift { "OctaveShift" };  // int 61-67 (-3-3), size 1
const String KeyFollow { "KeyFollow" };  // int 54-74 (-100-100), size 1

}  // namespace paramtemplate

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
const String VoiceReserve { "VoiceReserve" };
const String OffPartNumber { "OffPartNumber" };
const String OutputAssign { "OutputAssign" };
const String PartOutputAssign { "PartOutputAssign" };
const String ChorusType { "ChorusType" };
const String ChorusOutputSelect { "ChorusOutputSelect" };
const String ReverbType { "ReverbType" };
const String LetteredOutputs { "LetteredOutputs" };
const String RoomType { "RoomType" };
const String RoomSize { "RoomSize" };
const String EqLowFreq { "EqLowFreq" };
const String EqMidFreq { "EqMidFreq" };
const String EqHighFreq { "EqHighFreq" };
const String EqQ { "EqQ" };
const String MonoPolyTone { "MonoPolyTone" };
const String OffOnTone { "OffOnTone" };
const String PitchBendRangeTone { "PitchBendRangeTone" };
const String MidiByteTone { "MidiByteTone" };
const String KeyScale { "KeyScale" };
const String KeyboardRange { "KeyboardRange" };
const String OffMute { "OffMute" };
const String ScaleType { "ScaleType" };
const String VelocityCurveType { "VelocityCurveType" };
const String Priority { "Priority" };
const String StretchTuneDepth { "StretchTuneDepth" };
const String MonoPoly { "MonoPoly" };
const String PortamentoMode { "PortamentoMode" };
const String PortamentoType { "PortamentoType" };
const String PortamentoStart { "PortamentoStart" };
const String MatrixControlSource { "MatrixControlSource"};
const String MatrixControlDestination { "MatrixControlDestination" };
const String MFXType { "MFXType" };
const String MFXControlSource { "MFXControlSource" };
const String Booster { "Booster" };
const String PMTVelocityControl { "PMTVelocityControl" };
const String VelocityControl { "VelocityControl" };
const String RandomPitchDepth { "RandomPitchDepth" };
const String EnvMode { "EnvMode" };
const String DelayMode { "DelayMode" };
const String NoteDuration { "NoteDuration" };
const String DelayTime { "DelayTime" };
const String ControlSwitch { "ControlSwitch" };
const String WaveGroupType { "WaveGroupType" };
const String WaveGain { "WaveGain" };
const String FilterType { "FilterType" };
const String VelocityCurve { "VelocityCurve" };
const String BiasDirection { "BiasDirection" };
const String LFOWaveform { "LFOWaveform" };
const String FadeMode { "FadeMode" };
const String ToneCategory { "ToneCategory" };
const String AttackTime { "AttackTime" };
const String ReleaseTime { "ReleaseTime" };
const String CompRatio { "CompRatio" };
const String CompGain { "CompGain" };
const String AssignType { "AssignType" };
const String MuteGroup { "MuteGroup" };
const String CompGroupAssign { "CompGroupAssign" };

extern std::shared_ptr<StringArray> getChoicesFor(const String& choiceListName);
}  // namespace choice

struct ChoiceFactory {
  static const ChoiceListMap choiceMap;
};
