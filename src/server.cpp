#include <iostream>
#include "server.hpp"
#include "alfe.hpp"
#include <string>
#include <pigpio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <cstring>

using namespace std;

Server::Server(Alfe* a) {
    
	bot = a;
    //Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cout << "ERROR: Couldn't create socket" << endl;
    }
     
    memset(&server, '\0', sizeof(server)); 
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( portno );
     
    //Bind
    if( bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        cout << "ERROR: bind failed" << endl;
        exit(1);
    }
    cout << "bind done" << endl;
     
    //Listen
    listen(sockfd, 5);
    c = sizeof(struct sockaddr_in);


	cout << "waiting for a command" << endl;
	
	if( (newsockfd = accept(sockfd, (struct sockaddr *)&client, (socklen_t*) &c)) < 0) {
		cout << "ERROR: failed accept" << endl;
	}
	cout << "Waiting on data . . . " << endl;
	
	while(1) {
		char buffer[32];
		memset(buffer, '\0', sizeof(buffer));
		int n, data;

		if ((n = read(newsockfd, buffer, 31) ) < 0) {
			cout << "ERROR: failed reading from socket" << endl;
			exit(1);
		}
		data = atoi(buffer);
		
		switch(data) {
			case 1:
				bot->left();
				break;
			case 2:
				bot->right();
				break;
			case 3:
				bot->forwards();
				break;
			case 4:
				bot->backwards();
				break;
			default:
				bot->stop();
				break;
		
		
		}
	
		cout << "data: " << data << "\tbuffer:" << buffer << endl;

	}
		
	
	
	
}


