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

	VuidString() {

	}

	~VuidString() {

	}

	VuidString(const String& val) : String(val){

	}

	VuidString(const VuidString& val) : String(val) {

	}

	int compareTo(const VuidString& str) const {

		if(beginsWith(str))
			return 0;

		int compare = String::compareTo((String)str);

		if(compare > 0)
			return 1;

		return -1;
	}
};

#endif /* VUIDSTRING_H_ */
