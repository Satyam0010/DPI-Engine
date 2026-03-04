#include <pcap.h>
#include <iostream>
#include "../include/pcap_reader.h"

void read_pcap_file(const char* filename)
{
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t* handle = pcap_open_offline(filename, errbuf);

    if (handle == nullptr)
    {
        std::cerr << "Error opening PCAP file: " << errbuf << std::endl;
        return;
    }

    struct pcap_pkthdr* header;
    const u_char* data;

    int packet_count = 0;

    while (pcap_next_ex(handle, &header, &data) >= 0)
    {
        packet_count++;

        std::cout << "Packet #" << packet_count
                  << " Size: " << header->len
                  << " bytes" << std::endl;
    }

    pcap_close(handle);
}