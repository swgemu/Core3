/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STRINGIDPARAMETER_H_
#define STRINGIDPARAMETER_H_

#include "engine/engine.h"

#include "StringId.h"

namespace server {
namespace chat {
	class StringIdChatParameter;
}
}

using namespace server::chat;

namespace server {
namespace zone {
namespace objects {
namespace scene {

class SceneObject;

namespace variables {

class StringIdParameter : public Serializable {
protected:
	uint64 pointerParameter;
	StringId stringID;
	UnicodeString customName;

	StringIdParameter() : Serializable() {
		addSerializableVariables();
	}

private:
	inline void addSerializableVariables() {
		addSerializableVariable("stringID", &stringID);
		addSerializableVariable("pointerParameter", &pointerParameter);
		addSerializableVariable("customName", &customName);
	}

public:
	StringIdParameter(const StringIdParameter& par);

#ifdef CXX11_COMPILER
	StringIdParameter(StringIdParameter&& par);
#endif

	StringIdParameter& operator=(const StringIdParameter& par) {
		if (this == &par)
			return *this;

		pointerParameter = par.pointerParameter;
		stringID = par.stringID;
		customName = par.customName;

		return *this;
	}

#ifdef CXX11_COMPILER
	StringIdParameter& operator=(StringIdParameter&& par) {
		if (this == &par)
			return *this;

		pointerParameter = par.pointerParameter;
		stringID = std::move(par.stringID);
		customName = std::move(par.customName);

		return *this;
	}
#endif

	void set(SceneObject* obj);
	void set(StringId* sid);
	void set(StringId& sid);

	void clear() {
		stringID.clear();
		pointerParameter = 0;
	}

	void set(uint64 oid) {
		clear();

		pointerParameter = oid;
	}

	void set(const String& file, const String& id) {
		clear();

		stringID.setStringId(file, id);
	}

	void set(const UnicodeString& us) {
		clear();

		customName = us;
	}

	void set(const String& cs) {
		clear();

		customName = UnicodeString(cs);
	}

	void set(const char* cstr) {
		clear();

		customName = UnicodeString(cstr);
	}

	inline uint32 size() const {
		return sizeof(pointerParameter) + stringID.size();
	}

	inline uint64 getPointerParameter() const {
		return pointerParameter;
	}

	inline UnicodeString& getUnicodeParameter() {
		return customName;
	}

	inline String getDisplayedName() const {
		if (customName.isEmpty()) {
			return stringID.getFullPath();
		} else {
			return customName.toString();
		}
	}

	inline String getFileParameter() const {
		return stringID.getFile();
	}

	inline String getStringIDParameter() const {
		return stringID.getStringID();
	}

	friend class server::chat::StringIdChatParameter;
};


}
}
}
}
}

using namespace server::zone::objects::scene::variables;
#endif /* STRINGIDPARAMETER_H_ */
