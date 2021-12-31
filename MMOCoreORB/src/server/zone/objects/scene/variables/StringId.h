/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STRINGID_H_
#define STRINGID_H_

#include "engine/engine.h"

#include "engine/util/json_utils.h"

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
	StringId(StringId&& id);

	StringId& operator=(const StringId& id) {
		if (&id == this)
			return *this;

		file = id.file;
		stringID = id.stringID;
		filler = id.filler;

		return *this;
	}

	StringId& operator=(StringId&& id) {
		if (&id == this)
			return *this;

		file = std::move(id.file);
		stringID = std::move(id.stringID);
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

	inline const String& getFile() const {
		return file;
	}

	inline const String& getStringID() const {
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

	inline int getFiller() const {
		return filler;
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

	String toString() const {
		StringBuffer asStr;
		asStr << file << ":" << stringID;
		return asStr.toString();
	}
};

void to_json(nlohmann::json& k, const server::zone::objects::scene::variables::StringId& str);

}
}
}
}
}

using namespace server::zone::objects::scene::variables;
#endif /* STRINGID_H_ */
