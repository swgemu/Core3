/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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

#ifdef CXX11_COMPILER
	StringId(StringId&& id);
#endif

	StringId& operator=(const StringId& id) {
		if (&id == this)
			return *this;

		file = id.file;
		stringID = id.stringID;
		filler = id.filler;

		return *this;
	}

#ifdef CXX11_COMPILER
	StringId& operator=(StringId&& id) {
		if (&id == this)
			return *this;

		file = std::move(id.file);
		stringID = std::move(id.stringID);
		filler = id.filler;

		return *this;
	}
#endif


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
