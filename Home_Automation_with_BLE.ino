/*
BLE CONTROL

Turn a lamp ,christmas lightand Fan on and off using BLE and a phone o. Android and iOS devices only!

Based off of the BLE LED example written by Intel Corporation and included with the Curie BLE Arduino Library.

*/

 #include <CurieBLE.h>

BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
BLEService homeautomationService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service


//set BLE characteristic
       BLEUnsignedCharCharacteristic switchLampCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
       BLEUnsignedCharCharacteristic switchChristmasLightCharacteristic("19B10010-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
       BLEUnsignedCharCharacteristic switchFanCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int lampPin = 9; // pin to use for the lamp
const int christmaslightPin = 10; // pin to use for the christmaslight
const int FanPin = 7; // pin to use for the fan

 void setup()
{
 // set LED pin to output mode
  pinMode(lampPin, OUTPUT);
  pinMode(christmaslightPin, OUTPUT);
  pinMode(FanPin, OUTPUT);

  // set advertised local name and service UUID:
  blePeripheral.setLocalName("HOME AUTOMATION");
  blePeripheral.setAdvertisedServiceUuid(homeautomationService.uuid());

  // add service and characteristic:
   blePeripheral.addAttribute(homeautomationService);
   blePeripheral.addAttribute(switchLampCharacteristic);
   blePeripheral.addAttribute(switchChristmasLightCharacteristic);
   blePeripheral.addAttribute(switchFanCharacteristic);

   // set the initial value for the characeristic:
    switchLampCharacteristic.setValue(0);
    switchChristmasLightCharacteristic.setValue(0);
    switchFanCharacteristic.setValue(0);

   // begin advertising BLE service:
   blePeripheral.begin();
 }

void loop() 
{
  // listen for BLE peripherals to connect:
 BLECentral central = blePeripheral.central();

 // if a central is connected to peripheral:
  if (central)
  {
   // while the central is still connected to peripheral:
    while (central.connected())
    {
      // if the remote device wrote to the characteristic,
      // use the value to control the Lamp:
      if (switchLampCharacteristic.written())
      {
          // any value other than 0, turn on the Lamp
         if (switchLampCharacteristic.value()) 
         {  
          digitalWrite(lampPin, HIGH);         
         } 
      //else turn the Lamp off
       else 
        {                              
          digitalWrite(lampPin, LOW);         
        }
     }
      // if the remote device wrote to the characteristic,
      // use the value to control the Christmas light:
     if (switchChristmasLightCharacteristic.written())
      {
          // any value other than 0, turn on the ChristmasLight
         if (switchChristmasLightCharacteristic.value()) 
         {  
          digitalWrite( christmaslightPin, HIGH);         
         } 
      //else turn the ChristmasLight off
       else 
        {                              
          digitalWrite( christmaslightPin, LOW);         
        }
     }
      // if the remote device wrote to the characteristic,
      // use the value to control the Fan:
     if (switchFanCharacteristic.written())
      {
          // any value other than 0, turn on the Fan
         if (switchFanCharacteristic.value()) 
         {  
          digitalWrite(FanPin, HIGH);         
         } 
      //else turn the Fan off
       else 
        {                              
          digitalWrite(FanPin, LOW);         
        }
     }
    }
   }
 }




 
