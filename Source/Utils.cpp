/*
  ==============================================================================

    Utils.cpp
    Created: 9 Feb 2020 7:03:25am
    Author:  keith

  ==============================================================================
*/

#include "Utils.h"
// DEBUG
#include "Settings.h"

void syncValueTreeNotifyListeners (const ValueTree& source, ValueTree& destination)
{
  const int numProperties = source.getNumProperties();
  for (int i = 0; i < numProperties; ++i)
  {
    auto propertyName = source.getPropertyName (i);
    
    if (destination.hasProperty (propertyName)) {
      destination.setProperty (propertyName, source.getProperty (propertyName), nullptr);
      destination.sendPropertyChangeMessage(propertyName);
    }
  }

  for (const auto& child : source)
  {
    auto childInDestination = destination.getChild(source.indexOf(child));
    if (childInDestination.isValid()) {
      syncValueTreeNotifyListeners (child, childInDestination);
    } else {
      childInDestination = child.createCopy();
      destination.addChild(childInDestination, source.indexOf(child), nullptr);
    }
  }
}
