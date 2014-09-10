#ifndef _HEADER_VARIABLE_H
#define _HEADER_VARIABLE_H

struct traffic_detail{
    __be32 name_be;
    char name[50];
    int tcp_counter;
    unsigned int data_prosessed_tcp;
    int udp_counter;
    unsigned int data_processed_udp;

    /* We may not need this */
    unsigned int data_processed_total; // == data_processed_tcp + data_processed_udp
    unsigned int total_counter;    // == tco_counter + udp_counter

    /* implement this later */
    unsigned int frequency;
};

typedef struct traffic_detail Traffic;
static Traffic traffic[65535];
static unsigned int size_of_traffic = 0;
/*
 * Total count of all requests.
 */
static unsigned int count = 0 ;
static struct sockaddr_in source, destination;

typedef struct search_ret{
    int found;        //0 or 1
    int index;
}search_data;
#endif /* _HEADER_VARIABLE_H */