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

#ifndef STRINGID_H_
#define STRINGID_H_

#include "engine/engine.h"

#include "StringIdParameter.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
namespace variables {

class StringId : public Serializable {
	String file;
	String stringID;
	String fullPath;

	UnicodeString customName;

	//Parameters
	StringIdParameter TT;
	StringIdParameter TU;
	StringIdParameter TO;
	uint32 DI;
	float DF;

private:
	inline void addSerializableVariables();

public:
	StringId();
	StringId(const StringId& id);
	StringId(const String& fullPath);
	StringId(const String& fil, const String& stringId);
	StringId(const UnicodeString& custom);

	void getFullPath(String& str) const {
		str = "@" + file + ":" + stringID;
	}

	void clear() {
		file.clear();
		stringID.clear();
		fullPath.clear();
		customName.clear();

		TT.clear();
		TU.clear();
		TO.clear();
	}

	inline String& getFile() const {
		return file;
	}

	inline String& getStringID() const {
		return stringID;
	}

	inline UnicodeString& getCustomString() const {
		return customName;
	}

	void setCustomString(const UnicodeString& custom) {
		customName = custom;
	}

	void setStringId(const String& fullPath) {
		if (fullPath.isEmpty())
			return;

		this->fullPath = fullPath;

		if (fullPath.charAt(0) == '@') {
			StringTokenizer tokenizer(fullPath.subString(1));
			tokenizer.setDelimeter(":");

			tokenizer.getStringToken(file);
			tokenizer.getStringToken(stringID);
		}
	}

	//Parameter Stuff

	template<T>
	void setTT(T obj) {
		TT.set(obj);
	}

	void setTT(const String& f, const String& s) {
		TT.set(f,c);
	}

	template<T>
	void setTU(T obj) {
		TD.set(obj);
	}

	void setTU(const String& f, const String& s) {
		TU.set(f,c);
	}

	template<T>
	void setTO(T obj) {
		TO.set(obj);
	}

	void setTO(const String& f, const String& s) {
		TO.set(f,c);
	}

	void setDI(uint32 i) {
		DI = i;
	}

	void setDF(float f) {
		DF = f;
	}

	friend StringBuffer &operator<<(StringBuffer &stream, StringId ob) const;
};

StringBuffer &operator<<(StringBuffer &stream, StringId ob) {
	stream << ob.fullPath;

	return stream;
}

}
}
}
}
}

using namespace server::zone::objects::scene::variables;
#endif /* STRINGID_H_ */
