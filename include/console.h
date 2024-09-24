#ifndef CONSOLE_H
#define CONSOLE_H


#include "ESP32Console.h"
#include "constants.h"
static const char* CONSOLE = "Console";

using namespace ESP32Console;
extern Console console;

int led(int argc, char **argv);
void setupConsole();

#endif
