/*
  ==============================================================================

    MidiConstants.h
    Created: 13 Jun 2020 1:51:00pm
    Author:  Keith

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <unordered_map>

struct pairHash {
  template<class T1, class T2>
  std::size_t operator() (const std::pair<T1, T2> &pair) const {
    return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
  }
};

enum class ToneTypeSelect {
  SnAcoustic = static_cast<int>(ToneType::SnAcoustic),
  SnSynth = static_cast<int>(ToneType::SnSynth),
  SnDrum = static_cast<int>(ToneType::SnDrum),
  PcmSynth = static_cast<int>(ToneType::PcmSynth),
  PcmDrum = static_cast<int>(ToneType::PcmDrum),
  StudioSet,
};

typedef std::pair<ToneTypeSelect, Bank> ToneGroupId;


typedef std::pair</*MSB*/int, /*LSB*/int> BankSelectId;
typedef std::pair<BankSelectId, /*PC*/int> ProgramChangeId;
typedef std::unordered_map<ToneGroupId, BankSelectId, pairHash> BankSelectMap;


struct BankSelect {
  static const BankSelectMap bankSelectMap;
  static const BankSelectId getBankSelectBaseFor(const ToneGroupId& toneGroupId);
  static const ProgramChangeId getProgramChangeFor(const ToneId& toneId);
};
