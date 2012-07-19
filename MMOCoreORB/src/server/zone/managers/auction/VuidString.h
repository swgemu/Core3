/*
 * VuidString.h
 *
 *  Created on: Jun 11, 2012
 *      Author: kyle
 */

#ifndef VUIDSTRING_H_
#define VUIDSTRING_H_

#include "engine/engine.h"

class VuidString : public String {
public:

	VuidString() : String()  {

	}

	~VuidString(){

	}

	VuidString(const String& val) : String(val){

	}

	VuidString(const char* str) : String(str){

	}

	VuidString(const VuidString& val) : String(val) {

	}

	int compareTo(const VuidString& str) const {

		if(beginsWith(str))
			return 0;

		return String::compareTo((String)str);
	}
};

#endif /* VUIDSTRING_H_ */
