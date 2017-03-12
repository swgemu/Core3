/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#ifndef PLAYERCREATIONMANAGER_H_
#define PLAYERCREATIONMANAGER_H_

#include "engine/lua/Lua.h"
#include "server/zone/packets/charcreation/ClientCreateCharacterCallback.h"

namespace server {
namespace zone {
	class ZoneServer;
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

namespace server {
namespace zone {
namespace objects {
namespace scene {
	class SceneObject;
}
}
}
}

using namespace server::zone::objects::scene;

namespace server {
namespace zone {
namespace managers {
namespace player {
namespace creation {

class RacialCreationData;
class HairStyleInfo;
class ProfessionDefaultsInfo;

class PlayerCreationManager : public Singleton<PlayerCreationManager>, public Logger, public Object {
	ManagedReference<ZoneServer*> zoneServer;

	VectorMap<String, Reference<RacialCreationData*> > racialCreationData;
	VectorMap<String, Reference<ProfessionDefaultsInfo*> > professionDefaultsInfo;
	VectorMap<String, SortedVector<String> > defaultCharacterEquipment;
	VectorMap<String, Reference<HairStyleInfo*> > hairStyleInfo;

	/**
	 * Vector containing starting items common for all races and professions.
	 */
	Vector<String> commonStartingItems;

	int startingCash;
	int startingBank;
	int skillPoints;

	bool freeGodMode;

	mutable HashTable<uint32, Time> lastCreatedCharacter;
	mutable Mutex charCountMutex;

	void loadLuaConfig();
	void loadRacialCreationData();
	void loadDefaultCharacterItems();
	void loadProfessionDefaultsInfo();
	void loadHairStyleInfo();

	/**
	 * Loads all starting items (profession specific, race specific, common) and
	 * starting clothes.
	 * @param lua pointer to a Lua object which contains the starting items and clothes.
	 */
	void loadLuaStartingItems(Lua* lua);

	void addCustomization(CreatureObject* creature, const String& customizationString, const String& appearanceFilename) const;
	void addHair(CreatureObject* creature, const String& hairTemplate, const String& hairCustomization) const;
	void addRacialMods(CreatureObject* creature, const String& race, Vector<String>* startingSkills, Vector<String>* startingItems, bool equipmentOnly) const;
	void addStartingItems(CreatureObject* creature, const String& clientTemplate, bool equipmentOnly) const;
	void addProfessionStartingItems(CreatureObject* creature, const String& profession, const String& clientTemplate, bool equipmentOnly) const;
	//void generateHologrindProfessions(CreatureObject* creature);

public:
	PlayerCreationManager();
	~PlayerCreationManager();

	/**
	 * Validates the character's name.
	 * @param characterName The character's name.
	 */
	bool validateCharacterName(const String& characterName) const;
	/**
	 * Attempts to create a character, validating the information passed back by the client.
	 */
	bool createCharacter(ClientCreateCharacterCallback* callback) const;

	/**
	 * Returns the requested maximum attribute limit for the specified race.
	 * @param race the race of interest.
	 * @param attributeNumber The attribute number (starting from 0).
	 * @return maximum attribute limit.
	 */
	int getMaximumAttributeLimit(const String& race, int attributeNumber) const;

	/**
	 * Returns the requested minimum attribute limit for the specified race.
	 * @param race the race of interest.
	 * @param attributeNumber The attribute number (starting from 0).
	 * @return minimum attribute limit.
	 */
	int getMinimumAttributeLimit(const String& race, int attributeNumber) const;

	/**
	 * Returns the total attribute limit for the specified race.
	 * @param race the race of interest.
	 * @return total attribute limit.
	 */
	int getTotalAttributeLimit(const String& race) const;

	/**
	 * Adds starting Weapons into the target container
	 * @param creature the player creature
	 * @param container the target container
	 */
	void addStartingWeaponsInto(CreatureObject* creature, SceneObject* container) const;

	/**
	 * Adds starting Items except Weapons into the target container
	 * @param creature the player creature
	 * @param container the target container
	 */
	void addStartingItemsInto(CreatureObject* creature, SceneObject* container) const;
};

}
}
}
}
}

using namespace server::zone::managers::player::creation;

#endif // PLAYERCREATIONMANAGER_H_
