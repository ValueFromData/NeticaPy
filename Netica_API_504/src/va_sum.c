#include <stdarg.h>

#include "va_sum.h"

node_bn* sum_va(node_bn* node,int len, ...) {
    int i;
    va_list vl;
    va_start(vl,len);
    for (i=0; i<len; ++i) {
        node->val += va_arg(vl,double);
    }
    va_end(vl);
    return node;
}
