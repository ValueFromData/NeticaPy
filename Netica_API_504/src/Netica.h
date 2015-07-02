/* 
 * Netica.h
 *
 * Header file for Netica API, version 5.04 and greater.
 *
 * When used for Netica DLL, DYNAMIC_LINK_ns should be #defined below,
 * but when used for static linking it shouldn't.
 *
 * Copyright (C) 1992-2012 by Norsys Software Corp.
 * This file may be included as part of any software project, provided that
 * project doesn't pass NewNeticaEnviron_ns an unauthorized license string.
 */

#ifndef __NETICA_C_H
#define __NETICA_C_H

/*#define DYNAMIC_LINK_ns 1 /**/  /* Comment out, unless this file is used for Netica DLL */

#ifdef BUILDING_API		//$Release.  And above line.

#define IMPORT(typ)  EXPORT (typ)

#define NO_DEPRECATED_NETICA_FUNCS		// not while building API, since we should keep Norsys codebase current

typedef class Enviro environ_ns;

#include "Error.h"
#include "Bnet.h"
#include "CaseFile.h"	// FIRST_CASE
#include "NeticaP.h"	// MESG_LEN_ns, etc

#define prob_bn      probtype
#define util_bn      detvtype
#define state_bn     int_state
#define level_bn     leveltype
#define value_bn     detvtype
#define report_ns    rept
#define stream_ns    FileSpec
#define randgen_ns   RandGen
#define scripter_ns  ScripterAPI
#define net_bn       Bnet
#define node_bn      Bnode
#define nodelist_bn  BnodesAPI
#define caseset_cs   Caseset
#define learner_bn   LearnControl
#define tester_bn    NetTest
#define sensv_bn     Sensv
#define dbmgr_cs     DBmgr
#define errcond_ns   ErrCondEN
#define errseverity_ns ErrSeverityEN
#define checking_ns  APICheckingLevelEN
#define nodekind_bn  NodeKindEN
#define nodetype_bn  VarDiscreteEN
#define eventtype_ns EventTypeEN
#define setting_bn   icase3

#ifdef __cplusplus
extern "C" {
#endif

#else  /* !BUILDING_API */


#ifdef __cplusplus
extern "C" {
#endif

#ifdef DYNAMIC_LINK_ns
#define IMPORT(typ) __declspec (dllimport) typ __stdcall
#else
#define IMPORT(typ) typ
#endif


#define  UNDEF_DBL    GetUndefDbl_ns()
#define  INFINITY_ns  GetInfinityDbl_ns()


typedef enum {NO_CHECK=1, QUICK_CHECK, REGULAR_CHECK, COMPLETE_CHECK, QUERY_CHECK=-1} checking_ns;

typedef enum {NOTHING_ERR=1, REPORT_ERR, NOTICE_ERR, WARNING_ERR, ERROR_ERR, XXX_ERR} errseverity_ns;

typedef enum {OUT_OF_MEMORY_CND=0x08, USER_ABORTED_CND=0x20, FROM_WRAPPER_CND=0x40, FROM_DEVELOPER_CND=0x80, INCONS_FINDING_CND=0x200} errcond_ns;

typedef enum {CREATE_EVENT=0x01, DUPLICATE_EVENT=0x02, REMOVE_EVENT=0x04} eventtype_ns;

typedef enum {CONTINUOUS_TYPE=1, DISCRETE_TYPE, TEXT_TYPE} nodetype_bn;

typedef enum {NATURE_NODE=1, CONSTANT_NODE, DECISION_NODE, UTILITY_NODE, DISCONNECTED_NODE, ADVERSARY_NODE} nodekind_bn;

enum {REAL_VALUE = -25, STATE_VALUE = -20, GAUSSIAN_VALUE = -15, INTERVAL_VALUE = -10, STATE_NOT_VALUE = -7, LIKELIHOOD_VALUE, NO_VALUE = -3};

enum {EVERY_STATE = -5, IMPOSS_STATE, UNDEF_STATE};    /* special values for state_bn */

enum {FIRST_CASE = -15, NEXT_CASE, NO_MORE_CASES};     /* special values for caseposn_bn */

enum {ENTROPY_SENSV = 0x02, REAL_SENSV = 0x04, VARIANCE_SENSV = 0x100, VARIANCE_OF_REAL_SENSV = 0x104};   /* for NewSensvToFinding_bn */


#ifndef __NETICA_CPP_H

typedef struct environ_ins   environ_ns;
typedef struct report_ins    report_ns;
typedef struct stream_ins    stream_ns;
typedef struct randgen_ins   randgen_ns;
typedef struct scripter_ins  scripter_ns;
typedef struct net_ibn       net_bn;
typedef struct node_ibn      node_bn;
typedef struct nodelist_ibn  nodelist_bn;
typedef struct caseset_ics   caseset_cs;
typedef struct learner_ibn   learner_bn;
typedef struct test_ibn      tester_bn;
typedef struct sensv_ibn     sensv_bn;
typedef struct setting_ibn   setting_bn;
typedef struct dbmgr_ics     dbmgr_cs;

#endif /* __NETICA_CPP_H */

IMPORT (double) GetUndefDbl_ns();               /* use UNDEF_DBL   in your software */
IMPORT (double) GetInfinityDbl_ns();            /* use INFINITY_ns in your software */


typedef int     state_bn;
typedef float   prob_bn;
typedef float   util_bn;
typedef double  level_bn;

#endif  /* !BUILDING_API */

typedef int     color_ns;			/* most significant byte(s) is 0, and last 3 bytes are red, green, blue */
typedef long    caseposn_bn;
typedef unsigned char bool_ns;

typedef enum {DEFAULT_SAMPLING, JOIN_TREE_SAMPLING, FORWARD_SAMPLING} sampling_bn;


#ifndef FALSE
enum {FALSE=0, TRUE};
#endif

#ifndef NULL
#define NULL 0
#endif


#define  MESG_LEN_ns  600
#define  NAME_MAX_ns   30

typedef enum {COUNTING_LEARNING=1, EM_LEARNING=3, GRADIENT_DESCENT_LEARNING} learn_method_bn;

enum {NEGATIVE_FINDING = -7, LIKELIHOOD_FINDING, NO_FINDING = -3};   /* for GetNodeFinding_bn */

enum {NO_VISUAL_INFO=0, NO_WINDOW=0x10, MINIMIZED_WINDOW=0x30, REGULAR_WINDOW=0x70};   /* for ReadNet_bn */

enum {BELIEF_UPDATE = 0x100};	/* for SetNetAutoUpdate_bn */

enum {HALT_CALLBACK_RESULT = -1003};	/* return value for callback of AddNetListener_bn */

enum {ALL_THREADS = 0x20};		/* for ClearErrors_ns */

enum {LAST_ENTRY = -10};

enum {QUERY_ns = -1};


IMPORT (environ_ns*) NewNeticaEnviron_ns (const char* license, environ_ns* env, const char* locn);
IMPORT (int) InitNetica2_bn (environ_ns* env, char* mesg);
IMPORT (int) CloseNetica_bn (environ_ns* env, char* mesg);
IMPORT (int) GetNeticaVersion_bn (const environ_ns* env, const char** version);
IMPORT (checking_ns) ArgumentChecking_ns (checking_ns setting, environ_ns* env);
IMPORT (void) SetPassword_ns (environ_ns* env, const char* password, const char* options);
IMPORT (const char*) SetLanguage_ns (environ_ns* env, const char* language);
IMPORT (double) LimitMemoryUsage_ns (double max_mem, environ_ns* env);
IMPORT (void) SetEnvironUserData_ns (environ_ns* env, int kind, void* data);
IMPORT (void*) GetEnvironUserData_ns (environ_ns* env, int kind);

IMPORT (report_ns*) GetError_ns (environ_ns* env, errseverity_ns severity, const report_ns* after);
IMPORT (int) ErrorNumber_ns (const report_ns* error);
IMPORT (const char*) ErrorMessage_ns (const report_ns* error);
IMPORT (errseverity_ns) ErrorSeverity_ns (const report_ns* error);
IMPORT (bool_ns) ErrorCategory_ns (errcond_ns cond, const report_ns* error);
IMPORT (void) ClearError_ns (report_ns* error);
IMPORT (void) ClearErrors_ns (environ_ns* env, errseverity_ns severity);
IMPORT (report_ns*) NewError_ns (environ_ns* env, int number, errseverity_ns severity, const char* mesg);
IMPORT (int) TestFaultRecovery_ns (environ_ns* env, int test_num);

IMPORT (int) UserAllowed_ns (environ_ns* env, int setting);
IMPORT (void) GetAppWindowPosition_ns (environ_ns* env, int* left, int* top, int* width, int* height, int* status);
IMPORT (void) SetAppWindowPosition_ns (environ_ns* env, int left, int top, int width, int height, int status);
IMPORT (void) PrintToMessagesWindow_ns (environ_ns* env, char* mesg);

IMPORT (stream_ns*) NewFileStream_ns (const char* filename, environ_ns* env, const char* access);
IMPORT (stream_ns*) NewMemoryStream_ns (const char* name, environ_ns* env, const char* access);
IMPORT (void) DeleteStream_ns (stream_ns* file);
IMPORT (void) SetStreamPassword_ns (stream_ns* stream, const char* password);
IMPORT (void) SetStreamContents_ns (stream_ns* stream, const char* buffer, long length, bool_ns copy);
IMPORT (const char*) GetStreamContents_ns (stream_ns* stream, long* length);
IMPORT (void) WriteNet_bn (const net_bn* net, stream_ns* file);
IMPORT (net_bn*) ReadNet_bn (stream_ns* file, int options);
IMPORT (caseposn_bn) WriteNetFindings_bn (const nodelist_bn* nodes, stream_ns* file, long ID_num, double freq);
IMPORT (void) ReadNetFindings2_bn (caseposn_bn* case_posn, stream_ns* file, bool_ns add, const nodelist_bn* nodes, long* ID_num, double* freq);
IMPORT (int) SetCaseFileDelimChar_ns (int newchar, environ_ns* env);
IMPORT (int) SetMissingDataChar_ns (int newchar, environ_ns* env);

IMPORT (net_bn*) NewNet_bn (const char* name, environ_ns* env);
IMPORT (net_bn*) CopyNet_bn (const net_bn* net, const char* new_name, environ_ns* new_env, const char* options);
IMPORT (void) DeleteNet_bn (net_bn* net);
IMPORT (net_bn*) GetNthNet_bn (int nth, environ_ns* env);
IMPORT (node_bn*) NewNode_bn (const char* name, int num_states, net_bn* net);
IMPORT (nodelist_bn*) CopyNodes_bn (const nodelist_bn* nodes, net_bn* new_net, const char* options);
IMPORT (void) DeleteNode_bn (node_bn* node);

IMPORT (void) SetNetName_bn (net_bn* net, const char* name);
IMPORT (void) SetNetTitle_bn (net_bn* net, const char* title);
IMPORT (void) SetNetComment_bn (net_bn* net, const char* comment);
IMPORT (void) SetNetElimOrder_bn (net_bn* net, const nodelist_bn* elim_order);
IMPORT (int) SetNetAutoUpdate_bn (net_bn* net, int auto_update);
IMPORT (void) SetNetUserField_bn (net_bn* net, const char* name, const void* data, int length, int kind);
IMPORT (void) SetNetUserData_bn (net_bn* net, int kind, void* data);
IMPORT (void) AddNetListener_bn (net_bn* net, int callback (const net_bn* net, eventtype_ns what, void* object, void* info), void* object, int filter);

IMPORT (void) SetNodeName_bn (node_bn* node, const char* name);
IMPORT (void) SetNodeTitle_bn (node_bn* node, const char* title);
IMPORT (void) SetNodeComment_bn (node_bn* node, const char* comment);
IMPORT (void) SetNodeLevels_bn (node_bn* node, int num_states, const level_bn* levels);
IMPORT (void) SetNodeKind_bn (node_bn* node, nodekind_bn kind);
IMPORT (void) SetNodeStateName_bn (node_bn* node, state_bn state, const char* state_name);
IMPORT (void) SetNodeStateNames_bn (node_bn* node, const char* state_names);
IMPORT (void) SetNodeStateTitle_bn (node_bn* node, state_bn state, const char* state_title);
IMPORT (void) SetNodeStateComment_bn (node_bn* node, state_bn state, const char* state_comment);
IMPORT (void) SetNodeInputName_bn (node_bn* node, int link_index, const char* link_name);
IMPORT (void) SetNodeEquation_bn (node_bn* node, const char* eqn);
IMPORT (void) SetNodeFuncState_bn (node_bn* node, const state_bn* parent_states, state_bn st);
IMPORT (void) SetNodeFuncReal_bn (node_bn* node, const state_bn* parent_states, double val);
IMPORT (void) SetNodeProbs_bn (node_bn* node, const state_bn* parent_states, const prob_bn* probs);
IMPORT (void) SetNodeExperience_bn (node_bn* node, const state_bn* parent_states, double experience);
IMPORT (void) DeleteNodeTables_bn (node_bn* node);
IMPORT (void) SetNodeUserField_bn (node_bn* node, const char* name, const void* data, int length, int kind);
IMPORT (void) SetNodeUserData_bn (node_bn* node, int kind, void* data);
IMPORT (void) AddNodeListener_bn (node_bn* node, int callback (const node_bn* node, eventtype_ns what, void* object, void* info), void* object, int filter);
IMPORT (void) SetNodeVisPosition_bn (node_bn* node, void* vis, double x, double y);
IMPORT (void) SetNodeVisStyle_bn (node_bn* node, void* vis, const char* style);

IMPORT (const char*) GetNetName_bn (const net_bn* net);
IMPORT (const char*) GetNetTitle_bn (const net_bn* net);
IMPORT (const char*) GetNetComment_bn (const net_bn* net);
IMPORT (const nodelist_bn*) GetNetNodes2_bn (const net_bn* net, const char options[]);
IMPORT (node_bn*) GetNodeNamed_bn (const char* name, const net_bn* net);
IMPORT (const char*) GetNetFileName_bn (const net_bn* net);
IMPORT (int) GetNetAutoUpdate_bn (const net_bn* net);
IMPORT (const nodelist_bn*) GetNetElimOrder_bn (const net_bn* net);
IMPORT (const char*) GetNetUserField_bn (const net_bn* net, const char* name, int* length, int kind);
IMPORT (void) GetNetNthUserField_bn (const net_bn* net, int index, const char** name, const char** value, int* length, int kind);
IMPORT (void*) GetNetUserData_bn (const net_bn* net, int kind);

IMPORT (net_bn*) GetNodeNet_bn (const node_bn* node);
IMPORT (const char*) GetNodeName_bn (const node_bn* node);
IMPORT (const char*) GetNodeTitle_bn (const node_bn* node);
IMPORT (const char*) GetNodeComment_bn (const node_bn* node);
IMPORT (nodetype_bn) GetNodeType_bn (const node_bn* node);
IMPORT (nodekind_bn) GetNodeKind_bn (const node_bn* node);
IMPORT (int) GetNodeNumberStates_bn (const node_bn* node);
IMPORT (const level_bn*) GetNodeLevels_bn (const node_bn* node);
IMPORT (const char*) GetNodeStateName_bn (const node_bn* node, state_bn state);
IMPORT (const char*) GetNodeStateTitle_bn (const node_bn* node, state_bn state);
IMPORT (const char*) GetNodeStateComment_bn (const node_bn* node, state_bn state);
IMPORT (state_bn) GetStateNamed_bn (const char* name, const node_bn* node);
IMPORT (const nodelist_bn*) GetNodeParents_bn (const node_bn* node);
IMPORT (const nodelist_bn*) GetNodeChildren_bn (const node_bn* node);
IMPORT (const char*) GetNodeInputName_bn (const node_bn* node, int link_index);
IMPORT (int) GetInputNamed_bn (const char* name, const node_bn* node);
IMPORT (const char*) GetNodeEquation_bn (const node_bn* node);
IMPORT (state_bn) GetNodeFuncState_bn (const node_bn* node, const state_bn* parent_states);
IMPORT (double) GetNodeFuncReal_bn (const node_bn* node, const state_bn* parent_states);
IMPORT (const prob_bn*) GetNodeProbs_bn (const node_bn* node, const state_bn* parent_states);
IMPORT (double) GetNodeExperience_bn (const node_bn* node, const state_bn* parent_states);
IMPORT (bool_ns) HasNodeTable_bn (const node_bn* node, bool_ns* complete);
IMPORT (bool_ns) IsNodeDeterministic_bn (const node_bn* node);
IMPORT (const char*) GetNodeUserField_bn (const node_bn* node, const char* name, int* length, int kind);
IMPORT (void) GetNodeNthUserField_bn (const node_bn* node, int index, const char** name, const char** value, int* length, int kind);
IMPORT (void*) GetNodeUserData_bn (const node_bn* node, int kind);
IMPORT (void) GetNodeVisPosition_bn (const node_bn* node, void* vis, double* x, double* y);
IMPORT (const char*) GetNodeVisStyle_bn (const node_bn* node, void* vis);

IMPORT (int) AddLink_bn (node_bn* parent, node_bn* child);
IMPORT (void) DeleteLink_bn (int link_index, node_bn* child);
IMPORT (void) SwitchNodeParent_bn (int link_index, node_bn* node, node_bn* new_parent);
IMPORT (bool_ns) IsNodeRelated_bn (const node_bn* related_node, const char* relation, const node_bn* node);
IMPORT (void) GetRelatedNodes_bn (nodelist_bn* related_nodes, const char* relation, const node_bn* node);
IMPORT (void) GetRelatedNodesMult_bn (nodelist_bn* related_nodes, const char* relation, const nodelist_bn* nodes);

IMPORT (nodelist_bn*) NewNodeList2_bn (int length, const net_bn* net);
IMPORT (void) DeleteNodeList_bn (nodelist_bn* nodes);
IMPORT (void) ClearNodeList_bn (nodelist_bn* nodes);
IMPORT (int) LengthNodeList_bn (const nodelist_bn* nodes);
IMPORT (void) AddNodeToList_bn (node_bn* node, nodelist_bn* nodes, int index);
IMPORT (node_bn*) RemoveNthNode_bn (nodelist_bn* nodes, int index);
IMPORT (node_bn*) NthNode_bn (const nodelist_bn* nodes, int index);
IMPORT (void) SetNthNode_bn (nodelist_bn* nodes, int index, node_bn* node);
IMPORT (int) IndexOfNodeInList_bn (const node_bn* node, const nodelist_bn* nodes, int start_index);
IMPORT (nodelist_bn*) DupNodeList_bn (const nodelist_bn* nodes);

IMPORT (void) MapStateList_bn (const state_bn* src_states,  const nodelist_bn* src_nodes,
                               state_bn* dest_states, const nodelist_bn* dest_nodes);

IMPORT (void) ReviseCPTsByFindings_bn (const nodelist_bn* nodes, int updating, double degree);
IMPORT (void) ReviseCPTsByCaseFile_bn (stream_ns* file, const nodelist_bn* nodes, int updating, double degree);
IMPORT (void) FadeCPTable_bn (node_bn* node, double degree);

IMPORT (void) AddNodeStates_bn (node_bn* node, state_bn first_state, const char* state_names, int num_states, double cpt_fill);
IMPORT (void) RemoveNodeState_bn (node_bn* node, state_bn state);
IMPORT (void) ReorderNodeStates_bn (node_bn* node, const state_bn* new_order);
IMPORT (void) EquationToTable_bn (node_bn* node, int num_samples, bool_ns samp_unc, bool_ns add_exist);
IMPORT (void) ReverseLink_bn (node_bn* parent, node_bn* child);
IMPORT (void) AbsorbNodes_bn (nodelist_bn* nodes);

IMPORT (void) EnterFinding_bn (node_bn* node, state_bn state);
IMPORT (void) EnterFindingNot_bn (node_bn* node, state_bn state);
IMPORT (void) EnterNodeValue_bn (node_bn* node, double value);
IMPORT (void) EnterNodeLikelihood_bn (node_bn* node, const prob_bn* likelihood);
IMPORT (void) EnterNodeCalibration_bn (node_bn* node, const prob_bn* calibration);
IMPORT (void) EnterIntervalFinding_bn (node_bn* node, double low, double high);
IMPORT (void) EnterGaussianFinding_bn (node_bn* node, double mean, double std_dev);
IMPORT (state_bn) GetNodeFinding_bn (const node_bn* node);
IMPORT (double) GetNodeValueEntered_bn (const node_bn* node);
IMPORT (const prob_bn*) GetNodeLikelihood_bn (const node_bn* node);
IMPORT (void) RetractNodeFindings_bn (node_bn* node);
IMPORT (void) RetractNetFindings_bn (net_bn* net);

IMPORT (state_bn) CalcNodeState_bn (node_bn* node);
IMPORT (double) CalcNodeValue_bn (node_bn* node);

IMPORT (void) CompileNet_bn (net_bn* net);
IMPORT (void) UncompileNet_bn (net_bn* net);
IMPORT (double) SizeCompiledNet_bn (net_bn* net, int method);
IMPORT (bool_ns) IsBeliefUpdated_bn (const node_bn* node);
IMPORT (const prob_bn*) GetNodeBeliefs_bn (node_bn* node);
IMPORT (double) GetNodeExpectedValue_bn (node_bn* node, double* std_dev, double* x3, double* x4);
IMPORT (const util_bn*) GetNodeExpectedUtils_bn (node_bn* node);
IMPORT (double) FindingsProbability_bn (net_bn* net);
IMPORT (util_bn) GetNetExpectedUtility_bn (net_bn* net);
IMPORT (double) JointProbability_bn (const nodelist_bn* nodes, const state_bn* states);
IMPORT (void) MostProbableConfig_bn (const nodelist_bn* nodes, state_bn* config, int nth);

IMPORT (sensv_bn*) NewSensvToFinding_bn (const node_bn* t_node, const nodelist_bn* v_nodes, int what_calc);
IMPORT (void) DeleteSensvToFinding_bn (sensv_bn* s);
IMPORT (double) GetMutualInfo_bn (sensv_bn* s, const node_bn* v_node);
IMPORT (double) GetVarianceOfReal_bn (sensv_bn* s, const node_bn* v_node);

IMPORT (int) GenerateRandomCase_bn (const nodelist_bn* nodes, sampling_bn method, double num, randgen_ns* rand);

IMPORT (void) AddNodeToNodeset_bn (node_bn* node, const char* nodeset);
IMPORT (void) RemoveNodeFromNodeset_bn (node_bn* node, const char* nodeset);
IMPORT (bool_ns) IsNodeInNodeset_bn (const node_bn* node, const char* nodeset);
IMPORT (const char*) GetAllNodesets_bn (const net_bn* net, bool_ns include_system, void* vis);
IMPORT (color_ns) SetNodesetColor_bn (const char* nodeset, color_ns color, net_bn* net, void* vis);
IMPORT (void) ReorderNodesets_bn (net_bn* net, const char* nodeset_order, void* vis);

IMPORT (caseset_cs*) NewCaseset_cs (const char* name, environ_ns* env);
IMPORT (void) DeleteCaseset_cs (caseset_cs* cases);
IMPORT (void) AddFileToCaseset_cs (caseset_cs* cases, const stream_ns* file, double degree, const char* options);
IMPORT (void) WriteCaseset_cs (const caseset_cs* cases, stream_ns* file, const char* options);

IMPORT (dbmgr_cs*) NewDBManager_cs (const char* connect_str, const char* options, environ_ns* env);
IMPORT (void) DeleteDBManager_cs (dbmgr_cs* dbmgr);
IMPORT (void) ExecuteDBSql_cs (dbmgr_cs* dbmgr, const char* sql_cmnd, const char* options);
IMPORT (void) InsertFindingsIntoDB_bn (dbmgr_cs* dbmgr, const nodelist_bn* nodes, const char* column_names, const char* tables, const char* options);
IMPORT (void) AddDBCasesToCaseset_cs (caseset_cs* cases, dbmgr_cs* dbmgr, double degree, const nodelist_bn* nodes, const char* column_names, const char* tables, const char* condition, const char* options);
IMPORT (void) AddNodesFromDB_bn (dbmgr_cs* dbmgr, net_bn* net, const char* column_names, const char* tables, const char* condition, const char* options);

IMPORT (learner_bn*) NewLearner_bn (learn_method_bn method, const char* options, environ_ns* env);
IMPORT (void) DeleteLearner_bn (learner_bn* algo);
IMPORT (int) SetLearnerMaxIters_bn (learner_bn* algo, int max_iters);
IMPORT (double) SetLearnerMaxTol_bn (learner_bn* algo, double log_likeli_tol);
IMPORT (void) LearnCPTs_bn (learner_bn* algo, const nodelist_bn* nodes, const caseset_cs* cases, double degree);

IMPORT (tester_bn*) NewNetTester_bn (const nodelist_bn* test_nodes, const nodelist_bn* unobsv_nodes, int tests);
IMPORT (void) DeleteNetTester_bn (tester_bn* test);
IMPORT (void) TestWithCaseset_bn (tester_bn* test, const caseset_cs* cases);
IMPORT (double) GetTestErrorRate_bn (const tester_bn* test, const node_bn* node);
IMPORT (double) GetTestLogLoss_bn (const tester_bn* test, const node_bn* node);
IMPORT (double) GetTestQuadraticLoss_bn (const tester_bn* test, const node_bn* node);
IMPORT (double) GetTestConfusion_bn (const tester_bn* test, const node_bn* node, state_bn predicted, state_bn actual);

IMPORT (void) SetNetNumUndos_bn (net_bn* net, int count_limit, double memory_limit, const char* options);
IMPORT (int) UndoNetLastOper_bn (net_bn* net, double to_when);
IMPORT (int) RedoNetOper_bn (net_bn* net, double to_when);

IMPORT (int) GetNodeLabel_bn (const node_bn* node, unsigned short* label, int max_chars, const char* options);
IMPORT (int) GetNodeStateLabel_bn (const node_bn* node, state_bn state, unsigned short* label, int max_chars, const char* options);
IMPORT (const char*) CreateCustomReport_bn (net_bn* net, const nodelist_bn* sel_nodes, const char* templat, const char* options);

IMPORT (const char*) ControlConcurrency_ns (environ_ns* env, const char* command, const char* value);
IMPORT (const char*) ControlNetCaching_bn (net_bn* net, const char* command, const char* value, const nodelist_bn* nodes);

IMPORT (net_bn*) ExpandNet_bn (net_bn* net, int dimn, double result_time, double burn_time, const char* options);
IMPORT (void) SetNodeInputDelay_bn (node_bn* node, int link_index, int dimension, const char* delay);
IMPORT (void) SetNodePersistance_bn (node_bn* node, int dimension, const char* persistance);
IMPORT (node_bn*) GetNodeAtTime_bn (net_bn* net, const char* name, double* time);

IMPORT (randgen_ns*) NewRandomGenerator_ns (const char* seed, environ_ns* env, const char* options);
IMPORT (void) DeleteRandomGen_ns (randgen_ns* rand);
IMPORT (const char*) GetRandomGenState_ns (randgen_ns* rand, const char* options);
IMPORT (double) GenerateRandomNumbers_ns (randgen_ns* rand, double* results, int num, const char* options);
IMPORT (void) SetNetRandomGen_bn (net_bn* net, randgen_ns* rand, bool_ns is_private);

IMPORT (void) EnterAction_bn (node_bn* node, state_bn state);
IMPORT (void) EnterActionValue_bn (node_bn* node, double value);
IMPORT (void) EnterActionRandomized_bn (node_bn* node, const prob_bn* probs);

/*--------------*/


IMPORT (void) CleanupThreadEnding_ns (environ_ns* env);

IMPORT (scripter_ns*) NewScripter_ns (environ_ns* env, const char* file_name, const char* language, const char* options, const char* script);
IMPORT (void) DeleteScripter_ns (scripter_ns* scr);
IMPORT (const char*) ExecuteScript_ns (scripter_ns* scr, const char* options);
IMPORT (void) StartScriptRecorder_ns (scripter_ns* scr, const char* file_name, const char* language, const char* options);
IMPORT (const char*) StopScriptRecorder_ns (scripter_ns* scr, const char* file_name, const char* options);
IMPORT (const char*) GetScriptVar_ns (scripter_ns* scr, const char* name, const char* type);
IMPORT (void) ClearScriptVars_ns (scripter_ns* scr, const char* options);

IMPORT (setting_bn*) NewSetting_bn (const nodelist_bn* nodes, bool_ns load);
IMPORT (void) DeleteSetting_bn (setting_bn* cas);
IMPORT (void) SetSettingState_bn (setting_bn* cas, const node_bn* node, state_bn state);
IMPORT (state_bn) GetSettingState_bn (const setting_bn* cas, const node_bn* node);
IMPORT (void) ZeroSetting_bn (setting_bn* cas);
IMPORT (bool_ns) NextSetting_bn (setting_bn* cas);
IMPORT (void) MostProbableSetting_bn (net_bn* net, setting_bn* cas, int nth);

IMPORT (double) NthProb_bn (const prob_bn* probs, state_bn state);
IMPORT (double) NthLevel_bn (const level_bn* levels, state_bn state);
IMPORT (int) GetChars_ns (const char* str, int index, unsigned short* dest, int num);
IMPORT (int) NthChar_ns (const char* str, int index);
IMPORT (void) SetNthState_bn (state_bn* states, int index, state_bn state);

IMPORT (void) OptimizeDecisions_bn (const nodelist_bn* nodes);



/* Shorthand Notation */
#define NodeNamed_bn   GetNodeNamed_bn
#define StateNamed_bn  GetStateNamed_bn
#define InputNamed_bn  GetInputNamed_bn


/* These definitions are just for compatibility with old versions: */

#ifndef NO_DEPRECATED_NETICA_FUNCS

enum {WILDCARD_STATE = EVERY_STATE};
#define ASSUME_NODE       CONSTANT_NODE
#define SetLinkName_bn    SetNodeInputName_bn
#define GetLinkName_bn    GetNodeInputName_bn
#define LinkNamed_bn      GetInputNamed_bn
#define ReOrderStates_bn  MapStateList_bn
#define GetNodeValue_bn   GetNodeValueEntered_bn
#define SetNodeCenter_bn  SetNodeVisPosition_bn
#define FreeNet_bn        DeleteNet_bn
#define FreeNodeList_bn   DeleteNodeList_bn
#define ReportError_ns    NewError_ns
#define ErrorDanger_ns    ErrorSeverity_ns
#define errdanger_ns      errseverity_ns
#define GetJointProb_bn   JointProbability_bn
#define FadeProbs_bn      FadeCPTable_bn
#define RetractAllFindings_bn RetractNetFindings_bn
#define DeleteNodeRelation_bn DeleteNodeTables_bn
#define CaseProbability_bn    FindingsProbability_bn
#define GetNodeCalcState_bn   CalcNodeState_bn
#define GetNodeCalcValue_bn   CalcNodeValue_bn
#define CaseRevisesProbs_bn		ReviseCPTsByFindings_bn
#define CaseFileRevisesProbs_bn	ReviseCPTsByCaseFile_bn
extern double BaseExperience_bn;
#define NewStreamFile_ns  NewFileStream_ns
#define MaxMemoryUsage_ns LimitMemoryUsage_ns
#define ReadCase_bn		ReadNetFindings_bn
#define WriteCase_bn	WriteNetFindings_bn
#define RandomCase_bn(nodes, method, num)	GenerateRandomCase_bn (nodes, method, num, NULL)
#define FileNamed_ns(filename, env)  NewFileStream_ns (filename, env, 0)
#define GetNodeLevel_bn(node, state)  (GetNodeLevels_bn (node) ? GetNodeLevels_bn (node) [state] : UNDEF_DBL)
#define HasRelation_bn(node)   HasNodeTable_bn (node, 0)
#define GetNodeDiscrete_bn(node)  ((GetNodeType_bn (node) == DISCRETE_TYPE) ? TRUE : FALSE)
/*
void SetNodeFuncValue_bn (node_bn* node, const state_bn* parent_states, double func_value){		// put this code in your file for software pre v2.06
	if (GetNodeType_bn (node) == DISCRETE_TYPE)
	     SetNodeFuncState_bn (node, parent_states, (int)func_value);
	else SetNodeFuncReal_bn (node, parent_states, func_value);
	}
*/
#define GetNodeFuncValue_bn(node, parent_states)  ((GetNodeType_bn (node) == DISCRETE_TYPE) ? GetNodeFuncState_bn (node, parent_states) : GetNodeFuncReal_bn (node, parent_states))
#define NewNeticaEnviron_bn(license)  NewNeticaEnviron_ns (license, 0, 0)
#define InitNetica_bn(envp, mesg)   InitNetica2_bn (*(envp), mesg)
/*
void GetNodeCenter_bn (const node_bn* node, void* vis, int* x, int* y){		// put this code in your file for software pre v2.07
	double xd, yd;
	GetNodeVisPosition_bn (node, vis, &xd, &yd);
	if (x) *x = (int)xd;
	if (y) *y = (int)yd;
	}
*/
#define MutualInfo_bn      GetMutualInfo_bn
#define VarianceOfReal_bn  GetVarianceOfReal_bn
#define DuplicateNodes_bn(nodes, new_net)  CopyNodes_bn (nodes, new_net, NULL)
IMPORT (nodelist_bn*) NewNodeList_bn (int length, environ_ns* env);
#define ReadNetFindings_bn(case_posn, fs, nodes, ID_num, freq)  \
	ReadNetFindings2_bn (case_posn, fs, FALSE, nodes, ID_num, freq)
#define ReportJunctionTree_bn(net)  \
	CreateCustomReport_bn (net, NULL, "[[Net.JunctionTreeTable(TextFormat)]]", NULL)
#define GetNetNodes_bn(net)  \
	GetNetNodes2_bn (net, "incl_docn")

#endif  /* !NO_DEPRECATED_NETICA_FUNCS */


#ifdef __cplusplus
}
#endif

#endif  /* __NETICA_C_H */
