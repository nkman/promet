#include "header/header.h"

int main(int argc, char *argv[]){
	socklen_t sockfd_tcp = 0, sockfd_udp = 0, sockfd_icmp = 0;
	size_t size;
	char buffer[8192], input[10];
	struct sockaddr saddr;
	socklen_t saddr_size = sizeof(saddr);

	sockfd_tcp = socket(PF_INET, SOCK_RAW, IPPROTO_TCP);
	sockfd_udp = socket(PF_INET, SOCK_RAW, IPPROTO_UDP);
	sockfd_icmp = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);

	if(sockfd_tcp < 0){
		printf("\n Error : Could not create tcp socket \n");
		return 1;
	}
	if(sockfd_udp < 0){
		printf("\n Error : Could not create udp socket \n");
		return 1;
	}
	if(sockfd_icmp < 0){
		printf("\n Error : Could not create icmp socket \n");
		return 1;
	}

	if(argc == 1){
		printf("Assuming TCP !\n");
		strcpy(input, "TCP");
	}
	else if(argc == 2){
		strcpy(input, argv[1]);
		printf("Scanning %s traffic\n", input);
	}

	if(strcmp(input, "TCP") == 0)
	while(1){
		size = recvfrom(sockfd_tcp, buffer, 8192, 0, &saddr, &saddr_size);
		analyze(buffer, size);
	}

	else if(strcmp(input, "UDP") == 0)
	while(1){
		size = recvfrom(sockfd_udp, buffer, 8192, 0, &saddr, &saddr_size);
		analyze(buffer, size);
	}

	else if(strcmp(input, "ICMP") == 0)
	while(1){
		size = recvfrom(sockfd_icmp, buffer, 8192, 0, &saddr, &saddr_size);
		analyze(buffer, size);
	}

	return 0;
}