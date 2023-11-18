/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NAMEMANAGER_H_
#define NAMEMANAGER_H_

#include "engine/core/ManagedReference.h"
#include "server/zone/managers/name/NameData.h"
#include "server/zone/managers/name/RegexData.h"

namespace server {
namespace zone {

class ZoneProcessServer;

}
} // namespace server

using namespace server::zone;

namespace server {
namespace zone {
namespace objects {
namespace creature {

class CreatureObject;
}
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::creature;

class NameManagerResult {
public:
	static const uint8 DECLINED_EMPTY = 0;
	static const uint8 DECLINED_DEVELOPER = 1;
	static const uint8 DECLINED_FICT_RESERVED = 2;
	static const uint8 DECLINED_PROFANE = 3;
	static const uint8 DECLINED_RACE_INAPP = 4;
	static const uint8 DECLINED_SYNTAX = 5;
	static const uint8 DECLINED_RESERVED = 6;
	static const uint8 ACCEPTED = 7;

	static const uint8 DECLINED_GUILD_LENGTH = 11;
};

class NameManagerType {
public:
	static const int TAG = 0;	  // a mobile
	static const int GENERIC = 1; // Name Generator

	static const int R2 = 2; // R2-A1
	static const int R3 = 3; // R3-A1
	static const int R4 = 4; // R4-A1
	static const int R5 = 5; // R5-A1

	static const int DROID_3P0 = 6;	 // XX-P0
	static const int DROID_EG6 = 7;	 // EX-X
	static const int DROID_WED = 8;	 // WED-XX
	static const int DROID_LE = 9;	 // LE-XXX
	static const int DROID_RA7 = 10; // RA7-XX

	static const int STORMTROOPER = 11; // XX-123
	static const int SCOUTTROOPER = 12; // XX-123
	static const int DARKTROOPER = 13;	// XX-123
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

	Vector<Reference<RegexData*>> regexFilters;

	Vector<String> stormtrooperPrefixes;
	Vector<String> scouttrooperPrefixes;
	Vector<String> darktrooperPrefixes;
	Vector<String> swamptrooperPrefixes;

private:
	void initialize();

	char chooseNextLetter(const char, const char) const;

	inline bool isReserved(const String&) const;
	inline bool isDeveloper(const String&) const;
	inline bool isFiction(const String&) const;

	String appendSyllable(const String& left, const String& right, const NameData* data) const;

	int getFragmentType(const String& frag, const NameData* data) const;

	String makeImperialTrooperName(int type) const;

public:
	NameManager();
	NameManager(ZoneProcessServer* serv);

	~NameManager();

	bool isProfane(const String& name) const;
	void loadConfigData(bool reload = false);

	int validateName(const CreatureObject* obj) const;
	int validateName(const String& name, int species = -1) const;
	int validateGuildName(const String& name, int type = NameManagerType::GUILD_NAME) const;
	int validateCityName(const String& name) const;
	int validateVendorName(const String& name) const;
	int validateChatRoomName(const String& name) const;
	int checkNamingFilter(const String& name, int resultType = -1) const;

	const String makeCreatureName(int type = 1, int species = 0) const;

	String generateSingleName(const NameData* nameData, const NameRules* rules) const;
	String generateUniqueName(const NameData* nameData, const NameRules* rules) const;
	String generateRandomizedName(const NameData* nameData, const NameRules* nameRules) const;
	String generateRandomName(const NameData* nameData) const;
	String generateResourceName(const String& randomNameClass) const;

	String makeDroidName(int type) const;

	String capitalizeName(const String& name) const;

	const NameData* getSpeciesData(int species) const;
};

} // namespace name
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::name;

#endif /*NAMEMANAGER_H_*/
