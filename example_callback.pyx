cdef extern from "myfile.h":
    
   int reg(int callback(char* x,void* obj),char* x,void* obj)



def reg_(char* s,f):
   return reg(callback,s,<void*>f)

cdef int callback(char* x,void* obj):
   (<object>obj)(x)


