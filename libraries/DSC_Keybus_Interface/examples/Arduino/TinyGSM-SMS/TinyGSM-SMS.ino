/*
 *  TinyGSM SMS Notification 1.0 (Arduino)
 *
 *  Processes the security system status and demonstrates how to send an SMS text message when the status has
 *  changed.  This example sends SMS text messages via a TinyGSM-compatible SIM800L module which is connected
 *  onto Arduino board. Make sure that Micro-SIM card have PIN Code turned off (disable SIM Lock from phone).
 *
 *  Usage:
 *    1. Install the TinyGSM library, available in the Arduino IDE Library Manager and the Platform.io Library
 *       Registry: https://github.com/vshymanskyy/TinyGSM
 *    2. Set the destination phone numbers in the sketch settings.
 *
 *  Release notes:
 *    1.0 - Just converted from ESP32 to Arduino. Tested with SIM800L module.
 *
 *  Wiring:
 *      DSC Aux(+) --- Arduino Vin pin
 *
 *      DSC Aux(-) --- Arduino Ground
 *
 *                                         +--- dscClockPin (Arduino Uno: 2,3)
 *      DSC Yellow --- 15k ohm resistor ---|
 *                                         +--- 10k ohm resistor --- Ground
 *
 *                                         +--- dscReadPin (Arduino Uno: 2-12)
 *      DSC Green ---- 15k ohm resistor ---|
 *                                         +--- 10k ohm resistor --- Ground
 *
 *      Classic series only, PGM configured for PC-16 output:
 *      DSC PGM ---+-- 1k ohm resistor --- DSC Aux(+)
 *                 |
 *                 |                       +--- dscPC16Pin (Arduino Uno: 2-12)
 *                 +-- 15k ohm resistor ---|
 *                                         +--- 10k ohm resistor --- Ground
 *
 *
 *      Connecting SIM800L module with Arduino Uno:
 *      SIM800 RX -+-- 5.6k ohm resistor -- SIM800TxPin (Arduino Uno: 2-12)
 *                 |
 *                 |
 *                 +-- 10k ohm resistor -- Arduino Uno Ground
 *
 *      SIM800 TX ---- SIM800RxPin (Arduino Uno: 2-12)
 *
 *      SIM800 GND --- Arduino Uno Ground
 *      
 *      SIM800 Vcc --- (+) 3.7 - 4.4V power supply which can supply burst current of 2A
 *      (you can use LM2596 Buck converter set to output 4.2V and connected to Bell+ and Aux-)
 *
 *      Virtual keypad (optional):
 *      DSC Green ---- NPN collector --\
 *                                      |-- NPN base --- 1k ohm resistor --- dscWritePin (Arduino Uno: 2-12)
 *            Ground --- NPN emitter --/
 *            
 *
 *  Virtual keypad uses an NPN transistor to pull the data line low - most small signal NPN transistors should
 *  be suitable, for example:
 *   -- 2N3904
 *   -- BC547, BC548, BC549
 *
 *  Issues and (especially) pull requests are welcome:
 *  https://github.com/taligentx/dscKeybusInterface
 *  
 *  Based on TinyGSM-SMS example for ESP32 by jvitkauskas: https://github.com/jvitkauskas
 *
 *  This example code is in the public domain.
 */

// DSC Classic series: uncomment for PC1500/PC1550 support (requires PC16-OUT configuration per README.md)
//#define dscClassicSeries

// Configures GSM modem model. Must be done before including TinyGsmClient library.
#define TINY_GSM_MODEM_SIM800
#include <SoftwareSerial.h>
#include <TinyGsmClient.h>
#include <dscKeybusInterface.h>

// Settings
const char* sendToPhoneNumbers[] = {
  "+1234567890",
  "+2345678901"
};

#define phone_number_count (sizeof (sendToPhoneNumbers) / sizeof (const char *))

// Configures the Keybus interface with the specified pins.
#define dscClockPin 3  // Arduino Uno hardware interrupt pin: 2,3
#define dscPC16Pin  4  // DSC Classic Series only, Arduino Uno: 2-12
#define dscReadPin  5  // Arduino Uno: 2-12
#define SIM800RxPin 9  // Arduino Uno: 2-12
#define SIM800TxPin 10  // Arduino Uno: 2-12

// Settings
// NOTE: I kept getting "Keybus buffer overflow" when sketch was sending multiple messages at once (example: AC power trouble and trouble status ON)
bool notifyOnPartitionAlarm = true;
bool notifyOnPowerTroubles = false;
bool notifyOnKeypadAlarm = false;
bool notifyOnDisArming = false;
bool notifyOnTrouble = true;

// Initialize components
SoftwareSerial serialSIM800(SIM800RxPin,SIM800TxPin);
#ifndef dscClassicSeries
dscKeybusInterface dsc(dscClockPin, dscReadPin);
#else
dscClassicInterface dsc(dscClockPin, dscReadPin, dscPC16Pin);
#endif
TinyGsm modem(serialSIM800);

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println();
  Serial.println();

  serialSIM800.begin(9600);

  while (!modem.isNetworkConnected()) {
    Serial.print(F("GSM..."));
    while (!modem.restart()) {
      Serial.print(".");
    }
    Serial.println();

    Serial.print(F("Waiting for network..."));
    if (modem.waitForNetwork(600000L) && modem.isNetworkConnected()) {
      Serial.println(F("connected."));
    }
    else {
      Serial.println(F("connection error."));
    }
  }

  // Starts the Keybus interface
  dsc.begin();
  Serial.println(F("DSC Keybus Interface is online."));
}


void loop() {
  modem.maintain();

  dsc.loop();

  if (dsc.statusChanged) {      // Checks if the security system status has changed
    dsc.statusChanged = false;  // Reset the status tracking flag

    // If the Keybus data buffer is exceeded, the sketch is too busy to process all Keybus commands.  Call
    // loop() more often, or increase dscBufferSize in the library: src/dscKeybusInterface.h
    if (dsc.bufferOverflow) {
      Serial.println(F("Keybus buffer overflow"));
      dsc.bufferOverflow = false;
    }

    // Checks status per partition
    for (byte partition = 0; partition < dscPartitions; partition++) {

      // Skips processing if the partition is disabled or in installer programming
      if (dsc.disabled[partition]) continue;

      // Checks alarm triggered status
      if (notifyOnPartitionAlarm) {
        if (dsc.alarmChanged[partition]) {
          dsc.alarmChanged[partition] = false;  // Resets the partition alarm status flag

          if (dsc.alarm[partition]) {
            char messageContent[19] = "Alarm: Partition ";
            appendPartition(partition, messageContent);  // Appends the message with the partition number
            sendMessage(messageContent);
          }
          else {
            char messageContent[34] = "Disarmed after alarm: Partition ";
            appendPartition(partition, messageContent);  // Appends the message with the partition number
            sendMessage(messageContent);
          }
        }

        if (dsc.fireChanged[partition]) {
          dsc.fireChanged[partition] = false;  // Resets the fire status flag

          if (dsc.fire[partition]) {
            char messageContent[24] = "Fire alarm: Partition ";
            appendPartition(partition, messageContent);  // Appends the message with the partition number
            sendMessage(messageContent);
          }
          else {
            char messageContent[33] = "Fire alarm restored: Partition ";
            appendPartition(partition, messageContent);  // Appends the message with the partition number
            sendMessage(messageContent);
          }
        }
      }
      
      // Publishes armed/disarmed status
      if (notifyOnDisArming) {
        if (dsc.armedChanged[partition]) {
          if (dsc.armed[partition]) {
            // Night armed away
            if (dsc.armedAway[partition] && dsc.noEntryDelay[partition]) {
              char messageContent[33] = "Armed away - night: Partition: ";
              appendPartition(partition, messageContent);  // Appends the message with the partition number
              sendMessage(messageContent);
            }

            // Armed away
            else if (dsc.armedAway[partition]) {
              char messageContent[25] = "Armed away: Partition: ";
              appendPartition(partition, messageContent);  // Appends the message with the partition number
              sendMessage(messageContent);
            }

            // Night armed stay
            else if (dsc.armedStay[partition] && dsc.noEntryDelay[partition]) {
              char messageContent[33] = "Armed stay - night: Partition: ";
              appendPartition(partition, messageContent);  // Appends the message with the partition number
              sendMessage(messageContent);
            }

            // Armed stay
            else if (dsc.armedStay[partition]) {
              char messageContent[25] = "Armed stay: Partition: ";
              appendPartition(partition, messageContent);  // Appends the message with the partition number
              sendMessage(messageContent);
            }
          }

          // Disarmed
          else {
            char messageContent[23] = "Disarmed: Partition: ";
            appendPartition(partition, messageContent);  // Appends the message with the partition number
            sendMessage(messageContent);
          }
          dsc.armedChanged[partition] = false;  // Resets the partition armed status flag
        }
      }
    }
    
    // Checks trouble status
    if (notifyOnTrouble) {
      if (dsc.troubleChanged) {
        dsc.troubleChanged = false;  // Resets the trouble status flag
        if (dsc.trouble) sendMessage("Trouble status on");
        else sendMessage("Trouble status restored");
      }
    }
    // Checks for AC power status
    if (notifyOnPowerTroubles) {
      if (dsc.powerChanged) {
        dsc.powerChanged = false;  // Resets the battery trouble status flag
        if (dsc.powerTrouble) sendMessage("AC power trouble");
        else sendMessage("AC power restored");
      }
    }
    // Checks panel battery status
    if (dsc.batteryChanged) {
      dsc.batteryChanged = false;  // Resets the battery trouble status flag
      if (dsc.batteryTrouble) sendMessage("Panel battery trouble");
      else sendMessage("Panel battery restored");
    }

    if (notifyOnKeypadAlarm) {
      // Checks for keypad fire alarm status
      if (dsc.keypadFireAlarm) {
        dsc.keypadFireAlarm = false;  // Resets the keypad fire alarm status flag
        sendMessage("Keypad Fire alarm");
      }

      // Checks for keypad aux auxiliary alarm status
      if (dsc.keypadAuxAlarm) {
        dsc.keypadAuxAlarm = false;  // Resets the keypad auxiliary alarm status flag
        sendMessage("Keypad Aux alarm");
      }

      // Checks for keypad panic alarm status
      if (dsc.keypadPanicAlarm) {
        dsc.keypadPanicAlarm = false;  // Resets the keypad panic alarm status flag
        sendMessage("Keypad Panic alarm");
      }
    }
  }
}

bool sendMessage(const char* messageContent) {
  bool result = true;

  for (int i = 0; i < phone_number_count; i++) {
     result &= modem.sendSMS(sendToPhoneNumbers[i], messageContent);
  }

  return result;
}

void appendPartition(byte sourceNumber, char* pushMessage) {
  char partitionNumber[2];
  itoa(sourceNumber + 1, partitionNumber, 10);
  strcat(pushMessage, partitionNumber);
}
