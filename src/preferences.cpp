#include "constants.h"
#include "myPreferences.h"

Preferences preferences;



void setupPreferences() {
  preferences.begin("esp32", false);
}

