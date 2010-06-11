
#include <avr/io.h>
#include "config.h"
#include "filesys.h"
#include "hardwareserial.h"
#include "player.h"
#include "vs10xx.h"
#include "wiring.h"

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

