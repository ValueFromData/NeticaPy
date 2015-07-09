/* 
 * NeticaEx.c
 *
 * Extra and Example (external) Source Code for Netica API, version 5.02 or higher.
 *
 * Copyright (C) 1992-2011 by Norsys Software Corp.
 * The software in this file may be copied, modified, and/or included in 
 * derivative works without charge or obligation.
 * Norsys makes no warranty that this software is without defects.
 *
 */

#include <stdio.h>
#include <assert.h>
#include <limits.h>

#include "Netica.h"
#include "NeticaEx.h"

environ_ns* env = NULL;				/* currently there is always only one environ_ns, and this is it (or will be, when it is set) */

#pragma warning (disable: 4996)		/* using the regular version of Standard Library, instead of Microsoft's secure one, because we need to be portable */


/*_____________________________________________________________________________ main_ex
All programs using Netica API should contain code equivalent to this.
One possibility is to copy this code into your own routine named "main".
No Netica API function should be called before NewNeticaEnviron_ns or after 
  CloseNetica_bn, and most of them must not be called before InitNetica2_bn.
*/
#include <stdlib.h>

int main_ex (void){
	char mesg[MESG_LEN_ns];
	int res;
        
	env = NewNeticaEnviron_ns (NULL, NULL, NULL);    /* substitute your license string for the first NULL if desired */
	res = InitNetica2_bn (env, mesg);
	printf ("%s\n", mesg);
	if (res < 0)  exit (-1);
	/* 
	 * <rest of program>
	 */ 
	res = CloseNetica_bn (env, mesg);
	printf ("%s\n", mesg);
	return (res < 0 ? -1 : 0);
	}

/*_____________________________________________________________________________ GetNode
Like GetNodeNamed_bn, but generates an error if the name doesn't exist.
*/
node_bn* GetNode (char* node_name, net_bn* net){
	node_bn* node = GetNodeNamed_bn (node_name, net);
	if (node == NULL)
		NewError (env, 900, ERROR_ERR,
		         "GetNode: There is no node named '%s' in net '%s'",
		          node_name, GetNetName_bn (net));
	return node;
}

/*________________________________________________________________________ EnterFinding
Like EnterFinding_bn, but is passed names (C strings) instead.
*/
void EnterFinding (char* node_name, char* state_name, net_bn* net){
	node_bn* node = GetNode (node_name, net);
	state_bn state = GetStateNamed_bn (state_name, node);
	EnterFinding_bn (node, state);
}

/*______________________________________________________________________ SetNodeFinding
This routine may be useful if we are not sure whether node
  already has a finding, but if it does we just want to override it.
*/
void SetNodeFinding (node_bn* node, state_bn state){
	net_bn* net = GetNodeNet_bn (node);
	int saved = SetNetAutoUpdate_bn (net, 0);	/* turning it off can greatly aid efficiency */
	RetractNodeFindings_bn (node);
	EnterFinding_bn (node, state);
	SetNetAutoUpdate_bn (net, saved);
}

/*________________________________________________________________________ SetNodeValue
This routine may be useful if we are not sure whether node
  already has a finding, but if it does we just want to override it.
*/
void SetNodeValue (node_bn* node, double value){
	net_bn* net = GetNodeNet_bn (node);
	int saved = SetNetAutoUpdate_bn (net, 0);	/* turning it off can greatly aid efficiency */
	RetractNodeFindings_bn (node);
	EnterNodeValue_bn (node, value);
	SetNetAutoUpdate_bn (net, saved);
}

/*_______________________________________________________________________ GetNodeBelief
Like GetNodeBeliefs_bn, but is passed names (C strings) instead,
  and it returns the belief for a single state.
*/
double GetNodeBelief (char* node_name, char* state_name, net_bn* net){
	node_bn* node = GetNode (node_name, net);
	state_bn state = GetStateNamed_bn (state_name, node);
	const prob_bn* beliefs = GetNodeBeliefs_bn (node);
	if (!beliefs)  return UNDEF_DBL;
	return  beliefs[state];
}

/*________________________________________________________________________ SetNodeProbs
This routine is meant to be a more convenient (but slower) version of
  SetNodeProbs_bn.  Its first argument is the node whose probabilities we are setting.
  This is followed by the names of the conditioning states of its parents as C strings.
  Finally comes a list of doubles, being the probabilities for each of the states of
  the node.
For example:   SetNodeProbs (Temperature, "Windy", "Low", 0.6, 0.3, 0.1);
  means that the probability that Temperature is in its first state given that its
  first parent is in state "Windy" and its second parent is in state "Low" is 0.6, 
  the probability its in its second state is 0.3, and that its in its third state is 0.1.
Since the function prototype uses "...", you must be very careful to pass doubles
  for the probabilities (e.g. passing 0 instead of 0.0 will get you in trouble).
If time efficiency is critical, and you must set large probability tables,
  use SetNodeProbs_bn directly instead of this routine.
___________*/

#include <stdarg.h>
#define ARR_SIZE 20

void SetNodeProbs (node_bn* node, ...){
	state_bn parent_states[ARR_SIZE];
	prob_bn probs[ARR_SIZE];
	char* statename;
	state_bn state, numstates = GetNodeNumberStates_bn (node);
	const nodelist_bn* parents = GetNodeParents_bn (node);
	int pn, numparents = LengthNodeList_bn (parents);
	va_list ap;
	if (numstates > ARR_SIZE || numparents > ARR_SIZE){
		NewError_ns (env, 0, XXX_ERR, "SetNodeProbs: Array size defined too small");
		return;
	}
	va_start (ap, node);
	for (pn = 0;  pn < numparents;  ++pn){
		statename = va_arg (ap, char*);
		if (statename[0] == '*')  parent_states[pn] = EVERY_STATE;
		else parent_states[pn] = GetStateNamed_bn (statename, NthNode_bn (parents, pn));
	}
	for (state = 0;  state < numstates;  ++state)
		probs[state] = (prob_bn) va_arg (ap, double);
	va_end (ap);
	SetNodeProbs_bn (node, parent_states, probs);
}

void SetNodeFuncState (node_bn* node, state_bn value, ...){
	char* statename;
	state_bn parent_states[ARR_SIZE];
	const nodelist_bn* parents = GetNodeParents_bn (node);
	int pn, numparents = LengthNodeList_bn (parents);
	va_list ap;
	if (numparents > ARR_SIZE){
		NewError_ns (env, 0, XXX_ERR, "SetNodeFuncState: Array size defined too small");
		return;
	}
	va_start (ap, value);
	for (pn = 0;  pn < numparents;  ++pn){
		statename = va_arg (ap, char*);
		if (statename[0] == '*')  parent_states[pn] = EVERY_STATE;
		else parent_states[pn] = GetStateNamed_bn (statename, NthNode_bn (parents, pn));
	}
	va_end (ap);
	SetNodeFuncState_bn (node, parent_states, value);
}

void SetNodeFuncReal (node_bn* node, double value, ...){
	char* statename;
	state_bn parent_states[ARR_SIZE];
	const nodelist_bn* parents = GetNodeParents_bn (node);
	int pn, numparents = LengthNodeList_bn (parents);
	va_list ap;
	if (numparents > ARR_SIZE){
		NewError_ns (env, 0, XXX_ERR, "SetNodeFuncReal: Array size defined too small");
		return;
	}
	va_start (ap, value);
	for (pn = 0;  pn < numparents;  ++pn){
		statename = va_arg (ap, char*);
		if (statename[0] == '*')  parent_states[pn] = EVERY_STATE;
		else parent_states[pn] = GetStateNamed_bn (statename, NthNode_bn (parents, pn));
	}
	va_end (ap);
	SetNodeFuncReal_bn (node, parent_states, value);
}

void SetNodeExper (node_bn* node, double value, ...){
	char* statename;
	state_bn parent_states[ARR_SIZE];
	const nodelist_bn* parents = GetNodeParents_bn (node);
	int pn, numparents = LengthNodeList_bn (parents);
	va_list ap;
	if (numparents > ARR_SIZE){
		NewError_ns (env, 0, XXX_ERR, "SetNodeExper: Array size defined too small");
		return;
	}
	va_start (ap, value);
	for (pn = 0;  pn < numparents;  ++pn){
		statename = va_arg (ap, char*);
		if (statename[0] == '*')  parent_states[pn] = EVERY_STATE;
		else parent_states[pn] = GetStateNamed_bn (statename, NthNode_bn (parents, pn));
	}
	va_end (ap);
	SetNodeExperience_bn (node, parent_states, value);
}

#undef ARR_SIZE

/*____________________________________________________________________ MakeProbsUniform
Gives the passed node a uniform conditional probability distribution
  (i.e. all the probabilities the same).
*/
#include <stdlib.h>

void MakeProbsUniform (node_bn* node){
	int st, num_states  = GetNodeNumberStates_bn (node);
	int pn, num_parents = LengthNodeList_bn (GetNodeParents_bn (node));
	prob_bn*  uniform = (prob_bn*) malloc (num_states  * sizeof (prob_bn));
	state_bn* pstates = (state_bn*) malloc (num_parents * sizeof (state_bn));
	for (st = 0;  st < num_states;  ++st)  uniform[st] = (prob_bn) (1.0 / num_states);
	for (pn = 0;  pn < num_parents; ++pn)  pstates[pn] = EVERY_STATE;
	SetNodeProbs_bn (node, pstates, uniform);
	free (uniform);  free (pstates);
}

/*_____________________________________________________________________ GetNodeAllProbs
Puts all the conditional probabilities of 'node' into the array 'probs'.
If 'node' doesn't have any cond probs, 'probs' will be left unchanged.
You could allocate 'probs' as follows:
  int num_entries = SizeCartesianProduct (GetNodeParents_bn (node)) *
                    GetNodeNumberStates_bn (node)
  probs = (prob_bn*) malloc (num_entries) * sizeof (prob_bn);
*/
void GetNodeAllProbs (node_bn* node, prob_bn* probs, int num_entries){
	const prob_bn *prs;
	int i;
	assert (num_entries == SizeCartesianProduct (GetNodeParents_bn (node)) *
                           GetNodeNumberStates_bn (node));
	prs = GetNodeProbs_bn (node, NULL);
	if (prs)
		for (i = 0;  i < num_entries;  ++i)  probs[i] = prs[i];
}

/*__________________________________________________________________________ NextStates
STATES is a list of node states, one for each node of NODES.
This cycles through all possible configurations (i.e. elements of the cartesian
product) of STATES, odometer style, with the last state changing fastest.
It returns TRUE when all the configurations have been examined (i.e., when it
"rolls over" to all zeros again).
Don't forget to initialize STATES before calling it the first time (usually 
to all zeros).
See SizeCartesianProduct to calculate how many iterations will be made.
*/
bool_ns NextStates (state_bn* states, const nodelist_bn* nodes){
	int nn;
	for (nn = LengthNodeList_bn (nodes) - 1;  nn >= 0;  --nn){
		if (++states[nn] < GetNodeNumberStates_bn (NthNode_bn (nodes, nn)))
			return FALSE;
		states[nn] = 0;
		}
	return TRUE;
	}

/*_______________________________________________________________________ PrintNodeList
Prints out the names of the nodes in the list passed to it.
You may need to print a newline ('\n') before the writing appears.
See also NodeListToString.
*/
void PrintNodeList (nodelist_bn* nodes){
	int i, numnodes = LengthNodeList_bn (nodes);
	for (i = 0;  i < numnodes;  ++i){
		if (i != 0)  printf (", ");
		printf ("%s", GetNodeName_bn (NthNode_bn (nodes, i)));
	}
}

/*______________________________________________________________ RetractFindingsOfNodes
Retracts the findings of the nodes in the list passed to it.
Iff do_consts_too=FALSE, then any constant nodes in the list passed will not 
  have their "finding" retracted (retracting such findings can leave a compiled net uncompiled).
*/
void RetractFindingsOfNodes (nodelist_bn* nodes, bool_ns do_consts_too){
	net_bn* bn;
	int saved_auto, i, numnodes = LengthNodeList_bn (nodes);
	if (numnodes == 0)  return;
	bn = GetNodeNet_bn (NthNode_bn (nodes, 0));
	saved_auto = SetNetAutoUpdate_bn (bn, 0);		// this is just for efficiency, but it can make a big difference
	for (i = 0;  i < numnodes;  ++i){
		node_bn* node = NthNode_bn (nodes, i);
		if (do_consts_too || GetNodeKind_bn (node) != CONSTANT_NODE)
			RetractNodeFindings_bn (node);
		}
	if (saved_auto)  SetNetAutoUpdate_bn (bn, saved_auto);		// this will do a belief updating here if necessary
}

/*_______________________________________________________________________ FindNodeNamed
Returns the index of the node identified by 'name' in the list 'nodes',
  or -1 if it doesn't appear.
All of 'nodes' must be in the same net.
*/
int FindNodeNamed (const char* name, const nodelist_bn* nodes){
	if (LengthNodeList_bn (nodes) == 0)  return -1;
	else {
		net_bn* net = GetNodeNet_bn (NthNode_bn (nodes, 0));
		node_bn* node = GetNodeNamed_bn (name, net);
		if (node == NULL)  return -1;
		return IndexOfNodeInList_bn (node, nodes, 0);
	}
}

/*___________________________________________________________________ IndexOfNodeInList
Like IndexOfNodeInList_bn, but generates an error if there is not exactly
  one instance of 'node' in list 'nodes'.
*/
int IndexOfNodeInList (const node_bn* node, const nodelist_bn* nodes){
	int i = IndexOfNodeInList_bn (node, nodes, 0);
	if (i == -1)
		NewError (env, 901, ERROR_ERR,
		         "IndexOfNodeInList: There is no node '%s' in the list",
				 node ? GetNodeName_bn (node) : "null");
	else {
		int second = IndexOfNodeInList_bn (node, nodes, i + 1);
		if (second != -1)
			NewError (env, 902, ERROR_ERR,
					 "IndexOfNodeInList: There is more than one instance of node '%s' in the list",
					 node ? GetNodeName_bn (node) : "null");
	}
	return i;
}

/*_______________________________________________________________ RemoveOneNodeFromList
Removes 'node' from the list 'nodes'.
'node' must be in the list, and appear only once, or an error is generated.
*/
void RemoveOneNodeFromList (node_bn* node, nodelist_bn* nodes){
	int i = IndexOfNodeInList (node, nodes);
	RemoveNthNode_bn (nodes, i);
}

/*___________________________________________________________ RemoveNodeFromListIfThere
Removes the first occurrence of 'node' from the list.
If 'node' doesn't appear in the list, it does nothing.
*/
void RemoveNodeFromListIfThere (node_bn* node, nodelist_bn* nodes){
	int i = IndexOfNodeInList_bn (node, nodes, 0);
	if (i != -1) RemoveNthNode_bn (nodes, i);
}

/*___________________________________________________________________ RemoveNthNodeFast
This achieves the same purpose as RemoveNthNode_bn.
Since removing the last node is fastest, this will execute
  more quickly (for long lists), but the order won't be maintained.
*/
void RemoveNthNodeFast (int index, nodelist_bn* nodes){
	node_bn* lastnode = RemoveNthNode_bn (nodes, LAST_ENTRY);
	SetNthNode_bn (nodes, index, lastnode);
}

/*__________________________________________________________________________ DeleteLink
Removes the single link from node 'parent' to node 'child'.
If there is no link from 'parent' to 'child', or more than one, it generates an error.
See also DeleteLinks (to delete any and all links from 'parent' to 'child').
*/
void DeleteLink (node_bn* parent, node_bn* child){
	int pn = IndexOfNodeInList (parent, GetNodeParents_bn (child));
	DeleteLink_bn (pn, child);
}

/*_________________________________________________________________ DeleteLinksEntering
Removes all links entering the passed node.
*/
void DeleteLinksEntering (node_bn* child){
	int pn, num_parents = LengthNodeList_bn (GetNodeParents_bn (child));
	for (pn = 0;  pn < num_parents;  ++pn)
		DeleteLink_bn (0, child);       /* 0 since indexes change with each deletion */
}

/*____________________________________________________________________ SwitchNodeParent
Like SwitchNodeParent_bn, but accepts the parent node instead of a
  link index.
Switches the link from parent -> child to go from new_parent -> child.
Assumes there is already exactly one link from parent to child.
*/
void SwitchNodeParent (node_bn* parent, node_bn* child, node_bn* new_parent){
	int link_index = IndexOfNodeInList (parent, GetNodeParents_bn (child));
	SwitchNodeParent_bn (link_index, child, new_parent);
}

/*_________________________________________________________________________ DeleteNodes
Removes all of 'nodes' from their net, and frees them and node list 'nodes'.
*/
void DeleteNodes (nodelist_bn* nodes){
	int i, num = LengthNodeList_bn (nodes);
	for (i = 0;  i < num;  ++i){
		node_bn* node = NthNode_bn (nodes, i);
		SetNthNode_bn (nodes, i, NULL);				/* so node list stays legal */
		DeleteNode_bn (node);
	}
	DeleteNodeList_bn (nodes);
}

/*__________________________________________________________________ IsLinkDisconnected
Returns whether link 'link_index' entering 'node' is disconnected.
*/
bool_ns IsLinkDisconnected (int link_index, const node_bn* node){
	const node_bn* parent = NthNode_bn (GetNodeParents_bn (node), link_index);
	return GetNodeKind_bn (parent) == DISCONNECTED_NODE;
}

/*_______________________________________________________________________ TransferNodes
This transfers nodes from the net they are in to new_net,
  and returns a new list of the new nodes in the same order as they
  appeared in nodes.  The old list is freed.
In the process each node in nodes is freed, and a new one created,
  so be sure you don't have any dangling pointers to the old nodes.
Don't forget to free the nodelist_bn returned when you are done with it.
*/
nodelist_bn* TransferNodes (nodelist_bn* nodes, net_bn* new_net){
	int nn, num_nodes = LengthNodeList_bn (nodes);
	nodelist_bn* new_nodes = CopyNodes_bn (nodes, new_net, NULL);
	for (nn = 0;  nn < num_nodes;  ++nn)
		DeleteNode_bn (NthNode_bn (nodes, nn));
	DeleteNodeList_bn (nodes);         /* because its full of invalid pointers */
	return new_nodes;
}

/*_____________________________________________________________________________ DupNode
Handy function to duplicate a single node within its net.
*/
node_bn* DupNode (node_bn* node){
	return DuplicateNode (node, GetNodeNet_bn (node));
}

/*_______________________________________________________________________ DuplicateNode
Handy function to duplicate a single node into a new net.
*/
node_bn* DuplicateNode (node_bn* node, net_bn* new_net){
	node_bn* new_node;
	nodelist_bn *new_nodes, *nodes = NewNodeList_bn (1, env);
	SetNthNode_bn (nodes, 0, node);
	new_nodes = CopyNodes_bn (nodes, new_net, NULL);
	new_node = NthNode_bn (new_nodes, 0);
	DeleteNodeList_bn (nodes);
	DeleteNodeList_bn (new_nodes);
	return new_node;
}

/*________________________________________________________________________ DuplicateNet
Duplicates a whole net.
Normally you would use CopyNet_bn for that, but this is useful if you want to
  customize the code to do something different while duplicating.
A new name is passed (you could pass GetNetName_bn(net) if you wanted that 
  duplicated as well).
It makes the user-data pointer of the new net NULL, but you may want to copy the 
  pointer or duplicate the data it points to (some pointers within it may have 
  to be resolved in a similar style as ElimOrder list).
It doesn't duplicate visual info (node positions, etc.) or user fields.
Another way to duplicate a net, which will duplicate all fields, is to save the
  net to file (a stream buffer in memory, for speed), and read it back.
*/
net_bn* DuplicateNet (net_bn* net, const char* newname){
	nodelist_bn* new_order;
	net_bn* new_net = NewNet_bn (newname, env);
	nodelist_bn* new_nodes = CopyNodes_bn (GetNetNodes2_bn (net, "incl_docn"), new_net, NULL);

	new_order = MapNodeList (GetNetElimOrder_bn (net), new_net);
	SetNetElimOrder_bn (new_net, new_order);
	DeleteNodeList_bn (new_order);

	DeleteNodeList_bn (new_nodes);
	SetNetAutoUpdate_bn (new_net, GetNetAutoUpdate_bn (net));
	SetNetTitle_bn (new_net, GetNetTitle_bn (net));
	SetNetComment_bn (new_net, GetNetComment_bn (net));
	/* SetNetUserData_bn (new_net, 0, GetNetUserData_bn (net, 0));		// You may want this behaviour, but it would be different from CopyNet_bn */
	SetNetUserData_bn (new_net, 0, NULL);
	return new_net;
}

/*____________________________________________________________________________ NetNamed
Returns the first net with NAME, if there is one, otherwise NULL.
*/
#include <string.h>

net_bn* NetNamed (const char* name){
	int nth = 0;
	net_bn* net;
	do {
		net = GetNthNet_bn (nth++, env);
	} while (net && strcmp (name, GetNetName_bn (net)) != 0);
	return net;
}

/*______________________________________________________________________ FormCliqueWith
Ensures that the next compilation will produce a clique containing all
  of 'nodes', by adding a single-state node which has 'nodes' as parents.
This function is useful for the JointProbability_bn function, since that function works
  much faster if all of its nodes are in the same clique (providing it is going to
  be called multiple times after compiling, and 'nodes' is a short list).
This function returns the node added, or NULL only if it wasn't necc to add one.
  Its effects can be completely undone by calling DeleteNode_bn on the node it returns 
  (when it returns nonNULL).
*/
node_bn* FormCliqueWith (const nodelist_bn* nodes){
	net_bn* net;
	node_bn* new_node;
	int i, num_nodes = LengthNodeList_bn (nodes);
	if (num_nodes <= 1)  return NULL;
	net = GetNodeNet_bn (NthNode_bn (nodes, 0));
	new_node = NewNode_bn (NULL, 1, net);
	for (i = 0;  i < num_nodes;  ++i)
		AddLink_bn (NthNode_bn (nodes, i), new_node);
	return new_node;
}

/*__________________________________________________________________________ AbsorbNode
Handy function to absorb a single node.
*/
void AbsorbNode (node_bn* node){
	nodelist_bn* nodes = NewNodeList_bn (1, env);
	SetNthNode_bn (nodes, 0, node);
	AbsorbNodes_bn (nodes);
}

/*_____________________________________________________________________ DeleteNetTables
Removes the CPT and other tables from all nodes in the net.
*/
void DeleteNetTables (net_bn* net){
	int n;
	const nodelist_bn *nodes = GetNetNodes2_bn (net, NULL);
	for (n = 0;  n < LengthNodeList_bn (nodes);  ++n)
		DeleteNodeTables_bn (NthNode_bn (nodes,n));
}

/*________________________________________________________________________ FadeCPTables
The following does the same fading for a list of nodes:
*/
void FadeCPTables (const nodelist_bn* nodes, double degree){
	int nn, num = LengthNodeList_bn (nodes);
	for (nn = 0;  nn < num;  ++nn)
		FadeCPTable_bn (NthNode_bn (nodes, nn), degree);
}

/*__________________________________________________________________ PrintNeticaVersion
Don't call this routine until the global variable env has been 
  initialized by a call to NewNeticaEnviron_ns in the normal way.
*/
void PrintNeticaVersion (void){
	const char* version;
	GetNeticaVersion_bn (env, &version);
	printf ("Version of Netica running: %s\n", version);
}

/*_________________________________________________________________________ PrintErrors
This prints messages for all the serious errors currently registered with
  the environment in global variable 'env'.
*/
void PrintErrors (void){
	report_ns* error = NULL;
	while (1) {
		error = GetError_ns (env, ERROR_ERR, error);
		if (!error)  break;
		printf ("%d - %s\n", (int) ErrorNumber_ns (error), ErrorMessage_ns (error));
	}
}

/*____________________________________________________________________________ NewError
Like NewError_ns, but with printf style arguments for the error message.
You must be very careful that your error message length is limited so that it
  doesn't run over the declared buffer size, which you may want to make a little
  bigger or smaller.
For an example of its use, see the code for the "GetNode" function, in NeticaEx.c.
*/
#include <stdarg.h>

report_ns* NewError (environ_ns* env, int number, errseverity_ns severity, const char* mesg, ...){
	va_list ap;
	char buf[400];
	va_start (ap, mesg);
	vsprintf (buf, mesg, ap);
	/* vsnprintf (buf, sizeof (buf), mesg, ap);		// If your system has vsnprintf, use this instead of the above line */
	va_end (ap);
	return  NewError_ns (env, number, severity, buf);
}

/*_________________________________________________________________________ ClearErrors
Removes and frees all errors recorded with environment env 
  which are as serious as SEVERITY, or less serious.
Does the same function as ClearErrors_ns, but is less efficient.
*/
void ClearErrors (environ_ns* env, errseverity_ns severity){
	report_ns* error = NULL;
	while (1){
		error = GetError_ns (env, NOTHING_ERR, error);
		if (error == NULL)  break;
		if (ErrorSeverity_ns (error) <= severity)
			ClearError_ns (error);
	}
}

/*____________________________________________________________________________ StrLen
Does the same thing as the ANSI function 'strlen', but returns int.
*/
static int StrLen (const char* str){
	size_t n;
	const char* sp = str;
	while (*sp) ++sp;
	n = sp - str;
	if (n > INT_MAX)  return INT_MAX;		/* You may want to throw an error here instead, but in the intended usage, this should not create a problem */
	return (int)n;							/* Conversion from size_t to int won't be a problem, because of above check */
	}

/*__________________________________________________________________ SetNetUserString
*/
void SetNetUserString (net_bn* node, const char* fieldname, const char* str){
	SetNetUserField_bn (node, fieldname, str, StrLen (str), 0);
}

/*__________________________________________________________________ GetNetUserString
*/
const char* GetNetUserString (net_bn* net, const char* fieldname){
	return GetNetUserField_bn (net, fieldname, NULL, 0);
}

/*____________________________________________________________________ SetNetUserInt
*/
void SetNetUserInt (net_bn* net, const char* fieldname, int num){
	char buf[22];
	sprintf (buf, "%d", (int)num);
	/* snprintf (buf, sizeof(buf), "%d", (int)num);		// If your system has snprintf, use this instead of the above line */
	SetNetUserField_bn (net, fieldname, buf, StrLen (buf), 0);
}

/*____________________________________________________________________ GetNetUserInt
*/
long GetNetUserInt (net_bn* net, const char* fieldname){
	int length;
	const char* str = GetNetUserField_bn (net, fieldname, &length, 0);
	if (length == -1)
		NewError (env, 903, ERROR_ERR,
		         "GetNetUserInt: There is no user field named '%s' in net '%s'",
		          fieldname, GetNetName_bn (net));
	else {
		char* end;
		long num = strtol (str, &end, 10);
		if (*end != 0)
			NewError (env, 904, ERROR_ERR,
			         "GetNetUserInt: Field named '%s' of net '%s' was not storing an integer",
			          fieldname, GetNetName_bn (net));
		else return num;
	}
	return 0;
}

/*_________________________________________________________________ SetNetUserNumber
*/
void SetNetUserNumber (net_bn* net, const char* fieldname, double num){
	char buf[65];
	sprintf (buf, "%g", (double)num);
	/* snprintf (buf, sizeof(buf), "%g", (double)num);		// If your system has snprintf, use this instead of the above line */
	SetNetUserField_bn (net, fieldname, buf, StrLen (buf), 0);
}

/*_________________________________________________________________ GetNetUserNumber
*/
double GetNetUserNumber (net_bn* net, const char* fieldname){
	int length;
	const char* str = GetNetUserField_bn (net, fieldname, &length, 0);
	if (length == -1)
		NewError (env, 905, ERROR_ERR,
		         "GetNetUserNumber: There is no user field named '%s' in net '%s'",
		          fieldname, GetNetName_bn (net));
	else {
		char* end;
		double num = strtod (str, &end);
		if (*end != 0)
			NewError (env, 906, ERROR_ERR,
			         "GetNetUserNumber: Field named '%s' of net '%s' was not storing a number",
			          fieldname, GetNetName_bn (net));
		else return num;
	}
	return 0;
}

/*_________________________________________________________________ SetNodeUserString
*/
void SetNodeUserString (node_bn* node, const char* fieldname, const char* str){
	SetNodeUserField_bn (node, fieldname, str, StrLen (str), 0);
}

/*_________________________________________________________________ GetNodeUserString
*/
const char* GetNodeUserString (node_bn* node, const char* fieldname){
	return GetNodeUserField_bn (node, fieldname, NULL, 0);
}

/*____________________________________________________________________ SetNodeUserInt
*/
void SetNodeUserInt (node_bn* node, const char* fieldname, int num){
	char buf[22];
	sprintf (buf, "%d", (int)num);
	/* snprintf (buf, sizeof(buf), "%d", (int)num);		// If your system has snprintf, use this instead of the above line */
	SetNodeUserField_bn (node, fieldname, buf, StrLen (buf), 0);
}

/*____________________________________________________________________ GetNodeUserInt
*/
long GetNodeUserInt (node_bn* node, const char* fieldname){
	int length;
	const char* str = GetNodeUserField_bn (node, fieldname, &length, 0);
	if (length == -1)
		NewError (env, 903, ERROR_ERR,
		         "GetNodeUserInt: There is no user field named '%s' in node '%s'",
		          fieldname, GetNodeName_bn (node));
	else {
		char* end;
		long num = strtol (str, &end, 10);
		if (*end != 0)
			NewError (env, 904, ERROR_ERR,
			         "GetNodeUserInt: Field named '%s' of node '%s' was not storing an integer",
			          fieldname, GetNodeName_bn (node));
		else return num;
	}
	return 0;
}

/*_________________________________________________________________ SetNodeUserNumber
*/
void SetNodeUserNumber (node_bn* node, const char* fieldname, double num){
	char buf[65];
	sprintf (buf, "%g", (double)num);
	/* snprintf (buf, sizeof(buf), "%g", (double)num);		// If your system has snprintf, use this instead of the above line */
	SetNodeUserField_bn (node, fieldname, buf, StrLen (buf), 0);
}

/*_________________________________________________________________ GetNodeUserNumber
*/
double GetNodeUserNumber (node_bn* node, const char* fieldname){
	int length;
	const char* str = GetNodeUserField_bn (node, fieldname, &length, 0);
	if (length == -1)
		NewError (env, 905, ERROR_ERR,
		         "GetNodeUserNumber: There is no user field named '%s' in node '%s'",
		          fieldname, GetNodeName_bn (node));
	else {
		char* end;
		double num = strtod (str, &end);
		if (*end != 0)
			NewError (env, 906, ERROR_ERR,
			         "GetNodeUserNumber: Field named '%s' of node '%s' was not storing a number",
			          fieldname, GetNodeName_bn (node));
		else return num;
	}
	return 0;
}

/*_____________________________________________________________ PrintConfusionMatrix
Prints a confusion matrix table.  Use after a tester_bn has run its tests.

Sample output:
Confusion matrix for Cancer:
        Present  Absent   Actual
        11       1        Present
        4        184      Absent
*/
void PrintConfusionMatrix (tester_bn* tester, node_bn* node){
    int i,a,p;
    int numstates = GetNodeNumberStates_bn (node);
    printf ("Confusion matrix for %s:\n", GetNodeName_bn (node));
    for (i=0;  i < numstates;  ++i)
        printf ("\t %10s", GetNodeStateName_bn (node, i));
    printf ("\t Actual\n");
    for (a=0;  a < numstates;  ++a){
        for (p=0;  p < numstates;  ++p)
            printf ("\t %10d", (int) GetTestConfusion_bn (tester, node, p, a));
        printf ("\t %s\n", GetNodeStateName_bn (node, a));
    }
    printf ("\n");
}


/*======================= NOT IN REFERENCE MANUAL ========================*/


/*________________________________________________________________ CopyNodeRelation_bn
Copies the probability relation of node 'src' into node 'dest'.
src and dest must have compatible parents (e.g. same number of states), but perhaps in 
  a different order.  parent_order_dest consists of parents of src, but in the order of
  equivalent parents of dest.  If the parents of src and dest are in the same order,
  just call it as:   CopyNodeRelation_bn (dest, src, GetNodeParents_bn (src));
src and dest do not need to be in the same net.
*/
void CopyNodeRelation_bn (node_bn* dest, const node_bn* src, const nodelist_bn* parent_order_dest){
	const nodelist_bn* src_parents = GetNodeParents_bn (src);
	int num_parents = LengthNodeList_bn (src_parents);
	state_bn* src_states = (state_bn*) calloc (num_parents, sizeof (state_bn));
	state_bn* dest_states = (state_bn*) calloc (num_parents, sizeof (state_bn));
	while (1){
		const prob_bn* probs = GetNodeProbs_bn (src, src_states);
		SetNodeProbs_bn (dest, dest_states, probs);
		if (NextStates (src_states, src_parents))  break;
		MapStateList_bn (src_states, src_parents, dest_states, parent_order_dest);
		if (GetError_ns (env, ERROR_ERR, NULL))  break;
	}
	free (src_states);
	free (dest_states);
}

/*______________________________________________________________________ MultiDimnIndex
*/
int MultiDimnIndex (const state_bn states[], const nodelist_bn* nodes){
	int index = 0;
	int numnodes = LengthNodeList_bn (nodes);
	int i;
	for (i = 0;  i < numnodes;  ++i){
		node_bn* node = NthNode_bn (nodes, i);
		index = index * GetNodeNumberStates_bn (node) + *states++;	/* Borland C++ 5.0 and 6.0 erroneosly say this is a const violation */
		}
	return index;
	}

/*________________________________________________________________ SizeCartesianProduct
Returns the size of the cartesian product of the states of nodes,
  or 0 if one of nodes is continuous and not discretized.
Returns DBL_MAX if the size is greater than DBL_MAX (this type of overflow is not
  uncommon, since the values returned can be very large).
See NextStates to scan through them odometer style.
*/
#include <float.h>

double SizeCartesianProduct (const nodelist_bn* nodes){
	double size = 1;
	int nn;
	for (nn = 0;  nn < LengthNodeList_bn (nodes);  ++nn){
		int num_states = GetNodeNumberStates_bn (NthNode_bn (nodes, nn));
		if (num_states == 0)  return 0;
		if (num_states + 1 > DBL_MAX / size)  return DBL_MAX;
		size *= num_states;
		}
	return size;
}

/*_____________________________________________________________ MapNode ___ MapNodeList
Returns the node from net DEST_NET which is equivalent to NODE passed.
Equivalency is determined by the nodes having the same name.
This routine may seem like an inefficient way to map nodes, but since GetNodeNamed_bn
  uses a hashing table, it scales okay to large networks.
MapNodeList does the same thing for a whole list of nodes.  Don't forget to free the
  node list it returns.
*/
node_bn* MapNode (const node_bn* node, const net_bn* dest_net){
	return GetNodeNamed_bn (GetNodeName_bn (node), dest_net);
}

nodelist_bn* MapNodeList (const nodelist_bn* nodes, const net_bn* dest_net){
	node_bn* oldnode,* newnode;
	nodelist_bn* new_nodes;
	int nn, numnodes = LengthNodeList_bn (nodes);
	if (nodes == NULL)  return NULL;
	new_nodes = NewNodeList_bn (numnodes, env);
	for (nn = 0;  nn < numnodes;  ++nn){
		oldnode = NthNode_bn (nodes, nn);
		newnode = GetNodeNamed_bn (GetNodeName_bn (oldnode), dest_net);
		SetNthNode_bn (new_nodes, nn, newnode);
	}
	return new_nodes;
}

/*________________________________________________________________________ MapNodeList1
This does the same sort of thing as MapNodeList, but defines the mapping
  in terms of 2 matching lists of nodes, rather than identical node names in different
  networks.  It is useful when the names of matching nodes might be different 
  (e.g. duplicating into a net which already has nodes with the same names), 
  or when duplicating within one net.
WARNING: This modifies the user-data slots, so if you are already using them, you
  should change this routine to just use a field of the structure you have at each 
  node's user-data slot.
To compare with MapNodeList, see how DuplicateNet uses that routine, and compare with:

net_bn* DuplicateNet (net_bn* net, const char* new_name){
	nodelist_bn* new_order;
	net_bn* new_net = NewNet_bn (new_name, env);
	const nodelist_bn* old_nodes = GetNetNodes2_bn (net, NULL);
	nodelist_bn* new_nodes = CopyNodes_bn (old_nodes, new_net, NULL);

	new_order = MapNodeList1 (GetNetElimOrder_bn (net), old_nodes, new_nodes);
	SetNetElimOrder_bn (new_net, new_order);
	DeleteNodeList_bn (new_order);
	...
____________*/

nodelist_bn* MapNodeList1 (const nodelist_bn* nodes, const nodelist_bn* src_nodes, const nodelist_bn* dest_nodes){
	nodelist_bn* new_nodes;
	int nn, numnodes = LengthNodeList_bn (src_nodes);
	if (nodes == NULL)  return NULL;
	for (nn = 0;  nn < numnodes;  ++nn)
		SetNodeUserData_bn (NthNode_bn (src_nodes, nn), 0, NthNode_bn (dest_nodes, nn));    /* src_nodes[nn].userptr = dest_nodes[nn]  */
	numnodes = LengthNodeList_bn (nodes);
	new_nodes = NewNodeList_bn (numnodes, env);
	for (nn = 0;  nn < numnodes;  ++nn)
		SetNthNode_bn (new_nodes, nn, (node_bn*) GetNodeUserData_bn (NthNode_bn (nodes, nn), 0));      /* new_nodes[nn] = nodes[nn].userptr  */
	return new_nodes;
}

/*_________________________________________________________________________ DeleteLinks
Removes all links from node 'parent' to node 'child' (usually there is
  only 0 or 1 link).
It iterates backwards through the list of parents, since each time a link is removed,
  the indexes of all the links following it changes.
See also DeleteLink (for when it is known there is exactly one).
*/
void DeleteLinks (node_bn* parent, node_bn* child){
	while (1){
		const nodelist_bn* parents = GetNodeParents_bn (child);
		int pn = IndexOfNodeInList_bn (parent, parents, 0);
		if (pn == -1) break;
		DeleteLink_bn (pn, child);
	}
}

/*_________________________________________________________________ DisconnectNodeGroup
This disconnects a group of nodes from the rest of the net,
  without removing any of the links between members of the group,
  and returns a new list of the new nodes in the same order as they
  appeared in nodes.  The old list nodes is freed.
In the process each node in nodes is freed, and a new one constructed,
  so be sure you don't have any dangling pointers to the old nodes.
It uses TransferNodes, which is defined in the example above.
*/
nodelist_bn* DisconnectNodeGroup (nodelist_bn* nodes){
	net_bn* net,* scratch_net;
	nodelist_bn* new_nodes;
	int num_nodes = LengthNodeList_bn (nodes);
	if (num_nodes == 0)  return nodes;     /* otherwise next line will fail */
	net = GetNodeNet_bn (NthNode_bn (nodes, 0));
	scratch_net = NewNet_bn ("temp", env);
	new_nodes = TransferNodes (nodes, scratch_net);
	new_nodes = TransferNodes (new_nodes, net);
	DeleteNodeList_bn (nodes);               /* because its full of invalid pointers */
	DeleteNet_bn (scratch_net);
	return new_nodes;
}

/*____________________________________________________________________ NodeListToString
Returns a freshly allocated, null terminated, C char string containing
  the names of all the nodes in the passed list, separated by commas.
This may be useful during development / debugging.
Don't forget to free the string returned, using 'free'.
See also PrintNodeList.
*/
#include <string.h>

char* NodeListToString (const nodelist_bn* nodes){
	int nn, num_nodes = LengthNodeList_bn (nodes);
	char* str = (char*) malloc (num_nodes * (NAME_MAX_ns + 2) + 1);
	char* pstr = str;
	if (str == NULL)  return NULL;                           /* out of memory */
	for (nn = 0;  nn < num_nodes;  ++nn){
		if (NthNode_bn (nodes, nn) != NULL){
			const char* node_name = GetNodeName_bn (NthNode_bn (nodes, nn));
			strcpy (pstr, node_name);
			pstr += strlen (node_name);
			}
		if (nn < num_nodes - 1)  {*pstr++ = ',';  *pstr++ = ' ';}
		}
	*pstr = '\0';											/* null terminate */
	return str;
}

/*____________________________________________________________________ CountCasesInFile
Counts the number of cases in a case file.
This is not very efficient; if you just needed the number of cases it would be better
  to just count the number of relevant lines in the file.  However, if you wanted to 
  filter out some cases, or count categories of cases, this will make a good template.
*/
long CountCasesInFile (stream_ns* casefile){
	nodelist_bn* empty_nodes = NewNodeList_bn (0, env);
	long numcases = 0;
	caseposn_bn caseposn = FIRST_CASE;
	while (1){
		ReadNetFindings2_bn (&caseposn, casefile, FALSE, empty_nodes, NULL, NULL);
		if (caseposn == NO_MORE_CASES)  break;
		if (GetError_ns (env, ERROR_ERR, NULL))  break;
		++numcases;
		caseposn = NEXT_CASE;
	}
	DeleteNodeList_bn (empty_nodes);
	return numcases;
}

/*__________________________________________________________________ RemoveUnusedStates
Removes from NODE those states that have zero probability of occuring,
  according to the CPT of NODE.
Returns the number of states removed.
Note: Some other states may have zero probability of occuring if the rest of the
  net indicates it.
*/
int RemoveUnusedStates (node_bn* node){
	int num_states  = GetNodeNumberStates_bn (node);
	int num_parents = LengthNodeList_bn (GetNodeParents_bn (node));
	int num_zero = num_states;
	state_bn st, *parent_states = (state_bn*) calloc (num_parents, sizeof (state_bn));
	int* nonzero_states = (int*) calloc (num_states, sizeof (int));
	while (1){
		const prob_bn* probs = GetNodeProbs_bn (node, parent_states);
		if (!probs)  break;
		for (st = 0;  st < num_states;  ++st)
			if (nonzero_states[st] == 0  &&  probs[st] != 0){
				nonzero_states[st] = 1;
				--num_zero;
			}
		if (num_zero == 0)  break;		/* quit early, because there aren't any */
		if (NextStates (parent_states, GetNodeParents_bn (node)))  break;
		if (GetError_ns (env, ERROR_ERR, NULL))  break;
	}
	for (st = num_states - 1;  st >= 0;  --st)
		if (nonzero_states[st] == 0)
			RemoveNodeState_bn (node, st);
	free (parent_states);
	free (nonzero_states);
	return num_zero;
}

/*__________________________________________________________________ MakeInverseOrdering
Given ORDER, a permutation array, this creates the inverse order:
  invorder[order[i]] = i
Useful to use with ReorderNodeStates_bn.
*/
int* MakeInverseOrdering (const int order[], int num, int invorder[]){
	int i;
	for (i = 0;  i < num;  ++i)  invorder[i] = -1;		/* to help catch missing entries in order */
	for (i = 0;  i < num;  ++i)  invorder[order[i]] = i;
	return invorder;
	}


/*=============================== OBSOLETE =================================*/


/*___________________________________________________________________ SetNodeStateNames

OBSOLETE - New software should use SetNodeStateNames_bn instead of this.

This wraps several calls to SetNodeStateName_bn into one.
For instance to give the node 'Weather' its 3 state names you could call:

    SetNodeStateNames (Weather, "sunny", "cloudy", "rainy");
*/
#include <stdarg.h>

void SetNodeStateNames (node_bn* node, ...){
	state_bn state, numstates = GetNodeNumberStates_bn (node);
	va_list ap;
	va_start (ap, node);
	for (state = 0;  state < numstates;  ++state)
		SetNodeStateName_bn (node, state, va_arg (ap, char*));
	va_end (ap);
}

/*____________________________________________________________________ SetNodeFuncValue
OBSOLETE - New software should use SetNodeFuncState or SetNodeFuncReal.
*/
#define ARR_SIZE 20

void SetNodeFuncValue (node_bn* node, double value, ...){
	char* statename;
	state_bn parent_states[ARR_SIZE];
	const nodelist_bn* parents = GetNodeParents_bn (node);
	int pn, numparents = LengthNodeList_bn (parents);
	va_list ap;
	if (numparents > ARR_SIZE){
		NewError_ns (env, 0, XXX_ERR, "SetNodeFuncValue: Array size defined too small");
		return;
	}
	va_start (ap, value);
	for (pn = 0;  pn < numparents;  ++pn){
		statename = va_arg (ap, char*);
		if (statename[0] == '*')  parent_states[pn] = EVERY_STATE;
		else parent_states[pn] = GetStateNamed_bn (statename, NthNode_bn (parents, pn));
	}
	va_end (ap);
	if (GetNodeType_bn (node) == DISCRETE_TYPE)
	     SetNodeFuncState_bn (node, parent_states, (int)value);
	else SetNodeFuncReal_bn  (node, parent_states, value);
}
#undef ARR_SIZE

/*________________________________________________________________________ ExpectedValue
OBSOLETE - New software should use the built-in function GetNodeExpectedValue_bn.
*/
double ExpectedValue (node_bn* node, double* std_dev){
	return GetNodeExpectedValue_bn (node, std_dev, NULL, NULL);		/* this function now built in */
}

/*__________________________________________________________________ PositionInNodeList
OBSOLETE - New software should use IndexOfNodeInList_bn instead.
*/
int PositionInNodeList (const node_bn* node, const nodelist_bn* nodes){
	return IndexOfNodeInList_bn (node, nodes, 0);
}

/*__________________________________________________________________ RemoveNodeFromList
OBSOLETE - New software should use RemoveOneNodeFromList or RemoveNodeFromListIfThere.
*/
void RemoveNodeFromList (node_bn* node, nodelist_bn* nodes){
	RemoveNodeFromListIfThere (node, nodes);
}

/*_____________________________________________________________________ SetNodeAllProbs
OBSOLETE - New software should use SetNodeProbs_bn, passing NULL for psts.
*/
void SetNodeAllProbs (node_bn* node, const prob_bn* probs){
	SetNodeProbs_bn (node, NULL, probs);
}


