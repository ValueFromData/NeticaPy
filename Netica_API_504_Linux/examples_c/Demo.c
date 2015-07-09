
/* 
 * Demo.c
 *
 * Example use of Netica API Programmer's Library
 *
 * This is a combination of the first 2 examples in the Netica API
 * Reference Manual.  It can be used to test if the installation is successful.
 *
 * Copyright (C) 1992-2010 by Norsys Software Corp.
 * The software in this file may be copied, modified, and/or included in 
 * derivative works without charge or obligation.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "Netica.h"
#include "NeticaEx.h"

#define CHKERR  {if (GetError_ns (env, ERROR_ERR, NULL))  goto error;}

extern environ_ns *env;

int main (void){
	net_bn *net;
	node_bn *VisitAsia, *Tuberculosis, *Smoking, *Cancer, *TbOrCa, *XRay;
	double belief;
	char mesg[MESG_LEN_ns];
	int res;
	
	printf ("\nWelcome to Netica API!\n");
	printf ("This demo project is from the first 2 examples of the Reference Manual.\n");
	printf ("If it compiles, links and runs successfully (i.e. without generating\n");
	printf ("errors), then your installation is probably good.\n");
	printf ("Now you can replace the Demo.c file with your own code.\n");
	printf ("--------------------------------------------------------------------\n\n");
	
	env = NewNeticaEnviron_ns (NULL, NULL, NULL);
	res = InitNetica2_bn (env, mesg);

	printf ("%s\n", mesg);
	if (res < 0)  return -1;
	
	net = NewNet_bn ("ChestClinic", env);
	CHKERR

	VisitAsia =    NewNode_bn ("VisitAsia", 2, net);
	Tuberculosis = NewNode_bn ("Tuberculosis", 2, net);
	Smoking =      NewNode_bn ("Smoking", 2, net);
	Cancer =       NewNode_bn ("Cancer", 2, net);
	TbOrCa =       NewNode_bn ("TbOrCa", 2, net);
	XRay =         NewNode_bn ("XRay", 2, net);
	CHKERR

	SetNodeStateNames_bn (VisitAsia,   "visit,   no_visit");
	SetNodeStateNames_bn (Tuberculosis,"present, absent");
	SetNodeStateNames_bn (Smoking,     "smoker,  nonsmoker");
	SetNodeStateNames_bn (Cancer,      "present, absent");
	SetNodeStateNames_bn (TbOrCa,      "true,    false");
	SetNodeStateNames_bn (XRay,        "abnormal,normal");
	SetNodeTitle_bn (TbOrCa, "Tuberculosis or Cancer");
	SetNodeTitle_bn (Cancer, "Lung Cancer");
	CHKERR

	AddLink_bn (VisitAsia, Tuberculosis);
	AddLink_bn (Smoking, Cancer);
	AddLink_bn (Tuberculosis, TbOrCa);
	AddLink_bn (Cancer, TbOrCa);
	AddLink_bn (TbOrCa, XRay);
	CHKERR
	
	SetNodeProbs (VisitAsia, 0.01, 0.99);
	
	SetNodeProbs (Tuberculosis, "visit",    0.05, 0.95);
	SetNodeProbs (Tuberculosis, "no_visit", 0.01, 0.99);

	SetNodeProbs (Smoking, 0.5, 0.5);

	SetNodeProbs (Cancer, "smoker",    0.1,  0.9);
	SetNodeProbs (Cancer, "nonsmoker", 0.01, 0.99);

	//                   Tuberculosis Cancer
	SetNodeProbs (TbOrCa, "present", "present", 1.0, 0.0);
	SetNodeProbs (TbOrCa, "present", "absent",  1.0, 0.0);
	SetNodeProbs (TbOrCa, "absent",  "present", 1.0, 0.0);
	SetNodeProbs (TbOrCa, "absent",  "absent",  0.0, 1.0);

	//                  TbOrCa  Abnormal Normal
	SetNodeProbs (XRay, "true",  0.98,  0.02);
	SetNodeProbs (XRay, "false", 0.05,  0.95);
	CHKERR

	CompileNet_bn (net);
	CHKERR

	belief = GetNodeBelief ("Tuberculosis", "present", net);
	CHKERR

	printf ("The probability of tuberculosis is %g\n\n", belief);

	EnterFinding ("XRay", "abnormal", net);
	belief = GetNodeBelief ("Tuberculosis", "present", net);
	CHKERR

	printf ("Given an abnormal X-ray, \n\
         the probability of tuberculosis is %g\n\n", belief);

	EnterFinding ("VisitAsia", "visit", net);
	belief = GetNodeBelief ("Tuberculosis", "present", net);
	CHKERR

	printf ("Given an abnormal X-ray and a visit to Asia, \n\
	     the probability of tuberculosis is %g\n\n", belief);

	EnterFinding ("Cancer", "present", net);
	belief = GetNodeBelief ("Tuberculosis", "present", net);
	CHKERR

	printf ("Given abnormal X-ray, Asia visit, and lung cancer, \n\
         the probability of tuberculosis is %g\n\n", belief);

end:
	DeleteNet_bn (net);
	res = CloseNetica_bn (env, mesg);
	printf ("%s\n", mesg);
	printf ("Press <enter> key to quit ", mesg);
	getchar();
	return (res < 0) ? -1 : 0;

error:
	fprintf (stderr, "NeticaDemo: Error in %s\n", 
	         ErrorMessage_ns (GetError_ns (env, ERROR_ERR, NULL)));
	goto end;
}

