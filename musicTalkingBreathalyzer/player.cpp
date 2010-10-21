//  File player.cpp
//  Functions for user interface
//  For more details about the product please check http://www.seeedstudio.com/depot/
//
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
#include <Fat16.h>
#include <Fat16Util.h>
#include "string.h"
#include "player.h"
#include "config.h"
#include "vs10xx.h"
#include "newSDLib.h"

//do led controlling
void controlLed()
{
  byte static flagOn = 1;
  int static count = 100000;
  if(--count == 0)
  {
    count = 100000;
    if(flagOn == 1) 
    {
      GREEN_LED_ON();
      flagOn = 0;
    }
    else
    {
      GREEN_LED_OFF();
      flagOn = 1;
    }
  }
}
//do key scaning
void scanKey()
{

}

//do some interactive things when vs1053 is busy
void AvailableProcessorTime()
{
  scanKey();
  controlLed();
}
int playFile(char *fileName)
{

  Mp3SoftReset();//it is necessary to play each music file

  if(!openFile(fileName)){//open music file
    return 0;
  }
  int readLen = 0;
  byte readBuf[READ_BUF_LEN];
  byte *tp = readBuf;
  while(1)
  {
    readLen = readFile(readBuf,READ_BUF_LEN);//read file content length of 512 every time
    tp = readBuf;
    //Serial.println(readLen);

    Mp3SelectData();

    while (tp < readBuf+readLen)
    {
      if (!MP3_DREQ)
      {
        while (!MP3_DREQ)
        {
          Mp3DeselectData();
          AvailableProcessorTime();//here vs1053 is busy, so you can do some interactive things, like key scanning,led controlling.
          Mp3SelectData();
        }
      }
      // Send music content data to VS10xx 
      SPIPutChar(*tp++);
    }

    SPIWait();
    Mp3DeselectData();

    if(readLen < READ_BUF_LEN)
    {
      Mp3WriteRegister(SPI_MODE,0,SM_OUTOFWAV);
      SendZerosToVS10xx();
      break;
    }
  };
  Serial.println("played over\r\n");

  if(file.close() == 0)//close file
  {
    error("close file failed");
  }
  return 0; //OK Exit
}



