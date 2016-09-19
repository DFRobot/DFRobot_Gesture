/**************************************************
*!
 * @file 3D_GestureTest.ino
 * @brief 
 *         this procedure to achieve 3D gesture recognition can be achieved in 3-dimensional 
 *         space,up, down, left,right,Counterclockwise circle recognition and Clockwise circle recognition
 * @n [Get the module here](https://www.dfrobot.com/wiki/index.php?title=3D_Gesture_Sensor_mini_SKU:SEN0202)
 * @n [Connection and Diagram](https://www.dfrobot.com/wiki/index.php?title=3D_Gesture_Sensor_mini_SKU:SEN0202)
 *
 * @copyright [DFRobot](http://www.dfrobot.com), 2016
 * @copyright GNU Lesser General Public License
 *
 * @author [Carl](lei.wu@dfrobot.com)
 * @version  V1.0
 * @date  2016-09-9

Hardware Connections:
Arduino Pin  3D Gesture Sensor-mini  Board  Function
 GND          GND              Ground
 3.3V-5V      VCC              Power
 A5           SCL              I2C Clock
 A4           SDA              I2C Data
 D7           D                Digital port
 
***************************************************/
#include <DFRobot_Gesture.h>
#include <Wire.h>

int testPin= 7;
unsigned char cmd;

DFRobot_Gesture myGesture;

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
 pinMode(testPin, INPUT);  
 Serial.write("3D Gesture sensor is now running....\r\n");  
}


void loop()
{

  if(digitalRead(testPin)==0)
  {
     
   myGesture.I2C1_MasterRead(md.buf,26,0x42); //The address is:0x42
   cmd = myGesture.mgcProcMsg();     //process the message
          if(cmd != GI_NOGESTURE )
            {
                switch(cmd)
                {
                 
                    case GI_FLICK_R:
                      Serial.println("RIGHT");
                        break;

                    case GI_FLICK_L:
                        Serial.println("LEFT");
                        break;

                    case GI_FLICK_D:
                     Serial.println("DOWN");
                        break;

                    case GI_FLICK_U:
                       Serial.println("UP");
                        break;
                    case GI_AIRWHEEL_CW://Clockwise in circles
                     Serial.println("CW");
                        break;

                    case GI_AIRWHEEL_CCW://Counterclockwise circles
                       Serial.println("CCW");
                        break;

                    default: break;
                }
            }
  }
  
 else  {};

}
