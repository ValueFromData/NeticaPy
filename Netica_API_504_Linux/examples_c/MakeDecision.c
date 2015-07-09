/* 
 *  MakeDecision.c
 *
 *  Example use of Netica-C API to build a decision net and choose an
 *  optimal decision with it.
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
    node_bn *weather, *forecast, *umbrella, *satisfaction;
    state_bn fs, decision;
    const util_bn* utils;
    char mesg[MESG_LEN_ns];
    int res;
   	report_ns* err;

    env = NewNeticaEnviron_ns (NULL, NULL, NULL);
    res = InitNetica2_bn (env, mesg);
    printf ("%s\n", mesg);
    if (res < 0)  exit (-1);
    
    net = NewNet_bn ("Umbrella", env);
    CHKERR

    weather  = NewNode_bn ("Weather",  2, net);
    forecast = NewNode_bn ("Forecast", 3, net);
    umbrella = NewNode_bn ("Umbrella", 2, net);
    SetNodeKind_bn (umbrella, DECISION_NODE);
    satisfaction = NewNode_bn ("Satisfaction", 0, net);
    SetNodeKind_bn (satisfaction, UTILITY_NODE);
    CHKERR

    SetNodeStateNames_bn (weather, "sunshine,     rain");
    SetNodeStateNames_bn (forecast,"sunny,        cloudy,   rainy");
    SetNodeStateNames_bn (umbrella,"take_umbrella,dont_take_umbrella");
    CHKERR

    AddLink_bn (weather,  forecast);
    AddLink_bn (forecast, umbrella);
    AddLink_bn (weather,  satisfaction);
    AddLink_bn (umbrella, satisfaction);
    CHKERR
	
    SetNodeProbs (weather, 0.7, 0.3);
    
    //                                  forecast
    //                       weather |  sunny  cloudy rainy
    SetNodeProbs (forecast, "sunshine", 0.7,   0.2,   0.1);
    SetNodeProbs (forecast, "rain",     0.15,  0.25,  0.6);

    //                                   weather     umbrella
    SetNodeFuncReal (satisfaction,  20, "sunshine", "take_umbrella");
    SetNodeFuncReal (satisfaction, 100, "sunshine", "dont_take_umbrella");
    SetNodeFuncReal (satisfaction,  70, "rain",     "take_umbrella");
    SetNodeFuncReal (satisfaction,   0, "rain",     "dont_take_umbrella");
    CHKERR

    CompileNet_bn (net);
	
    //--- 1st type of usage:  To get the expected utilities, given the current findings

    EnterFinding ("Forecast", "sunny", net);
    utils = GetNodeExpectedUtils_bn (umbrella);  // returns expected utilities, given current findings

    printf ("If the forecast is sunny, the expected utility of %s is %f, of %s is %f\n",
	    GetNodeStateName_bn (umbrella, 0), utils[0],
	    GetNodeStateName_bn (umbrella, 1), utils[1]);
    CHKERR
    
    RetractNetFindings_bn (net);
    EnterFinding ("Forecast", "cloudy", net);
    utils = GetNodeExpectedUtils_bn (umbrella);

    printf ("If the forecast is cloudy, the expected utility of %s is %f, of %s is %f\n\n",
	    GetNodeStateName_bn (umbrella, 0), utils[0],
	    GetNodeStateName_bn (umbrella, 1), utils[1]);
    CHKERR


    //--- 2nd type of usage:  To get the optimal decision table

    RetractNetFindings_bn (net);
    GetNodeExpectedUtils_bn (umbrella);   // causes Netica to recompute decision tables, given current findings
                                          // (which in this case are no findings)

    for (fs = 0;  fs < GetNodeNumberStates_bn (forecast);  ++fs){
        decision = GetNodeFuncState_bn (umbrella, &fs);
        printf ("If the forecast is '%s',\tthe best decision is %s.\n",
                GetNodeStateName_bn (forecast, fs),
                GetNodeStateName_bn (umbrella, decision));
    }
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
	fprintf (stderr, "MakeDecision: Error %d %s\n", 
	         ErrorNumber_ns (err), ErrorMessage_ns (err));
	goto end;
}
