// File : unixio.i 
// Some file I/O and memory functions
%{
%}
int read(int fd, void *buffer, int n);
int write(int fd, void *buffer, int n);
typedef unsigned int size_t;
void *malloc(size_t nbytes);
