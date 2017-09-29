# Tiles Boilerplate Code

This code is meant to be shared among [Tiles](http://tilestoolkit.io)-related projects. 

Based on the code created by Theo Hyvon for the [Anyboard](http://anyboardgames.co) project 

I reccommend to use Microsoft Visual Studio Code with Arduino plugin as IDE

The code is released under Apache 2.0 license.
Simone Mora (simonem@ntnu.no). 5-9-2017 

## Setup
* Install Arduino
* Install RFDUINO package for Arduino
* Copy the content of /libraries into Arduino library folder
* Install Ms Visual Studio Code + Arduino plugin (optional) 
* Upload the code (boilerplate.ino) to a RFDUINO board 

## Data Primitives

This code allows you to exchange data via BLE with a set of sensors and actuator connected to a RFDUINO board. Data is packaged in so-called *data primitives*, composed by the name of the primitive plus two optional parameters. 

A data primitive is exchanged between RFDUINO and a BLE Client using UTF-8 comma-separated strings; e.g. *primitive_name[,parameter1][,parameter2]*  

A data primtive containing an event triggered from a sensor (e.g. accelerometer) is called *input primitive*; e.g. *"tap,single"*. A data primitive containing a command send to an actuator (e.g. motor) is called *output primitive*; e.g. *"led,blink,red"*.

## List of sensors and actuators
These are the electronic parts for which data primitives are available

### Input
* ADXL345 Accelerometer
* LSM9DS0 IMU
* CAP1188 Touch Sensor
* Momentary pushbutton (soon)

### Output
* RGB LED, common anode or common catode
* NeoPixel LEDs
* 8X8 Dot Matrix based on HT16K33
* Vibration motor driven by analogic circuit
* Vibration motor driven by DRV2605 IC

## Protocol

### Sensor
|SenderID|Name|P1|P2|Device|Note|
|--------|----|--|--|------|----|
|Tile_XX|tap|single,double||ADXL345,LSM9DS0||
|Tile_XX|shake|||ADXL345,LSM9DS0||
|Tile_XX|tilt|||ADXL345,LSM9DS0||
|Tile_XX|rotation|clockwise,counterclock||LSM9DS0|
|Tile_XX|touched|1,2,3,4||CAP1188|ID of the pin touched in P1|

### Feedbacks
|ReceiverID|Name|P1|P2|Device|Note|
|----------|----|--|--|------|----|
|          |led |off||RGB,NEOPIXEL||
|          |led |on |red,green,blue,white|RGB,NEOPIXEL||
|          |led |blink |red,green,blue,white|NEOPIXEL||
|          |led |fade |red,green,blue,white|NEOPIXEL||
|          |matrix|off||8X8 Matrix||
|          |matrix|gazing||8X8 Matrix||
|          |matrix|dollar,happy1,x,puzzled,sad1,sad2,sad3,||8X8 Matrix||
|          |haptic|short,long||Vibration motor (analog)||
|          |haptic|[ID]]||DRV2605| Feedback pattern ID, see page 57-58 of the [datasheet](http://www.ti.com/lit/ds/symlink/drv2605.pdf) |

##ToDo
- add hex color handling