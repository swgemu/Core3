/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CUSTOMIZATIONVARIABLES_H_
#define CUSTOMIZATIONVARIABLES_H_

#include "system/lang.h"

#include "engine/util/json_utils.h"

// #define DEBUG_CUSTOMIZATION_PARSING 1

class CustomizationVariables : public VectorMap<uint8, int16> {
#if DEBUG_CUSTOMIZATION_PARSING
	bool debug = false;
#endif // DEBUG_CUSTOMIZATION_PARSING
	uint8 unknown = 0;

	Vector<uint8> keyIndex;

public:
	CustomizationVariables();
	~CustomizationVariables();

	CustomizationVariables(const CustomizationVariables& cv);

	CustomizationVariables& operator=(const CustomizationVariables& var);

	CustomizationVariables& operator=(const String& custString);

	void setVariable(uint8 type, int16 value);

	void setVariable(const String& type, int16 value);

	int16 getVariable(uint8 type) const {
		return get(type);
	}

	int16 getVariable(int idx) const {
		return get(idx);
	}

	void getVariable(int idx, uint8& type, int16& value) const;

	int getSize() const {
		return size();
	}

	void parseFromClientString(const String& custString);

	void getData(String& ascii) const;

	bool toString(String& ascii);

	bool parseFromString(const String& str, int version = 0);

	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	friend void to_json(nlohmann::json& j, const CustomizationVariables& vars);

};

#endif /*CUSTOMIZATIONVARIABLES_H_*/
