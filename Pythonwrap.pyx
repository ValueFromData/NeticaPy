from libc.stdlib cimport malloc, free
from cpython.string cimport PyString_AsString
import cython
cdef char ** to_cstring_array(list_str):
    cdef char **ret = <char **>malloc(len(list_str) * sizeof(char *))
    for i in xrange(len(list_str)):
        ret[i] = PyString_AsString(list_str[i])
    return ret

cdef extern from "Netica.h":

    ctypedef struct environ_ns:
        pass

    ctypedef struct net_bn:
        pass

    ctypedef struct node_bn:
        pass

    environ_ns* NewNeticaEnviron_ns (const char* license, environ_ns* env, const char* locn)
    
    int InitNetica2_bn (environ_ns* env, char* mesg)

    net_bn* NewNet_bn (const char* name, environ_ns* env)
    
    node_bn* NewNode_bn (const char* name, int num_states, net_bn* net)

    void SetNodeStateNames_bn (node_bn* node, const char* state_names)

    void SetNodeTitle_bn (node_bn* node, const char* title)

    int AddLink_bn (node_bn* parent, node_bn* child)

    void DeleteNet_bn (net_bn* net)
    
    int CloseNetica_bn (environ_ns* env, char* mesg)


cdef extern from "NeticaEx.h":

    void SetNodeProbs (node_bn* node, ...)

    void CompileNet_bn (net_bn* net)

    double GetNodeBelief (char* node_name, char* state_name, net_bn* net)

    void EnterFinding (char* node_name, char* state_name, net_bn* net)



cdef extern environ_ns *env
cdef char mesg[600]

def test():
    #cdef char mesg[600]
    cdef int res
    env = NewNeticaEnviron_ns (NULL, NULL, NULL)
    res = InitNetica2_bn (env, mesg)
    return ( res,mesg)

def get_msg():
    return mesg

#cdef test_intptr(cython.p_int x,cython.p_int y):
#   cdef int temp
#   temp=x
#   x = y
#   y = temp
#   print <int> x,<int>y

#def intptr():
#   cython.declare(x=cython.int,y=cython.int)
#	cdef int x=3
#	cdef int y=10
#	test_intptr(&x,&y)
#	print <int>x,<int>y
def lis(list x):
    cdef char** version = to_cstring_array(x)
    v = []
    for i in version[:cython.sizeof(version)/cython.sizeof(version[0])]:
        print i
        v.append(i)
    free(version)
    return v

def con():
    cdef double* x=[1,2,3,4]
    sz_x = sizeof(x)
    sz_d = sizeof(double)
    print sz_x,sz_d,sizeof(x[0]),x[0],x[1],x[2],x[3],x[4]
    return [i for i in x[:sz_x/sz_d]]

def t( x=None,y=None,z=None):
    print  x if x else "n"
    print y if y else "n"
    print z if z else "n"
    res = IntList()
    x=[1,2,3,4]
    res.value = <int *>malloc(len(x) * sizeof(int))
    for i in range(len(x)):
        res.value[i] = <int> x[i]
    return res


cdef class IntList:
    cdef int* value
    def __getitem__(self, item):

        x=[]
        prev=0
        i=0
        
        def getWithEclipsis(index):
            index+=1
            assert index<len(item),"The list slice operator shouldn't end with Ellipsis (...)"
            if type(item[index])==int and item[index]>=0:
                for j in range(prev,item[index]):
                    x.append(self.value[j])
                return index+1
            elif type(item[index])==slice:
                start=(item[index].start if not item[index].start == None else 0)
                if type(start)==int and start>=0:
                    for j in range(prev,start):
                       x.append(self.value[j])
                    return index
            raise TypeError("Invalid type or invalid number is been passed")
        
        def getWithSlice(item):
            start,stop,step=(item.start if not item.start == None else 0,item.stop,item.step if not item.step == None else 1)
            assert type(start)==int,"Invalid slice start type"
            assert type(stop)==int,"Invalid slice stop type(should be specified and it should be int)"
            assert type(start)==int,"Invalid slice start type"
            for j in range(start,stop,step):
                x.append(self.value[j])
            return
        
 
        if type(item)==int:
            x=self.value[item]
            print item,self.value[item]
        elif type(item)==slice:
            getWithSlice(item)
        elif type(item)==tuple:
            while i<len(item):
                if type(i)==slice:
                    getWithSlice(item[i])
                    i+=1
                elif type(item[i])==int and item[i]>=0:
                    if i+1<len(item) and item[i+1]==Ellipsis:
                         i=getWithEclipsis(i+1)  
                    else:
                        x.append(self.value[item[i]])
                        i+=1
                elif item[i]==Ellipsis:
                    i=getWithEclipsis(i)
                else:
                    raise TypeError("Invalid type or invalid number is been passed")
        else:
            raise TypeError("Invalid type or invalid number is been passed")
        print x
        return x
    
    def __del__(self):
        try:
            free(self.value)
        except:
            pass

