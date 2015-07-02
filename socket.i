// socket.i
// SWIG Interface file to play with some sockets
%init sock          // Name of our module
%{
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

/* Set some values in the sockaddr_in structure */
struct sockaddr *new_sockaddr_in(short family, unsigned long hostid, int port) {
        struct sockaddr_in *addr;
        addr = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));
        bzero((char *) addr, sizeof(struct sockaddr_in));
        addr->sin_family = family;
        addr->sin_addr.s_addr = hostid;
        addr->sin_port = htons(port);
        return (struct sockaddr *) addr;
}
/* Get host address, but return as a string instead of hostent */
char *my_gethostbyname(char *hostname) {
        struct hostent *h;
        h = gethostbyname(hostname);
        if (h) return h->h_name;
        else return "";
}
%}

// Add these constants
enum {AF_UNIX, AF_INET, SOCK_STREAM, SOCK_DGRAM, SOCK_RAW,
      IPPROTO_UDP, IPPROTO_TCP, INADDR_ANY};

#define  SIZEOF_SOCKADDR  sizeof(struct sockaddr)

// Wrap these functions 
int socket(int family, int type, int protocol);
int bind(int sockfd, struct sockaddr *myaddr, int addrlen);
int connect(int sockfd, struct sockaddr *servaddr, int addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *peer, %val int *addrlen);
int close(int fd);
struct sockaddr *new_sockaddr_in(short family, unsigned long, int port);
%name gethostbyname { char *my_gethostbyname(char *); }
unsigned long inet_addr(const char *ip);

%include unixio.i
