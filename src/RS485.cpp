#include "Arduino.h"

#include <SoftwareSerial.h>
#include <RS485.h>

// RS485 control
#define SERIAL_COMMUNICATION_CONTROL_PIN 5 // Transmission set pin
#define RS485_TX_PIN_VALUE HIGH
#define RS485_RX_PIN_VALUE LOW
#define RX_PIN 14  //D5
#define TX_PIN 12  //D6

SoftwareSerial UartToRS485(RX_PIN, TX_PIN);

uint8_t rs485_buffer[8];
byte readBuffer[15];

int byteSend;

int modbus_crc(uint8_t *pdata, int len)
{
  int crc = 0xFFFF;

  while (len--)
  {
    crc ^= *pdata++;
    for (int i = 0; i < 8; i++)
    {
      if (crc & 1)
        crc = (crc >> 1) ^ 0xA001;
      else
        crc >>= 1;
    }
  }

  return crc;
}

void intitRS485()
{

  pinMode(SERIAL_COMMUNICATION_CONTROL_PIN, OUTPUT);
  digitalWrite(SERIAL_COMMUNICATION_CONTROL_PIN, RS485_RX_PIN_VALUE);
  // set the data rate

  // delay(500);
}

void transmitRS485()
{

  digitalWrite(SERIAL_COMMUNICATION_CONTROL_PIN, RS485_TX_PIN_VALUE); // Now trasmit
  Serial.println("SEND RS485\n");
  UartToRS485.begin(9600, SWSERIAL_8N2);

  rs485_buffer[0] = 254;      // addr
  rs485_buffer[1] = 0x03;     // cmd
  rs485_buffer[2] = 259 >> 8; // reg_addr
  rs485_buffer[3] = (uint8_t)259;
  rs485_buffer[4] = 1 >> 8;     // size
  rs485_buffer[5] = (uint8_t)1; // size

  uint16_t crc16 = modbus_crc((uint8_t *)rs485_buffer, 6);

  rs485_buffer[6] = (uint8_t)crc16;
  rs485_buffer[7] = (uint8_t)(crc16 >> 8);

  UartToRS485.write(0xFE); // Send message
  UartToRS485.write(0x03);
  UartToRS485.write(0x03);
  UartToRS485.write(0x00);
  UartToRS485.write(0x00);
  UartToRS485.write(0x05);
  UartToRS485.write(0x91);
  UartToRS485.write(0x82);
}

void listeningАnswer()
{
  digitalWrite(SERIAL_COMMUNICATION_CONTROL_PIN, RS485_RX_PIN_VALUE); // Disable RS485 Transmit
  delay(100);


  if (UartToRS485.available() > 0)
  {
    UartToRS485.read(readBuffer,15);
  }
  int i=0;
  while (i<=14)
  {
    Serial.print(readBuffer[i], HEX);
    //Serial.println();
    i++;
  }
  



  delay(5000);
}
