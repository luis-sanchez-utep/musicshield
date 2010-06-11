#include "filesys.h"
#include "storage.h"
#include "string.h"
#include "mmc.h"
#include "record.h"
#include "player.h"
#include "config.h"
#include "hardwareserial.h"
#include "myDelay.h"
#include "ui.h"
#include "vs10xx.h"

/** Playing State Global */
 playingstatetype playingState = PS_NORMAL;

unsigned char playStop = 1; // play or stop flag,1-play,0-stop

unsigned char currentFile = 0;

/** Plays a disk file. Returns 1) if the file ends or 2) if the global
    variable playingState is not PS_NORMAL i.e. user has requested 
    stop or next or previous.*/
void PlayCurrentFile()
{
   char c, nFragments;

  playingState = PS_NORMAL; /* Request to play normally */
  //uiMode = UI_SPEC; /* User interface: show title SPECANA FOR VS1003*/

  ///LcdLocateHome();
  ///LcdPutConstantString("Opening ");

  //Serial.print("\r\nBuilding file fragment table...");

  //sectorAddress.l = album[currentAlbumCnt].track[currentFile].trackAddr.l;
  delay(100);//delay here is very important, give some time to sd card.---by Icing
  nFragments = BuildFragmentTable(); /* Too slow, rewrite! */
  //Serial.print("Fragments: ");
  //Serial.print(nFragments,DEC);

  ///LcdLocateHome();
  ///LcdPutConstantString("Playing ");

  for (c=0; c<nFragments; c++){
    sectorAddress.l = fragment[c].start;
    //ConsoleWrite ("\r\nPlayer: Playing from sector ");
    //ConsolePutUInt (sectorAddress.l);
    if (PlayDiskSectors(fragment[c].length)!=0){
      Mp3WriteRegister(SPI_MODE,0,SM_OUTOFWAV);
      SendZerosToVS10xx();
      return; //return without touching the value of playingState
    }
  }
  SendZerosToVS10xx();

  // After finishing normally default to requesting to play next song        
  playingState = PS_NEXT_SONG;
}

//check play or stop
/*void CheckPlay()
{
	playStop = 1;
}
*/
void CheckKey()
{
  static unsigned char volume = 40;
  static unsigned int vu_cnt = 2000;//volume up interval
  static unsigned int vd_cnt = 2000;//volume down interval

  if(0 == PSKey)
  {
  	playStop = 1-playStop;
	delay(20);
	while(0 == PSKey);
	delay(20);
  }
  
  while(!playStop)
  {
	if(0 == PSKey)
    {
  	  playStop = 1-playStop;
	  delay(20);
	  while(0 == PSKey);
	  delay(20);
    }
  }

  if(0 == NTKey)
  {
  	playingState = PS_NEXT_SONG;
	delay(20);
	while(0 == NTKey);
	delay(20);
  }
  else if(0 == BKKey)
  {
    playingState = PS_PREVIOUS_SONG;
	delay(20);
	while(0 == BKKey);
	delay(20);
  }
  else if(0 == VUKey)
  {
  	if(--vu_cnt == 0)
	{
    	if (volume-- == 0) volume = 0; //Change + limit to 0 (maximum volume)
    
		Mp3SetVolume(volume,volume);		

		vu_cnt = 2000;
	 }
  }
  else if (0 == VDKey)
  {
    if(--vd_cnt == 0)
	{
      if (volume++ == 254) volume = 254; //Change + limit to 254 (minimum vol)
	
	  Mp3SetVolume(volume,volume);
	  
	  vd_cnt = 2000;
	 }
       	         
  }
}

/** This function is called when the player is playing a song
 and there is free processor time. The basic task of this
 function is to implement the player user interface. */
void AvailableProcessorTime()
{

  CheckKey();
  //do other things
}

void Play()
{
  playingState = PS_NEXT_SONG;

  currentFile = 1;

 #if defined(__AVR_ATmega1280__)
   // If play/stop button is pressed during boot, enter recording.
  if (0== PSKey)
  {
  	 delay(20);
	 while(0 == PSKey);
	 delay(20);
        Record();
  }
  #endif
  
  //cyclely play 
  while(1)
  {

	 //CheckPlay();
	 CheckKey();
	 	 
	 if(1 ==playStop)
	 {
	 	if(OpenFile(currentFile))
	 	{	
			//if open failed, then try it again
	 		if(OpenFile(currentFile))
			{
				playStop = 0;
				playingState = PS_NEXT_SONG;
  				currentFile = 1;
				continue;
			}
	 	}
		
		PlayCurrentFile();
		if (playingState == PS_PREVIOUS_SONG) currentFile--;
	    if (playingState == PS_NEXT_SONG) currentFile++;
    	if (currentFile==0) currentFile = 1;
     	//if (playingState == PS_END_OF_SONG) playingState = PS_NORMAL; 
		Mp3SoftReset();
	 }
  }
}
