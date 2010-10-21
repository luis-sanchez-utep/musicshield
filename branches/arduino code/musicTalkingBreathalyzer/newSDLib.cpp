#include <Fat16.h>
#include <Fat16Util.h>
#include "newSDLib.h"
#include "vs10xx.h"

SdCard card;
Fat16 file;

void error_P(const char* str) {
  PgmPrint("error: ");
  SerialPrintln_P(str);
  if (card.errorCode) {
    PgmPrint("SD error: ");
    Serial.print(card.errorCode, HEX);
  }
  //while(1);
}

int initialSDCard()
{
  //SPI speed: 0 - F_CPU/2, 1 - F_CPU/4
  if (!card.init(0))
 {
   error("card.init failed");
    return 0;
 }
  // initialize a FAT16 volume
  if (!Fat16::init(&card))
 {
   error("Fat16::init");
   return 0;
 }
 return 1;
}

int openFile(char *fileName)
{
  if (file.open(fileName, O_READ)) {
    Serial.write(fileName);
    Serial.println(" opened");
    return 1;
  }
  else{
    error("open file failed");
    return 0;
  }
}

int readFile(byte *buffer, int len)
{
  int readLen = 0;
  readLen = file.read(buffer,len);
  return readLen;
}



