/* 
 * NeticaCPP.cpp
 *
 * Source file for C++ Development with Netica API, version 4.14 and higher.
 *
 * See file NeticaCPP.h for the header file.
 * For more information, see www.norsys.com
 *
 * Copyright (C) 2000-2011 by Norsys Software Corp.  All rights reserved.
 *
 */
#include <stdio.h>
#pragma warning (disable: 4996)		// using the regular version of Standard Library, instead of Microsoft's secure one, because we need to be portable

#include "NeticaCPP.h"

namespace netica {


Environ* GlobalEnv = 0;


Environ::Environ (const char license[], Environ* env, const char locn[]){
	START_ns
	cenv = NewNeticaEnviron_ns (license, env ? env->cenv : 0, locn);
	cenvloc = env ? env->cenv : cenv;
	if (GlobalEnv == 0)  GlobalEnv = this;
	SetEnvironUserData_ns (cenv, 0, this);
	SetLanguage_ns (cenv, "C++");
	char mesg[MESG_LEN_ns];
	int ret = InitNetica2_bn (cenv, mesg);
	if (ret < 0) throw NeticaError ((Environ*)NULL, mesg, 5, ERROR_ERR);
	END_ns
	}

/*____________________________________________________________________________ StrLen
*/
static int StrLen (const char* str){
	const char* sp = str;
	while (*sp) ++sp;
	return sp - str;
	}

/*______________________________________________________________ User::getNthFieldName
'buf' must have room for at least NAME_MAX_ns characters.
*/
const char* User::getNthFieldName (int index){
	const char* name = NULL;
	START_ns
	if      (what == FOR_NET)  GetNetNthUserField_bn  (((Net*)obj)->getCPtr(),  index, &name, NULL, NULL, 0);
	else if (what == FOR_NODE) GetNodeNthUserField_bn (((Node*)obj)->getCPtr(), index, &name, NULL, NULL, 0);
	END2_ns
	return name;
}

/*_________________________________________________________________ User::removeField
*/
void User::removeField (const char field_name[]){
	START_ns
	if      (what == FOR_NET)  SetNetUserField_bn  (((Net*)obj)->getCPtr(),  field_name, NULL, 0, 0);
	else if (what == FOR_NODE) SetNodeUserField_bn (((Node*)obj)->getCPtr(), field_name, NULL, 0, 0);
	END2_ns
}

/*__________________________________________________________________ User::setString
*/
void User::setString (const char field_name[], const char str[]){
	START_ns
	if      (what == FOR_NET)  SetNetUserField_bn  (((Net*)obj)->getCPtr(),  field_name, str, StrLen (str), 0);
	else if (what == FOR_NODE) SetNodeUserField_bn (((Node*)obj)->getCPtr(), field_name, str, StrLen (str), 0);
	END2_ns
}

/*__________________________________________________________________ User::getString
*/
const char* User::getString (const char field_name[]){
	START_ns
	if      (what == FOR_NET)  return GetNetUserField_bn  (((Net*)obj)->getCPtr(),  field_name, NULL, 0);
	else if (what == FOR_NODE) return GetNodeUserField_bn (((Node*)obj)->getCPtr(), field_name, NULL, 0);
	END2_ns
	return NULL;
}

/*__________________________________________________________________ User::setString
*/
void User::setBytes (const char field_name[], const char bytes[], int num_bytes){
	START_ns
	if      (what == FOR_NET)  SetNetUserField_bn  (((Net*)obj)->getCPtr(),  field_name, bytes, num_bytes, 0);
	else if (what == FOR_NODE) SetNodeUserField_bn (((Node*)obj)->getCPtr(), field_name, bytes, num_bytes, 0);
	END2_ns
}

/*__________________________________________________________________ User::getString
On return, num_bytes will contain the number of bytes.
*/
const char* User::getBytes (const char field_name[], int& num_bytes){
	START_ns
	if      (what == FOR_NET)  return GetNetUserField_bn  (((Net*)obj)->getCPtr(),  field_name, &num_bytes, 0);
	else if (what == FOR_NODE) return GetNodeUserField_bn (((Node*)obj)->getCPtr(), field_name, &num_bytes, 0);
	END2_ns
	return NULL;
}

/*_________________________________________________________________ User::setNumber
*/
void User::setNumber (const char field_name[], double field_value){
	START_ns
	char buf[65];
	sprintf (buf, "%g", field_value);					// The below is better, but if your system doesn't have it, use this instead
	// snprintf (buf, sizeof(buf), "%g", field_value);
	if      (what == FOR_NET)  SetNetUserField_bn  (((Net*)obj)->getCPtr(),  field_name, buf, StrLen (buf), 0);
	else if (what == FOR_NODE) SetNodeUserField_bn (((Node*)obj)->getCPtr(), field_name, buf, StrLen (buf), 0);
	END2_ns
}

/*_________________________________________________________________ GetNetUserNumber
*/
#include <stdlib.h>

double User::getNumber (const char field_name[]){
	START_ns
	int length;
	const char* str;
	if      (what == FOR_NET)  str = GetNetUserField_bn  (((Net*)obj)->getCPtr(),  field_name, &length, 0);
	else if (what == FOR_NODE) str = GetNodeUserField_bn (((Node*)obj)->getCPtr(), field_name, &length, 0);
	if (length == -1)  NewError_ns (Environ::getDefault()->getCPtr(), 905, ERROR_ERR, "There is no user field with that name");
	else {
		char* end;
		double num = strtod (str, &end);
		if (*end != 0)  NewError_ns (Environ::getDefault()->getCPtr(), 906, ERROR_ERR, "The user field did not hold a valid number");
		else return num;
	}
	END2_ns
	return 0;
}

/*____________________________________________________________________ SetNetUserInt
*/
void User::setInteger (const char field_name[], int field_value){
	START_ns
	char buf[22];
	sprintf (buf, "%d", field_value);					// The below is better, but if your system doesn't have it, use this instead
	// snprintf (buf, sizeof(buf), "%d", field_value);
	if      (what == FOR_NET)  SetNetUserField_bn  (((Net*)obj)->getCPtr(),  field_name, buf, StrLen (buf), 0);
	else if (what == FOR_NODE) SetNodeUserField_bn (((Node*)obj)->getCPtr(), field_name, buf, StrLen (buf), 0);
	END2_ns
}

/*____________________________________________________________________ GetNetUserInt
*/
int User::getInteger (const char field_name[]){
	START_ns
	int length;
	const char* str;
	if      (what == FOR_NET)  str = GetNetUserField_bn  (((Net*)obj)->getCPtr(),  field_name, &length, 0);
	else if (what == FOR_NODE) str = GetNodeUserField_bn (((Node*)obj)->getCPtr(), field_name, &length, 0);
	if (length == -1)  NewError_ns (Environ::getDefault()->getCPtr(), 903, ERROR_ERR, "There is no user field with that name");
	else {
		char* end;
		long num = strtol (str, &end, 10);
		if (*end != 0)  NewError_ns (Environ::getDefault()->getCPtr(), 904, ERROR_ERR, "The user field did not hold a valid integer");
		else return num;
	}
	END2_ns
	return 0;
}

/*____________________________________________________________________________ NewError
Like NewError_ns, but with printf style arguments for the error message.
*/
#include <stdarg.h>

report_ns* NewError (int number, errseverity_ns severity, const char* mesg, ...){
	va_list ap;
	char buf[500];
	va_start (ap, mesg);
	// vsprintf (buf, mesg, ap);					// The below is better, but if your system doesn't have it, use this instead (but then be careful mesg is not too long)
	vsnprintf (buf, sizeof (buf), mesg, ap);
	va_end (ap);
	return  NewError_ns (Environ::getDefault()->getCPtr(), number, severity, buf);
}



}  // namespace netica



