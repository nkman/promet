#include "header/header.h"
#define port 443
#define localhost "172.25.12.12"

int main(int argc, char *argv[]){
	socklen_t sockfd = 0;
	int size;
	char buffer[8192];
	struct sockaddr saddr;
	socklen_t saddr_size = sizeof(saddr);

	sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_TCP);

	if(sockfd < 0){
		printf("\n Error : Could not create socket \n");
		return 1;
	}
	while(1){
		recvfrom(sockfd , buffer , 65536 , 0 , &saddr , &saddr_size);
		printf ("Caught tcp packet: %s\n", buffer);
	}

	return 0;
}