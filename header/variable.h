#ifndef _HEADER_VARIABLE_H
#define _HEADER_VARIABLE_H

struct traffic_detail{
	char name[50];
	int tcp_counter;
	unsigned int data_prosessed_tcp;
	int udp_counter;
	unsigned int data_processed_udp;

	/* We may not need this */
	unsigned int data_processed_total; // == data_processed_tcp + data_processed_udp
	unsigned int total_counter;	// == tco_counter + udp_counter

	/* implement this later */
	unsigned int frequency;
};

/*
 * Total count of all requests.
 */
static unsigned int count = 0 ;
#endif /* _HEADER_VARIABLE_H */