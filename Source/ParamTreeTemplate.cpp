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
          {{ "addr", 0x00000000 }, { "len", 6 }, { "desc", "Studio Set Common" }},
          {studioSetCommonTemplate()}
        },
        { "Group",
          {{ "addr", 0x00040000 }, { "len", 6 }, { "desc", "Studio Set Common Chorus" }},
          {studioSetCommonChorusTemplate()}
        },
        { "Group",
          {{ "addr", 0x00060000 }, { "len", 6 }, { "desc", "Studio Set Common Reverb" }},
          {studioSetCommonReverbTemplate()}
        },
        { "Group",
          {{ "addr", 0x00080000 }, { "len", 6 }, { "desc", "Studio Set Common Motional Surround" }},
          {studioSetCommonMotionalSurroundTemplate()}
        },
        { "Group",
          {{ "addr", 0x00090000 }, { "len", 6 }, { "desc", "Studio Set Master EQ" }},
          {studioSetMasterEqTemplate()}
        },
        { "GroupRange",
          {
            { "first_addr", 0x00001000 }, { "last_addr", 0x00001F00 }, { "len", 6 },
            { "first_index", 1 }, { "last_index", 16 },
            { "desc", "Studio Set MIDI" }, { "fmt", "Studio Set MIDI (Channel %d)" },
          },
          {studioSetMidiTemplate()}
        },
        { "GroupRange",
          {
            { "first_addr", 0x00002000 }, { "last_addr", 0x00002F00 }, { "len", 6 },
            { "first_index", 1 }, { "last_index", 16 },
            { "desc", "Studio Set Part" }, { "fmt", "Studio Set Part (Part %d)" },
          },
          {studioSetPartTemplate()}
        },
        { "GroupRange",
          {
            { "first_addr", 0x00005000 }, { "last_addr", 0x00005F00 }, { "len", 6 },
            { "first_index", 1 }, { "last_index", 16 },
            { "desc", "Studio Set Part EQ" }, { "fmt", "Studio Set Part EQ (Part %d)" },
          },
          {studioSetPartEqTemplate()}
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
          {{ "addr", 0x00000000 }, { "len", 6 }, { "desc", "PCM Synth Tone Common" }},
          {pcmSynthToneCommonTemplate()}
        },
        { "Group",
          {{ "addr", 0x00000200 }, { "len", 6 }, { "desc", "PCM Synth Tone Common MFX" }},
          {commonMFXTemplate()}
        },
        { "Group",
          {{ "addr", 0x00001000 }, { "len", 6 }, { "desc", "PCM Synth Tone PMT (Partial Mix Table)" }},
          {pcmSynthTonePMTTemplate()}
        },
        { "GroupRange",
          {
            { "first_addr", 0x00002000 }, { "last_addr", 0x00002600 }, { "len", 6 },
            { "first_index", 1 }, { "last_index", 4 },
            { "desc", "PCM Synth Tone Partial" }, { "fmt", "PCM Synth Tone Partial (Partial %d)" },
          },
          {pcmSynthTonePartialTemplate()}
        },
        { "Group",
          {{ "addr", 0x00003000 }, { "len", 6 }, { "desc", "PCM Synth Tone Common 2" }},
          {pcmSynthToneCommon2Template()}
        },
      }
    };
}

ValueTree ParamTreeTemplateBuilder::pcmDrumKitTemplate() {
  return
    { "Template", {{ "name", "PCM Drum Kit" }},
      {
        { "Group",
          {{ "addr", 0x00000000 }, { "len", 6 }, { "desc", "PCM Drum Kit Common" }},
          {pcmDrumKitCommonTemplate()}
        },
        { "Group",
          {{ "addr", 0x00000200 }, { "len", 6 }, { "desc", "PCM Drum Kit Common MFX" }},
          {commonMFXTemplate()}
        },
        { "Group",
          {{ "addr", 0x00001000 }, { "len", 6 }, { "desc", "PCM Drum Kit Common Comp/EQ" }},
          {commonCompEqTemplate()}
        },
        { "GroupRange",
          {
            { "first_addr", 0x00001000 }, { "last_addr", 0x00003E00 }, { "len", 6 },
            { "first_index", 21 }, { "last_index", 108 },
            { "desc", "PCM Drum Kit Partial" }, { "fmt", "PCM Drum Kit Partial (Key # %d)" },
          },
          {pcmDrumKitPartialTemplate()}
        },
        { "Group",
          {{ "addr", 0x00003000 }, { "len", 4 }, { "desc", "PCM Drum Kit Common 2" }},
          {pcmDrumKitCommon2Template()}
        },
      }
    };
}

ValueTree ParamTreeTemplateBuilder::superNATURALSynthToneTemplate() {
  return
    { "Template", {{ "name", "SuperNATURAL Synth Tone" }},
      {
        { "Group",
          {{ "addr", 0x00000000 }, { "len", 6 }, { "desc", "SuperNATURAL Synth Tone Common" }},
          {superNATURALSynthToneCommonTemplate()}
        },
        { "Group",
          {{ "addr", 0x00000200 }, { "len", 6 }, { "desc", "SuperNATURAL Synth Tone MFX" }},
          {commonMFXTemplate()}
        },
        { "GroupRange",
          {
            { "first_addr", 0x00002000 }, { "last_addr", 0x00002200 }, { "len", 6 },
            { "first_index", 1 }, { "last_index", 3 },
            { "desc", "SuperNATURAL Synth Tone Partial" }, { "fmt", "SuperNATURAL Synth Tone Partial (%d)" },
          },
          {superNATURALSynthTonePartialTemplate()}          
        },
      }
    };
}

ValueTree ParamTreeTemplateBuilder::superNATURALAcousticToneTemplate() {
  return
    { "Template", {{ "name", "SuperNATURAL Acoustic Tone" }},
      {
        { "Group",
          {{ "addr", 0x00000000 }, { "len", 6 }, { "desc", "SuperNATURAL Acoustic Tone Common" }},
          {superNATURALAcousticToneCommonTemplate()}
        },
        { "Group",
          {{ "addr", 0x00000200 }, { "len", 6 }, { "desc", "SuperNATURAL Acoustic Tone MFX" }},
          {commonMFXTemplate()}
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
          {{ "addr", 0x00000800 }, { "len", 6 }, { "desc", "SuperNATURAL Drum Kit Common Comp/EQ" }}
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
        { "Parameter", {
          { "addr", 0x00000024 }, { "size", 1 }, { "desc", "Control Source" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "ControlSource" },
        }},
        { "Parameter", {
          { "addr", 0x00000025 }, { "size", 1 }, { "desc", "System Clock Source" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "ClockSource" },
        }},        
        { "Parameter", {
          { "addr", 0x00000026 }, { "size", 2 }, { "desc", "System Tempo" },
          { "min", 20 }, { "max", 250 }, { "type", "int" },
        }},        
        { "Parameter", {
          { "addr", 0x00000028 }, { "size", 1 }, { "desc", "Tempo Assign Source" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "ControlSource" },
        }},
        { "Parameter", {
          { "addr", 0x00000029 }, { "size", 1 }, { "desc", "Receive Program Change" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000002A }, { "size", 1 }, { "desc", "Receive Bank Select" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000002B }, { "size", 1 }, { "desc", "5.1CH Center Speaker Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000002C }, { "size", 1 }, { "desc", "5.1CH Sub Woofer Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000002D }, { "size", 1 }, { "desc", "2CH Output Mode" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "AudioOutput" },
        }},
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::studioSetCommonTemplate() {
  return
    { "Template", {{ "name", "Studio Set Common" }},
      {
        { "TextParameter", {
          { "first_addr", 0x00000000 }, { "last_addr", 0x0000000F }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 16 },
          { "desc", "Studio Set Name" }, { "fmt", "Studio Set Name %d" },
          { "type", "ascii" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000018 }, { "last_addr", 0x00000027 }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 16 },
          { "desc", "Voice Reserve" }, { "fmt", "Voice Reserve %d" },
          { "min", 0 }, { "max", 64 },
          { "type", "choice" }, { "choice_list", "VoiceReserve" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000039 }, { "last_addr", 0x0000003C }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 4 },
          { "desc", "Tone Control Source" }, { "fmt", "Tone Control %d Source" },
          { "min", 0 }, { "max", 97 },
          { "type", "choice" }, { "choice_list", "MidiControlSource" },
        }},        
        { "Parameter", {
          { "addr", 0x00000030 }, { "size", 2 }, { "desc", "Studio Set Tempo" },
          { "min", 20 }, { "max", 250 }, { "type", "int" },
        }},        
        { "Parameter", {
          { "addr", 0x0000003F }, { "size", 1 }, { "desc", "Solo Part" },
          { "min", 0 }, { "max", 16 },
          { "type", "choice" }, { "choice_list", "OffPartNumber" },
        }},
        { "Parameter", {
          { "addr", 0x00000040 }, { "size", 1 }, { "desc", "Reverb Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000041 }, { "size", 1 }, { "desc", "Chorus Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000042 }, { "size", 1 }, { "desc", "Master EQ Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000043 }, { "size", 1 }, { "desc", "Drum Comp/EQ Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000044 }, { "size", 1 }, { "desc", "Drum Comp/EQ Part" },
          { "min", 0 }, { "max", 15 }, { "type", "int" },
          { "display_min", 1 }, { "display_max", 16 },
        }},        
        { "ParameterRange", {
          { "first_addr", 0x00000045 }, { "last_addr", 0x0000004A }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 6 },
          { "desc", "Drum Comp/EQ Output Assign" }, { "fmt", "Drum Comp/EQ %d Output Assign" },
          { "min", 0 }, { "max", 12 },
          { "type", "choice" }, { "choice_list", "PartOutputAssign" },
        }},        
        { "Parameter", {
          { "addr", 0x0000004C }, { "size", 1 }, { "desc", "Ext Part Level" },
          { "min", 0 }, { "max", 127 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x0000004D }, { "size", 1 }, { "desc", "Ext Part Chorus Send Level" },
          { "min", 0 }, { "max", 127 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x0000004E }, { "size", 1 }, { "desc", "Ext Part Reverb Send Level" },
          { "min", 0 }, { "max", 127 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x0000004F }, { "size", 1 }, { "desc", "Ext Part Mute Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
      }       
    };
}

inline ValueTree ParamTreeTemplateBuilder::studioSetCommonChorusTemplate() {
  return
    { "Template", {{ "name", "Studio Set Common Chorus" }},
      {
        { "Parameter", {
          { "addr", 0x00000000 }, { "size", 1 }, { "desc", "Chorus Type" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "ChorusType" },
        }},        
        { "Parameter", {
          { "addr", 0x00000001 }, { "size", 1 }, { "desc", "Chorus Level" },
          { "min", 0 }, { "max", 127 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000003 }, { "size", 1 }, { "desc", "Chorus Output Select" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "ChorusOutputSelect" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000000 }, { "last_addr", 0x00000050 }, { "size", 4 },
          { "first_index", 1 }, { "last_index", 20 },
          { "desc", "Chorus Parameter" }, { "fmt", "Chorus Parameter %d" },
          { "min", 12768 }, { "max", 52768 }, { "type", "int" },
          { "display_min", -20000 }, { "display_max", 20000 },
        }},
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::studioSetCommonReverbTemplate() {
  return
    { "Template", {{ "name", "Studio Set Common Reverb" }},
      {
        { "Parameter", {
          { "addr", 0x00000000 }, { "size", 1 }, { "desc", "Reverb Type" },
          { "min", 0 }, { "max", 6 },
          { "type", "choice" }, { "choice_list", "ReverbType" },
        }},
        { "Parameter", {
          { "addr", 0x00000001 }, { "size", 1 }, { "desc", "Reverb Level" },
          { "min", 0 }, { "max", 127 }, { "type", "int" }
        }},        
        { "Parameter", {
          { "addr", 0x00000002 }, { "size", 1 }, { "desc", "Reverb Output Assign" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "LetteredOutputs" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000003 }, { "last_addr", 0x0000005F }, { "size", 4 },
          { "first_index", 1 }, { "last_index", 24 },
          { "desc", "Reverb Parameter" }, { "fmt", "Reverb Parameter %d" },
          { "min", 12768 }, { "max", 52768 }, { "type", "int" },
          { "display_min", -20000 }, { "display_max", 20000 },
        }},
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::studioSetCommonMotionalSurroundTemplate() {
  return
    { "Template", {{ "name", "Studio Set Common Motional Surround" }},
      {
        { "Parameter", {
          { "addr", 0x00000000 }, { "size", 1 }, { "desc", "Motional Surround Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000001 }, { "size", 1 }, { "desc", "Room Type" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "RoomType" },
        }},
        { "Parameter", {
          { "addr", 0x00000002 }, { "size", 1 }, { "desc", "Ambience Level" },
          { "min", 0 }, { "max", 127 }, { "type", "int" }
        }},        
        { "Parameter", {
          { "addr", 0x00000003 }, { "size", 1 }, { "desc", "Room Size" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "RoomSize" },
        }},
        { "Parameter", {
          { "addr", 0x00000004 }, { "size", 1 }, { "desc", "Ambience Time" },
          { "min", 0 }, { "max", 100 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000005 }, { "size", 1 }, { "desc", "Ambience Density" },
          { "min", 0 }, { "max", 100 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000006 }, { "size", 1 }, { "desc", "Ambience HF Damp" },
          { "min", 0 }, { "max", 100 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000007 }, { "size", 1 }, { "desc", "Ext Part L-R" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000008 }, { "size", 1 }, { "desc", "Ext Part F-B" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000009 }, { "size", 1 }, { "desc", "Ext Part Width" },
          { "min", 0 }, { "max", 32 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x0000000A }, { "size", 1 }, { "desc", "Ext Part Ambience Send Level" },
          { "min", 0 }, { "max", 127 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x0000000B }, { "size", 1 }, { "desc", "Ext Part Control Channel" },
          { "min", 0 }, { "max", 16 },
          { "type", "choice" }, { "choice_list", "MidiChannelPlusOff" },
        }},
        { "Parameter", {
          { "addr", 0x0000000C }, { "size", 1 }, { "desc", "Motional Surround Depth" },
          { "min", 0 }, { "max", 100 }, { "type", "int" }
        }},
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::studioSetMasterEqTemplate() {
  return
    { "Template", {{ "name", "Studio Set Master Eq" }},
      {
        { "Parameter", {
          { "addr", 0x00000000 }, { "size", 1 }, { "desc", "EQ Low Freq" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "EqLowFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000001 }, { "size", 1 }, { "desc", "EQ Low Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000002 }, { "size", 1 }, { "desc", "EQ Mid Freq" },
          { "min", 0 }, { "max", 16 },
          { "type", "choice" }, { "choice_list", "EqMidFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000003 }, { "size", 1 }, { "desc", "EQ Mid Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000004 }, { "size", 1 }, { "desc", "EQ Mid Q" },
          { "min", 0 }, { "max", 4 },
          { "type", "choice" }, { "choice_list", "EqQ" },
        }},
        { "Parameter", {
          { "addr", 0x00000005 }, { "size", 1 }, { "desc", "EQ High Freq" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "EqHighFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000006 }, { "size", 1 }, { "desc", "EQ High Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::studioSetMidiTemplate() {
  return
    { "Template", {{ "name", "Studio Set MIDI" }},
      {
        { "Parameter", {
          { "addr", 0x00000000 }, { "size", 1 }, { "desc", "Phase Lock" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::studioSetPartTemplate() {
  return
    { "Template", {{ "name", "Studio Set Part" }},
      {
        { "Parameter", {
          { "addr", 0x00000000 }, { "size", 1 }, { "desc", "Receive Channel" },
          { "min", 0 }, { "max", 15 }, { "type", "int" },
          { "display_min", 1 }, { "display_max", 16 },
        }},        
        { "Parameter", {
          { "addr", 0x00000001 }, { "size", 1 }, { "desc", "Receive Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000006 }, { "size", 1 }, { "desc", "Tone Bank Select MSB (CC# 0)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000007 }, { "size", 1 }, { "desc", "Tone Bank Select LSB (CC# 32)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000008 }, { "size", 1 }, { "desc", "Tone Program Number (PC)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000009 }, { "size", 1 }, { "desc", "Part Level (CC# 7)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x0000000A }, { "size", 1 }, { "desc", "Part Pan (CC# 10)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x0000000B }, { "size", 1 }, { "desc", "Part Coarse Tune (RPN# 2)" },
          { "min", 16 }, { "max", 112 }, { "type", "int" },
          { "display_min", -48 }, { "display_max", 48 },
        }},
        { "Parameter", {
          { "addr", 0x0000000C }, { "size", 1 }, { "desc", "Part Fine Tune (RPN# 1)" },
          { "min", 14 }, { "max", 114 }, { "type", "int" },
          { "display_min", -50 }, { "display_max", 50 },
        }},
        { "Parameter", {
          { "addr", 0x0000000D }, { "size", 1 }, { "desc", "Part Mono/Poly (MONO ON/POLY ON)" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "MonoPolyTone" },
        }},
        { "Parameter", {
          { "addr", 0x0000000E }, { "size", 1 }, { "desc", "Part Legato Switch (CC# 68)" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "OffOnTone" },
        }},
        { "Parameter", {
          { "addr", 0x0000000F }, { "size", 1 }, { "desc", "Part Pitch Bend Range (RPN# 0)" },
          { "min", 0 }, { "max", 25 },
          { "type", "choice" }, { "choice_list", "PitchBendRangeTone" },
        }},
        { "Parameter", {
          { "addr", 0x00000010 }, { "size", 1 }, { "desc", "Part Portamento Switch (CC# 65)" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "OffOnTone" },
        }},
        { "Parameter", {
          { "addr", 0x00000011 }, { "size", 2 }, { "desc", "Part Portamento Time (CC# 5)" },
          { "min", 0 }, { "max", 128 },
          { "type", "choice" }, { "choice_list", "MidiByteTone" },
        }},
        { "Parameter", {
          { "addr", 0x00000013 }, { "size", 1 }, { "desc", "Part Cutoff Offset (CC# 74)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000014 }, { "size", 1 }, { "desc", "Part Resonance Offset (CC# 71)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000015 }, { "size", 1 }, { "desc", "Part Attack Time Offset (CC# 73)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000016 }, { "size", 1 }, { "desc", "Part Decay Time Offset (CC# 75)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000017 }, { "size", 1 }, { "desc", "Part Release Time Offset (CC# 72)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000018 }, { "size", 1 }, { "desc", "Part Vibrato Rate (CC# 76)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000019 }, { "size", 1 }, { "desc", "Part Vibrato Depth (CC# 77)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x0000001A }, { "size", 1 }, { "desc", "Part Vibrato Delay (CC# 78)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x0000001B }, { "size", 1 }, { "desc", "Part Octave Shift" },
          { "min", 61 }, { "max", 67 }, { "type", "int" },
          { "display_min", -3 }, { "display_max", 3 },
        }},
        { "Parameter", {
          { "addr", 0x0000001C }, { "size", 1 }, { "desc", "Part Velocity Sens Offset" },
          { "min", 1 }, { "max", 127 }, { "type", "int" },
          { "display_min", -63 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x0000001D }, { "size", 1 }, { "desc", "Keyboard Range Lower" },
          { "min", 0 }, { "max", 127 },
          { "type", "choice" }, { "choice_list", "KeyboardRange" },
        }},
        { "Parameter", {
          { "addr", 0x0000001E }, { "size", 1 }, { "desc", "Keyboard Range Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "type", "choice" }, { "choice_list", "KeyboardRange" },
        }},
        { "Parameter", {
          { "addr", 0x0000001F }, { "size", 1 }, { "desc", "Keyboard Fade Width Lower" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000020 }, { "size", 1 }, { "desc", "Keyboard Fade Width Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000021 }, { "size", 1 }, { "desc", "Velocity Range Lower" },
          { "min", 1 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000022 }, { "size", 1 }, { "desc", "Velocity Range Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000023 }, { "size", 1 }, { "desc", "Velocity Fade Width Lower" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000024 }, { "size", 1 }, { "desc", "Velocity Fade Width Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000025 }, { "size", 1 }, { "desc", "Mute Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffMute" },
        }},
        { "Parameter", {
          { "addr", 0x00000027 }, { "size", 1 }, { "desc", "Part Chorus Send Level (CC# 93)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000028 }, { "size", 1 }, { "desc", "Part Reverb Send level (CC# 91)" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000029 }, { "size", 1 }, { "desc", "Part Output Assign" },
          { "min", 0 }, { "max", 11 },
          { "type", "choice" }, { "choice_list", "OutputAssign" },
        }},
        { "Parameter", {
          { "addr", 0x0000002B }, { "size", 1 }, { "desc", "Part Scale Tune Type" },
          { "min", 0 }, { "max", 8 },
          { "type", "choice" }, { "choice_list", "ScaleType" },
        }},
        { "Parameter", {
          { "addr", 0x0000002C }, { "size", 1 }, { "desc", "Part Scale Tune Key" },
          { "min", 0 }, { "max", 11 },
          { "type", "choice" }, { "choice_list", "KeyScale" },
        }},
        { "Parameter", {
          { "addr", 0x0000002D }, { "size", 1 }, { "desc", "Part Scale Tune for C" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x0000002E }, { "size", 1 }, { "desc", "Part Scale Tune for C#" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x0000002F }, { "size", 1 }, { "desc", "Part Scale Tune for D" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000030 }, { "size", 1 }, { "desc", "Part Scale Tune for D#" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000031 }, { "size", 1 }, { "desc", "Part Scale Tune for E" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000032 }, { "size", 1 }, { "desc", "Part Scale Tune for F" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000033 }, { "size", 1 }, { "desc", "Part Scale Tune for F#" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000034 }, { "size", 1 }, { "desc", "Part Scale Tune for G" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000035 }, { "size", 1 }, { "desc", "Part Scale Tune for G#" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000036 }, { "size", 1 }, { "desc", "Part Scale Tune for A" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000037 }, { "size", 1 }, { "desc", "Part Scale Tune for A#" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000038 }, { "size", 1 }, { "desc", "Part Scale Tune for B" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000039 }, { "size", 1 }, { "desc", "Receive Program Change" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000003A }, { "size", 1 }, { "desc", "Receive Bank Select" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000003B }, { "size", 1 }, { "desc", "Receive Pitch Bend" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000003C }, { "size", 1 }, { "desc", "Receive Polyphonic Key Pressure" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000003D }, { "size", 1 }, { "desc", "Receive Channel Pressure" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000003E }, { "size", 1 }, { "desc", "Receive Modulation" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000003F }, { "size", 1 }, { "desc", "Receive Volume" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000040 }, { "size", 1 }, { "desc", "Receive Pan" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000041 }, { "size", 1 }, { "desc", "Receive Expression" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000042 }, { "size", 1 }, { "desc", "Receive Hold-1" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000043 }, { "size", 1 }, { "desc", "Velocity Curve Type" },
          { "min", 0 }, { "max", 4 },
          { "type", "choice" }, { "choice_list", "VelocityCurveType" },
        }},
        { "Parameter", {
          { "addr", 0x00000044 }, { "size", 1 }, { "desc", "Motional Surround L-R" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000046 }, { "size", 1 }, { "desc", "Motional Surround F-B" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000048 }, { "size", 1 }, { "desc", "Motional Surround Width" },
          { "min", 0 }, { "max", 32 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000049 }, { "size", 1 }, { "desc", "Motional Surround Ambience Send Level" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::studioSetPartEqTemplate() {
  return
    { "Template", {{ "name", "Studio Set Part EQ" }},
      {
        { "Parameter", {
          { "addr", 0x00000000 }, { "size", 1 }, { "desc", "EQ Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000001 }, { "size", 1 }, { "desc", "EQ Low Freq" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "EqLowFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000002 }, { "size", 1 }, { "desc", "EQ Low Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000003 }, { "size", 1 }, { "desc", "EQ Mid Freq" },
          { "min", 0 }, { "max", 16 },
          { "type", "choice" }, { "choice_list", "EqMidFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000004 }, { "size", 1 }, { "desc", "EQ Mid Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000005 }, { "size", 1 }, { "desc", "EQ Mid Q" },
          { "min", 0 }, { "max", 4 },
          { "type", "choice" }, { "choice_list", "EqQ" },
        }},
        { "Parameter", {
          { "addr", 0x00000006 }, { "size", 1 }, { "desc", "EQ High Freq" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "EqHighFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000007 }, { "size", 1 }, { "desc", "EQ High Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::pcmSynthToneCommonTemplate() {
  return
    { "Template", {{ "name", "PCM Synth Tone Common" }},
      {
        { "TextParameter", {
          { "first_addr", 0x00000000 }, { "last_addr", 0x0000000B }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 12 },
          { "desc", "PCM Synth Tone Name" }, { "fmt", "PCM Synth Tone Name %d" },
          { "type", "ascii" },
        }},
        { "Parameter", {
          { "addr", 0x0000000E }, { "size", 1 }, { "desc", "PCM Synth Tone Level" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000000F }, { "size", 1 }, { "desc", "PCM Synth Tone Pan" },
          { "template", "Pan" },
        }},
        { "Parameter", {
          { "addr", 0x00000010 }, { "size", 1 }, { "desc", "PCM Synth Tone Priority" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "Priority" },
        }},      
        { "Parameter", {
          { "addr", 0x00000011 }, { "size", 1 }, { "desc", "PCM Synth Tone Coarse Tune" },
          { "template", "CoarseTune" },
        }},
        { "Parameter", {
          { "addr", 0x00000012 }, { "size", 1 }, { "desc", "PCM Synth Tone Fine Tune" },
          { "template", "FineTune" },
        }},
        { "Parameter", {
          { "addr", 0x00000013 }, { "size", 1 }, { "desc", "Octave Shift" },
          { "template", "OctaveShift" },
        }},
        { "Parameter", {
          { "addr", 0x00000014 }, { "size", 1 }, { "desc", "Stretch Tune Depth" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "StretchTuneDepth" },
        }},
        { "Parameter", {
          { "addr", 0x00000015 }, { "size", 1 }, { "desc", "Analog Feel"},
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000016 }, { "size", 1 }, { "desc", "Mono/Poly" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "MonoPoly" },
        }},
        { "Parameter", {
          { "addr", 0x00000017 }, { "size", 1 }, { "desc", "Legato Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000018 }, { "size", 1 }, { "desc", "Legato Retrigger" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000019 }, { "size", 1 }, { "desc", "Portamento Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},                        
        { "Parameter", {
          { "addr", 0x0000001A }, { "size", 1 }, { "desc", "Portamento Mode" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "PortamentoMode" },
        }},                        
        { "Parameter", {
          { "addr", 0x0000001B }, { "size", 1 }, { "desc", "Portamento Type" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "PortamentoType" },
        }},                        
        { "Parameter", {
          { "addr", 0x0000001C }, { "size", 1 }, { "desc", "Portamento Start" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "PortamentoStart" },
        }},                        
        { "Parameter", {
          { "addr", 0x0000001D }, { "size", 1 }, { "desc", "Portamento Time" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000022 }, { "size", 1 }, { "desc", "Cutoff Offset" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000023 }, { "size", 1 }, { "desc", "Resonance Offset" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000024 }, { "size", 1 }, { "desc", "Attack Time Offset" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000025 }, { "size", 1 }, { "desc", "Release Time Offset" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000026 }, { "size", 1 }, { "desc", "Velocity Sens Offset" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000028 }, { "size", 1 }, { "desc", "PMT Control Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},                                                            
        { "Parameter", {
          { "addr", 0x00000029 }, { "size", 1 }, { "desc", "Pitch Bend Range Up" },
          { "min", 0 }, { "max", 48 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x0000002A }, { "size", 1 }, { "desc", "Pitch Bend Range Down" },
          { "min", 0 }, { "max", 48 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x0000002B }, { "size", 1 }, { "desc", "Matrix Control 1 Source" },
          { "min", 0 }, { "max", 109 },
          { "type", "choice" }, { "choice_list", "MatrixControlSource" },
        }},
        { "Parameter", {
          { "addr", 0x0000002C }, { "size", 1 }, { "desc", "Matrix Control 1 Destination 1" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x0000002D }, { "size", 1 }, { "desc", "Matrix Control 1 Sens 1" },
          { "template", "SignedMidiByte" },
        }},                        
        { "Parameter", {
          { "addr", 0x0000002E }, { "size", 1 }, { "desc", "Matrix Control 1 Destination 2" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x0000002F }, { "size", 1 }, { "desc", "Matrix Control 1 Sens 2" },
          { "template", "SignedMidiByte" },
        }},                        
        { "Parameter", {
          { "addr", 0x00000030 }, { "size", 1 }, { "desc", "Matrix Control 1 Destination 3" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x00000031 }, { "size", 1 }, { "desc", "Matrix Control 1 Sens 3" },
          { "template", "SignedMidiByte" },
        }},                        
        { "Parameter", {
          { "addr", 0x00000032 }, { "size", 1 }, { "desc", "Matrix Control 1 Destination 4" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x00000033 }, { "size", 1 }, { "desc", "Matrix Control 1 Sens 4" },
          { "template", "SignedMidiByte" },
        }},                        
        { "Parameter", {
          { "addr", 0x00000034 }, { "size", 1 }, { "desc", "Matrix Control 2 Source" },
          { "min", 0 }, { "max", 109 },
          { "type", "choice" }, { "choice_list", "MatrixControlSource" },
        }},
        { "Parameter", {
          { "addr", 0x00000035 }, { "size", 1 }, { "desc", "Matrix Control 2 Destination 1" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x00000036 }, { "size", 1 }, { "desc", "Matrix Control 2 Sens 1" },
          { "template", "SignedMidiByte" },
        }},                        
        { "Parameter", {
          { "addr", 0x00000037 }, { "size", 1 }, { "desc", "Matrix Control 2 Destination 2" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x00000038 }, { "size", 1 }, { "desc", "Matrix Control 2 Sens 2" },
          { "template", "SignedMidiByte" },
        }},                        
        { "Parameter", {
          { "addr", 0x00000039 }, { "size", 1 }, { "desc", "Matrix Control 2 Destination 3" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x0000003A }, { "size", 1 }, { "desc", "Matrix Control 2 Sens 3" },
          { "template", "SignedMidiByte" },
        }},                        
        { "Parameter", {
          { "addr", 0x0000003B }, { "size", 1 }, { "desc", "Matrix Control 2 Destination 4" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x0000003C }, { "size", 1 }, { "desc", "Matrix Control 2 Sens 4" },
          { "template", "SignedMidiByte" },
        }},                        
        { "Parameter", {
          { "addr", 0x0000003D }, { "size", 1 }, { "desc", "Matrix Control 3 Source" },
          { "min", 0 }, { "max", 109 },
          { "type", "choice" }, { "choice_list", "MatrixControlSource" },
        }},
        { "Parameter", {
          { "addr", 0x0000003E }, { "size", 1 }, { "desc", "Matrix Control 3 Destination 1" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x0000003F }, { "size", 1 }, { "desc", "Matrix Control 3 Sens 1" },
          { "template", "SignedMidiByte" },
        }},                        
        { "Parameter", {
          { "addr", 0x00000040 }, { "size", 1 }, { "desc", "Matrix Control 3 Destination 2" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x00000041 }, { "size", 1 }, { "desc", "Matrix Control 3 Sens 2" },
          { "template", "SignedMidiByte" },
        }},                        
        { "Parameter", {
          { "addr", 0x00000042 }, { "size", 1 }, { "desc", "Matrix Control 3 Destination 3" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x00000043 }, { "size", 1 }, { "desc", "Matrix Control 3 Sens 3" },
          { "template", "SignedMidiByte" },
        }},                        
        { "Parameter", {
          { "addr", 0x00000044 }, { "size", 1 }, { "desc", "Matrix Control 3 Destination 4" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x00000045 }, { "size", 1 }, { "desc", "Matrix Control 3 Sens 4" },
          { "template", "SignedMidiByte" },
        }},                        
        { "Parameter", {
          { "addr", 0x00000046 }, { "size", 1 }, { "desc", "Matrix Control 4 Source" },
          { "min", 0 }, { "max", 109 },
          { "type", "choice" }, { "choice_list", "MatrixControlSource" },
        }},
        { "Parameter", {
          { "addr", 0x00000047 }, { "size", 1 }, { "desc", "Matrix Control 4 Destination 1" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x00000048 }, { "size", 1 }, { "desc", "Matrix Control 4 Sens 1" },
          { "template", "SignedMidiByte" },
        }},                        
        { "Parameter", {
          { "addr", 0x00000049 }, { "size", 1 }, { "desc", "Matrix Control 4 Destination 2" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x0000004A }, { "size", 1 }, { "desc", "Matrix Control 4 Sens 2" },
          { "template", "SignedMidiByte" },
        }},                        
        { "Parameter", {
          { "addr", 0x0000004B }, { "size", 1 }, { "desc", "Matrix Control 4 Destination 3" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x0000004C }, { "size", 1 }, { "desc", "Matrix Control 4 Sens 3" },
          { "template", "SignedMidiByte" },
        }},                        
        { "Parameter", {
          { "addr", 0x0000004D }, { "size", 1 }, { "desc", "Matrix Control 4 Destination 4" },
          { "min", 0 }, { "max", 33 },
          { "type", "choice" }, { "choice_list", "MatrixControlDestination" },
        }},
        { "Parameter", {
          { "addr", 0x0000004E }, { "size", 1 }, { "desc", "Matrix Control 4 Sens 4" },
          { "template", "SignedMidiByte" },
        }},                        
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::commonMFXTemplate() {
  return
    { "Template", {{ "name", "Common MFX" }},
      {
        { "Parameter", {
          { "addr", 0x00000000 }, { "size", 1 }, { "desc", "MFX Type" },
          { "min", 0 }, { "max", 67 },
          { "type", "choice" }, { "choice_list", "MFXType" },
        }},
        { "Parameter", {
          { "addr", 0x00000002 }, { "size", 1 }, { "desc", "MFX Chorus Send Level" },
          { "template", "MidiByte" },
        }},              
        { "Parameter", {
          { "addr", 0x00000003 }, { "size", 1 }, { "desc", "MFX Reverb Send Level" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000005 }, { "size", 1 }, { "desc", "MFX Control 1 Source" },
          { "min", 0 }, { "max", 101 },
          { "type", "choice" }, { "choice_list", "MFXControlSource" },
        }},
        { "Parameter", {
          { "addr", 0x00000006 }, { "size", 1 }, { "desc", "MFX Control 1 Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000007 }, { "size", 1 }, { "desc", "MFX Control 2 Source" },
          { "min", 0 }, { "max", 101 },
          { "type", "choice" }, { "choice_list", "MFXControlSource" },
        }},
        { "Parameter", {
          { "addr", 0x00000008 }, { "size", 1 }, { "desc", "MFX Control 2 Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000009 }, { "size", 1 }, { "desc", "MFX Control 3 Source" },
          { "min", 0 }, { "max", 101 },
          { "type", "choice" }, { "choice_list", "MFXControlSource" },
        }},
        { "Parameter", {
          { "addr", 0x0000000A }, { "size", 1 }, { "desc", "MFX Control 3 Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000000B }, { "size", 1 }, { "desc", "MFX Control 4 Source" },
          { "min", 0 }, { "max", 101 },
          { "type", "choice" }, { "choice_list", "MFXControlSource" },
        }},
        { "Parameter", {
          { "addr", 0x0000000C }, { "size", 1 }, { "desc", "MFX Control 4 Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x0000000D }, { "last_addr", 0x00000010 }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 4 },
          { "desc", "MFX Control Assign" }, { "fmt", "MFX Control Assign %d" },
          { "min", 0 }, { "max", 16 },
          { "type", "choice" }, { "choice_list", "OffPartNumber" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000011 }, { "last_addr", 0x0000010D }, { "size", 4 },
          { "first_index", 1 }, { "last_index", 32 },
          { "desc", "MFX Parameter" }, { "fmt", "MFX Parameter %d" },
          { "min", 12768 }, { "max", 52768 }, { "type", "int" },
          { "display_min", -20000 }, { "display_max", 20000 },
        }},

      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::pcmSynthTonePMTTemplate() {
  return
    { "Template", {{ "name", "PCM Synth Tone PMT (Partial Mix Table)" }},
      {
        { "Parameter", {
          { "addr", 0x00000000 }, { "size", 1 }, { "desc", "Structure Type 1 & 2" },
          { "min", 0 }, { "max", 9 }, { "type", "int" },
          { "display_min", 1 }, { "display_max", 10 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000001 }, { "size", 1 }, { "desc", "Booster 1 & 2" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "Booster" },
        }},
        { "Parameter", {
          { "addr", 0x00000002 }, { "size", 1 }, { "desc", "Structure Type 3 & 4" },
          { "min", 0 }, { "max", 9 }, { "type", "int" },
          { "display_min", 1 }, { "display_max", 10 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000003 }, { "size", 1 }, { "desc", "Booster 3 & 4" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "Booster" },
        }},        
        { "Parameter", {
          { "addr", 0x00000004 }, { "size", 1 }, { "desc", "PMT Velocity Control" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "PMTVelocityControl" },
        }},        
        { "Parameter", {
          { "addr", 0x00000005 }, { "size", 1 }, { "desc", "PMT1 Partial Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000006 }, { "size", 1 }, { "desc", "PMT1 Keyboard Range Lower" },
          { "min", 0 }, { "max", 127 },
          { "type", "choice" }, { "choice_list", "KeyboardRange" },
        }},
        { "Parameter", {
          { "addr", 0x00000007 }, { "size", 1 }, { "desc", "PMT1 Keyboard Range Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "type", "choice" }, { "choice_list", "KeyboardRange" },
        }},
        { "Parameter", {
          { "addr", 0x00000008 }, { "size", 1 }, { "desc", "PMT1 Keyboard Fade Width Lower" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000009 }, { "size", 1 }, { "desc", "PMT1 Keyboard Fade Width Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000000A }, { "size", 1 }, { "desc", "PMT1 Velocity Range Lower" },
          { "min", 1 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000000B }, { "size", 1 }, { "desc", "PMT1 Velocity Range Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000000C }, { "size", 1 }, { "desc", "PMT1 Velocity Fade Width Lower" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000000D }, { "size", 1 }, { "desc", "PMT1 Velocity Fade Width Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000000E }, { "size", 1 }, { "desc", "PMT2 Partial Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000000F }, { "size", 1 }, { "desc", "PMT2 Keyboard Range Lower" },
          { "min", 0 }, { "max", 127 },
          { "type", "choice" }, { "choice_list", "KeyboardRange" },
        }},
        { "Parameter", {
          { "addr", 0x00000010 }, { "size", 1 }, { "desc", "PMT2 Keyboard Range Upper" },
          { "min", 0 }, { "max", 127 },
          { "type", "choice" }, { "choice_list", "KeyboardRange" },
        }},
        { "Parameter", {
          { "addr", 0x00000011 }, { "size", 1 }, { "desc", "PMT2 Keyboard Fade Width Lower" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000012 }, { "size", 1 }, { "desc", "PMT2 Keyboard Fade Width Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000013 }, { "size", 1 }, { "desc", "PMT2 Velocity Range Lower" },
          { "min", 1 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000014 }, { "size", 1 }, { "desc", "PMT2 Velocity Range Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000015 }, { "size", 1 }, { "desc", "PMT2 Velocity Fade Width Lower" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000016 }, { "size", 1 }, { "desc", "PMT2 Velocity Fade Width Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000017 }, { "size", 1 }, { "desc", "PMT3 Partial Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000018 }, { "size", 1 }, { "desc", "PMT3 Keyboard Range Lower" },
          { "min", 0 }, { "max", 127 },
          { "type", "choice" }, { "choice_list", "KeyboardRange" },
        }},
        { "Parameter", {
          { "addr", 0x00000019 }, { "size", 1 }, { "desc", "PMT3 Keyboard Range Upper" },
          { "min", 0 }, { "max", 127 },
          { "type", "choice" }, { "choice_list", "KeyboardRange" },
        }},
        { "Parameter", {
          { "addr", 0x0000001A }, { "size", 1 }, { "desc", "PMT3 Keyboard Fade Width Lower" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000001B }, { "size", 1 }, { "desc", "PMT3 Keyboard Fade Width Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000001C }, { "size", 1 }, { "desc", "PMT3 Velocity Range Lower" },
          { "min", 1 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000001D }, { "size", 1 }, { "desc", "PMT3 Velocity Range Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000001E }, { "size", 1 }, { "desc", "PMT3 Velocity Fade Width Lower" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000001F }, { "size", 1 }, { "desc", "PMT3 Velocity Fade Width Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000020 }, { "size", 1 }, { "desc", "PMT4 Partial Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000021 }, { "size", 1 }, { "desc", "PMT4 Keyboard Range Lower" },
          { "min", 0 }, { "max", 127 },
          { "type", "choice" }, { "choice_list", "KeyboardRange" },
        }},
        { "Parameter", {
          { "addr", 0x00000022 }, { "size", 1 }, { "desc", "PMT4 Keyboard Range Upper" },
          { "min", 0 }, { "max", 127 },
          { "type", "choice" }, { "choice_list", "KeyboardRange" },
        }},
        { "Parameter", {
          { "addr", 0x00000023 }, { "size", 1 }, { "desc", "PMT4 Keyboard Fade Width Lower" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000024 }, { "size", 1 }, { "desc", "PMT4 Keyboard Fade Width Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000025 }, { "size", 1 }, { "desc", "PMT4 Velocity Range Lower" },
          { "min", 1 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000026 }, { "size", 1 }, { "desc", "PMT4 Velocity Range Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000027 }, { "size", 1 }, { "desc", "PMT4 Velocity Fade Width Lower" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000028 }, { "size", 1 }, { "desc", "PMT4 Velocity Fade Width Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::pcmSynthTonePartialTemplate() {
  return
    { "Template", {{ "name", "PCM Synth Tone Partial" }},
      {
        { "Parameter", {
          { "addr", 0x00000000 }, { "size", 1 }, { "desc", "Partial Level"},
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000001 }, { "size", 1 }, { "desc", "Partial Coarse Tune" },
          { "template", "CoarseTune" },
        }},
        { "Parameter", {
          { "addr", 0x00000002 }, { "size", 1 }, { "desc", "Partial Fine Tune" },
          { "template", "FineTune" },
        }},
        { "Parameter", {
          { "addr", 0x00000003 }, { "size", 1 }, { "desc", "Partial Random Pitch Depth" },
          { "min", 0 }, { "max", 30 },
          { "type", "choice" }, { "choice_list", "RandomPitchDepth" },
        }},
        { "Parameter", {
          { "addr", 0x00000004 }, { "size", 1 }, { "desc", "Partial Pan" },
          { "template", "Pan" },
        }},
        { "Parameter", {
          { "addr", 0x00000005 }, { "size", 1 }, { "desc", "Partial Pan Keyfollow" },
          { "template", "KeyFollow" },
        }},
        { "Parameter", {
          { "addr", 0x00000006 }, { "size", 1 }, { "desc", "Partial Random Pan Depth" },
          { "min", 0 }, { "max", 63 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000007 }, { "size", 1 }, { "desc", "Partial Alternate Pan Depth" },
          { "min", 1 }, { "max", 127 }, { "type", "int" },
          { "display_min", -63 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000008 }, { "size", 1 }, { "desc", "Partial Env Mode" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "EnvMode" },
        }},
        { "Parameter", {
          { "addr", 0x00000009 }, { "size", 1 }, { "desc", "Partial Delay Mode" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "DelayMode" },
        }},
        { "Parameter", {
          { "addr", 0x0000000A }, { "size", 2 }, { "desc", "Partial Delay Time" },
          { "min", 0 }, { "max", 149 },
          { "type", "choice" }, { "choice_list", "DelayTime" },
        }},
        { "Parameter", {
          { "addr", 0x0000000C }, { "size", 1 }, { "desc", "Partial Output Level" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000000F }, { "size", 1 }, { "desc", "Partial Chorus Send Level" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000010 }, { "size", 1 }, { "desc", "Partial Reverb Send Level" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000012 }, { "size", 1 }, { "desc", "Partial Receive Bender" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000013 }, { "size", 1 }, { "desc", "Partial Receive Expression" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000014 }, { "size", 1 }, { "desc", "Partial Receive Hold-1" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000016 }, { "size", 1 }, { "desc", "Partial Redamper Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000017 }, { "last_addr", 0x0000001A }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 4 },
          { "desc", "Partial Control 1 Switch" }, { "fmt", "Partial Control 1 Switch %d" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "ControlSwitch" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x0000001B }, { "last_addr", 0x0000001E }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 4 },
          { "desc", "Partial Control 2 Switch" }, { "fmt", "Partial Control 2 Switch %d" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "ControlSwitch" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x0000001F }, { "last_addr", 0x00000022 }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 4 },
          { "desc", "Partial Control 3 Switch" }, { "fmt", "Partial Control 3 Switch %d" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "ControlSwitch" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000023 }, { "last_addr", 0x00000026 }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 4 },
          { "desc", "Partial Control 4 Switch" }, { "fmt", "Partial Control 4 Switch %d" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "ControlSwitch" },
        }},
        { "Parameter", {
          { "addr", 0x00000027 }, { "size", 1 }, { "desc", "Wave Group Type" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "WaveGroupType" },
        }},
        { "Parameter", {
          { "addr", 0x00000028 }, { "size", 4 }, { "desc", "Wave Group ID" },
          { "min", 0 }, { "max", 13684 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x0000002C }, { "size", 4 }, { "desc", "Wave Number L (Mono)" },
          { "min", 0 }, { "max", 13684 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000030 }, { "size", 4 }, { "desc", "Wave Number R" },
          { "min", 0 }, { "max", 13684 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000034 }, { "size", 1 }, { "desc", "Wave Gain" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "WaveGain" },
        }},
        { "Parameter", {
          { "addr", 0x00000035 }, { "size", 1 }, { "desc", "Wave FXM Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000036 }, { "size", 1 }, { "desc", "Wave FXM Color" },
          { "min", 0 }, { "max", 3 }, { "type", "int" },
          { "display_min", 1 }, { "display_max", 4},
        }},
        { "Parameter", {
          { "addr", 0x00000037 }, { "size", 1 }, { "desc", "Wave FXM Depth" },
          { "min", 0 }, { "max", 16 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000038 }, { "size", 1 }, { "desc", "Wave Tempo Sync" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000039 }, { "size", 1 }, { "desc", "Wave Pitch Keyfollow" },
          { "min", 44 }, { "max", 84 }, { "type", "int" },
          { "display_min", -200 }, { "display_max", 200 },
        }},
        { "Parameter", {
          { "addr", 0x0000003A }, { "size", 1 }, { "desc", "Pitch Env Depth" },
          { "min", 52 }, { "max", 76 }, { "type", "int" },
          { "display_min", -12 }, { "display_max", 12 },
        }},
        { "Parameter", {
          { "addr", 0x0000003B }, { "size", 1 }, { "desc", "Pitch Env Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000003C }, { "size", 1 }, { "desc", "Pitch Env Time 1 Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000003D }, { "size", 1 }, { "desc", "Pitch Env Time 4 Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000003E }, { "size", 1 }, { "desc", "Pitch Env Time Keyfollow" },
          { "template", "KeyFollow" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x0000003F }, { "last_addr", 0x00000042 }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 4 },
          { "desc", "Pitch Env Time" }, { "fmt", "Pitch Env Time %d" },
          { "template", "MidiByte" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000043 }, { "last_addr", 0x00000047 }, { "size", 1 },
          { "first_index", 0 }, { "last_index", 4 },
          { "desc", "Pitch Env Level" }, { "fmt", "Pitch Env Level %d" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000048 }, { "size", 1 }, { "desc", "TVF Filter Type" },
          { "min", 0 }, { "max", 6 },
          { "type", "choice" }, { "choice_list", "FilterType" },
        }},
        { "Parameter", {
          { "addr", 0x00000049 }, { "size", 1 }, { "desc", "TVF Cutoff Frequency" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x0000004A }, { "size", 1 }, { "desc", "TVF Cutoff Keyfollow" },
          { "min", 44 }, { "max", 84 }, { "type", "int" },
          { "display_min", -200 }, { "display_max", 200 },
        }},
        { "Parameter", {
          { "addr", 0x0000004B }, { "size", 1 }, { "desc", "TVF Cutoff Velocity Curve" },
          { "min", 0 }, { "max", 7 },
          { "type", "choice" }, { "choice_list", "VelocityCurve" },
        }},
        { "Parameter", {
          { "addr", 0x0000004C }, { "size", 1 }, { "desc", "TVF Cutoff Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000004D }, { "size", 1 }, { "desc", "TVF Resonance" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x0000004E }, { "size", 1 }, { "desc", "TVF Resonance Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000004F }, { "size", 1 }, { "desc", "TVF Env Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000050 }, { "size", 1 }, { "desc", "TVF Env Velocity Curve" },
          { "min", 0 }, { "max", 7 },
          { "type", "choice" }, { "choice_list", "VelocityCurve" },
        }},
        { "Parameter", {
          { "addr", 0x00000051 }, { "size", 1 }, { "desc", "TVF Env Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000052 }, { "size", 1 }, { "desc", "TVF Env Time 1 Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000053 }, { "size", 1 }, { "desc", "TVF Env Time 4 Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000054 }, { "size", 1 }, { "desc", "TVF Env Time Keyfollow" },
          { "template", "KeyFollow" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000055 }, { "last_addr", 0x00000058 }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 4 },
          { "desc", "TVF Env Time" }, { "fmt", "TVF Env Time %d" },
          { "template", "MidiByte" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000059 }, { "last_addr", 0x0000005D }, { "size", 1 },
          { "first_index", 0 }, { "last_index", 4 },
          { "desc", "TVF Env Level" }, { "fmt", "TVF Env Level %d" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000005E }, { "size", 4 }, { "desc", "Bias Level" },
          { "min", 54 }, { "max", 74 }, { "type", "int" },
          { "display_min", -100 }, { "display_max", 100. }
        }},
        { "Parameter", {
          { "addr", 0x0000005F }, { "size", 1 }, { "desc", "Bias Position" },
          { "min", 0 }, { "max", 127 },
          { "type", "choice" }, { "choice_list", "KeyboardRange" },
        }},
        { "Parameter", {
          { "addr", 0x00000060 }, { "size", 1 }, { "desc", "Bias Direction" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "BiasDirection" },
        }},
        { "Parameter", {
          { "addr", 0x00000061 }, { "size", 1 }, { "desc", "TVA Env Velocity Curve" },
          { "min", 0 }, { "max", 7 },
          { "type", "choice" }, { "choice_list", "VelocityCurve" },
        }},
        { "Parameter", {
          { "addr", 0x00000062 }, { "size", 1 }, { "desc", "TVA Env Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000063 }, { "size", 1 }, { "desc", "TVA Env Time 1 Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000064 }, { "size", 1 }, { "desc", "TVA Env Time 4 Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000065 }, { "size", 1 }, { "desc", "TVA Env Time Keyfollow" },
          { "template", "KeyFollow" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000066 }, { "last_addr", 0x00000069 }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 4 },
          { "desc", "TVA Env Time" }, { "fmt", "TVA Env Time %d" },
          { "template", "MidiByte" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x0000006A }, { "last_addr", 0x0000006C }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 3 },
          { "desc", "TVA Env Level" }, { "fmt", "TVA Env Level %d" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000006D }, { "size", 1 }, { "desc", "LFO1 Waveform" },
          { "min", 0 }, { "max", 12 },
          { "type", "choice" }, { "choice_list", "LFOWaveform" },
        }},
        { "Parameter", {
          { "addr", 0x0000006E }, { "size", 2 }, { "desc", "LFO1 Rate" },
          { "min", 0 }, { "max", 149 },
          { "type", "choice" }, { "choice_list", "DelayTime" },
        }},
        { "Parameter", {
          { "addr", 0x00000070 }, { "size", 1 }, { "desc", "LFO1 Offset" },
          { "min", 0 }, { "max", 4 }, { "type", "int" },
          { "display_min", -100 }, { "display_max", 100 },
        }},
        { "Parameter", {
          { "addr", 0x00000071 }, { "size", 1 }, { "desc", "LFO1 Rate Detune" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000072 }, { "size", 1 }, { "desc", "LFO1 Delay Time" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000073 }, { "size", 1 }, { "desc", "LFO1 Delay Time Keyfollow" },
          { "template", "KeyFollow" },
        }},
        { "Parameter", {
          { "addr", 0x00000074 }, { "size", 2 }, { "desc", "LFO1 Fade Mode" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "FadeMode" },
        }},
        { "Parameter", {
          { "addr", 0x00000075 }, { "size", 1 }, { "desc", "LFO1 Fade Time" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000076 }, { "size", 1 }, { "desc", "LFO1 Key Trigger" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000077 }, { "size", 1 }, { "desc", "LFO1 Pitch Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000078 }, { "size", 1 }, { "desc", "LFO1 TVF Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000079 }, { "size", 1 }, { "desc", "LFO1 TVA Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000007A }, { "size", 1 }, { "desc", "LFO1 Pan Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000007B }, { "size", 1 }, { "desc", "LFO2 Waveform" },
          { "min", 0 }, { "max", 12 },
          { "type", "choice" }, { "choice_list", "LFOWaveform" },
        }},
        { "Parameter", {
          { "addr", 0x0000007C }, { "size", 2 }, { "desc", "LFO2 Rate" },
          { "min", 0 }, { "max", 149 },
          { "type", "choice" }, { "choice_list", "DelayTime" },
        }},
        { "Parameter", {
          { "addr", 0x0000007E }, { "size", 1 }, { "desc", "LFO2 Offset" },
          { "min", 0 }, { "max", 4 }, { "type", "int" },
          { "display_min", -100 }, { "display_max", 100 },
        }},
        { "Parameter", {
          { "addr", 0x0000007F }, { "size", 1 }, { "desc", "LFO2 Rate Detune" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000100 }, { "size", 1 }, { "desc", "LFO2 Delay Time" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000101 }, { "size", 1 }, { "desc", "LFO2 Delay Time Keyfollow" },
          { "template", "KeyFollow" },
        }},
        { "Parameter", {
          { "addr", 0x00000102 }, { "size", 2 }, { "desc", "LFO2 Fade Mode" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "FadeMode" },
        }},
        { "Parameter", {
          { "addr", 0x00000103 }, { "size", 1 }, { "desc", "LFO2 Fade Time" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000104 }, { "size", 1 }, { "desc", "LFO2 Key Trigger" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000105 }, { "size", 1 }, { "desc", "LFO2 Pitch Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000106 }, { "size", 1 }, { "desc", "LFO2 TVF Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000107 }, { "size", 1 }, { "desc", "LFO2 TVA Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000108 }, { "size", 1 }, { "desc", "LFO2 Pan Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000109 }, { "size", 1 }, { "desc", "LFO Step Type" },
          { "min", 0 }, { "max", 1 }, { "type", "int" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x0000010A }, { "last_addr", 0x00000119 }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 16 },
          { "desc", "LFO Step" }, { "fmt", "LFO Step%d" },
          { "min", 28 }, { "max", 100 }, { "type", "int" },
          { "display_min", -36 }, { "display_max", 36 },
        }},
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::pcmSynthToneCommon2Template() {
  return
    { "Template", {{ "name", "PCM Synth Tone Common 2" }},
      {
        { "Parameter", {
          { "addr", 0x00000010 }, { "size", 1 }, { "desc", "Tone Category" },
          { "min", 0 }, { "max", 34 },  // 0-127 but only 35 categories
          { "type", "choice" }, { "choice_list", "ToneCategory" },
        }},
        { "Parameter", {
          { "addr", 0x00000013 }, { "size", 1 }, { "desc", "Phrase Octave Shift" },
          { "min", 61 }, { "max", 67 }, { "type", "int" },
          { "display_min", -3 }, { "display_max", 3 },
        }},
        { "Parameter", {
          { "addr", 0x00000033 }, { "size", 1 }, { "desc", "TFX Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" }
        }},
        { "Parameter", {
          { "addr", 0x00000038 }, { "size", 4 }, { "desc", "Phrase Number" },
          { "min", 0 }, { "max", 65535 }, { "type", "int" },
        }},
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::pcmDrumKitCommonTemplate() {
  return
    { "Template", {{ "name", "PCM Drum Kit Common" }},
      {
        { "TextParameter", {
          { "first_addr", 0x00000000 }, { "last_addr", 0x0000000B }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 12 },
          { "desc", "Kit Name" }, { "fmt", "Kit Name %d" },
          { "type", "ascii" },
        }},
        { "Parameter", {
          { "addr", 0x0000000C }, { "size", 1 }, { "desc", "Kit Level" },
          { "template", "MidiByte" }
        }},
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::commonCompEqTemplate() {
  return
    { "Template", {{ "name", "Common Comp/EQ" }},
      {
        { "Parameter", {
          { "addr", 0x00000000 }, { "size", 1 }, { "desc", "Comp1 Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000001 }, { "size", 1 }, { "desc", "Comp1 Attack Time" },
          { "min", 0 }, { "max", 31 },
          { "type", "choice" }, { "choice_list", "AttackTime" },
        }},
        { "Parameter", {
          { "addr", 0x00000002 }, { "size", 1 }, { "desc", "Comp1 Release Time" },
          { "min", 0 }, { "max", 23 },
          { "type", "choice" }, { "choice_list", "ReleaseTime" },
        }},
        { "Parameter", {
          { "addr", 0x00000003 }, { "size", 1 }, { "desc", "Comp1 Threshold" },
          { "template", "MidiByte" }
        }},
        { "Parameter", {
          { "addr", 0x00000004 }, { "size", 1 }, { "desc", "Comp1 Ratio" },
          { "min", 0 }, { "max", 19 },
          { "type", "choice" }, { "choice_list", "CompRatio" },
        }},
        { "Parameter", {
          { "addr", 0x00000005 }, { "size", 1 }, { "desc", "Comp1 Output Gain" },
          { "min", 0 }, { "max", 24 },
          { "type", "choice" }, { "choice_list", "CompGain" },
        }},
        { "Parameter", {
          { "addr", 0x00000006 }, { "size", 1 }, { "desc", "EQ1 Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000007 }, { "size", 1 }, { "desc", "EQ1 Low Freq" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "EqLowFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000008 }, { "size", 1 }, { "desc", "EQ1 Low Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000009 }, { "size", 1 }, { "desc", "EQ1 Mid Freq" },
          { "min", 0 }, { "max", 16 },
          { "type", "choice" }, { "choice_list", "EqMidFreq" },
        }},
        { "Parameter", {
          { "addr", 0x0000000A }, { "size", 1 }, { "desc", "EQ1 Mid Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x0000000B }, { "size", 1 }, { "desc", "EQ1 Mid Q" },
          { "min", 0 }, { "max", 4 },
          { "type", "choice" }, { "choice_list", "EqQ" },
        }},
        { "Parameter", {
          { "addr", 0x0000000C }, { "size", 1 }, { "desc", "EQ1 High Freq" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "EqHighFreq" },
        }},
        { "Parameter", {
          { "addr", 0x0000000D }, { "size", 1 }, { "desc", "EQ1 High Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x0000000E }, { "size", 1 }, { "desc", "Comp2 Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000000F }, { "size", 1 }, { "desc", "Comp2 Attack Time" },
          { "min", 0 }, { "max", 31 },
          { "type", "choice" }, { "choice_list", "AttackTime" },
        }},
        { "Parameter", {
          { "addr", 0x00000010 }, { "size", 1 }, { "desc", "Comp2 Release Time" },
          { "min", 0 }, { "max", 23 },
          { "type", "choice" }, { "choice_list", "ReleaseTime" },
        }},
        { "Parameter", {
          { "addr", 0x00000011 }, { "size", 1 }, { "desc", "Comp2 Threshold" },
          { "template", "MidiByte" }
        }},
        { "Parameter", {
          { "addr", 0x00000012 }, { "size", 1 }, { "desc", "Comp2 Ratio" },
          { "min", 0 }, { "max", 19 },
          { "type", "choice" }, { "choice_list", "CompRatio" },
        }},
        { "Parameter", {
          { "addr", 0x00000013 }, { "size", 1 }, { "desc", "Comp2 Output Gain" },
          { "min", 0 }, { "max", 24 },
          { "type", "choice" }, { "choice_list", "CompGain" },
        }},
        { "Parameter", {
          { "addr", 0x00000014 }, { "size", 1 }, { "desc", "EQ2 Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000015 }, { "size", 1 }, { "desc", "EQ2 Low Freq" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "EqLowFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000016 }, { "size", 1 }, { "desc", "EQ2 Low Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000017 }, { "size", 1 }, { "desc", "EQ2 Mid Freq" },
          { "min", 0 }, { "max", 16 },
          { "type", "choice" }, { "choice_list", "EqMidFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000018 }, { "size", 1 }, { "desc", "EQ2 Mid Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000019 }, { "size", 1 }, { "desc", "EQ2 Mid Q" },
          { "min", 0 }, { "max", 4 },
          { "type", "choice" }, { "choice_list", "EqQ" },
        }},
        { "Parameter", {
          { "addr", 0x0000001A }, { "size", 1 }, { "desc", "EQ2 High Freq" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "EqHighFreq" },
        }},
        { "Parameter", {
          { "addr", 0x0000001B }, { "size", 1 }, { "desc", "EQ2 High Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x0000001C }, { "size", 1 }, { "desc", "Comp3 Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000001D }, { "size", 1 }, { "desc", "Comp3 Attack Time" },
          { "min", 0 }, { "max", 31 },
          { "type", "choice" }, { "choice_list", "AttackTime" },
        }},
        { "Parameter", {
          { "addr", 0x0000001E }, { "size", 1 }, { "desc", "Comp3 Release Time" },
          { "min", 0 }, { "max", 23 },
          { "type", "choice" }, { "choice_list", "ReleaseTime" },
        }},
        { "Parameter", {
          { "addr", 0x0000001F }, { "size", 1 }, { "desc", "Comp3 Threshold" },
          { "template", "MidiByte" }
        }},
        { "Parameter", {
          { "addr", 0x00000020 }, { "size", 1 }, { "desc", "Comp3 Ratio" },
          { "min", 0 }, { "max", 19 },
          { "type", "choice" }, { "choice_list", "CompRatio" },
        }},
        { "Parameter", {
          { "addr", 0x00000021 }, { "size", 1 }, { "desc", "Comp3 Output Gain" },
          { "min", 0 }, { "max", 24 },
          { "type", "choice" }, { "choice_list", "CompGain" },
        }},
        { "Parameter", {
          { "addr", 0x00000022 }, { "size", 1 }, { "desc", "EQ3 Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000023 }, { "size", 1 }, { "desc", "EQ3 Low Freq" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "EqLowFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000024 }, { "size", 1 }, { "desc", "EQ3 Low Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000025 }, { "size", 1 }, { "desc", "EQ3 Mid Freq" },
          { "min", 0 }, { "max", 16 },
          { "type", "choice" }, { "choice_list", "EqMidFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000026 }, { "size", 1 }, { "desc", "EQ3 Mid Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000027 }, { "size", 1 }, { "desc", "EQ3 Mid Q" },
          { "min", 0 }, { "max", 4 },
          { "type", "choice" }, { "choice_list", "EqQ" },
        }},
        { "Parameter", {
          { "addr", 0x00000028 }, { "size", 1 }, { "desc", "EQ3 High Freq" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "EqHighFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000029 }, { "size", 1 }, { "desc", "EQ3 High Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x0000002A }, { "size", 1 }, { "desc", "Comp4 Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000002B }, { "size", 1 }, { "desc", "Comp4 Attack Time" },
          { "min", 0 }, { "max", 31 },
          { "type", "choice" }, { "choice_list", "AttackTime" },
        }},
        { "Parameter", {
          { "addr", 0x0000002C }, { "size", 1 }, { "desc", "Comp4 Release Time" },
          { "min", 0 }, { "max", 23 },
          { "type", "choice" }, { "choice_list", "ReleaseTime" },
        }},
        { "Parameter", {
          { "addr", 0x0000002D }, { "size", 1 }, { "desc", "Comp4 Threshold" },
          { "template", "MidiByte" }
        }},
        { "Parameter", {
          { "addr", 0x0000002E }, { "size", 1 }, { "desc", "Comp4 Ratio" },
          { "min", 0 }, { "max", 19 },
          { "type", "choice" }, { "choice_list", "CompRatio" },
        }},
        { "Parameter", {
          { "addr", 0x0000002F }, { "size", 1 }, { "desc", "Comp4 Output Gain" },
          { "min", 0 }, { "max", 24 },
          { "type", "choice" }, { "choice_list", "CompGain" },
        }},
        { "Parameter", {
          { "addr", 0x00000030 }, { "size", 1 }, { "desc", "EQ4 Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000031 }, { "size", 1 }, { "desc", "EQ4 Low Freq" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "EqLowFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000032 }, { "size", 1 }, { "desc", "EQ4 Low Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000033 }, { "size", 1 }, { "desc", "EQ4 Mid Freq" },
          { "min", 0 }, { "max", 16 },
          { "type", "choice" }, { "choice_list", "EqMidFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000034 }, { "size", 1 }, { "desc", "EQ4 Mid Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000035 }, { "size", 1 }, { "desc", "EQ4 Mid Q" },
          { "min", 0 }, { "max", 4 },
          { "type", "choice" }, { "choice_list", "EqQ" },
        }},
        { "Parameter", {
          { "addr", 0x00000036 }, { "size", 1 }, { "desc", "EQ4 High Freq" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "EqHighFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000037 }, { "size", 1 }, { "desc", "EQ4 High Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000038 }, { "size", 1 }, { "desc", "Comp5 Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000039 }, { "size", 1 }, { "desc", "Comp5 Attack Time" },
          { "min", 0 }, { "max", 31 },
          { "type", "choice" }, { "choice_list", "AttackTime" },
        }},
        { "Parameter", {
          { "addr", 0x0000003A }, { "size", 1 }, { "desc", "Comp5 Release Time" },
          { "min", 0 }, { "max", 23 },
          { "type", "choice" }, { "choice_list", "ReleaseTime" },
        }},
        { "Parameter", {
          { "addr", 0x0000003B }, { "size", 1 }, { "desc", "Comp5 Threshold" },
          { "template", "MidiByte" }
        }},
        { "Parameter", {
          { "addr", 0x0000003C }, { "size", 1 }, { "desc", "Comp5 Ratio" },
          { "min", 0 }, { "max", 19 },
          { "type", "choice" }, { "choice_list", "CompRatio" },
        }},
        { "Parameter", {
          { "addr", 0x0000003D }, { "size", 1 }, { "desc", "Comp5 Output Gain" },
          { "min", 0 }, { "max", 24 },
          { "type", "choice" }, { "choice_list", "CompGain" },
        }},
        { "Parameter", {
          { "addr", 0x0000003E }, { "size", 1 }, { "desc", "EQ5 Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000003F }, { "size", 1 }, { "desc", "EQ5 Low Freq" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "EqLowFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000040 }, { "size", 1 }, { "desc", "EQ5 Low Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000041 }, { "size", 1 }, { "desc", "EQ5 Mid Freq" },
          { "min", 0 }, { "max", 16 },
          { "type", "choice" }, { "choice_list", "EqMidFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000042 }, { "size", 1 }, { "desc", "EQ5 Mid Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000043 }, { "size", 1 }, { "desc", "EQ5 Mid Q" },
          { "min", 0 }, { "max", 4 },
          { "type", "choice" }, { "choice_list", "EqQ" },
        }},
        { "Parameter", {
          { "addr", 0x00000044 }, { "size", 1 }, { "desc", "EQ5 High Freq" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "EqHighFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000045 }, { "size", 1 }, { "desc", "EQ5 High Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000046 }, { "size", 1 }, { "desc", "Comp6 Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000047 }, { "size", 1 }, { "desc", "Comp6 Attack Time" },
          { "min", 0 }, { "max", 31 },
          { "type", "choice" }, { "choice_list", "AttackTime" },
        }},
        { "Parameter", {
          { "addr", 0x00000048 }, { "size", 1 }, { "desc", "Comp6 Release Time" },
          { "min", 0 }, { "max", 23 },
          { "type", "choice" }, { "choice_list", "ReleaseTime" },
        }},
        { "Parameter", {
          { "addr", 0x00000049 }, { "size", 1 }, { "desc", "Comp6 Threshold" },
          { "template", "MidiByte" }
        }},
        { "Parameter", {
          { "addr", 0x0000004A }, { "size", 1 }, { "desc", "Comp6 Ratio" },
          { "min", 0 }, { "max", 19 },
          { "type", "choice" }, { "choice_list", "CompRatio" },
        }},
        { "Parameter", {
          { "addr", 0x0000004B }, { "size", 1 }, { "desc", "Comp6 Output Gain" },
          { "min", 0 }, { "max", 24 },
          { "type", "choice" }, { "choice_list", "CompGain" },
        }},
        { "Parameter", {
          { "addr", 0x0000004C }, { "size", 1 }, { "desc", "EQ6 Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000004D }, { "size", 1 }, { "desc", "EQ6 Low Freq" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "EqLowFreq" },
        }},
        { "Parameter", {
          { "addr", 0x0000004E }, { "size", 1 }, { "desc", "EQ6 Low Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x0000004F }, { "size", 1 }, { "desc", "EQ6 Mid Freq" },
          { "min", 0 }, { "max", 16 },
          { "type", "choice" }, { "choice_list", "EqMidFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000050 }, { "size", 1 }, { "desc", "EQ6 Mid Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
        { "Parameter", {
          { "addr", 0x00000051 }, { "size", 1 }, { "desc", "EQ6 Mid Q" },
          { "min", 0 }, { "max", 4 },
          { "type", "choice" }, { "choice_list", "EqQ" },
        }},
        { "Parameter", {
          { "addr", 0x00000052 }, { "size", 1 }, { "desc", "EQ6 High Freq" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "EqHighFreq" },
        }},
        { "Parameter", {
          { "addr", 0x00000053 }, { "size", 1 }, { "desc", "EQ6 High Gain" },
          { "min", 0 }, { "max", 30 }, { "type", "int" },
          { "display_min", -15 }, { "display_max", 15 },
        }},        
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::pcmDrumKitPartialTemplate() {
  return
    { "Template", {{ "name", "PCM Drum Kit Partial" }},
      {
        { "TextParameter", {
          { "first_addr", 0x00000000 }, { "last_addr", 0x0000000B }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 12 },
          { "desc", "Partial Name" }, { "fmt", "Partial Name %d" },
          { "type", "ascii" },
        }},
        { "Parameter", {
          { "addr", 0x0000000C }, { "size", 1 }, { "desc", "Assign Type" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "AssignType" },
        }},
        { "Parameter", {
          { "addr", 0x0000000D }, { "size", 1 }, { "desc", "Mute Group" },
          { "min", 0 }, { "max", 31 }, { "type", "int" },
          { "type", "choice" }, { "choice_list", "MuteGroup" },
        }},
        { "Parameter", {
          { "addr", 0x0000000E }, { "size", 1 }, { "desc", "Partial Level" },
          { "template", "MidiByte" },
        }},
         { "Parameter", {
          { "addr", 0x0000000F }, { "size", 1 }, { "desc", "Partial Coarse Tune" },
          { "template", "CoarseTune" },
        }},
        { "Parameter", {
          { "addr", 0x00000010 }, { "size", 1 }, { "desc", "Partial Fine Tune" },
          { "template", "FineTune" },
        }},
        { "Parameter", {
          { "addr", 0x00000011 }, { "size", 1 }, { "desc", "Partial Random Pitch Depth" },
          { "min", 0 }, { "max", 30 },
          { "type", "choice" }, { "choice_list", "RandomPitchDepth" },
        }},
        { "Parameter", {
          { "addr", 0x00000012 }, { "size", 1 }, { "desc", "Partial Pan" },
          { "template", "Pan" },
        }},
        { "Parameter", {
          { "addr", 0x00000013 }, { "size", 1 }, { "desc", "Partial Random Pan Depth" },
          { "min", 0 }, { "max", 63 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000014 }, { "size", 1 }, { "desc", "Partial Alternate Pan Depth" },
          { "min", 1 }, { "max", 127 }, { "type", "int" },
          { "display_min", -63 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000015 }, { "size", 1 }, { "desc", "Partial Env Mode" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "EnvMode" },
        }},
        { "Parameter", {
          { "addr", 0x00000016 }, { "size", 1 }, { "desc", "Partial Output Level" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000019 }, { "size", 1 }, { "desc", "Partial Chorus Send Level" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000001A }, { "size", 1 }, { "desc", "Partial Reverb Send Level" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000001B }, { "size", 1 }, { "desc", "Partial Output Assign" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "CompGroupAssign" },
        }},
        { "Parameter", {
          { "addr", 0x0000001C }, { "size", 1 }, { "desc", "Partial Pitch Bend Range" },
          { "min", 0 }, { "max", 48 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000001D }, { "size", 1 }, { "desc", "Partial Receive Expression" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000001E }, { "size", 1 }, { "desc", "Partial Receive Hold-1" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000020 }, { "size", 1 }, { "desc", "WMT Velocity Control" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "VelocityControl" },
        }},
        { "Parameter", {
          { "addr", 0x00000021 }, { "size", 1 }, { "desc", "WMT1 Wave Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
         { "Parameter", {
          { "addr", 0x00000022 }, { "size", 1 }, { "desc", "WMT1 Wave Group Type" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "WaveGroupType" },
        }},
        { "Parameter", {
          { "addr", 0x00000023 }, { "size", 4 }, { "desc", "WMT1 Wave Group ID" },
          { "min", 0 }, { "max", 13684 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000027 }, { "size", 4 }, { "desc", "WMT1 Wave Number L (Mono)" },
          { "min", 0 }, { "max", 13684 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x0000002B }, { "size", 4 }, { "desc", "WMT1 Wave Number R" },
          { "min", 0 }, { "max", 13684 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x0000002F }, { "size", 1 }, { "desc", "WMT1 Wave Gain" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "WaveGain" },
        }},
        { "Parameter", {
          { "addr", 0x00000030 }, { "size", 1 }, { "desc", "WMT1 Wave FXM Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000031 }, { "size", 1 }, { "desc", "WMT1 Wave FXM Color" },
          { "min", 0 }, { "max", 3 }, { "type", "int" },
          { "display_min", 1 }, { "display_max", 4},
        }},
        { "Parameter", {
          { "addr", 0x00000032 }, { "size", 1 }, { "desc", "WMT1 Wave FXM Depth" },
          { "min", 0 }, { "max", 16 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000033 }, { "size", 1 }, { "desc", "WMT1 Wave Tempo Sync" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000034 }, { "size", 1 }, { "desc", "WMT1 Wave Coarse Tune" },
          { "template", "CoarseTune" },
        }},
        { "Parameter", {
          { "addr", 0x00000035 }, { "size", 1 }, { "desc", "WMT1 Wave Fine Tune" },
          { "template", "FineTune" },
        }},
        { "Parameter", {
          { "addr", 0x00000036 }, { "size", 1 }, { "desc", "WMT1 Wave Pan" },
          { "template", "Pan" },
        }},
        { "Parameter", {
          { "addr", 0x00000037 }, { "size", 1 }, { "desc", "WMT1 Wave Random Pan Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000038 }, { "size", 1 }, { "desc", "WMT1 Wave Alternate Pan Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "ControlSwitch" },
        }},
        { "Parameter", {
          { "addr", 0x00000039 }, { "size", 1 }, { "desc", "WMT1 Wave Level" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000003A }, { "size", 1 }, { "desc", "WMT1 Velocity Range Lower" },
          { "min", 1 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000003B }, { "size", 1 }, { "desc", "WMT1 Velocity Range Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000003C }, { "size", 1 }, { "desc", "WMT1 Velocity Fade Width Lower" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000003D }, { "size", 1 }, { "desc", "WMT1 Velocity Fade Width Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000003E }, { "size", 1 }, { "desc", "WMT2 Wave Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
         { "Parameter", {
          { "addr", 0x0000003F }, { "size", 1 }, { "desc", "WMT2 Wave Group Type" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "WaveGroupType" },
        }},
        { "Parameter", {
          { "addr", 0x00000040 }, { "size", 4 }, { "desc", "WMT2 Wave Group ID" },
          { "min", 0 }, { "max", 13684 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000044 }, { "size", 4 }, { "desc", "WMT2 Wave Number L (Mono)" },
          { "min", 0 }, { "max", 13684 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000048 }, { "size", 4 }, { "desc", "WMT2 Wave Number R" },
          { "min", 0 }, { "max", 13684 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x0000004C }, { "size", 1 }, { "desc", "WMT2 Wave Gain" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "WaveGain" },
        }},
        { "Parameter", {
          { "addr", 0x0000004D }, { "size", 1 }, { "desc", "WMT2 Wave FXM Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000004E }, { "size", 1 }, { "desc", "WMT2 Wave FXM Color" },
          { "min", 0 }, { "max", 3 }, { "type", "int" },
          { "display_min", 1 }, { "display_max", 4},
        }},
        { "Parameter", {
          { "addr", 0x0000004F }, { "size", 1 }, { "desc", "WMT2 Wave FXM Depth" },
          { "min", 0 }, { "max", 16 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000050 }, { "size", 1 }, { "desc", "WMT2 Wave Tempo Sync" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000051 }, { "size", 1 }, { "desc", "WMT2 Wave Coarse Tune" },
          { "template", "CoarseTune" },
        }},
        { "Parameter", {
          { "addr", 0x00000052 }, { "size", 1 }, { "desc", "WMT2 Wave Fine Tune" },
          { "template", "FineTune" },
        }},
        { "Parameter", {
          { "addr", 0x00000053 }, { "size", 1 }, { "desc", "WMT2 Wave Pan" },
          { "template", "Pan" },
        }},
        { "Parameter", {
          { "addr", 0x00000054 }, { "size", 1 }, { "desc", "WMT2 Wave Random Pan Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000055 }, { "size", 1 }, { "desc", "WMT2 Wave Alternate Pan Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "ControlSwitch" },
        }},
        { "Parameter", {
          { "addr", 0x00000056 }, { "size", 1 }, { "desc", "WMT2 Wave Level" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000057 }, { "size", 1 }, { "desc", "WMT2 Velocity Range Lower" },
          { "min", 1 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000058 }, { "size", 1 }, { "desc", "WMT2 Velocity Range Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000059 }, { "size", 1 }, { "desc", "WMT2 Velocity Fade Width Lower" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000005A }, { "size", 1 }, { "desc", "WMT2 Velocity Fade Width Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000005B }, { "size", 1 }, { "desc", "WMT3 Wave Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
         { "Parameter", {
          { "addr", 0x0000005C }, { "size", 1 }, { "desc", "WMT3 Wave Group Type" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "WaveGroupType" },
        }},
        { "Parameter", {
          { "addr", 0x0000005D }, { "size", 4 }, { "desc", "WMT3 Wave Group ID" },
          { "min", 0 }, { "max", 13684 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000061 }, { "size", 4 }, { "desc", "WMT3 Wave Number L (Mono)" },
          { "min", 0 }, { "max", 13684 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000065 }, { "size", 4 }, { "desc", "WMT3 Wave Number R" },
          { "min", 0 }, { "max", 13684 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000069 }, { "size", 1 }, { "desc", "WMT3 Wave Gain" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "WaveGain" },
        }},
        { "Parameter", {
          { "addr", 0x0000006A }, { "size", 1 }, { "desc", "WMT3 Wave FXM Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000006B }, { "size", 1 }, { "desc", "WMT3 Wave FXM Color" },
          { "min", 0 }, { "max", 3 }, { "type", "int" },
          { "display_min", 1 }, { "display_max", 4},
        }},
        { "Parameter", {
          { "addr", 0x0000006C }, { "size", 1 }, { "desc", "WMT3 Wave FXM Depth" },
          { "min", 0 }, { "max", 16 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000006D }, { "size", 1 }, { "desc", "WMT3 Wave Tempo Sync" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000006E }, { "size", 1 }, { "desc", "WMT3 Wave Coarse Tune" },
          { "template", "CoarseTune" },
        }},
        { "Parameter", {
          { "addr", 0x0000006F }, { "size", 1 }, { "desc", "WMT3 Wave Fine Tune" },
          { "template", "FineTune" },
        }},
        { "Parameter", {
          { "addr", 0x00000070 }, { "size", 1 }, { "desc", "WMT3 Wave Pan" },
          { "template", "Pan" },
        }},
        { "Parameter", {
          { "addr", 0x00000071 }, { "size", 1 }, { "desc", "WMT3 Wave Random Pan Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000072 }, { "size", 1 }, { "desc", "WMT3 Wave Alternate Pan Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "ControlSwitch" },
        }},
        { "Parameter", {
          { "addr", 0x00000073 }, { "size", 1 }, { "desc", "WMT3 Wave Level" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000074 }, { "size", 1 }, { "desc", "WMT3 Velocity Range Lower" },
          { "min", 1 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000075 }, { "size", 1 }, { "desc", "WMT3 Velocity Range Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000076 }, { "size", 1 }, { "desc", "WMT3 Velocity Fade Width Lower" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000077 }, { "size", 1 }, { "desc", "WMT3 Velocity Fade Width Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000078 }, { "size", 1 }, { "desc", "WMT4 Wave Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
         { "Parameter", {
          { "addr", 0x00000079 }, { "size", 1 }, { "desc", "WMT4 Wave Group Type" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "WaveGroupType" },
        }},
        { "Parameter", {
          { "addr", 0x0000007A }, { "size", 4 }, { "desc", "WMT4 Wave Group ID" },
          { "min", 0 }, { "max", 13684 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x0000007E }, { "size", 4 }, { "desc", "WMT4 Wave Number L (Mono)" },
          { "min", 0 }, { "max", 13684 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000102 }, { "size", 4 }, { "desc", "WMT4 Wave Number R" },
          { "min", 0 }, { "max", 13684 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000106 }, { "size", 1 }, { "desc", "WMT4 Wave Gain" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "WaveGain" },
        }},
        { "Parameter", {
          { "addr", 0x00000107 }, { "size", 1 }, { "desc", "WMT4 Wave FXM Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000108 }, { "size", 1 }, { "desc", "WMT4 Wave FXM Color" },
          { "min", 0 }, { "max", 3 }, { "type", "int" },
          { "display_min", 1 }, { "display_max", 4},
        }},
        { "Parameter", {
          { "addr", 0x00000109 }, { "size", 1 }, { "desc", "WMT4 Wave FXM Depth" },
          { "min", 0 }, { "max", 16 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000010A }, { "size", 1 }, { "desc", "WMT4 Wave Tempo Sync" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000010B }, { "size", 1 }, { "desc", "WMT4 Wave Coarse Tune" },
          { "template", "CoarseTune" },
        }},
        { "Parameter", {
          { "addr", 0x0000010C }, { "size", 1 }, { "desc", "WMT4 Wave Fine Tune" },
          { "template", "FineTune" },
        }},
        { "Parameter", {
          { "addr", 0x0000010D }, { "size", 1 }, { "desc", "WMT4 Wave Pan" },
          { "template", "Pan" },
        }},
        { "Parameter", {
          { "addr", 0x0000010E }, { "size", 1 }, { "desc", "WMT4 Wave Random Pan Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000010F }, { "size", 1 }, { "desc", "WMT4 Wave Alternate Pan Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "ControlSwitch" },
        }},
        { "Parameter", {
          { "addr", 0x00000110 }, { "size", 1 }, { "desc", "WMT4 Wave Level" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000111 }, { "size", 1 }, { "desc", "WMT4 Velocity Range Lower" },
          { "min", 1 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000112 }, { "size", 1 }, { "desc", "WMT4 Velocity Range Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000113 }, { "size", 1 }, { "desc", "WMT4 Velocity Fade Width Lower" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000114 }, { "size", 1 }, { "desc", "WMT4 Velocity Fade Width Upper" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000115 }, { "size", 1 }, { "desc", "Pitch Env Depth" },
          { "min", 52 }, { "max", 76 }, { "type", "int" },
          { "display_min", -12 }, { "display_max", 12 },
        }},
        { "Parameter", {
          { "addr", 0x00000116 }, { "size", 1 }, { "desc", "Pitch Env Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000117 }, { "size", 1 }, { "desc", "Pitch Env Time 1 Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000118 }, { "size", 1 }, { "desc", "Pitch Env Time 4 Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000119 }, { "last_addr", 0x0000011C }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 4 },
          { "desc", "Pitch Env Time" }, { "fmt", "Pitch Env Time %d" },
          { "template", "MidiByte" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x0000011D }, { "last_addr", 0x00000121 }, { "size", 1 },
          { "first_index", 0 }, { "last_index", 4 },
          { "desc", "Pitch Env Level" }, { "fmt", "Pitch Env Level %d" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000122 }, { "size", 1 }, { "desc", "TVF Filter Type" },
          { "min", 0 }, { "max", 6 },
          { "type", "choice" }, { "choice_list", "FilterType" },
        }},
        { "Parameter", {
          { "addr", 0x00000123 }, { "size", 1 }, { "desc", "TVF Cutoff Frequency" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x00000124 }, { "size", 1 }, { "desc", "TVF Cutoff Velocity Curve" },
          { "min", 0 }, { "max", 7 },
          { "type", "choice" }, { "choice_list", "VelocityCurve" },
        }},
        { "Parameter", {
          { "addr", 0x00000125 }, { "size", 1 }, { "desc", "TVF Cutoff Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000126 }, { "size", 1 }, { "desc", "TVF Resonance" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x00000127 }, { "size", 1 }, { "desc", "TVF Resonance Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000128 }, { "size", 1 }, { "desc", "TVF Env Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000129 }, { "size", 1 }, { "desc", "TVF Env Velocity Curve Type" },
          { "min", 0 }, { "max", 7 },
          { "type", "choice" }, { "choice_list", "VelocityCurve" },
        }},
        { "Parameter", {
          { "addr", 0x0000012A }, { "size", 1 }, { "desc", "TVF Env Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000012B }, { "size", 1 }, { "desc", "TVF Env Time 1 Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000012C }, { "size", 1 }, { "desc", "TVF Env Time 4 Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x0000012D }, { "last_addr", 0x00000130 }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 4 },
          { "desc", "TVF Env Time" }, { "fmt", "TVF Env Time %d" },
          { "template", "MidiByte" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000131 }, { "last_addr", 0x00000135 }, { "size", 1 },
          { "first_index", 0 }, { "last_index", 4 },
          { "desc", "TVF Env Level" }, { "fmt", "TVF Env Level %d" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000136 }, { "size", 1 }, { "desc", "TVA Level Velocity Curve" },
          { "min", 0 }, { "max", 7 },
          { "type", "choice" }, { "choice_list", "VelocityCurve" },
        }},
        { "Parameter", {
          { "addr", 0x00000137 }, { "size", 1 }, { "desc", "TVA Level Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000138 }, { "size", 1 }, { "desc", "TVA Env Time 1 Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000139 }, { "size", 1 }, { "desc", "TVA Env Time 4 Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x0000013E }, { "last_addr", 0x00000140 }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 4 },
          { "desc", "TVA Env Time" }, { "fmt", "TVA Env Time %d" },
          { "template", "MidiByte" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000131 }, { "last_addr", 0x00000135 }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 3 },
          { "desc", "TVA Env Level" }, { "fmt", "TVA Env Level %d" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000141 }, { "size", 1 }, { "desc", "One Shot mode" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::pcmDrumKitCommon2Template() {
  return
    { "Template", {{ "name", "PCM Drum Kit Common 2" }},
      {
        { "Parameter", {
          { "addr", 0x00000010 }, { "size", 2 }, { "desc", "Phrase Number" },
          { "min", 0 }, { "max", 255 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x00000031 }, { "size", 1 }, { "desc", "TFX Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" }
        }},
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::superNATURALSynthToneCommonTemplate() {
  return
    { "Template", {{ "name", "SuperNATURAL Synth Tone Common" }},
      {
        { "TextParameter", {
          { "first_addr", 0x00000000 }, { "last_addr", 0x0000000B }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 12 },
          { "desc", "Tone Name" }, { "fmt", "Tone Name %d" },
          { "type", "ascii" },
        }},
        { "Parameter", {
          { "addr", 0x0000000C }, { "size", 1 }, { "desc", "Tone Level" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000012 }, { "size", 1 }, { "desc", "Portamento Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},                        
        { "Parameter", {
          { "addr", 0x00000013 }, { "size", 1 }, { "desc", "Portamento Time" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000014 }, { "size", 1 }, { "desc", "Mono Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},                        
        { "Parameter", {
          { "addr", 0x00000015 }, { "size", 1 }, { "desc", "Octave Shift" },
          { "min", 61 }, { "max", 67 }, { "type", "int" },
          { "display_min", -3 }, { "display_max", 3 },
        }},
        { "Parameter", {
          { "addr", 0x00000016 }, { "size", 1 }, { "desc", "Pitch Bend Range Up" },
          { "min", 0 }, { "max", 24 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000017 }, { "size", 1 }, { "desc", "Pitch Bend Range Down" },
          { "min", 0 }, { "max", 24 }, { "type", "int" }
        }},
        { "Parameter", {
          { "addr", 0x00000019 }, { "size", 1 }, { "desc", "Partial1 Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},                        
        { "Parameter", {
          { "addr", 0x0000001A }, { "size", 1 }, { "desc", "Partial1 Select" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},                        
        { "Parameter", {
          { "addr", 0x0000001B }, { "size", 1 }, { "desc", "Partial2 Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},                        
        { "Parameter", {
          { "addr", 0x0000001C }, { "size", 1 }, { "desc", "Partial2 Select" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},                        
        { "Parameter", {
          { "addr", 0x0000001D }, { "size", 1 }, { "desc", "Partial3 Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},                        
        { "Parameter", {
          { "addr", 0x0000001E }, { "size", 1 }, { "desc", "Partial3 Select" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},                        
        { "Parameter", {
          { "addr", 0x0000001F }, { "size", 1 }, { "desc", "RING Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "RingSwitch" },
        }},                        
        { "Parameter", {
          { "addr", 0x00000020 }, { "size", 1 }, { "desc", "TFX Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" }
        }},
        { "Parameter", {
          { "addr", 0x00000021 }, { "size", 1 }, { "desc", "Unison Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" }
        }},
        { "Parameter", {
          { "addr", 0x00000031 }, { "size", 1 }, { "desc", "Portamento Mode" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "PortamentoMode" },
        }},                        
        { "Parameter", {
          { "addr", 0x00000032 }, { "size", 1 }, { "desc", "Legato Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" }
        }},
        { "Parameter", {
          { "addr", 0x00000034 }, { "size", 1 }, { "desc", "Analog Feel" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000035 }, { "size", 1 }, { "desc", "Wave Shape" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000036 }, { "size", 1 }, { "desc", "Tone Category" },
          { "min", 0 }, { "max", 34 },  // 0-127 but only 35 categories
          { "type", "choice" }, { "choice_list", "ToneCategory" },
        }},
        { "Parameter", {
          { "addr", 0x00000037 }, { "size", 4 }, { "desc", "Phrase Number" },
          { "min", 0 }, { "max", 65535 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000003B }, { "size", 1 }, { "desc", "Phrase Octave Shift" },
          { "min", 61 }, { "max", 67 }, { "type", "int" },
          { "display_min", -3 }, { "display_max", 3 },
        }},
        { "Parameter", {
          { "addr", 0x0000001C }, { "size", 1 }, { "desc", "Unison Size" },
          { "min", 0 }, { "max", 3 }, { "type", "int" },
          { "display_min", 2 }, { "display_max", 8 },
        }},
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::superNATURALSynthTonePartialTemplate() {
  return
    { "Template", {{ "name", "SuperNATURAL Synth Tone Partial" }},
      {
        { "Parameter", {
          { "addr", 0x00000000 }, { "size", 1 }, { "desc", "OSC Wave" },
          { "min", 0 }, { "max", 7 },
          { "type", "choice" }, { "choice_list", "OscWaveform" },
        }},
        { "Parameter", {
          { "addr", 0x00000001 }, { "size", 1 }, { "desc", "OSC Wave Variation" },
          { "min", 0 }, { "max", 2 },
          { "type", "choice" }, { "choice_list", "ABC" },
        }},
        { "Parameter", {
          { "addr", 0x00000003 }, { "size", 1 }, { "desc", "OSC Pitch" },
          { "min", 40 }, { "max", 88 }, { "type", "int" },
          { "display_min", -24 }, { "display_max", 24 },
        }},
        { "Parameter", {
          { "addr", 0x00000004 }, { "size", 1 }, { "desc", "OSC Detune" },
          { "min", 14 }, { "max", 114 }, { "type", "int" },
          { "display_min", -50 }, { "display_max", 50 },
        }},
        { "Parameter", {
          { "addr", 0x00000005 }, { "size", 1 }, { "desc", "OSC Pulse Width Mod Depth" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000006 }, { "size", 1 }, { "desc", "OSC Pulse Width" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000007 }, { "size", 1 }, { "desc", "OSC Pitch Env Attack Time" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000008 }, { "size", 1 }, { "desc", "OSC Pitch Env Decay" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000009 }, { "size", 1 }, { "desc", "OSC Pitch Env Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000000A }, { "size", 1 }, { "desc", "FILTER Mode" },
          { "min", 0 }, { "max", 7 },
          { "type", "choice" }, { "choice_list", "FilterMode" },
        }},        
        { "Parameter", {
          { "addr", 0x0000000B }, { "size", 1 }, { "desc", "FILTER Slope" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "FilterSlope" },
        }},        
        { "Parameter", {
          { "addr", 0x0000000C }, { "size", 1 }, { "desc", "FILTER Cutoff" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000000D }, { "size", 1 }, { "desc", "FILTER Cutoff Keyfollow" },
          { "template", "KeyFollow" },
        }},
        { "Parameter", {
          { "addr", 0x0000000E }, { "size", 1 }, { "desc", "FILTER Env Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000000F }, { "size", 1 }, { "desc", "FILTER Resonance" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x00000010 }, { "size", 1 }, { "desc", "FILTER Env Attack Time" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x00000011 }, { "size", 1 }, { "desc", "FILTER Env Decay Time" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x00000012 }, { "size", 1 }, { "desc", "FILTER Env Sustain level" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x00000013 }, { "size", 1 }, { "desc", "FILTER Env Release Time" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x00000014 }, { "size", 1 }, { "desc", "FILTER Env Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000015 }, { "size", 1 }, { "desc", "AMP Level" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x00000016 }, { "size", 1 }, { "desc", "AMP Level Velocity Sens" },
          { "template", "SignedMidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x00000017 }, { "size", 1 }, { "desc", "AMP Env Attack Time" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x00000018 }, { "size", 1 }, { "desc", "AMP Env Decay Time" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x00000019 }, { "size", 1 }, { "desc", "AMP Env Sustain level" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x0000001A }, { "size", 1 }, { "desc", "AMP Env Release Time" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x0000001B }, { "size", 1 }, { "desc", "AMP Pan" },
          { "template", "Pan" },
        }},      
        { "Parameter", {
          { "addr", 0x0000001C }, { "size", 1 }, { "desc", "LFO Shape" },
          { "min", 0 }, { "max", 5 },
          { "type", "choice" }, { "choice_list", "LFOShape" }
        }},
        { "Parameter", {
          { "addr", 0x0000001D }, { "size", 1 }, { "desc", "LFO Rate" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x0000001E }, { "size", 1 }, { "desc", "LFO Tempo Sync Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x0000001F }, { "size", 1 }, { "desc", "LFO Tempo Sync Note" },
          { "min", 0 }, { "max", 19 },
          { "type", "choice" }, { "choice_list", "LFOTempoSync" }
        }},
        { "Parameter", {
          { "addr", 0x00000020 }, { "size", 1 }, { "desc", "LFO Fade Time" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x00000021 }, { "size", 1 }, { "desc", "LFO Key Trigger" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000022 }, { "size", 1 }, { "desc", "LFO Pitch Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000023 }, { "size", 1 }, { "desc", "LFO Filter Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000024 }, { "size", 1 }, { "desc", "LFO Amp Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000025 }, { "size", 1 }, { "desc", "LFO Pan Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000026 }, { "size", 1 }, { "desc", "Modulation LFO Shape" },
          { "min", 0 }, { "max", 5 },
          { "type", "choice" }, { "choice_list", "LFOShape" }
        }},
        { "Parameter", {
          { "addr", 0x00000027 }, { "size", 1 }, { "desc", "Modulation LFO Rate" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x00000028 }, { "size", 1 }, { "desc", "Modulation LFO Tempo Sync Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" },
        }},
        { "Parameter", {
          { "addr", 0x00000029 }, { "size", 1 }, { "desc", "Modulation LFO Tempo Sync Note" },
          { "min", 0 }, { "max", 19 },
          { "type", "choice" }, { "choice_list", "LFOTempoSync" }
        }},
        { "Parameter", {
          { "addr", 0x0000002A }, { "size", 1 }, { "desc", "OSC Pulse Width Shift" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x0000002C }, { "size", 1 }, { "desc", "Modulation LFO Pitch Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000002D }, { "size", 1 }, { "desc", "Modulation LFO Filter Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000002E }, { "size", 1 }, { "desc", "Modulation LFO Amp Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000002F }, { "size", 1 }, { "desc", "Modulation LFO Pan Depth" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000030 }, { "size", 1 }, { "desc", "Cutoff Aftertouch Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000031 }, { "size", 1 }, { "desc", "Level Aftertouch Sens" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000034 }, { "size", 1 }, { "desc", "Wave Gain" },
          { "min", 0 }, { "max", 3 },
          { "type", "choice" }, { "choice_list", "WaveGain" },
        }},
        { "Parameter", {
          { "addr", 0x00000035 }, { "size", 4 }, { "desc", "Wave Number" },
          { "template", "WaveNumber"}
        }},
        { "Parameter", {
          { "addr", 0x00000039 }, { "size", 1 }, { "desc", "HPF Cutoff" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x0000003A }, { "size", 1 }, { "desc", "Super Saw Detune" },
          { "template", "MidiByte" },
        }},        
        { "Parameter", {
          { "addr", 0x0000003B }, { "size", 1 }, { "desc", "Modulation LFO Rate Control" },
          { "template", "SignedMidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x0000003C }, { "size", 1 }, { "desc", "AMP Level Keyfollow" },
          { "template", "KeyFollow" },
        }},
      }
    };
}

inline ValueTree ParamTreeTemplateBuilder::superNATURALAcousticToneCommonTemplate() {
  return
    { "Template", {{ "name", "SuperNATURAL Acoustic Tone Common" }},
      {
        { "TextParameter", {
          { "first_addr", 0x00000000 }, { "last_addr", 0x0000000B }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 12 },
          { "desc", "Tone Name" }, { "fmt", "Tone Name %d" },
          { "type", "ascii" },
        }},
        { "Parameter", {
          { "addr", 0x00000010 }, { "size", 1 }, { "desc", "Tone Level" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000011 }, { "size", 1 }, { "desc", "Mono/Poly" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "MonoPoly" },
        }},
        { "Parameter", {
          { "addr", 0x00000012 }, { "size", 1 }, { "desc", "Portamento Time Offset" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000013 }, { "size", 1 }, { "desc", "Cutoff Offset" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000014 }, { "size", 1 }, { "desc", "Resonance Offset" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000015 }, { "size", 1 }, { "desc", "Attack Time Offset" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000016 }, { "size", 1 }, { "desc", "Release Time Offset" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000017 }, { "size", 1 }, { "desc", "Vibrato Rate" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000018 }, { "size", 1 }, { "desc", "Vibrato Depth" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x00000019 }, { "size", 1 }, { "desc", "Vibrato Delay" },
          { "min", 0 }, { "max", 127 }, { "type", "int" },
          { "display_min", -64 }, { "display_max", 63 },
        }},
        { "Parameter", {
          { "addr", 0x0000001A }, { "size", 1 }, { "desc", "Octave Shift" },
          { "template", "OctaveShift" },
        }},
        { "Parameter", {
          { "addr", 0x0000001B }, { "size", 1 }, { "desc", "Category" },
          { "min", 0 }, { "max", 34 },  // 0-127 but only 35 categories
          { "type", "choice" }, { "choice_list", "ToneCategory" },
        }},
        { "Parameter", {
          { "addr", 0x0000001C }, { "size", 2 }, { "desc", "Phrase Number" },
          { "min", 0 }, { "max", 255 }, { "type", "int" },
        }},
        { "Parameter", {
          { "addr", 0x0000001E }, { "size", 1 }, { "desc", "Phrase Octave Shift" },
          { "template", "OctaveShift" },
        }},
        { "Parameter", {
          { "addr", 0x0000001F }, { "size", 1 }, { "desc", "TFX Switch" },
          { "min", 0 }, { "max", 1 },
          { "type", "choice" }, { "choice_list", "OffOn" }
        }},
        { "Parameter", {
          { "addr", 0x00000020 }, { "size", 1 }, { "desc", "Inst Variation" },
          { "template", "MidiByte" },
        }},
        { "Parameter", {
          { "addr", 0x00000021 }, { "size", 1 }, { "desc", "Inst Number" },
          { "template", "MidiByte" },
        }},
        { "ParameterRange", {
          { "first_addr", 0x00000022 }, { "last_addr", 0x00000041 }, { "size", 1 },
          { "first_index", 1 }, { "last_index", 32 },
          { "desc", "Modify Parameter" }, { "fmt", "Modify Parameter %d" },
          { "template", "MidiByte" },
        }},
      }
    };
}
