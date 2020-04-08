/*
  ==============================================================================

    ParamBase.h
    Created: 5 Feb 2020 6:55:18pm
    Author:  keith

  ==============================================================================
*/

#pragma once

#include <cstdint>
#include <iostream>

typedef uint8_t uint8;
typedef uint32_t uint32;

constexpr uint8 BITMASK[] =
  {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F};


inline uint32 Get7BitAddress(uint32 padded_addr) {
  return padded_addr & 0x7F |
         (padded_addr >> 8 & 0x7F) << 7 |
         (padded_addr >> 16 & 0x7F) << 14 |
         (padded_addr >> 24 & 0x7F) << 21;
}

inline uint32 Get8BitAddress(uint32 sb_addr) {
 return sb_addr & 0x7F |
         (sb_addr >> 7 & 0x7F) << 8 |
         (sb_addr >> 14 & 0x7F) << 16 |
         (sb_addr >> 21 & 0x7F) << 24;
}

inline uint32 Pack8Bit(const uint8* data, int size) {
  uint32 val = 0;
  for (int i = size; i > 0; --i) {
    uint32 v = static_cast<uint32>((data[i-1]) & 0xFF);
    val |= static_cast<uint32>((data[i - 1]) & 0x7F) << (size - i) * 8;
  }
  return val;
}

inline uint32 Pack7Bit(const uint8* data, int size) {
  uint32 val = 0;
  for (int i = size; i > 0; --i) {
    uint32 v = static_cast<uint32>((data[i-1]) & 0xFF);
    val |= static_cast<uint32>((data[i - 1]) & 0x7F) << (size - i) * 7;
  }
  return val;
}

inline uint32 Pack4Bit(const uint8* data, int size) {
  uint32 val = 0;
  for (int i = size; i > 0; --i) {
    uint32 v = static_cast<uint32>((data[i-1]) & 0xFF);
    val |= static_cast<uint32>((data[i - 1]) & 0x7F) << (size - i) * 4;
  }
  return val;
}

inline uint32 PackWithBitmask(const uint8* data, int size, const uint8* bitlen) {
  uint32 val = 0;
  int bit_pos = 0;
  for (int i = size; i >= 0; --i) {
    val |= static_cast<uint32>(data[i] & BITMASK[bitlen[i]]) << bit_pos;
    bit_pos += bitlen[i];
  }
}

inline int Unpack8Bit(uint32 value, uint8* buf, int size) {
  for (int i = size; i > 0; --i) {
    buf[i - 1] = static_cast<uint8>(value >> (size - i) * 8) & 0x7F;
  }
  return size;
}

inline int Unpack7Bit(uint32 value, uint8* buf, int size) {
  for (int i = size; i > 0; --i) {
    buf[i - 1] = static_cast<uint8>(value >> (size - i) * 7) & 0x7F;
  }
  return size;
}

inline int Unpack4Bit(uint32 value, uint8* buf, int size) {
  for (int i = size; i > 0; --i) {
    buf[i - 1] = static_cast<uint8>(value >> (size - i) * 4) & 0x0F;
  }
  return size;
}

inline int UnpackWithBitmask(uint32 value, uint8* buf, int size, const uint8* bitlen) {
  int bit_pos = 0;
  for (int i = size - 1; i >= 0; ++i) {
    buf[i] = static_cast<uint8>(value >> bit_pos) & BITMASK[bitlen[i]];
    bit_pos += bitlen[i];
  }
  return size;
}

inline int CopyBytes(const uint8* src, uint8* dst, int size,
    int max_size = 0, int max_value = 0) {
  if (max_size && size > max_size) {
    // TODO: Throw error.
    return 0;
  }
  int count = 0;
  for (int i = 0; i < size; ++i) {
    if (max_value && src[i] > max_value) {
      dst[i] = src[i];
      count += 1;
    }
  }
  return count;
}

constexpr int NibbleToBit[9] = {0, 3, 7, 10, 14, 17, 21, 24, 28};
