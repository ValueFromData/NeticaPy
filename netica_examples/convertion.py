from NeticaPy import Netica
N=Netica()
mesg=bytearray()
env=N.NewNeticaEnviron_ns("",None,"")
#env = N.NewNeticaEnviron_ns ("",None,"")
res = N.InitNetica2_bn (env, mesg)

print mesg
	
net = N.NewNet_bn ("Convertion", env)

converted = N. NewNode_bn ("Converted", 2, net)
email     = N.NewNode_bn ("Email", 2, net)
company   = N.NewNode_bn ("Company", 2, net)
jobTitle  = N.NewNode_bn ("Job_Title", 2, net)
purpose   = N.NewNode_bn ("Purpose", 2, net)
activity  = N.NewNode_bn ("Activity", 2, net)


N.SetNodeStateNames_bn (converted,"Yes,         No")
N.SetNodeStateNames_bn (email,    "Specific,    Generic")
N.SetNodeStateNames_bn (company,  "Specified,   Not_Specified")
N.SetNodeStateNames_bn (jobTitle, "Present,     Absent")
N.SetNodeStateNames_bn (purpose,  "Specified,   Not_Specified")
N.SetNodeStateNames_bn (activity, "Occured,     Not_Occured")

node_variables = {
    "Email"     :   ["Specific", "Generic"],
    "Company"   :   ["Specified","Not_Specified"],
    "Job_Title" :   ["Present",  "Absent"],
    "Purpose"   :   ["Specified","Not_Specified"],
    "Activity"  :   ["Occured",  "Not_Occured"]
    }
node_names=list(node_variables)

N.AddLink_bn (converted, email)
N.AddLink_bn (converted, company)
N.AddLink_bn (converted, jobTitle)
N.AddLink_bn (converted, purpose)
N.AddLink_bn (converted, activity)

	
N.SetNodeProbs (converted, 0.1302, 0.8698)
	
N.SetNodeProbs (email, "Yes", 0.8394, 0.1606)
N.SetNodeProbs (email, "No",  0.5895, 0.4105)

N.SetNodeProbs (company, "Yes", 0.6451, 0.3549)
N.SetNodeProbs (company, "No",  0.1864, 0.8136)

N.SetNodeProbs (jobTitle, "Yes", 0.6155, 0.3845)
N.SetNodeProbs (jobTitle, "No",  0.1697, 0.8303)

N.SetNodeProbs (purpose, "Yes", 0.40282, 0.59718)
N.SetNodeProbs (purpose, "No",  0.13177, 0.86823)

N.SetNodeProbs (activity, "Yes", 1.0, 0.0)
N.SetNodeProbs (activity, "No",  0.32406, 0.67594)

N.CompileNet_bn (net)

#belief = N.GetNodeBelief ("Converted", "Yes", net)
#print """The probability of convertion is %g"""% belief

#for i in range(32):
#    x=map(int,bin(31-i)[2:].zfill(5))
#    msg="Given "
#    N.CompileNet_bn(net)
#    for j in  range(5):
#        N.EnterFinding (node_names[j], node_variables[node_names[j]][x[j]], net)
#        msg+="%s[%s], " % (node_names[j], node_variables[node_names[j]][x[j]])
#    belief = N.GetNodeBelief ("Converted", "Yes", net)
#    print msg,"the probability of convertion is %s"% belief

msg= "Given "
for j in  range(5):
    print "Choise for %s:\n-1 : Unknown" % node_names[j]
    for k in range(len(node_variables[node_names[j]])):
        print k," : ",node_variables[node_names[j]][k]
    i = input("Enter choice: ")
    if i>=0 and i<len(node_variables[node_names[j]]):
        N.EnterFinding (node_names[j], node_variables[node_names[j]][i], net)
        msg+="%s %s, " % (node_names[j], node_variables[node_names[j]][i])
belief = N.GetNodeBelief ("Converted", "Yes", net)
print msg,"the probability of convertion is %s"% belief

N.DeleteNet_bn (net)
res = N.CloseNetica_bn (env, mesg)

print mesg
