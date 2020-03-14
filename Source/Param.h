/*
  ==============================================================================

    Param.h
    Created: 3 Feb 2020 11:09:41pm
    Author:  keith

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "ParamBase.h"
//#include "ParamTemplate.h"
#include "Constants.h"

class LinearIntRange {
 public:
  int min_;
  int max_;
  int step_;

  LinearIntRange(int first, int last, int step = 1) :
    min_(first), max_(last), step_(step) {}
  LinearIntRange(int size);
  LinearIntRange(const LinearIntRange& range);

  inline int getMin() const { return min_; }
  inline int getMax() const { return max_; }
  inline int getStep() const { return step_; }
  int getSize() const;
  LinearIntRange getNormalizedRange() const;

};

inline LinearIntRange LinearOffsetRange(int size, int offset, int step = 1) {
  return LinearIntRange(offset, offset + size, step);
}

inline LinearIntRange MidiByteRange(int offset = 0) {
  return LinearOffsetRange(128, offset);
}
  
class ParamValueDecoder {
 public:

  ParamValueDecoder(int size) : size_(size) {}

  int getPaddedInt(const uint8* data) {
    return Pack8Bit(data, size_);
  }

  int getRawInt(const uint8* data) {
    //return PackWithBitmask(data, size_, bitlength_);
    return size_ > 1 ? Pack4Bit(data, size_) : Pack8Bit(data, size_);
  }

  int getBitLength() {
    int bits_per_byte = (size_ > 1) ? 4 : 7;
    return size_ * bits_per_byte;
  }

  // Gets the possible number of values based on bits with data.
  int getRangeSize() {
    return 1 << getBitLength();
  }

  int getRawData(const int value, uint8* buf) {
    //return UnpackWithBitmask(value, buf, size_, bitlength_);
    return size_ > 1 ? Unpack4Bit(value, buf, size_) : Unpack8Bit(value, buf, size_);
  }

  int getRawDataSize() { return size_; }

 private:
  //uint8 data_[4] = {0, 0, 0, 0}; // 4 bytes that store the data.
  uint8 size_;  // # actual bytes that contain data.
  //uint8 bitlength_[4] = {7, 7, 7, 7};  // number of bits per byte that contain data.
};

inline ParamValueDecoder MidiByteDecoder() {
  return ParamValueDecoder(1);
}

class RangedParamDecoder {
 public:
  static RangedParamDecoder MidiByteParam(const int offset = 0) {
    return RangedParamDecoder(
      std::make_shared<ParamValueDecoder>(MidiByteDecoder()),
      std::make_shared<LinearIntRange>(MidiByteRange(offset)));
  }

  static RangedParamDecoder createDecoder(int size,
                                          int first,
                                          int last) {
                                          //int step = 1) {
                                          //uint8* bitlength = nullptr) {
      return RangedParamDecoder(
      std::make_shared<ParamValueDecoder>(size), //, bitlength),
      std::make_shared<LinearIntRange>(first, last, 1));
  }

  int getValue(const uint8* data);
  int getSize();  // in (padded) bytes.
  int getBytes(const int value, uint8* buf);
  int getMin();
  int getMax();

 private:
  RangedParamDecoder(std::shared_ptr<ParamValueDecoder> decoder,
                     std::shared_ptr<LinearIntRange> range) :
      decoder_(decoder), base_range_(range) {}

  std::shared_ptr<LinearIntRange> base_range_;
  std::shared_ptr<ParamValueDecoder> decoder_;
};

class ParamTranslator {
 public:
  ParamTranslator(){}
  virtual ~ParamTranslator() {}

  virtual String getDisplayValue(int int_value) = 0;
  virtual int getNormalizedInt(const int display_value) { return 0; }
  //virtual int getDisplayInt(const int normalized_value) = 0;
};

class IntParamTranslator : public ParamTranslator {
  public:
   IntParamTranslator() : offset_(0), skew_(1) {}
   IntParamTranslator(int offset, int skew) :
    offset_(offset), skew_(skew) {}
   IntParamTranslator(const LinearIntRange& base, const LinearIntRange& display) :
    offset_(display.getMin() - base.getMin()), skew_(display.getStep() / base.getStep()) {}
   IntParamTranslator(int base_first, int base_last,
                      int display_first, int display_last,
                      int step = 1) :
    offset_(display_first - base_first),
    skew_((display_last - display_first) / (base_last - base_first)) {}
   ~IntParamTranslator() {}

   String getDisplayValue(const int int_value) override;
   int getNormalizedInt(const int display_value) override;
   int getDisplayInt(const int normalized_value);
   int getOffset();
   int getSkew();

  private:
   int offset_;
   int skew_;
};

class AsciiParamTranslator : public ParamTranslator {
 public:
  AsciiParamTranslator() {}
  ~AsciiParamTranslator() {}

  String getDisplayValue(const int int_value) override;
  int getNormalizedInt(const int display_value) { return display_value; }
};

class FloatParamTranslator : public ParamTranslator {
  public:
   FloatParamTranslator(int min, int max,
                        float display_min, float display_max,
                        int decimal_places) :
    base_offset_(min),
    display_offset_(display_min),
    skew_((display_max - display_min) / float(max - min)),
    decimal_places_(decimal_places) {}

   ~FloatParamTranslator() {}
   
   String getDisplayValue(const int normalized_value) override;
   int getNormalizedInt(const float display_value);

   float getDisplayFloat(const int normalized_value);
   float getBaseOffset();
   float getDisplayOffset();
   float getSkew();
   
  private:
   int base_offset_;
   float display_offset_;
   float skew_;
   int decimal_places_;
};

class ChoiceParamTranslator : public IntParamTranslator {
 public:
  ChoiceParamTranslator(const std::shared_ptr<StringArray> choices) : choices_(choices) {}

  String getDisplayValue(const int normalized_value) override;
  int getChoiceIndex(const int normalized_value);
  int getChoiceIndexFromDisplayInt(const int display_value);
  //void appendChoice(const String& choice_name);

 private:
  std::shared_ptr<StringArray> choices_ = nullptr;
};

enum class ParamType {INT, FLOAT, CHOICE, ASCII, INVALID};
ParamType GetParamType(String name);

enum class ParamTemplateType {
  MIDI_BYTE, SIGNED_MIDI_BYTE, PAN, COARSE_TUNE, FINE_TUNE, OCTAVE_SHIFT,
  KEYFOLLOW, INVALID
};
ParamTemplateType GetParamTemplateType(String name);

// Convenience class for initializing ParamInfo.
struct ParamProperties {
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

  static ParamProperties fromTemplate(const String& param_template);
  static ParamProperties intParam(int size, int min, int max) {
    return ParamProperties(ParamType::INT, size, min, max);
  }
  static ParamProperties intParam(int size, int min, int max,
                                  int display_min, int display_max) {
    ParamProperties props = intParam(size, min, max);
    props.display_min = display_min;
    props.display_max = display_max;
    return props;
  }
  //static ParamProperties midiByte() { return intParam(1, 0, 127); }

  inline ParamProperties() {}
  inline ParamProperties(ParamType param_type, int size, int min, int max) :
    param_type(param_type), size(size), min(min), max(max),
    display_min(min), display_max(max) {}
};

class ParamInfo {
 public:
  ParamInfo() {}
  ParamInfo(ParamType param_type,
          std::shared_ptr<RangedParamDecoder> decoder,
          std::shared_ptr<ParamTranslator> translator) :
    type_(param_type),decoder_(decoder), translator_(translator) {}

  static ParamInfo makeParamInfo(const ParamProperties& props);

  String getDisplayValue(const uint8* bytes);
  String getDisplayValue(int normalized_value);
  int getBytes(const String& display_value, uint8* buf);
  int getBytes(int normalized_value, uint8* buf);
  int getByteSize();
  int getNormalizedInt(const uint8* bytes);
  int getNormalizedInt(const String& display_value);
  
  inline ParamType getType() { return type_; }

 private:
  static ParamInfo makeBaseParamInfo(const ParamProperties& props);
  static void makeIntParamInfo(const ParamProperties& props, ParamInfo* pinfo);
  static void makeFloatParamInfo(const ParamProperties& props, ParamInfo* pinfo);
  static void makeChoiceParamInfo(const ParamProperties& props, ParamInfo* pinfo);
  static void makeAsciiParamInfo(const ParamProperties& props, ParamInfo* pinfo);

  ParamType type_;
  std::shared_ptr<RangedParamDecoder> decoder_ = nullptr;
  std::shared_ptr<ParamTranslator> translator_ = nullptr;
};

struct ParamPathElement {
  Identifier node_id;
  int index = -1;
};

typedef std::vector<ParamPathElement> ParamPath;

struct ParamUpdate {
  ParamPath path;
  int value;
  std::shared_ptr<ParamInfo> info = nullptr;

  String toString();
  String pathString();
};