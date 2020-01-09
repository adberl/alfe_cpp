#include <iostream>
#include "alfe.hpp"
#include "server.hpp"
#include <string>
#include <pigpio.h>
#include <unistd.h>

using namespace std;

int main() {
	
	Alfe* bot = new Alfe();
//	bot->forwards();
//	sleep(20);
//	bot->stop();
	Server* serv = new Server(bot);
	
	return 0;
}