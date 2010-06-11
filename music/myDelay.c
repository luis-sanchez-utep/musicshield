#include "myDelay.h"

//delay 1ms
void delay(int ms)
{
	volatile int i,j,k;
	
	for(int i = 0; i < ms;i++)
		for(int j = 0; j < 10; j++)
			for(k = 0; k < 90; k++)
			;

}
