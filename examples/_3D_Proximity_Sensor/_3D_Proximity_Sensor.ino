/**************************************************
*!
 * @file 3D_GestureTest.ino
 * @brief 
 *         The program 3D gesture recognition at a distance of 3-dimensional space induction
 *        
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
int testPin = 7;
DFRobot_Gesture myGesture;
void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  pinMode(testPin, INPUT);
 Serial.write("3D Proximity sensor is now running....\r\n");  

}

void loop()
{

  if(digitalRead(testPin)==0)
  {
     
   myGesture.I2C1_MasterRead(md.buf,26,0x42); //The address is:0x42 
  if(md.sensorData.posX>0||md.sensorData.posY>0||md.sensorData.posZ>0)
    { 
      Serial.print(1);   
     }   // print the character
   } 
 else{
     Serial.println();
     Serial.println(0); }
 delay(100);
}

