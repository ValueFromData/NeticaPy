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
bayesian_network = N.NewNet_bn ("Mesentria", env)

# create each node in the network
Snags = N.NewNode_bn("Snags", 3, bayesian_network)
Stumps = N.NewNode_bn("Stumps", 3, bayesian_network)
TreeCanopyCover = N.NewNode_bn("TreeCanopyCover", 3, bayesian_network)
MesicIndicatorPlants = N.NewNode_bn("MesicIndicatorPlants", 3, bayesian_network)
DecayClass = N.NewNode_bn("DecayClass", 4, bayesian_network)
SubstrateType = N.NewNode_bn("SubstrateType", 2, bayesian_network)
LocalSlope = N.NewNode_bn("LocalSlope", 2, bayesian_network)
LocalVegetation = N.NewNode_bn("LocalVegetation", 2, bayesian_network)
Pinaceae = N.NewNode_bn("Pinaceae", 2, bayesian_network)
BMesPresence = N.NewNode_bn("BMesPresence", 2, bayesian_network)



# setting node levels for the contiuous variables that have been made discrete
N.SetNodeLevels_bn(Snags,3,[0,0,100,INFINITY_ns])
N.SetNodeLevels_bn(Stumps,3,[0,0,100,INFINITY_ns])
N.SetNodeLevels_bn(TreeCanopyCover,3,[0,50,80,100])
N.SetNodeLevels_bn(LocalSlope,2,[0,30,INFINITY_ns])


N.SetNodeStateNames_bn(Snags, "r0,r0_100,greater100")
N.SetNodeStateNames_bn(Stumps, "r0,r0_100,greater100")
N.SetNodeStateNames_bn(TreeCanopyCover, "r0_50,r50_80,r80_100")
N.SetNodeStateNames_bn(LocalSlope, "r0_30,greater30")
N.SetNodeStateNames_bn(MesicIndicatorPlants, "abundant,sparse,absent")
N.SetNodeStateNames_bn(DecayClass, "sound,intermediate,decayed,none")
N.SetNodeStateNames_bn(SubstrateType, "adequate,inadequate")
N.SetNodeStateNames_bn(LocalVegetation, "adequate,inadequate")
N.SetNodeStateNames_bn(Pinaceae, "adequate,inadequate")
N.SetNodeStateNames_bn(BMesPresence, "present,absent")



# adding links between nodes
N.AddLink_bn(Stumps, SubstrateType)
N.AddLink_bn(Snags, SubstrateType)
N.AddLink_bn(MesicIndicatorPlants, LocalVegetation)
N.AddLink_bn(TreeCanopyCover, LocalVegetation)
N.AddLink_bn(SubstrateType, Pinaceae)
N.AddLink_bn(DecayClass, Pinaceae)
N.AddLink_bn(Pinaceae, BMesPresence)
N.AddLink_bn(LocalVegetation, BMesPresence)
N.AddLink_bn(LocalSlope, BMesPresence)




N.SetNodeProbs (SubstrateType,'r0','r0',0.0,1.0)
N.SetNodeProbs (SubstrateType,'r0','r0_100',0.5,0.5)
N.SetNodeProbs (SubstrateType,'r0','greater100',1,0)
N.SetNodeProbs (SubstrateType,'r0_100','r0',0.5,0.5)
N.SetNodeProbs (SubstrateType,'r0_100','r0_100',0.5,0.5)
N.SetNodeProbs (SubstrateType,'r0_100','greater100',1,0)
N.SetNodeProbs (SubstrateType,'greater100','r0',1,0)
N.SetNodeProbs (SubstrateType,'greater100','r0_100',1,0)
N.SetNodeProbs (SubstrateType,'greater100','greater100',1,0)

N.SetNodeProbs (LocalVegetation,'abundant','r0_50',0.1,0.9)
N.SetNodeProbs (LocalVegetation,'abundant','r50_80',0.8,0.2)
N.SetNodeProbs (LocalVegetation,'abundant','r80_100',1,0)
N.SetNodeProbs (LocalVegetation,'sparse','r0_50',0.1,0.9)
N.SetNodeProbs (LocalVegetation,'sparse','r50_80',0.5,0.5)
N.SetNodeProbs (LocalVegetation,'sparse','r80_100',0.7,0.3)
N.SetNodeProbs (LocalVegetation,'absent','r0_50',0,1)
N.SetNodeProbs (LocalVegetation,'absent','r50_80',0.2,0.8)
N.SetNodeProbs (LocalVegetation,'absent','r80_100',0.5,0.5)

N.SetNodeProbs (Pinaceae,'adequate','sound',0.2,0.8)
N.SetNodeProbs (Pinaceae,'adequate','intermediate',1,0)
N.SetNodeProbs (Pinaceae,'adequate','decayed',1,0)
N.SetNodeProbs (Pinaceae,'adequate','none',0,1)
N.SetNodeProbs (Pinaceae,'inadequate','sound',0.1,0.9)
N.SetNodeProbs (Pinaceae,'inadequate','intermediate',0.5,0.5)
N.SetNodeProbs (Pinaceae,'inadequate','decayed',0.5,0.5)
N.SetNodeProbs (Pinaceae,'inadequate','none',0,1)


N.SetNodeProbs (BMesPresence,'adequate','adequate','r0_30',1,0)
N.SetNodeProbs (BMesPresence,'adequate','adequate','greater30',0.8,0.2)
N.SetNodeProbs (BMesPresence,'adequate','inadequate','r0_30',0.8,0.2)
N.SetNodeProbs (BMesPresence,'adequate','inadequate','greater30',0.5,0.5)
N.SetNodeProbs (BMesPresence,'inadequate','adequate','r0_30',0.1,0.9)
N.SetNodeProbs (BMesPresence,'inadequate','adequate','greater30',0.05,0.95)
N.SetNodeProbs (BMesPresence,'inadequate','inadequate','r0_30',0.05,0.95)
N.SetNodeProbs (BMesPresence,'inadequate','inadequate','greater30',0,1)


# print the error message in case of any errors within Netica
print N.ErrorMessage_ns(N.GetError_ns(N, 5, 0))

# compile the final network
N.CompileNet_bn (bayesian_network)            



belief = N.GetNodeBelief ("BMesPresence", "absent", bayesian_network)
print """The probability is %g"""% belief
