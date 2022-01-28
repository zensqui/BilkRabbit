#include <winsock2.h>

typedef u_long tcp_seq;
/*
 * TCP header.
 * Per RFC 793, September, 1981.
 */
struct tcphdr
{
    u_short source;  /* source port */
    u_short dest;    /* destination port */
    tcp_seq seq;     /* sequence number */
    tcp_seq ack_seq; /* acknowledgement number */

    u_char th_x2 : 4; /* (unused) */

    u_char doff : 4; /* data offset */

    u_char th_flags;
    unsigned char fin : 1;
    unsigned char syn : 1;
    unsigned char rst : 1;
    unsigned char psh : 1;
    unsigned char ack : 1;
    unsigned char urg : 1;
    u_short window;  /* window */
    u_short check;   /* checksum */
    u_short urg_ptr; /* urgent pointer */
};

#define TCPOPT_EOL 0
#define TCPOPT_NOP 1
#define TCPOPT_MAXSEG 2
#define TCPOLEN_MAXSEG 4
#define TCPOPT_WINDOW 3
#define TCPOLEN_WINDOW 3
#define TCPOPT_SACK_PERMITTED 4 /* Experimental */
#define TCPOLEN_SACK_PERMITTED 2
#define TCPOPT_SACK 5 /* Experimental */
#define TCPOPT_TIMESTAMP 8
#define TCPOLEN_TIMESTAMP 10
#define TCPOLEN_TSTAMP_APPA (TCPOLEN_TIMESTAMP + 2) /* appendix A */

#define TCPOPT_TSTAMP_HDR \
    (TCPOPT_NOP << 24 | TCPOPT_NOP << 16 | TCPOPT_TIMESTAMP << 8 | TCPOLEN_TIMESTAMP)

/*
 * Default maximum segment size for TCP.
 * With an IP MSS of 576, this is 536,
 * but 512 is probably more convenient.
 * This should be defined as MIN(512, IP_MSS - sizeof (struct tcpiphdr)).
 */
#define TCP_MSS 512

#define TCP_MAXWIN 65535 /* largest value for (unscaled) window */

#define TCP_MAX_WINSHIFT 14 /* maximum window shift */

/*
 * User-settable options (used with setsockopt).
 */
#define TCP_NODELAY 0x01 /* don't delay send to coalesce packets */
#define TCP_MAXSEG 0x02  /* set maximum segment size */
