#include <stdio.h>
#include "example_callback_c.h"

typedef int (*callback)(char* x,void* obj);

int reg(callback func,char* x,void* obj ){
   return  func(x,obj);
}

