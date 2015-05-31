/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NAMEMANAGER_H_
#define NAMEMANAGER_H_

#include "engine/lua/Lua.h"
#include "engine/lua/LuaObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/managers/templates/TemplateManager.h"

namespace server {
	namespace zone {

	class ZoneProcessServer;

	}
}

using namespace server::zone;

namespace server {
	namespace zone {
		namespace objects {
			namespace creature {

				class CreatureObject;
			}
		}
	}
}

using namespace server::zone::objects::creature;

class BannedNameSet : public HashSet<String> {
	int hash(const String& str) const {
		return str.hashCode();
	}

public:
	BannedNameSet() : HashSet<String>() {
	}
};

class NameManagerResult {
public:
	static const uint8 DECLINED_EMPTY = 0;
	static const uint8 DECLINED_DEVELOPER = 1;
	static const uint8 DECLINED_FICT_RESERVED = 2;
	static const uint8 DECLINED_PROFANE = 3;
	static const uint8 DECLINED_RACE_INAPP = 4;
	static const uint8 DECLINED_SYNTAX = 5;
	static const uint8 DECLINED_RESERVED = 6;
	static const uint8 ACCEPTED	= 7;

	static const uint8 DECLINED_GUILD_LENGTH = 11;
};

class NameManagerType {
public:

	static const int TAG = 0; // a mobile

	// List format must be main type with odd value followed by _TAG type with even value for AiAgent to properly generate name
	static const int GENERIC = 1; // Firstname Lastname
	static const int GENERIC_TAG = 2; // Firstname Lastname (a mobile)
	static const int GENERIC_FIRSTNAME = 3; // Firstname
	static const int GENERIC_FIRSTNAME_TAG = 4; // Firstname (a mobile)

	static const int STORMTROOPER = 11; // XX-123
	static const int STORMTROOPER_TAG = 12; // XX-123 (a stormtrooper)
	static const int SCOUTTROOPER = 13; // XX-123
	static const int SCOUTTROOPER_TAG = 14; // XX-123 (a scout trooper)
	static const int DARKTROOPER = 15; // XX-123
	static const int DARKTROOPER_TAG = 16; // XX-123 (a dark trooper)
	static const int SWAMPTROOPER = 17; // XX-123
	static const int SWAMPTROOPER_TAG = 18; // XX-123 (a swamp trooper)

	static const int GUILD_NAME = 31;
	static const int GUILD_ABBREV = 32;
	static const int GUILD_TITLE = 33;
};

namespace server {
	namespace zone {
		namespace managers {
			namespace name {

class NameManager : public Singleton<NameManager>, public Logger, public Object {
	ManagedReference<ZoneProcessServer*> server;

	Lua* lua;

	Vector<String>* profaneNames;
	BannedNameSet* developerNames;
	BannedNameSet* fictionNames;
	BannedNameSet* reservedNames;

	VectorMap<String, String> letterMappings;

	Vector<String> organicPrefixes;
	Vector<String> organicSuffixes;

	Vector<String> inorganicPrefixes;
	Vector<String> inorganicSuffixes;

	Vector<String> npcFirstNames;
	Vector<String> npcSurnames;

	Vector<String> stormtrooperPrefixes;
	Vector<String> scouttrooperPrefixes;
	Vector<String> darktrooperPrefixes;
	Vector<String> swamptrooperPrefixes;


private:

	void initialize();

	bool loadConfigFile();

	bool loadConfigData();

	void loadDefaultConfig();

	void fillNames();

	char chooseNextLetter(const char, const char);

	inline bool isReserved(String);

	inline bool isDeveloper(String);

	inline bool isFiction(String);

	inline bool isVowel(const char);

	inline void addPrefix(String& name, bool isOrganic);

	inline void addSuffix(String& name, bool isOrganic);

	char chooseLetterInclusive(String include);

	String makeName(int nameLength);

	String makeImperialTrooperName(int type);

public:
	NameManager();
	NameManager(ZoneProcessServer* serv);

	~NameManager();

	void test();

	bool isProfane(String name);

	int validateName(CreatureObject * obj);
	int validateName(const String& name, int species = -1);
	int validateFirstName(const String& name, int species = -1);
	int validateLastName(const String& name, int species = -1);
	int validateGuildName(const String& name, int type = NameManagerType::GUILD_NAME);
	int validateCityName(const String& name);
	int validateVendorName(const String& name);

	const String makeCreatureName(int type = 1);

	const String makeResourceName(bool isOrganic);
};

			}
		}
	}
}

using namespace server::zone::managers::name;

#endif /*NAMEMANAGER_H_*/
