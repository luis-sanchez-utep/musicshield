#include <SdFat.h>
#include <SdFatUtil.h>
#include "newSDLib.h"
#include "vs10xx.h"

Sd2Card card;
SdVolume volume;
SdFile root;
SdFile file;

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



