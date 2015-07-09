#include <stdio.h>
#include <stdlib.h>
#include "Netica.h"
#include "NeticaEx.h"

#define CHKERR  {if (GetError_ns (env, ERROR_ERR, NULL))  goto error;}

extern environ_ns *env;

int main (void){
    net_bn *net;
    node_bn *UKInterestRates, *EcuRate, *FixedCosts, *UnitCosts, *UnitPrice, *UnitSalesSterling, *UnitSalesEcu, *TotalSales;
    double belief;
    level_bn arr[5];
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
    
    net = NewNet_bn ("forex", env);
    CHKERR
        
    UKInterestRates = NewNode_bn("UKInterestRates", 5, net);
    EcuRate = NewNode_bn("EcuRate", 4, net);
    FixedCosts = NewNode_bn("FixedCosts", 3, net);
    UnitCosts = NewNode_bn("UnitCosts", 6, net);


    UnitPrice = NewNode_bn("UnitPrice", 7, net);
    UnitSalesSterling = NewNode_bn("UnitSalesSterling", 9, net);
    UnitSalesEcu = NewNode_bn("UnitSalesEcu", 7, net);
    TotalSales = NewNode_bn("TotalSales", 3, net);


	SetNodeStateNames_bn(UKInterestRates, "static,uplow,downlow,downhigh,uphigh");
    arr[0]=160;
    arr[1]=165;
    arr[2]=170;
    arr[3]=175;
    arr[4]=176;
    SetNodeLevels_bn(EcuRate, 4,arr );
    
    
	CHKERR
    SetNodeStateNames_bn(EcuRate, "er_160_165,er_165_170,er_170_175,er_175_176");
    SetNodeStateNames_bn(FixedCosts, "s50000,s55000,s60000");
    SetNodeStateNames_bn(UnitCosts, "c10,c11,c12,c13,c14,c15");
    SetNodeStateNames_bn(UnitPrice, "p1600,p1650,p1700,p1750,p1800,p1850,p1900");
    SetNodeStateNames_bn(UnitSalesEcu, "e6000,e7000,e8000,e9000,e10000,e11000,e12000");
    SetNodeStateNames_bn(UnitSalesSterling, "ss10000,ss11000,ss12000,ss13000,ss14000,ss15000,ss16000,ss17000,ss18000");
    
    SetNodeStateNames_bn(TotalSales, "complete,lose5,lose10");
    
    
	CHKERR
    
    AddLink_bn(UKInterestRates, EcuRate);
    AddLink_bn(UKInterestRates, FixedCosts);
    AddLink_bn(EcuRate, UnitCosts);
    AddLink_bn(FixedCosts, UnitCosts);
    
    AddLink_bn(UnitCosts, UnitPrice);
    AddLink_bn(UnitPrice, UnitSalesSterling);
    AddLink_bn(UnitPrice, UnitSalesEcu);
    AddLink_bn(EcuRate, UnitSalesEcu);
    AddLink_bn(UnitSalesEcu, TotalSales);
    AddLink_bn(UnitSalesSterling, TotalSales);
    
	CHKERR
    
    SetNodeProbs (UKInterestRates, 0.10,0.30,0.25,0.25,0.10);
    
    SetNodeProbs (EcuRate,"static",0.17,0.37,0.28,0.18);
    SetNodeProbs (EcuRate,"uplow",0.05,0.15,0.50,0.30);
    SetNodeProbs (EcuRate,"downlow",0.25,0.50,0.15,0.10);
    SetNodeProbs (EcuRate,"downhigh",0.75,0.25,0.00,0.00);
    SetNodeProbs (EcuRate,"uphigh",0.00,0.00,0.25,0.75);
    
	CHKERR
    
    
    SetNodeProbs (FixedCosts,"static",0.25,0.55,0.20);
    SetNodeProbs (FixedCosts,"uplow",0.25,0.50,0.25);
    SetNodeProbs (FixedCosts,"downlow",0.40,0.45,0.15);
    SetNodeProbs (FixedCosts,"downhigh",0.60,0.40,0.00);
    SetNodeProbs (FixedCosts,"uphigh",0.00,0.40,0.60);
    
    
	CHKERR
    
    SetNodeProbs(UnitCosts,"er_160_165","s50000",0.30,0.30,0.20,0.10,0.08,0.02);
    SetNodeProbs(UnitCosts,"er_160_165","s55000",0.20,0.35,0.25,0.10,0.08,0.02);
    SetNodeProbs(UnitCosts,"er_160_165","s60000",0.15,0.40,0.25,0.10,0.08,0.02);
    SetNodeProbs(UnitCosts,"er_165_170","s50000",0.10,0.50,0.20,0.10,0.07,0.03);
    SetNodeProbs(UnitCosts,"er_165_170","s55000",0.05,0.50,0.25,0.10,0.07,0.03);
    SetNodeProbs(UnitCosts,"er_165_170","s60000",0.00,0.40,0.35,0.15,0.07,0.03);
    SetNodeProbs(UnitCosts,"er_170_175","s50000",0.10,0.25,0.30,0.20,0.10,0.05);
    SetNodeProbs(UnitCosts,"er_170_175","s55000",0.05,0.20,0.40,0.25,0.05,0.05);
    SetNodeProbs(UnitCosts,"er_170_175","s60000",0.00,0.15,0.35,0.30,0.15,0.05);
    SetNodeProbs(UnitCosts,"er_175_176","s50000",0.00,0.10,0.15,0.40,0.25,0.10);
    SetNodeProbs(UnitCosts,"er_175_176","s55000",0.00,0.05,0.10,0.30,0.35,0.20);
    SetNodeProbs(UnitCosts,"er_175_176","s60000",0.00,0.00,0.05,0.15,0.50,0.30);
    
    
	CHKERR
    
    

    SetNodeFuncState (UnitPrice,0,"c10");
    SetNodeFuncState (UnitPrice,1,"c11");
    SetNodeFuncState (UnitPrice,2,"c12");
    SetNodeFuncState (UnitPrice,3,"c13");
    SetNodeFuncState (UnitPrice,4,"c14");
    SetNodeFuncState (UnitPrice,5,"c15");
    SetNodeFuncState (UnitPrice,6,"*");
    
    
	CHKERR
    
    SetNodeProbs (UnitSalesSterling, "p1600", 0.0,0.0,0.0,0.0,0.05,0.10,0.20,0.45,0.20);
    
    SetNodeProbs (UnitSalesSterling, "p1650", 0.0,0.0,0.0,0,0.10,0.15,0.35,0.30,0.10);
    SetNodeProbs (UnitSalesSterling, "p1700", 0.0,0.0,0.10,0.15,0.25,0.30,0.10,0.10,0.0);
    SetNodeProbs (UnitSalesSterling, "p1750", 0.0,0.05,0.15,0.40,0.20,0.10,0.5,0.05,0.0);
    SetNodeProbs (UnitSalesSterling, "p1800", 0.0,0.20,0.40,0.25,0.10,0.05,0.0,0.0,0.0);
    SetNodeProbs (UnitSalesSterling, "p1850", 0.15,0.35,0.20,0.20,0.05,0.05,0.0,0.0,0.0);
    
    
	CHKERR
    
    SetNodeProbs(UnitSalesEcu,"p1600","er_160_165",0.00,0.00,0.00,0.00,0.20,0.30,0.50);


	CHKERR

    SetNodeProbs(UnitSalesEcu,"p1600","er_165_170",0.00,0.00,0.00,0.10,0.15,0.35,0.40);
    SetNodeProbs(UnitSalesEcu,"p1600","er_170_175",0.0,0.0,0.05,0.15,0.15,0.30,0.35);
    SetNodeProbs(UnitSalesEcu,"p1600","er_175_176",0.0,0.0,0.05,0.20,0.25,0.30,0.20);
    SetNodeProbs(UnitSalesEcu,"p1650","er_160_165",0.0,0.0,0.10,0.25,0.30,0.20,0.15);
    SetNodeProbs(UnitSalesEcu,"p1650","er_165_170",0.0,0.05,0.15,0.20,0.30,0.20,0.10);
    SetNodeProbs(UnitSalesEcu,"p1650","er_170_175",0.05,0.10,0.20,0.30,0.15,0.10,0.10);
    SetNodeProbs(UnitSalesEcu,"p1650","er_175_176",0.10,0.15,0.25,0.20,0.15,0.10,0.05);
    SetNodeProbs(UnitSalesEcu,"p1700","er_160_165",0.15,0.20,0.25,0.20,0.10,0.07,0.03);
    SetNodeProbs(UnitSalesEcu,"p1700","er_165_170",0.20,0.20,0.25,0.15,0.10,0.05,0.05);
    SetNodeProbs(UnitSalesEcu,"p1700","er_170_175",0.25,0.20,0.20,0.15,0.10,0.05,0.05);
    SetNodeProbs(UnitSalesEcu,"p1700","er_175_176",0.30,0.25,0.20,0.15,0.05,0.05,0.0);
    SetNodeProbs(UnitSalesEcu,"p1750","er_160_165",0.30,0.30,0.20,0.10,0.05,0.05,0.0);
    SetNodeProbs(UnitSalesEcu,"p1750","er_165_170",0.35,0.30,0.20,0.10,0.05,0.0,0.0);
    SetNodeProbs(UnitSalesEcu,"p1750","er_170_175",0.40,0.35,0.15,0.05,0.05,0.0,0.0);
    SetNodeProbs(UnitSalesEcu,"p1750","er_175_176",0.45,0.40,0.10,0.05,0.0,0.0,0.0);
    SetNodeProbs(UnitSalesEcu,"p1800","er_160_165",0.45,0.40,0.10,0.05,0.0,0.0,0.0);
    SetNodeProbs(UnitSalesEcu,"p1800","er_165_170",0.50,0.40,0.05,0.05,0.0,0.0,0.0);
    SetNodeProbs(UnitSalesEcu,"p1800","er_170_175",0.55,0.40,0.05,0.0,0.0,0.0,0.0);
    SetNodeProbs(UnitSalesEcu,"p1800","er_175_176",0.60,0.40,0.0,0.0,0.0,0.0,0.0);
    SetNodeProbs(UnitSalesEcu,"p1850","er_160_165",0.60,0.40,0.0,0.0,0.0,0.0,0.0);
    SetNodeProbs(UnitSalesEcu,"p1850","er_165_170",0.65,0.35,0.0,0.0,0.0,0.0,0.0);
    SetNodeProbs(UnitSalesEcu,"p1850","er_170_175",0.70,0.30,0.0,0.0,0.0,0.0,0.0);
    SetNodeProbs(UnitSalesEcu,"p1850","er_175_176",0.75,0.25,0.0,0.0,0.0,0.0,0.0);
    SetNodeProbs(UnitSalesEcu,"p1900","er_160_165",0.75,0.25,0.0,0.0,0.0,0.0,0.0);
    SetNodeProbs(UnitSalesEcu,"p1900","er_165_170",0.80,0.20,0.0,0.0,0.0,0.0,0.0);
    SetNodeProbs(UnitSalesEcu,"p1900","er_170_175",0.85,0.15,0.0,0.0,0.0,0.0,0.0);
    SetNodeProbs(UnitSalesEcu,"p1900","er_175_176",0.90,0.10,0.0,0.0,0.0,0.0,0.0);
    
    

	CHKERR



SetNodeFuncState(TotalSales,0,"ss10000","e6000");
SetNodeFuncState(TotalSales,0,"ss10000","e7000");
SetNodeFuncState(TotalSales,0,"ss10000","e8000");
SetNodeFuncState(TotalSales,0,"ss10000","e9000");
SetNodeFuncState(TotalSales,1,"ss10000","e10000");
SetNodeFuncState(TotalSales,1,"ss10000","e11000");
SetNodeFuncState(TotalSales,1,"ss10000","e12000");
SetNodeFuncState(TotalSales,0,"ss11000","e6000");
SetNodeFuncState(TotalSales,0,"ss11000","e7000");
SetNodeFuncState(TotalSales,0,"ss11000","e8000");
SetNodeFuncState(TotalSales,1,"ss11000","e9000");
SetNodeFuncState(TotalSales,1,"ss11000","e10000");
SetNodeFuncState(TotalSales,1,"ss11000","e11000");
SetNodeFuncState(TotalSales,1,"ss11000","e12000");
SetNodeFuncState(TotalSales,0,"ss12000","e6000");
SetNodeFuncState(TotalSales,0,"ss12000","e7000");
SetNodeFuncState(TotalSales,1,"ss12000","e8000");
SetNodeFuncState(TotalSales,1,"ss12000","e9000");
SetNodeFuncState(TotalSales,1,"ss12000","e10000");
SetNodeFuncState(TotalSales,1,"ss12000","e11000");
SetNodeFuncState(TotalSales,1,"ss12000","e12000");
SetNodeFuncState(TotalSales,0,"ss13000","e6000");
SetNodeFuncState(TotalSales,1,"ss13000","e7000");
SetNodeFuncState(TotalSales,1,"ss13000","e8000");
SetNodeFuncState(TotalSales,1,"ss13000","e9000");
SetNodeFuncState(TotalSales,1,"ss13000","e10000");
SetNodeFuncState(TotalSales,1,"ss13000","e11000");
SetNodeFuncState(TotalSales,1,"ss13000","e12000");
SetNodeFuncState(TotalSales,1,"ss14000","e6000");
SetNodeFuncState(TotalSales,1,"ss14000","e7000");
SetNodeFuncState(TotalSales,1,"ss14000","e8000");
SetNodeFuncState(TotalSales,1,"ss14000","e9000");
SetNodeFuncState(TotalSales,1,"ss14000","e10000");
SetNodeFuncState(TotalSales,1,"ss14000","e11000");
SetNodeFuncState(TotalSales,1,"ss14000","e12000");
SetNodeFuncState(TotalSales,1,"ss15000","e6000");
SetNodeFuncState(TotalSales,1,"ss15000","e7000");
SetNodeFuncState(TotalSales,1,"ss15000","e8000");
SetNodeFuncState(TotalSales,1,"ss15000","e9000");
SetNodeFuncState(TotalSales,1,"ss15000","e10000");
SetNodeFuncState(TotalSales,1,"ss15000","e11000");
SetNodeFuncState(TotalSales,1,"ss15000","e12000");
SetNodeFuncState(TotalSales,1,"ss16000","e6000");
SetNodeFuncState(TotalSales,1,"ss16000","e7000");
SetNodeFuncState(TotalSales,1,"ss16000","e8000");
SetNodeFuncState(TotalSales,1,"ss16000","e9000");
SetNodeFuncState(TotalSales,1,"ss16000","e10000");
SetNodeFuncState(TotalSales,1,"ss16000","e11000");
SetNodeFuncState(TotalSales,2,"ss16000","e12000");
SetNodeFuncState(TotalSales,1,"ss17000","e6000");
SetNodeFuncState(TotalSales,1,"ss17000","e7000");
SetNodeFuncState(TotalSales,1,"ss17000","e8000");
SetNodeFuncState(TotalSales,1,"ss17000","e9000");
SetNodeFuncState(TotalSales,1,"ss17000","e10000");
SetNodeFuncState(TotalSales,2,"ss17000","e11000");
SetNodeFuncState(TotalSales,2,"ss17000","e12000");
SetNodeFuncState(TotalSales,1,"ss18000","e6000");
SetNodeFuncState(TotalSales,1,"ss18000","e7000");
SetNodeFuncState(TotalSales,1,"ss18000","e8000");
SetNodeFuncState(TotalSales,1,"ss18000","e9000");
SetNodeFuncState(TotalSales,2,"ss18000","e10000");
SetNodeFuncState(TotalSales,2,"ss18000","e11000");
SetNodeFuncState(TotalSales,2,"ss18000","e12000");






	CHKERR

	CompileNet_bn (net);
	CHKERR

	belief = GetNodeBelief("TotalSales", "complete", net);
	CHKERR

	
end:
	DeleteNet_bn (net);
	res = CloseNetica_bn (env, mesg);
	printf ("%s\n", mesg);
	printf ("Press <enter> key to quit ");
	getchar();
	return (res < 0) ? -1 : 0;

error:
	fprintf (stderr, "NeticaDemo: Error in %s\n", 	         ErrorMessage_ns (GetError_ns (env, ERROR_ERR, NULL)));
	goto end;
}


