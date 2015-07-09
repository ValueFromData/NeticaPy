from NeticaPy import Netica
N=Netica()
mesg=bytearray()
env=N.NewNeticaEnviron_ns("",None,"")
#env = N.NewNeticaEnviron_ns ("",None,"");
res = N.InitNetica2_bn (env, mesg)

print mesg
	
net = N.NewNet_bn ("ChestClinic", env)

VisitAsia =   N. NewNode_bn ("VisitAsia", 2, net);
Tuberculosis = N.NewNode_bn ("Tuberculosis", 2, net);
Smoking =      N.NewNode_bn ("Smoking", 2, net);
Cancer =       N.NewNode_bn ("Cancer", 2, net);
TbOrCa =       N.NewNode_bn ("TbOrCa", 2, net);
XRay =         N.NewNode_bn ("XRay", 2, net);


N.SetNodeStateNames_bn (VisitAsia,   "visit,   no_visit");
N.SetNodeStateNames_bn (Tuberculosis,"present, absent");
N.SetNodeStateNames_bn (Smoking,     "smoker,  nonsmoker");
N.SetNodeStateNames_bn (Cancer,      "present, absent");
N.SetNodeStateNames_bn (TbOrCa,      "true,    false");
N.SetNodeStateNames_bn (XRay,        "abnormal,normal");
N.SetNodeTitle_bn (TbOrCa, "Tuberculosis or Cancer");
N.SetNodeTitle_bn (Cancer, "Lung Cancer");


N.AddLink_bn (VisitAsia, Tuberculosis);
N.AddLink_bn (Smoking, Cancer);
N.AddLink_bn (Tuberculosis, TbOrCa);
N.AddLink_bn (Cancer, TbOrCa);
N.AddLink_bn (TbOrCa, XRay);

	
N.SetNodeProbs (VisitAsia, 0.01, 0.99);
	
N.SetNodeProbs (Tuberculosis, "visit",    0.05, 0.95);
N.SetNodeProbs (Tuberculosis, "no_visit", 0.01, 0.99);

N.SetNodeProbs (Smoking, 0.5, 0.5);

N.SetNodeProbs (Cancer, "smoker",    0.1,  0.9);
N.SetNodeProbs (Cancer, "nonsmoker", 0.01, 0.99);

#                   Tuberculosis Cancer
N.SetNodeProbs (TbOrCa, "present", "present", 1.0, 0.0);
N.SetNodeProbs (TbOrCa, "present", "absent",  1.0, 0.0);
N.SetNodeProbs (TbOrCa, "absent",  "present", 1.0, 0.0);
N.SetNodeProbs (TbOrCa, "absent",  "absent",  0.0, 1.0);

#                  TbOrCa  Abnormal Normal

N.SetNodeProbs (XRay, "true",  0.98,  0.02);
N.SetNodeProbs (XRay, "false", 0.05,  0.95);


N.CompileNet_bn (net)

belief = N.GetNodeBelief ("Tuberculosis", "present", net)
print """The probability of tuberculosis is %g"""% belief

N.EnterFinding ("XRay", "abnormal", net);
belief = N.GetNodeBelief ("Tuberculosis", "present", net);


print """Given an abnormal X-ray, 
         the probability of tuberculosis is %s""" % belief

N.EnterFinding ("VisitAsia", "visit", net)
belief = N.GetNodeBelief ("Tuberculosis", "present", net)

print """Given an abnormal X-ray and a visit to Asia,
	     the probability of tuberculosis is %s""" % belief

N.EnterFinding ("Cancer", "present", net)
belief = N.GetNodeBelief ("Tuberculosis", "present", net)


print """Given abnormal X-ray, Asia visit, and lung cancer, 
         the probability of tuberculosis is %s""" % belief


N.DeleteNet_bn (net)
res = N.CloseNetica_bn (env, mesg)

print mesg
