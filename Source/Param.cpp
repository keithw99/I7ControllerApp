/*
  ==============================================================================

    Param.cpp
    Created: 3 Feb 2020 11:09:41pm
    Author:  keith

  ==============================================================================
*/

#include <unordered_map>

#include "Param.h"

static const std::unordered_map<String, ParamType>
getParamTypeIndexMap() {
  std::unordered_map<String, ParamType> m = {
    {paramtype::int_type, ParamType::INT},
    {paramtype::float_type, ParamType::FLOAT},
    {paramtype::choice, ParamType::CHOICE},
    {paramtype::ascii, ParamType::ASCII},
    {paramtype::int_choice, ParamType::INT_CHOICE},
  };
  return m;
}

static const std::unordered_map<String, ParamTemplateType>
getParamTemplateMap() {
  std::unordered_map<String, ParamTemplateType> m = {
    {paramtemplate::MidiByte, ParamTemplateType::MIDI_BYTE},
    {paramtemplate::SignedMidiByte, ParamTemplateType::SIGNED_MIDI_BYTE},        
    {paramtemplate::Pan, ParamTemplateType::PAN},
    {paramtemplate::CoarseTune, ParamTemplateType::COARSE_TUNE},
    {paramtemplate::FineTune, ParamTemplateType::FINE_TUNE},
    {paramtemplate::OctaveShift, ParamTemplateType::OCTAVE_SHIFT},
    {paramtemplate::KeyFollow, ParamTemplateType::KEYFOLLOW},
    {paramtemplate::WaveNumber, ParamTemplateType::WAVE_NUMBER},
  };
  return m;
}

ParamType GetParamType(String name) {
  const auto& m = getParamTypeIndexMap();
  const auto found = m.find(name);
  if (found == m.end()) {
    // TODO: Throw error
    DBG("ERROR: invalid ParamType: " << name);
    return ParamType::INVALID;
  }
  return found->second;
}

ParamTemplateType GetParamTemplateType(String name) {
  const auto& m = getParamTemplateMap();
  const auto found = m.find(name);
  if (found == m.end()) {
    // TODO: Throw error
    DBG("ERROR: invalid ParamTemplateType: " << name);
    return ParamTemplateType::INVALID;
  }
  return found->second;
}

LinearIntRange::LinearIntRange(int size) {
  min_ = 0;
  max_ = size - 1;
  step_ = 1;
}

LinearIntRange::LinearIntRange(const LinearIntRange& range) {
  min_ = range.min_;
  max_ = range.max_;
  step_ = range.step_;
}

int LinearIntRange::getSize() const {
  return max_ - min_ + 1;
}

/*
LinearIntRange LinearIntRange::getNormalizedRange() const {
  return LinearIntRange(0, getSize() / step_ + 1, 1);
}
*/

int RangedParamDecoder::getValue(const uint8* data) {
  return decoder_->getRawInt(data);
}

int RangedParamDecoder::getMin() {
  return base_range_->getMin();
}

int RangedParamDecoder::getMax() {
  return base_range_->getMax();
}

int RangedParamDecoder::getSize() {
  return decoder_->getRawDataSize();
}

int RangedParamDecoder::getBytes(const int value, uint8* buf) {
  return decoder_->getRawData(value, buf);
}

String IntParamTranslator::getDisplayValue(int normalized_value) {
  return String(getDisplayInt(normalized_value));
}

int IntParamTranslator::getDisplayInt(const int normalized_value) {
  return normalized_value * skew_ + offset_;
}

int IntParamTranslator::getNormalizedInt(const int display_value) {
  return (display_value - offset_) / skew_;
}

int IntParamTranslator::getOffset() { return offset_; }

int IntParamTranslator::getSkew() { return skew_; }

int ChoiceParamTranslator::getChoiceIndex(const int normalized_value) {
  return normalized_value - getOffset();
}

int ChoiceParamTranslator::getChoiceIndexFromDisplayInt(const int display_value) {
  return getChoiceIndex(getNormalizedInt(display_value));
}

String ChoiceParamTranslator::getDisplayValue(const int normalized_value) {
  if (choices_ == nullptr) {
    DBG("ERROR: choices_ is Null!!");
    return "";
  }
  return (*choices_)[getChoiceIndex(normalized_value)];
}

String IntChoiceParamTranslator::getDisplayValue(const int normalized_value) {
  const auto found = choices_->find(normalized_value);
  if (found != choices_->end()) {
    return found->second;
  }
  return String(getDisplayInt(normalized_value));
}

String FloatParamTranslator::getDisplayValue(const int normalized_value) {
  return String(getDisplayFloat(normalized_value), decimal_places_);
}

int FloatParamTranslator::getNormalizedInt(const float display_value) {
  return display_offset_ + skew_ * (display_value - base_offset_);
}

float FloatParamTranslator::getDisplayFloat(const int normalized_value) {
  return display_offset_ + skew_ * (normalized_value - base_offset_);
}

float FloatParamTranslator::getBaseOffset() {
  return base_offset_;
}

float FloatParamTranslator::getDisplayOffset() {
  return display_offset_;
}

float FloatParamTranslator::getSkew() {
  return skew_;
}

String AsciiParamTranslator::getDisplayValue(const int int_value) {
  return String((char*)&int_value, 1);
}

ParamProperties ParamProperties::fromTemplate(const String& param_template) {
  ParamTemplateType pt_type = GetParamTemplateType(param_template);
  switch (pt_type) {
    case ParamTemplateType::MIDI_BYTE:
      return intParam(1, 0, 127);
    case ParamTemplateType::SIGNED_MIDI_BYTE:
      return intParam(1, 1, 127, -63, 63);
    case ParamTemplateType::PAN:
      return intParam(1, 0, 127, -64, 63);
    case ParamTemplateType::COARSE_TUNE:
      return intParam(1, 16, 112, -48, 48);
    case ParamTemplateType::FINE_TUNE:
      return intParam(1, 14, 114, -50, 50);
    case ParamTemplateType::OCTAVE_SHIFT:
      return intParam(1, 61, 67, -3, 3);
    case ParamTemplateType::KEYFOLLOW:
      return intParam(1, 54, 74, -100, 100);
    case ParamTemplateType::WAVE_NUMBER:
      {
        std::unordered_map<int, String> m = {
          {0, "OFF"},
        };
        return intChoiceParam(
          4, 0, 16384,
          std::make_shared<std::unordered_map<int, String>>(m)
        );
      }
    default:
      DBG("ERROR: invalid ParamTemplateType: " << int(pt_type));
      return ParamProperties();
  };
}

ParamInfo ParamInfo::makeBaseParamInfo(const ParamProperties& props) {
  ParamInfo pinfo;
  pinfo.type_ = props.param_type;
  pinfo.decoder_ = std::make_shared<RangedParamDecoder>(
    RangedParamDecoder::createDecoder(props.size, props.min, props.max));
  return pinfo;
}

void ParamInfo::makeIntParamInfo(const ParamProperties& props, ParamInfo* pinfo) {
  pinfo->translator_ = std::make_shared<IntParamTranslator>(
    props.min, props.max, props.display_min, props.display_max, props.step);
}

void ParamInfo::makeFloatParamInfo(const ParamProperties& props, ParamInfo* pinfo) {
  pinfo->translator_ = std::make_shared<FloatParamTranslator>(
    props.min, props.max, props.display_float_min, props.display_float_max, props.decimal_places);
}

void ParamInfo::makeChoiceParamInfo(const ParamProperties& props, ParamInfo* pinfo) {
  pinfo->translator_ = std::make_shared<ChoiceParamTranslator>(props.choices);
}

void ParamInfo::makeAsciiParamInfo(const ParamProperties& props, ParamInfo* pinfo) {
  pinfo->translator_ = std::make_shared<AsciiParamTranslator>();
}

void ParamInfo::makeIntChoiceParamInfo(const ParamProperties& props, ParamInfo* pinfo) {
  pinfo->translator_ = std::make_shared<IntChoiceParamTranslator>(props.int_choices);
}

ParamInfo ParamInfo::makeParamInfo(const ParamProperties& props) {
  ParamInfo pinfo = makeBaseParamInfo(props);
  switch (pinfo.type_) {
    case ParamType::INT:
      makeIntParamInfo(props, &pinfo);
      break;
    case ParamType::CHOICE:
      makeChoiceParamInfo(props, &pinfo);
      break;
    case ParamType::FLOAT:
      makeFloatParamInfo(props, &pinfo);
      break;
    case ParamType::ASCII:
      makeAsciiParamInfo(props, &pinfo);
      break;
    case ParamType::INT_CHOICE:
      makeIntChoiceParamInfo(props, &pinfo);
      break;
    default:
      DBG("ERROR: Adding parameter type Not yet supported");
      return ParamInfo(ParamType::INVALID, nullptr, nullptr);
  }
  return pinfo;
}

String ParamInfo::getDisplayValue(const uint8* bytes) {
  return translator_->getDisplayValue(decoder_->getValue(bytes));
}

String ParamInfo::getDisplayValue(const int normalized_value) {
  return translator_->getDisplayValue(normalized_value);
}

int ParamInfo::getNormalizedInt(const uint8* bytes) {
  int val = translator_->getNormalizedInt(decoder_->getValue(bytes));
  //DBG("val = " + val);
  return val;
}

int ParamInfo::getNormalizedInt(const String& display_value) {
  return translator_->getNormalizedInt(display_value.getFloatValue());
}

int ParamInfo::getBytes(const String& display_value, uint8* buf) {
  return decoder_->getBytes(
    translator_->getNormalizedInt(display_value.getIntValue()), buf);
}

int ParamInfo::getBytes(int normalized_value, uint8* buf) {
  return decoder_->getBytes(normalized_value, buf);
}

int ParamInfo::getByteSize() {
  return decoder_->getSize();
}

String ParamUpdate::pathString() {
  String pstr = "/";
  for (const ParamPathElement& pe : path) {
    if (pe.index > -1) {
      pstr += "/" + pe.node_id + "[" + String(pe.index) + "]";
    } else {
      pstr += "/" + pe.node_id;
    }
  }
  return pstr;
}

String ParamUpdate::toString() {
  return pathString() + " -> " + info->getDisplayValue(value);
}