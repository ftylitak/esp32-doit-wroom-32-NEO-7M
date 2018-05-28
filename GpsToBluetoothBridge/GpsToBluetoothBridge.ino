/**
 * The sketch is for communication between PC and any other device using Arduino Mega. With u-blox NEO-7M in the case.
 *
 * u-blox NEO-7M - Arduino Mega
 * VCC - 5V
 * RX - TX3
 * TX - RX3
 * GND - GND
 */
 
#include "BluetoothSerial.h"

#define PC_BAUDRATE     9600
#define GPS_BAUDRATE    9600

BluetoothSerial SerialBT;
HardwareSerial Serial3(2);

unsigned char buffer[256];

void setup()
{
    Serial.begin(PC_BAUDRATE);
    Serial3.begin(GPS_BAUDRATE);
    SerialBT.begin("ESP32");
    
    changeFrequency();
}

// If there is a data from the receiver, read it and send to the PC or vice versa
void loop()
{
  int pos = 0;
  String str;

    if (Serial3.available())
    {
        //pos = Serial3.readBytesUntil('\n', buffer, 256);
        str = Serial3.readStringUntil('\n');
        str += '\n';
      
//        if(pos < 255) 
//        {
//          buffer[pos-2] = (char) lf;
//          //buffer[pos-2] = (char) 13;
////          buffer[pos-1] = (char) 10;
//        }
          
        SerialBT.print(str);
        //SerialBT.write(buffer, pos);
        //Serial.write(Serial3.read());
    }

//    if (SerialBT.available())
//    {
//        Serial3.write(SerialBT.read());
//    }
}

// Send a packet to the receiver to change frequency to 100 ms
void changeFrequency()
{
    // CFG-RATE packet
    byte packet[] = {
        0xB5, // sync char 1
        0x62, // sync char 2
        0x06, // class
        0x08, // id
        0x06, // length
        0x00, // length
        0x64, // payload
        0x00, // payload
        0x01, // payload
        0x00, // payload
        0x01, // payload
        0x00, // payload
        0x7A, // CK_A
        0x12, // CK_B
    };

    sendPacket(packet, sizeof(packet));
}

// Send the packet specified to the receiver
void sendPacket(byte *packet, byte len)
{
    for (byte i = 0; i < len; i++)
    {
        Serial3.write(packet[i]);
    }

   // printPacket(packet, len);
}

