from libc.stdlib cimport malloc, free
import types
from cpython.string cimport PyString_AsString
import cython
cdef char ** to_cstring_array(list_str):
    cdef char **ret = <char **>malloc(len(list_str) * sizeof(char *))
    for i in xrange(len(list_str)):
        ret[i] = PyString_AsString(list_str[i])
    return ret

cdef extern from "Netica.h":

    cdef enum:
        EVERY_STATE =-5,
        IMPOSS_STATE,
        UNDEF_STATE  

    ctypedef struct environ_ns:
        pass

    ctypedef struct report_ns:
        pass

    ctypedef struct stream_ns:
        pass

    ctypedef struct randgen_ns:
        pass

    ctypedef struct scripter_ns:
        pass

    ctypedef struct net_bn:
        pass

    ctypedef struct node_bn:
        pass

    ctypedef struct nodelist_bn:
        pass

    ctypedef struct caseset_cs:
        pass

    ctypedef struct learner_bn:
        pass

    ctypedef struct tester_bn:
        pass

    ctypedef struct sensv_bn:
        pass

    ctypedef struct setting_bn:
        pass

    ctypedef struct dbmgr_cs:
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
    ctypedef float   util_bn
    ctypedef double  level_bn

        
    ctypedef int     color_ns
    ctypedef long    caseposn_bn
    ctypedef unsigned char bool_ns

    ctypedef enum sampling_bn:
        DEFAULT_SAMPLING,
        JOIN_TREE_SAMPLING,
        FORWARD_SAMPLING 

    ctypedef enum checking_ns:
        NO_CHECK=1,
        QUICK_CHECK,
        REGULAR_CHECK,
        COMPLETE_CHECK,
        QUERY_CHECK=-1

    ctypedef enum errseverity_ns:
        NOTHING_ERR=1,
        REPORT_ERR,
        NOTICE_ERR,
        WARNING_ERR,
        ERROR_ERR,
        XXX_ERR

    ctypedef enum errcond_ns:
        OUT_OF_MEMORY_CND=0x08,
        USER_ABORTED_CND=0x20,
        FROM_WRAPPER_CND=0x40,
        FROM_DEVELOPER_CND=0x80,
        INCONS_FINDING_CND=0x200 

    ctypedef enum eventtype_ns:
        CREATE_EVENT=0x01,
        DUPLICATE_EVENT=0x02,
        REMOVE_EVENT=0x04

    ctypedef enum nodetype_bn:
        CONTINUOUS_TYPE=1,
        DISCRETE_TYPE,
        TEXT_TYPE

    ctypedef enum nodekind_bn:
        NATURE_NODE=1,
        CONSTANT_NODE,
        DECISION_NODE,
        UTILITY_NODE,
        DISCONNECTED_NODE,
        ADVERSARY_NODE 

    cdef enum:
        REAL_VALUE = -25,
        STATE_VALUE = -20,
        GAUSSIAN_VALUE = -15,
        INTERVAL_VALUE = -10,
        STATE_NOT_VALUE = -7,
        LIKELIHOOD_VALUE,
        NO_VALUE = -3

    cdef enum:
        EVERY_STATE = -5,
        IMPOSS_STATE,
        UNDEF_STATE

    cdef enum:
        FIRST_CASE = -15,
        NEXT_CASE,
        NO_MORE_CASES

    cdef enum:
        ENTROPY_SENSV = 0x02,
        REAL_SENSV = 0x04,
        VARIANCE_SENSV = 0x100,
        VARIANCE_OF_REAL_SENSV = 0x104

    ctypedef enum learn_method_bn:
        COUNTING_LEARNING=1,
        EM_LEARNING=3,
        GRADIENT_DESCENT_LEARNING

    cdef enum:
        NEGATIVE_FINDING = -7,
        LIKELIHOOD_FINDING,
        NO_FINDING = -3

    cdef enum:
        NO_VISUAL_INFO=0,
        NO_WINDOW=0x10,
        MINIMIZED_WINDOW=0x30,
        REGULAR_WINDOW=0x70

    cdef enum:
        BELIEF_UPDATE = 0x100

    cdef enum:
        HALT_CALLBACK_RESULT = -1003

    cdef enum:
        ALL_THREADS = 0x20
        
    cdef enum:
        LAST_ENTRY = -10

    cdef enum:
        QUERY_ns = -1



    environ_ns* NewNeticaEnviron_ns (const char* license, environ_ns* env, const char* locn)

    int InitNetica2_bn (environ_ns* env, char* mesg)

    int CloseNetica_bn (environ_ns* env, char* mesg)

    int GetNeticaVersion_bn (const environ_ns* env, const char** version)

    checking_ns ArgumentChecking_ns (checking_ns setting, environ_ns* env)

    void SetPassword_ns (environ_ns* env, const char* password, const char* options)

    const char* SetLanguage_ns (environ_ns* env, const char* language)

    double LimitMemoryUsage_ns (double max_mem, environ_ns* env)

    void SetEnvironUserData_ns (environ_ns* env, int kind, void* data)

    void* GetEnvironUserData_ns (environ_ns* env, int kind)

    report_ns* GetError_ns (environ_ns* env, errseverity_ns severity, const report_ns* after)

    int ErrorNumber_ns (const report_ns* error)

    const char* ErrorMessage_ns (const report_ns* error)

    errseverity_ns ErrorSeverity_ns (const report_ns* error)

    bool_ns ErrorCategory_ns (errcond_ns cond, const report_ns* error)

    void ClearError_ns (report_ns* error)

    void ClearErrors_ns (environ_ns* env, errseverity_ns severity)

    report_ns* NewError_ns (environ_ns* env, int number, errseverity_ns severity, const char* mesg)

    int TestFaultRecovery_ns (environ_ns* env, int test_num)

    int UserAllowed_ns (environ_ns* env, int setting)

    void GetAppWindowPosition_ns (environ_ns* env, int* left, int* top, int* width, int* height, int* status)

    void SetAppWindowPosition_ns (environ_ns* env, int left, int top, int width, int height, int status)

    void PrintToMessagesWindow_ns (environ_ns* env, char* mesg)

    stream_ns* NewFileStream_ns (const char* filename, environ_ns* env, const char* access)

    stream_ns* NewMemoryStream_ns (const char* name, environ_ns* env, const char* access)

    void DeleteStream_ns (stream_ns* file)

    void SetStreamPassword_ns (stream_ns* stream, const char* password)

    void SetStreamContents_ns (stream_ns* stream, const char* buffer, long length, bool_ns copy)

    const char* GetStreamContents_ns (stream_ns* stream, long* length)

    void WriteNet_bn (const net_bn* net, stream_ns* file)

    net_bn* ReadNet_bn (stream_ns* file, int options)

    caseposn_bn WriteNetFindings_bn (const nodelist_bn* nodes, stream_ns* file, long ID_num, double freq)

    void ReadNetFindings2_bn (caseposn_bn* case_posn, stream_ns* file, bool_ns add, const nodelist_bn* nodes, long* ID_num, double* freq)

    int SetCaseFileDelimChar_ns (int newchar, environ_ns* env)

    int SetMissingDataChar_ns (int newchar, environ_ns* env)

    net_bn* NewNet_bn (const char* name, environ_ns* env)

    net_bn* CopyNet_bn (const net_bn* net, const char* new_name, environ_ns* new_env, const char* options)

    void DeleteNet_bn (net_bn* net)

    net_bn* GetNthNet_bn (int nth, environ_ns* env)

    node_bn* NewNode_bn (const char* name, int num_states, net_bn* net)

    nodelist_bn* CopyNodes_bn (const nodelist_bn* nodes, net_bn* new_net, const char* options)

    void DeleteNode_bn (node_bn* node)

    void SetNetName_bn (net_bn* net, const char* name)

    void SetNetTitle_bn (net_bn* net, const char* title)

    void SetNetComment_bn (net_bn* net, const char* comment)

    void SetNetElimOrder_bn (net_bn* net, const nodelist_bn* elim_order)

    int SetNetAutoUpdate_bn (net_bn* net, int auto_update)

    void SetNetUserField_bn (net_bn* net, const char* name, const void* data, int length, int kind)

    void SetNetUserData_bn (net_bn* net, int kind, void* data)

    void AddNetListener_bn (net_bn* net, int callback (const net_bn* net, eventtype_ns what, void* object, void* info), void* object, int filter)

    void SetNodeName_bn (node_bn* node, const char* name)

    void SetNodeTitle_bn (node_bn* node, const char* title)

    void SetNodeComment_bn (node_bn* node, const char* comment)

    void SetNodeLevels_bn (node_bn* node, int num_states, const level_bn* levels)

    void SetNodeKind_bn (node_bn* node, nodekind_bn kind)

    void SetNodeStateName_bn (node_bn* node, state_bn state, const char* state_name)

    void SetNodeStateNames_bn (node_bn* node, const char* state_names)

    void SetNodeStateTitle_bn (node_bn* node, state_bn state, const char* state_title)

    void SetNodeStateComment_bn (node_bn* node, state_bn state, const char* state_comment)

    void SetNodeInputName_bn (node_bn* node, int link_index, const char* link_name)

    void SetNodeEquation_bn (node_bn* node, const char* eqn)

    void SetNodeFuncState_bn (node_bn* node, const state_bn* parent_states, state_bn st)

    void SetNodeFuncReal_bn (node_bn* node, const state_bn* parent_states, double val)

    void SetNodeProbs_bn (node_bn* node, const state_bn* parent_states, const prob_bn* probs)

    void SetNodeExperience_bn (node_bn* node, const state_bn* parent_states, double experience)

    void DeleteNodeTables_bn (node_bn* node)

    void SetNodeUserField_bn (node_bn* node, const char* name, const void* data, int length, int kind)

    void SetNodeUserData_bn (node_bn* node, int kind, void* data)

    void AddNodeListener_bn (node_bn* node, int callback (const node_bn* node, eventtype_ns what, void* object, void* info), void* object, int filter)

    void SetNodeVisPosition_bn (node_bn* node, void* vis, double x, double y)

    void SetNodeVisStyle_bn (node_bn* node, void* vis, const char* style)

    const char* GetNetName_bn (const net_bn* net)

    const char* GetNetTitle_bn (const net_bn* net)

    const char* GetNetComment_bn (const net_bn* net)

    const nodelist_bn* GetNetNodes2_bn (const net_bn* net, const char options[])

    node_bn* GetNodeNamed_bn (const char* name, const net_bn* net)

    const char* GetNetFileName_bn (const net_bn* net)

    int GetNetAutoUpdate_bn (const net_bn* net)

    const nodelist_bn* GetNetElimOrder_bn (const net_bn* net)

    const char* GetNetUserField_bn (const net_bn* net, const char* name, int* length, int kind)

    void GetNetNthUserField_bn (const net_bn* net, int index, const char** name, const char** value, int* length, int kind)

    void* GetNetUserData_bn (const net_bn* net, int kind)

    net_bn* GetNodeNet_bn (const node_bn* node)

    const char* GetNodeName_bn (const node_bn* node)

    const char* GetNodeTitle_bn (const node_bn* node)

    const char* GetNodeComment_bn (const node_bn* node)

    nodetype_bn GetNodeType_bn (const node_bn* node)

    nodekind_bn GetNodeKind_bn (const node_bn* node)

    int GetNodeNumberStates_bn (const node_bn* node)

    const level_bn* GetNodeLevels_bn (const node_bn* node)

    const char* GetNodeStateName_bn (const node_bn* node, state_bn state)

    const char* GetNodeStateTitle_bn (const node_bn* node, state_bn state)

    const char* GetNodeStateComment_bn (const node_bn* node, state_bn state)

    state_bn GetStateNamed_bn (const char* name, const node_bn* node)

    const nodelist_bn* GetNodeParents_bn (const node_bn* node)

    const nodelist_bn* GetNodeChildren_bn (const node_bn* node)

    const char* GetNodeInputName_bn (const node_bn* node, int link_index)

    int GetInputNamed_bn (const char* name, const node_bn* node)

    const char* GetNodeEquation_bn (const node_bn* node)

    state_bn GetNodeFuncState_bn (const node_bn* node, const state_bn* parent_states)

    double GetNodeFuncReal_bn (const node_bn* node, const state_bn* parent_states)

    const prob_bn* GetNodeProbs_bn (const node_bn* node, const state_bn* parent_states)

    double GetNodeExperience_bn (const node_bn* node, const state_bn* parent_states)

    bool_ns HasNodeTable_bn (const node_bn* node, bool_ns* complete)

    bool_ns IsNodeDeterministic_bn (const node_bn* node)

    const char* GetNodeUserField_bn (const node_bn* node, const char* name, int* length, int kind)

    void GetNodeNthUserField_bn (const node_bn* node, int index, const char** name, const char** value, int* length, int kind)

    void* GetNodeUserData_bn (const node_bn* node, int kind)

    void GetNodeVisPosition_bn (const node_bn* node, void* vis, double* x, double* y)

    const char* GetNodeVisStyle_bn (const node_bn* node, void* vis)

    int AddLink_bn (node_bn* parent, node_bn* child)

    void DeleteLink_bn (int link_index, node_bn* child)

    void SwitchNodeParent_bn (int link_index, node_bn* node, node_bn* new_parent)

    bool_ns IsNodeRelated_bn (const node_bn* related_node, const char* relation, const node_bn* node)

    void GetRelatedNodes_bn (nodelist_bn* related_nodes, const char* relation, const node_bn* node)

    void GetRelatedNodesMult_bn (nodelist_bn* related_nodes, const char* relation, const nodelist_bn* nodes)

    nodelist_bn* NewNodeList2_bn (int length, const net_bn* net)

    void DeleteNodeList_bn (nodelist_bn* nodes)

    void ClearNodeList_bn (nodelist_bn* nodes)

    int LengthNodeList_bn (const nodelist_bn* nodes)

    void AddNodeToList_bn (node_bn* node, nodelist_bn* nodes, int index)

    node_bn* RemoveNthNode_bn (nodelist_bn* nodes, int index)

    node_bn* NthNode_bn (const nodelist_bn* nodes, int index)

    void SetNthNode_bn (nodelist_bn* nodes, int index, node_bn* node)

    int IndexOfNodeInList_bn (const node_bn* node, const nodelist_bn* nodes, int start_index)

    nodelist_bn* DupNodeList_bn (const nodelist_bn* nodes)

    void MapStateList_bn (const state_bn* src_states,  const nodelist_bn* src_nodes, state_bn* dest_states, const nodelist_bn* dest_nodes)

    void ReviseCPTsByFindings_bn (const nodelist_bn* nodes, int updating, double degree)

    void ReviseCPTsByCaseFile_bn (stream_ns* file, const nodelist_bn* nodes, int updating, double degree)

    void FadeCPTable_bn (node_bn* node, double degree)

    void AddNodeStates_bn (node_bn* node, state_bn first_state, const char* state_names, int num_states, double cpt_fill)

    void RemoveNodeState_bn (node_bn* node, state_bn state)

    void ReorderNodeStates_bn (node_bn* node, const state_bn* new_order)

    void EquationToTable_bn (node_bn* node, int num_samples, bool_ns samp_unc, bool_ns add_exist)

    void ReverseLink_bn (node_bn* parent, node_bn* child)

    void AbsorbNodes_bn (nodelist_bn* nodes)

    void EnterFinding_bn (node_bn* node, state_bn state)

    void EnterFindingNot_bn (node_bn* node, state_bn state)

    void EnterNodeValue_bn (node_bn* node, double value)

    void EnterNodeLikelihood_bn (node_bn* node, const prob_bn* likelihood)

    void EnterNodeCalibration_bn (node_bn* node, const prob_bn* calibration)

    void EnterIntervalFinding_bn (node_bn* node, double low, double high)

    void EnterGaussianFinding_bn (node_bn* node, double mean, double std_dev)

    state_bn GetNodeFinding_bn (const node_bn* node)

    double GetNodeValueEntered_bn (const node_bn* node)

    const prob_bn* GetNodeLikelihood_bn (const node_bn* node)

    void RetractNodeFindings_bn (node_bn* node)

    void RetractNetFindings_bn (net_bn* net)

    state_bn CalcNodeState_bn (node_bn* node)

    double CalcNodeValue_bn (node_bn* node)

    void CompileNet_bn (net_bn* net)

    void UncompileNet_bn (net_bn* net)

    double SizeCompiledNet_bn (net_bn* net, int method)

    bool_ns IsBeliefUpdated_bn (const node_bn* node)

    const prob_bn* GetNodeBeliefs_bn (node_bn* node)

    double GetNodeExpectedValue_bn (node_bn* node, double* std_dev, double* x3, double* x4)

    const util_bn* GetNodeExpectedUtils_bn (node_bn* node)

    double FindingsProbability_bn (net_bn* net)

    util_bn GetNetExpectedUtility_bn (net_bn* net)

    double JointProbability_bn (const nodelist_bn* nodes, const state_bn* states)

    void MostProbableConfig_bn (const nodelist_bn* nodes, state_bn* config, int nth)

    sensv_bn* NewSensvToFinding_bn (const node_bn* t_node, const nodelist_bn* v_nodes, int what_calc)

    void DeleteSensvToFinding_bn (sensv_bn* s)

    double GetMutualInfo_bn (sensv_bn* s, const node_bn* v_node)

    double GetVarianceOfReal_bn (sensv_bn* s, const node_bn* v_node)

    int GenerateRandomCase_bn (const nodelist_bn* nodes, sampling_bn method, double num, randgen_ns* rand)

    void AddNodeToNodeset_bn (node_bn* node, const char* nodeset)

    void RemoveNodeFromNodeset_bn (node_bn* node, const char* nodeset)

    bool_ns IsNodeInNodeset_bn (const node_bn* node, const char* nodeset)

    const char* GetAllNodesets_bn (const net_bn* net, bool_ns include_system, void* vis)

    color_ns SetNodesetColor_bn (const char* nodeset, color_ns color, net_bn* net, void* vis)
    
    void ReorderNodesets_bn (net_bn* net, const char* nodeset_order, void* vis)

    caseset_cs* NewCaseset_cs (const char* name, environ_ns* env)

    void DeleteCaseset_cs (caseset_cs* cases)

    void AddFileToCaseset_cs (caseset_cs* cases, const stream_ns* file, double degree, const char* options)

    void WriteCaseset_cs (const caseset_cs* cases, stream_ns* file, const char* options)

    dbmgr_cs* NewDBManager_cs (const char* connect_str, const char* options, environ_ns* env)

    void DeleteDBManager_cs (dbmgr_cs* dbmgr)

    void ExecuteDBSql_cs (dbmgr_cs* dbmgr, const char* sql_cmnd, const char* options)

    void InsertFindingsIntoDB_bn (dbmgr_cs* dbmgr, const nodelist_bn* nodes, const char* column_names, const char* tables, const char* options)

    void AddDBCasesToCaseset_cs (caseset_cs* cases, dbmgr_cs* dbmgr, double degree, const nodelist_bn* nodes, const char* column_names, const char* tables, const char* condition, const char* options)

    void AddNodesFromDB_bn (dbmgr_cs* dbmgr, net_bn* net, const char* column_names, const char* tables, const char* condition, const char* options)

    learner_bn* NewLearner_bn (learn_method_bn method, const char* options, environ_ns* env)

    void DeleteLearner_bn (learner_bn* algo)

    int SetLearnerMaxIters_bn (learner_bn* algo, int max_iters)

    double SetLearnerMaxTol_bn (learner_bn* algo, double log_likeli_tol)

    void LearnCPTs_bn (learner_bn* algo, const nodelist_bn* nodes, const caseset_cs* cases, double degree)

    tester_bn* NewNetTester_bn (const nodelist_bn* test_nodes, const nodelist_bn* unobsv_nodes, int tests)

    void DeleteNetTester_bn (tester_bn* test)

    void TestWithCaseset_bn (tester_bn* test, const caseset_cs* cases)

    double GetTestErrorRate_bn (const tester_bn* test, const node_bn* node)

    double GetTestLogLoss_bn (const tester_bn* test, const node_bn* node)

    double GetTestQuadraticLoss_bn (const tester_bn* test, const node_bn* node)

    double GetTestConfusion_bn (const tester_bn* test, const node_bn* node, state_bn predicted, state_bn actual)

    void SetNetNumUndos_bn (net_bn* net, int count_limit, double memory_limit, const char* options)

    int UndoNetLastOper_bn (net_bn* net, double to_when)

    int RedoNetOper_bn (net_bn* net, double to_when)

    int GetNodeLabel_bn (const node_bn* node, unsigned short* label, int max_chars, const char* options)

    int GetNodeStateLabel_bn (const node_bn* node, state_bn state, unsigned short* label, int max_chars, const char* options)

    const char* CreateCustomReport_bn (net_bn* net, const nodelist_bn* sel_nodes, const char* templat, const char* options)

    const char* ControlConcurrency_ns (environ_ns* env, const char* command, const char* value)

    const char* ControlNetCaching_bn (net_bn* net, const char* command, const char* value, const nodelist_bn* nodes)

    net_bn* ExpandNet_bn (net_bn* net, int dimn, double result_time, double burn_time, const char* options)

    void SetNodeInputDelay_bn (node_bn* node, int link_index, int dimension, const char* delay)

    void SetNodePersistance_bn (node_bn* node, int dimension, const char* persistance)

    node_bn* GetNodeAtTime_bn (net_bn* net, const char* name, double* time)

    randgen_ns* NewRandomGenerator_ns (const char* seed, environ_ns* env, const char* options)

    void DeleteRandomGen_ns (randgen_ns* rand)

    const char* GetRandomGenState_ns (randgen_ns* rand, const char* options)

    double GenerateRandomNumbers_ns (randgen_ns* rand, double* results, int num, const char* options)

    void SetNetRandomGen_bn (net_bn* net, randgen_ns* rand, bool_ns is_private)

    void EnterAction_bn (node_bn* node, state_bn state)

    void EnterActionValue_bn (node_bn* node, double value)

    void EnterActionRandomized_bn (node_bn* node, const prob_bn* probs)

    void CleanupThreadEnding_ns (environ_ns* env)

    scripter_ns* NewScripter_ns (environ_ns* env, const char* file_name, const char* language, const char* options, const char* script)

    void DeleteScripter_ns (scripter_ns* scr)

    const char* ExecuteScript_ns (scripter_ns* scr, const char* options)

    void StartScriptRecorder_ns (scripter_ns* scr, const char* file_name, const char* language, const char* options)

    const char* StopScriptRecorder_ns (scripter_ns* scr, const char* file_name, const char* options)

    const char* GetScriptVar_ns (scripter_ns* scr, const char* name, const char* type)

    void ClearScriptVars_ns (scripter_ns* scr, const char* options)

    setting_bn* NewSetting_bn (const nodelist_bn* nodes, bool_ns load)

    void DeleteSetting_bn (setting_bn* cas)

    void SetSettingState_bn (setting_bn* cas, const node_bn* node, state_bn state)

    state_bn GetSettingState_bn (const setting_bn* cas, const node_bn* node)

    void ZeroSetting_bn (setting_bn* cas)

    bool_ns NextSetting_bn (setting_bn* cas)

    void MostProbableSetting_bn (net_bn* net, setting_bn* cas, int nth)

    double NthProb_bn (const prob_bn* probs, state_bn state)

    double NthLevel_bn (const level_bn* levels, state_bn state)

    int GetChars_ns (const char* str, int index, unsigned short* dest, int num)

    int NthChar_ns (const char* str, int index)

    void SetNthState_bn (state_bn* states, int index, state_bn state)

    void OptimizeDecisions_bn (const nodelist_bn* nodes)
    
    nodelist_bn* NewNodeList_bn (int length, environ_ns* env)
    
    double GetUndefDbl_ns()
    double GetInfinityDbl_ns()



cdef extern from "NeticaExV.h":

    void CompileNet_bn (net_bn* net)

    double GetNodeBelief (char* node_name, char* state_name, net_bn* net)

    void EnterFinding (char* node_name, char* state_name, net_bn* net)

    int main_ex ()

    node_bn* GetNode (char* node_name, net_bn* net)
        
    void EnterFinding (char* node_name, char* state_name, net_bn* net)
        
    void SetNodeFinding (node_bn* node, state_bn state)
        
    void SetNodeValue (node_bn* node, double value)
        
    double GetNodeBelief (char* node_name, char* state_name, net_bn* net)
        
    void SetNodeProbs (node_bn* node, ...)
        
    void SetNodeFuncState (node_bn* node, state_bn value, ...)
        
    void SetNodeFuncReal (node_bn* node, double value, ...)
        
    void SetNodeExper (node_bn* node, double value, ...)
        
    void MakeProbsUniform (node_bn* node)
        
    void GetNodeAllProbs (node_bn* node, prob_bn* probs, int num_entries)
        
    bool_ns NextStates (state_bn* states, const nodelist_bn* nodes)
        
    void PrintNodeList (nodelist_bn* nodes)
        
    void RetractFindingsOfNodes (nodelist_bn* nodes, bool_ns do_consts_too)
        
    int FindNodeNamed (const char* name, const nodelist_bn* nodes)
        
    int IndexOfNodeInList (const node_bn* node, const nodelist_bn* nodes)
        
    void RemoveOneNodeFromList (node_bn* node, nodelist_bn* nodes)
        
    void RemoveNodeFromListIfThere (node_bn* node, nodelist_bn* nodes)
        
    void RemoveNthNodeFast (int index, nodelist_bn* nodes)
        
    void DeleteLink (node_bn* parent, node_bn* child)
        
    void DeleteLinks (node_bn* parent, node_bn* child)
        
    void DeleteLinksEntering (node_bn* child)
        
    void SwitchNodeParent (node_bn* parent, node_bn* child, node_bn* new_parent)
        
    void DeleteNodes (nodelist_bn* nodes)
        
    bool_ns IsLinkDisconnected (int link_index, const node_bn* node)
    
    nodelist_bn* TransferNodes (nodelist_bn* nodes, net_bn* new_net)
        
    node_bn* DupNode (node_bn* node)
        
    node_bn* DuplicateNode (node_bn* node, net_bn* new_net)
        
    net_bn* DuplicateNet (net_bn* net, const char* newname)
        
    net_bn* NetNamed (const char* name)
        
    node_bn* FormCliqueWith (const nodelist_bn* nodes)
        
    void AbsorbNode (node_bn* node)
        
    void DeleteNetTables (net_bn* net)
        
    void FadeCPTables (const nodelist_bn* nodes, double degree)
        
    void PrintNeticaVersion ()
        
    void PrintErrors ()
        
    report_ns* NewError (environ_ns* env, int number, errseverity_ns severity, const char* mesg, ...)
        
    void ClearErrors (environ_ns* env, errseverity_ns severity)

    void SetNetUserString (net_bn* net, const char* fieldname, const char* str)
    
    const char* GetNetUserString (net_bn* net, const char* fieldname)
    
    void SetNetUserInt (net_bn* net, const char* fieldname, int num)
    
    long GetNetUserInt (net_bn* net, const char* fieldname)
    
    void SetNetUserNumber (net_bn* net, const char* fieldname, double num)
    
    double GetNetUserNumber (net_bn* net, const char* fieldname)
    
    void SetNodeUserString (node_bn* node, const char* fieldname, const char* str)
    
    const char* GetNodeUserString (node_bn* node, const char* fieldname)
    
    void SetNodeUserInt (node_bn* node, const char* fieldname, int num)
    
    long GetNodeUserInt (node_bn* node, const char* fieldname)
    
    void SetNodeUserNumber (node_bn* node, const char* fieldname, double num)
    
    double GetNodeUserNumber (node_bn* node, const char* fieldname)
    
    void PrintConfusionMatrix (tester_bn* tester, node_bn* node)
    
    void CopyNodeRelation_bn (node_bn* dest, const node_bn* src, const nodelist_bn* parent_order_dest)
    
    int MultiDimnIndex (const state_bn states[], const nodelist_bn* nodes)
    
    double SizeCartesianProduct (const nodelist_bn* nodes)
    
    node_bn* MapNode (const node_bn* node, const net_bn* dest_net)

    nodelist_bn* MapNodeList (const nodelist_bn* nodes, const net_bn* dest_net)

    nodelist_bn* MapNodeList1 (const nodelist_bn* oldorder, const nodelist_bn* oldnodes, const nodelist_bn* newnodes)

    nodelist_bn* DisconnectNodeGroup (nodelist_bn* nodes)

    char* NodeListToString (const nodelist_bn* nodes)
    
    long CountCasesInFile (stream_ns* casefile)

    int RemoveUnusedStates (node_bn* node)

    int* MakeInverseOrdering (const int order[], int num, int invorder[])

    void SetNodeStateNames (node_bn* node, ...)

    void SetNodeFuncValue (node_bn* node, double value, ...)

    double ExpectedValue (node_bn* node, double* stddev)

    int PositionInNodeList (const node_bn* node, const nodelist_bn* nodes)

    void RemoveNodeFromList (node_bn* node, nodelist_bn* nodes)

    void SetNodeAllProbs (node_bn* node, const prob_bn* probs)
    



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
        self.env=environ.env if type(environ)==Netica else NULL
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
    
    def CloseNetica_bn(self,Netica env, mesg=None):
        cdef int res
        res = CloseNetica_bn(env.env, self.mesg)
        if type(mesg)==bytearray:
              while(len(mesg)):
                  mesg.pop()
              for i in self.mesg:
                  mesg.append(i)
        return res

    def GetNeticaVersion_bn (self,Netica environ, _version = None):
        cdef int res
        cdef char* version 
        res = GetNeticaVersion_bn (environ.env if type(environ)==Netica else NULL,&version)
        if type(_version)==bytearray:
              while(len(_version)):
                  _version.pop()
              for i in version:
                  _version.append(i)
        return res

    def ArgumentChecking_ns (self,checking_ns setting, Netica environ):
        cdef checking_ns res
        res=ArgumentChecking_ns (setting, environ.env if type(environ)==Netica else NULL)
        return res
    
    def SetPassword_ns (self,Netica environ,char* password,char* options):
        SetPassword_ns (environ.env if type(environ)==Netica else NULL,password,options)

    def SetLanguage_ns (self,Netica environ, char* language):
        cdef char* res
        res = SetLanguage_ns (environ.env if type(environ)==Netica else NULL,language)
        return res

    def LimitMemoryUsage_ns (self,double max_mem, Netica environ):
        cdef double res
        res = LimitMemoryUsage_ns (max_mem,environ.env if type(environ)==Netica else NULL)
        return res

    def SetEnvironUserData_ns (self,Netica environ, int kind, UserData data):
        SetEnvironUserData_ns (environ.env if type(environ)==Netica else NULL,kind,data.value)

    def GetEnvironUserData_ns (self,Netica environ, int kind):
        res = UserData()
        res.value=GetEnvironUserData_ns (environ.env if type(environ)==Netica else NULL,kind)
        return res

    def GetError_ns (self,Netica environ, ErrSeverity severity, Report after):
        res=Report()
        res.value = GetError_ns (environ.env if type(environ)==Netica else NULL, severity.value, after.value)
        return res
    
    def ErrorNumber_ns (self,Report error):
        cdef int res
        res = ErrorNumber_ns (error.value)
        return res

    def ErrorMessage_ns (self,Report error):
        cdef char* res
        res = ErrorMessage_ns (error.value)
        return res

    def ErrorSeverity_ns (self,Report error):
        res = ErrSeverity()
        res.value = ErrorSeverity_ns (error.value)
        return res
    
    def ErrorCategory_ns (self,ErrorCondition cond, Report error):
        cdef bool_ns res
        res = ErrorCategory_ns (cond.value, error.value)
        return res

    def ClearError_ns (self,Report error):
        ClearError_ns (error.value)

    def ClearErrors_ns (self,Netica environ, ErrSeverity severity):
        ClearErrors_ns (environ.env if type(environ)==Netica else NULL, severity.value)

    def NewError_ns (self,Netica environ, int number, ErrSeverity severity, mesg=None):
        res = Report()
        res.value = NewError_ns (environ.env if type(environ)==Netica else NULL,number, severity.value, self.mesg)
        if type(mesg)==bytearray:
            while(len(mesg)):
                mesg.pop()
            for i in self.mesg:
                mesg.append(i)
        return res
    
    def TestFaultRecovery_ns (self,Netica environ, int test_num):
        cdef int res
        res = TestFaultRecovery_ns (environ.env if type(environ)==Netica else NULL, test_num)
        return res

    def UserAllowed_ns (self,Netica environ, int setting):
        cdef int res
        res = UserAllowed_ns (environ.env if type(environ)==Netica else NULL, setting)
        return res

    def GetAppWindowPosition_ns (self,Netica environ,int left=0,int top=0,int width=0,int height=0,int status=0):        
        GetAppWindowPosition_ns (environ.env if type(environ)==Netica else NULL, &left, &top, &width, &height, &status)
        return (left, top, width, height, status)
    
    def SetAppWindowPosition_ns (self,Netica environ, int left, int top, int width, int height, int status):
        SetAppWindowPosition_ns (environ.env if type(environ)==Netica else NULL,left,top,width,height,status)

    def PrintToMessagesWindow_ns (self,Netica environ, mesg=None):
        PrintToMessagesWindow_ns (environ.env if type(environ)==Netica else NULL, self.mesg)
        if type(mesg)==bytearray:
            while(len(mesg)):
                mesg.pop()
            for i in self.mesg:
                mesg.append(i)
        return self.mesg

    def NewFileStream_ns (self,char* filename, Netica environ,access=None):
        cdef char* _access
        if access:
            _access=PyString_AsString(access)
        else:
            _access=NULL
        res = Stream()
        res.value = NewFileStream_ns (filename, environ.env if type(environ)==Netica else NULL, _access)
        if type(access)==bytearray:
            while(len(access)):
                access.pop()
            for i in _access:
                access.append(i)
        free(_access)
        return res
    
    def NewMemoryStream_ns (self,char* name, Netica environ, access=None):
        cdef char* _access
        if access:
            _access = PyString_AsString(access)
        else:
            NULL
        res = Stream()
        res.value = NewMemoryStream_ns (name, environ.env if type(environ)==Netica else NULL, _access)
        if type(access)==bytearray:
            while(len(access)):
                access.pop()
            for i in _access:
                access.append(i)
        free(_access)
        return res

    def DeleteStream_ns (self,Stream _file):
        DeleteStream_ns (_file.value if type(_file)==Stream else NULL)

    def SetStreamPassword_ns (self,Stream stream, char* password):
        SetStreamPassword_ns (stream.value if type(stream)==Stream else NULL, password)
        
    def SetStreamContents_ns (self,Stream stream,_buffer, long length=0, bool_ns copy=True):
        if not length:
            length=len(_buffer)
        SetStreamContents_ns (stream.value if type(stream)==Stream else NULL,_buffer,length, copy)
        

    def GetStreamContents_ns (self,Stream stream,long length=0):
        cdef char* res
        res = GetStreamContents_ns (stream.value if type(stream)==Stream else NULL, &length)
        return res

    def WriteNet_bn (self, NewNet net, Stream _file):
        WriteNet_bn (net.value, _file.value if type(_file)==Stream else NULL)

    def ReadNet_bn (self,Stream _file, int options):
        res = NewNet()
        res.value = ReadNet_bn ( _file.value if type(_file)==Stream else NULL,options)
        return res

    def WriteNetFindings_bn (self, NodeList nodes, Stream _file, long ID_num, double freq):
        cdef caseposn_bn res
        res = WriteNetFindings_bn (nodes.value, _file.value if type(_file)==Stream else NULL, ID_num, freq)
        return res

    def ReadNetFindings2_bn (self,caseposn_bn case_posn, Stream _file, bool_ns add, NodeList nodes, long ID_num=0, double freq=0):
        ReadNetFindings2_bn (&case_posn,  _file.value if type(_file)==Stream else NULL,add, nodes.value, &ID_num, &freq)
        return {
            "case_posn" : case_posn,
            "ID_num" :ID_num,
            "freq" : freq
            }
    def SetCaseFileDelimChar_ns (self,int newchar, Netica environ):
        cdef int res
        res = SetCaseFileDelimChar_ns (newchar, environ.env if type(environ)==Netica else NULL)
        return res
    
    def SetMissingDataChar_ns (int newchar, Netica environ):
        cdef int res
        res = SetMissingDataChar_ns (newchar, environ.env if type(environ)==Netica else NULL)
        return res

    def DeleteNet_bn(self,NewNet net): 
        DeleteNet_bn(net.value)

    cpdef NewNet_bn (self,char* name,Netica env):
        net = NewNet()
        net.run(name,env)
        return net

    def CopyNet_bn (self,NewNet net, char* new_name, Netica environ, char* options):
        res = NewNet()
        res.value = CopyNet_bn (net.value,new_name, environ.env, options)
        return res

    
    def GetNthNet_bn (self,int nth, Netica environ):
        res = NewNet()
        res.value = GetNthNet_bn (nth, environ.env)
        return res
    
    cpdef NewNode_bn(self,char* name,int num_states,NewNet net):
        node=NewNode()
        node.run(name,num_states,net)
        return node
    
    def CopyNodes_bn (self,NodeList nodes, NewNet new_net,char* options):
        res = NodeList()
        res.value = CopyNodes_bn (nodes.value, new_net.value, options)
        return res

    def DeleteNode_bn (self,NewNode node):
        DeleteNode_bn (node.value if type(node)==NewNode else NULL)

    def SetNetName_bn (self,NewNet net,char* name):
        SetNetName_bn (net.value, name)

    def SetNetTitle_bn (self,NewNet net,char* title):
        SetNetTitle_bn (net.value,title)

    def SetNetComment_bn (self,NewNet net,char* comment):
        SetNetComment_bn (net.value,comment)

    def SetNetElimOrder_bn (self,NewNet net, NodeList elim_order):
        SetNetElimOrder_bn (net.value, elim_order.value)

    def SetNetAutoUpdate_bn (self,NewNet net, int auto_update):
        cdef int res
        res = SetNetAutoUpdate_bn (net.value, auto_update)
        return res

    def SetNetUserField_bn (self,NewNet net,char* name,UserData data, int length, int kind):
        SetNetUserField_bn (net.value,name,data.value,length,kind)

    def SetNetUserData_bn (self,NewNet net, int kind, UserData data):
        SetNetUserData_bn (net.value,kind,data.value)

    def SetNodeName_bn (self,NewNode node, char* name):
        SetNodeName_bn (node.value, name)

    def SetNodeTitle_bn (self,NewNode node, char* title):
        SetNodeTitle_bn (node.value,title)

    def SetNodeComment_bn (self,NewNode node,char* comment):
        SetNodeComment_bn (node.value, comment)

    def SetNodeLevels_bn (self,NewNode node, int num_states, level_bn levels):
        SetNodeLevels_bn (node.value,num_states, &levels)
        return levels

    def SetNodeKind_bn (self,NewNode node, nodekind_bn kind):
        SetNodeKind_bn (node.value, kind)

    def SetNodeStateName_bn (self,NewNode node, state_bn state, char* state_name):
        SetNodeStateName_bn (node.value, state, state_name)
        
    def SetNodeStateNames_bn (self,NewNode node, char* state_names):
        SetNodeStateNames_bn (node.value,state_names)

    def SetNodeStateTitle_bn (self,NewNode node, state_bn state,char* state_title):
        SetNodeStateTitle_bn (node.value,state,state_title)
        
    def SetNodeStateComment_bn (self,NewNode node, state_bn state,char* state_comment):
        SetNodeStateComment_bn (node.value,state,state_comment)

    def SetNodeInputName_bn (self,NewNode node, int link_index, char* link_name):
            SetNodeInputName_bn (node.value, link_index, link_name)

    def SetNodeEquation_bn (self,NewNode node,char* eqn):
        SetNodeEquation_bn (node.value,eqn)

    def SetNodeFuncState_bn (self,NewNode node, list parent_states, state_bn st):
        cdef state_bn* ps
        ps = <state_bn *>malloc(len(parent_states)*cython.sizeof(state_bn))
        for i in range(len(parent_states)):
            ps[i]=<state_bn>parent_states[i]
        SetNodeFuncState_bn (node.value, ps, st)
        free(ps)

    def SetNodeFuncReal_bn (self,NewNode node, list parent_states, double val):
        cdef state_bn* ps
        ps = <state_bn *>malloc(len(parent_states)*cython.sizeof(state_bn))
        for i in range(len(parent_states)):
            ps[i]=<state_bn>parent_states[i]
        SetNodeFuncReal_bn (node.value,ps,val)
        free(ps)

    def SetNodeProbs_bn (self,NewNode node, list parent_states, list probs):
        cdef prob_bn* _probs
        cdef state_bn* ps
        ps = <state_bn *>malloc(len(parent_states)*cython.sizeof(state_bn))
        for i in range(len(parent_states)):
            ps[i]=<state_bn>parent_states[i]
        _probs = <prob_bn *>malloc(len(probs)*cython.sizeof(prob_bn))
        for i in range(len(probs)):
            _probs[i]=<state_bn>probs[i]
        SetNodeProbs_bn (node.value, ps, _probs)
        free(ps)
        free(_probs)

    def SetNodeExperience_bn (self,NewNode node, list parent_states, double experience):
        cdef state_bn* ps
        ps = <state_bn *>malloc(len(parent_states)*cython.sizeof(state_bn))
        for i in range(len(parent_states)):
            ps[i]=<state_bn>parent_states[i]
        SetNodeExperience_bn (node.value, ps,experience)
        free(ps)

    def DeleteNodeTables_bn (self,NewNode node):
        DeleteNodeTables_bn (node.value)
    
    def EnterFinding_bn (self,NewNode node, state_bn state):
        EnterFinding_bn (node.value,state)

    def EnterFindingNot_bn (self,NewNode node, state_bn state):
        EnterFindingNot_bn (node.value,state)


    def EnterNodeValue_bn (self,NewNode node, double value):
        EnterNodeValue_bn (node.value,value)

    def EnterNodeLikelihood_bn (self,NewNode node, list likelihood):
        cdef prob_bn* _likelihood
        _likelihood = <prob_bn *>malloc(len(likelihood)*cython.sizeof(prob_bn))
        for i in range(len(likelihood)):
            _likelihood[i]=<prob_bn>likelihood[i]
        EnterNodeLikelihood_bn (node.value, _likelihood)
        free(_likelihood)

    def EnterNodeCalibration_bn (self,NewNode node, list calibration):
        cdef prob_bn* _calibration
        _calibration = <prob_bn *>malloc(len(calibration)*cython.sizeof(prob_bn))
        for i in range(len(calibration)):
            _calibration[i]=<prob_bn>calibration[i]
        EnterNodeCalibration_bn (node.value, _calibration)
        free(_calibration)

    def EnterIntervalFinding_bn (self,NewNode node, double low, double high):
        EnterIntervalFinding_bn (node.value,low,high)

    def EnterGaussianFinding_bn (self,NewNode node, double mean, double std_dev):
        EnterGaussianFinding_bn (node.value, mean,std_dev)

    def GetNodeFinding_bn (self,NewNode node):
        cdef state_bn res
        res = GetNodeFinding_bn (node.value)
        return res

    def GetNodeValueEntered_bn (self,NewNode node):
        cdef double res
        res = GetNodeValueEntered_bn (node.value)
        return res
    
    def GetNodeLikelihood_bn (self,NewNode node):
##        cdef  prob_bn* res
##        cdef int size
##        size = <int><prob_bn>GetNodeNumberStates_bn (node.value)    
##        res = GetNodeLikelihood_bn (node.value)
##        return [i for i in res[:size]]
        res = FloatList()
        res.value = GetNodeLikelihood_bn (node.value)
        return res

    def RetractNodeFindings_bn (self,NewNode node):
        RetractNodeFindings_bn (node.value)     

    def RetractNetFindings_bn (self,NewNet net):
        RetractNetFindings_bn (net.value)

    def FindingsProbability_bn (self,NewNet net):
        cdef double res
        res = FindingsProbability_bn (net.value)
        return res

    def CompileNet_bn (self,NewNet net):
        CompileNet_bn (net.value)

    def UncompileNet_bn (self,NewNet net):
        UncompileNet_bn (net.value)

    def SizeCompiledNet_bn (self,NewNet net, int method):
        cdef double res
        res = SizeCompiledNet_bn (net.value,method)
        return res

    def CreateCustomReport_bn (self,NewNet net,NodeList sel_nodes,char* templat=NULL, char* options=NULL):
        cdef char* res
        res = CreateCustomReport_bn (net.value,sel_nodes.value if type(sel_nodes) else NULL, templat, options)
        return res
   
    def ReportJunctionTree_bn (self,NewNet net):
        cdef char* res
        res = CreateCustomReport_bn (net.value, NULL, "[[Net.JunctionTreeTable(TextFormat)]]", NULL)
        return res


    def GetNetAutoUpdate_bn (self,NewNet net):
        cdef int res
        res = GetNetAutoUpdate_bn (net.value)
        return res

    def GetNetElimOrder_bn(self,NewNet net):
        res = NodeList()
        res.value = GetNetElimOrder_bn (net.value)
        return res

    def EquationToTable_bn (self,NewNode node, int num_samples, bool_ns samp_unc, bool_ns add_exist):
        EquationToTable_bn (node.value, num_samples, samp_unc, add_exist)


    def IsBeliefUpdated_bn (self,NewNode node):
        cdef bool_ns res
        res = IsBeliefUpdated_bn (node.value)
        return res

    def GetNodeBeliefs_bn (self,NewNode node):
        res = FloatList()
        res.value = GetNodeBeliefs_bn (node.value)
        return res

    def GetNodeExpectedValue_bn (self,NewNode node,std_dev,x3=None,x4=None):
        cdef double res
        cdef double _std_dev
        cdef double _x3
        cdef double _x4
        _std_dev = <int> std_dev if type(std_dev)==int else 0
        _x3 = <int> x3 if type(x3)==int else 0
        _x4 = <int> x4 if type(x4)==int else 0
        res = GetNodeExpectedValue_bn (node.value, &_std_dev, &_x3, &_x4)
        return (res,_std_dev,_x3,_x4)

    def GetNodeExpectedUtils_bn (self,NewNode node):
        res=FloatList()
        res.value = GetNodeExpectedUtils_bn (node.value)
        return res

    
    cdef __JointProbability_bn_IntList (self,nodelist_bn* nodes,IntList states):
        return JointProbability_bn (nodes,states.value)
        
    def JointProbability_bn (self,NodeList nodes, states):
        cdef double res
        cdef int* _states
        if type(states)==IntList:
            res = self.__JointProbability_bn_IntList (nodes.value,states)
        elif type(states)==list:
            _states = <int *>malloc(len(states) * sizeof(int))
            for i in range(len(states)):
                _states[i] = states[i]
            res = JointProbability_bn (nodes.value,_states)
        else:
            raise ValueError("States should be list of integer| Intlist type found %s" % type(states))
        free(_states)
        return res


    cdef __MostProbableConfig_bn_IntList (self,nodelist_bn* nodes,IntList config, int nth):
        MostProbableConfig_bn (nodes,config.value,nth)

    def MostProbableConfig_bn (self,NodeList nodes, config, int nth):
        cdef int* _config
        if type(config)==IntList:
            res = self.__MostProbableConfig_bn_IntList (nodes.value,config,nth)
        elif type(config)==list:
            _config = <int *>malloc(len(config) * sizeof(int))
            for i in range(len(config)):
                _config[i] = config[i]
            res = MostProbableConfig_bn (nodes.value,_config,nth)
        else:
            raise ValueError("States should be list of integer| Intlist type found %s" % type(config))
        free(_config)
    
    def AddNetListener_bn (self,NewNet net,func, _object, int _filter=-1):
        if type(func)==types.FunctionType:
            _object.__temp__function__handler=func
            return AddNetListener_bn (net.value, callback,<void*> _object , _filter)
        return AddNetListener_bn (net.value, callbackNULL,<void*> _object , _filter)
####################################################################

    def AddLink_bn(self,NewNode parent,NewNode child):
        cdef int res
        res=AddLink_bn(parent.value,child.value)
        return res

    def SetNodeProbs(self,NewNode node_obj, *arg):
        cdef node_bn* node
        cdef node_bn* curNode
        cdef state_bn parent_states[20]
        cdef prob_bn probs[20]
        cdef char* statename
        cdef int state, numstates
        cdef const nodelist_bn* parents 
        cdef int pn, numparents, i
        node = node_obj.value
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

    def GetNodeBelief(self,char* node_name,char* state_name,NewNet net):
        cdef double res
        res = GetNodeBelief (node_name,state_name, net.value)
        return res
    
    def EnterFinding(self,char* node_name, char* state_name, NewNet net):
        EnterFinding(node_name,state_name,net.value)




cdef class UserData:
    cdef void* value 

cdef class Report:
    cdef report_ns* value

cdef class ErrSeverity:
    cdef errseverity_ns value

cdef class ErrorCondition:
    cdef errcond_ns value

cdef class Stream:
    cdef stream_ns* value

cdef class NodeList:
    cdef nodelist_bn* value

cdef class  NewNet:
    cdef net_bn *value
    cpdef run(self,char* name,Netica environ):
        if type(environ)==Netica:
            self.value = NewNet_bn (name, environ.env)
        else:
            self.value = NewNet_bn (name, NULL)

cdef class NewNode:
    cdef node_bn* value
    cpdef run(self,char* name,int num_states,NewNet net):
        self.value=NewNode_bn(name,num_states,net.value)


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
        return x
    
    def __del__(self):
        try:
            free(self.value)
        except:
            pass



cdef class FloatList:
    cdef float* value
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
        return x
    
    def __del__(self):
        try:
            free(self.value)
        except:
            pass

cdef class DoubleList:
    cdef double* value
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
        return x
    
    def __del__(self):
        try:
            free(self.value)
        except:
            pass

cdef class LongList:
    cdef long* value
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
        return x
    
    def __del__(self):
        try:
            free(self.value)
        except:
            pass

cdef int callback (net_bn* net, eventtype_ns what, void* obj, void* info):
    net_py = NewNet()
    net_py.value = net
    return (<object>obj).__temp__function__handler(net_py,what,<object>obj,<object>info)


cdef int callbackNULL (net_bn* net, eventtype_ns what, void* obj, void* info):
    pass
            
        
