/*
  ==============================================================================

    ParamTreeTemplate.h
    Created: 2 Feb 2020 6:05:23pm
    Author:  keith

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class ParamTreeTemplateBuilder {
 public:
  static ValueTree& getTemplate() {
    DBG("inside getTemplate");
    static ValueTree root = rootTemplate();
    return root;
  }

 private:
  ParamTreeTemplateBuilder() {}
  static ValueTree rootTemplate();
  static ValueTree systemTemplate();
  static ValueTree setupTemplate();
  static ValueTree studioSetTemplate();
  static ValueTree temporaryToneTemplate();
  static ValueTree pcmSynthToneTemplate();
  static ValueTree pcmDrumKitTemplate();
  static ValueTree superNATURALSynthToneTemplate();
  static ValueTree superNATURALAcousticToneTemplate();
  static ValueTree superNATURALDrumKitTemplate();
  static ValueTree systemCommonTemplate();
  static ValueTree studioSetCommonTemplate();
  static ValueTree studioSetCommonChorusTemplate();
  static ValueTree studioSetCommonReverbTemplate();
  static ValueTree studioSetCommonMotionalSurroundTemplate();
  static ValueTree studioSetMasterEqTemplate();
  static ValueTree studioSetMidiTemplate();
  static ValueTree studioSetPartTemplate();
  static ValueTree studioSetPartEqTemplate();
  static ValueTree pcmSynthToneCommonTemplate();
  static ValueTree commonMFXTemplate();
  static ValueTree pcmSynthTonePMTTemplate();
  static ValueTree pcmSynthTonePartialTemplate();
  static ValueTree pcmSynthToneCommon2Template();
  static ValueTree pcmDrumKitCommonTemplate();
  static ValueTree commonCompEqTemplate();
  static ValueTree pcmDrumKitPartialTemplate();
  static ValueTree pcmDrumKitCommon2Template();
  static ValueTree superNATURALSynthToneCommonTemplate();
  static ValueTree superNATURALSynthTonePartialTemplate();
  static ValueTree superNATURALAcousticToneCommonTemplate();
  static ValueTree superNATURALDrumKitCommonTemplate();
  static ValueTree superNATURALDrumKitNoteTemplate();
};

