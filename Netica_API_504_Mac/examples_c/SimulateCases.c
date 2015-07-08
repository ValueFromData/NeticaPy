/* 
 *  SmulateCases.c
 *
 *  Example use of Netica-C API for generating random cases that follow
 *  the probability distribution given by a Bayes net.
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
	net_bn *orig_net = NULL;
	const nodelist_bn* orig_nodes;
	const int numcases = 200;
	stream_ns* casefile = NULL;
	char mesg[MESG_LEN_ns];
	int i, res;
	report_ns* err;

	env = NewNeticaEnviron_ns (NULL, NULL, NULL);
	res = InitNetica2_bn (env, mesg);
	printf ("%s\n", mesg);
	if (res < 0)  exit (-1);
	
	// Read in the net created by the BuildNet.c example program
	orig_net = ReadNet_bn ( NewFileStream_ns ("Data Files/ChestClinic.dne", env, NULL), NO_VISUAL_INFO);
	orig_nodes = GetNetNodes_bn (orig_net);
	SetNetAutoUpdate_bn (orig_net, 0);
	CHKERR

	remove ("Data Files/ChestClinic.cas");  // since it may exist from a previous run and we do not wish to append
	casefile =  NewFileStream_ns ("Data Files/ChestClinic.cas", env, NULL);
	for (i = 0;  i < numcases;  ++i){
		RetractNetFindings_bn (orig_net);
		res= GenerateRandomCase_bn (orig_nodes, 0, 20, NULL);
		if (res >= 0)
			WriteNetFindings_bn (orig_nodes, casefile, i, -1);
		CHKERR
	}
	
end:
	DeleteStream_ns (casefile);
	DeleteNet_bn (orig_net);
	res= CloseNetica_bn (env, mesg);
	printf ("%s\n", mesg);
	printf ("Press <enter> key to quit ", mesg);
	getchar();
	return (res < 0 ? -1 : 0);

error:
	err = GetError_ns (env, ERROR_ERR, NULL);
	fprintf (stderr, "SimulateCases: Error %d %s\n", 
	         ErrorNumber_ns (err), ErrorMessage_ns (err));
	goto end;
}
