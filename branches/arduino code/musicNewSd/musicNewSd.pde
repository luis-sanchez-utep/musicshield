
#include <avr/io.h>
#include "config.h"
#include "filesys.h"
#include "player.h"
#include "vs10xx.h"
#include "record.h"

#include <SdFat.h>
#include <SdFatUtil.h>
#include "newSDLib.h"

//#include <NewSoftSerial.h>
//NewSoftSerial mySerial(2, 3);//pin2-Rx,pin3-Tx(note: pin3 is actually later used as volume down input)

void setup()
{
  Serial.begin(9600);
  //Serial.println("Hello test!");
  //mySerial.begin(19200);// used for receiving command data from the iPod dock.
  
  InitSPI();

  InitIOForVs10xx();

  InitIOForKeys();
  
  InitIOForLEDs();

  //InitFileSystem();

  //VsSineTest();

  Mp3Reset();
   //RED_LED_ON();
  //delay(1000);//give enough time to stable the power to the SD card, so that, the intialization will be much easier to succeed.
  initialSDCard();

  //openFile("trackM.ogg");
}


void loop()
{ 
  playFile("blow0.wav");
  playFile("blow1.wav");
  playFile("blow2.wav");
  playFile("blow3.wav");
  playFile("buzzed0.wav");
  playFile("buzzed1.wav");
  playFile("buzzed2.wav");
  playFile("buzzed3.wav");
  playFile("drunk0.wav");
  playFile("drunk1.wav");
  playFile("drunk2.wav");
  playFile("drunk3.wav");
  playFile("few0.wav");
  playFile("few1.wav");
  playFile("few2.wav");
  playFile("few3.wav");
  playFile("mode0.wav");
  playFile("mode1.wav");
  playFile("mode2.wav");
  playFile("mode3.wav");
  playFile("nothing0.wav");
  playFile("nothing1.wav");
  playFile("nothing2.wav");
  playFile("nothing3.wav");
  playFile("wait0.wav");
  playFile("wait1.wav");
  playFile("wait2.wav");
  playFile("wait3.wav");
}


