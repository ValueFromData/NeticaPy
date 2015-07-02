#include <stdio.h>

int main()
{
double x[]={1.0,2.5,5.6,9};
double* y=x;
printf("sizeof y %ld y[0] %ld",sizeof(y),sizeof(y[0]));
return 0;
}
