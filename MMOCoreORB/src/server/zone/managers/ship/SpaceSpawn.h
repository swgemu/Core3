/*
 * SpaceSpawn.h
 *
 *  Created on: 2024-09-15
 *  Author: Hakry
 */

#ifndef SPACESPAWN_H_
#define SPACESPAWN_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace managers {
namespace ship {

class SpaceSpawn : public Object {
	protected:
		String shipSpawnGroupName;

		Vector<uint32> leadShips;
		Vector<uint32> groupShips;

		int spawnLimit;
		int numberToSpawn;
		int weighting;
		uint32 capitalShipCRC;

	public:
		SpaceSpawn() : Object() {
			shipSpawnGroupName = "";
			spawnLimit = -1;
			numberToSpawn = 5;
			weighting = 1;
			capitalShipCRC = 0;
		}

		SpaceSpawn(const SpaceSpawn& spaceSp) : Object() {
			shipSpawnGroupName = spaceSp.shipSpawnGroupName;

			leadShips = spaceSp.leadShips;
			groupShips = spaceSp.groupShips;

			spawnLimit = spaceSp.spawnLimit;
			numberToSpawn = spaceSp.numberToSpawn;
			weighting = spaceSp.weighting;
			capitalShipCRC = spaceSp.capitalShipCRC;
		}

		SpaceSpawn& operator=(const SpaceSpawn& spaceSp) {
			if (this == &spaceSp) {
				return *this;
			}

			shipSpawnGroupName = spaceSp.shipSpawnGroupName;

			leadShips = spaceSp.leadShips;
			groupShips = spaceSp.groupShips;

			spawnLimit = spaceSp.spawnLimit;
			numberToSpawn = spaceSp.numberToSpawn;
			weighting = spaceSp.weighting;
			capitalShipCRC = spaceSp.capitalShipCRC;

			return *this;
		}

		void readObject(LuaObject& obj) {
			shipSpawnGroupName = obj.getStringField("shipSpawnGroupName");

			// Logger::console.info(true) << "Reading SpaceSpawn - Group Name: " << shipSpawnGroupName;

			LuaObject leadShipsObj = obj.getObjectField("leadShips");

			if (leadShipsObj.isValidTable()) {
				for (int i = 1; i <= leadShipsObj.getTableSize(); ++i) {
					String leadShip = "object/ship/" + leadShipsObj.getStringAt(i) + ".iff";

					// Logger::console.info(true) << "Adding Lead Ship #" << i << " - " << leadShip;

					leadShips.add(leadShip.hashCode());
				}
			}

			leadShipsObj.pop();

			LuaObject groupShipsObj = obj.getObjectField("groupShips");

			if (groupShipsObj.isValidTable()) {
				for (int i = 1; i <= groupShipsObj.getTableSize(); ++i) {
					String groupShip = "object/ship/" + groupShipsObj.getStringAt(i) + ".iff";

					// Logger::console.info(true) << "Adding Group Ship #" << i << " - " << groupShip;

					groupShips.add(groupShip.hashCode());
				}
			}

			groupShipsObj.pop();

			spawnLimit = obj.getIntField("spawnLimit");
			numberToSpawn = obj.getIntField("numberToSpawn");
			weighting = obj.getIntField("weighting");

			String capitalShip = obj.getStringField("capitalShip");

			if (!capitalShip.isEmpty()) {
				String shipString = "object/ship/" + capitalShip + ".iff";

				// Logger::console.info(true) << "Adding Capital Ship: " << shipString;

				capitalShipCRC = shipString.hashCode();
			}
		}

		const String& getShipSpawnGroupName() const {
			return shipSpawnGroupName;
		}

		int getSpawnLimit() const {
			return spawnLimit;
		}

		int getNumberToSpawn() const {
			return numberToSpawn;
		}

		int getWeighting() const {
			return weighting;
		}

		uint32 getRandomLeadShip() {
			if (leadShips.size() < 1) {
				return 0;
			}

			int totalShips = leadShips.size() - 1;

			return (leadShips.get(System::random(totalShips)));
		}

		uint32 getRandomGroupShip() {
			if (groupShips.size() < 1) {
				return 0;
			}

			int totalShips = groupShips.size() - 1;

			return (groupShips.get(System::random(totalShips)));
		}

		uint32 getCapitalShipCRC() {
			return capitalShipCRC;
		}
};

} // ship
} // managers
} // zone
} // server

using namespace server::zone::managers::ship;

#endif /* SPACESPAWN_H_ */
