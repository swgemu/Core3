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


namespace server {
namespace zone {
namespace objects {
namespace scene {
namespace variables {

class StringId : public virtual Object {
protected:
	String file;
	int filler;
	String stringID;

public:
	StringId();
	StringId(const StringId& id);
	StringId(const char * cstr);
	StringId(const String& fullPath);
	StringId(const String& fil, const String& stringId);

	StringId& operator=(const StringId& id) {
		if (&id == this)
			return *this;

		file = id.file;
		stringID = id.stringID;
		filler = id.filler;

		return *this;
	}

	bool operator==(const StringId& id) const {
		if (&id == this)
			return true;

		if(file == id.file &&
				stringID == id.stringID)
			return true;

		return false;
	}

	int compareTo(const StringId& id) const {
		return getFullPath().compareTo(id.getFullPath());
	}

	void clear();

	inline void getFullPath(String& str) const {
		str = "@" + file + ":" + stringID;
	}

	String getFullPath() const {
		return "@" + file + ":" + stringID;
	}

	inline String getFile() const {
		return file;
	}

	inline String getStringID() const {
		return stringID;
	}

	inline uint32 size() const {
		return file.length() + stringID.length();
	}

	inline bool isEmpty() const {
		if (file.isEmpty())
			return true;

		return false;
	}


	void setStringId(const String& fullPath);

	inline void setStringId(const String& file, const String& id) {
		StringId::file = file;
		StringId::stringID = id;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		return file.toBinaryStream(stream) &&
				TypeInfo<int >::toBinaryStream(&filler, stream) &&
				stringID.toBinaryStream(stream);
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {

		file.parseFromBinaryStream(stream);
		TypeInfo<int >::parseFromBinaryStream(&filler, stream);
		stringID.parseFromBinaryStream(stream);

		return true;
	}
};

}
}
}
}
}

using namespace server::zone::objects::scene::variables;
#endif /* STRINGID_H_ */
