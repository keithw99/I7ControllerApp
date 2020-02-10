/*
  ==============================================================================

    ParamTreeTest.h
    Created: 28 Jan 2020 10:32:21pm
    Author:  keith

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "ParamTree.h"
#include "Param.h"

class PTreeTest : public UnitTest {
  public:
  PTreeTest() : UnitTest("ParamTree testing") {}

  void runTest() override {
    beginTest("PTree Construction");
    PTree ptree;

    beginTest("ParamAddr Construction");
    uint8 addr1[4] = {0x12, 0x34, 0x56, 0x78};
    ParamAddr paddr1(addr1);

    uint32 expected_addr1 = 0x12345678;
    expectEquals(int(paddr1.address), int(expected_addr1));

    // Construct a ParamAddr with specified prefix length.
    uint8 addr2[4] = {0x01, 0x00, 0x00, 0x00};
    ParamAddr setup_addr(addr2, 2);
    expectEquals(int(setup_addr.len), 2);

    beginTest("NodeInfo Construction");
    NodeInfo setup_info(NodeType::PATH, "Setup");

    beginTest("ParamTree Insert");
    ptree.Insert(setup_addr, setup_info);
    expect(ptree.HasData(), "ptree root should not be null");
    expectEquals(int(setup_addr.address), int(0x01000000));

    beginTest("ParamTree Lookup");
    NodeInfo found = ptree.Find(setup_addr);
    expectEquals(found.getDescription().toString(), String("Setup"));

    beginTest("Get7Bit Test");
    expectEquals(int(Get7BitAddress(0x11)), int(0x11));
    expectEquals(int(Get8BitAddress(0x11)), int(0x11));
    expectEquals(int(Get7BitAddress(0x1111)), int(0x0891));
    expectEquals(int(Get8BitAddress(0x0891)), int(0x1111));
    
    beginTest("ParamAddrRange Construction");
    uint32 tone_base_addr = 0x19000000;
    ParamAddr tone_base(tone_base_addr, 3);
    ParamAddrRange tone_range(tone_base, uint32(0x1C600000), 1, 16);
    auto tone_addresses = tone_range.GetAddresses();
    expectEquals(int(tone_addresses[2].address), int(0x19400000));
    
    beginTest("ParamTree InsertRange");
    String desc = "Temporary Tone";
    String fmt = "Temporary Tone (Part %d)";
    ptree.InsertRange(tone_range, NodeType::PATH, desc, fmt);

    NodeInfo found_tone = ptree.Find(ParamAddr(0x19200000, 3));
    expectEquals(found_tone.getDescription().toString(), String("Temporary Tone (Part 2)"));
    expectEquals(found_tone.getBaseDescription().toString(), String("Temporary Tone"));

    beginTest("NodeInfo permanence");
    ptree.Reset();
    expectEquals(found_tone.getDescription().toString(), String("Temporary Tone (Part 2)"));
    expectEquals(found_tone.getBaseDescription().toString(), String("Temporary Tone"));

    beginTest("ParamTree InsertOffset");
    ptree.Insert(setup_addr, setup_info);
    ptree.InsertOffset(setup_addr, ParamAddr(uint32(0x00000000), 8), NodeInfo(NodeType::PARAM, "Sound Mode"));
    NodeInfo found_sm = ptree.Find(ParamAddr(uint32(0x01000000), 8));
    expectEquals(found_sm.getDescription().toString(), String("Sound Mode"));
    NodeInfo found_setup = ptree.Find(setup_addr);
    expectEquals(found_setup.getDescription().toString(), String("Setup"));

    beginTest("ParamValueStore construction");
    //ParamValueStore mbs = ParamValueStore::MidiByteStore();
    //LinearIntRange mbr = MidiByteRange();
    //RangedParamValue rpv(mbs, mbr);
    RangedParamDecoder b = RangedParamDecoder::MidiByteParam();

    beginTest("ParamTreeTemplateBuilder::BuildTemplate");
    ValueTree paramTemplate = ParamTreeTemplateBuilder::getTemplate();
    ValueTree setupTree = paramTemplate.getChildWithProperty("desc", "Setup");
    expect(setupTree.isValid());
    expectEquals(int(setupTree.getProperty("len")), 2);

    beginTest("ParamAddressTree: InsertParamRange");
    ParamProperties props;
    props.param_type = ParamType::CHOICE;
    props.size = 1;
    props.display_min = props.min = 0;
    props.display_max = props.max = 97;
    props.choices = choice::getChoicesFor(choice::MidiControlSource);
  
    ptree.InsertParamRangeOffset(
      {0x02000000, 4},
      ParamAddrRange({0x00000020, 8}, 0x00000023, 1, 4),
      "System Control Source", "System Control %d Source", props);

    NodeInfo* sc1_info = ptree.FindPtr({0x02000020, 8});
    expect(sc1_info != nullptr);
    expectEquals(sc1_info->getDescription().toString(), String("System Control 1 Source"));
    expect(sc1_info->isBase());
    expect(sc1_info->isRangeBase());
    expect(sc1_info->isIndexed());
    expect(sc1_info->hasParamInfo());

    NodeInfo* sc2_info = ptree.FindPtr({0x02000021, 8});
    expect(sc2_info != nullptr);
    expectEquals(sc2_info->getDescription().toString(), String("System Control 2 Source"));
    expect(sc2_info->hasBase());
    expect(sc2_info->isIndexed());
    expect(sc2_info->hasParamInfo());

    beginTest("ParamTreeTemplateBuilder::BuildAddressTree");
    PTree addrTree = AddressTreeBuilder::getAddressTree();
    NodeInfo fnd_stp = ptree.Find(setup_addr);
    expectEquals(fnd_stp.getDescription().toString(), String("Setup"));

    beginTest("ParamAddressTree GetPath");
    ParamPath path = addrTree.GetPath(setup_addr);
    expectEquals(path[0].node_id.toString(), String("Setup"));
    ParamAddr ssm2_addr(uint32(0x18001100), 6);
    path = addrTree.GetPath(ssm2_addr);
    expectEquals(path[0].node_id.toString(), String("Temporary Studio Set"));
    expectEquals(path[1].node_id.toString(), String("Studio Set MIDI"));
    expectEquals(path[1].index, 2);
    path = addrTree.GetPath({uint32(0x01000000), 8});
    expectEquals(path[1].node_id.toString(), String("Sound Mode"));

    path = addrTree.GetPath({uint32(0x01000004), 8});
    expectEquals(path[1].node_id.toString(), String("Studio Set BS MSB (CC# 0)"));

    beginTest("ParamAddressTree getting ParamInfo");
    NodeInfo* sm_info = addrTree.FindPtr(ParamAddr(uint32(0x01000000), 8));
    expectEquals(sm_info->getDescription().toString(), String("Sound Mode"));
    expect(sm_info->hasParamInfo());
    expectEquals(int(sm_info->getParamInfo()->getType()), int(ParamType::CHOICE));
    NodeInfo* mt_info = addrTree.FindPtr(ParamAddr(uint32(0x02000000), 8));
    expectEquals(mt_info->getDescription().toString(), String("Master Tune"));
    expect(mt_info->hasParamInfo());
    std::shared_ptr<ParamInfo> pinfo = mt_info->getParamInfo();
    expectEquals(int(pinfo->getType()), int(ParamType::FLOAT));
    expectEquals(int(pinfo->getByteSize()), 4);
    expectEquals(pinfo->getDisplayValue(24), String(-100.0, 1));
    expectEquals(pinfo->getDisplayValue(1024), String(0.0, 1));
    expectEquals(pinfo->getDisplayValue(2023), String(99.9, 1));

    NodeInfo* mks_info = addrTree.FindPtr(ParamAddr(uint32(0x02000004), 8));
    expectEquals(mks_info->getDescription().toString(), String("Master Key Shift"));
    expect(mks_info->hasParamInfo());
    pinfo = mks_info->getParamInfo();
    expectEquals(int(pinfo->getType()), int(ParamType::INT));
    expectEquals(pinfo->getDisplayValue(40), String(-24));
    expectEquals(pinfo->getNormalizedInt("23"), 87);

    NodeInfo* sc_info = addrTree.FindPtr(ParamAddr(uint32(0x02000011), 8));
    expectEquals(sc_info->getDescription().toString(), String("Studio Set Control Channel"));
    expect(sc_info->hasParamInfo());
    pinfo = sc_info->getParamInfo();
    expectEquals(int(pinfo->getType()), int(ParamType::CHOICE));
    expectEquals(pinfo->getDisplayValue(0), String("1"));
    expectEquals(pinfo->getDisplayValue(16), String("OFF"));

    beginTest("ParamValueDecoder construction");
    ParamValueDecoder decoder(1);
    uint8 byte[1] = {0x01};

    expectEquals(decoder.getPaddedInt(byte), 1);
    byte[0] = {0x03};
    expectEquals(decoder.getPaddedInt(byte), 3);
    uint8 buf[1] = {0x00};
    decoder.getRawData(3, buf);
    expectEquals(int(buf[0]), 3);

    ParamValueDecoder fb_decoder(4);
    uint8 four_bytes[4] = {0x02, 0x01, 0x07, 0x02};
    expectEquals(fb_decoder.getRawInt(four_bytes), 8562);

    uint8 buf4[4] = {0, 0, 0, 0};
    fb_decoder.getRawData(8562, buf);
    expectEquals(int(buf[0]), 2);
    expectEquals(int(buf[1]), 1);
    expectEquals(int(buf[2]), 7);
    expectEquals(int(buf[3]), 2);

    beginTest("ParamAddressTree GetParamUpdates");
    uint8 sm_addr_bytes[4] = {0x01, 0x00, 0x00, 0x00};
    uint8 sm_val_bytes[1] = {0x03};
    
    std::vector<ParamUpdate> updates = addrTree.GetParamUpdates(sm_addr_bytes, sm_val_bytes, 1);
    expectEquals(int(updates.size()), 1);
    expectEquals(int(updates[0].value), 3);
    expectEquals(updates[0].toString(), String("//Setup/Sound Mode -> GS"));
    
    uint8 ss_addr_bytes[4] = {0x01, 0x00, 0x00, 0x04};
    uint8 ss_val_bytes[3] = {0x01, 0x02, 0x03};
    updates = addrTree.GetParamUpdates(ss_addr_bytes, ss_val_bytes, 3);
    expectEquals(int(updates.size()), 3);
    expectEquals(updates[1].toString(), String("//Setup/Studio Set BS LSB (CC# 32) -> 2"));
    expectEquals(updates[1].value, 2);

    uint8 sc_addr[4] = {0x02, 0x00, 0x00, 0x22};
    uint8 sc_val[1] = {0x29}; // 0x29 = 41 -> "CC42"
    updates = addrTree.GetParamUpdates(sc_addr, sc_val, 1);
    expectEquals(updates[0].toString(),
                 String("//System/System Common/System Control Source[3] -> CC42"));
  
  }
};