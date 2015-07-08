/* 
 *  ClassifyData.c
 *
 *  Example use of Netica-C API for doing Naive Bayesian Classification.
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
	const nodelist_bn *nodes;
	net_bn  *net = NULL;
	node_bn *Malignancy, *ClumpThickness, *UniformityOfCellSize;
	node_bn *UniformityOfCellShape, *MarginalAdhesion, *SingleEpithelialCellSize;
	node_bn *BareNuclei, *BlandChromatin, *NormalNucleoli, *Mitoses;
	char mesg[MESG_LEN_ns];
	int res, i;
	report_ns* err;
	double belief;
	
	env = NewNeticaEnviron_ns (NULL, NULL, NULL);
	res = InitNetica2_bn (env, mesg);
	printf ("%s\n", mesg);
	if (res < 0)  exit (-1);
	CHKERR

	net = ReadNet_bn (NewFileStream_ns ("Data Files/BreastCancer.dne", env, NULL), NO_VISUAL_INFO);

	Malignancy               = NodeNamed_bn ("Malignancy", net);
	ClumpThickness           = NodeNamed_bn ("ClumpThickness", net);
	UniformityOfCellSize     = NodeNamed_bn ("UniformityOfCellSize", net);
	UniformityOfCellShape    = NodeNamed_bn ("UniformityOfCellShape", net);
	MarginalAdhesion         = NodeNamed_bn ("MarginalAdhesion", net);
	SingleEpithelialCellSize = NodeNamed_bn ("SingleEpithelialCellSize", net);
	BareNuclei               = NodeNamed_bn ("BareNuclei", net);
	BlandChromatin           = NodeNamed_bn ("BlandChromatin", net);
	NormalNucleoli           = NodeNamed_bn ("NormalNucleoli", net);
	Mitoses                  = NodeNamed_bn ("Mitoses", net);

	//-- Clear any CPT data
	nodes = GetNetNodes_bn (net);
	for (i = 0;  i < LengthNodeList_bn (nodes);  ++i){
		DeleteNodeTables_bn (NthNode_bn (nodes, i));
	}

	//-- Train net based on database of Wisconsin breast cancer study
	ReviseCPTsByCaseFile_bn (NewFileStream_ns ("Data Files/BreastCancer.cas", env, NULL), 
	                         nodes, 0, 1.0);

	//-- Now perform a classification for a particular case:  10,3,3,2,2,10,4,1,2

	EnterNodeValue_bn (ClumpThickness, 10.0);
	EnterNodeValue_bn (ClumpThickness, 10.0);
	EnterNodeValue_bn (UniformityOfCellSize, 3.0);
	EnterNodeValue_bn (UniformityOfCellShape, 3.0);
	EnterNodeValue_bn (MarginalAdhesion, 2.0);
	EnterNodeValue_bn (SingleEpithelialCellSize, 2.0);
	EnterNodeValue_bn (BareNuclei, 10.0);
	EnterNodeValue_bn (BlandChromatin, 4.0);
	EnterNodeValue_bn (NormalNucleoli, 1.0);
	EnterNodeValue_bn (Mitoses, 2.0);
	CHKERR

	CompileNet_bn (net);
	CHKERR

	belief = GetNodeBelief ("Malignancy", "Malignant", net);
	printf ("\nThe probability of this cell being malignant is %g\n\n", belief);
	CHKERR
	
end:
	DeleteNet_bn (net);
	res= CloseNetica_bn (env, mesg);
	printf ("%s\n", mesg);
	printf ("Press <enter> key to quit ", mesg);
	getchar();
	return (res < 0 ? -1 : 0);

error:
	err = GetError_ns (env, ERROR_ERR, NULL);
	fprintf (stderr, "ClassifyData: Error %d %s\n", 
	         ErrorNumber_ns (err), ErrorMessage_ns (err));
	goto end;
}
