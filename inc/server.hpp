#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include "alfe.hpp"

using namespace std;

class Server {

    int sockfd , newsockfd , c, portno = 60004;
    struct sockaddr_in server , client;
	Alfe* bot;
	
	public: 
		Server(Alfe*);
		~Server() = default;
		void start_listen();
};

#endif
