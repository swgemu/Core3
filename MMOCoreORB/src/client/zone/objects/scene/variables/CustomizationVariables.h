/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CUSTOMIZATIONVARIABLES_H_
#define CUSTOMIZATIONVARIABLES_H_

#include "system/lang.h"

class CustomizationVariables : public VectorMap<uint8, int16> {
	uint8 unknown;

	Vector<uint8> keyIndex;

public:
	CustomizationVariables();
	~CustomizationVariables();

	CustomizationVariables(const CustomizationVariables& cv);

	CustomizationVariables& operator=(const CustomizationVariables& var);

	CustomizationVariables& operator=(const String& custString);

	void setVariable(uint8 type, int16 value);

	void setVariable(const String& type, int16 value);

	int16 getVariable(uint8 type) {
		return get(type);
	}

	int16 getVariable(int idx) {
		return get(idx);
	}

	void getVariable(int idx, uint8& type, int16& value);

	int getSize() {
		return size();
	}

	void parseFromClientString(const String& custString);

	void getData(String& ascii);

	bool toString(String& ascii);

	bool parseFromString(const String& str, int version = 0);

	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

};

#endif /*CUSTOMIZATIONVARIABLES_H_*/
