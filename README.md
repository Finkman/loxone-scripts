# Loxone-Pico-C-Scripts
Pico-C Scripts for Loxone

## Yamaha Status
 It connects to a Yamaha AV receiver and gets the current device status.

 ### Inputs
 - *TI1* Set the ip-address of the avr device
 - *AI1* Enable or disable the script


 ### Outputs
 - *AQ1* Status of the script (See below)
 - *AQ2* Power State of the Device. 1 if powered, 0 otherwise
 - *AQ3* Reads 1 if the output mode is 2ch Stereo, 0 otherwise
 - *AQ4* Reads 1 if the selected input is hdmi2, 0 otherwise
