cdef extern from "Netica.h":

    cdef enum:
        EVERY_STATE =-5,
        IMPOSS_STATE,
        UNDEF_STATE  

    ctypedef struct environ_ns:
        pass

    ctypedef struct net_bn:
        pass

    ctypedef struct node_bn:
        pass

    ctypedef enum  errseverity_ns:
        NOTHING_ERR=1,
        REPORT_ERR,
        NOTICE_ERR,
        WARNING_ERR,
        ERROR_ERR,
        XXX_ERR
        
    ctypedef int     state_bn
    ctypedef float   prob_bn
    ctypedef float   util_bn;
    ctypedef double  level_bn;

    ctypedef struct nodelist_bn:
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
    void SetNodeProbs_bn (node_bn* node, const state_bn* parent_states, const prob_bn* probs)
    int GetNodeNumberStates_bn (const node_bn* node)
    const nodelist_bn* GetNodeParents_bn (const node_bn* node)
    int LengthNodeList_bn (const nodelist_bn* nodes)
    state_bn GetStateNamed_bn (const char* name, const node_bn* node)
    node_bn* NthNode_bn (const nodelist_bn* nodes, int index)


cdef extern from "NeticaExV.h":

    void SetNodeProbs (node_bn* node, ...)
    void VSetNodeProbs (node_bn* node, va_list ap)

    void CompileNet_bn (net_bn* net)

    double GetNodeBelief (char* node_name, char* state_name, net_bn* net)

    void EnterFinding (char* node_name, char* state_name, net_bn* net)


cdef extern from "stdarg.h":
    ctypedef struct va_list:
        pass
    ctypedef struct fake_type:
        pass
    void va_start(va_list, void* arg)
    void* va_arg(va_list, fake_type)
    void va_end(va_list)
    fake_type int_type "int" 


cdef class Netica:
    cdef environ_ns *env
    cdef char mesg[600]

    def __str__(self):
        return self.mesg

    def __repr__(self):
        return self.mesg
    
    def __unicode__(self):
       return unicode(self.mesg)

    cpdef NewNeticaEnviron_ns(self,char* license,Netica environ,char* locn):
        if not license[0]:
            licence=NULL
        if not locn[0]:
            locn=NULL
        if type(environ)==Netica:
            self.env=environ.env
        else:
            self.env=NULL
        self.env=NewNeticaEnviron_ns(license,self.env,locn)
        return self

    def InitNetica2_bn(self,Netica env,mesg=None):
        cdef int res
        if type(env)==Netica:
            res = InitNetica2_bn (env.env,self.mesg)
        else:
            res = InitNetica2_bn (self.env,self.mesg)
        if type(mesg)==bytearray:
              while(len(mesg)):
                  mesg.pop()
              for i in self.mesg:
                  mesg.append(i)
        return res

    cpdef NewNet_bn (self,char* name,Netica env):
        net= NewNet()
        net.run(name,env)
        return net

    cpdef NewNode_bn(self,char* name,int num_states,NewNet net):
        node=NewNode()
        node.run(name,num_states,net)
        return node

    def SetNodeStateNames_bn(self,NewNode node,char* state_names):
        SetNodeStateNames_bn(node.node,state_names)

    def AddLink_bn(self,NewNode parent,NewNode child):
        cdef int res
        res=AddLink_bn(parent.node,child.node)
        return res

    def SetNodeTitle_bn(self,NewNode node,char* title):
        SetNodeTitle_bn (node.node,title)

    def SetNodeProbs(self,NewNode node_obj, *arg):
        cdef node_bn* node
        cdef node_bn* curNode
        cdef state_bn parent_states[20]
        cdef prob_bn probs[20]
        cdef char* statename
        cdef int state, numstates
        cdef const nodelist_bn* parents 
        cdef int pn, numparents, i
        node=node_obj.node
        numstates = GetNodeNumberStates_bn (node)
        parents = GetNodeParents_bn (node)
        numparents = LengthNodeList_bn (parents)
        for pn in range(numparents):
            statename = <char*> arg[pn]
            if statename[0] == '*':
                parent_states[pn] = <state_bn> EVERY_STATE
            else:
                curNode=NthNode_bn (parents, pn)
                parent_states[pn] = GetStateNamed_bn (statename, curNode)
        i=numparents
        for state in range(numstates):
            probs[state] = <prob_bn> arg[i]
            i+=1
        SetNodeProbs_bn (node, parent_states, probs)

    def CompileNet_bn(self,NewNet net):
        CompileNet_bn(net.net)

    def GetNodeBelief(self,char* node_name,char* state_name,NewNet net):
        cdef double res
        res = GetNodeBelief (node_name,state_name, net.net)
        return res
    
    def EnterFinding(self,char* node_name, char* state_name, NewNet net):
        EnterFinding(node_name,state_name,net.net)

    def DeleteNet_bn(self,NewNet net): 
        DeleteNet_bn(net.net)

    def CloseNetica_bn(self,Netica env, mesg=None):
        cdef int res
        res = CloseNetica_bn(env.env, self.mesg)
        if type(mesg)==bytearray:
              while(len(mesg)):
                  mesg.pop()
              for i in self.mesg:
                  mesg.append(i)
        return res

cdef class  NewNet:
    cdef net_bn *net
    cpdef run(self,char* name,Netica environ):
        if type(environ)==Netica:
            self.net = NewNet_bn (name, environ.env)
        else:
            self.net = NewNet_bn (name, NULL)

cdef class NewNode:
    cdef node_bn *node
    cpdef run(self,char* name,int num_states,NewNet net):
        self.node=NewNode_bn(name,num_states,net.net)



    
