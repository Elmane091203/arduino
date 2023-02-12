/*
*****************************************************************************
@file         Deneyap_DokunmatikTusTakimi.h
@mainpage     Deneyap Keypad Arduino library header file
@version      v1.0.1
@date         August 19, 2022
@brief        This file contains all function prototypes and macros
              for Deneyap Keypad Arduino library
*****************************************************************************
*/
  
#ifndef __KEYPAD_H
#define __KEYPAD_H

#include <Wire.h>
#include <Arduino.h>
//#include <deneyap.h>

/*
#define I2C_SLV_ADDR_DEFAULT    (uint8_t)0x0E 
#define I2C_SLV_ADDR_ALT1       (uint8_t)0x4C
#define I2C_SLV_ADDR_ALT2       (uint8_t)(I2C_SLV_ADDR_DEFAULT + 2)
#define I2C_SLV_ADDR_ALT3       (uint8_t)(I2C_SLV_ADDR_DEFAULT + 3)
*/

#define DATA_BUFFER_SIZE        2     // in Byte (max data size)


typedef struct                        // Data packet (protocol) created by master
{																			// for I2C data exchange process 
  uint8_t command       : 3;
  uint8_t dataSize      : 2;
  uint8_t data[DATA_BUFFER_SIZE];
} Keypad_DataPacket_TypeDef;

enum Keypad_packetCommands                   // Commands in data packet (protocol)
{
  KEYPAD_READ = (uint8_t)0x00,
  KEYPAD_CHANGE_ADDR,
  KEYPAD_REQUEST_FW_VERSION,
};

class Keypad
{ 
  public:
    /* Check device status */
    bool begin(uint8_t address , TwoWire &port = Wire); 
    bool isConnected();                                                       
    uint16_t getFwVersion();                                                  
    bool setI2Caddress(uint8_t newAddress);                                      

    /* Functions for data manipulation */
    uint8_t KeypadRead(void);
  
  private:
    TwoWire* _i2cPort;                // Port selection (0 or 1)
    uint8_t _i2cAddress;              // Device I2C address
    Keypad_DataPacket_TypeDef _dataPacket;   // Struct to transfer data over I2C interface

    /* I2C data transaction functions */
    uint8_t I2C_ReadData8bit(Keypad_DataPacket_TypeDef* dataPacket);
    uint16_t I2C_ReadData16bit(Keypad_DataPacket_TypeDef* dataPacket);
    bool I2C_SendDataPacket(Keypad_DataPacket_TypeDef* dataPacket);
};

#endif /* __KEYPAD_H */
