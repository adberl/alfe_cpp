#include <iostream>
#include <cstdlib>
#include <string>
#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <pthread.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 

#define PORT 60004 
#define ADDRESS "192.168.43.174" 

using namespace std;

bool working = true;

void readLED(int sock) {
	char status;
	if(read(sock, &status, 1) < 0) {
		cout << "failed to get LED status" << endl;
		exit(1);
	}
	for(int i = 0; i < 8; i++) {
		cout << (status>>i & 0x01);
	}
	cout << endl;
}

void *graphics(void* arg1) {

	int sock = (intptr_t) arg1;
    sf::RenderWindow window(sf::VideoMode(600, 600), "alfe_cpp control panel");
	sf::Keyboard::Key lastpressed = sf::Keyboard::Unknown;
	
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
        	switch(event.type) {
        		case sf::Event::Closed:
                	window.close();
                	working = false;
                	shutdown(sock, SHUT_WR);
                	close(sock);
                	break;

				case sf::Event::KeyReleased:
					if(event.key.code == lastpressed) { 
						lastpressed = sf::Keyboard::Unknown;   
						write(sock, "0", 1);	         
					}
					break;

            	case sf::Event::KeyPressed:
					if(event.key.code == lastpressed)
						break;
					else {
						if(event.key.code == sf::Keyboard::Left) {
							write(sock, "1", 1);
							cout << "going left" << endl;
						} 
						else if(event.key.code == sf::Keyboard::Right) {
							write(sock, "2", 1);
							cout << "going right" << endl;
						} 
						else if(event.key.code == sf::Keyboard::Up) {
							write(sock, "3", 1);
							cout << "going up" << endl;
						} 					
						else if(event.key.code == sf::Keyboard::Down) {
							write(sock, "4", 1);
							cout << "going down" << endl;
						}
						else if(event.key.code == sf::Keyboard::S) {
							write(sock, "5", 1);
							cout << "reading LEDs" << endl;
							readLED(sock);
						}
						else if(event.key.code == sf::Keyboard::D) {
							write(sock, "6", 1);
						}
						lastpressed = event.key.code;
						if(event.key.code == sf::Keyboard::Escape) {
						    window.close();
                			working = false;
                           	shutdown(sock, SHUT_RDWR);
                			close(sock);
                			//close(
                		}
						cout << "pressed: " << event.key.code << endl;		
					}
					break;
					  
	  
            	default:
            		break;   
               
            }
        }
		window.clear();

        window.display();
    }

    return 0;
}

int connect_serv() {
    int sock = 0;
    struct sockaddr_in serv_addr; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, ADDRESS, &serv_addr.sin_addr) <= 0)  
    { 
        printf("\nInvalid address/Address not supported \n"); 
    } 
   
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
	return sock;
}

int main() {

	pthread_t newthread;
	intptr_t sock = connect_serv();
	int rc = pthread_create(&newthread, NULL, graphics,(void *) sock);
	if (rc) {
		cout << "Couldn't create thread: " << rc << endl;
		exit(-1);
	}
	while(working);
	
	return 0;
}
