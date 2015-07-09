/* 
 *  NetTester.c
 *
 *  Example use of Netica-C API for testing the performance of 
 *  a learned net with the net tester tool.
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
	nodelist_bn *test_nodes = NULL, *unobsv_nodes = NULL;
	node_bn *VisitAsia, *Tuberculosis, *Smoking, *Cancer, *TbOrCa, *XRay, *Bronchitis, *Dyspnea;
	tester_bn* tester = NULL;
	stream_ns* casefile = NULL;
	caseset_cs* caseset = NULL;
	char mesg[MESG_LEN_ns];
	int res;
	report_ns* err;
	
	env = NewNeticaEnviron_ns (NULL, NULL, NULL);
	res = InitNetica2_bn (env, mesg);
	printf ("%s\n", mesg);
	if (res < 0)  exit (-1);
	CHKERR

	net = ReadNet_bn (NewFileStream_ns ("Data Files/ChestClinic.dne", env, NULL), NO_VISUAL_INFO);
	test_nodes   = NewNodeList2_bn (0, net);
	unobsv_nodes = NewNodeList2_bn (0, net);
	VisitAsia    = NodeNamed_bn ("VisitAsia", net);
	Tuberculosis = NodeNamed_bn ("Tuberculosis", net);
	Cancer       = NodeNamed_bn ("Cancer",  net);
	Smoking      = NodeNamed_bn ("Smoking", net);
	TbOrCa       = NodeNamed_bn ("TbOrCa", net);
	XRay         = NodeNamed_bn ("XRay", net);
	Dyspnea      = NodeNamed_bn ("Dyspnea", net);
	Bronchitis   = NodeNamed_bn ("Bronchitis", net);
	CHKERR

	// The observed nodes are the factors known during diagnosis:
	AddNodeToList_bn (Cancer, test_nodes, LAST_ENTRY);

	// The unobserved nodes are the factors not known during diagnosis:
	AddNodeToList_bn (Bronchitis,   unobsv_nodes, LAST_ENTRY);
	AddNodeToList_bn (Tuberculosis, unobsv_nodes, LAST_ENTRY);
	AddNodeToList_bn (TbOrCa,       unobsv_nodes, LAST_ENTRY);

	RetractNetFindings_bn (net);   // IMPORTANT: Otherwise any findings will be part of tests !!
	CompileNet_bn (net);
	CHKERR
	tester = NewNetTester_bn (test_nodes, unobsv_nodes, -1);
	CHKERR
	
	casefile = NewFileStream_ns ("Data Files/ChestClinic.cas", env, NULL);
	caseset = NewCaseset_cs ("ChestClinicCases", env);
	AddFileToCaseset_cs (caseset, casefile, 1.0, NULL);
	TestWithCaseset_bn (tester, caseset);
	CHKERR

	PrintConfusionMatrix (tester, Cancer);
	printf ("Error rate for %s = %g %%\n\n", GetNodeName_bn (Cancer), 
		GetTestErrorRate_bn (tester, Cancer) * 100.0);
	printf ("Logarithmic loss for %s = %.4g\n\n", GetNodeName_bn (Cancer), 
		GetTestLogLoss_bn (tester, Cancer));
	CHKERR

	
end:
	DeleteCaseset_cs (caseset);
	DeleteStream_ns (casefile);
	DeleteNetTester_bn (tester);
	DeleteNodeList_bn (test_nodes);
	DeleteNodeList_bn (unobsv_nodes);
	DeleteNet_bn (net);
	CHKERR
	res= CloseNetica_bn (env, mesg);
	printf ("%s\n", mesg);
	printf ("Press <enter> key to quit ", mesg);
	getchar();
	return (res < 0 ? -1 : 0);

error:
	err = GetError_ns (env, ERROR_ERR, NULL);
	fprintf (stderr, "NetTester: Error %d %s\n", 
	         ErrorNumber_ns (err), ErrorMessage_ns (err));
	goto end;
}
