#ifndef _HEADER_FUNCTION_H
#define _HEADER_FUNCTION_H

/*
 * Function identifies type of protocol.
 * TCP, UDP, ICMP.
 */
void analyze(void *, size_t);

/*
 * Process TCP data.
 */
void process_tcp_data(void *, size_t);

/*
 * Process UDP data.
 */
void process_udp_data(void *, size_t);

/*
 * Process ICMP data ??
 */
void process_icmp_data(void *, size_t);

/*
 * Ip header.
 */
void process_ip(void *buffer);

/*
 * search __be32/ul ip in traffic array.
 * Implemented using binary search.
 */
search_data find(unsigned int ip);

/*
 * Insert ip in __be32/ul format in traffic array.
 * Keep em sorted.
 * Implemented using array translation.
 */
unsigned int insert(unsigned int, int);

/*
 * Increase counter.
 * write in console.
 */
void detail_ip(unsigned int, struct iphdr *);

/*
 * Swap function.
 */
void swap(Traffic *, Traffic *);
/* ------------------------------------------ */

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

/* ------------------------------------------ */

void process_tcp_data(void *buffer, size_t size){
    process_ip(buffer);

}

/* ------------------------------------------ */

void process_udp_data(void *buffer, size_t size){
    printf("UDP Data\n");
}

/* ------------------------------------------ */

void process_icmp_data(void *buffer, size_t size){
    printf("ICMP DATA\n");
}

/* ------------------------------------------ */

void process_ip(void *buffer){
    struct iphdr *iph = (struct iphdr *)buffer;
    unsigned int ip, index;
    search_data data;

    //Empty it everytime.
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;
    ip  = source.sin_addr.s_addr;

    data = find(ip);
    index = data.index;
    switch(data.found){
        case 0:
            index = insert(ip, data.index);
        case 1:
            detail_ip(index, iph);
            break;
    }
}

/* ------------------------------------------ */

void detail_ip(unsigned int index, struct iphdr *iph){
    switch(iph->protocol){
        case IPPROTO_TCP:
            traffic[index].tcp_counter++;
            traffic[index].data_processed_tcp += (ntohs(iph->tot_len)/1024);
            printf("%u\t%u\t%uKB\t%s\tTCP\n",count, traffic[index].tcp_counter, traffic[index].data_processed_tcp,
                inet_ntoa(source.sin_addr));
            break;
    }
}

/* ------------------------------------------ */

search_data find(unsigned int ip){
    search_data data;
    int first, mid, last, i;
    first = 0;
    last = size_of_traffic - 1;
    mid = (first + last)/2;
    while(first <= last){
        if(traffic[mid].name_be == ip){
            data.found = 1;
            data.index = mid;
            return data;
        }
        else if(traffic[mid].name_be > ip)
            last = mid-1;
        else if(traffic[mid].name_be < ip)
            first = mid+1;
        mid = (first+last)/2;
    }
    data.index = mid;
    data.found = 0;
    return data;
};

/* ------------------------------------------ */

unsigned int insert(unsigned int ip, int index){
    int i;
    Traffic T;
    T.name_be = ip;
    T.tcp_counter = T.udp_counter = T.data_processed_tcp = T.data_processed_udp = 0;

    traffic[size_of_traffic] = T;
    size_of_traffic++;

    i = size_of_traffic - 2;
    while(i>=0 && traffic[i].name_be > traffic[i+1].name_be){
        swap(&traffic[i], &traffic[i+1]);
        i--;
    }
    i++;

    return i;
}

/* ------------------------------------------ */

void swap(Traffic *t1, Traffic *t2){
    Traffic temp = *t2;
    *t2 = *t1;
    *t1 = temp;
}

/* ------------------------------------------ */

#endif /* _HEADER_FUNCTION_H */