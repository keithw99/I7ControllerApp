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
          { "addr", 0x00000003 }, { "size", 1 }, { "desc", "Ext Mid Gain" },
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
          { "type", "choice" }, { "choice_list", "VelocityCurve" },
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
          { "addr", 0x00000004 }, { "size", 1 }, { "desc", "Ext Mid Gain" },
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
