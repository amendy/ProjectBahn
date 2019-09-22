#pragma once
#include <iostream>
#include <string>

using namespace std;

class Exception : public exception {

public:
	enum ExceptionType
	{
		//shouldnt ever be thrown
		UNKNOWN_EXCEPTION,
		//same as above but has a string that may provide some info
		HALTESTELLEN_NOT_FOUND,
		//eg file not found
		FILE_OPEN_ERROR,
		//lexical cast type error
		TYPE_PARSE_ERROR,
		//NOTE: in many cases functions only check and throw this in debug
		INVALID_ARG,
		//an error occured while trying to parse data from a file
		FILE_PARSE_ERROR,
	} type;
	static const char* ErrorName[];


	Exception(const string& msg) : exception(), msg_(msg) {};
	~Exception() {};
	string getMessage() const { return(msg_); };


private:
	string msg_;

};