/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


MainComponent::MainComponent(I7Controller* controller) {
  setOpaque(true);
  initializeSettings();
  
  // Instantiate MidiPreferences with controller Settings object.
  midiPreferences_.reset(new MidiPreferences(controller->getSettings(),
                                             preferencesPanel_.getMidiPreferencesPanel()));
  
  // Instantiate OscPreferences.
  ValueTree oscSettings = controller->getSettings()->getSettingsFor(settings::Osc);
  oscPreferences_.reset(new OscPreferences(oscSettings,
                                           preferencesPanel_.getOscPreferencesPanel()));
  
  // Set MidiMonitorComponent to listen to controller's MIDI input.
  controller->addMidiInputCallback(&midiMonitorComponent_);
  
  mainPanel_.addChildComponent(preferencesPanel_);
  mainPanel_.addChildComponent(midiMonitorComponent_);
  
  setApplicationCommandManagerToWatch(&commandManager_);
  commandManager_.registerAllCommandsForTarget(this);
  commandManager_.setFirstCommandTarget(this);
  
  //addAndMakeVisible(burgerMenu_);
  addAndMakeVisible(menuHeader_);
  addAndMakeVisible(mainPanel_);
  addAndMakeVisible(sidePanel_);
  
  burgerMenu_.setModel(this);
  sidePanel_.setContent(&burgerMenu_, false);
  

  
  /*
  addAndMakeVisible (midiInputList_);
  midiInputList_.setTextWhenNoChoicesAvailable ("No MIDI Inputs Enabled");
  auto midiInputs = MidiInput::getAvailableDevices();
        
  StringArray midiInputNames;
  for (const auto& input : midiInputs)
    midiInputNames.add (input.name);
  
  midiInputList_.addItemList (midiInputNames, 1);
  midiInputList_.onChange = [this] { setMidiInput (midiInputList_.getSelectedItemIndex()); };

  setMidiInput(midiInputs.indexOf(getDefaultDevice(midiInputs)));

  // Set up the MIDI Monitor display.
  addAndMakeVisible(midiMonitorComponent_);
  */
  setSize (600, 400);
}

MainComponent::~MainComponent()
{
  //auto currentDeviceId = MidiInput::getAvailableDevices()[midiInputList_.getSelectedItemIndex()].identifier;
  //deviceManager_.removeMidiInputDeviceCallback(currentDeviceId, &i7Communicator_);
  //deviceManager_.removeMidiInputDeviceCallback(currentDeviceId, &midiMonitorComponent_);
  // deviceManager_.removeMidiInputDeviceCallback (
  //   MidiInput::getAvailableDevices()[midiInputList_.getSelectedItemIndex()].identifier,
  //   &i7Communicator_);

}

void MainComponent::initializeSettings() {
  /*
  PropertiesFile::Options options;
  options.osxLibrarySubFolder = "Application Support";
    
  options.applicationName = ProjectInfo::projectName;
  options.filenameSuffix = ".settings";
  options.folderName = File::getSpecialLocation(
    File::SpecialLocationType::userApplicationDataDirectory)
    .getChildFile(ProjectInfo::projectName).getFullPathName();
  appProperties_.setStorageParameters(options);
   */
}


//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

  /*
    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
  */
}

void MainComponent::resized()
{
  // This is called when the MainComponent is resized.
  // If you add any child components, this is where you should
  // update their positions.
  auto area = getLocalBounds();
  
  menuHeader_.setBounds(area.removeFromTop(40));
  mainPanel_.setBounds(area);
  
  /*
  midiInputList_.setBounds (area.removeFromTop (36).removeFromRight (getWidth() - 150).reduced (8));
  midiMonitorComponent_.setBounds (area.reduced (8));
  */
}

//==============================================================================
/** Starts listening to a MIDI input device, enabling it if necessary. */
/*
void MainComponent::setMidiInput (int index) {
  auto device_list = MidiInput::getAvailableDevices();

  //deviceManager_.removeMidiInputDeviceCallback(device_list[lastInputIndex_].identifier, &i7Communicator_);
  deviceManager_.removeMidiInputDeviceCallback(device_list[lastInputIndex_].identifier, &midiMonitorComponent_);
  auto newInput = device_list[index];

  if (! deviceManager_.isMidiInputDeviceEnabled (newInput.identifier))
    deviceManager_.setMidiInputDeviceEnabled (newInput.identifier, true);

  //deviceManager_.addMidiInputDeviceCallback (newInput.identifier, &i7Communicator_);
  deviceManager_.addMidiInputDeviceCallback (newInput.identifier, &midiMonitorComponent_);
  midiInputList_.setSelectedId (index + 1, dontSendNotification);
  appProperties_.getUserSettings()->setValue("midiInputDeviceId", device_list[index].identifier);

  lastInputIndex_ = index;
}

MidiDeviceInfo MainComponent::getDefaultDevice(const Array<MidiDeviceInfo>& devices) {
  auto savedDeviceId = appProperties_.getUserSettings()->getValue("midiInputDeviceId", "");
  if (savedDeviceId.isNotEmpty()) {
    for (auto device : devices) {
      if (device.identifier == savedDeviceId)
        return device;
    }
  }

  // find the first enabled device and use that by default
  for (auto device : devices) {
    if (deviceManager_.isMidiInputDeviceEnabled (device.identifier))
      return device;
  }

  // Return the first device if none of the above criteria were met.
  return devices[0];
 }
*/

// ApplicationCommandTarget overrides.
ApplicationCommandTarget* MainComponent::getNextCommandTarget()
{
  return findFirstTargetParentComponent();
  //return nullptr;
}

void MainComponent::getAllCommands(Array<CommandID>& c)
{
  Array<CommandID> commands {
    CommandIDs::showPreferences,
    CommandIDs::showMidiMonitor
  };
  c.addArray(commands);
}

void MainComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
  switch(commandID) {
    case CommandIDs::showPreferences:
      result.setInfo("Preferences", "Displays the Preferences panel", "Menu", 0);
      break;
    case CommandIDs::showMidiMonitor:
      result.setInfo("Midi Monitor", "Displays the MIDI Monitor", "Menu", 0);
      break;
    default:
      break;
  }
}

bool MainComponent::perform(const InvocationInfo &info)
{
  switch(info.commandID) {
    case CommandIDs::showPreferences:
      midiMonitorComponent_.setVisible(false);
      preferencesPanel_.setVisible(true);
      //preferencesPanel_.showInDialogBox("Preferences", 300, 300);
      break;
    case CommandIDs::showMidiMonitor:
      preferencesPanel_.setVisible(false);
      midiMonitorComponent_.setVisible(true);
      break;
    default:
      return false;
  }
  sidePanel_.showOrHide(false);
  repaint();
  mainPanel_.repaint();
  return true;
}

// MenuBarModel overrides.
PopupMenu MainComponent::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
  PopupMenu menu;
  if (topLevelMenuIndex == 0) {
    menu.addCommandItem(&commandManager_, CommandIDs::showPreferences);
    menu.addCommandItem(&commandManager_, CommandIDs::showMidiMonitor);
  }
  return menu;
}

void MainComponent::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
  
}

StringArray MainComponent::getMenuBarNames()
{
  return { "I7 Controller" };
}
