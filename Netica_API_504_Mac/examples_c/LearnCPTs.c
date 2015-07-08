/* 
 *  LearnCPTs.c
 *
 *  Example use of Netica-C API for learning the CPTs of a Bayes net
 *  from a file of cases.
 *
 * Copyright (C) 1992-2007 by Norsys Software Corp.
 * The software in this file may be copied, modified, and/or included in 
 * derivative works without charge or obligation.
 * This file contains example software only, and Norsys makes no warranty that 
 * it is suitable for any particular purpose, or without defects.
 */

#include <stdio.h>
#include <stdlib.h>
#include "Netica.h"
#include "NeticaEx.h"

#define CHKERR  {if (GetError_ns (env, ERROR_ERR, NULL))  goto error;}

environ_ns* env;

int main (void){
	net_bn *orig_net = NULL, *learned_net = NULL;
	const nodelist_bn* orig_nodes;
	nodelist_bn* learned_nodes = NULL;
	int numnodes;
	stream_ns* casefile;
	char mesg[MESG_LEN_ns];
	int i, res;
	report_ns* err;
	
	env = NewNeticaEnviron_ns (NULL, NULL, NULL);
	res = InitNetica2_bn (env, mesg);
	printf ("%s\n", mesg);
	if (res < 0)  exit (-1);
	
	/* Read in the net created by the BuildNet.c example program */
	orig_net = ReadNet_bn ( NewFileStream_ns ("Data Files/ChestClinic.dne", env, NULL), NO_VISUAL_INFO);
	orig_nodes = GetNetNodes_bn (orig_net);
	SetNetAutoUpdate_bn (orig_net, 0);
	CHKERR

	learned_net = NewNet_bn ("Learned_ChestClinic", env);
	learned_nodes = CopyNodes_bn (orig_nodes, learned_net, NULL);
	numnodes = LengthNodeList_bn (learned_nodes);

	/* Remove CPTables of nodes in learned_net, so new ones can be learned. */
	for (i = 0;  i < numnodes;  ++i)
		DeleteNodeTables_bn (NthNode_bn (learned_nodes, i));
	CHKERR
	
	/* Read in the case file created by the the SimulateCases.c
	   example program, and learn new CPTables. */
	casefile = NewFileStream_ns ("Data Files/ChestClinic.cas", env, NULL);
	ReviseCPTsByCaseFile_bn (casefile, learned_nodes, 0, 1.0);

	WriteNet_bn (learned_net,  NewFileStream_ns ("Data Files/Learned_ChestClinic.dne", env, NULL));
	CHKERR
	
end:
	DeleteNodeList_bn (learned_nodes);
	DeleteNet_bn (orig_net);
	DeleteNet_bn (learned_net);
	res= CloseNetica_bn (env, mesg);
	printf ("%s\n", mesg);
	printf ("Press <enter> key to quit ", mesg);
	getchar();
	return (res < 0 ? -1 : 0);

error:
	err = GetError_ns (env, ERROR_ERR, NULL);
	fprintf (stderr, "LearnCPTs: Error %d %s\n", 
	         ErrorNumber_ns (err), ErrorMessage_ns (err));
	goto end;
}

	/* ==============================================================
	 * This alternate way can replace the ReviseCPTsByCaseFile_bn 
	 * line above, if you need to filter or adjust individual cases.

	case_posn = FIRST_CASE;
	while(1){
		RetractNetFindings_bn (learned_net);
		ReadCase_bn (&case_posn, casefile, learned_nodes, NULL, NULL);
		if (case_posn == NO_MORE_CASES)  break;
		ReviseCPTsByFindings_bn (learned_nodes, 0, 1.0);
		case_posn = NEXT_CASE;
		CHKERR
		}

	  ============================================================== */
