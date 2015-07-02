#include "myfile.h"

int reg(int callback(char* x,void* obj),char* x,void* obj)
{
 return callback(x,obj);
}

