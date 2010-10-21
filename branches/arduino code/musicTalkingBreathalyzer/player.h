#ifndef __PLAYER_H
#define __PLAYER_H


#define READ_BUF_LEN  32

void controlLed();
void scanKey();
void AvailableProcessorTime();
int playFile(char *fileName);

#endif

