/*
  ==============================================================================

    PreferencesPanel.h
    Created: 14 Jun 2020 1:47:38am
    Author:  Keith

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Settings.h"
#include "Utils.h"

static Identifier midiInputProp("input");
static Identifier midiOutputProp("output");

class MidiPreferencesPanel : public Component {
public:
  MidiPreferencesPanel();
  ComboBox* getMidiInputList() { return &midiInputList_; }
  ComboBox* getMidiOutputList() { return &midiOutputList_; }
  void setMidiInputList(const StringArray& devices, const int selectedIndex);
  void setMidiOutputList(const StringArray& devices, const int selectedIndex);
  
  void paint(Graphics& g) override;
  void resized() override;
  
private:
  Label midiInputLabel_, midiOutputLabel_;
  ComboBox midiInputList_, midiOutputList_;
};

class OscPreferencesPanel : public Component
{
public:
  OscPreferencesPanel();
  Label* getOscListenPortValue() { return &oscListenPortValue_; }
  TableListBox* getDestinationTable() { return &destinationTable_; }
  Button* getAddDestinationButton() { return &addDestinationButton_; }
  Button* getRemoveDestinationButton() { return &removeDestinationButton_; }
  
  // Component implementation.
  void resized() override;

private:
  Label oscListenPort_, oscListenPortValue_;
  TableListBox destinationTable_;
  TextButton addDestinationButton_, removeDestinationButton_;
};

class OscDestinationTable : public TableListBoxModel, public ChangeBroadcaster
{
public:
  class EditableCell : public Label
  {
  public:
    EditableCell(OscDestinationTable& owner, ValueTree& destination, Identifier& property);
    void setRowAndColumn(const int row, const int column);
    
    // Label implementation.
    void textWasEdited() override;
    void mouseDown(const MouseEvent& event) override;
    
  private:
    OscDestinationTable& owner_;
    int row_, column_;
    ValueTree destination_;
    Identifier property_;
  };
  
  OscDestinationTable(TableListBox* table, ValueTree& destinations);
  TableListBox* getTable() { return table_; }
  String getText(const int row, const int column);
  void setText(const int row, const int column, const String& text);
  
  // TableListBoxModel implementation.
  int getNumRows() override;
  void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
  void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
  Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
  
private:
  TableListBox* table_;
  ValueTree destinations_;
};

class OscPreferences : private Label::Listener, private ValueTree::Listener, private Button::Listener
{
public:
  OscPreferences(ValueTree& oscSettings, OscPreferencesPanel* view);
  
private:
  
  // Label::Listener implementation.
  void labelTextChanged(Label* label) override;
  
  // Button::Listener implementation.
  void buttonClicked(Button* button) override;
  
  // ValueTree::Listener implementation.
  void valueTreeChildAdded(ValueTree& parent, ValueTree& child) override;
  void valueTreeChildRemoved(ValueTree& parent, ValueTree& child, int index) override;
  void valueTreeChildOrderChanged(ValueTree& parent, int oldIndex, int newIndex) override;
  void valueTreePropertyChanged(ValueTree& tree, const Identifier& property) override;
  
  // Data members.
  ValueTree oscSettings_;
  OscPreferencesPanel* view_;
  std::unique_ptr<OscDestinationTable> destinationTable_;
};

class MidiPreferences : private ComboBox::Listener, private ValueTree::Listener
{
public:
  MidiPreferences(Settings* settings, MidiPreferencesPanel* view);
  
private:
  StringArray fetchMidiInputs();
  StringArray fetchMidiOutputs();
  void refreshMidiDevices();
  int inputDeviceIndex(const String& identifier);
  int outputDeviceIndex(const String& identifier);
  
  // Overrides ComboBox::Listener.
  void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
  
  // Implements ValueTree::Listener.
  void valueTreePropertyChanged(ValueTree& t, const Identifier& property) override;
  
  // Data members.
  Settings* settings_;
  MidiPreferencesPanel* view_;
  
  Array<MidiDeviceInfo> inputList_;
  Array<MidiDeviceInfo> outputList_;
};

class I7PreferencesPanel : public TabbedComponent {
public:
  I7PreferencesPanel();
  //void resized() override;
  void parentSizeChanged() override;
  MidiPreferencesPanel* getMidiPreferencesPanel() { return &midiPanel_; }
  OscPreferencesPanel* getOscPreferencesPanel() { return &oscPanel_; }

private:
  MidiPreferencesPanel midiPanel_;
  OscPreferencesPanel oscPanel_;
};
