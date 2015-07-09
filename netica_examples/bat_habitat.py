from NeticaPy import Netica
import os


BASE_DIR = os.getcwd()

N = Netica()

INFINITY_ns = N.GetInfinityDbl_ns()
mesg = bytearray()
env = N.NewNeticaEnviron_ns("", None, "")
res = N.InitNetica2_bn (env, mesg)

print mesg

# initializing the network with environment
bayesian_network = N.NewNet_bn ("BatHabitatBasinscale", env)

# create each node in the network
RangeExpansionContraction = N.NewNode_bn("RangeExpansionContraction", 5, bayesian_network)
Connectivity = N.NewNode_bn("Connectivity", 5, bayesian_network)
EnvIndexRelHistorical = N.NewNode_bn("EnvIndexRelHistorical", 5, bayesian_network)
OtherOrganisms = N.NewNode_bn("OtherOrganisms", 2, bayesian_network)
PopulationSizeEffect = N.NewNode_bn("PopulationSizeEffect", 2, bayesian_network)
EnvironmentalOutcome = N.NewNode_bn("EnvironmentalOutcome", 5, bayesian_network)
NonHabitatInfluences = N.NewNode_bn("NonHabitatInfluences", 3, bayesian_network)
PopulationOutcome = N.NewNode_bn("PopulationOutcome", 5, bayesian_network)



# setting node levels for the contiuous variables that have been made discrete
N.SetNodeLevels_bn(RangeExpansionContraction, 5, [0,20,40,60,80,INFINITY_ns])
N.SetNodeLevels_bn(Connectivity, 5, [0,20,40,60,80,INFINITY_ns])
N.SetNodeLevels_bn(EnvIndexRelHistorical, 5, [0,20,40,60,80,INFINITY_ns])

# adding states to each node
N.SetNodeStateNames_bn(OtherOrganisms, "absent,present")
N.SetNodeStateNames_bn(PopulationSizeEffect, "absent,present")
N.SetNodeStateNames_bn(EnvironmentalOutcome, "A,B,C,D,E")
N.SetNodeStateNames_bn(NonHabitatInfluences, "strong,medium,weak")
N.SetNodeStateNames_bn(PopulationOutcome, "A,B,C,D,E")
N.SetNodeStateNames_bn(RangeExpansionContraction, "r0_20,r20_40,r40_60,r60_80,greater80")
N.SetNodeStateNames_bn(Connectivity, "r0_20,r20_40,r40_60,r60_80,greater80")
N.SetNodeStateNames_bn(EnvIndexRelHistorical, "r0_20,r20_40,r40_60,r60_80,greater80")

# adding links between nodes
N.AddLink_bn(RangeExpansionContraction, EnvironmentalOutcome)
N.AddLink_bn(Connectivity, EnvironmentalOutcome)
N.AddLink_bn(EnvIndexRelHistorical, EnvironmentalOutcome)
N.AddLink_bn(OtherOrganisms, NonHabitatInfluences)
N.AddLink_bn(PopulationSizeEffect, NonHabitatInfluences)
N.AddLink_bn(EnvironmentalOutcome, PopulationOutcome)
N.AddLink_bn(NonHabitatInfluences, PopulationOutcome)

# setting the probabilities for each top level node
N.SetNodeProbs (RangeExpansionContraction, 0.2, 0.2, 0.2, 0.2, 0.2)
N.SetNodeProbs (Connectivity, 0.2, 0.2, 0.2, 0.2, 0.2)
N.SetNodeProbs (EnvIndexRelHistorical, 0.2, 0.2, 0.2, 0.2, 0.2)
N.SetNodeProbs (OtherOrganisms, 0.5, 0.5)
N.SetNodeProbs (PopulationSizeEffect, 0.5, 0.5)

# assigning probabilities for the lower level nodes
N.SetNodeProbs (NonHabitatInfluences, "absent", "absent", 0.0, 0.0, 1.0)
N.SetNodeProbs (NonHabitatInfluences, "absent", "present", 0.5, 0.4, 0.1)
N.SetNodeProbs (NonHabitatInfluences, "present", "absent", 0.1, 0.3, 0.6)
N.SetNodeProbs (NonHabitatInfluences, "present", "present", 0.9, 0.1, 0.0)


# Set the node probabilities for EnvironmentalOutcome from a TSV file
# since there are too many values
ranges = ["r0_20","r20_40","r40_60","r60_80","greater80"]

with open(BASE_DIR + '/Environmental Outcome.txt') as f:
    env_data = [map(float,i.split()) for i in f.readlines()]

count = 0
for i in ranges:
    for j in ranges:
        for k in ranges:
            N.SetNodeProbs (EnvironmentalOutcome, i, j, k, env_data[count][0], env_data[count][1], env_data[count][2], env_data[count][3], env_data[count][4])
            #print "N.SetNodeProbs (EnvironmentalOutcome, "+i+", "+j+", "+k+", "+str(env_data[count][0])+", "+str(env_data[count][1])+", "+str(env_data[count][2])+", "+str(env_data[count][3])+", "+str(env_data[count][4])
            count += 1
            

# set the node function for the Population Outcome
N.SetNodeFuncState(PopulationOutcome, 2,"A",'strong')
N.SetNodeFuncState(PopulationOutcome, 1,"A",'medium')
N.SetNodeFuncState(PopulationOutcome, 0,"A",'weak')
N.SetNodeFuncState(PopulationOutcome, 3,"B",'strong')
N.SetNodeFuncState(PopulationOutcome, 2,"B",'medium')
N.SetNodeFuncState(PopulationOutcome, 1,"B",'weak')
N.SetNodeFuncState(PopulationOutcome, 4,"C",'strong')
N.SetNodeFuncState(PopulationOutcome, 3,"C",'medium')
N.SetNodeFuncState(PopulationOutcome, 2,"C",'weak')
N.SetNodeFuncState(PopulationOutcome, 4,"D",'strong')
N.SetNodeFuncState(PopulationOutcome, 4,"D",'medium')
N.SetNodeFuncState(PopulationOutcome, 3,"D",'weak')
N.SetNodeFuncState(PopulationOutcome, 4,"E",'strong')
N.SetNodeFuncState(PopulationOutcome, 4,"E",'medium')
N.SetNodeFuncState(PopulationOutcome, 4,"E",'weak')


# print the error message in case of any errors within Netica
print N.ErrorMessage_ns(N.GetError_ns(N, 5, 0))

# compile the final network
N.CompileNet_bn (bayesian_network)            

# get the belief for each state for PopulationOutcome
belief = N.GetNodeBelief ("PopulationOutcome", "A", bayesian_network)
print """The probability is %g"""% belief

belief = N.GetNodeBelief ("PopulationOutcome", "B", bayesian_network)
print """The probability is %g"""% belief

belief = N.GetNodeBelief ("PopulationOutcome", "C", bayesian_network)
print """The probability is %g"""% belief

belief = N.GetNodeBelief ("PopulationOutcome", "D", bayesian_network)
print """The probability is %g"""% belief

belief = N.GetNodeBelief ("PopulationOutcome", "E", bayesian_network)
print """The probability is %g"""% belief

# delete the network and print the returned message
N.DeleteNet_bn (bayesian_network)
res = N.CloseNetica_bn (env, mesg)

print mesg
