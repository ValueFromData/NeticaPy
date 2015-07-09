/* 
 * NeticaEx.h
 *
 * Header for NeticaEx.c, 
 * which contains extra source code for Netica API, version 4.16.
 *
 * Copyright (C) 1992-2010 by Norsys Software Corp.  All rights reserved.
 *
 */

#ifndef __NeticaEx_h
#define __NeticaEx_h

#include "Netica.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CHKERR  {if (GetError_ns (env, ERROR_ERR, NULL))  goto error;}

extern environ_ns* env;

int main_ex (void);

node_bn* GetNode (char* node_name, net_bn* net);
void EnterFinding (char* node_name, char* state_name, net_bn* net);
void SetNodeFinding (node_bn* node, state_bn state);
void SetNodeValue (node_bn* node, double value);
double GetNodeBelief (char* node_name, char* state_name, net_bn* net);
void SetNodeProbs (node_bn* node, ...);
void SetNodeFuncState (node_bn* node, state_bn value, ...);
void SetNodeFuncReal (node_bn* node, double value, ...);
void SetNodeExper (node_bn* node, double value, ...);
void MakeProbsUniform (node_bn* node);
void GetNodeAllProbs (node_bn* node, prob_bn* probs, int num_entries);
bool_ns NextStates (state_bn* states, const nodelist_bn* nodes);
void PrintNodeList (nodelist_bn* nodes);
void RetractFindingsOfNodes (nodelist_bn* nodes, bool_ns do_consts_too);
int FindNodeNamed (const char* name, const nodelist_bn* nodes);
int IndexOfNodeInList (const node_bn* node, const nodelist_bn* nodes);
void RemoveOneNodeFromList (node_bn* node, nodelist_bn* nodes);
void RemoveNodeFromListIfThere (node_bn* node, nodelist_bn* nodes);
void RemoveNthNodeFast (int index, nodelist_bn* nodes);
void DeleteLink (node_bn* parent, node_bn* child);
void DeleteLinks (node_bn* parent, node_bn* child);
void DeleteLinksEntering (node_bn* child);
void SwitchNodeParent (node_bn* parent, node_bn* child, node_bn* new_parent);
void DeleteNodes (nodelist_bn* nodes);
bool_ns IsLinkDisconnected (int link_index, const node_bn* node);

nodelist_bn* TransferNodes (nodelist_bn* nodes, net_bn* new_net);
node_bn* DupNode (node_bn* node);
node_bn* DuplicateNode (node_bn* node, net_bn* new_net);
net_bn* DuplicateNet (net_bn* net, const char* newname);
net_bn* NetNamed (const char* name);
node_bn* FormCliqueWith (const nodelist_bn* nodes);
void AbsorbNode (node_bn* node);
void DeleteNetTables (net_bn* net);
void FadeCPTables (const nodelist_bn* nodes, double degree);
void PrintNeticaVersion (void);
void PrintErrors (void);
report_ns* NewError (environ_ns* env, int number, errseverity_ns severity, const char* mesg, ...);
void ClearErrors (environ_ns* env, errseverity_ns severity);

void SetNetUserString (net_bn* net, const char* fieldname, const char* str);
const char* GetNetUserString (net_bn* net, const char* fieldname);
void SetNetUserInt (net_bn* net, const char* fieldname, int num);
long GetNetUserInt (net_bn* net, const char* fieldname);
void SetNetUserNumber (net_bn* net, const char* fieldname, double num);
double GetNetUserNumber (net_bn* net, const char* fieldname);
void SetNodeUserString (node_bn* node, const char* fieldname, const char* str);
const char* GetNodeUserString (node_bn* node, const char* fieldname);
void SetNodeUserInt (node_bn* node, const char* fieldname, int num);
long GetNodeUserInt (node_bn* node, const char* fieldname);
void SetNodeUserNumber (node_bn* node, const char* fieldname, double num);
double GetNodeUserNumber (node_bn* node, const char* fieldname);
void PrintConfusionMatrix (tester_bn* tester, node_bn* node);

// Not mentioned in Reference Manual

void CopyNodeRelation_bn (node_bn* dest, const node_bn* src, const nodelist_bn* parent_order_dest);
int MultiDimnIndex (const state_bn states[], const nodelist_bn* nodes);
double SizeCartesianProduct (const nodelist_bn* nodes);
node_bn* MapNode (const node_bn* node, const net_bn* dest_net);
nodelist_bn* MapNodeList (const nodelist_bn* nodes, const net_bn* dest_net);
nodelist_bn* MapNodeList1 (const nodelist_bn* oldorder, const nodelist_bn* oldnodes, const nodelist_bn* newnodes);
nodelist_bn* DisconnectNodeGroup (nodelist_bn* nodes);
char* NodeListToString (const nodelist_bn* nodes);
long CountCasesInFile (stream_ns* casefile);
int RemoveUnusedStates (node_bn* node);
int* MakeInverseOrdering (const int order[], int num, int invorder[]);

// Obsolete

void SetNodeStateNames (node_bn* node, ...);
void SetNodeFuncValue (node_bn* node, double value, ...);
double ExpectedValue (node_bn* node, double* stddev);
int PositionInNodeList (const node_bn* node, const nodelist_bn* nodes);
void RemoveNodeFromList (node_bn* node, nodelist_bn* nodes);
void SetNodeAllProbs (node_bn* node, const prob_bn* probs);

#ifdef __cplusplus
}
#endif


#endif  /* __NeticaEx_h */
