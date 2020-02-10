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
    static ValueTree root = rootTemplate();
    return root;
  }

 private:
  ParamTreeTemplateBuilder() {}
  static ValueTree rootTemplate();
  static ValueTree systemTemplate();
  static ValueTree setupTemplate();
  static ValueTree systemCommonTemplate();
  static ValueTree studioSetTemplate();
  static ValueTree temporaryToneTemplate();
  static ValueTree pcmSynthToneTemplate();
  static ValueTree pcmDrumKitTemplate();
  static ValueTree superNATURALSynthToneTemplate();
  static ValueTree superNATURALAcousticToneTemplate();
  static ValueTree superNATURALDrumKitTemplate();
};

