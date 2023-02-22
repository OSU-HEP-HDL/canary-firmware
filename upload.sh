#!/bin/bash
# specify the first argument as the port
if [ -z "$1" ]
  then
    echo "No argument supplied. Please specify the port."
    exit 1
fi

arduino-cli upload -b esp32:esp32:featheresp32 -p $1 --input-dir ./sleepMeasurePostRepeat/build/

