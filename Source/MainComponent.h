/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "I7Controller.h"
#include "I7SysexCommunicator.h"
#include "MidiMonitorComponent.h"
#include "PreferencesPanel.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
struct BurgerMenuHeader  : public Component
{
    BurgerMenuHeader (SidePanel& sp)
        : sidePanel (sp)
    {
        static const unsigned char burgerMenuPathData[]
            = { 110,109,0,0,128,64,0,0,32,65,108,0,0,224,65,0,0,32,65,98,254,212,232,65,0,0,32,65,0,0,240,65,252,
                169,17,65,0,0,240,65,0,0,0,65,98,0,0,240,65,8,172,220,64,254,212,232,65,0,0,192,64,0,0,224,65,0,0,
                192,64,108,0,0,128,64,0,0,192,64,98,16,88,57,64,0,0,192,64,0,0,0,64,8,172,220,64,0,0,0,64,0,0,0,65,
                98,0,0,0,64,252,169,17,65,16,88,57,64,0,0,32,65,0,0,128,64,0,0,32,65,99,109,0,0,224,65,0,0,96,65,108,
                0,0,128,64,0,0,96,65,98,16,88,57,64,0,0,96,65,0,0,0,64,4,86,110,65,0,0,0,64,0,0,128,65,98,0,0,0,64,
                254,212,136,65,16,88,57,64,0,0,144,65,0,0,128,64,0,0,144,65,108,0,0,224,65,0,0,144,65,98,254,212,232,
                65,0,0,144,65,0,0,240,65,254,212,136,65,0,0,240,65,0,0,128,65,98,0,0,240,65,4,86,110,65,254,212,232,
                65,0,0,96,65,0,0,224,65,0,0,96,65,99,109,0,0,224,65,0,0,176,65,108,0,0,128,64,0,0,176,65,98,16,88,57,
                64,0,0,176,65,0,0,0,64,2,43,183,65,0,0,0,64,0,0,192,65,98,0,0,0,64,254,212,200,65,16,88,57,64,0,0,208,
                65,0,0,128,64,0,0,208,65,108,0,0,224,65,0,0,208,65,98,254,212,232,65,0,0,208,65,0,0,240,65,254,212,
                200,65,0,0,240,65,0,0,192,65,98,0,0,240,65,2,43,183,65,254,212,232,65,0,0,176,65,0,0,224,65,0,0,176,
                65,99,101,0,0 };

        Path p;
        p.loadPathFromData (burgerMenuPathData, sizeof (burgerMenuPathData));
        burgerButton.setShape (p, true, true, false);

        burgerButton.onClick = [this] { showOrHide(); };
        addAndMakeVisible (burgerButton);
    }

    ~BurgerMenuHeader() override
    {
        sidePanel.showOrHide (false);
    }
  
private:
    void paint (Graphics& g) override
    {
        auto titleBarBackgroundColour = getLookAndFeel().findColour (ResizableWindow::backgroundColourId)
                                                        .darker();

        g.setColour (titleBarBackgroundColour);
        g.fillRect (getLocalBounds());
    }

    void resized() override
    {
        auto r = getLocalBounds();

        burgerButton.setBounds (r.removeFromRight (40).withSizeKeepingCentre (20, 20));

        titleLabel.setFont (Font (getHeight() * 0.5f, Font::plain));
        titleLabel.setBounds (r);
    }

    void showOrHide()
    {
        sidePanel.showOrHide (! sidePanel.isPanelShowing());
    }

    SidePanel& sidePanel;

    Label titleLabel         { "titleLabel", "I7 Controller" };
    ShapeButton burgerButton { "burgerButton", Colours::lightgrey, Colours::lightgrey, Colours::white };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BurgerMenuHeader)
};

class MainComponent : public Component,
                      public ApplicationCommandTarget,
                      public MenuBarModel
{
public:
  //==============================================================================
  MainComponent(I7Controller* controller);
  ~MainComponent();

  //==============================================================================
  // Overrides Component.
  void paint (Graphics&) override;
  void resized() override;

  // Overrides ApplicationCommandTarget.
  ApplicationCommandTarget* getNextCommandTarget() override;
  void getAllCommands (Array<CommandID>& c) override;
  void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;
  bool perform(const InvocationInfo& info) override;
  
  // Overrides MenuBarModel.
  PopupMenu getMenuForIndex(int topLevelMenuIndex, const String& menuName) override;
  void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;
  StringArray getMenuBarNames() override;
  
private:
  // Loads user settings if available.
  void initializeSettings();

  // Returns the default Midi input device to be used.
  //MidiDeviceInfo getDefaultDevice(const Array<MidiDeviceInfo>& devices);

  // Enables and sets the active midi input device.
  //void setMidiInput(int index);

  //==============================================================================
  // Your private member variables go here...
  //AudioDeviceManager deviceManager_;
  //ComboBox midiInputList_;
  //Label midiInputListLabel_;
  //int lastInputIndex_ = 0;

  ApplicationCommandManager commandManager_;
  
  SidePanel sidePanel_ { "Menu", 300, false };
  BurgerMenuComponent burgerMenu_;
  BurgerMenuHeader menuHeader_ { sidePanel_ };
  
  //ApplicationProperties appProperties_;
  
  // Individual Components to display in mainPanel_.
  Component mainPanel_;
  I7PreferencesPanel preferencesPanel_;
  MidiMonitorComponent midiMonitorComponent_;
  
  // GUI controllers.
  std::unique_ptr<MidiPreferences> midiPreferences_ = nullptr;
  std::unique_ptr<OscPreferences> oscPreferences_ = nullptr;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

enum CommandIDs
{
  showPreferences = 1,
  showMidiMonitor,
};


