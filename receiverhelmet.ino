// receiver.pde
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;
int D4=7,D3=6,D2=5,D1=4;
char check[7];

void setup()
{
    delay(1000);
    Serial.begin(9600);	// Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running

    pinMode(led_pin, OUTPUT);
    pinMode(D1,OUTPUT);
    pinMode(D2,OUTPUT);
    pinMode(D3,OUTPUT);
    pinMode(D4,OUTPUT);
}

void loop()
{
   uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
  String msg,msg1;
  char message1[10],message2[10],message[20];
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
 int j=0,l=0,k=0;

        digitalWrite(led_pin, HIGH); // Flash a light to show received good message
  // Message with a good checksum received, dump it.
  Serial.print("Got: ");
  for(int q=0;q<buflen;q++)
    {
      message[q]=(char)buf[q];
    }
  for(int i=0;i<5;i++)
  {
    message1[j]=message[i];
    j++;
  }
  message1[j]='\0';
 msg=message1;
 Serial.print(msg);
 Serial.print(' ');
 for(k=j;k<11;k++)
 {
   message2[l]=message[k];
    l++;
 }
 message2[l]='\0';
 msg1=message2;
 //Serial.print(msg1);
 Serial.println();
if(msg.equals("HELLO")==1)
 {Serial.println("RECEIVED");
if(msg1.equals("switch")==1)
 {Serial.println("IGNITION ON");
   digitalWrite(D1,1);
   digitalWrite(D2,0);  
   digitalWrite(D3,0);
   digitalWrite(D4,0);   
 }
  else if(msg1.equals("switoh")==1)
  {Serial.println("IGNITION OFF");
  digitalWrite(D1,0);
  digitalWrite(D2,0);  
  digitalWrite(D3,0);
  digitalWrite(D4,0); 
 }
 }
 else
 Serial.println("NOT RECEIVED");
 delay(500);
} 
}
