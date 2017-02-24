/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NAMEMANAGER_H_
#define NAMEMANAGER_H_

#include "engine/lua/Lua.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/managers/name/NameData.h"

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
	static const int GENERIC = 1; // Name Generator

	static const int R2 = 2; // R2-A1
	static const int R3 = 3; // R3-A1
	static const int R4 = 4; // R4-A1
	static const int R5 = 5; // R5-A1

	static const int DROID_3P0 = 6; // XX-P0
	static const int DROID_EG6 = 7; // EX-X
	static const int DROID_WED = 8; // WED-XX
	static const int DROID_LE = 9; // LE-XXX
	static const int DROID_RA7 = 10; // RA7-XX

	static const int STORMTROOPER = 11; // XX-123
	static const int SCOUTTROOPER = 12; // XX-123
	static const int DARKTROOPER = 13; // XX-123
	static const int SWAMPTROOPER = 14; // XX-123

	static const int GUILD_NAME = 31;
	static const int GUILD_ABBREV = 32;
	static const int GUILD_TITLE = 33;

	static const int FRAG_CONSONANT = 41;
	static const int FRAG_VOWEL = 42;
	static const int FRAG_SPECIAL = 43;
	static const int FRAG_MIXED = 44;
};

namespace server {
	namespace zone {
		namespace managers {
			namespace name {

class NameManager : public Singleton<NameManager>, public Logger, public Object {
	ManagedReference<ZoneProcessServer*> server;

	Lua* lua;

	NameData* bothanData;
	NameData* humanData;
	NameData* ithorianData;
	NameData* monCalData;
	NameData* rodianData;
	NameData* sullustanData;
	NameData* trandoshanData;
	NameData* twilekData;
	NameData* wookieeData;
	NameData* zabrakData;

	NameData* energyResourceData;
	NameData* mineralResourceData;
	NameData* plainResourceData;
	NameData* reactiveGasResourceData;

	Vector<String>* profaneNames;
	BannedNameSet* developerNames;
	BannedNameSet* fictionNames;
	BannedNameSet* reservedNames;

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

	String appendSyllable(const String& left, const String& right, NameData* data);

	int getFragmentType(const String& frag, NameData* data);

	String makeImperialTrooperName(int type);

public:
	NameManager();
	NameManager(ZoneProcessServer* serv);

	~NameManager();

	void test();

	bool isProfane(String name);

	int validateName(CreatureObject * obj);
	int validateName(const String& name, int species = -1);
	int validateGuildName(const String& name, int type = NameManagerType::GUILD_NAME);
	int validateCityName(const String& name);
	int validateVendorName(const String& name);
	int validateChatRoomName(const String& name);

	const String makeCreatureName(int type = 1, int species = 0);

	String generateSingleName(NameData* nameData, NameRules* rules);

	String generateUniqueName(NameData* nameData, NameRules* rules);

	String generateRandomizedName(NameData* nameData, NameRules* nameRules);

	String generateRandomName(NameData* nameData);

	String generateResourceName(const String& randomNameClass);

	String makeDroidName(int type);

	String capitalizeName(String& name);

	NameData* getSpeciesData(int species);

};

			}
		}
	}
}

using namespace server::zone::managers::name;

#endif /*NAMEMANAGER_H_*/
