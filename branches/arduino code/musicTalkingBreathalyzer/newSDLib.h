#ifndef NEWSDLIB_H
#define NEWSDLIB_H

extern Sd2Card card;
extern SdVolume volume;
extern SdFile root;
extern SdFile file;

// store error strings in flash to save RAM
#define error(s) error_P(PSTR(s))

void initialSDCard();
void openFile(char *fileName);
int readFile(byte *buffer, int len);
void error_P(const char* str) ;
#endif

