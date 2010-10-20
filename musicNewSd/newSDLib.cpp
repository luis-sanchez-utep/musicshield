#include <SdFat.h>
#include <SdFatUtil.h>
#include "newSDLib.h"
#include "buffer.h"
#include "vs10xx.h"

Sd2Card card;
SdVolume volume;
SdFile root;
SdFile file;

// store error strings in flash to save RAM
#define error(s) error_P(PSTR(s))

void error_P(const char* str) {
  PgmPrint("error: ");
  SerialPrintln_P(str);
  if (card.errorCode()) {
    PgmPrint("SD error: ");
    Serial.print(card.errorCode(), HEX);
    Serial.print(',');
    Serial.println(card.errorData(), HEX);
  }
  while(1);
}

void initialSDCard()
{
  // initialize the SD card at SPI_HALF_SPEED to avoid bus errors with
  // breadboards.  use SPI_FULL_SPEED for better performance.
  if (!card.init(SPI_HALF_SPEED)) error("card.init failed");

  // initialize a FAT volume
  if (!volume.init(&card)) error("volume.init failed");

  // open the root directory
  if (!root.openRoot(&volume)) error("openRoot failed");

}

void openFile(char *fileName)
{
  if (file.open(&root, fileName, O_READ)) {
    Serial.write(fileName);
    Serial.println(" opened");
  }
  else{
    error("open file failed");
  }
}

int readFile(byte *buffer, int len)
{
  int readLen = 0;
  readLen = file.read(buffer,len);
  return readLen;
}

int playFile(char *fileName)
{

  openFile(fileName);//open music file

    int len = 512;
  int readLen = 0;
  while(1)
  {
    readLen = readFile(diskSect.raw.buf,len);//read file content length of 512 every time
    if(readLen <= 0)
      break;

    Mp3SelectData();

    dataBufPtr = diskSect.raw.buf;

    while (dataBufPtr < diskSect.raw.buf+readLen)
    {
      if (!MP3_DREQ)
      {
        while (!MP3_DREQ)
        {
          Mp3DeselectData();
          AvailableProcessorTime();
          Mp3SelectData();
        }
      }
      /* Send 32 octets of disk block data to VS10xx */
      SPIPutCharWithoutWaiting(*dataBufPtr++);
      SPIWait();
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      //LED_Sel();
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIPutChar(*dataBufPtr++);
      SPIWait();
    }
    SPIWait();
    Mp3DeselectData();
  };
  return 0; //OK Exit
}


