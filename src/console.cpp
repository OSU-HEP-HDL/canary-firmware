#include "console.h"
#include "constants.h"
Console console;

void setupConsole()
{
    // You can change the console prompt before calling begin(). By default it is "ESP32>"
    console.setPrompt("MyConsole> ");

    // You can change the baud rate and pin numbers similar to Serial.begin() here.
    console.begin(115200);

    // Register builtin commands like 'reboot', 'version', or 'meminfo'
    console.registerSystemCommands();

    // Register our own command
    // First argument is the name with which the command can be executed, second argument is the function to execute and third one is the description shown in help command.
    console.registerCommand(ConsoleCommand("led", &led, "Turn the LED on or off"));

    // When console is in use, we can not use Serial.print but you can use printf to output text
    printf("\n\nWelcome to ESP32Console example. Try out typing 'led off' and 'led on' (without quotes) or see 'help' for all commands.");
}
