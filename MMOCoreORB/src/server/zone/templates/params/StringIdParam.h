/*
 * StringIdParam.h
 *
 *  Created on: 22-feb-2009
 *      Author: TheAnswer
 */

#ifndef STRINGIDPARAM_H_
#define STRINGIDPARAM_H_

#include "TemplateBase.h"


#include "primitives/StringParam.h"

class StringIdParamData {
	StringParam file;
	StringParam stringId;
public:
	StringIdParamData(const String& File, const String& id) {
		file = File;
		stringId = id;
	}

	StringIdParamData(const StringParam& File, const StringParam& id) {
		file = File;
		stringId = id;
	}

	StringIdParamData(const StringParam& fullString) {
		String str = fullString.get();

		int idx = str.indexOf(":");

		if (idx != -1) {
			file = str.subString(1, idx);
			stringId = str.subString(idx + 1);
		}
	}

	StringIdParamData() {
		file = "";
		stringId = "";
	}


	bool operator< (const StringIdParamData& val) const {
		return false;
	}

	bool operator> (const StringIdParamData& val) const {
		return false;
	}

	StringIdParamData& operator+= (const StringIdParamData& val) {
		return *this;
	}

	StringIdParamData& operator-= (const StringIdParamData& val) {
		return *this;
	}


	friend class StringIdParam;
};

class StringIdParam : public TemplateBase<StringIdParamData> {

public:
	StringIdParam(const String& str) :  TemplateBase<StringIdParamData>(StringIdParamData(str)) {
		setType(STRINGID);
	}

	StringIdParam() : TemplateBase<StringIdParamData>(StringIdParamData("", "")) {
		setType(STRINGID);
	}

	~StringIdParam() {
	}

	String toString() {
		return getFullString();
	}

	virtual bool parse(Chunk* source) {
		int readCase = source->readByte();

		if (readCase != 1) {
			//create(StringIdParamData());
			return false;
		}

		StringParam stfFile;
		stfFile.parse(source);

		StringParam stringId;
		stringId.parse(source);

		create(StringIdParamData(stfFile, stringId));

		return true;
	}

	StringIdParam& operator=(const String& str) {
		create(StringIdParamData(str));

		return *this;
	}

	/*operator String() const {
		String file = get().file.get();
		//std::cout << "testFile:[" << file.toStdString() << "]\n";

		String stringId = get().stringId.get();
		//std::cout << "testStringId:[" << stringId.toStdString() << "]\n";

		if (stringId.isEmpty())
			return file;

		else return "@" + file + ":" + stringId + ""; 
	}*/

	StringIdParam& operator= (const StringIdParamData& custom) {
		create(custom);

		return *this;
	}

	String getFullString() const {
		String file = get().file.get();
		//std::cout << "testFile:[" << file.toStdString() << "]\n";

		String stringId = get().stringId.get();
		//std::cout << "testStringId:[" << stringId.toStdString() << "]\n";

		if (stringId.isEmpty())
			return get().file.toString();

		else return "@" + file + ":" + stringId;
	}

};


#endif /* STRINGIDPARAM_H_ */
