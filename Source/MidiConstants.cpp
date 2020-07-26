/*
  ==============================================================================

    MidiConstants.cpp
    Created: 13 Jun 2020 1:51:00pm
    Author:  Keith

  ==============================================================================
*/

#include "MidiConstants.h"

/*
static BankSelectMap buildBankSelectMap() {
  return {
    {{ToneTypeSelect::StudioSet, Bank::USER}, {85, 0}},
    {{ToneTypeSelect::SnAcoustic, Bank::USER}, {89, 0}},
    {{ToneTypeSelect::SnAcoustic, Bank::PRST}, {89, 64}},
    {{ToneTypeSelect::SnSynth, Bank::USER}, {95, 0}},
    {{ToneTypeSelect::SnSynth, Bank::PRST}, {95, 64}},
    {{ToneTypeSelect::SnDrum, Bank::USER}, {88, 0}},
    {{ToneTypeSelect::SnDrum, Bank::PRST}, {88, 64}},
    {{ToneTypeSelect::PcmSynth, Bank::USER}, {87, 0}},
    {{ToneTypeSelect::PcmSynth, Bank::PRST}, {87, 64}},
    {{ToneTypeSelect::PcmSynth, Bank::GM2}, {121, 0}},
    {{ToneTypeSelect::PcmDrum, Bank::USER}, {86, 0}},
    {{ToneTypeSelect::PcmDrum, Bank::PRST}, {86, 64}},
    {{ToneTypeSelect::PcmDrum, Bank::GM2}, {120, 0}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX01}, {93, 0}},
    {{ToneTypeSelect::PcmDrum, Bank::SRX01}, {92, 0}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX02}, {93, 1}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX03}, {93, 2}},
    {{ToneTypeSelect::PcmDrum, Bank::SRX03}, {92, 2}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX04}, {93, 3}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX05}, {93, 4}},
    {{ToneTypeSelect::PcmDrum, Bank::SRX05}, {92, 4}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX06}, {93, 7}},
    {{ToneTypeSelect::PcmDrum, Bank::SRX06}, {92, 7}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX07}, {93, 11}},
    {{ToneTypeSelect::PcmDrum, Bank::SRX07}, {92, 11}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX08}, {93, 15}},
    {{ToneTypeSelect::PcmDrum, Bank::SRX08}, {92, 15}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX09}, {93, 19}},
    {{ToneTypeSelect::PcmDrum, Bank::SRX09}, {92, 19}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX10}, {93, 23}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX11}, {93, 24}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX12}, {93, 25}},
    {{ToneTypeSelect::SnAcoustic, Bank::ExSN1}, {89, 96}},
    {{ToneTypeSelect::SnAcoustic, Bank::ExSN2}, {89, 97}},
    {{ToneTypeSelect::SnAcoustic, Bank::ExSN3}, {89, 98}},
    {{ToneTypeSelect::SnAcoustic, Bank::ExSN4}, {89, 99}},
    {{ToneTypeSelect::SnAcoustic, Bank::ExSN5}, {89, 100}},
    {{ToneTypeSelect::SnDrum, Bank::ExSN6}, {88, 101}},
    {{ToneTypeSelect::PcmSynth, Bank::ExPCM}, {97, 0}},
    {{ToneTypeSelect::StudioSet, Bank::ExPCM}, {96, 0}},
  };
}
*/

static BankSelectMap buildBankSelectMap() {
  return {
    {{ToneTypeSelect::StudioSet, Bank::USER}, {{85, 0}}},
    {{ToneTypeSelect::SnAcoustic, Bank::USER}, {{89, 0}, 2}},
    {{ToneTypeSelect::SnAcoustic, Bank::PRST}, {{89, 64}, 2}},
    {{ToneTypeSelect::SnSynth, Bank::USER}, {{95, 0}, 4}},
    {{ToneTypeSelect::SnSynth, Bank::PRST}, {{95, 64}, 9}},
    {{ToneTypeSelect::SnDrum, Bank::USER}, {{88, 0}}},
    {{ToneTypeSelect::SnDrum, Bank::PRST}, {{88, 64}}},
    {{ToneTypeSelect::PcmSynth, Bank::USER}, {{87, 0}, 2}},
    {{ToneTypeSelect::PcmSynth, Bank::PRST}, {{87, 64}, 7}},
    {{ToneTypeSelect::PcmSynth, Bank::GM2}, {{121, 0}, 10}},
    {{ToneTypeSelect::PcmDrum, Bank::USER}, {{86, 0}}},
    {{ToneTypeSelect::PcmDrum, Bank::PRST}, {{86, 64}}},
    {{ToneTypeSelect::PcmDrum, Bank::GM2}, {{120, 0}}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX01}, {{93, 0}}},
    {{ToneTypeSelect::PcmDrum, Bank::SRX01}, {{92, 0}}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX02}, {{93, 1}}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX03}, {{93, 2}}},
    {{ToneTypeSelect::PcmDrum, Bank::SRX03}, {{92, 2}}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX04}, {{93, 3}}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX05}, {{93, 4}, 3}},
    {{ToneTypeSelect::PcmDrum, Bank::SRX05}, {{92, 4}}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX06}, {{93, 7}, 4}},
    {{ToneTypeSelect::PcmDrum, Bank::SRX06}, {{92, 7}}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX07}, {{93, 11}, 4}},
    {{ToneTypeSelect::PcmDrum, Bank::SRX07}, {{92, 11}}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX08}, {{93, 15}, 4}},
    {{ToneTypeSelect::PcmDrum, Bank::SRX08}, {{92, 15}}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX09}, {{93, 19}, 4}},
    {{ToneTypeSelect::PcmDrum, Bank::SRX09}, {{92, 19}}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX10}, {{93, 23}}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX11}, {{93, 24}}},
    {{ToneTypeSelect::PcmSynth, Bank::SRX12}, {{93, 25}}},
    {{ToneTypeSelect::SnAcoustic, Bank::ExSN1}, {{89, 96}}},
    {{ToneTypeSelect::SnAcoustic, Bank::ExSN2}, {{89, 97}}},
    {{ToneTypeSelect::SnAcoustic, Bank::ExSN3}, {{89, 98}}},
    {{ToneTypeSelect::SnAcoustic, Bank::ExSN4}, {{89, 99}}},
    {{ToneTypeSelect::SnAcoustic, Bank::ExSN5}, {{89, 100}}},
    {{ToneTypeSelect::SnDrum, Bank::ExSN6}, {{88, 101}}},
    {{ToneTypeSelect::PcmSynth, Bank::ExPCM}, {{97, 0}, 4}},
    {{ToneTypeSelect::StudioSet, Bank::ExPCM}, {{96, 0}}},
  };
}

static ToneGroupMap buildToneGroupMap() {
  ToneGroupMap tim;
  for (const auto& toneBsPair : BankSelect::bankSelectMap) {
    const ToneGroupId& tgid = toneBsPair.first;
    const BankSelectInfo& bsi = toneBsPair.second;
    for (int i = 0; i < bsi.numLsb; ++i) {
      tim[{bsi.base.first, bsi.base.second + i}] = {tgid, bsi.numLsb - 1};
    }
  }
  return tim;
}

const BankSelectMap BankSelect::bankSelectMap = buildBankSelectMap();
const ToneGroupMap BankSelect::toneGroupMap = buildToneGroupMap();

const BankSelectId BankSelect::getBankSelectBaseFor(const ToneGroupId& toneGroupId) {
  //return BankSelect::bankSelectMap.find(toneGroupId)->second;
  return BankSelect::bankSelectMap.find(toneGroupId)->second.base;

}

const ProgramChangeId BankSelect::getProgramChangeFor(const ToneId& toneId) {
  ToneGroupId tgId = {
    static_cast<ToneTypeSelect>(toneId.toneType), toneId.bank
  };
  
  BankSelectId bsBase = getBankSelectBaseFor(tgId);
  div_t divResult = div(toneId.toneNumber - 1, 128);
  int lsb = bsBase.second + divResult.quot;
  int pc = divResult.rem;
  
  return {{bsBase.first, lsb}, pc};
}

const ToneId BankSelect::getToneIdFor(const BankSelectId& bankSelectId, const int pc)
{
  const ToneGroupInfo& tgi = BankSelect::toneGroupMap.find(bankSelectId)->second;
  return {
    static_cast<ToneType>(tgi.base.first),
    tgi.base.second,
    pc + tgi.offset * 128 + 1
  };
}

