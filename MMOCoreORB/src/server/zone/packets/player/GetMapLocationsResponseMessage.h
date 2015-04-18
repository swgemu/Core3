/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETMAPLOCATIONSRESPONSEMESSAGE_H_
#define GETMAPLOCATIONSRESPONSEMESSAGE_H_

#include "engine/engine.h"

#include "server/zone/managers/templates/PlanetMapCategory.h"
#include "server/zone/managers/planet/MapLocationTable.h"
#include "server/zone/managers/planet/MapLocationEntry.h"
#include "server/zone/managers/templates/TemplateManager.h"

class GetMapLocationsResponseMessage : public BaseMessage {
public:
	GetMapLocationsResponseMessage(const String& planet, MapLocationTable* mapLocations, SceneObject* player) : BaseMessage() {
		insertShort(0x05);
		insertInt(0x9F80464C);  //GetMapLocationsResponseMessage

		insertAscii(planet);

#ifndef WITH_STM
		mapLocations->rlock();
#endif

		insertInt(0);

		int totalEntries = 0;

		TangibleObject* play = cast<TangibleObject*>(player);
		unsigned int faction = play->getFaction();

		try {
			for (int i = 0; i < mapLocations->size(); ++i) {
				SortedVector<MapLocationEntry>& sortedVector = mapLocations->get(i);

				for (int j = 0; j < sortedVector.size(); ++j) {
					if (sortedVector.elementAt(j).insertToMessage(this, faction))
						++totalEntries;
				}
			}

		} catch (Exception& e) {
			System::out << e.getMessage() << endl;
			e.printStackTrace();
		}

#ifndef WITH_STM
		mapLocations->runlock();
#endif

		insertInt(12 + planet.length(), totalEntries);

		insertInt(0); //Blank List
		insertInt(0); //Blank List

		insertInt(0); //Unknown
		insertInt(0); //Unknown
		insertInt(0); //Unknown

		setCompression(true);
	}

};
#endif /*GETMAPLOCATIONSRESPONSEMESSAGE_H_*/
