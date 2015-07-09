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
bayesian_network = N.NewNet_bn ("Animals", env)

# create each node in the network
Animal = N.NewNode_bn("Animal", 5, bayesian_network)
HasShell = N.NewNode_bn("HasShell", 2, bayesian_network)
Environment = N.NewNode_bn("Environment", 3, bayesian_network)
Class = N.NewNode_bn("Class", 3, bayesian_network)
BearsYoung = N.NewNode_bn("BearsYoung", 2, bayesian_network)
WarmBlooded = N.NewNode_bn("WarmBlooded", 2, bayesian_network)
BodyCovering = N.NewNode_bn("BodyCovering", 3, bayesian_network)




# adding states to each node
N.SetNodeStateNames_bn(Animal, "monkey,penguin,platypus,robin,turtle")
N.SetNodeStateNames_bn(HasShell, "true,false")
N.SetNodeStateNames_bn(Environment, "air,land,water")
N.SetNodeStateNames_bn(Class, "bird,mammal,reptile")
N.SetNodeStateNames_bn(WarmBlooded, "true,false")
N.SetNodeStateNames_bn(BodyCovering, "fur,feathers,scales")


# adding links between nodes
N.AddLink_bn(Animal, HasShell)
N.AddLink_bn(Animal, BearsYoung)
N.AddLink_bn(Animal, Class)
N.AddLink_bn(Animal, Environment)
N.AddLink_bn(Class, WarmBlooded)
N.AddLink_bn(Class, BodyCovering)


# setting the probabilities for each top level node
#N.SetNodeProbs (Animal, 0.2, 0.2, 0.2, 0.2, 0.2)

N.SetNodeFuncState (HasShell, 1,'monkey')
N.SetNodeFuncState (HasShell, 1,'penguin')
N.SetNodeFuncState (HasShell, 1,'platypus')
N.SetNodeFuncState (HasShell, 1,'robin')
N.SetNodeFuncState (HasShell, 0,'turtle')


N.SetNodeProbs (Environment,'monkey',0,1,0)
N.SetNodeProbs (Environment,'penguin',0, 0.5,0.5)
N.SetNodeProbs (Environment,'platypus',0,0,1)
N.SetNodeProbs (Environment,'robin',0.5,0.5,0)
N.SetNodeProbs (Environment,'turtle',0,0.5,0.5)


N.SetNodeFuncState (BearsYoung,0,'monkey')
N.SetNodeFuncState (BearsYoung,1,'penguin')
N.SetNodeFuncState (BearsYoung,1,'platypus')
N.SetNodeFuncState (BearsYoung,1,'robin')
N.SetNodeFuncState (BearsYoung,1,'turtle')




N.SetNodeFuncState (Class,1,'monkey')
N.SetNodeFuncState (Class,0,'penguin')
N.SetNodeFuncState (Class,1,'platypus')
N.SetNodeFuncState (Class,0,'robin')
N.SetNodeFuncState (Class,2,'turtle')




N.SetNodeFuncState (WarmBlooded,0,'bird')
N.SetNodeFuncState (WarmBlooded,0,'mammal')
N.SetNodeFuncState (WarmBlooded,1,'reptile')



N.SetNodeFuncState (BodyCovering,1,'bird')
N.SetNodeFuncState (BodyCovering,0,'mammal')
N.SetNodeFuncState (BodyCovering,2,'reptile')






# print the error message in case of any errors within Netica
print N.ErrorMessage_ns(N.GetError_ns(N, 5, 0))

# compile the final network
N.CompileNet_bn (bayesian_network)            

# get the belief for each state for PopulationOutcome
belief = N.GetNodeBelief ("Animal", "turtle", bayesian_network)
print """The probability of being turtle is %g"""% belief


N.EnterFinding ("WarmBlooded", 'true', bayesian_network)
belief = N.GetNodeBelief ("Animal", "turtle", bayesian_network)
print """The probability of being turtle when its WarmBlooded %g"""% belief


# delete the network and print the returned message
N.DeleteNet_bn (bayesian_network)
res = N.CloseNetica_bn (env, mesg)

print mesg
