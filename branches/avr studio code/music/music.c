
#include <avr/io.h>
#include "config.h"
#include "filesys.h"
#include "hardwareserial.h"
#include "player.h"
#include "vs10xx.h"
#include "wiring.h"
//#include "NewSoftSerial.h"

//NewSoftSerial mySerial(2, 3);//pin2-Rx,pin3-Tx(note: pin3 is actually later used as volume down input)

void Setup()
{
  Serial.begin(9600);
  
  InitSPI();

  InitIOForVs10xx();

  InitIOForKeys();
  
  InitIOForLEDs();

  InitFileSystem();

  //VsSineTest();

  Mp3Reset();
  
}


int main()
{
	init();

	Setup();

	Play();

	while(1);
  
}

