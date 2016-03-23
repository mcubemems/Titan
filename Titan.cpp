#include "Titan.h"
#include <Arduino.h>
#include <inttypes.h>

#define MAX_BTCMDLEN 20
#define BUFFER 16

boolean Debug = false;
boolean debugAscii = false;

void Titan::init()
{
	Serial.println("Titan Init");
	Serial1.begin(9600);
}

bool Titan::checkAscii(uint8_t thisChar)
{
	// analyze what was sent:
	
	if (isAlphaNumeric(thisChar)) 
	{
		if (debugAscii) Serial.println("it's alphanumeric");
	}
	if (isAlpha(thisChar)) 
	{
		if (debugAscii) Serial.println("it's alphabetic");
	}
	if (isAscii(thisChar)) 
	{
		if (debugAscii) Serial.println("it's ASCII");
	}
	if (isWhitespace(thisChar)) 
	{
		if (debugAscii) Serial.println("it's whitespace");
	}
	if (isControl(thisChar)) 
	{
		if (debugAscii) Serial.println("it's a control character");
	}
	if (isDigit(thisChar)) 
	{
		if (debugAscii) Serial.println("it's a numeric digit");
	}
	if (isGraph(thisChar)) 
	{
		if (debugAscii) Serial.println("it's a printable character that's not whitespace");
	}
	if (isLowerCase(thisChar)) 
	{
		if (debugAscii) Serial.println("it's lower case");
	}
	if (isPrintable(thisChar)) 
	{
		if (debugAscii) Serial.println("it's printable");
	}
	if (isPunct(thisChar)) 
	{
		if (debugAscii) Serial.println("it's punctuation");
	}
	if (isSpace(thisChar)) 
	{
		if (debugAscii) Serial.println("it's a space character");
	}
	if (isHexadecimalDigit(thisChar)) 
	{
		if (debugAscii) Serial.println("it's a valid hexadecimaldigit (i.e. 0 - 9, a - F, or A - F)");
		return true;
	}
	if (thisChar == '\r')
	{
		if (debugAscii) Serial.println("it's a Carriage Return character");
		return true;
	}
	if (thisChar == '\n')
	{
		if (debugAscii) Serial.println("it's a New Line character");
		return true;
	}
	return false;
}

void Titan::PrintHex(uint8_t data) // prints 8-bit data in hex with leading zeroes
{
  Serial.print("0x"); 
       
  if (data < 0x10) 
	{
		Serial.print("0");
	} 
    Serial.print(data,HEX); 
    Serial.print(" "); 
}

void Titan::PrintHexByteArray(uint8_t *data, uint8_t length) // prints 8-bit byte array data in hex with leading zeroes
{
     
  for (int i=0; i<length; i++) 
	{ 
	if( i == 0)
		Serial.print("0x");
	
	if (data[i]<0x10) 
	{
		Serial.print("0");
	} 
      Serial.print(data[i],HEX); 
      Serial.print(" "); 
  }
}

void Titan::printHeaderCmd(uint8_t cmdBytes)
{
	//if (Debug) Serial.println("Titan printHeaderCmd()");
	
	if(cmdBytes < 0x10)
	{
		//if (Debug) Serial.println("Wrong Command Header Byte received from BT");
		return;
	}
	
	switch(cmdBytes)
	{
		//PEDOMETER Response
		case  PEDOMETER_CONTROL:  
			Serial.println("PEDOMETER_CONTROL"); 
			break;
		case  PEDOMETER_CONTROL_RESPONSE:  
			Serial.println("PEDOMETER_CONTROL_RESPONSE"); 
			break;
		case  PEDOMETER_RECORD_GET:  
			Serial.println("PEDOMETER_RECORD_GET"); 
			break;
		case  PEDOMETER_STEP_GET:  
			Serial.println("PEDOMETER_STEP_GET"); 
			break;
		case  PEDOMETER_NOTIFICATION_ENABLE:  
			Serial.println("PEDOMETER_NOTIFICATION_ENABLE"); 
			break;		
		case  PEDOMETER_RECORD_GET_RESPONSE:
			Serial.println("PEDOMETER_RECORD_GET_RESPONSE"); 
			break;
		case  PEDOMETER_STEP_GET_RESPONSE:  
			Serial.println("PEDOMETER_STEP_GET_RESPONSE"); 
			break;
		case  PEDOMETER_NOTIFICATION_ENABLE_RESPONSE:  
			Serial.println("PEDOMETER_NOTIFICATION_ENABLE_RESPONSE"); 
			break;
		case  PEDOMETER_NOTIFICATION:  
			Serial.println("PEDOMETER_NOTIFICATION"); 
			break;
			
		//SLEEP MONITOR Response
		case  SLEEP_MONITOR_CONTROL_RESPONSE:  
			Serial.println("SLEEP_MONITOR_CONTROL_RESPONSE"); 
			break;
		case  SLEEP_MONITOR_SENSITIVITY_SET_RESPONSE:  
			Serial.println("SLEEP_MONITOR_SENSITIVITY_SET_RESPONSE"); 
			break;
		case  SLEEP_MONITOR_NOTIFICATION_ENABLE_RESPONSE:  
			Serial.println("SLEEPMONITOR_NOTIFICATION_ENABLE_RESPONSE"); 
			break;	
		case  SLEEP_MONITOR_EVENT_NOTIFICATION:  
			Serial.println("SLEEP_MONITOR_EVENT_NOTIFICATION"); 
			break;
		case  SLEEP_MONITOR_CONTROL:  
			Serial.println("SLEEP_MONITOR_CONTROL"); 
			break;
		case  SLEEP_MONITOR_SENSITIVITY_SET:  
			Serial.println("SLEEP_MONITOR_SENSITIVITY_SET"); 
			break;
		case  SLEEP_MONITOR_NOTIFICATION_ENABLE:  
			Serial.println("SLEEP_MONITOR_NOTIFICATION_ENABLE"); 
			break;		
      
		//Sensor Control	
		case  SENSOR_CONTROL:
			Serial.println("BLE_CONTROL"); 
			break;
		case  SENSOR_CONTROL_RESPONSE:  
			Serial.println("SENSOR_CONTROL_RESPONSE"); 
			break;	
		
		//Reporter control
		case  REPORTER_CONTROL:  
			Serial.println("REPORTER_CONTROL"); 
			break;	
		case  REPORTER_CONTROL_RESPONSE:  
			Serial.println("REPORTER_CONTROL_RESPONSE"); 
			break;

		default:
		 	Serial.print("Header Cmd=");
		 	Serial.println(cmdBytes,HEX);
		 	Serial.println();
			break;
	}
}

void Titan::commandTRANS(uint8_t bCmdHeader, uint8_t* baCmdBytes, uint8_t len)
{
  if (Debug) 
	{	
		Serial.print("Titan commandTRANS() Cmd Header = 0x");
		Serial.println(byte(bCmdHeader), HEX);
		Serial.print("check transmit byte size: ");
		Serial.println(len);
		Serial.print("Transmit Command: ");
	}
		
 	if(baCmdBytes == NULL)
	{
		Serial.println("Null Command Bytes sent to BT");
		return;
	}
	if(bCmdHeader < 16)
	{
		Serial.println("Wrong Command Header sent to BT");
		return;
	}

  Serial1.write(baCmdBytes, len);
	delayMicroseconds(100); // pauses for 100 microseconds  
  }