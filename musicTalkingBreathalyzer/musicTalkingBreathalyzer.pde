//  File musicTalkingBreathalyzer.pde
//  Demo code for playing any existing music file on Micro SD card by file name
//  For more details about the product please check http://www.seeedstudio.com/depot/

//  Copyright (c) 2010 seeed technology inc.
//  Author: Icing Chang
//  Version: 1.0
//  Time: Oct 21, 2010
//  Changing records:
//    
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#include <WProgram.h>
#include <avr/io.h>
#include "config.h"
#include "player.h"
#include "vs10xx.h"

#include <Fat16.h>
#include <Fat16Util.h>
#include "newSDLib.h"

void setup()
{
  Serial.begin(9600);

  InitSPI();

  InitIOForVs10xx();

  InitIOForKeys();

  InitIOForLEDs();

  Mp3Reset();
  if (!initialSDCard())
    return;

  RED_LED_ON();//light red LED
}


void loop()
{ 
  playFile("trackM.ogg");
  playFile("trackN.ogg");
  playFile("trackO.ogg");
  /*playFile("blow0.wav");
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
   playFile("wait3.wav");*/
}



