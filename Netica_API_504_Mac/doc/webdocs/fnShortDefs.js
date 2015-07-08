var shortDef = new Array(); 
var ii=0;

function tooltip ( fn ) {
  var i;
  for (i=0;i < shortDef.length;i++){
    if (shortDef[i].fnName == fn ) {
      var obj = document.getElementById( "ID_" + fn );
      if ( obj ) obj.title = shortDef[i].fnText;
      break;
    }
  }
}
//-------------------------------------------------------------
//                   C o n s t r u c t o r s
//-------------------------------------------------------------
function ShortDef ( fnName, fnText ) {
  this.fnName = fnName;
  this.fnText = fnText;
}

shortDef[ii++] = new ShortDef( 'xyz', 'xyx description' );



 
shortDef[ii++] = new ShortDef( 'AbsorbNodes_bn', 'Absorb these nodes, so that they are removed from the net, but the net`s overall joint probabilities for the other nodes is unchanged' );
shortDef[ii++] = new ShortDef( 'AddDBCasesToCaseset_cs', 'Creates a caseset_cs by selecting node values from a database' );
shortDef[ii++] = new ShortDef( 'AddFileToCaseset_cs', 'Reads the entire contents of a stream and places all the cases found into a given Caseset' );
shortDef[ii++] = new ShortDef( 'AddLink_bn', 'Add a link from parent to this node, returning the new link`s index.' );
shortDef[ii++] = new ShortDef( 'AddNodesFromDB_bn', 'Creates and adds nodes and their states to a net, based on the values retrieved from a database' );
shortDef[ii++] = new ShortDef( 'AddNodeStates_bn', 'Adds one or more states to a node, inserting them into the existing states' );
shortDef[ii++] = new ShortDef( 'AddNodeToList_bn', 'Inserts index, making the list one longer, and maintaining the order of the rest of the nodes' );
shortDef[ii++] = new ShortDef( 'AddNodeToNodeset_bn', 'Adds nodeset' );
shortDef[ii++] = new ShortDef( 'ArgumentChecking_ns', 'Adjusts the amount that Netica functions check their arguments' );
shortDef[ii++] = new ShortDef( 'CalcNodeState_bn', 'Returns the discrete finding entered for UNDEF_STATE' );
shortDef[ii++] = new ShortDef( 'CalcNodeValue_bn', 'Returns the real-valued finding entered for UNDEF_DBL' );
shortDef[ii++] = new ShortDef( 'ClearError_ns', 'Removes the given error report from the system' );
shortDef[ii++] = new ShortDef( 'ClearErrors_ns', 'Removes all errors recorded with environment severity, or less serious' );
shortDef[ii++] = new ShortDef( 'ClearNodeList_bn', 'Removes all the nodes from the list nodes' );
shortDef[ii++] = new ShortDef( 'CloseNetica_bn', 'Closes down and frees all Netica resources' );
shortDef[ii++] = new ShortDef( 'CompileNet_bn', 'Compiles net for fast belief updating' );
shortDef[ii++] = new ShortDef( 'ControlConcurrency_ns', 'Controls how Netica operates in multi-threaded environments.' );
shortDef[ii++] = new ShortDef( 'ControlNetCaching_bn', 'Controls how net is cached.' );
shortDef[ii++] = new ShortDef( 'CopyNet_bn', 'Duplicates a net' );
shortDef[ii++] = new ShortDef( 'CopyNodes_bn', 'Duplicate the nodes in this list, putting the new nodes in passed `net`, and return a list of them.' );
shortDef[ii++] = new ShortDef( 'CreateCustomReport_bn', 'Creates a text (possibly HTML, RTF, TXT, etc.) report on net.' );
shortDef[ii++] = new ShortDef( 'DeleteCaseset_cs', 'Removes the Caseset and frees all its resources' );
shortDef[ii++] = new ShortDef( 'DeleteDBManager_cs', 'Removes the database manager from the system and releases its database connections' );
shortDef[ii++] = new ShortDef( 'DeleteLearner_bn', 'Removes the learner_bn object and frees all its resources' );
shortDef[ii++] = new ShortDef( 'DeleteLink_bn', 'Delete the link entering this node from the give parent node.' );
shortDef[ii++] = new ShortDef( 'DeleteNet_bn', 'Removes net from the system, and releases all resources it uses (e.g., frees memory), including all its substructures (e.g., nodes)' );
shortDef[ii++] = new ShortDef( 'DeleteNetTester_bn', 'Releases all memory and other resources used by the net tester object' );
shortDef[ii++] = new ShortDef( 'DeleteNode_bn', 'Removes node from its net, and frees all resources (e.g., memory) it was using' );
shortDef[ii++] = new ShortDef( 'DeleteNodeList_bn', 'Releases the memory used by the node list nodes' );
shortDef[ii++] = new ShortDef( 'DeleteNodeTables_bn', 'Delete the CPT, experience, and function tables for this node, if there are any' );
shortDef[ii++] = new ShortDef( 'DeleteRandomGen_ns', 'Removes gen from the system, and releases all resources it uses (e.g., frees memory)' );
shortDef[ii++] = new ShortDef( 'DeleteSensvToFinding_bn', 'Remove this sensitivity measurer, freeing all resources it consumes (including memory)' );
shortDef[ii++] = new ShortDef( 'DeleteStream_ns', 'Frees all resources this stream is using' );
shortDef[ii++] = new ShortDef( 'DupNodeList_bn', 'Duplicates the list nodes, and returns the duplicate list' );
shortDef[ii++] = new ShortDef( 'EnterFinding_bn', 'Enters the discrete finding state for node, that is, declare the node to be in the given state' );
shortDef[ii++] = new ShortDef( 'EnterFindingNot_bn', 'Enter a negative finding for this node, that is, declare that the node is in some state other than the given state' );
shortDef[ii++] = new ShortDef( 'EnterGaussianFinding_bn', 'Enters a likelihood finding for this continuous node that is equivalent to a gaussian distribution' );
shortDef[ii++] = new ShortDef( 'EnterIntervalFinding_bn', 'Enters a likelihood finding that this node`s value falls between high, inclusive' );
shortDef[ii++] = new ShortDef( 'EnterNodeLikelihood_bn', 'Enter a likelihood vector for this node.  The vector is an array of one probability per state (that need not sum to 1)' );
shortDef[ii++] = new ShortDef( 'EnterNodeValue_bn', 'Enters a real number finding for node (which is normally a continuous variable node)' );
shortDef[ii++] = new ShortDef( 'EquationToTable_bn', 'Builds this node`s CPT based on its equation' );
shortDef[ii++] = new ShortDef( 'ErrorCategory_ns', 'Test a given ERROR_CATEGORY to see if this error is in that category' );
shortDef[ii++] = new ShortDef( 'ErrorMessage_ns', 'Returns a message describing this error' );
shortDef[ii++] = new ShortDef( 'ErrorNumber_ns', 'Returns the error number identifying this error' );
shortDef[ii++] = new ShortDef( 'ErrorSeverity_ns', 'Returns the severity level of this error' );
shortDef[ii++] = new ShortDef( 'ExecuteDBSql_cs', 'Executes an arbitrary SQL command on a database' );
shortDef[ii++] = new ShortDef( 'ExpandNet_bn', 'Expands this dynamic Bayes net (DBN).' );
shortDef[ii++] = new ShortDef( 'FadeCPTable_bn', 'Reduce the confidence of this node`s CPT to reflect the fact that the world has changed since the CPT was learned from it' );
shortDef[ii++] = new ShortDef( 'FindingsProbability_bn', 'Returns the joint probability of the findings entered into net so far' );
shortDef[ii++] = new ShortDef( 'GenerateRandomCase_bn', 'Generate a random case by simulation' );
shortDef[ii++] = new ShortDef( 'GenerateRandomNumbers_ns', 'Returns a set of random number between 0.0 and 1.0, inclusive' );
shortDef[ii++] = new ShortDef( 'GetAllNodesets_bn', 'Returns a string which is list of all node-sets defined for net' );
shortDef[ii++] = new ShortDef( 'GetError_ns', 'Gets the next error report of a given severity or worse' );
shortDef[ii++] = new ShortDef( 'GetInputNamed_bn', 'Returns the input index of this node`s `parent` link, or -1 if there isn`t one.  ' );
shortDef[ii++] = new ShortDef( 'GetMutualInfo_bn', 'The mutual information between this (query) node and Vnode.  Pass EntropyMeasure to BNet#NewSensitivity for this to work' );
shortDef[ii++] = new ShortDef( 'GetNetAutoUpdate_bn', 'Returns the current auto-updating value.  E.g., if =BELIEF_UPDATE then beliefs are automatically recalculated whenever a finding is entered into this net; if =0 then no auto-updating is performed' );
shortDef[ii++] = new ShortDef( 'GetNetComment_bn', 'Get documentation or a description of this net' );
shortDef[ii++] = new ShortDef( 'GetNetElimOrder_bn', 'Returns a list of the nodes of net' );
shortDef[ii++] = new ShortDef( 'GetNetFileName_bn', 'Returns the name of the file (including full path) that the net was last written to or read from' );
shortDef[ii++] = new ShortDef( 'GetNeticaVersion_bn', 'Returns the version number of Netica, multiplied by 100.  (So version 1.34 would return 134)' );
shortDef[ii++] = new ShortDef( 'GetNetName_bn', 'Returns the size-restricted name of this net' );
shortDef[ii++] = new ShortDef( 'GetNetNodes_bn', 'Returns a list of all the nodes in a net' );
shortDef[ii++] = new ShortDef( 'GetNetNthUserField_bn', 'This returns the field-by-field user-defined data associated with the net, by index rather than field name' );
shortDef[ii++] = new ShortDef( 'GetNetTitle_bn', 'Gets the unrestricted label for this net' );
shortDef[ii++] = new ShortDef( 'GetNetUserData_bn', 'Returns a pointer to information previously attached to NULL if none has been attached' );
shortDef[ii++] = new ShortDef( 'GetNetUserField_bn', 'Retrieves field-by-field info from net by field name' );
shortDef[ii++] = new ShortDef( 'GetNodeBeliefs_bn', 'Returns a belief vector indicating the current probability for each state of node' );
shortDef[ii++] = new ShortDef( 'GetNodeChildren_bn', 'Get a list of child nodes of this node, that is, those nodes which are at the end of a link that exits this node' );
shortDef[ii++] = new ShortDef( 'GetNodeComment_bn', 'Get documentation or a description of this node' );
shortDef[ii++] = new ShortDef( 'GetNodeEquation_bn', 'Gets the equation giving the probability of this node conditioned on its parent nodes, or the value of this node as a function of its parents' );
shortDef[ii++] = new ShortDef( 'GetNodeExpectedUtils_bn', 'Returns a vector providing the expected utility of each choice in a decision node, considering findings currently entered' );
shortDef[ii++] = new ShortDef( 'GetNodeExpectedValue_bn', 'Returns the expected real value of node' );
shortDef[ii++] = new ShortDef( 'GetNodeExperience_bn', 'Gets the experience of this node as a function of its parent nodes being in the given states' );
shortDef[ii++] = new ShortDef( 'GetNodeFinding_bn', 'Gets the state finding entered for this node (returns a `SpecialFinding` code if another kind of finding is entered)' );
shortDef[ii++] = new ShortDef( 'GetNodeFuncReal_bn', 'Gets the real value of this node as a function of its parent nodes.  For discrete nodes, it is better to use SetNodeFuncState_bn' );
shortDef[ii++] = new ShortDef( 'GetNodeFuncState_bn', 'Gets the state value of this node as a function of its parent nodes.  For continuous nodes, it is better to use GetNodeFuncReal_bn' );
shortDef[ii++] = new ShortDef( 'GetNodeInputName_bn', 'Gets the name of this node`s input (i.e., link) identified by the given index' );
shortDef[ii++] = new ShortDef( 'GetNodeKind_bn', 'Returns whether node is a nature, decision, utility or constant node' );
shortDef[ii++] = new ShortDef( 'GetNodeLevels_bn', 'Returns the list of numbers used to enable a continuous node to act discrete, or enables a discrete node to provide real-valued numbers.  Levels are used to discretize continuous nodes, or to map from discrete nodes to real numbers' );
shortDef[ii++] = new ShortDef( 'GetNodeLikelihood_bn', 'Returns the accumulated (likelihood and other) findings for this node' );
shortDef[ii++] = new ShortDef( 'GetNodeName_bn', 'Returns the size-restricted name of this node' );
shortDef[ii++] = new ShortDef( 'GetNodeNamed_bn', 'Returns the node of this net which has a name exactly matching NULL' );
shortDef[ii++] = new ShortDef( 'GetNodeNet_bn', 'Returns the net that node is part of' );
shortDef[ii++] = new ShortDef( 'GetNodeNthUserField_bn', 'This returns the field-by-field user-defined data associated with the node, by index rather than field name' );
shortDef[ii++] = new ShortDef( 'GetNodeNumberStates_bn', 'Gets the number of states node has (0 for undiscretized continuous nodes)' );
shortDef[ii++] = new ShortDef( 'GetNodeParents_bn', 'Get a list of parent nodes of this node, that is, those nodes which are at the beginning of a link that enters this node' );
shortDef[ii++] = new ShortDef( 'GetNodeProbs_bn', 'Gets the probabilities for each state parent_states, pass an array of their state indexes' );
shortDef[ii++] = new ShortDef( 'GetNodeStateComment_bn', 'Gets the comment of this node`s state identified by the given index' );
shortDef[ii++] = new ShortDef( 'GetNodeStateName_bn', 'Returns the name of the given state' );
shortDef[ii++] = new ShortDef( 'GetNodeStateTitle_bn', 'Gets the title of this node`s state identified by the given index' );
shortDef[ii++] = new ShortDef( 'GetNodeTitle_bn', 'Gets the unrestricted label for this node' );
shortDef[ii++] = new ShortDef( 'GetNodeType_bn', 'Returns DISCRETE_TYPE if the variable corresponding to node is discrete (digital), and CONTINUOUS_TYPE if it is continuous (analog)' );
shortDef[ii++] = new ShortDef( 'GetNodeUserData_bn', 'Retrieves the data object previously placed with SetNodeUserData_bn' );
shortDef[ii++] = new ShortDef( 'GetNodeUserField_bn', 'Gets the user-defined data associated with name for this node' );
shortDef[ii++] = new ShortDef( 'GetNodeValueEntered_bn', 'Gets the real value finding entered for this node' );
shortDef[ii++] = new ShortDef( 'GetNodeVisPosition_bn', 'Returns the x and y values of the center of the node in the net diagram (assuming a visual display exists)' );
shortDef[ii++] = new ShortDef( 'GetNodeVisStyle_bn', 'Returns the style of the node, should it be displayed.' );
shortDef[ii++] = new ShortDef( 'GetNthNet_bn', 'Returns the Nth Net (starting from 0) in the environment, or null if there is no Nth net' );
shortDef[ii++] = new ShortDef( 'GetRandomGenState_ns', 'Returns an ascii text representation of the current state of the random generator' );
shortDef[ii++] = new ShortDef( 'GetRelatedNodes_bn', 'Finds all the Nodes that have a given  relationship with a node' );
shortDef[ii++] = new ShortDef( 'GetRelatedNodesMult_bn', 'Finds all the Nodes that have a given relationship with any member of a nodelist' );
shortDef[ii++] = new ShortDef( 'GetStateNamed_bn', 'Gets the index of the state with the given name (valid for this node only)' );
shortDef[ii++] = new ShortDef( 'GetStreamContents_ns', 'Returns the memory buffer associated with a memory stream' );
shortDef[ii++] = new ShortDef( 'GetTestConfusion_bn', 'Computes and retrieves the percentage of times the net predicted actualState' );
shortDef[ii++] = new ShortDef( 'GetTestErrorRate_bn', 'Returns the cumulative "error rate" of a node under the tests previously performed' );
shortDef[ii++] = new ShortDef( 'GetTestLogLoss_bn', 'Returns the "logarithmic loss" of a node under the tests previously performed' );
shortDef[ii++] = new ShortDef( 'GetTestQuadraticLoss_bn', 'Returns the "quadratic loss" of a node under the tests previously performed' );
shortDef[ii++] = new ShortDef( 'GetVarianceOfReal_bn', 'The expected change squared in the expected real value of the query node, if a finding was obtained for finding_node.  Pass RealMeasure+VarianceMeasure to BNet.NewSensitivity for this to work' );
shortDef[ii++] = new ShortDef( 'HasNodeTable_bn', 'Whether or not this node has a relation table (i.e., conditional probability table (CPT) or function table)' );
shortDef[ii++] = new ShortDef( 'IndexOfNodeInList_bn', 'Returns the index position of nodes, or -1 if it was not found' );
shortDef[ii++] = new ShortDef( 'InitNetica2_bn', 'Initializes the Netica system' );
shortDef[ii++] = new ShortDef( 'InsertFindingsIntoDB_bn', 'Inserts a net`s findings into a database' );
shortDef[ii++] = new ShortDef( 'IsBeliefUpdated_bn', 'Whether the beliefs for this node have already been calculated (by belief propagation)' );
shortDef[ii++] = new ShortDef( 'IsNodeDeterministic_bn', 'Whether the value of this node given its parents is deterministic (versus probabilistic)' );
shortDef[ii++] = new ShortDef( 'IsNodeInNodeset_bn', 'Returns whether nodeset' );
shortDef[ii++] = new ShortDef( 'IsNodeRelated_bn', 'Tests whether two nodes are in a given relationship.' );
shortDef[ii++] = new ShortDef( 'JointProbability_bn', 'Returns the joint probability that these nodes are in the given states must have one entry for each node in this Node, and in the same order' );
shortDef[ii++] = new ShortDef( 'LearnCPTs_bn', 'Performs batch learning (e.g., EM or Gradient Descent)' );
shortDef[ii++] = new ShortDef( 'LengthNodeList_bn', 'Returns the number of nodes in a list' );
shortDef[ii++] = new ShortDef( 'LimitMemoryUsage_ns', 'Adjusts the amount of system memory that Netica can consume' );
shortDef[ii++] = new ShortDef( 'MapStateList_bn', 'Rearranges a state list to correspond to the order of a node list' );
shortDef[ii++] = new ShortDef( 'MostProbableConfig_bn', 'Finds the most probable configuration, also known as the most probable explanation (MPE) for all the nodes in the net' );
shortDef[ii++] = new ShortDef( 'NewCaseset_cs', 'Creates a new caseset_cs object, initially containing no cases' );
shortDef[ii++] = new ShortDef( 'NewDBManager_cs', 'Creates a new ODBC Manager object for working with a database' );
shortDef[ii++] = new ShortDef( 'NewError_ns', 'Make your own error report using Netica' );
shortDef[ii++] = new ShortDef( 'NewFileStream_ns', 'Creates a stream for the file with the given name' );
shortDef[ii++] = new ShortDef( 'NewLearner_bn', 'Creates a Learner object for use in EM, gradient-descent, and other learning' );
shortDef[ii++] = new ShortDef( 'NewMemoryStream_ns', 'Creates a stream that can read or write to a memory buffer, rather than a file' );
shortDef[ii++] = new ShortDef( 'NewNet_bn', 'Creates a new empty net' );
shortDef[ii++] = new ShortDef( 'NewNeticaEnviron_ns', 'Constructs and returns an uninitialized Netica environment' );
shortDef[ii++] = new ShortDef( 'NewNetTester_bn', 'Creates a tool for grading how well the predictions of a net match actual cases' );
shortDef[ii++] = new ShortDef( 'NewNode_bn', 'Creates and returns a new node for net' );
shortDef[ii++] = new ShortDef( 'NewNodeList2_bn', 'Creates a new (empty) list of nodes' );
shortDef[ii++] = new ShortDef( 'NewRandomGenerator_ns', 'Creates a new object to control the randomized aspects of Netica, or generate pseudo-random numbers' );
shortDef[ii++] = new ShortDef( 'NewSensvToFinding_bn', 'Construct a sensitivity measurer to determine how much this node could be affected by new findings at certain other nodes; for VARIANCE_OF_REAL_SENSV' );
shortDef[ii++] = new ShortDef( 'NthNode_bn', 'Returns the Nth node of a list (the first node is numbered 0)' );
shortDef[ii++] = new ShortDef( 'ReadNet_bn', 'Read a Bayes net from this stream' );
shortDef[ii++] = new ShortDef( 'ReadNetFindings2_bn', 'Read a case from the given stream into this node list' );
shortDef[ii++] = new ShortDef( 'RemoveNodeState_bn', 'Removes node has one fewer state' );
shortDef[ii++] = new ShortDef( 'RemoveNthNode_bn', 'Removes and returns the node at the given index of a list, making the list one shorter' );
shortDef[ii++] = new ShortDef( 'RedoNetOper_bn', 'Re-does an operation that was previously undone' );
shortDef[ii++] = new ShortDef( 'RemoveNodeFromNodeset_bn', 'Removes nodeset' );
shortDef[ii++] = new ShortDef( 'ReorderNodesets_bn', 'Rearranges the priority order of the node-sets of net' );
shortDef[ii++] = new ShortDef( 'ReorderNodeStates_bn', 'Rearranges the order of the states so that state i is moved to position new_order[i]' );
shortDef[ii++] = new ShortDef( 'ReportJunctionTree_bn', 'Returns a string describing the internal compiled junction tree' );
shortDef[ii++] = new ShortDef( 'RetractNetFindings_bn', 'Retract all findings entered in this net (from all nodes except `constant` nodes)' );
shortDef[ii++] = new ShortDef( 'RetractNodeFindings_bn', 'Retract findings previously entered for this node (state, real-valued and likelihood findings)' );
shortDef[ii++] = new ShortDef( 'ReverseLink_bn', 'Reverse the direction of the link from child, keeping the overall joint probabilities of the net unchanged.' );
shortDef[ii++] = new ShortDef( 'ReviseCPTsByCaseFile_bn', 'Revises the CPTs of these nodes, to account for the cases in the given file' );
shortDef[ii++] = new ShortDef( 'ReviseCPTsByFindings_bn', 'Revises the CPTs of these nodes, to account for the currently entered case' );
shortDef[ii++] = new ShortDef( 'SetCaseFileDelimChar_ns', 'Sets the character to use as a delimeter when creating case files.  Must be one of tab, space, or comma' );
shortDef[ii++] = new ShortDef( 'SetLearnerMaxIters_bn', 'Sets the maximum number of learning-step iterations of the learning algorithm' );
shortDef[ii++] = new ShortDef( 'SetLearnerMaxTol_bn', 'Sets the log likelihood tolerance, a termination limit of the learning algorithm' );
shortDef[ii++] = new ShortDef( 'SetLearnerRandomGen_bn', 'Sets the log likelihood tolerance, a termination limit of the learning algorithm' );
shortDef[ii++] = new ShortDef( 'SetMissingDataChar_ns', 'Sets the character (*, ?, space, or absent) to use to indicate missing data when creating case files' );
shortDef[ii++] = new ShortDef( 'SetNetAutoUpdate_bn', 'Turns auto-updating on or off' );
shortDef[ii++] = new ShortDef( 'SetNetComment_bn', 'Set documentation or a description of this net' );
shortDef[ii++] = new ShortDef( 'SetNetElimOrder_bn', 'Set an "Elimination order" of all the nodes in this net, used to guide compiling to find an efficient junction tree' );
shortDef[ii++] = new ShortDef( 'SetNetName_bn', 'Sets the size-restricted name of this net' );
shortDef[ii++] = new ShortDef( 'SetNetRandomGen_bn', 'Sets the net.' );
shortDef[ii++] = new ShortDef( 'SetNetTitle_bn', 'Sets the (size-unrestricted) label for this net' );
shortDef[ii++] = new ShortDef( 'SetNetUserData_bn', 'Attaches an arbitrary data object to this Net' );
shortDef[ii++] = new ShortDef( 'SetNetUserField_bn', 'Attaches user-defined data to this net (under category `fieldName`)' );
shortDef[ii++] = new ShortDef( 'SetNodeComment_bn', 'Set documentation or a description of this node' );
shortDef[ii++] = new ShortDef( 'SetNodeEquation_bn', 'Sets the equation giving the probability of this node conditioned on its parent nodes, or the value of this node as a function of its parents' );
shortDef[ii++] = new ShortDef( 'SetNodeExperience_bn', 'Sets the experience of this node as a function of its parent nodes.' );
shortDef[ii++] = new ShortDef( 'SetNodeFuncReal_bn', 'Sets the real value of this node as a function of its parent nodes.  For discrete nodes, it is better to use SetNodeFuncState_bn' );
shortDef[ii++] = new ShortDef( 'SetNodeFuncState_bn', 'Sets the state value of this node as a function of its parent nodes.  For continuous nodes, it is better to use SetNodeFuncReal_bn' );
shortDef[ii++] = new ShortDef( 'SetNodeInputDelay_bn', 'Sets the "time" delay for a link of a dynamic Bayes net (DBN).' );
shortDef[ii++] = new ShortDef( 'SetNodeInputName_bn', 'Sets the name of this node`s input (i.e., link) identified by the given index' );
shortDef[ii++] = new ShortDef( 'SetNodeKind_bn', 'Set how this node is being used (nature, decision, etc.), defining how this Node (i.e., variable) relates to the agent; submit one of: DISCONNECTED_NODE' );
shortDef[ii++] = new ShortDef( 'SetNodeLevels_bn', 'If this node is for a continuous variable, then this returns a discretization threshold, otherwise it returns an output level' );
shortDef[ii++] = new ShortDef( 'SetNodeName_bn', 'Sets the size-restricted name of this node' );
shortDef[ii++] = new ShortDef( 'SetNodePersistance_bn', 'Sets the time persistance for a node of a dynamic Bayes net (DBN).' );
shortDef[ii++] = new ShortDef( 'SetNodeProbs_bn', 'Sets the probabilities for each state of this node, conditioned on its parent nodes.' );
shortDef[ii++] = new ShortDef( 'SetNodesetColor_bn', 'Sets the color of color' );
shortDef[ii++] = new ShortDef( 'SetNodeStateComment_bn', 'Sets the comment of this node`s state identified by the given index' );
shortDef[ii++] = new ShortDef( 'SetNodeStateName_bn', 'Sets the name of this node`s state identified by the given index' );
shortDef[ii++] = new ShortDef( 'SetNodeStateNames_bn', 'Set all of the state names for this node' );
shortDef[ii++] = new ShortDef( 'SetNodeStateTitle_bn', 'Sets the title of this node`s state identified by the given index' );
shortDef[ii++] = new ShortDef( 'SetNodeTitle_bn', 'Sets the unrestricted label for this node' );
shortDef[ii++] = new ShortDef( 'SetNodeUserData_bn', 'Attaches an arbitrary data object to this node' );
shortDef[ii++] = new ShortDef( 'SetNodeUserField_bn', 'Sets the user-defined data associated with name for this node' );
shortDef[ii++] = new ShortDef( 'SetNodeVisPosition_bn', 'Sets the x and y pixel values of the center of the node in the net diagram (assuming a visual display exists)' );
shortDef[ii++] = new ShortDef( 'SetNodeVisStyle_bn', 'Sets the style of the node, should it be displayed.' );
shortDef[ii++] = new ShortDef( 'SetNthNode_bn', 'Sets the Nth node of a list to a given node without changing length' );
shortDef[ii++] = new ShortDef( 'SetStreamContents_ns', 'Sets the contents of a memory buffer to be read' );
shortDef[ii++] = new ShortDef( 'SetStreamPassword_ns', 'Sets the encryption/decryption password for a stream' );
shortDef[ii++] = new ShortDef( 'SizeCompiledNet_bn', 'The size and speed of the compiled net (i.e., of the junction tree)' );
shortDef[ii++] = new ShortDef( 'SwitchNodeParent_bn', 'Switches the parent of the identified link with parent.  ' );
shortDef[ii++] = new ShortDef( 'TestWithCaseset_bn', 'Use the case data in cases for the testing operation' );
shortDef[ii++] = new ShortDef( 'UncompileNet_bn', 'Release the resources (junction tree) required for doing fast inference with this net' );
shortDef[ii++] = new ShortDef( 'UndoNetLastOper_bn', 'Undoes the last operation on this net' );
shortDef[ii++] = new ShortDef( 'WriteCaseset_cs', 'Writes all the cases within the caseset file' );
shortDef[ii++] = new ShortDef( 'WriteNet_bn', 'Write this net to the given file stream.  See also `SaveAs`.' );
shortDef[ii++] = new ShortDef( 'WriteNetFindings_bn', 'Write a case from this node list to the given stream' );