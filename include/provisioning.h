#ifndef provisioning_h
#define provisioning_h

#include "constants.h"
#include "WiFiProv.h"
#include "WiFi.h"


void Provision();
void SysProvEvent(arduino_event_t *sys_event);

#endif