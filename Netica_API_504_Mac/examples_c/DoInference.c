/* 
 *  DoInference.c
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
	double belief;
	char mesg[MESG_LEN_ns];
	int res;
	report_ns* err;
	
	env = NewNeticaEnviron_ns (NULL, NULL, NULL);
	res = InitNetica2_bn (env, mesg);
	printf ("%s\n", mesg);
	if (res < 0)  exit (-1);
	
	net = ReadNet_bn ( NewFileStream_ns ("Data Files/ChestClinic.dne", env, NULL), NO_VISUAL_INFO);
	CHKERR

	CompileNet_bn (net);

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

end:
	DeleteNet_bn (net);
	res = CloseNetica_bn (env, mesg);
	printf ("%s\n", mesg);
	printf ("Press <enter> key to quit ", mesg);
	getchar();
	return (res < 0 ? -1 : 0);

error:
	err = GetError_ns (env, ERROR_ERR, NULL);
	fprintf (stderr, "DoInference: Error %d %s\n", 
	         ErrorNumber_ns (err), ErrorMessage_ns (err));
	goto end;
}
