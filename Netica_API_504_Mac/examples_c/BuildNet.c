/* 
 *  BuildNet.c
 *
 *  Example use of Netica-C API to construct a Bayes net and save it to file.
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
	net_bn* net = NULL;
	node_bn *VisitAsia, *Tuberculosis, *Smoking, *Cancer, *TbOrCa, *XRay, *Bronchitis, *Dyspnea;
	char mesg[MESG_LEN_ns];
	int res;
	report_ns* err;
	
	env = NewNeticaEnviron_ns (NULL, NULL, NULL);
	res = InitNetica2_bn (env, mesg);
	printf ("%s\n", mesg);
	if (res < 0)  exit (-1);
	
	net = NewNet_bn ("ChestClinic", env);
	CHKERR

	VisitAsia =    NewNode_bn ("VisitAsia", 2, net);
	Tuberculosis = NewNode_bn ("Tuberculosis", 2, net);
	Smoking =      NewNode_bn ("Smoking", 2, net);
	Cancer =       NewNode_bn ("Cancer", 2, net);
	TbOrCa =       NewNode_bn ("TbOrCa", 2, net);
	XRay =         NewNode_bn ("XRay", 2, net);
	Dyspnea =      NewNode_bn ("Dyspnea", 2, net);
	Bronchitis =   NewNode_bn ("Bronchitis", 2, net);
	CHKERR

	SetNodeStateNames_bn (VisitAsia,   "visit,   no_visit");
	SetNodeStateNames_bn (Tuberculosis,"present, absent");
	SetNodeStateNames_bn (Smoking,     "smoker,  nonsmoker");
	SetNodeStateNames_bn (Cancer,      "present, absent");
	SetNodeStateNames_bn (TbOrCa,      "true,    false");
	SetNodeStateNames_bn (XRay,        "abnormal,normal");
	SetNodeStateNames_bn (Dyspnea,     "present, absent");
	SetNodeStateNames_bn (Bronchitis,  "present, absent");
	SetNodeTitle_bn (TbOrCa, "Tuberculosis or Cancer");
	SetNodeTitle_bn (Cancer, "Lung Cancer");
	CHKERR

	AddLink_bn (VisitAsia, Tuberculosis);
	AddLink_bn (Smoking, Cancer);
	AddLink_bn (Tuberculosis, TbOrCa);
	AddLink_bn (Cancer, TbOrCa);
	AddLink_bn (TbOrCa, XRay);
	AddLink_bn (TbOrCa, Dyspnea);
	AddLink_bn (Smoking, Bronchitis);
	AddLink_bn (Bronchitis, Dyspnea);
	CHKERR
	
	// WARNING: floats must be passed to SetNodeProbs, ie, 0.0 not 0

	SetNodeProbs (VisitAsia, 0.01, 0.99);
	
	SetNodeProbs (Tuberculosis, "visit",    0.05, 0.95);
	SetNodeProbs (Tuberculosis, "no_visit", 0.01, 0.99);

	SetNodeProbs (Smoking, 0.5, 0.5);

	SetNodeProbs (Cancer, "smoker",    0.1,  0.9);
	SetNodeProbs (Cancer, "nonsmoker", 0.01, 0.99);

	SetNodeProbs (Bronchitis, "smoker",    0.6, 0.4);
	SetNodeProbs (Bronchitis, "nonsmoker", 0.3, 0.7);

	//                   Tuberculosis Cancer
	SetNodeProbs (TbOrCa, "present", "present", 1.0, 0.0);
	SetNodeProbs (TbOrCa, "present", "absent",  1.0, 0.0);
	SetNodeProbs (TbOrCa, "absent",  "present", 1.0, 0.0);
	SetNodeProbs (TbOrCa, "absent",  "absent",  0.0, 1.0);

	//                  TbOrCa  Abnormal Normal
	SetNodeProbs (XRay, "true",  0.98,  0.02);
	SetNodeProbs (XRay, "false", 0.05,  0.95);

	//                     TbOrCa   Bronchitis 
	SetNodeProbs (Dyspnea, "true",  "present", 0.9, 0.1);
	SetNodeProbs (Dyspnea, "true",  "absent",  0.7, 0.3);
	SetNodeProbs (Dyspnea, "false", "present", 0.8, 0.2);
	SetNodeProbs (Dyspnea, "false", "absent",  0.1, 0.9);

	CHKERR

	WriteNet_bn (net,  NewFileStream_ns ("Data Files/ChestClinic.dne", env, NULL));
	CHKERR

end:
	DeleteNet_bn (net);
	res = CloseNetica_bn (env, mesg);
	printf ("%s\n", mesg);
	printf ("Press <enter> key to quit ", mesg);
	getchar();
	return (res < 0 ? -1 : 0);

error:
	err = GetError_ns (env, ERROR_ERR, NULL);
	fprintf (stderr, "BuildNet: Error %d %s\n", 
	         ErrorNumber_ns (err), ErrorMessage_ns (err));
	goto end;
}

