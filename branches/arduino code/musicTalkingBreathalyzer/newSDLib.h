#ifndef NEWSDLIB_H
#define NEWSDLIB_H

extern SdCard card;
extern Fat16 file;

// store error strings in flash to save RAM
#define error(s) error_P(PSTR(s))

int initialSDCard();
int openFile(char *fileName);
int readFile(byte *buffer, int len);
void error_P(const char* str) ;
#endif

