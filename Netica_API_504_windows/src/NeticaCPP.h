/* 
 * NeticaCPP.h
 *
 * Header file for C++ Development with Netica API, version 4.12 or later.
 *
 * This file is UNDER DEVELOPMENT
 * Please send any suggestions, or reports of problems, to:  support@norsys.com
 *
 * See file Netica.h for the C interface to Netica API.
 * For more information, see www.norsys.com
 *
 * Copyright (C) 2000-2011 by Norsys Software Corp.  All rights reserved.
 *
 */

#ifndef __NETICA_CPP_H
#define __NETICA_CPP_H

#ifdef __cplusplus

namespace netica {

class environ_ns;
class report_ns;
class stream_ns;
class randgen_ns;
class scripter_ns;
class setting_bn;
class caseset_cs;
class dbmgr_cs;
class net_bn;
class node_bn;
class nodelist_bn;
class sensv_bn;
class tester_bn;
class learner_bn;

class Environ;
class NeticaError;
class Streamer;
class General;
class User;
class Caseset;
class DatabaseManager;
class Node;
class NodeList;
class Net;
class State;
class Value;
class VisualNode;
class Sensitivity;
class Learner;
class NetTester;

#endif /* __cplusplus */

#include "Netica.h"

#ifdef __cplusplus


#define ERR_CHECK_ns	\
	check_for_errors_ns (cenvloc, cenv);

// You can add to these any pre or post processing desired.

#define START_NOTHROW_ns

#define END_NOTHROW_ns

#define START_ns

#define END_ns	\
	ERR_CHECK_ns

#define END_ret_ns	\
	ERR_CHECK_ns	\
	return ret;

#define END_notgen_ns(obj)	\
	check_for_errors_ns (obj.cenvloc, obj.cenv);

#define END_ret_notgen_ns(obj)	\
	check_for_errors_ns (obj.cenvloc, obj.cenv);  \
	return ret;

#define END2_ns	\
	check_for_errors_ns (Environ::getDefault()->getCPtr(), NULL);


static inline void check_for_errors_ns (environ_ns* cenvloc, environ_ns* cenv);

static int NodeCallbackToDelete (const node_bn* node, eventtype_ns what, void* obj, void* data);

extern Environ* GlobalEnv;							// don't use this in your code, use GetEnviron()
inline Environ* GetEnviron() {return GlobalEnv;}	// could call Environ::getDefault() instead

/*=========================== Environ ========================*/

class Environ {
public:
	Environ (bool primitive, const char license[], Environ* env = 0, const char locn[] = 0){	// normally use other Environ constructor
		START_NOTHROW_ns
		cenv = NewNeticaEnviron_ns (license, env ? env->cenv : 0, locn);
		cenvloc = env ? env->cenv : cenv;
		SetEnvironUserData_ns (cenv, 0, this);
		SetLanguage_ns (cenv, "C++");
		if (GlobalEnv == 0)  GlobalEnv = this;
		END_NOTHROW_ns			// cenv is not yet init, so we cant check for errors yet
		}
	Environ (const char license[], Environ* env = 0, const char locn[] = 0);
	~Environ(){
		START_NOTHROW_ns
		if (cenv){				// will be NULL if close() already called
			char mesg[MESG_LEN_ns];
			CloseNetica_bn (cenv, mesg);
			cenv = 0;
			if (GlobalEnv == this)  GlobalEnv = 0;
			}
		END_NOTHROW_ns
		}
	static Environ* getDefault(){
		return GetEnviron();
		}
	int init (char mesg[] = NULL){
		START_ns
		int ret = InitNetica2_bn (cenv, mesg);
		END_ret_ns
		}
	int close (char mesg[] = NULL){
		START_NOTHROW_ns
		if (GlobalEnv == this)  GlobalEnv = 0;
		int res = 0;
		if (cenv) res = CloseNetica_bn (cenv, mesg);
		cenv = 0;
		// if (res < 0) throw NeticaError (0, mesg);
		END_NOTHROW_ns
		return res;
		}
	int getVersion (const char** version = NULL) const	{
		START_ns
		int ret = GetNeticaVersion_bn (cenv, version);
		END_ret_ns
		}
	checking_ns setArgumentChecking (checking_ns setting){
		START_ns
		checking_ns ret = ArgumentChecking_ns (setting, cenv);
		END_ret_ns
		}
	checking_ns getArgumentChecking() const {
		START_ns
		checking_ns ret = ArgumentChecking_ns ((checking_ns)QUERY_ns, cenv);
		END_ret_ns
		}
	bool setUserAllowed (bool allowed){
		START_ns
		bool ret = (UserAllowed_ns (cenv, allowed ? 1 : 0) != 0);
		END_ret_ns
		}
	bool getUserAllowed() const {
		START_ns
		bool ret = (UserAllowed_ns (cenv, QUERY_ns) != 0);
		END_ret_ns
		}
	double setMemoryUsageLimit (double max_mem){
		START_ns
		double ret = LimitMemoryUsage_ns (max_mem, cenv);
		END_ret_ns
		}
	double getMemoryUsageLimit() const {
		START_ns
		double ret = LimitMemoryUsage_ns (QUERY_ns, cenv);
		END_ret_ns
		}
	int setCaseFileDelimChar (int newchar){
		START_ns
		int ret = SetCaseFileDelimChar_ns (newchar, cenv);
		END_ret_ns
		}
	int getCaseFileDelimChar() const {
		START_ns
		int ret = SetCaseFileDelimChar_ns (QUERY_ns, cenv);
		END_ret_ns
		}
	int setMissingDataChar (int newchar){
		START_ns
		int ret = SetMissingDataChar_ns (newchar, cenv);
		END_ret_ns
		}
	int getMissingDataChar() const {
		START_ns
		int ret = SetMissingDataChar_ns (QUERY_ns, cenv);
		END_ret_ns
		}
	environ_ns* getCPtr() const {
		return this ? cenv : 0;
		}

	void clearErrors (errseverity_ns severity){			//- remove
		START_ns
		ClearErrors_ns (cenv, severity);
		END_ns
		}
private:
	Environ (const Environ& n);		// private to prevent default cctor.  To work with Environs that already exist, use an Environ ref instead: Environ&

	environ_ns* cenv;
	environ_ns* cenvloc;
	friend class NeticaError;
	friend class Streamer;
	friend class Net;
	friend class Caseset;			// for access to cenv, cenvloc
	friend class DatabaseManager;	// ditto
	friend class Learner;			// ditto
	};


/*=========================== NeticaError ========================*/

class NeticaError {
public:
	NeticaError (Environ* env, const char mesg[], int number = 1, errseverity_ns severity = ERROR_ERR){
		START_NOTHROW_ns
		if (!env)  env = GetEnviron();
		cenv = env->cenv;
		// c_err = NewError_ns (cenv, number, severity, mesg);
		c_err = 0;
		my_idnum = number;
		my_severity = severity;
		load_mesg (mesg);
		ClearError_ns (c_err);
		c_err = 0;
		END_NOTHROW_ns
		}
	NeticaError (environ_ns* env, const char mesg[], int number = 1, errseverity_ns severity = ERROR_ERR){
		START_NOTHROW_ns
		if (!env)  env = GetEnviron()->cenv;
		cenv = env;
		// c_err = NewError_ns (cenv, number, severity, mesg);
		c_err = 0;
		my_idnum = number;
		my_severity = severity;
		load_mesg (mesg);
		if (env) ClearError_ns (c_err);
		c_err = 0;
		END_NOTHROW_ns
		}
	NeticaError (environ_ns* env){	// meant to be used only by check_for_errors_ns
		START_NOTHROW_ns
		cenv = env;
		c_err = GetError_ns (cenv, ERROR_ERR, 0);
		my_idnum = ErrorNumber_ns (c_err);
		my_severity = ErrorSeverity_ns (c_err);
		load_mesg (ErrorMessage_ns (c_err));
		ClearError_ns (c_err);
		c_err = 0;
		END_NOTHROW_ns
		}
	~NeticaError(){
		START_NOTHROW_ns
		if (c_err) ClearError_ns (c_err);
		END_NOTHROW_ns
		}
	int getIdNumber() const {
		return my_idnum;
		}
	const char* getMessage() const	{
		return my_mesg;
		}
	errseverity_ns getSeverity() const {
		return my_severity;
		}
	bool isInCategory (errcond_ns cond) const {		//= doesnt work
		START_NOTHROW_ns
		bool ret = (ErrorCategory_ns (cond, c_err) == TRUE);
		END_NOTHROW_ns
		return ret;
		}
	Environ& getEnviron() const {
		return *static_cast<Environ*>(GetEnvironUserData_ns (cenv, 0));
		}
	report_ns* getCPtr() const {
		return this ? c_err : 0;
		}
private:
	//- NeticaError (const NeticaError& n);		// private to prevent default cctor.  To work with NeticaErrors that already exist, use a NeticaError ref instead: NeticaError&
	enum {max_mesg_size = MESG_LEN_ns};

	void load_mesg (const char mesg[]){
		const char* p = mesg;
		const char* pend = p + max_mesg_size;
		char* my_mesgp = my_mesg;
		while (*p != 0 && p < pend)  *my_mesgp++ = *p++;
		*my_mesgp = 0;
		}

	environ_ns* cenv;
	report_ns* c_err;
	char my_mesg[max_mesg_size+2];
	int my_idnum;
	errseverity_ns my_severity;
	};

static inline void check_for_errors_ns (environ_ns* cenvloc, environ_ns* cenv){
	// We could do the below for safety, but no dtors should EVER call this anyway, and it reduces efficiency of this critical func
	// if (std::uncaught_exception())  return;						// if we are stack unwinding (ie, this was called by dtor), we don't want to throw another exception, or program will terminate()
	report_ns* err = GetError_ns (cenvloc, ERROR_ERR, 0);
	//- if (err)  throw new NeticaError (cenvloc);
	if (err)  throw NeticaError (cenvloc);							//- should have option to avoid throws
	if (cenv != cenvloc && cenv){
		err = GetError_ns (cenv, ERROR_ERR, 0);
		if (err)  throw NeticaError (cenv);
		}
	}


/*=========================== Streamer ========================*/

class Streamer {
public:
	Streamer (const char filename[], Environ* env = 0, const char access[] = 0){
		START_ns
		if (!env)  env = GetEnviron();
		cenv = env->cenv;
		cenvloc = env->cenvloc;
		cstream = NewFileStream_ns (filename, cenv, access);
		END_ns
		}
	Streamer (Environ* env = 0, const char name[] = 0, const char access[] = 0){
		START_ns
		if (!env)  env = GetEnviron();
		cenv = env->cenv;
		cenvloc = env->cenvloc;
		cstream = NewMemoryStream_ns (name, cenv, access);
		END_ns
		}
	~Streamer (){
		START_NOTHROW_ns
		DeleteStream_ns (cstream);
		END_NOTHROW_ns
		}
	void setPassword (const char password[]) const {
		START_ns
		SetStreamPassword_ns (cstream, password);
		END_ns
		}
	const char* getContents (long length[] = 0) const {
		START_ns
		const char* ret = GetStreamContents_ns (cstream, length);
		END_ret_ns
		}
	void setContents (const char string[], long length, bool copy) const {		// LENGTH does not include null termination
		START_ns
		SetStreamContents_ns (cstream, string, length, copy ? TRUE : FALSE);
		END_ns
		}
	Environ& getEnviron() const {
		return *static_cast<Environ*>(GetEnvironUserData_ns (cenv, 0));
		}
	stream_ns* getCPtr() const {
		return this ? cstream : 0;
		}
private:
	Streamer (const Streamer& n);		// private to prevent default cctor.  To work with Streams that already exist, use a Streamer ref instead: Streamer&

	stream_ns* cstream;
	environ_ns* cenv;
	environ_ns* cenvloc;
	friend class Net;
	friend class NodeList;
	};


/*========================= General ========================*/

class General {
public:
	Environ& getEnviron() const {
		return *static_cast<Environ*>(GetEnvironUserData_ns (cenv, 0));
		}
protected:
	environ_ns* cenv;
	environ_ns* cenvloc;
private:
	General (const General& gen){
		cenv = gen.cenv;
		cenvloc = gen.cenvloc;
		}
	General (environ_ns* cenvA, environ_ns* cenvlocA){
		cenv = cenvA;
		cenvloc = cenvlocA;
		}
	friend class Net;		// for General ctor
	friend class Node;		// for General ctor
	friend class NodeList;	// for General ctor
	friend class State;		// for General ctor
	friend class Value;		// for access to cenv, cenvloc
	friend class VisualNode;	// for access to cenv, cenvloc
	friend class Caseset;		// for access to cenv, cenvloc
	friend class DatabaseManager;	// for access to cenv, cenvloc
	friend class Sensitivity;	// for access to cenv, cenvloc
	};


/*========================= Caseset ========================*/

class Caseset : public General {
public:
	Caseset (const char* name = 0, Environ* env = 0):
		General (env ? env->cenv : GetEnviron()->cenv, env ? env->cenvloc : GetEnviron()->cenvloc){
		START_ns
		ccases = NewCaseset_cs (name, cenv);
		END_ns
		}
	~Caseset (){
		START_NOTHROW_ns
		DeleteCaseset_cs (ccases);
		END_NOTHROW_ns
		}
	void addCases (const Streamer& file, double degree = 1.0, const char* options = 0){
		START_ns
		AddFileToCaseset_cs (ccases, file.getCPtr(), degree, options);
		END_ns
		}
	void addCases (DatabaseManager dbmgr, double degree, NodeList& nodes, const char* column_names, const char* tables, const char* condition, const char* options = 0);
	void writeCases (const Streamer& file, const char* options){
		START_ns
		WriteCaseset_cs (ccases, file.getCPtr(), options);
		END_ns
		}
	Environ& getEnviron() const {
		return *static_cast<Environ*>(GetEnvironUserData_ns (cenv, 0));
		}
	caseset_cs* getCPtr() const {
		return this ? ccases : 0;
		}
private:
	caseset_cs* ccases;
	};


/*========================= DatabaseManager ========================*/

class DatabaseManager : public General {
public:
	DatabaseManager (const char* connect_str, const char* options = 0, Environ* env = 0):
		General (env ? env->cenv : GetEnviron()->cenv, env ? env->cenvloc : GetEnviron()->cenvloc){
		START_ns
		cdbmgr = NewDBManager_cs (connect_str, options, cenv);
		END_ns
		}
	~DatabaseManager (){
		START_NOTHROW_ns
		DeleteDBManager_cs (cdbmgr);
		END_NOTHROW_ns
		}
	void executeSql (const char* command, const char* options){
		START_ns
		ExecuteDBSql_cs (cdbmgr, command, options);
		END_ns
		}
	void insertFindings (NodeList& nodes, const char* column_names, const char* tables, const char* options);
	void addNodes (Net& net, const char* column_names, const char* tables, const char* condition, const char* options);			// use Net::addNodes instead; this is just for compatability with old Netica-java API
	Environ& getEnviron() const {
		return *static_cast<Environ*>(GetEnvironUserData_ns (cenv, 0));
		}
	dbmgr_cs* getCPtr() const {
		return this ? cdbmgr : 0;
		}
private:
	dbmgr_cs* cdbmgr;
	};


/*========================== NodeList ========================*/

class NodeList {
public:
	NodeList (Net& net, int length = 0);
	NodeList (const NodeList& list){
		START_ns
		cenv = list.cenv;
		cenvloc = list.cenvloc;
		owns = list.owns;
		clist = owns ? DupNodeList_bn (list.clist) : list.clist;
		END_ns
		}
	NodeList (const nodelist_bn* clistA, bool ownsA, environ_ns* cenvA = 0){
		START_ns
		if (!cenvA)  cenvA = GetEnviron()->getCPtr();
		cenv = cenvA;
		cenvloc = cenvA;					//=
		owns = ownsA;
		clist = owns ? DupNodeList_bn (clistA) : (nodelist_bn*) clistA;		//= fix cast
		END_ns
		}
	NodeList (nodelist_bn* clistA, bool ownsA, environ_ns* cenvA = 0){
		START_ns
		if (!cenvA)  cenvA = GetEnviron()->getCPtr();
		cenv = cenvA;
		cenvloc = cenvA;					//=
		owns = ownsA;
		clist = owns ? DupNodeList_bn (clistA) : clistA;
		END_ns
		}
	~NodeList (){
		START_NOTHROW_ns
		if (owns)  DeleteNodeList_bn (clist);
		END_NOTHROW_ns
		}
	void clear (){
		START_ns
		ClearNodeList_bn (clist);
		END_ns
		}
	int size () const {
		START_ns
		int ret = LengthNodeList_bn (clist);
		END_ret_ns
		}
	void add (Node& node);
	void insert (int index, Node& node);
	void erase (int index){
		START_ns
		RemoveNthNode_bn (clist, index);
		END_ns
		}
	Node* getNode (int index) const;
	Node* operator[] (int index) const;
	void setNth (int index, const Node* node);
	int getIndex (const Node& node, int start_index = 0);
	nodelist_bn* getCPtr() const {
		return this ? clist : 0;
		}
private:
	nodelist_bn* clist;
	bool owns;
	environ_ns* cenv;
	environ_ns* cenvloc;

	friend class NetTester;	// for access to cenv, cenvloc
	};


/*=========================== Net ========================*/

class Net : public General {
public:
	Net (const char name[], Environ* env = 0):
		General (env ? env->cenv : GetEnviron()->cenv, env ? env->cenvloc : GetEnviron()->cenvloc){
		START_ns
		cnet = NewNet_bn (name, cenv);
		my_userdata = 0;
		END_ns
		}
	Net (const Net& net, const char new_name[] = 0, Environ* env = 0, const char options[] = 0):
		General (env ? env->cenv : net.cenv, env ? env->cenvloc : net.cenvloc){
		START_ns
		cnet = CopyNet_bn (net.cnet, new_name, cenv, options);
		my_userdata = 0;
		END_ns
		}
	Net (Streamer& stream, int control = NO_WINDOW):
		General (stream.cenv, stream.cenvloc){
		START_ns
		cenv = stream.cenv;
		cenvloc = stream.cenvloc;
		cnet = ReadNet_bn (stream.cstream, control);
		my_userdata = 0;
		END_ns
		}
	~Net (){
		START_NOTHROW_ns
		DeleteNet_bn (cnet);
		END_NOTHROW_ns
		}
	void setName (const char name[]){
		START_ns
		SetNetName_bn (cnet, name);
		END_ns
		}
	int setAutoUpdate (int auto_update){
		START_ns
		int ret = SetNetAutoUpdate_bn (cnet, auto_update);
		END_ret_ns
		}
	void setElimOrder (const NodeList& elim_order){
		START_ns
		SetNetElimOrder_bn (cnet, elim_order.getCPtr());
		END_ns
		}
	void setTitle (const char title[]){
		START_ns
		SetNetTitle_bn (cnet, title);
		END_ns
		}
	void setComment (const char comment[]){
		START_ns
		SetNetComment_bn (cnet, comment);
		END_ns
		}
	void setUserField (const char name[], const void* data, int length){
		START_ns
		SetNetUserField_bn (cnet, name, data, length, 0);
		END_ns
		}
	const char* getName () const {
		START_ns
		const char* ret = GetNetName_bn (cnet);
		END_ret_ns
		}
	int isAutoUpdate () const {
		START_ns
		int ret = GetNetAutoUpdate_bn (cnet);
		END_ret_ns
		}
	const NodeList getElimOrder() const {
		START_ns
		const NodeList ret = NodeList (GetNetElimOrder_bn (cnet), false, cenv);
		END_ret_ns
		}
	const char* getTitle () const {
		START_ns
		const char* ret = GetNetTitle_bn (cnet);
		END_ret_ns
		}
	const char* getLabel (const char* options = NULL) const {
		START_ns
		const char* ret = GetNetTitle_bn (cnet);
		if (!ret)  ret = GetNetName_bn (cnet);
		END_ret_ns
		}
	const char* getComment () const {
		START_ns
		const char* ret = GetNetComment_bn (cnet);
		END_ret_ns
		}
	const char* getUserField (const char name[], int* length) const {
		START_ns
		const char* ret = GetNetUserField_bn (cnet, name, length, 0);
		END_ret_ns
		}
	void getNthUserField (int index, const char** name, const char** value, int* length) const {
		START_ns
		GetNetNthUserField_bn (cnet, index, name, value, length, 0);
		END_ns
		}
	const NodeList getNodes (const char options[] = 0) const;
	Node* getNode (const char name[]) const;
	User user();
	Node& node (const char name[]) const {
		Node* n = getNode (name);
		if (n == 0)  throw NeticaError (cenv, "node not present in net", 999);
		return *n;
		}
	void absorbNodes (NodeList& nodes){
		START_ns
		AbsorbNodes_bn (nodes.getCPtr());
		END_ns
		}
	const NodeList copyNodes (const NodeList& nodes, Net& new_net, const char* options){
		START_ns
		const NodeList ret (CopyNodes_bn (nodes.getCPtr(), new_net.getCPtr(), options), true, cenv);
		END_ret_ns
		}
	void getRelatedNodes (NodeList related_nodes, const char relation[], const NodeList nodes) const;
	const char* createCustomReport (const NodeList& sel_nodes, const char templat[], const char options[]){
		START_ns
		const char* ret = CreateCustomReport_bn (cnet, sel_nodes.getCPtr(), templat, options);
		END_ret_ns
		}
	caseposn_bn writeFindings (Streamer& stream, const NodeList* nodes = 0, long ID_num = -1, double freq = 1.0){
		START_ns
		caseposn_bn ret = WriteNetFindings_bn (nodes ? nodes->getCPtr(): GetNetNodes2_bn (cnet, 0), stream.cstream, ID_num, freq);
		END_ret_ns
		}
	void readFindings (caseposn_bn* case_posn, Streamer& stream, bool add, const NodeList* nodes = 0, long* ID_num = 0, double* freq = 0){
		START_ns
		ReadNetFindings2_bn (case_posn, stream.cstream, add, nodes ? nodes->getCPtr(): GetNetNodes2_bn (cnet, 0), ID_num, freq);
		END_ns
		}
	void write (Streamer& file) const {
		START_ns
		WriteNet_bn (cnet, file.cstream);
		END_ns
		}
	void reviseCPTsByFindings (const NodeList& nodes, double degree){
		START_ns
		ReviseCPTsByFindings_bn (nodes.getCPtr(), 0, degree = 1.0);
		END_ns
		}
	void compile (){
		START_ns
		CompileNet_bn (cnet);
		END_ns
		}
	void retractFindings (){
		START_ns
		RetractNetFindings_bn (cnet);
		END_ns
		}
	double getFindingsProbability (){
		START_ns
		double ret = FindingsProbability_bn (cnet);
		END_ret_ns
		}
	int generateRandomCase (const NodeList* nodes = 0, sampling_bn method = DEFAULT_SAMPLING, double num = 100, randgen_ns* gen = 0){
		START_ns
		int ret = GenerateRandomCase_bn (nodes ? nodes->getCPtr() : GetNetNodes2_bn (cnet, 0), method, num, gen);
		END_ret_ns
		}
	void addNodes (DatabaseManager& dbmgr, const char* column_names, const char* tables, const char* condition, const char* options){
		START_ns
		AddNodesFromDB_bn (dbmgr.getCPtr(), cnet, column_names, tables, condition, options);
		END_ns
		}
	const char* controlCaching (const char command[], const char value[], const NodeList* nodes = 0){
		START_ns
		const char* ret = ControlNetCaching_bn (cnet, command, value, nodes->getCPtr());
		END_ret_ns
		}
	net_bn* getCPtr() const {
		return this ? cnet : 0;
		}
	void setUserData (void* data){
		my_userdata = data;
		}
	void* getUserData () const {
		return my_userdata;
		}
private:
	net_bn* cnet;
	void* my_userdata;
	friend class Node;
	};



/*=========================== Node ========================*/


class Node : public General {
public:
	Node (const char name[], int num_states, Net& net):
		General (net){
		START_ns
		my_userdata = 0;
		cnode = NewNode_bn (name, num_states, net.cnet);
		ERR_CHECK_ns
		SetNodeUserData_bn (cnode, 0, this);
		END_ns
		}
	Node (const char name[], const char state_names[], Net& net):
		General (net){
		START_ns
		my_userdata = 0;
		int numstates = 1;
		const char* p;
		for (p = state_names;  *p != 0;  ++p)
			if (*p == ',')  numstates++;
		if (numstates > 1 && *(p-1) == ',')  numstates--;	// trailing comma
		cnode = NewNode_bn (name, numstates, net.cnet);
		ERR_CHECK_ns
		SetNodeUserData_bn (cnode, 0, this);
		SetNodeStateNames_bn (cnode, state_names);
		END_ns
		}
	~Node (){
		START_NOTHROW_ns
		if (cnode)  SetNodeUserData_bn (cnode, 0, 0);
		END_NOTHROW_ns
		}
	void remove (){
		START_ns
		DeleteNode_bn (cnode);
		cnode = 0;
		END_ns
		}
	void setName (const char name[]){
		START_ns
		SetNodeName_bn (cnode, name);
		END_ns
		}
	void setKind (nodekind_bn kind){
		START_ns
		SetNodeKind_bn (cnode, kind);
		END_ns
		}
	void setStateNames (const char state_names[]){
		START_ns
		SetNodeStateNames_bn (cnode, state_names);
		END_ns
		}
	void setLevels (int num_states, const level_bn* levels){
		START_ns
		SetNodeLevels_bn (cnode, num_states, levels);
		END_ns
		}
	void setInputName (int link_index, const char link_name[]){
		START_ns
		SetNodeInputName_bn (cnode, link_index, link_name);
		END_ns
		}
	void setProbs (const state_bn parent_states[], const prob_bn probs[]){
		START_ns
		SetNodeProbs_bn (cnode, parent_states, probs);
		END_ns
		}
	void setFuncState (const state_bn parent_states[], int func_value){
		START_ns
		SetNodeFuncState_bn (cnode, parent_states, func_value);
		END_ns
		}
	void setFuncReal (const state_bn parent_states[], double func_value){
		START_ns
		SetNodeFuncReal_bn (cnode, parent_states, func_value);
		END_ns
		}
	void setExperience (const state_bn parent_states[], double experience){
		START_ns
		SetNodeExperience_bn (cnode, parent_states, experience);
		END_ns
		}
	void deleteTables (){
		START_ns
		DeleteNodeTables_bn (cnode);
		END_ns
		}
	void setTitle (const char title[]){
		START_ns
		SetNodeTitle_bn (cnode, title);
		END_ns
		}
	void setComment (const char comment[]){
		START_ns
		SetNodeComment_bn (cnode, comment);
		END_ns
		}
	void setUserField (const char name[], const void* data, int length){
		START_ns
		SetNodeUserField_bn (cnode, name, data, length, 0);
		END_ns
		}
	Net& getNet () const {
		START_ns
		net_bn* net = GetNodeNet_bn (cnode);
		ERR_CHECK_ns
		Net& ret = *static_cast<Net*>(GetNetUserData_bn (net, 0));
		END_ret_ns
		}
	const char* getName () const {
		START_ns
		const char* ret = GetNodeName_bn (cnode);
		END_ret_ns
		}
	nodekind_bn getKind () const {
		START_ns
		nodekind_bn ret = GetNodeKind_bn (cnode);
		END_ret_ns
		}
	nodetype_bn getType () const {
		START_ns
		nodetype_bn ret = GetNodeType_bn (cnode);
		END_ret_ns
		}
	int getNumStates () const {
		START_ns
		int ret = GetNodeNumberStates_bn (cnode);
		END_ret_ns
		}
	State state (int index) const;
	State state (const char name[]) const;
	const level_bn* getLevels () const {
		START_ns
		const level_bn* ret = GetNodeLevels_bn (cnode);
		END_ret_ns
		}
	const char* getTitle () const {
		START_ns
		const char* ret = GetNodeTitle_bn (cnode);
		END_ret_ns
		}
	int getLabel (unsigned short label[], int max_chars, const char* options = NULL) const {
		START_ns
		int ret = GetNodeLabel_bn (cnode, label, max_chars, options);
		END_ret_ns
		}
	const char* getComment () const {
		START_ns
		const char* ret = GetNodeComment_bn (cnode);
		END_ret_ns
		}
	int addLink (Node& parent){
		START_ns
		int ret = AddLink_bn (parent.cnode, cnode);
		END_ret_ns
		}
	void deleteLink (int link_index){
		START_ns
		DeleteLink_bn (link_index, cnode);
		END_ns
		}
	void deleteLink (Node& parent){
		START_ns
		int link_index = IndexOfNodeInList_bn (parent.cnode, GetNodeParents_bn (cnode), 0);
		ERR_CHECK_ns
		if (link_index == -1)  throw NeticaError (cenv, "node passed to deleteLink is not a parent", 999);
		DeleteLink_bn (link_index, cnode);
		END_ns
		}
	void switchParent (int link_index, Node& new_parent){
		START_ns
		SwitchNodeParent_bn (link_index, cnode, new_parent.cnode);
		END_ns
		}
	void reverseLink (Node& parent){
		START_ns
		ReverseLink_bn (parent.cnode, cnode);
		END_ns
		}
	const NodeList getParents () const {
		START_ns
		const NodeList ret (GetNodeParents_bn (cnode), false, cenv);;
		END_ret_ns
		}
	const NodeList getChildren () const {
		START_ns
		const NodeList ret (GetNodeChildren_bn (cnode), false, cenv);
		END_ret_ns
		}
	bool isRelated (const char relation[], const Node& node){
		START_ns
		bool ret = IsNodeRelated_bn (cnode, relation, node.cnode) == TRUE;
		END_ret_ns
		}
	void getRelatedNodes (const char relation[], NodeList related_nodes) const;
	const char* getNodeInputName (int link_index) const {
		START_ns
		const char* ret = GetNodeInputName_bn (cnode, link_index);
		END_ret_ns
		}
	int getInputIndex (const char name[]) const {
		START_ns
		int ret = GetInputNamed_bn (name, cnode);
		END_ret_ns
		}
	bool hasTable (bool* complete) const {
		START_ns
		bool_ns cc;
		bool ret = HasNodeTable_bn (cnode, complete ? &cc : 0) == TRUE;
		if (complete) *complete = (cc == TRUE);
		END_ret_ns
		}
	bool isDetermin () const {
		START_ns
		bool ret = IsNodeDeterministic_bn (cnode) == TRUE;
		END_ret_ns
		}
	const prob_bn* getProbs (const int parent_states[]) const {
		START_ns
		const prob_bn* ret = GetNodeProbs_bn (cnode, parent_states);
		END_ret_ns
		}
	int getFuncState (const state_bn parent_states[]) const {
		START_ns
		int ret = GetNodeFuncState_bn (cnode, parent_states);
		END_ret_ns
		}
	double getFuncReal (const state_bn parent_states[]) const {
		START_ns
		double ret = GetNodeFuncReal_bn (cnode, parent_states);
		END_ret_ns
		}
	double getExperience (const state_bn parent_states[]) const {
		START_ns
		double ret = GetNodeExperience_bn (cnode, parent_states);
		END_ret_ns
		}
	const char* getUserField (const char name[], int* length) const {
		START_ns
		const char* ret = GetNodeUserField_bn (cnode, name, length, 0);
		END_ret_ns
		}
	void getNthUserField (int index, const char** name, const char** value, int* length) const {
		START_ns
		GetNodeNthUserField_bn (cnode, index, name, value, length, 0);
		END_ns
		}
	void fadeCPTable (double degree){
		START_ns
		FadeCPTable_bn (cnode, degree);
		END_ns
		}
	Value finding ();
	VisualNode visual();
	User user();
	int calcState (){
		START_ns
		int ret = CalcNodeState_bn (cnode);
		END_ret_ns
		}
	double calcValue (){
		START_ns
		double ret = CalcNodeValue_bn (cnode);
		END_ret_ns
		}
	bool isBeliefUpdated () const {
		START_ns
		bool ret = IsBeliefUpdated_bn (cnode) == TRUE;
		END_ret_ns
		}
	const prob_bn* getBeliefs (){
		START_ns
		const prob_bn* ret = GetNodeBeliefs_bn (cnode);
		END_ret_ns
		}
	double getBelief (const char state_name[]){
		START_ns
		int state = GetStateNamed_bn (state_name, cnode);
		ERR_CHECK_ns
		double ret = GetNodeBeliefs_bn (cnode) [state];
		END_ret_ns
		}
	const util_bn* getExpectedUtils (){
		START_ns
		const util_bn* ret = GetNodeExpectedUtils_bn (cnode);
		END_ret_ns
		}
	double getExpectedValue (double* std_dev){
		START_ns
		double ret = GetNodeExpectedValue_bn (cnode, std_dev, 0, 0);
		END_ret_ns
		}
	static Node& nativeToNode (node_bn* native, const General& gen){
		Node* ret = static_cast<Node*>(GetNodeUserData_bn (native, 0));
		if (!ret)  ret = new Node (native, gen);
		AddNodeListener_bn (native, NodeCallbackToDelete, 0, -1);		// this function created the Node (with 'new' above), so it is responsible for freeing it
		return *ret;
		}
	node_bn* getCPtr() const {
		return this ? cnode : 0;
		}
	void setUserData (void* data){
		my_userdata = data;
		}
	void* getUserData () const {
		return my_userdata;
		}

private:
	Node (const Node& n);		// private to prevent default cctor.  To work with nodes that already exist, use a Node ref instead: Node&

	Node (node_bn* existing_node, const General& gen):					// for use only by nativeToNode
		General (gen){
		cnode = existing_node;
		my_userdata = 0;
		SetNodeUserData_bn (cnode, 0, this);
		}

	node_bn* cnode;
	void* my_userdata;
	friend class Net;		// getNode
	};


static int NodeCallbackToDelete (const node_bn* node, eventtype_ns what, void* obj, void* data){
	// printf ("  Callback %d for node %s\n", what, GetNodeName_bn (node));	// GetNodeName_bn should not be locked out, but someday funcs that modify will be
	if (what == REMOVE_EVENT){
		Node* n = static_cast<Node*>(GetNodeUserData_bn (node, 0));
		delete n;
		}
	return 0;
	}


/*========================== State ========================*/

class State {
public:
	~State (){}
	int getIndex() const {
		return index;
		}
	const Node& getNode() const {
		return node;
		}
	const Environ& getEnviron() const {
		return node.getEnviron();
		}
	void remove(){			// Netica-Java calls this 'delete', but that is a reserved word in C++
		START_ns
		RemoveNodeState_bn (node.getCPtr(), index);
		END_notgen_ns (node)
		}
	double getNumeric() const {
		START_ns
		double ret = GetNodeLevels_bn (node.getCPtr()) [index];
		END_ret_notgen_ns (node)
		}
	void setNumeric (double value){
		START_ns
		int numstates = GetNodeNumberStates_bn (node.getCPtr());
		const double* oldlevels = GetNodeLevels_bn (node.getCPtr());
		double* levels = new double [numstates];
		for (int st = 0;  st < numstates;  ++st)
			levels[st] = oldlevels[st];
		levels[index] = value;
		SetNodeLevels_bn (node.getCPtr(), numstates, levels);
		delete[] levels;
		END_notgen_ns (node)
		}
	const char* getName() const {
		START_ns
		const char* ret = GetNodeStateName_bn (node.getCPtr(), index);
		END_ret_notgen_ns (node)
		}
	void setName (const char name[]){
		START_ns
		SetNodeStateName_bn (node.getCPtr(), index, name);
		END_notgen_ns (node)
		}
	const char* getTitle() const {
		START_ns
		const char* ret = GetNodeStateTitle_bn (node.getCPtr(), index);
		END_ret_notgen_ns (node)
		}
	void setTitle (const char title[]){
		START_ns
		SetNodeStateTitle_bn (node.getCPtr(), index, title);
		END_notgen_ns (node)
		}
	int getLabel (unsigned short label[], int max_chars, const char* options = NULL) const {
		START_ns
		int ret = GetNodeStateLabel_bn (node.getCPtr(), index, label, max_chars, options);
		END_ret_notgen_ns (node)
		}
	const char* getComment() const {
		START_ns
		const char* ret = GetNodeStateComment_bn (node.getCPtr(), index);
		END_ret_notgen_ns (node)
		}
	void setComment (const char comment[]){
		START_ns
		SetNodeStateComment_bn (node.getCPtr(), index, comment);
		END_notgen_ns (node)
		}
private:
	int index;
	const Node& node;

	State (int indexA, const Node& nodeA):					// for use only by Node::state
		node (nodeA), index (indexA){
		}
	friend class Node;		// for State ctor
	};


/*========================== Value ========================*/

class Value {
public:
	Value (Node& nodeA, int whatA):
		node (nodeA),
		what (whatA)
		{}
	~Value (){}
	Node& getNode(){
		return Node::nativeToNode (node.getCPtr(), node);
		}
	int getKind (){
		START_ns
		int ret = NO_VALUE;
		if (what == 0){
			int st = GetNodeFinding_bn (node.getCPtr());
			ret = (st >= 0) ?                  STATE_VALUE : 
			      (st == NO_FINDING) ?         NO_VALUE : 
				  (st == NEGATIVE_FINDING) ?   STATE_NOT_VALUE : 
				  (st == LIKELIHOOD_FINDING) ? LIKELIHOOD_VALUE : NO_VALUE;
			}
		END_ret_notgen_ns (node)
		}
	void clear (){
		START_ns
		if (what == 0)  RetractNodeFindings_bn (node.getCPtr());
		END_notgen_ns (node)
		}
	void enterGaussian (double mean, double std_dev){
		START_ns
		EnterGaussianFinding_bn (node.getCPtr(), mean, std_dev);
		END_notgen_ns (node)
		}
	void enterInterval (double lo, double hi){
		START_ns
		EnterIntervalFinding_bn (node.getCPtr(), lo, hi);
		END_notgen_ns (node)
		}
	void enterLikelihood (prob_bn likelihood[]){
		START_ns
		EnterNodeLikelihood_bn (node.getCPtr(), likelihood);
		END_notgen_ns (node)
		}
	void enterCalibration (prob_bn calibration[]){
		START_ns
		EnterNodeCalibration_bn (node.getCPtr(), calibration);
		END_notgen_ns (node)
		}
	void enterReal (double value){
		START_ns
		EnterNodeValue_bn (node.getCPtr(), value);
		END_notgen_ns (node)
		}
	void enterState (state_bn state_index){
		START_ns
		EnterFinding_bn (node.getCPtr(), state_index);
		END_notgen_ns (node)
		}
	void enterState (const char* state_name){
		START_ns
		int state_index = GetStateNamed_bn (state_name, node.getCPtr());
		EnterFinding_bn (node.getCPtr(), state_index);
		END_notgen_ns (node)
		}
	void enterStateNot (state_bn state_index){
		START_ns
		EnterFindingNot_bn (node.getCPtr(), state_index);
		END_notgen_ns (node)
		}
	const prob_bn* getLikelihood(){
		START_ns
		const prob_bn* ret = GetNodeLikelihood_bn (node.getCPtr());
		END_ret_notgen_ns (node)
		}
	double getReal(){
		START_ns
		double ret = GetNodeValueEntered_bn (node.getCPtr());
		END_ret_notgen_ns (node)
		}
	int getState(){
		START_ns
		int ret = GetNodeFinding_bn (node.getCPtr());
		END_ret_notgen_ns (node)
		}
	void setReal (double value){
		START_ns
		RetractNodeFindings_bn (node.getCPtr());
		EnterNodeValue_bn (node.getCPtr(), value);
		END_notgen_ns (node)
		}
	void setState (state_bn state_index){
		START_ns
		RetractNodeFindings_bn (node.getCPtr());
		EnterFinding_bn (node.getCPtr(), state_index);
		END_notgen_ns (node)
		}
	void setState (const char* state_name){
		START_ns
		int state_index = GetStateNamed_bn (state_name, node.getCPtr());
		RetractNodeFindings_bn (node.getCPtr());
		EnterFinding_bn (node.getCPtr(), state_index);
		END_notgen_ns (node)
		}
private:
	Node& node;
	int what;			// 0 means finding
	};

inline Value Node::finding(){
	return Value (*this, 0);
	}


/*======================== VisualNode ======================*/

class VisualNode {
public:
	~VisualNode (){}
	const Node& getNode() const {
		return node;
		}
	const Environ& getEnviron() const {
		return node.getEnviron();
		}
	void setPostion (double x, double y){
		START_ns
		SetNodeVisPosition_bn (node.getCPtr(), 0, x, y);
		END_notgen_ns (node)
		}
	void getPosition (double& x, double& y) const {
		START_ns
		GetNodeVisPosition_bn (node.getCPtr(), 0, &x, &y);
		END_notgen_ns (node)
		}
	void getPosition (int& x, int& y) const {
		START_ns
		double xd, yd;
		GetNodeVisPosition_bn (node.getCPtr(), 0, &xd, &yd);
		x = (int)xd;  y = (int)yd;
		END_notgen_ns (node)
		}
	void setStyle (const char style[]){
		START_ns
		SetNodeVisStyle_bn (node.getCPtr(), 0, style);
		END_notgen_ns (node)
		}
	const char* getStyle() const {
		START_ns
		const char* ret = GetNodeVisStyle_bn (node.getCPtr(), 0);
		END_ret_notgen_ns (node)
		}
private:
	const Node& node;

	VisualNode (const Node& nodeA):					// for use only by Node::visual
		node (nodeA){
		}
	friend class Node;		// for VisualNode ctor
	};


/*========================== User ========================*/

class User {
public:
	User (Node& node):
		obj (&node),
		what (FOR_NODE)
		{}
	User (Net& net):
		obj (&net),
		what (FOR_NET)
		{}
	~User (){}
	void setString (const char field_name[], const char str[]);
	const char* getString (const char field_name[]);
	void setBytes (const char field_name[], const char bytes[], int num_bytes);
	const char* getBytes (const char field_name[], int& num_bytes);
	void setNumber (const char field_name[], double field_value);
	double getNumber (const char field_name[]);
	void setInteger (const char field_name[], int field_value);
	int getInteger (const char field_name[]);
	const char* getNthFieldName (int index);
	void removeField (const char field_name[]);
	void* getReference(){
		if (what == FOR_NET)  return ((Net*)obj)->getUserData();
		if (what == FOR_NODE) return ((Node*)obj)->getUserData();
		return NULL;
		}
	void setReference (void* ref){
		if      (what == FOR_NET)  ((Net*)obj)->setUserData (ref);
		else if (what == FOR_NODE) ((Node*)obj)->setUserData (ref);
		}
private:
	enum obj_type {FOR_NET, FOR_NODE};
	void* obj;
	obj_type what;
	};

inline User Node::user(){
	return User (*this);
	}

inline User Net::user(){
	return User (*this);
	}


/*========================= Sensitivity ========================*/

class Sensitivity {
public:
	Sensitivity (const Node& t_node, const NodeList& v_nodes, int what_calc){
		START_ns
		cenv = t_node.cenv;
		cenvloc = t_node.cenvloc;
		csensv = NewSensvToFinding_bn (t_node.getCPtr(), v_nodes.getCPtr(), what_calc);
		END_ns
		}
	~Sensitivity (){
		START_NOTHROW_ns
		DeleteSensvToFinding_bn (csensv);
		END_NOTHROW_ns
		}
	double getMutualInfo (const Node& varying_node){
		START_ns
		double ret = GetMutualInfo_bn (csensv, varying_node.getCPtr());
		END_ret_ns
		}
	double getVarianceOfReal (const Node& varying_node){
		START_ns
		double ret = GetVarianceOfReal_bn (csensv, varying_node.getCPtr());
		END_ret_ns
		}
	Environ& getEnviron() const {
		return *static_cast<Environ*>(GetEnvironUserData_ns (cenv, 0));
		}
	sensv_bn* getCPtr() const {
		return this ? csensv : 0;
		}
private:
	sensv_bn* csensv;
	environ_ns* cenv;
	environ_ns* cenvloc;
	};


/*========================= Learner ========================*/

class Learner {
public:
	Learner (learn_method_bn method, const char* options = 0, Environ* env = 0){
		START_ns
		if (!env)  env = GetEnviron();
		cenv = env->cenv;
		cenvloc = env->cenvloc;
		method_shadow = method;
		clearn = NewLearner_bn (method, options, cenv);
		END_ns
		}
	~Learner (){
		START_NOTHROW_ns
		DeleteLearner_bn (clearn);
		END_NOTHROW_ns
		}
	void setMaxIterations (int max_iters){
		START_ns
		SetLearnerMaxIters_bn (clearn, max_iters);
		END_ns
		}
	int getMaxIterations (){
		START_ns
		int ret = SetLearnerMaxIters_bn (clearn, QUERY_ns);
		END_ret_ns
		}
	void setMaxTolerance (double log_likeli_tol){
		START_ns
		SetLearnerMaxTol_bn (clearn, log_likeli_tol);
		END_ns
		}
	double getMaxTolerance (){
		START_ns
		double ret = SetLearnerMaxTol_bn (clearn, QUERY_ns);
		END_ret_ns
		}
	learn_method_bn getMethod (){
		return method_shadow;
		}
	void learnCPTs (const NodeList& nodes, const Caseset& cases, double degree = 1.0){
		START_ns
		LearnCPTs_bn (clearn, nodes.getCPtr(), cases.getCPtr(), degree);
		END_ns
		}
	Environ& getEnviron() const {
		return *static_cast<Environ*>(GetEnvironUserData_ns (cenv, 0));
		}
	learner_bn* getCPtr() const {
		return this ? clearn : 0;
		}
private:
	learn_method_bn method_shadow;
	learner_bn* clearn;
	environ_ns* cenv;
	environ_ns* cenvloc;
	};




/*========================= NetTester ========================*/

class NetTester {
public:
	NetTester (const NodeList& test_nodes, const NodeList& unobsv_nodes, int tests){
		START_ns
		cenv = test_nodes.cenv;
		cenvloc = test_nodes.cenvloc;
		ctest = NewNetTester_bn (test_nodes.getCPtr(), unobsv_nodes.getCPtr(), tests);
		END_ns
		}
	~NetTester (){
		START_NOTHROW_ns
		DeleteNetTester_bn (ctest);
		END_NOTHROW_ns
		}
	void testWithCaseset (const Caseset& cases){
		START_ns
		TestWithCaseset_bn (ctest, cases.getCPtr());
		END_ns
		}
	double getErrorRate (const Node& node){
		START_ns
		double ret = GetTestErrorRate_bn (ctest, node.getCPtr());
		END_ret_ns
		}
	double getLogLoss (const Node& node){
		START_ns
		double ret = GetTestLogLoss_bn (ctest, node.getCPtr());
		END_ret_ns
		}
	double getQuadraticLoss (const Node& node){
		START_ns
		double ret = GetTestQuadraticLoss_bn (ctest, node.getCPtr());
		END_ret_ns
		}
	double getConfusion (const State predicted, const State actual){
		START_ns
		double ret = GetTestConfusion_bn (ctest, predicted.getNode().getCPtr(), predicted.getIndex(), actual.getIndex());
		END_ret_ns
		}
	Environ& getEnviron() const {
		return *static_cast<Environ*>(GetEnvironUserData_ns (cenv, 0));
		}
	tester_bn* getCPtr() const {
		return this ? ctest : 0;
		}
private:
	tester_bn* ctest;
	environ_ns* cenv;
	environ_ns* cenvloc;
	};


/*==========================================================*/

inline NodeList::NodeList (Net& net, int length){
	START_ns
	cenv = cenvloc = net.getEnviron().getCPtr();
	clist = NewNodeList2_bn (length, net.getCPtr());
	owns = true;
	END_ns
	}

inline void NodeList::add (Node& node){
	START_ns
	AddNodeToList_bn (node.getCPtr(), clist, LAST_ENTRY);
	END_ns
	}

inline void NodeList::insert (int index, Node& node){
	START_ns
	AddNodeToList_bn (node.getCPtr(), clist, index);
	END_ns
	}

inline Node* NodeList::getNode (int index) const {			// to be compatible with Java version
	START_ns
	node_bn* cnode = NthNode_bn (clist, index);
	Node* ret = cnode ? &Node::nativeToNode (cnode, General (cenv, cenvloc)) : 0;
	END_ret_ns
	}

inline Node* NodeList::operator[] (int index) const {
	START_ns
	node_bn* cnode = NthNode_bn (clist, index);
	Node* ret = cnode ? &Node::nativeToNode (cnode, General (cenv, cenvloc)) : 0;
	END_ret_ns
	}

inline void NodeList::setNth (int index, const Node* node){
	START_ns
	SetNthNode_bn (clist, index, node->getCPtr());
	END_ns
	}

inline int NodeList::getIndex (const Node& node, int start_index){
	START_ns
	int ret = IndexOfNodeInList_bn (node.getCPtr(), clist, start_index);
	END_ret_ns
	}

inline const NodeList Net::getNodes (const char options[]) const {
	START_ns
	const NodeList ret (GetNetNodes2_bn (cnet, options), true, cenv);
	END_ret_ns
	}

inline void Net::getRelatedNodes (NodeList related_nodes, const char relation[], const NodeList nodes) const {
	START_ns
	GetRelatedNodesMult_bn (related_nodes.getCPtr(), relation, nodes.getCPtr());
	END_ns
	}

inline void Node::getRelatedNodes (const char relation[], NodeList related_nodes) const {
	START_ns
	GetRelatedNodes_bn (related_nodes.getCPtr(), relation, cnode);
	END_ns
	}

inline Node* Net::getNode (const char name[]) const {
	START_ns
	node_bn* node = GetNodeNamed_bn (name, cnet);
	Node* ret = node ? &Node::nativeToNode (node, *this) : 0;
	END_ret_ns
	}

inline State Node::state (int index) const {
	return State (index, *this);
	}

inline State Node::state (const char name[]) const {
	START_ns
	int index = GetStateNamed_bn (name, cnode);
	ERR_CHECK_ns
	if (index == -1)  throw NeticaError (cenv, "state not present in node", 999);
	END_ns
	return state (index);
	}

inline void Caseset::addCases (DatabaseManager dbmgr, double degree, NodeList& nodes, const char* column_names, const char* tables, const char* condition, const char* options){
	START_ns
	AddDBCasesToCaseset_cs (ccases, dbmgr.getCPtr(), degree, nodes.getCPtr(), column_names, tables, condition, options);
	END_ns
	}

inline void DatabaseManager::insertFindings (NodeList& nodes, const char* column_names, const char* tables, const char* options){
	START_ns
	InsertFindingsIntoDB_bn (cdbmgr, nodes.getCPtr(), column_names, tables, options);
	END_ns
	}

inline void DatabaseManager::addNodes (Net& net, const char* column_names, const char* tables, const char* condition, const char* options){		// use Net::addNodes instead; this is just for compatability with old Netica-java API
	START_ns
	AddNodesFromDB_bn (cdbmgr, net.getCPtr(), column_names, tables, condition, options);
	END_ns
	}

}  // namespace netica

#endif  /* __cplusplus */

#endif  /* __NeticaCPP_h */
