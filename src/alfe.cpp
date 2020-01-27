#include <iostream>
#include "alfe.hpp"
#include <string>
#include <pigpio.h>
#include <unistd.h>
#include <ctime>

using namespace std;

Alfe::Alfe() {
	GPIO_TRIGGER = 21;
	GPIO_ECHO = 20;
//	MOTORS = 
//	LEDS
	
	
    if(gpioInitialise() < 0) {
        exit(-1337);
    }
	
	gpioSetMode(GPIO_TRIGGER, PI_OUTPUT);
	gpioSetMode(GPIO_ECHO, PI_INPUT);	
	for(int i : MOTORS) { 
		gpioSetMode(i, PI_OUTPUT);
	}
	for(int i : LEDS) { 
		gpioSetMode(i, PI_INPUT);
	}
	
}

void Alfe::stop() {
	gpioWrite(12, 0);
	gpioWrite(24, 0);	
	gpioWrite(18, 0);
	gpioWrite(25, 0);	
}

void Alfe::forwards() {
	gpioWrite(12, 1);
	gpioWrite(24, 1);
	gpioWrite(18, 0);
	gpioWrite(25, 0);	
}

void Alfe::backwards() {
	gpioWrite(12, 0);
	gpioWrite(24, 0);	
	gpioWrite(18, 1);
	gpioWrite(25, 1);
}

void Alfe::left() {
	gpioWrite(12, 1);
	gpioWrite(24, 0);	
	gpioWrite(18, 0);
	gpioWrite(25, 0);	
}

void Alfe::right() {
	gpioWrite(12, 0);
	gpioWrite(24, 1);	
	gpioWrite(18, 0);
	gpioWrite(25, 0);	
}

int Alfe::distance() {
	gpioWrite(GPIO_TRIGGER, PI_OFF);
	usleep(0.005);
	gpioWrite(GPIO_TRIGGER, PI_ON);
	usleep(0.015);
	gpioWrite(GPIO_TRIGGER, PI_OFF);

	gpioSetAlertFunc(GPIO_ECHO, Alfe::distanceHelper);

	return 0;
}

void Alfe::distanceHelper(int gpio, int level, uint32_t tick) {

   static uint32_t startTick=0;
   int diffTick;

   if (level == PI_ON)
   {
      startTick = tick;
   }
   else if (level == PI_OFF)
   {
      diffTick = tick - startTick;
      cout << (diffTick/2) * 0.0343 << endl;
   }

}

char Alfe::leds() {
	char status;
	for(int i : LEDS) {
		int a = gpioRead(i);
		if(a == 1)
			status = (status + 1) << 1;
		else	
			status = status << 1;
	}
	return status;
}

