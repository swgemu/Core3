/*
 * StringParam.h
 *
 *  Created on: 22-feb-2009
 *      Author: TheAnswer
 */

#ifndef STRINGPARAM_H_
#define STRINGPARAM_H_

#include "templates/params/TemplateBase.h"

class StringParam : public TemplateBase<String> {
public:
	StringParam() : TemplateBase<String>(String("")) {
		setType(STRING);
	}

	StringParam(const String& val) : TemplateBase<String>(val) {
		setType(STRING);
	}

	StringParam(const StringParam& p) : TemplateBase<String>(p.get()) {
		setType(STRING);
	}

	virtual String toString() {
		//return get();
		StringBuffer stream;

		stream << "\"" << get() << "\"";

		return stream.toString();
	}

	virtual bool parse(engine::util::Chunk* source) {
		int readCase = source->readByte();

		if (readCase == 1) {
			String val;
			source->readString(val);

			//std::cout << "read case 1:[" << val.toStdString() << "]\n";
			create(val);

			return true;
		}/* else if (readCase == 0) {
			create("");
			std::cout << "read case 0\n";
		} else {
			throw Exception("Unknown case in StringParam::parse(Chunk* dat)");
		}*/

		return false;
	}

	StringParam& operator= (const String& val) {
		create(val);

		return *this;
	}

	String& operator-= (const String& val) {
		return value;
	}
};

#endif /* STRINGPARAM_H_ */
