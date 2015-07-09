from NeticaPy import Netica
import os


BASE_DIR = os.getcwd()

N = Netica()


mesg = bytearray()
env = N.NewNeticaEnviron_ns("", None, "")
res = N.InitNetica2_bn (env, mesg)

print mesg

# initializing the network with environment
bayesian_network = N.NewNet_bn ("ForExConsideration", env)

# create each node in the network
UKInterestRates = N.NewNode_bn("UKInterestRates", 5, bayesian_network)
EcuRate = N.NewNode_bn("EcuRate", 4, bayesian_network)
FixedCosts = N.NewNode_bn("FixedCosts", 3, bayesian_network)
UnitCosts = N.NewNode_bn("UnitCosts", 6, bayesian_network)


UnitPrice = N.NewNode_bn("UnitPrice", 6, bayesian_network)
UnitSalesSterling = N.NewNode_bn("UnitSalesSterling", 9, bayesian_network)
UnitSalesEcu = N.NewNode_bn("UnitSalesEcu", 7, bayesian_network)
TotalSales = N.NewNode_bn("TotalSales", 3, bayesian_network)



# setting node levels for the contiuous variables that have been made discrete
N.SetNodeStateNames_bn(UKInterestRates, "static,uplow,downlow,downhigh,uphigh")

N.SetNodeLevels_bn(EcuRate, 4, [160,165,170,175,176])


N.SetNodeStateNames_bn(EcuRate, "er_160_165,er_165_170,er_170_175,er_175_176")
N.SetNodeStateNames_bn(FixedCosts, "s50000,s55000,s60000")
N.SetNodeStateNames_bn(UnitCosts, "c10,c11,c12,c13,c14,c15")
N.SetNodeStateNames_bn(UnitPrice, "p1600,p1650,p1700,p1750,p1800,p1850")
N.SetNodeStateNames_bn(UnitSalesEcu, "e6000,e7000,e8000,e9000,e10000,e11000,e12000")
N.SetNodeStateNames_bn(UnitSalesSterling, "ss10000,ss11000,ss12000,ss13000,ss14000,ss15000,ss16000,ss17000,ss18000")

N.SetNodeStateNames_bn(TotalSales, "complete,lose5,lose10")


# adding links between nodes
N.AddLink_bn(UKInterestRates, EcuRate)
N.AddLink_bn(UKInterestRates, FixedCosts)
N.AddLink_bn(EcuRate, UnitCosts)
N.AddLink_bn(FixedCosts, UnitCosts)

N.AddLink_bn(UnitCosts, UnitPrice)
N.AddLink_bn(UnitPrice, UnitSalesSterling)
N.AddLink_bn(UnitPrice, UnitSalesEcu)
N.AddLink_bn(EcuRate, UnitSalesEcu)
N.AddLink_bn(UnitSalesEcu, TotalSales)
N.AddLink_bn(UnitSalesSterling, TotalSales)

# setting the probabilities for each top level node
N.SetNodeProbs (UKInterestRates, 0.10,0.30,0.25,0.25,0.10)

N.SetNodeProbs (EcuRate,"static",0.17,0.37,0.28,0.18)
N.SetNodeProbs (EcuRate,"uplow",0.05,0.15,0.50,0.30)
N.SetNodeProbs (EcuRate,"downlow",0.25,0.50,0.15,0.10)
N.SetNodeProbs (EcuRate,"downhigh",0.75,0.25,0.00,0.00)
N.SetNodeProbs (EcuRate,"uphigh",0.00,0.00,0.25,0.75)



N.SetNodeProbs (FixedCosts,'static',0.25,0.55,0.20)
N.SetNodeProbs (FixedCosts,'uplow',0.25,0.50,0.25)
N.SetNodeProbs (FixedCosts,'downlow',0.40,0.45,0.15)
N.SetNodeProbs (FixedCosts,'downhigh',0.60,0.40,0.00)
N.SetNodeProbs (FixedCosts,'uphigh',0.00,0.40,0.60)



N.SetNodeProbs(UnitCosts,'er_160_165','s50000',0.30,0.30,0.20,0.10,0.08,0.02)
N.SetNodeProbs(UnitCosts,'er_160_165','s55000',0.20,0.35,0.25,0.10,0.08,0.02)
N.SetNodeProbs(UnitCosts,'er_160_165','s60000',0.15,0.40,0.25,0.10,0.08,0.02)
N.SetNodeProbs(UnitCosts,'er_165_170','s50000',0.10,0.50,0.20,0.10,0.07,0.03)
N.SetNodeProbs(UnitCosts,'er_165_170','s55000',0.05,0.50,0.25,0.10,0.07,0.03)
N.SetNodeProbs(UnitCosts,'er_165_170','s60000',0.00,0.40,0.35,0.15,0.07,0.03)
N.SetNodeProbs(UnitCosts,'er_170_175','s50000',0.10,0.25,0.30,0.20,0.10,0.05)
N.SetNodeProbs(UnitCosts,'er_170_175','s55000',0.05,0.20,0.40,0.25,0.05,0.05)
N.SetNodeProbs(UnitCosts,'er_170_175','s60000',0.00,0.15,0.35,0.30,0.15,0.05)
N.SetNodeProbs(UnitCosts,'er_175_176','s50000',0.00,0.10,0.15,0.40,0.25,0.10)
N.SetNodeProbs(UnitCosts,'er_175_176','s55000',0.00,0.05,0.10,0.30,0.35,0.20)
N.SetNodeProbs(UnitCosts,'er_175_176','s60000',0.00,0.00,0.05,0.15,0.50,0.30)





N.SetNodeFuncState (UnitPrice,0,"c10")
N.SetNodeFuncState (UnitPrice,1,"c11")
N.SetNodeFuncState (UnitPrice,2,"c12")
N.SetNodeFuncState (UnitPrice,3,"c13")
N.SetNodeFuncState (UnitPrice,4,"c14")
N.SetNodeFuncState (UnitPrice,5,"c15")






print N.ErrorMessage_ns(N.GetError_ns(N, 5, 0))
print 1


N.SetNodeProbs (UnitSalesSterling, "p1600", 0.0,0.0,0.0,0.0,0.05,0.10,0.20,0.45,0.20)
print N.ErrorMessage_ns(N.GetError_ns(N, 5, 0))
N.SetNodeProbs (UnitSalesSterling, "p1650", 0.0,0.0,0.0,0,0.10,0.15,0.35,0.30,0.10)
N.SetNodeProbs (UnitSalesSterling, "p1700", 0.0,0.0,0.10,0.15,0.25,0.30,0.10,0.10,0.0)
N.SetNodeProbs (UnitSalesSterling, "p1750", 0.0,0.05,0.15,0.40,0.20,0.10,0.5,0.05,0.0)
N.SetNodeProbs (UnitSalesSterling, "p1800", 0.0,0.20,0.40,0.25,0.10,0.05,0.0,0.0,0.0)
N.SetNodeProbs (UnitSalesSterling, "p1850", 0.15,0.35,0.20,0.20,0.05,0.05,0.0,0.0,0.0)
#N.SetNodeProbs (UnitSalesSterling, "p1900", 0.35,0.40,0.20,0.05,0.0,0.0,0.0,0.0,0.0)










print N.ErrorMessage_ns(N.GetError_ns(N, 5, 0))
print 1



N.SetNodeProbs(UnitSalesEcu,'p1600','er_160_165',0.00,0.00,0.00,0.00,0.20,0.30,0.50)


print N.ErrorMessage_ns(N.GetError_ns(N, 5, 0))
print 2


N.SetNodeProbs(UnitSalesEcu,'p1600','er_165_170',0.00,0.00,0.00,0.10,0.15,0.35,0.40)
N.SetNodeProbs(UnitSalesEcu,'p1600','er_170_175',0.0,0.0,0.05,0.15,0.15,0.30,0.35)
N.SetNodeProbs(UnitSalesEcu,'p1600','er_175_176',0.0,0.0,0.05,0.20,0.25,0.30,0.20)
N.SetNodeProbs(UnitSalesEcu,'p1650','er_160_165',0.0,0.0,0.10,0.25,0.30,0.20,0.15)
N.SetNodeProbs(UnitSalesEcu,'p1650','er_165_170',0.0,0.05,0.15,0.20,0.30,0.20,0.10)
N.SetNodeProbs(UnitSalesEcu,'p1650','er_170_175',0.05,0.10,0.20,0.30,0.15,0.10,0.10)
N.SetNodeProbs(UnitSalesEcu,'p1650','er_175_176',0.10,0.15,0.25,0.20,0.15,0.10,0.05)
N.SetNodeProbs(UnitSalesEcu,'p1700','er_160_165',0.15,0.20,0.25,0.20,0.10,0.07,0.03)
N.SetNodeProbs(UnitSalesEcu,'p1700','er_165_170',0.20,0.20,0.25,0.15,0.10,0.05,0.05)
N.SetNodeProbs(UnitSalesEcu,'p1700','er_170_175',0.25,0.20,0.20,0.15,0.10,0.05,0.05)
N.SetNodeProbs(UnitSalesEcu,'p1700','er_175_176',0.30,0.25,0.20,0.15,0.05,0.05,0.0)
N.SetNodeProbs(UnitSalesEcu,'p1750','er_160_165',0.30,0.30,0.20,0.10,0.05,0.05,0.0)
N.SetNodeProbs(UnitSalesEcu,'p1750','er_165_170',0.35,0.30,0.20,0.10,0.05,0.0,0.0)
N.SetNodeProbs(UnitSalesEcu,'p1750','er_170_175',0.40,0.35,0.15,0.05,0.05,0.0,0.0)
N.SetNodeProbs(UnitSalesEcu,'p1750','er_175_176',0.45,0.40,0.10,0.05,0.0,0.0,0.0)
N.SetNodeProbs(UnitSalesEcu,'p1800','er_160_165',0.45,0.40,0.10,0.05,0.0,0.0,0.0)
N.SetNodeProbs(UnitSalesEcu,'p1800','er_165_170',0.50,0.40,0.05,0.05,0.0,0.0,0.0)
N.SetNodeProbs(UnitSalesEcu,'p1800','er_170_175',0.55,0.40,0.05,0.0,0.0,0.0,0.0)
N.SetNodeProbs(UnitSalesEcu,'p1800','er_175_176',0.60,0.40,0.0,0.0,0.0,0.0,0.0)
N.SetNodeProbs(UnitSalesEcu,'p1850','er_160_165',0.60,0.40,0.0,0.0,0.0,0.0,0.0)
N.SetNodeProbs(UnitSalesEcu,'p1850','er_165_170',0.65,0.35,0.0,0.0,0.0,0.0,0.0)
N.SetNodeProbs(UnitSalesEcu,'p1850','er_170_175',0.70,0.30,0.0,0.0,0.0,0.0,0.0)
N.SetNodeProbs(UnitSalesEcu,'p1850','er_175_176',0.75,0.25,0.0,0.0,0.0,0.0,0.0)
#N.SetNodeProbs(UnitSalesEcu,'p1900','er_160_165',0.75,0.25,0.0,0.0,0.0,0.0,0.0)
#N.SetNodeProbs(UnitSalesEcu,'p1900','er_165_170',0.80,0.20,0.0,0.0,0.0,0.0,0.0)
#N.SetNodeProbs(UnitSalesEcu,'p1900','er_170_175',0.85,0.15,0.0,0.0,0.0,0.0,0.0)
#N.SetNodeProbs(UnitSalesEcu,'p1900','er_175_176',0.90,0.10,0.0,0.0,0.0,0.0,0.0)

















N.SetNodeFuncState(TotalSales,0,'ss10000','e6000')
N.SetNodeFuncState(TotalSales,0,'ss10000','e7000')
N.SetNodeFuncState(TotalSales,0,'ss10000','e8000')
N.SetNodeFuncState(TotalSales,0,'ss10000','e9000')
N.SetNodeFuncState(TotalSales,1,'ss10000','e10000')
N.SetNodeFuncState(TotalSales,1,'ss10000','e11000')
N.SetNodeFuncState(TotalSales,1,'ss10000','e12000')
N.SetNodeFuncState(TotalSales,0,'ss11000','e6000')
N.SetNodeFuncState(TotalSales,0,'ss11000','e7000')
N.SetNodeFuncState(TotalSales,0,'ss11000','e8000')
N.SetNodeFuncState(TotalSales,1,'ss11000','e9000')
N.SetNodeFuncState(TotalSales,1,'ss11000','e10000')
N.SetNodeFuncState(TotalSales,1,'ss11000','e11000')
N.SetNodeFuncState(TotalSales,1,'ss11000','e12000')
N.SetNodeFuncState(TotalSales,0,'ss12000','e6000')
N.SetNodeFuncState(TotalSales,0,'ss12000','e7000')
N.SetNodeFuncState(TotalSales,1,'ss12000','e8000')
N.SetNodeFuncState(TotalSales,1,'ss12000','e9000')
N.SetNodeFuncState(TotalSales,1,'ss12000','e10000')
N.SetNodeFuncState(TotalSales,1,'ss12000','e11000')
N.SetNodeFuncState(TotalSales,1,'ss12000','e12000')
N.SetNodeFuncState(TotalSales,0,'ss13000','e6000')
N.SetNodeFuncState(TotalSales,1,'ss13000','e7000')
N.SetNodeFuncState(TotalSales,1,'ss13000','e8000')
N.SetNodeFuncState(TotalSales,1,'ss13000','e9000')
N.SetNodeFuncState(TotalSales,1,'ss13000','e10000')
N.SetNodeFuncState(TotalSales,1,'ss13000','e11000')
N.SetNodeFuncState(TotalSales,1,'ss13000','e12000')
N.SetNodeFuncState(TotalSales,1,'ss14000','e6000')
N.SetNodeFuncState(TotalSales,1,'ss14000','e7000')
N.SetNodeFuncState(TotalSales,1,'ss14000','e8000')
N.SetNodeFuncState(TotalSales,1,'ss14000','e9000')
N.SetNodeFuncState(TotalSales,1,'ss14000','e10000')
N.SetNodeFuncState(TotalSales,1,'ss14000','e11000')
N.SetNodeFuncState(TotalSales,1,'ss14000','e12000')
N.SetNodeFuncState(TotalSales,1,'ss15000','e6000')
N.SetNodeFuncState(TotalSales,1,'ss15000','e7000')
N.SetNodeFuncState(TotalSales,1,'ss15000','e8000')
N.SetNodeFuncState(TotalSales,1,'ss15000','e9000')
N.SetNodeFuncState(TotalSales,1,'ss15000','e10000')
N.SetNodeFuncState(TotalSales,1,'ss15000','e11000')
N.SetNodeFuncState(TotalSales,1,'ss15000','e12000')
N.SetNodeFuncState(TotalSales,1,'ss16000','e6000')
N.SetNodeFuncState(TotalSales,1,'ss16000','e7000')
N.SetNodeFuncState(TotalSales,1,'ss16000','e8000')
N.SetNodeFuncState(TotalSales,1,'ss16000','e9000')
N.SetNodeFuncState(TotalSales,1,'ss16000','e10000')
N.SetNodeFuncState(TotalSales,1,'ss16000','e11000')
N.SetNodeFuncState(TotalSales,2,'ss16000','e12000')
N.SetNodeFuncState(TotalSales,1,'ss17000','e6000')
N.SetNodeFuncState(TotalSales,1,'ss17000','e7000')
N.SetNodeFuncState(TotalSales,1,'ss17000','e8000')
N.SetNodeFuncState(TotalSales,1,'ss17000','e9000')
N.SetNodeFuncState(TotalSales,1,'ss17000','e10000')
N.SetNodeFuncState(TotalSales,2,'ss17000','e11000')
N.SetNodeFuncState(TotalSales,2,'ss17000','e12000')
N.SetNodeFuncState(TotalSales,1,'ss18000','e6000')
N.SetNodeFuncState(TotalSales,1,'ss18000','e7000')
N.SetNodeFuncState(TotalSales,1,'ss18000','e8000')
N.SetNodeFuncState(TotalSales,1,'ss18000','e9000')
N.SetNodeFuncState(TotalSales,2,'ss18000','e10000')
N.SetNodeFuncState(TotalSales,2,'ss18000','e11000')
N.SetNodeFuncState(TotalSales,2,'ss18000','e12000')






## set the node function for the Population Outcome
#N.SetNodeFuncState(PopulationOutcome, 2,"A",'strong')
#N.SetNodeFuncState(PopulationOutcome, 1,"A",'medium')
#N.SetNodeFuncState(PopulationOutcome, 0,"A",'weak')
#N.SetNodeFuncState(PopulationOutcome, 3,"B",'strong')
#N.SetNodeFuncState(PopulationOutcome, 2,"B",'medium')
#N.SetNodeFuncState(PopulationOutcome, 1,"B",'weak')
#N.SetNodeFuncState(PopulationOutcome, 4,"C",'strong')
#N.SetNodeFuncState(PopulationOutcome, 3,"C",'medium')
#N.SetNodeFuncState(PopulationOutcome, 2,"C",'weak')
#N.SetNodeFuncState(PopulationOutcome, 4,"D",'strong')
#N.SetNodeFuncState(PopulationOutcome, 4,"D",'medium')
#N.SetNodeFuncState(PopulationOutcome, 3,"D",'weak')
#N.SetNodeFuncState(PopulationOutcome, 4,"E",'strong')
#N.SetNodeFuncState(PopulationOutcome, 4,"E",'medium')
#N.SetNodeFuncState(PopulationOutcome, 4,"E",'weak')




# print the error message in case of any errors within Netica
print N.ErrorMessage_ns(N.GetError_ns(N, 5, 0))

# compile the final network
N.CompileNet_bn (bayesian_network)            

# get the belief for each state for PopulationOutcome
belief = N.GetNodeBelief ("TotalSales", "complete", bayesian_network)
print """The probability is %g"""% belief

#belief = N.GetNodeBelief ("PopulationOutcome", "B", bayesian_network)
#print """The probability is %g"""% belief
#
#belief = N.GetNodeBelief ("PopulationOutcome", "C", bayesian_network)
#print """The probability is %g"""% belief
#
#belief = N.GetNodeBelief ("PopulationOutcome", "D", bayesian_network)
#print """The probability is %g"""% belief
#
#belief = N.GetNodeBelief ("PopulationOutcome", "E", bayesian_network)
#print """The probability is %g"""% belief

# delete the network and print the returned message
N.DeleteNet_bn (bayesian_network)
res = N.CloseNetica_bn (env, mesg)

print mesg
