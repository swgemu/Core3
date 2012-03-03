/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

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

	StringIdParameter& operator=(const StringIdParameter& par) {
		if (this == &par)
			return *this;

		pointerParameter = par.pointerParameter;
		stringID = par.stringID;
		customName = par.customName;

		return *this;
	}

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

	inline String getDisplayedName() {
		if (customName.isEmpty()) {
			return stringID.getFullPath();
		} else {
			return customName.toString();
		}
	}

	inline String& getFileParameter() {
		return stringID.getFile();
	}

	inline String& getStringIDParameter() {
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
