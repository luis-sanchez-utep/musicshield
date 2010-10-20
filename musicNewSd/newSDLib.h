#ifndef NEWSDLIB_H
#define NEWSDLIB_H

extern Sd2Card card;
extern SdVolume volume;
extern SdFile root;
extern SdFile file;

void initialSDCard();
void openFile(char *fileName);
int readFile(byte *buffer, int len);
int playFile(char *fileName);
#endif

