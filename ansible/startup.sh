#!/bin/bash
arduino-cli config init --additional-urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json --overwrite
arduino-cli core update-index
arduino-cli core install esp32:esp32
arduino-cli board listall
arduino-cli completion bash > arduino-cli.sh
sudo mv arduino-cli.sh /etc/bash_completion.d/
arduino-cli lib update-index
arduino-cli lib install ArduinoJson



