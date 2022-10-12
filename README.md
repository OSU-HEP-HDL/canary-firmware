# canary-software

This is the software to operate a Canary.  
Refer to the [Canary Wiki](https://gitlab.cern.ch/guescini/canary/-/wikis/home) for additional information and instructions.

## scripts
- **PCPost.py**: use a PC to read the serial output from the Canary and post the data to an MQTT server. This is useful when the Canary cannot access a wi-fi nework.
- **readSerial.py**: read the serial output and print it to screen.

## sleepMeasurePostRepeat
This is the Arduino sketch to be flashed on the Canary. To configure the Canary edit `config.h`. Do not edit the rest of the code.

## Dependencies
You will need to install Vagrant and Ansible

* Mac OS
```
  brew install vagrant ansible
```

# To get started these are some basic Vagrant Commands
```
vagrant up # this command will start the virtual machine
vagrant ssh # this will allow you to log into the machine. Your files will be avalaible at /vagrant
vagrant provision # this will allow you to re-provision the machine if you need to make changes to the ansible file
vagrant halt # this will turn the machine off 
vagrant destroy # this will delete the machine 
```

You can also use a docker envrionment
```
vagrant up --provider docker
```
When you execute 
Ansible is used to configure the environment. 

