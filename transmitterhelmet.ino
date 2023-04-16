// transmitter.pde
//
// Simple example of how to use VirtualWire to transmit messages
// Implements a simplex (one-way) transmitter with an TX-C1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: transmitter.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>

const int led_pin = 11;
const int transmit_pin = 12;
const int receive_pin = 2;
const int transmit_en_pin = 3;
#define ctsPin 2 
int ledPin = 10;
int pulse=0;
int rate=0;
int led=13;
int count=0;
int c=0;
int t1=0,t2=0;
int d=0;

void authenticate()
{
    for(int i=0;i>=0;i++) 
     {
     c=0;
            while (digitalRead(ctsPin)== HIGH)
        {
          c=1;
        }
           if(c==1)
           count++;
           //t2=millis();
       if(count==1)
          {
            t1=millis();
          }
          
       if(count==3)
         {
            t2=millis();
           if((t2-t1)>3000)
            {
             //t2=t1=0;
           count=0;
           Serial.print("tap again");
            
            }
          else
          {
            count=0;
           digitalWrite(ledPin,1);
           Serial.print("authenticated");
           transmit();
           delay(1000);
           digitalWrite(ledPin,0);
           break;
            
          }
           //t1=t2=0;
        }
        }
}
void setup()
{
    // Initialise the IO and ISR
    Serial.begin(9600);
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);       // Bits per sec
    pinMode(led_pin, OUTPUT);
     pinMode(pulse,INPUT);
  pinMode(led,OUTPUT);
   pinMode(ledPin, OUTPUT);
       pinMode(ctsPin, INPUT);
       authenticate();
}

byte count1 = 1;
byte count2=1;
void loop()
{
    rate=analogRead(pulse);
    Serial.println(rate);
    if(rate>900&&rate<1000)
    {Serial.println("HUMAN");
    c=0;
    if(d=0)
      transmit();
    d++;
    }
    else
   {
    while(analogRead(pulse)<900&&c<=7) 
    {
      digitalWrite(led,HIGH);
      delay(500);
      digitalWrite(led,LOW);
      delay(500);
      Serial.println(rate); 
      c++;   
    }
   if(c>=7)
   {transmitstop();
    authenticate();
   }
   }
    delay(20);  
}


void transmit()
{
  char *code="HELLOswitchon";
  //char msg[7] = {'s','w','i','t','h','o','n'};

  //msg[6] = count1;
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t*)code,strlen(code));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  //for(int i=0;i<7;i++)
  //{
    //Serial.print(msg[i]);
  //}
  Serial.println("start");
  delay(1000);
  count1 = count1 + 1;
}
void transmitstop()
{
  d=0;
  char msg[7] = {'s','w','i','t','h','o','f'};

  msg[6] = count2;
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 7);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  for(int i=0;i<7;i++)
  {
    Serial.print(msg[i]);
  }
  Serial.println("stop");
  delay(1000);
  count2 = count2 + 1;
}
