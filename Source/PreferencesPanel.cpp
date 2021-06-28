/*
  ==============================================================================

    PreferencesPanel.cpp
    Created: 14 Jun 2020 1:47:38am
    Author:  Keith

  ==============================================================================
*/

#include "PreferencesPanel.h"

const StringArray oscDestinationColumns = {
  settings::osc::DestinationIpAddress.toString(),
  settings::osc::DestinationPort.toString(),
};

I7PreferencesPanel::I7PreferencesPanel() : TabbedComponent(TabbedButtonBar::Orientation::TabsAtTop)
{
  
  addTab("MIDI",
         getLookAndFeel().findColour(ResizableWindow::backgroundColourId),
         &midiPanel_, false);
  addTab("OSC",
         getLookAndFeel().findColour(ResizableWindow::backgroundColourId),
         &oscPanel_, false);
  
  setSize(getParentWidth(), getParentHeight());
  //addSettingsPage("MIDI", nullptr, 0);
  //setButtonSize(100);
  //setCurrentPage("MIDI");
}

void I7PreferencesPanel::parentSizeChanged()
{
  setSize(getParentWidth(), getParentHeight());
}

/*
void I7PreferencesPanel::resized()
{
  setBounds(getLocalBounds());
}
*/

/*
Component* I7PreferencesPanel::createComponentForPage(const String& pageName)
{
  return new MidiPreferencesPanel();
}
*/

MidiPreferencesPanel::MidiPreferencesPanel()
{
  midiInputLabel_.setText("MIDI Input:", dontSendNotification);
  addAndMakeVisible(midiInputLabel_);
  addAndMakeVisible(midiInputList_);
  
  midiOutputLabel_.setText("MIDI Output:", dontSendNotification);
  addAndMakeVisible(midiOutputLabel_);
  addAndMakeVisible(midiOutputList_);
  

  midiInputList_.setTextWhenNoChoicesAvailable ("No MIDI Inputs Enabled");
  midiOutputList_.setTextWhenNoChoicesAvailable ("No MIDI Outputs Enabled");

}
void MidiPreferencesPanel::setMidiInputList(const StringArray& devices, const int selectedIndex)
{
  midiInputList_.clear();
  midiInputList_.addItemList(devices, 1);
  midiInputList_.setSelectedItemIndex(selectedIndex);
}

void MidiPreferencesPanel::setMidiOutputList(const StringArray& devices, const int selectedIndex)
{
  midiOutputList_.clear();
  midiOutputList_.addItemList(devices, 1);
  midiOutputList_.setSelectedItemIndex(selectedIndex);
}

void MidiPreferencesPanel::paint (Graphics& g)
{
  g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MidiPreferencesPanel::resized()
{
  auto area = getLocalBounds();
  int labelWidth = midiOutputLabel_.getFont().getStringWidth(midiOutputLabel_.getText());

  auto inputRow = area.removeFromTop(50);
  midiInputLabel_.setBounds(inputRow.removeFromLeft(labelWidth));
  midiInputList_.setBounds(inputRow);
  
  auto outputRow = area.removeFromTop(50);
  midiOutputLabel_.setBounds(outputRow.removeFromLeft(labelWidth));
  midiOutputList_.setBounds(outputRow);
}

MidiPreferences::MidiPreferences(Settings* settings,
                                 MidiPreferencesPanel* view) : settings_(settings),
                                                               view_(view)
{
  settings_->addListener(this, settings::Midi);
  refreshMidiDevices();
  const ValueTree& midiSettings = settings_->getSettingsFor(settings::Midi);
  view_->setMidiInputList(fetchMidiInputs(), inputDeviceIndex(midiSettings.getProperty(settings::midi::Input)));
  view_->getMidiInputList()->addListener(this);

  view_->setMidiOutputList(fetchMidiOutputs(), outputDeviceIndex(midiSettings.getProperty(settings::midi::Output)));
  view_->getMidiOutputList()->addListener(this);
}

StringArray MidiPreferences::fetchMidiInputs()
{
  StringArray midiInputNames;
  for (const auto& input : inputList_)
    midiInputNames.add (input.name);
  
  return midiInputNames;
}

StringArray MidiPreferences::fetchMidiOutputs()
{
  StringArray midiOutputNames;
  for (const auto& output : outputList_)
    midiOutputNames.add (output.name);
  
  return midiOutputNames;
}

void MidiPreferences::refreshMidiDevices()
{
  inputList_ = MidiInput::getAvailableDevices();
  outputList_ = MidiOutput::getAvailableDevices();
}

int MidiPreferences::inputDeviceIndex(const String& identifier)
{
  int index = 0;
  for (const MidiDeviceInfo& mdi : inputList_) {
    if (mdi.identifier == identifier)
      return index;
    index++;
  }
  return -1;
}

int MidiPreferences::outputDeviceIndex(const String& identifier)
{
  int index = 0;
  for (const MidiDeviceInfo& mdi : outputList_) {
    if (mdi.identifier == identifier)
      return index;
    index++;
  }
  return -1;
}

void MidiPreferences::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
  ValueTree midiSettings = settings_->getSettingsFor(settings::Midi);
  if (comboBoxThatHasChanged == view_->getMidiInputList()) {
    ComboBox* midiInputList = view_->getMidiInputList();
    DBG ("getText() = " + midiInputList->getText());
    int i = midiInputList->getSelectedItemIndex();
    DBG ("selected index = " + String(i));
    const MidiDeviceInfo& mdi = inputList_[i];
    DBG ("inputList_[" + String(i) + "].name = " + mdi.name);
    DBG ("inputList_[" + String(i) + "].identifier = " + mdi.identifier);

    midiSettings.setPropertyExcludingListener(this,
                                              settings::midi::Input,
                                              inputList_[midiInputList->getSelectedItemIndex()].identifier,
                                              nullptr);
  }
  else if (comboBoxThatHasChanged == view_->getMidiOutputList()) {
    ComboBox* midiOutputList = view_->getMidiOutputList();
    midiSettings.setPropertyExcludingListener(this,
                                              settings::midi::Output,
                                              outputList_[midiOutputList->getSelectedItemIndex()].identifier,
                                              nullptr);
  }
}

void MidiPreferences::valueTreePropertyChanged(ValueTree& t, const Identifier& property)
{
  if (t.getType() != settings::Midi) return;
  
  const String& deviceId = t.getProperty(property);
  
  if (property == settings::midi::Input) {
    view_->getMidiInputList()->setSelectedItemIndex(inputDeviceIndex(deviceId), dontSendNotification);
  }
  else if (property == settings::midi::Output) {
    view_->getMidiOutputList()->setSelectedItemIndex(outputDeviceIndex(deviceId), dontSendNotification);
  }
}

OscPreferencesPanel::OscPreferencesPanel()
{
  oscListenPort_.setText("OSC Server Port:", dontSendNotification);
  oscListenPort_.attachToComponent(&oscListenPortValue_, true);
  oscListenPortValue_.setEditable(true);
  oscListenPortValue_.setColour(Label::backgroundColourId, Colours::darkblue);
  
  addDestinationButton_.setButtonText("+");
  removeDestinationButton_.setButtonText("-");
  
  addAndMakeVisible(oscListenPort_);
  addAndMakeVisible(oscListenPortValue_);
  addAndMakeVisible(destinationTable_);
  addAndMakeVisible(addDestinationButton_);
  addAndMakeVisible(removeDestinationButton_);
}

void OscPreferencesPanel::resized()
{
  auto area = getLocalBounds();
  int labelWidth = oscListenPort_.getFont().getStringWidth(oscListenPort_.getText());

  auto oscPortRow = area.removeFromTop(30);
  oscListenPort_.setBounds(oscPortRow.removeFromLeft(labelWidth));
  oscListenPortValue_.setBounds(oscPortRow);
  
  destinationTable_.setBounds(area.removeFromLeft(300));
  addDestinationButton_.setBounds(area.removeFromTop(30));
  removeDestinationButton_.setBounds(area.removeFromTop(30));
}

OscDestinationTable::OscDestinationTable(TableListBox* table, ValueTree& destinations) : table_(table), destinations_(destinations)
{
  table_->setModel(this);
  table_->getHeader().addColumn("IP Address", 1, 150);
  table_->getHeader().addColumn("UDP Port", 2, 150);
}

String OscDestinationTable::getText(const int row, const int column)
{
  Identifier property = column == 1 ? settings::osc::DestinationIpAddress : settings::osc::DestinationPort;
  ValueTree element = destinations_.getChild(row);
  return element.getProperty(property);
}

void OscDestinationTable::setText(const int row, const int column, const String& text)
{
  Identifier property = column == 1 ? settings::osc::DestinationIpAddress : settings::osc::DestinationPort;
  ValueTree element = destinations_.getChild(row);
  element.setProperty(property, text, nullptr);
}

int OscDestinationTable::getNumRows()
{
  return destinations_.getNumChildren();
}

void OscDestinationTable::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
  if (rowIsSelected)
    g.fillAll(Colours::lightblue);
}

void OscDestinationTable::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
  g.setColour(rowIsSelected ? Colours::lightblue : table_->getLookAndFeel().findColour(ListBox::textColourId));
  
  ValueTree destElement = destinations_.getChild(rowNumber);
  if (destElement.isValid()) {
    StringRef text = destElement.getProperty(oscDestinationColumns[columnId]).toString();
    g.drawText (text, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
  }
}

Component* OscDestinationTable::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
  auto* cell = static_cast<EditableCell*>(existingComponentToUpdate);
  
  Identifier property = columnId == 1 ? settings::osc::DestinationIpAddress : settings::osc::DestinationPort;
  ValueTree element = destinations_.getChild(rowNumber);
  
  if (cell == nullptr)
    cell = new EditableCell(*this, element, property);
  
  //cell->setText(element.getProperty(property), dontSendNotification);
  cell->setRowAndColumn(rowNumber, columnId);
  
  return cell;
}

OscDestinationTable::EditableCell::EditableCell(OscDestinationTable& owner, ValueTree& destination, Identifier& property) :
  owner_(owner), destination_(destination), property_(property)
{
  setEditable(false, true, false);
}

void OscDestinationTable::EditableCell::textWasEdited()
{
  owner_.setText(row_, column_, getText());
  /*
  if (property_ == settings::osc::DestinationPort) {
    destination_.setProperty(property_, getText().getIntValue(), nullptr);
    return;
  }
  destination_.setProperty(property_, getText(), nullptr);
  */
}

void OscDestinationTable::EditableCell::mouseDown(const MouseEvent& event)
{
  //int row = destination_.getParent().indexOf(destination_);
  owner_.getTable()->selectRowsBasedOnModifierKeys(row_, event.mods, false);
  Label::mouseDown(event);
}

void OscDestinationTable::EditableCell::setRowAndColumn(const int row, const int column)
{
  row_ = row;
  column_ = column;
  setText(owner_.getText(row, column), dontSendNotification);
}

OscPreferences::OscPreferences(ValueTree& oscSettings, OscPreferencesPanel* view) :
  oscSettings_(oscSettings), view_(view)
{
  ValueTree destinations = oscSettings_.getChildWithName(settings::osc::Destinations);
  destinationTable_.reset(new OscDestinationTable(view_->getDestinationTable(), destinations));
  destinationTable_->getTable()->updateContent();
  
  oscSettings_.addListener(this);
  view_->getOscListenPortValue()->addListener(this);
  view_->getAddDestinationButton()->addListener(this);
  view_->getRemoveDestinationButton()->addListener(this);
  
  syncValueTreeNotifyListeners(oscSettings, oscSettings_);
  //destinationTable_->getTable()->updateContent();
}

void OscPreferences::labelTextChanged(Label* label)
{
  if (label == view_->getOscListenPortValue()) {
    oscSettings_.setProperty(settings::osc::ServerPort, label->getText().getIntValue(), nullptr);
  }
}

void OscPreferences::buttonClicked(Button* button)
{
  if (button == view_->getAddDestinationButton()) {
    ValueTree child(settings::osc::Destination,
                    {{settings::osc::DestinationIpAddress, ""},
                     {settings::osc::DestinationPort, 0}});
    oscSettings_.getChildWithName(settings::osc::Destinations).appendChild(child, nullptr);
    // In valueTreeChildAdded(), set the row selected.
  }
  else if (button == view_->getRemoveDestinationButton()) {
    SparseSet<int> rowsToDelete = destinationTable_->getTable()->getSelectedRows();
    for (int i = 0; i < rowsToDelete.size(); ++i) {
      oscSettings_.getChildWithName(settings::osc::Destinations).removeChild(rowsToDelete[i], nullptr);
    }
    int lastRowSelected = destinationTable_->getTable()->getLastRowSelected();
    if (lastRowSelected >= destinationTable_->getNumRows())
      destinationTable_->getTable()->selectRow(destinationTable_->getNumRows() - 1);
  }
  destinationTable_->getTable()->updateContent();
}

void OscPreferences::valueTreeChildAdded(ValueTree& parent, ValueTree& child)
{
  if (parent.getType() == settings::osc::Destinations) {
    destinationTable_->getTable()->updateContent();
    destinationTable_->getTable()->selectRow(parent.indexOf(child));
  }
}

void OscPreferences::valueTreeChildRemoved(ValueTree& parent, ValueTree& child, int index)
{
  if (parent.getType() == settings::osc::Destinations) {
    const auto& root = parent.getRoot();
    DBG(root.toXmlString());
    destinationTable_->getTable()->updateContent();
    int numRows = destinationTable_->getTable()->getNumRows();
    int treeSize = parent.getNumChildren();
    DBG("Destinations has " + String(treeSize) + " children; rows = " + String(numRows));
    if (index >= numRows) {
      destinationTable_->getTable()->selectRow(numRows - 1);
    }
  }
}

void OscPreferences::valueTreeChildOrderChanged(ValueTree& parent, int oldIndex, int newIndex)
{
  
}

void OscPreferences::valueTreePropertyChanged(ValueTree& tree, const Identifier& property)
{
  if (property == settings::osc::ServerPort) {
    view_->getOscListenPortValue()->setText(tree.getProperty(property), dontSendNotification);
    return;
  }
  
  if (tree.getType() == settings::osc::Destination) {
    //const auto& root = tree.getRoot();
    //DBG(root.toXmlString());
    DBG("Property " + property.toString() + " changed to " + tree.getProperty(property).toString());
    int childIndex = tree.getParent().indexOf(tree);
    DBG("VTPC [" + String(childIndex) + "]: {" + tree.getProperty(settings::osc::DestinationIpAddress).toString() + ", " + tree.getProperty(settings::osc::DestinationPort).toString() + "}");
  }
}
