/*
* @file DFRobot_Gesture.cpp
* @brief DFRobot_Gesture.cpp   3D Gesture Sensor-mini Library file
*
*  DFRobot_Gesture.cpp 
*  Read gesture recognition and sensor data processing
* 
* @author leiwu(lei.wu@dfrobot.com)
* @version  V1.0
* @date  2015-12-11
*/

 #include <Arduino.h>
 #include "DFRobot_Gesture.h"
 #include <Wire.h>

typedef unsigned char uint8_t;
typedef unsigned long int uint32_t;
typedef unsigned int uint16_t;
static uint8_t AirWheelActivePrevious = 0;   // AirWheel status in the previous run
static int16_t AirWheelValuePrevious=0;                 // AirWheel counter value each time that the flag in the SystemInfo goes from 0 to 1
static int16_t AirWheelDiff = 0; 

unsigned char *cRecData=md.buf;
union data md;

void DFRobot_Gesture::I2C1_MasterRead( uint8_t *pdata,uint8_t reclength,uint16_t address)
{
	unsigned char i=0;
	Wire.requestFrom(address,reclength);    // request 6 bytes from slave device #2

	while(i<reclength)
	{
		while (Wire.available())   // slave may send less than requested
		{
			*pdata = Wire.read(); // receive a byte as character
			pdata++;
			i++;
		}
			delay(1);
	}
}
uint8_t DFRobot_Gesture::mgcProcMsg(void)
{
     // bits 0 to 4 must be set in the StreamOutputMask to have valid data to read
   uint16_t streamOutRequired = (STREAMOUT_DSPINFO | STREAMOUT_GESTUREINFO | STREAMOUT_TOUCHINFO | STREAMOUT_AIRWHEELINFO | STREAMOUT_XYZPOSITION);

    uint8_t retVal = GI_NOGESTURE;


    if(md.header.id != MSGID_SENSORDATAOUT)
        return GI_NOGESTURE;

    if(md.header.size < 22 )  // message too short for our sensor data configuration
        return GI_NOGESTURE;              //DSP(2)+Gesture(4)+Touch(4)+AirWheel(2)+XYZPosition(6)+NoisePower(4)= 22bytes

    // ok, we got a sensor data message. Check that the 5 first bits of the StreamOutputMask are set to indicate valid data are present
    if((md.sensorData.streamingOutputMask & streamOutRequired) == streamOutRequired) {

        uint32_t TouchInfo = md.sensorData.touchInfo;
        uint8_t AirWheelActive = (md.sensorData.systemInfo & SI_AIRWHEELVALID) != 0; // AirWheel is active and valid if bit1 of SystemInfo is set
        int16_t AirWheelValueNew = md.sensorData.airWheelCounter;

        /* FLICK DETECTION */
	retVal = md.sensorData.gestureInfo & 0xFF; // keep only the first byte (b0..b7) that gives the gesture information (in DECIMAL)

        /* TAP DETECTION */
        if(TouchInfo & 1<<BITSHIFT_TAP_SOUTH ) {
            retVal = GI_TAP_SOUTH;
        }
        else if(TouchInfo & 1<<BITSHIFT_TAP_WEST) {
            retVal = GI_TAP_WEST;
        }
        else if(TouchInfo & 1<<BITSHIFT_TAP_NORTH) {
            retVal = GI_TAP_NORTH;
        }
        else if(TouchInfo & 1<<BITSHIFT_TAP_EAST) {
            retVal = GI_TAP_EAST;
        }
        else if(TouchInfo & 1<<BITSHIFT_TAP_CENTER) {
            retVal = GI_TAP_CENTER;
        }
        else {}

        /* AIRWHEEL DETECTION */
        //store the airwheel counter when the airwheel is started
        if (AirWheelActive && !AirWheelActivePrevious)
        {
            AirWheelValuePrevious = md.sensorData.airWheelCounter;
        }
        else if (AirWheelActive)
        {
            if( AirWheelValuePrevious < 64 && AirWheelValueNew > 192 ){
                    // "crossing zero point" happened
                    AirWheelDiff += ( (AirWheelValueNew-256) - AirWheelValuePrevious);
            }
            else if( AirWheelValuePrevious > 192 && AirWheelValueNew < 64 ){
                    // "crossing zero point" happened
                    AirWheelDiff += ( (AirWheelValueNew+256) - AirWheelValuePrevious);
            }
            else{
                    AirWheelDiff += AirWheelValueNew - AirWheelValuePrevious ;
            }

            if (AirWheelDiff >= 32)
            {
                AirWheelDiff=0;
                retVal = GI_AIRWHEEL_CW;
            }
            else if (AirWheelDiff <= -32)
            {
                AirWheelDiff=0;
                retVal = GI_AIRWHEEL_CCW;
            }
            else{}
        }
        AirWheelActivePrevious = AirWheelActive;    // save the status for the next run
        AirWheelValuePrevious = AirWheelValueNew;
    }
    return retVal;
}
	

/******************************************************************************
  Copyright (C) <2015>  <Wulei>
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  Contact: lei.wu@dfrobot.com
 ******************************************************************************/