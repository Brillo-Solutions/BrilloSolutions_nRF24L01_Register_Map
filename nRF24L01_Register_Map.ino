/*Written By: Er. Dapinder Singh Virk
  Email ID: brillosolutions@gmail.com
  Version: 1.0.0
  Date: September 24, 2018
  Outputs: Displays power-on-reset values of all nRF24L01+ registers from 00H to 1DH on serial terminal. */

#include <SPI.h>
#define IRQ_pin 2
#define CE_pin 9
#define CSN_pin 10
#define MOSI_pin 11
#define MISO_pin 12
#define SCK_pin 13

byte regVal;
void setup() 
{
  Serial.begin(9600);
  SPI.begin();
  pinMode(CE_pin, OUTPUT);        //  Setting CE pin as output.
  pinMode(CSN_pin, OUTPUT);       //  Setting CSN pin as output.
  pinMode(MOSI_pin, OUTPUT);      //  Setting MOSI pin as output.
  pinMode(MISO_pin, INPUT);       //  Setting MISO pin as input.
  pinMode(SCK_pin, OUTPUT);       //  Setting SCK pin as output.
  digitalWrite(CSN_pin, HIGH);    //  Setting CSN = 1 to make SPI idle.
  digitalWrite(CE_pin, HIGH);
}

void loop() 
{
  for (uint8_t k = 0; k <= 0x1D; k++)
  {
    if (k < 0x18 || k >= 0x1C)
    {
      digitalWrite(CSN_pin, LOW);
      SPI.transfer(k);
      Serial.print(k, HEX);
      Serial.print("H: ");
      regVal = SPI.transfer(0x00);
      Serial.println(regVal, HEX);
      digitalWrite(CSN_pin, HIGH);
      delay(1);
    }
    else
      k += 0x03;
  }
  while(1);
}
