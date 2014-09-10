#ifndef _HEADER_FUNCTION_H
#define _HEADER_FUNCTION_H

void analyze(void *, size_t);
void process_tcp_data(void *, size_t);
void process_udp_data(void *, size_t);
void process_icmp_data(void *, size_t);


void analyze(void *buffer, size_t size_of_buffer){
	count++;
	struct iphdr *iph = (struct iphdr *)buffer;
	switch(iph->protocol){
		case 1:
			process_icmp_data(buffer, size_of_buffer);
			break;
		case 6:
			process_tcp_data(buffer, size_of_buffer);
			break;
		case 17:
			process_udp_data(buffer, size_of_buffer);
			break;
		default:
			printf("Cannot identify the protocol for this connection.\n");
	}
}

void process_tcp_data(void *buffer, size_t size){
	// struct ip
}

void process_udp_data(void *buffer, size_t size){

}

void process_icmp_data(void *buffer, size_t size){

}

#endif /* _HEADER_FUNCTION_H */



/*
http://sock-raw.org/papers/sock_raw
enum {
	IPPROTO_IP = 0,			/* Dummy protocol for TCP		
	IPPROTO_ICMP = 1,		/* Internet Control Message Protocol	
	IPPROTO_IGMP = 2,		/* Internet Group Management Protocol	
	IPPROTO_IPIP = 4,		/* IPIP tunnels (older KA9Q tunnels use 94) 
	IPPROTO_TCP = 6,		/* Transmission Control Protocol	
	IPPROTO_EGP = 8,		/* Exterior Gateway Protocol		
	IPPROTO_PUP = 12,		/* PUP protocol				
	IPPROTO_UDP = 17,		/* User Datagram Protocol		
	IPPROTO_IDP = 22,		/* XNS IDP protocol			
	IPPROTO_DCCP = 33,		/* Datagram Congestion Control Protocol 
	IPPROTO_RSVP = 46,		/* RSVP protocol			
	IPPROTO_GRE = 47,		/* Cisco GRE tunnels (rfc 1701,1702)	
	IPPROTO_IPV6 = 41,		/* IPv6-in-IPv4 tunnelling		
	IPPROTO_ESP = 50,       	/* Encapsulation Security Payload protocol 
	IPPROTO_AH = 51,             	/* Authentication Header protocol       
	IPPROTO_BEETPH = 94,	       	/* IP option pseudo header for BEET 
	IPPROTO_PIM    = 103,		/* Protocol Independent Multicast	
	IPPROTO_COMP   = 108,           /* Compression Header protocol 
	IPPROTO_SCTP   = 132,		/* Stream Control Transport Protocol	
	IPPROTO_UDPLITE = 136,		/* UDP-Lite (RFC 3828)			
	IPPROTO_RAW	 = 255,		/* Raw IP packets			
	IPPROTO_MAX
};
*/