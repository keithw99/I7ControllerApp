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
#include "I7Waveforms.h"

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

/*
StringArray makeRange(int min, int max) {
  StringArray r;
  for (int i = min; i <= max; ++i) {
    r.add(String(i));
  }
  return r;
}
*/

StringArray makeRange(int min, int max, int step = 1) {
  StringArray r;
  for (int i = min; i <= max; i += step) {
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

const StringArray velocityCurveType =
  addArrays<StringArray>(StringArray{"OFF"}, makeRange(1, 4));

const StringArray priority = {
  "LAST", "LOUDEST"
};

const StringArray monoPoly = {
  "MONO", "POLY"
};

const StringArray stretchTuneDepth =
  addArrays<StringArray>(StringArray{"OFF"}, makeRange(1, 3));

const StringArray portamentoMode = {
  "NORMAL", "LEGATO"
};

const StringArray portamentoType = {
  "RATE", "TIME"
};

const StringArray portamentoStart = {
  "PITCH", "NOTE"
};

const StringArray matrixControlSource = {
  addArrays<StringArray>(
    midiControlSource,
    makeRange(1, 4, "CTRL%d"),
    StringArray{
      "VELOCITY", "KEYFOLLOW", "TEMPO", "LFO1", "LFO2",
      "PIT_ENV", "TVF-ENV", "TVA-ENF"})
};

const StringArray matrixControlDestination = {
  "OFF", "PITCH", "CUTOFF", "RESONANCE", "LEVEL", "PAN", "OUTPUT LEVEL",
  "CHORUS SEND", "REVERB SEND", "LFO1 PITCH DEPTH", "LFO2 PITCH DEPTH",
  "LFO1 TVF DEPTH", "LFO2 TVF DEPTH", "LFO1 TVA DEPTH", "LFO2 TVA DEPTH",
  "LFO1 PAN DEPTH", "LFO2 PAN DEPTH", "LFO1 RATE", "LFO2 RATE",
  "PITCH ENV ATTACK TIME", "PITCH ENV DECAY TIME", "PITCH ENV RELEASE TIME",
  "TVF ENV ATTACK TIME", "TVF ENV DECAY TIME", "TVF ENV RELEASE TIME",
  "TVA ENV ATTACK TIME", "TVA ENV DECAY TIME", "TVA ENV RELEASE TIME",
  "PMT", "FXM DEPTH",
  "---", "---", "---", "---",
};

const StringArray mfxFilter = {
  "Equalizer", "Spectrum", "Low Boost", "Step Filter",
  "Enhancer", "Auto Wah", "Humanizer", "SpeakerSimulator",
};

const StringArray mfxModulation = {
  "Phaser 1", "Phaser 2", "Phaser 3", "Step Phaser", "Multi Stage Phaser",
  "Infinite Phaser", "Ring Modulator", "Tremolo", "Auto Pan", "Slicer",
  "Rotary 1", "Rotary 2", "Rotary 3",
};

const StringArray mfxChorus = {
  "Chorus", "Flanger", "Step Flanger", "Hexa-Chorus", "Tremolo Chorus", "Space-D",
};

const StringArray mfxDynamics = {
  "Overdrive", "Distortion", "Guitar Amp Simulator", "Compressor", "Limiter", "Gate",
};

const StringArray mfxDelay = {
  "Delay", "Modulation Delay", "3Tap Pan Delay", "4Tap Pan Delay",
  "MultiTap Delay", "Reverse Delay", "Time Ctrl Delay", 
};

const StringArray mfxLoFi = {
  "LOFI Compress", "Bit Crasher",
};

const StringArray mfxPitch = {
  "Pitch Shifter", "2Voice Pitch Shifter",
};

const StringArray mfxCombination = {
  "Overdrive -> Chorus", "Overdrive -> Flanger", "Overdrive -> Delay",
  "Distortion -> Chorus", "Distortion -> Flanger", "Distortion -> Delay",
  "OD/DS -> TouchWah", "OD/DS -> AutoWah",
  "GuitarAmpSim -> Chorus", "GuitarAmpSim -> Flanger",
  "GuitarAmpSim -> Phaser", "GuitarAmpSim -> Delay"
  "EP AmpSim -> Tremolo", "EP AmpSim -> Chorus", "EP AmpSim -> Flanger",
  "EP AmpSim -> Phaser", "EP AmpSim -> Delay",
  "Enhancer -> Chorus", "Enhancer -> Flanger", "Enhancer -> Delay",
  "Chorus -> Delay", "Flanger -> Delay", "Chorus -> Flanger",
};

const StringArray mfxType =
  addArrays<StringArray>(
    StringArray{"Thru"},
    mfxFilter, mfxModulation, mfxChorus, mfxDynamics,
    mfxLoFi, mfxPitch, mfxCombination);

const StringArray mfxControlSource =
  addArrays<StringArray>(
    midiControlSource, makeRange(1, 4, "SYS%d"));

const StringArray booster = {
  "0 dB", "+6 dB", "+12 dB", "+18 dB"
};

const StringArray velocityControl = {
  "OFF", "ON", "RANDOM",
};

const StringArray pmtVelocityControl =
  addArrays<StringArray>(velocityControl, { "CYCLE" });

const StringArray randomPitchDepth =
  addArrays<StringArray>(
    makeRange(0, 9),
    makeRange(10, 90, 10),
    makeRange(100, 1200, 100));

const StringArray envMode = {
  "NO-SUS", "SUSTAIN"
};

const StringArray delayMode = {
  "NORMAL", "HOLD", "KEY-OFF-NORMAL", "KEY-OFF-DECAY"
};

const StringArray noteDuration = {
  "64TH NOTE TRIPLET", "64TH NOTE",
  "32ND NOTE TRIPLET", "32ND NOTE",
  "SIXTEENTH NOTE TRIPLET", "DOTTED 32ND NOTE", "SIXTEENTH NOTE",
  "EIGHTH NOTE TRIPLET", "DOTTED SIXTEENTH NOTE", "EIGHTH NOTE",
  "QUARTER NOTE TRIPLET", "DOTTED EIGHTH NOTE", "QUARTER NOTE",
  "HALF NOTE TRIPLET", "DOTTED QUARTER NOTE", "HALF NOTE",
  "WHOLE NOTE TRIPLET", "DOTTED HALF NOTE", "WHOLE NOTE",
  "DOUBLE WHOLE NOTE TRIPLET", "DOTTED WHOLE NOTE", "DOUBLE WHOLE NOTE"
};

const StringArray delayTime = addArrays<StringArray>(midiByte, noteDuration);

const StringArray controlSwitch = {
  "OFF", "ON", "REVERSE"
};

const StringArray waveGroupType = {
  "INT", "SRX", "---", "---"
};

const StringArray waveGain = {
  "-6 dB", "0 dB", "+6 dB", "+12 dB"
};

const StringArray filterType = {
  "OFF", "LPF", "BPF", "HPF", "PKG", "LPF2", "LPF3"
};

const StringArray velocityCurve =
  addArrays<StringArray>({"FIXED"}, makeRange(1, 7));

const StringArray biasDirection = {
  "LOWER", "UPPER", "LOWER&UPPER", "ALL"
};

const StringArray lfoWaveform = {
  "SIN", "TRI", "SAW-UP", "SAW-DW", "SQR",
  "RND", "BEND-UP", "BEND-DW", "TRP", "S&H",
  "CHS", "VSIN", "STEP"
};

const StringArray fadeMode = {
  "ON-IN", "ON-OUT", "OFF-IN", "OFF-OUT"
};

const StringArray toneCategory = {
  "No assign", "Ac.Piano", "E.Piano", "Organ", "Other Keyboards",
  "Accordion/Harmonica", "Bell/Mallet", "Ac.Guitar", "E.Guitar", "Dist.Guitar",
  "Ac.Bass", "E.Bass", "Synth Bass", "Plucked/Stroke", "Strings",
  "Brass", "Wind", "Flute", "Sax", "Recorder",
  "Vox/Choir", "Synth Lead", "Synth Brass", "Synth Pad/Strings", "Synth Bellpad",
  "Synth PolyKey", "FX", "Synth Seq/Pop", "Phrase", "Pulsating",
  "Beat&Groove", "Hit", "Sound", "FX", "Percussion",
  "Combination"
};

const StringArray attackTime = {
  "0.05 ms", "0.06 ms", "0.07 ms", "0.08 ms", "0.09 ms",
  "0.1 ms", "0.2 ms", "0.3 ms", "0.4 ms", "0.5 ms",
  "0.6 ms", "0.7 ms", "0.8 ms", "0.9 ms", "1.0 ms",
  "2.0 ms", "3.0 ms", "4.0 ms", "5.0 ms", "6.0 ms",
  "7.0 ms", "8.0 ms", "9.0 ms", "10.0 ms", "15.0 ms",
  "20.0 ms", "25.0 ms", "30.0 ms", "35.0 ms", "40.0 ms",
  "45.0 ms", "50.0 ms"
};

const StringArray releaseTime = {
  "0.05 ms", "0.07 ms", "0.1 ms", "0.5 ms", "1 ms",
  "5 ms", "10 ms", "17 ms", "25 ms", "50 ms",
  "75 ms", "100 ms", "200 ms", "300 ms", "400 ms",
  "500 ms", "600 ms", "700 ms", "800 ms", "900 ms",
  "1000 ms", "1200 ms", "1500 ms", "2000 ms"
};

const StringArray compRatio = {
  "1:1", "2:1", "3:1", "4:1", "5:1",
  "6:1", "7:1", "8:1", "9:1", "10:1",
  "20:1", "30:1", "40:1", "50:1", "60:1",
  "70:1", "80:1", "90:1", "100:1", "inf:1"
};

const StringArray assignType = {
  "MULTI", "SINGLE"
};

const StringArray compGain =
  makeRange(0, 24, "+ %d dB");

const StringArray muteGroup =
  addArrays<StringArray>({"OFF"}, makeRange(1, 31));

const StringArray compGroupAssign =
  addArrays<StringArray>({"PART"}, makeRange(1, 6, "COMP+EQ%d"));

const StringArray ringSwitch = {
  "OFF", "---", "ON"
};

const StringArray oscWaveform = {
  "SAW", "SQR", "PW-SQR", "TRI", "SINE", "NOISE", "SUPER-SAW", "PCM"
};

const StringArray abc = {
  "A", "B", "C"
};

const StringArray filterMode = {
  "BYPASS", "LPF", "HPF", "BPF", "PKG", "LPF2", "LPF3", "LPF4"
};

const StringArray filterSlope = {
  "-12 dB", "-24 dB"
};

const StringArray lfoShape = {
  "TRI", "SIN", "SAW", "SQR", "S&H", "RND"
};

const StringArray lfoTempoSync = {
  "16", "12", "8", "4", "2", "1", "3/4", "2/3", "1/2", "3/8",
  "1/3", "1/4", "3/16", "1/6", "1/8", "3/32", "1/12", "1/16", "1/24", "1/32"
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
    {choice::VelocityCurveType, std::make_shared<StringArray>(velocityCurveType)},
    {choice::Priority, std::make_shared<StringArray>(priority)},
    {choice::StretchTuneDepth, std::make_shared<StringArray>(stretchTuneDepth)},
    {choice::MonoPoly, std::make_shared<StringArray>(monoPoly)},
    {choice::PortamentoMode, std::make_shared<StringArray>(portamentoMode)},
    {choice::PortamentoType, std::make_shared<StringArray>(portamentoType)},
    {choice::PortamentoStart, std::make_shared<StringArray>(portamentoStart)},
    {choice::MatrixControlSource, std::make_shared<StringArray>(matrixControlSource)},
    {choice::MatrixControlDestination, std::make_shared<StringArray>(matrixControlDestination)},
    {choice::MFXType, std::make_shared<StringArray>(mfxType)},
    {choice::MFXControlSource, std::make_shared<StringArray>(mfxControlSource)},
    {choice::Booster, std::make_shared<StringArray>(booster)},
    {choice::VelocityControl, std::make_shared<StringArray>(velocityControl)},
    {choice::PMTVelocityControl, std::make_shared<StringArray>(pmtVelocityControl)},
    {choice::RandomPitchDepth, std::make_shared<StringArray>(randomPitchDepth)},
    {choice::EnvMode, std::make_shared<StringArray>(envMode)},
    {choice::DelayMode, std::make_shared<StringArray>(delayMode)},
    {choice::DelayTime, std::make_shared<StringArray>(delayTime)},
    {choice::ControlSwitch, std::make_shared<StringArray>(controlSwitch)},
    {choice::WaveGroupType, std::make_shared<StringArray>(waveGroupType)},
    {choice::WaveGain, std::make_shared<StringArray>(waveGain)},
    {choice::FilterType, std::make_shared<StringArray>(filterType)},
    {choice::BiasDirection, std::make_shared<StringArray>(biasDirection)},
    {choice::LFOWaveform, std::make_shared<StringArray>(lfoWaveform)},
    {choice::FadeMode, std::make_shared<StringArray>(fadeMode)},
    {choice::VelocityCurve, std::make_shared<StringArray>(velocityCurve)},
    {choice::ToneCategory, std::make_shared<StringArray>(toneCategory)},
    {choice::AttackTime, std::make_shared<StringArray>(attackTime)},
    {choice::ReleaseTime, std::make_shared<StringArray>(releaseTime)},
    {choice::CompRatio, std::make_shared<StringArray>(compRatio)},
    {choice::CompGain, std::make_shared<StringArray>(compGain)},
    {choice::AssignType, std::make_shared<StringArray>(assignType)},
    {choice::MuteGroup, std::make_shared<StringArray>(muteGroup)},
    {choice::CompGroupAssign, std::make_shared<StringArray>(compGroupAssign)},
    {choice::RingSwitch, std::make_shared<StringArray>(ringSwitch)},
    {choice::ABC, std::make_shared<StringArray>(abc)},
    {choice::FilterMode, std::make_shared<StringArray>(filterMode)},
    {choice::FilterSlope, std::make_shared<StringArray>(filterSlope)},
    {choice::LFOShape, std::make_shared<StringArray>(lfoShape)},
    {choice::LFOTempoSync, std::make_shared<StringArray>(lfoTempoSync)},
  };
}

std::shared_ptr<StringArray> choice::getChoicesFor(const String& choiceListName) {
  return ChoiceFactory::choiceMap.find(choiceListName)->second;
}

const ChoiceListMap ChoiceFactory::choiceMap = buildChoiceMap();

//const ChoiceListMap choice::choiceMap = buildChoiceMap();