#ifndef _HEADER_FUNCTION_H
#define _HEADER_FUNCTION_H

void analyze(void *, size_t);
void process_tcp_data(void *, size_t);
void process_udp_data(void *, size_t);
void process_icmp_data(void *, size_t);
void process_ip(void *buffer);

void analyze(void *buffer, size_t size_of_buffer){
	count++;
	struct iphdr *iph = (struct iphdr *)buffer;
	switch(iph->protocol){
		case IPPROTO_ICMP:
			process_icmp_data(buffer, size_of_buffer);
			break;
		case IPPROTO_TCP:
			process_tcp_data(buffer, size_of_buffer);
			break;
		case IPPROTO_UDP:
			process_udp_data(buffer, size_of_buffer);
			break;
		default:
			printf("Cannot identify the protocol for this connection.\n");
	}
}

void process_tcp_data(void *buffer, size_t size){
	struct iphdr *iph = (struct iphdr *)buffer;
	struct tcphdr *tcp = (struct tcphdr *)(buffer + iph->ihl);

	process_ip(buffer);
	printf("TCP %u\n", ntohs(tcp->source));
}

void process_udp_data(void *buffer, size_t size){

}

void process_icmp_data(void *buffer, size_t size){

}

void process_ip(void *buffer){
	struct iphdr *iph = (struct iphdr *)buffer;

	//Empty it everytime.
	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = iph->saddr;
	printf("%u\t", (source.sin_addr.s_addr));
	printf("%s\t", inet_ntoa(source.sin_addr));
	printf("%u\t", count);
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

struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};

struct in_addr {
    unsigned long s_addr;  // load with inet_aton()
};

 struct iphdr {
 86 #if defined(__LITTLE_ENDIAN_BITFIELD)
 87         __u8    ihl:4,
 88                 version:4;
 89 #elif defined (__BIG_ENDIAN_BITFIELD)
 90         __u8    version:4,
 91                 ihl:4;
 92 #else
 93 #error  "Please fix <asm/byteorder.h>"
 94 #endif
 95         __u8    tos;
 96         __be16  tot_len;
 97         __be16  id;
 98         __be16  frag_off;
 99         __u8    ttl;
100         __u8    protocol;
101         __sum16 check;
102         __be32  saddr;
103         __be32  daddr;
104         /*The options start here. 
105 };

*/