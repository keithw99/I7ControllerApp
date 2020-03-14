/*
  ==============================================================================

    ParamTemplate.h
    Created: 14 Feb 2020 7:08:47pm
    Author:  keith

  ==============================================================================
*/

#pragma once

#include "Constants.h"

enum class ParamType {INT, FLOAT, CHOICE, ASCII, INVALID};

enum class ParamTemplateType {MIDI_BYTE, INVALID};

struct ParamTemplateBase {
  ParamType param_type;
  int size;
  int min;
  int max;
  int step = 1;
  int display_min = min;
  int display_max = max;
  float display_float_min = float(min);  // float params only.
  float display_float_max = float(max);  // float params only.
  int decimal_places = 1;  // float params.only
  std::shared_ptr<StringArray> choices;  // choice params only.

  ParamTemplateBase(ParamType param_type, int size, int min, int max) :
    param_type(param_type), size(size), min(min), max(max),
    display_min(min), display_max(max) {}
};

struct MidiByteTemplate : ParamTemplateBase {
  MidiByteTemplate() : ParamTemplateBase(ParamType::INT, 1, 0, 127) {}
};
