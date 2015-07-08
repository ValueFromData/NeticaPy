/* 
 *  LearnLatent.c
 *
 *  Example use of Netica-C API for learning a latent (hidden) variable
 *  using the EM Learning technique.
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
	net_bn *net = NULL;
	node_bn *R,*S,*T,*A;
	const nodelist_bn* nodes;
	stream_ns* casefile = NULL;
	caseset_cs* cases = NULL;
	learner_bn *learner = NULL;
	char mesg[MESG_LEN_ns];
	int res;
	report_ns* err;

	env = NewNeticaEnviron_ns (NULL, NULL, NULL);
	res = InitNetica2_bn (env, mesg);
	printf ("%s\n", mesg);
	if (res < 0)  exit (-1);
	
	/* Build the net */

	net = NewNet_bn ("Learned_Latent", env);
	CHKERR

	R = NewNode_bn ("R", 2, net);
	S = NewNode_bn ("S", 2, net);
	T = NewNode_bn ("T", 2, net);
	SetNodeStateName_bn (R, 0, "false");
	SetNodeStateName_bn (R, 1, "true");
	SetNodeStateName_bn (S, 0, "false");
	SetNodeStateName_bn (S, 1, "true");
	SetNodeStateName_bn (T, 0, "false");
	SetNodeStateName_bn (T, 1, "true");

	A = NewNode_bn ("A", 2, net); // the latent node; trying 2 states
	// A = NewNode_bn ("A", 3, net); // the latent node; trying 3 states

	AddLink_bn (A,R);
	AddLink_bn (A,S);
	AddLink_bn (A,T);

	CHKERR

	nodes = GetNetNodes_bn (net);

	/* Read the case file into a caseset */

	cases = NewCaseset_cs ("LearnLatentCases", env);
	casefile = NewFileStream_ns ("Data Files/LearnLatent.cas", env, NULL);
	AddFileToCaseset_cs (cases, casefile, 1.0, NULL);

	learner = NewLearner_bn (EM_LEARNING, NULL, env);
	SetLearnerMaxIters_bn (learner, 200); /* terminate at 200 iterations */

	LearnCPTs_bn (learner, nodes, cases, 1.0);

	WriteNet_bn (net,  NewFileStream_ns ("Data Files/Learned_Latent.dne", env, NULL));
	CHKERR
	
end:
	DeleteLearner_bn (learner);
	DeleteStream_ns (casefile);
	DeleteCaseset_cs (cases);
	DeleteNet_bn (net);
	res= CloseNetica_bn (env, mesg);
	printf ("%s\n", mesg);
	printf ("Press <enter> key to quit ", mesg);
	getchar();
	return (res < 0 ? -1 : 0);

error:
	err = GetError_ns (env, ERROR_ERR, NULL);
	fprintf (stderr, "LearnLatent: Error %d %s\n", 
	         ErrorNumber_ns (err), ErrorMessage_ns (err));
	goto end;
}
