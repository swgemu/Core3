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

#include "../../managers/resource/ResourceManager.h"
#include "../../managers/resource/ResourceList.h"
#include "../../managers/resource/ResourceItem.h"

#include "../../objects/structure/installation/harvester/HarvesterObject.h"
#include "../../objects/tangible/TangibleObject.h"

class InstallationObjectMessage7 : public BaseLineMessage {
public:
	InstallationObjectMessage7(InstallationObject* installation)
			: BaseLineMessage(installation->getObjectID(), 0x494E534F, 7, 0x05) {

		if (installation->isGenerator() || installation->isHarvester())
			insertResourceList((HarvesterObject*) installation);
		else
			insertEmptyResourceList();

		insertLong(installation->getSelectedResourceID()); //Currently selected resource objectID

		insertByte(installation->isOperating()); //Is the installation operating.

		insertInt((int) installation->getDisplayedBaseExtractionRate()); //Extraction Rate Displayed
		insertFloat(installation->getBaseExtractionRate()); //Base Extraction Rate
		insertFloat(installation->getExtractionRate()); //Extraction Rate

		insertFloat(installation->getHopperSize()); //Hopper Size
		insertInt((int) installation->getHopperSizeMax()); //Hopper Size Max

		insertHopperItems(installation);

		uint32 percentcondition = (uint32) round((installation->getCondition() / installation->getMaxCondition()) * 100);
		insertByte(percentcondition); //Condition of Installation (percentage)

		setSize();
	}

	void insertResourceList(HarvesterObject* harvester) {
		ResourceManager* resourceManager = harvester->getZone()->getZoneServer()->getResourceManager();
		ResourceList* list = resourceManager->getResourceListAtLocation(harvester->getZone()->getZoneID(), harvester->getPositionX(), harvester->getPositionY(), harvester->getHarvesterType());

		insertByte(1); //Resource Spawns Updated Flag

		if (list == NULL) {
			insertEmptyResourceList();
		} else {
			insertResourceIDList(list);
			insertResourceIDList(list);
			insertResourceNameList(list);
			insertResourceTypeList(list);
		}
	}

	void insertEmptyResourceList() {
		//Insert an empty list since we didn't retrieve any resources.
		insertInt(0); //Resource ID Size
		insertInt(0); //Resource ID Counter

		insertInt(0); //Resource ID Size
		insertInt(0); //Resource ID Counter

		insertInt(0); //Resource Name Size
		insertInt(0); //Resource Name Counter

		insertInt(0); //Resource Type Size
		insertInt(0); //Resource Type Counter
	}

	void insertResourceIDList(ResourceList* list) {
		insertInt(list->size()); //size
		insertInt(list->size()); //counter

		for (int x = 0; x < list->size(); x++) {
			ResourceItem *ri = list->get(x);
			insertLong(ri->getObjectID());
		}
	}

	void insertResourceNameList(ResourceList *list) {

		insertInt(list->size()); //size
		insertInt(list->size()); //counter

		for (int x = 0; x < list->size(); x++) {
			ResourceItem *ri = list->get(x);
			insertAscii(ri->getName());
		}
	}

	void insertResourceTypeList(ResourceList *list) {
		insertInt(list->size()); //size
		insertInt(list->size()); //counter

		for (int x = 0; x < list->size(); x++) {
			ResourceItem *ri = list->get(x);
			insertAscii(ri->getType());
		}
	}

	void insertHopperItems(InstallationObject* installation) {
		insertByte(installation->isHopperEmpty() ? 0 : 1); //Hopper Update Flag
		insertInt(installation->getHopperListSize()); //How many items are in the hopper
		insertInt(installation->getUpdateCounter()); //Hopper update counter

		for (int i = 0; i < installation->getHopperListSize(); i++) {
			insertLong(installation->getHopperItemID(i));
			insertFloat(installation->getHopperItemQuantity(i));
		}
	}
};

#endif /* INSTALLATIONOBJECTMESSAGE7_H_ */
