#include "header/header.h"

int main(int argc, char *argv[]){
	socklen_t sockfd = 0;
	size_t size;
	char buffer[8192];
	struct sockaddr saddr;
	socklen_t saddr_size = sizeof(saddr);

	sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_TCP);

	if(sockfd < 0){
		printf("\n Error : Could not create socket \n");
		return 1;
	}
	while(1){
		size = recvfrom(sockfd, buffer, 8192, 0, &saddr, &saddr_size);
		analyze(buffer, size);
	}

	return 0;
}