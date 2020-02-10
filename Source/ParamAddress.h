/*
  ==============================================================================

    ParamAddress.h
    Created: 3 Feb 2020 10:13:14pm
    Author:  keith

  ==============================================================================
*/

#pragma once

#include <vector>
#include <iostream>

#include "ParamBase.h"

struct ParamAddr {
  uint32 address = 0;
  uint8 len;  // length in nibbles.

  ParamAddr() {}
  ParamAddr(const ParamAddr& other) : address(other.address), len(other.len) {}
  ParamAddr(uint32 address, uint8 len) :
    address(address), len(len) {}

  ParamAddr(uint8* bytes, uint8 len) : len(len) {
    for (int i = 0; i < len / 2; ++i) {
      int shift = 24 - i * 8;
      address |= static_cast<uint32>((bytes[i] & 0x7F)) << shift;
    }
  }

  ParamAddr(uint8* bytes) : ParamAddr(bytes, 8) {}
  
  ParamAddr operator+(const ParamAddr& other) const {
    ParamAddr sum(*this);
    sum.address += other.address;
    sum.len = other.len;
    return sum;
  }

  ParamAddr operator+=(const int inc) {
     address += inc;
     return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const ParamAddr& pa) {
    return os << std::hex << int(pa.address) << "/" << std::dec << int(pa.len);
  }
};

inline ParamAddr ZeroAddr() {
  return ParamAddr(uint32(0), 0);
}

struct ParamAddrRange {
  uint32 base_address;
  uint8 prefixlen;
  uint8 start_index;
  uint8 count;
  uint32 step_offset;

  ParamAddrRange() {}
  ParamAddrRange(const ParamAddrRange& other) :
    base_address(other.base_address),
    prefixlen(other.prefixlen),
    start_index(other.start_index),
    count(other.count),
    step_offset(other.step_offset) {}

  ParamAddrRange(ParamAddr base, uint32 last_address,
      uint8 start_index, uint8 last_index) :
      base_address(base.address), prefixlen(base.len),
      start_index(start_index) {
    
    count = last_index - start_index + 1;

    uint32 sb_base = Get7BitAddress(base_address);
    uint32 sb_last = Get7BitAddress(last_address);
    
    int sb_prefixlen = NibbleToBit[prefixlen];
    int step_shift = 28 - sb_prefixlen;
    
    uint32 shifted_base = sb_base >> step_shift;
    uint32 shifted_last = sb_last >> step_shift;
    
    uint32 normalized_difference = shifted_last - shifted_base;
    
    uint32 normalized_step = normalized_difference / (count - 1);
    step_offset = normalized_step << step_shift;
  }

  ParamAddrRange operator+(const ParamAddr& offset) const {
    ParamAddrRange shifted(*this);
    shifted.base_address += offset.address;
    return shifted;
  }

  ParamAddr GetBaseAddr() const {
    return ParamAddr(base_address, prefixlen);
  }

  std::vector<ParamAddr> GetAddresses() const {
    std::vector<ParamAddr> addrs;
    uint32 sb_base_addr = Get7BitAddress(base_address);
    for (int i = 0; i < count; ++i) {
      addrs.push_back(ParamAddr(
        Get8BitAddress(sb_base_addr + (step_offset * i)), prefixlen));
    }
    return addrs;
  }

};
