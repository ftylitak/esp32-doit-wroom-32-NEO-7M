/**
 * The sketch is for communication between serial device and the retransmittion of the date via Bluetooth. With u-blox NEO-7M in the case as the serial device.
 *
 * u-blox NEO-7M - Arduino Mega
 * VCC - 3V
 * RX - TX2
 * TX - RX2
 * GND - GND
 */
 
#include "BluetoothSerial.h"

#define PC_BAUDRATE     9600
#define GPS_BAUDRATE    9600

BluetoothSerial SerialBT;
HardwareSerial Serial3(2);
String str;

void setup()
{
    Serial.begin(PC_BAUDRATE);
    Serial3.begin(GPS_BAUDRATE, SERIAL_8N1, 16, 17);
    SerialBT.begin("ESP32");
    
    changeFrequency();

    Serial.print("All ready");
}

// If there is a data from the receiver, read it and send to the PC or vice versa
void loop()
{
    if (Serial3.available())
    {
        str = Serial3.readStringUntil('\n');
        str += '\n';
          
        SerialBT.print(str);
    }
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
}
