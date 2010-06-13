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

#ifndef INSTALLATIONOBJECTMESSAGE7_H_
#define INSTALLATIONOBJECTMESSAGE7_H_

#include "../BaseLineMessage.h"

#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/objects/resource/ResourceSpawn.h"

#include "server/zone/objects/installation/harvester/HarvesterObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"

class InstallationObjectMessage7 : public BaseLineMessage {
public:
	InstallationObjectMessage7(InstallationObject * inso)
			: BaseLineMessage(inso->getObjectID(), 0x494E534F, 7, 0x05) {

		if (inso->getObjectSubType() == TangibleObjectImplementation::HARVESTER) {
			HarvesterObject* hino = (HarvesterObject*) inso;
			ResourceManager* resourceManager = inso->getZone()->getZoneServer()->getResourceManager();
			ResourceList* list = resourceManager->getResourceListAtLocation(inso->getZone()->getZoneID(), inso->getPositionX(), inso->getPositionY(), hino->getHarvesterType());

			if (list == NULL)
				System::out << "list was null!" << endl;

			insertByte(1); // ResourcePoolUpdateFlag ?
			insertResourceIDList(list);
			insertResourceIDList(list);
			insertResourceNameList(list);
			insertResourceTypeList(list);
		} else
		{
			insertByte(1);
			// ID
			insertInt(0);
			insertInt(0);
			// ID
			insertInt(0);
			insertInt(0);
			// Name
			insertInt(0);
			insertInt(0);
			// Type
			insertInt(0);
			insertInt(0);
		}

		insertLong(inso->getActiveResourceID());

		insertByte(inso->isOperating());

		insertInt((int)inso->getExtractionRate()); // Extraction Rate Displayed
		insertFloat(inso->getExtractionRate()); // Extract Rate Max

		insertFloat(inso->getActualRate()); // Current Extract Rate

		insertFloat(inso->getHopperSize());
		insertInt((int)inso->getHopperSizeMax());

		//insertByte(0); // Hopper Update Flag
		//insertInt(inso->getHopperSize());

		insertHopperItems(inso);

		insertByte(100); // Percentage of Condition
		setSize();

	}

	//float density = getDensity(player->getZoneIndex(), resourceName, player->getPositionX(), player->getPositionY());
	// .f

	void insertResourceIDList(ResourceList *list) {

		//System::out << "insertResourceIDList size(): " << list->size() << endl;
		insertInt(list->size()); // size
		insertInt(list->size()); // counter
		for (int x = 0; x < list->size(); x++)
		{
			ResourceItem *ri = list->get(x);
			//System::out << "insertResourceIDList() ObjectID: " << hex << ri->getObjectID() << endl;
			insertLong(ri->getObjectID());
		}

	}

	void insertResourceNameList(ResourceList *list) {

		//System::out << "insertResourceNameList size(): " << list->size() << endl;
		insertInt(list->size()); // size
		insertInt(list->size()); // counter
		for (int x = 0; x < list->size(); x++)
		{
			ResourceItem *ri = list->get(x);
			//System::out << "insertResourceNameList() Name: " << ri->getName() << endl;
			insertAscii(ri->getName());
		}
	}

	void insertResourceTypeList(ResourceList *list) {
		//System::out << "insertResourceTypeList size(): " << list->size() << endl;
		insertInt(list->size()); // size
		insertInt(list->size()); // counter
		for (int x = 0; x < list->size(); x++)
		{
			ResourceItem *ri = list->get(x);
			//System::out << "insertResourceTypeList() Type: " << ri->getType() << endl;
			insertAscii(ri->getType());
		}
	}

	void insertHopperItems(InstallationObject *inso) {

		/*insertByte(0);
		insertInt(0);
		insertInt(0);*/


		// Hopper Update Flag
		insertByte(inso->getHopperItemCount() > 0 ? 1 : 0);
		insertInt(inso->getHopperItemCount());
		insertInt(inso->getNewHopperUpdateCounter(1));
		for (int i = 0; i < inso->getHopperItemCount(); i++) {
			uint64 rid = inso->getHopperItemID(i);
			insertLong(rid);
			float quant = inso->getHopperItemQuantity(i);
			insertFloat(quant);
		}
	}
};

#endif /* INSTALLATIONOBJECTMESSAGE7_H_ */
