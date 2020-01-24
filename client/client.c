#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 60004 
#define ADDRESS "192.168.1.13"   
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0;
    struct sockaddr_in serv_addr; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, ADDRESS, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    char buffer[32];
    buffer[0] = '1';
    buffer[1] = '\0';
	write(sock, buffer, sizeof(buffer));
//    send(sock , "1\0", 32, 0 ); 
    printf("Sent command\n");
    printf("%s", buffer);  
	sleep(1); 
    send(sock, "12\0", 32, 0 ); 
    return 0; 
} 

