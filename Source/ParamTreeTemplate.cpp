/*
  ==============================================================================

    ParamTreeTemplate.cpp
    Created: 2 Feb 2020 6:05:23pm
    Author:  keith

  ==============================================================================
*/

#include "ParamTreeTemplate.h"

ValueTree ParamTreeTemplateBuilder::rootTemplate() {
  return
    { "Template", {{ "name", "INTEGRA-7" }},
      {
        { "Group",
          {{ "addr", 0x01000000 }, { "len", 2 }, { "desc", "Setup" }},
          {setupTemplate()}
        },
        { "Group",
          {{ "addr", 0x02000000 }, { "len", 2 }, { "desc", "System" }},
          {systemTemplate()}
        },
        { "Group",
          {{ "addr", 0x18000000 }, { "len", 2 }, { "desc", "Temporary Studio Set" }},
          {studioSetTemplate()}
        },
        { "GroupRange",
          {
            { "first_addr", 0x19000000 }, { "last_addr", 0x1c600000 }, { "len", 3 },
            { "first_index", 1 }, { "last_index", 16 },
            { "desc", "Temporary Tone" }, { "fmt", "Temporary Tone (Part %d)" },
          },
          {temporaryToneTemplate()}
        },
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::systemTemplate() {
  return
    { "Template", {{ "name", "System" }},
      {
        { "Group",
          {{ "addr", 0x00000000 }, { "len", 4 }, { "desc", "System Common" }},
          {systemCommonTemplate()}
        }
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::studioSetTemplate() {
  return
    { "Template", {{ "name", "Studio Set" }},
      {
        { "Group",
          {{ "addr", 0x00000000 }, { "len", 6 }, { "desc", "Studio Set Common" }}
        },
        { "Group",
          {{ "addr", 0x00040000 }, { "len", 6 }, { "desc", "Studio Set Common Chorus" }}
        },
        { "Group",
          {{ "addr", 0x00060000 }, { "len", 6 }, { "desc", "Studio Set Common Reverb" }}
        },
        { "Group",
          {{ "addr", 0x00080000 }, { "len", 6 }, { "desc", "Studio Set Common Motional Surround" }}
        },
        { "Group",
          {{ "addr", 0x00090000 }, { "len", 6 }, { "desc", "Studio Set Master EQ" }}
        },
        { "GroupRange",
          {
            { "first_addr", 0x00001000 }, { "last_addr", 0x00001F00 }, { "len", 6 },
            { "first_index", 1 }, { "last_index", 16 },
            { "desc", "Studio Set MIDI" }, { "fmt", "Studio Set MIDI (Channel %d)" },
          }
        },
        { "GroupRange",
          {
            { "first_addr", 0x00002000 }, { "last_addr", 0x00002F00 }, { "len", 6 },
            { "first_index", 1 }, { "last_index", 16 },
            { "desc", "Studio Set Part" }, { "fmt", "Studio Set Part (Part %d)" },
          }
        },
        { "GroupRange",
          {
            { "first_addr", 0x00005000 }, { "last_addr", 0x00005F00 }, { "len", 6 },
            { "first_index", 1 }, { "last_index", 16 },
            { "desc", "Studio Set Part EQ" }, { "fmt", "Studio Set Part EQ (Part %d)" },
          }
        },
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::temporaryToneTemplate() {
  return
    { "Template", {{ "name", "Temporary Tone" }},
      {
        { "Group",
          {{ "addr", 0x00000000 }, { "len", 4 }, { "desc", "Temporary PCM Synth Tone" }},
          {pcmSynthToneTemplate()}
        },
        { "Group",
          {{ "addr", 0x00000000 }, { "len", 4 }, { "desc", "Temporary SuperNATURAL Synth Tone" }}
        },
        { "Group",
          {{ "addr", 0x00000000 }, { "len", 4 }, { "desc", "Temporary SuperNATURAL Acoustic Tone" }}
        },
        { "Group",
          {{ "addr", 0x00000000 }, { "len", 4 }, { "desc", "Temporary SuperNATURAL Drum Kit" }}
        },
        { "Group",
          {{ "addr", 0x00000000 }, { "len", 4 }, { "desc", "Temporary PCM Drum Kit" }}
        },
      }
    };
}

ValueTree ParamTreeTemplateBuilder::pcmSynthToneTemplate() {
  return
    { "Template", {{ "name", "PCM Synth Tone" }},
      {
        { "Group",
          {{ "addr", 0x00000000 }, { "len", 6 }, { "desc", "PCM Synth Tone Common" }}
        },
        { "Group",
          {{ "addr", 0x00000200 }, { "len", 6 }, { "desc", "PCM Synth Tone Common MFX" }}
        },
        { "Group",
          {{ "addr", 0x00001000 }, { "len", 6 }, { "desc", "PCM Synth Tone PMT (Partial Mix Table)" }}
        },
        { "GroupRange",
          {
            { "first_addr", 0x00002000 }, { "last_addr", 0x00002600 }, { "len", 6 },
            { "first_index", 1 }, { "last_index", 4 },
            { "desc", "PCM Synth Tone Partial" }, { "fmt", "PCM Synth Tone Partial (Partial %d)" },
          }
        },
        { "Group",
          {{ "addr", 0x00003000 }, { "len", 6 }, { "desc", "PCM Synth Tone Common 2" }}
        },
      }
    };
}

ValueTree ParamTreeTemplateBuilder::pcmDrumKitTemplate() {
  return
    { "Template", {{ "name", "PCM Drum Kit" }},
      {
        { "Group",
          {{ "addr", 0x00000000 }, { "len", 6 }, { "desc", "PCM Drum Kit Common" }}
        },
        { "Group",
          {{ "addr", 0x00000200 }, { "len", 6 }, { "desc", "PCM Drum Kit Common MFX" }}
        },
        { "Group",
          {{ "addr", 0x00001000 }, { "len", 6 }, { "desc", "PCM Drum Kit Common Comp/EQ" }}
        },
        { "GroupRange",
          {
            { "first_addr", 0x00001000 }, { "last_addr", 0x00003E00 }, { "len", 6 },
            { "first_index", 21 }, { "last_index", 108 },
            { "desc", "PCM Drum Kit Partial" }, { "fmt", "PCM Drum Kit Partial (Key # %d)" },
          }
        },
        { "Group",
          {{ "addr", 0x00003000 }, { "len", 4 }, { "desc", "PCM Drum Kit Common 2" }}
        },
      }
    };
}

ValueTree ParamTreeTemplateBuilder::superNATURALSynthToneTemplate() {
  return
    { "Template", {{ "name", "SuperNATURAL Synth Tone" }},
      {
        { "Group",
          {{ "addr", 0x00000000 }, { "len", 6 }, { "desc", "SuperNATURAL Synth Tone Common" }}
        },
        { "Group",
          {{ "addr", 0x00000200 }, { "len", 6 }, { "desc", "SuperNATURAL Synth Tone MFX" }}
        },
        { "GroupRange",
          {
            { "first_addr", 0x00002000 }, { "last_addr", 0x00002200 }, { "len", 6 },
            { "first_index", 1 }, { "last_index", 3 },
            { "desc", "SuperNATURAL Synth Tone Partial" }, { "fmt", "SuperNATURAL Synth Tone Partial (%d)" },
          }
        },
      }
    };
}

ValueTree ParamTreeTemplateBuilder::superNATURALAcousticToneTemplate() {
  return
    { "Template", {{ "name", "SuperNATURAL Acoustic Tone" }},
      {
        { "Group",
          {{ "addr", 0x00000000 }, { "len", 6 }, { "desc", "SuperNATURAL Acoustic Tone Common" }}
        },
        { "Group",
          {{ "addr", 0x00000200 }, { "len", 6 }, { "desc", "SuperNATURAL Acoustic Tone MFX" }}
        },
      }
    };
}

ValueTree ParamTreeTemplateBuilder::superNATURALDrumKitTemplate() {
  return
    { "Template", {{ "name", "SuperNATURAL Drum Kit" }},
      {
        { "Group",
          {{ "addr", 0x00000000 }, { "len", 6 }, { "desc", "SuperNATURAL Drum Kit Common" }}
        },
        { "Group",
          {{ "addr", 0x00000200 }, { "len", 6 }, { "desc", "SuperNATURAL Drum Kit MFX" }}
        },
        { "Group",
          {{ "addr", 0x00000800 }, { "len", 6 }, { "desc", "SuperNATURAL Drum Kit MFX" }}
        },
        { "GroupRange",
          {
            { "first_addr", 0x00001000 }, { "last_addr", 0x00004000 }, { "len", 6 },
            { "first_index", 27 }, { "last_index", 88 },
            { "desc", "SuperNATURAL Drum Kit Note" }, { "fmt", "SuperNATURAL Drum Kit Note (Key # %d)" },
          }
        },
      }
    };
}

ValueTree ParamTreeTemplateBuilder::setupTemplate() {
  return
    { "Template", {{ "name", "Setup" }},
      {
        { "Parameter", {
          { "addr", 0x00000000 }, { "size", 1 }, { "desc", "Sound Mode" },
          { "min", 1 }, { "max", 4 },
          { "choice_list", "SoundMode" }, { "type", "choice" }, 
        }},
        { "Parameter", {
          { "addr", 0x00000004 }, { "size", 1 }, { "desc", "Studio Set BS MSB (CC# 0)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000005 }, { "size", 1 }, { "desc", "Studio Set BS LSB (CC# 32)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000006 }, { "size", 1 }, { "desc", "Studio Set BS PC (PC)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" }
        }},
      }
    };
}

ValueTree ParamTreeTemplateBuilder::systemCommonTemplate() {
  return
    { "Template", {{ "name", "System Common" }},
      {
        { "Parameter", {
          { "addr", 0x00000000 }, { "size", 4 }, { "desc", "Master Tune" },
          { "min", 24 }, { "max", 2024 }, { "type", "float" },
          { "display_min", "-100.0" }, { "display_max", "100.0" }
        }},
        { "Parameter", {
          { "addr", 0x00000004 }, { "size", 1 }, { "desc", "Master Key Shift" },
          { "min", 40 }, { "max", 88 }, { "type", "int" },
          { "display_min", -24 }, { "display_max", 24 },
        }},
        { "Parameter", {
          { "addr", 0x00000005 }, { "size", 1 }, { "desc", "Master Level" },
          { "min", 0 }, { "max", 127 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000006 }, { "size", 1 }, { "desc", "Scale Tune Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000011 }, { "size", 1 }, { "desc", "Studio Set Control Channel" },
          { "min", 0 }, { "max", 16 },
          { "type", "choice" }, { "choice_list", "MidiChannelPlusOff" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000020 }, { "last_addr", 0x00000023 }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 4 },
          { "desc", "System Control Source" }, { "fmt", "System Control %d Source" },
          { "min", 0 }, { "max", 97 },
          { "type", "choice" }, { "choice_list", "MidiControlSource" },
        }},
      }
    };
}
