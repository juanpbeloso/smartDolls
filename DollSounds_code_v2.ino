/*  DATE: 09/07/2019
 *  DESCRIPTION
 *  This code will play a track when the piezo
 *  sensors are touched.
 */

/* A2.mp3 -> Hand touch (That's ok)
 * A3.mp3 -> Intimate areas (Don't touch!)
 * A1.mp3 -> Cheek touch (That's ok)
 */


#include <SoftwareSerial.h>
#include <DFMiniMp3.h>

//Connected sensors
const int knockSensor1 = A1;
const int knockSensor2 = A2;
const int knockSensor3 = A3;

//Action thresholds when sensor is pressed
const int threshold1 = 450; 
const int threshold2 = 450;  
const int threshold3 = 200;  

// Analog readings
int sensorReading1 = 0;
int sensorReading2 = 0;
int sensorReading3 = 0;


/* Implement a notification class,
 * its member methods will get called
 */
 
class Mp3Notify {
  public:
    static void OnError(uint16_t errorCode)
    {}

    static void OnPlayFinished(uint16_t globalTrack)
    {}

    static void OnCardOnline(uint16_t code)
    {}

    static void OnCardInserted(uint16_t code)
    {}

    static void OnCardRemoved(uint16_t code)
    {}
};

// Some arduino boards only have one hardware serial port, so a software serial port is needed instead.
// comment out the above definition and uncomment these lines

SoftwareSerial secondarySerial(0, 1); // RX, TX
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(secondarySerial);

void setup()
{

  mp3.begin();
  waitMilliseconds(1000);
  mp3.setVolume(25);
  waitMilliseconds(500);
  mp3.playMp3FolderTrack(4);
  waitMilliseconds(500);

}

void waitMilliseconds(uint16_t msWait)
{
  uint32_t start = millis();

  while ((millis() - start) < msWait)
  {
    // Calling mp3.loop() periodically allows for notifications
    // to be handled without interrupts
    mp3.loop();
    delay(1);
  }
}

void loop()
{

  sensorReading1 = analogRead(knockSensor1);

  if (sensorReading1 >= threshold1) {
    mp3.playMp3FolderTrack(1);
    waitMilliseconds(2000);
  }

  sensorReading2 = analogRead(knockSensor2);

  if (sensorReading2 >= threshold2) {
    mp3.playMp3FolderTrack(2);  
    waitMilliseconds(2000);
  }

  sensorReading3 = analogRead(knockSensor3);

  if (sensorReading3 >= threshold3) {
    mp3.playMp3FolderTrack(3);  // 
    waitMilliseconds(5000);
  }

}
