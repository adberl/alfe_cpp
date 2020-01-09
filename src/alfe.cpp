#include <iostream>
#include "alfe.hpp"
#include <string>
#include <pigpio.h>
#include <unistd.h>

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
	gpioSetMode(GPIO_ECHO, PI_OUTPUT);	
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
	
	return 0;
}

void Alfe::leds() {
	
}

