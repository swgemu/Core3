/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef JEDIMANAGER_H_
#define JEDIMANAGER_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"

namespace server {
namespace zone {
namespace managers {
namespace jedi {

/**
 * Singleton class with a common interface for all different Jedi progression systems.
 */
class JediManager : public Singleton<JediManager>, public Logger, public Object, public ReadWriteLock {
private:
	/**
	 * The Jedi progression type currently configured.
	 */
	int jediProgressionType;

	/**
	 * The name of the jedi manager class in Lua.
	 */
	String jediManagerName;

	/**
	 * Setup Lua global values.
	 * @param luaEngine the lua instance.
	 */
	void setupLuaValues(Lua* luaEngine);

public:
	
	enum {
		NOJEDIPROGRESSION,         // Jedi progression not available.
		HOLOGRINDJEDIPROGRESSION,  // Jedi progression through the hologrind system, i.e. master five random professions.
		VILLAGEJEDIPROGRESSION,    // Jedi progression through the village system.
		CUSTOMJEDIPROGRESSION      // Custom defined jedi progression system.
	};
	
	enum {
		ITEMHOLOCRON,         // Item type holocron.
		ITEMWAYPOINTDATAPAD,  // Item type waypoint datapad.
		ITEMTHEATERDATAPAD    // ITEMTHEATERDATAPAD
	};
	
	/**
	 * Constructor for the Jedi Manager.
	 */
	JediManager();

	/**
	 * Destructor for the Jedi Manager.
	 */
	~JediManager();

	/**
	 * Load the Jedi Manager configuration.
	 * @param luaEngine the lua engine to use for loading the configuration.
	 */
	void loadConfiguration(Lua* luaEngine);

	/**
	 * On player created.
	 * @param creature the creature/player that was created.
	 */
	void onPlayerCreated(CreatureObject* creature);

	/**
	 * On player logged in.
	 * @param creature the creature/player that logged in.
	 */
	void onPlayerLoggedIn(CreatureObject* creature);

	/**
	 * On player logged out.
	 * @param creature the creature/player that logged out.
	 */
	void onPlayerLoggedOut(CreatureObject* creature);

	/**
	 * Check force status command.
	 * Calls the checkForceStatusCommand in the lua manager.
	 * @param creature the creature that performed the command.
	 */
	void checkForceStatusCommand(CreatureObject* creature);

	/**
	 * Get the name of the currently active lua jedi manager.
	 * @return the name of the currently active lua jedi manager.
	 */
	String getJediManagerName();

	/**
	 * Set the name of the currently active lua jedi manager.
	 * @param name the name of the currently active lua jedi manager.
	 */
	void setJediManagerName(String name);

	/**
	 * Handle usage of any item related to the jedi progression.
	 * @param item pointer to the item object.
	 * @param itemType the type of item.
	 * @param creature the creature that used the item.
	 */
	void useItem(SceneObject* item, const int itemType, CreatureObject* creature);
};

}
}
}
}

using namespace server::zone::managers::jedi;

#endif /* JEDIMANAGER_H_ */
