/*
 * BoolParam.h
 *
 *  Created on: 22-feb-2009
 *      Author: TheAnswer
 */

#ifndef BOOLPARAM_H_
#define BOOLPARAM_H_

#include "templates/params/TemplateBase.h"

class BoolParam : public TemplateBase<bool> {
public:
	BoolParam() : TemplateBase<bool>(false) {
		setType(BOOL);
	}

	BoolParam(bool b) : TemplateBase<bool>(b) {
		setType(BOOL);
	}

	BoolParam& operator= (bool val) {
		create(val);

		return *this;
	}

	String toString() {
		return String::valueOf((int)get());
	}

	static bool toBinaryStream(ObjectOutputStream* stream) {
		return false;
	}

	/*static bool parseFromString(T* address, const sys::lang::String& value, int version = 0) {
		return address->parseFromString(value, version);
	}*/

	static bool parseFromBinaryStream(ObjectInputStream* stream) {
		return false;
	}

	virtual bool parse(engine::util::Chunk* source) {
		uint8 readCase = source->readByte();

		if (readCase == 1) {
			create(source->readByte());

			return true;
		}

		return false;
		/*else {
			create(false);
		}*/
	}
};


#endif /* BOOLPARAM_H_ */
