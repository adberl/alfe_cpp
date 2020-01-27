#ifndef ALFE_HPP
#define ALFE_HPP

using namespace std;

class Alfe {
	int GPIO_TRIGGER;
	int GPIO_ECHO;
	int MOTORS[4] = {18, 24, 25, 12};
	int LEDS[6] = {4, 17, 27, 22, 13, 26};
	
	private:
		static void distanceHelper(int, int, uint32_t);
	
	public: 
		Alfe();
		~Alfe() = default;
		void forwards();
		void backwards();
		void left();
		void right();
		int distance(); 
		char leds();
		void stop();

};

#endif
