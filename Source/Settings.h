/*
  ==============================================================================

    Settings.h
    Created: 15 Jun 2020 10:01:09pm
    Author:  Keith

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace settings {
// Root identifier.
static const Identifier Root("Root");

// Top-level tree names.
static const Identifier Midi("Midi");
static const Identifier Osc("Osc");

// MIDI properties.
namespace midi {
static const Identifier Input("Input");
static const Identifier Output("Output");
}  // namespace midi

// OSC properties.
namespace osc {
static const Identifier ServerPort("ServerPort");
static const Identifier Destinations("Destinations");
static const Identifier Destination("Destination");
static const Identifier DestinationIpAddress("DestinationIpAddress");
static const Identifier DestinationPort("DestinationPort");
                                  
}  // namespace osc

}  // namespace settings

class Settings : private ValueTree::Listener {
public:
  Settings();
  ~Settings();
  void loadUserSettings();
  
  ValueTree getSettingsFor(const Identifier& typeName);
  void addListener(ValueTree::Listener* listener, const Identifier& typeName);
  void removeListener(ValueTree::Listener* listener, const Identifier& typeName);
  
private:
  void initializeTree();
  void initializeStorage();
  
  
  // Implements ValueTree::Listener.
  void valueTreePropertyChanged(ValueTree& t, const Identifier& property) override;
  
  // Members.
  ValueTree root_;
  std::unordered_map<String, ValueTree> nodesWithListeners_;
  ApplicationProperties appProperties_;
};
