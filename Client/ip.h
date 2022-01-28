#ifndef _IPHDR_H_
#define _IPHDR_H_

#include <pshpack1.h>

struct ip
{

    u_char ip_v : 4, /* version */
        ip_hl : 4;   /* header length */

    u_char ip_tos;                 /* type of service */
    u_short tot_len;                /* total length */
    u_short ip_id;                 /* identification */
    u_short ip_off;                /* fragment offset field */
#define IP_RF 0x8000               /* reserved fragment flag */
#define IP_DF 0x4000               /* dont fragment flag */
#define IP_MF 0x2000               /* more fragments flag */
#define IP_OFFMASK 0x1fff          /* mask for fragmenting bits */
    u_char ip_ttl;                 /* time to live */
    u_char ip_p;                   /* protocol */
    u_short ip_sum;                /* checksum */
    struct in_addr ip_src, ip_dst; /* source and dest address */
} __packed;

//
// IPv4 Header (without any IP options)
//
typedef struct ip_hdr
{
    unsigned char version;       // 4-bit IPv4 version
    unsigned char ihl;           // 4-bit header length (in 32-bit words)
    unsigned char tos;          // IP type of service
    unsigned short tot_len; // Total length
    unsigned short id;          // Unique identifier
    unsigned short frag_off;      // Fragment offset field
    unsigned char ttl;          // Time to live
    unsigned char protocol;     // Protocol(TCP,UDP etc)
    unsigned short check;    // IP checksum
    unsigned int saddr;       // Source address
    unsigned int daddr;      // Source address
} IPV4_HDR, *PIPV4_HDR, FAR *LPIPV4_HDR;

//
// Define the UDP header
//
typedef struct udp_hdr
{
    unsigned short src_portno;   // Source port no.
    unsigned short dest_portno;  // Dest. port no.
    unsigned short udp_length;   // Udp packet length
    unsigned short udp_checksum; // Udp checksum
} UDP_HDR, *PUDP_HDR;

//
// Define the TCP header
//
typedef struct tcp_hdr
{
    unsigned short src_portno;    // Source port no.
    unsigned short dest_portno;   // Dest. port no.
    unsigned long seq_num;        // Sequence number
    unsigned long ack_num;        // Acknowledgement number;
    unsigned short lenflags;      // Header length and flags
    unsigned short window_size;   // Window size
    unsigned short tcp_checksum;  // Checksum
    unsigned short tcp_urgentptr; // Urgent data?
} TCP_HDR, *PTCP_HDR;

//
// Stucture to extract port numbers that overlays the UDP and TCP header
//
typedef struct port_hdr
{
    unsigned short src_portno;
    unsigned short dest_portno;
} PORT_HDR, *PPORT_HDR;

//
// IGMP header
//
typedef struct igmp_hdr
{
    unsigned char version_type;
    unsigned char max_resp_time;
    unsigned short checksum;
    unsigned long group_addr;
} IGMP_HDR, *PIGMP_HDR;

typedef struct igmp_hdr_query_v3
{
    unsigned char type;
    unsigned char max_resp_time;
    unsigned short checksum;
    unsigned long group_addr;
    unsigned char resv_suppr_robust;
    unsigned char qqi;
    unsigned short num_sources;
    unsigned long sources[1];
} IGMP_HDR_QUERY_V3, *PIGMP_HDR_QUERY_V3;

typedef struct igmp_group_record_v3
{
    unsigned char type;
    unsigned char aux_data_len;
    unsigned short num_sources;
    unsigned long group_addr;
    unsigned long source_addr[1];
} IGMP_GROUP_RECORD_V3, *PIGMP_GROUP_RECORD_V3;

typedef struct igmp_hdr_report_v3
{
    unsigned char type;
    unsigned char reserved1;
    unsigned short checksum;
    unsigned short reserved2;
    unsigned short num_records;
} IGMP_HDR_REPORT_V3, *PIGMP_HDR_REPORT_V3;

#include <poppack.h>

#endif