/*
  ==============================================================================

    Settings.cpp
    Created: 15 Jun 2020 10:01:09pm
    Author:  Keith

  ==============================================================================
*/

#include "Settings.h"

Settings::Settings()
{
  initializeTree();
  initializeStorage();
  addListener(this, settings::Root);
}

Settings::~Settings()
{
  auto xml = root_.createXml();
  juce::File xmlFile(appProperties_.getUserSettings()->getValue("SettingsFile"));
  xml->writeTo(xmlFile);
}

void Settings::initializeTree()
{
  root_ =
  { settings::Root, {},
    {
      { settings::Midi,
        {
          { settings::midi::Input, {} },
          { settings::midi::Output, {} },
        }, {},
      },
      { settings::Osc,
        {
          { settings::osc::ServerPort, 9099 }
        },
        {
          { settings::osc::Destinations, {},
            {}
          },
        },
      },
    },
  };
}

void Settings::initializeStorage() {
  PropertiesFile::Options options;
  options.osxLibrarySubFolder = "Application Support";
    
  options.applicationName = ProjectInfo::projectName;
  options.folderName = ProjectInfo::projectName;
  options.filenameSuffix = ".settings";
  DBG("getDefaultFile = " + options.getDefaultFile().getFullPathName());
  appProperties_.setStorageParameters(options);
  
  // Get default settings file.
  String settingsPath = options.getDefaultFile().getSiblingFile("settings.xml").getFullPathName();
  appProperties_.getUserSettings()->setValue("SettingsFile", settingsPath);
}

/*
std::pair<StringArray, Identifier> parsePath(const String& path)
{
  StringArray pair = StringArray::fromTokens(path, ".", "");
  
  if (pair.size() != 2) {
    return {StringArray(), Identifier::null};
  }
  
  return {StringArray::fromTokens(pair[0], "/", ""), pair[1]};
}

ValueTree traversePath(ValueTree t, StringArray* v)
{
  if (!t.isValid()) return t;
  if (v->isEmpty()) return t;
  
  const Identifier& next = (*v)[0];
  ValueTree child = t.getChildWithName(next);
  v->remove(0);
  return traversePath(child, v);
}
*/

void Settings::loadUserSettings()
{
  juce::File settingsFile(appProperties_.getUserSettings()->getValue("SettingsFile"));
  std::unique_ptr<XmlElement> xmlRoot = parseXML(settingsFile);
  
  auto newSettings = ValueTree::fromXml(*xmlRoot);
  syncValueTreeNotifyListeners(newSettings, root_);
  //root_ = ValueTree::fromXml(*xmlRoot);
  
  const int svrPort = root_.getChildWithName(settings::Osc).getProperty(settings::osc::ServerPort);
  DBG("svrPort = " + String(svrPort));
  
  
  /*
  PropertiesFile* userSettings = appProperties_.getUserSettings();
  const PropertiesFile::Options& opts = appProperties_.getStorageParameters();
  DBG("Default File: " + opts.getDefaultFile().getFullPathName());
  DBG("folderName: " + opts.folderName);
  DBG("osxLibrarySubFolder: " + opts.osxLibrarySubFolder);
  
  for (const String& k : userSettings->getAllProperties().getAllKeys()) {
    auto nodeAndProperty = parsePath(k);
    if (nodeAndProperty.first.isEmpty()) continue;
    if (nodeAndProperty.second.isNull()) continue;
    
    // First path vector element should be empty string because of leading "/".
    StringArray* v = &nodeAndProperty.first;
    if (!v->begin()->isEmpty()) continue;
    v->remove(0);
    
    // Find the ValueTree node containing the property.
    ValueTree n = traversePath(root_, v);
    if (!n.isValid()) continue;
    
    // Find the property belonging to the node.
    const Identifier& propId = nodeAndProperty.second;
    if (!n.hasProperty(propId)) continue;

    // Set the property from the PropertiesFile.
    n.setPropertyExcludingListener(this, propId, userSettings->getValue(k), nullptr);
  }
  */
}



ValueTree Settings::getSettingsFor(const Identifier& typeName)
{
  return root_.getChildWithName(typeName);
}

void Settings::addListener(ValueTree::Listener* listener, const Identifier& typeName = {})
{
  if (typeName.isNull() || typeName == settings::Root) {
    root_.addListener(listener);
    return;
  }

  //ValueTree treeToListen = root_.getChildWithName(typeName);
  const String& idString = typeName.toString();
  auto it = nodesWithListeners_.find(idString);
  if (it == nodesWithListeners_.end())
    it = nodesWithListeners_.insert(nodesWithListeners_.end(), {idString, root_.getChildWithName(typeName)});
  it->second.addListener(listener);
}

void Settings::removeListener(ValueTree::Listener* listener, const Identifier& typeName = {})
{
  if (typeName.isNull()) {
    root_.removeListener(listener);
    return;
  }

  auto it = nodesWithListeners_.find(typeName.toString());
  if (it == nodesWithListeners_.end()) return;
  it->second.removeListener(listener);
}

/*
Array<const ValueTree> getSiblingsOfSameType(const ValueTree& t)
{
  Array<const ValueTree> siblings;
  const ValueTree& parent = t.getParent();
  for (ValueTree::Iterator it = parent.begin(); it != parent.end(); ++it) {
    if ((*it).getType() == t.getType()) {
      siblings.add(*it);
    }
  }
  return siblings;
}
*/

String getCanonicalPropertyName(ValueTree& t, const Identifier& property)
{
  // StringArray v = {t.getType().toString()};
  StringArray v;
  while (t != t.getRoot()) {
    v.insert(0, t.getType().toString());
    t = t.getParent();
  }
  return "/" + v.joinIntoString("/") + "." + property.toString();
}

void Settings::valueTreePropertyChanged(ValueTree& t, const Identifier& property)
{
  // Save the property by in userSettings by its canonical name.
  const String& tType = t.getType().toString();
  DBG("ValueTree " + tType + ", property " + property.toString() + " changed.");

  auto value = t.getProperty(property);
  DBG("-> value = " + value.toString());
  
  //auto siblings = getSiblingsOfSameType(t);
  
  /*
  appProperties_.getUserSettings()
    ->setValue(getCanonicalPropertyName(t, property), value);
  */
}
