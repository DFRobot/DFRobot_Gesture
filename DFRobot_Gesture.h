/*
* @file DFRobot_Gesture.h
* @brief DFRobot_Gesture.h   3D Gesture Sensor-mini Library file
*
*  DFRobot_Gesture.h 
*  Gesture recognition parameters of the chip set
* 
* @author leiwu(lei.wu@dfrobot.com)
* @version  V1.0
* @date  2015-12-11
*/

#ifndef DFRobot_Gesture_h
#define DFRobot_Gesture_h

#include <Arduino.h>





/** GENERAL DEFINES *******************************************************/
#define MSGID_SENSORDATAOUT 0x91
//StreamingOutput Mask (DataOutputConfig), bitmask, 2Bytes
#define STREAMOUT_DSPINFO      0x0001               //b0 : DSPInfo field
#define STREAMOUT_GESTUREINFO  0x0002               //b1 : GestureInfo field
#define STREAMOUT_TOUCHINFO    0x0004               //b2 : TouchInfo field
#define STREAMOUT_AIRWHEELINFO 0x0008               //b3 : AirWheelInfo field
#define STREAMOUT_XYZPOSITION  0x0010               //b4 : XYZPosition field

//SytemInfo Mask, bitmask, 1Byte
#define SI_POSVALID         0x01                    //b0 : PositionValid
#define SI_AIRWHEELVALID    0x02                    //b1 : AirWheelValid

//Tap Bitmask
#define BITSHIFT_TAP_SOUTH       5
#define BITSHIFT_TAP_WEST        6
#define BITSHIFT_TAP_NORTH       7
#define BITSHIFT_TAP_EAST        8
#define BITSHIFT_TAP_CENTER      9

//Gesture Info (decimal number)
#define GI_NOGESTURE       0
#define GI_GARBAGEMOD      1
#define GI_FLICK_R         2
#define GI_FLICK_L         3
#define GI_FLICK_U         4
#define GI_FLICK_D         5

//Tap Info
#define GI_TAP_WEST         50
#define GI_TAP_EAST         51
#define GI_TAP_SOUTH        52
#define GI_TAP_NORTH        53
#define GI_TAP_CENTER       54

//Airwheel Info
#define GI_AIRWHEEL_CW      90
#define GI_AIRWHEEL_CCW     91

#define MD_BUF_LEN          128



struct msgHeaderT {
        uint8_t size;
        uint8_t flags;
        uint8_t seq;
        uint8_t id;
};
union data {
    uint8_t buf[128];
    struct msgHeaderT header;
    struct {                            // follow the Sensor Data Output
        struct msgHeaderT header;       //       Size, Flags, Seq, ID
        uint16_t streamingOutputMask;        //       StreamingOutputMask
        uint8_t timeStamp;                   //       ....
        uint8_t systemInfo;
        uint16_t dspInfo;
        uint32_t gestureInfo;
        uint32_t touchInfo;
        uint8_t  airWheelCounter;
        uint8_t  airWheelUnused;
        uint16_t posX;
        uint16_t posY;
        uint16_t posZ;
    } sensorData;
};

extern union data md;


class DFRobot_Gesture{
public:
	void I2C1_MasterRead( uint8_t *pdata,uint8_t reclength,uint16_t address);
	uint8_t mgcProcMsg(void);
};


#endif




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