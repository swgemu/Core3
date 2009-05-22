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

#ifndef INSTALLATIONOBJECTDELTAMESSAGE7_H_
#define INSTALLATIONOBJECTDELTAMESSAGE7_H_

//#include "engine/engine.h"

#include "../../packets/DeltaMessage.h"

#include "../../objects/structure/installation/InstallationObject.h"
#include "../../objects/structure/installation/harvester/HarvesterObject.h"

class InstallationObjectDeltaMessage7 : public DeltaMessage {
	InstallationObject* installation;

public:
	InstallationObjectDeltaMessage7(InstallationObject* inso)
			: DeltaMessage(inso->getObjectID(), 0x494E534F, 7) {
		installation = inso;
	}

	void updateExtractionRate(float rate) {
		addFloatUpdate(0x09, rate);
	}

	void setNoHopperUpdate() {
		addByteUpdate(0x0C, 0);
	}

	void updateSelectedResourceID(uint64 resourceid) {

		if (installation->isHarvester() || installation->isGenerator())
			((HarvesterObject*)installation)->changeSelectedResourceID(resourceid);

		addLongUpdate(0x05, resourceid); //Selected Resource ID
	}

	void updateOperating(bool state) {
		installation->setOperating(state);
		addByteUpdate(0x06, state);
	}

	void updateHopper() {
		addByteUpdate(0x0C, installation->getUpdateCounter() + 1);
	}

	void updateHopperSize() {
		addFloatUpdate(0x0A, installation->getHopperSize());
	}

	void updateHopperItem(uint64 resourceid) {
		startUpdate(0x0D); // hopper
		insertInt(1); // list size
		insertInt(installation->getUpdateCounter());
		insertByte(0x02); //change
		insertShort(installation->getHopperItemIndex(resourceid));
		insertLong(resourceid); // ID
		insertFloat(installation->getHopperItemQuantity(resourceid)); // size
	}

	void removeHopperItem(int index) {
		startUpdate(0x0D);
		insertInt(1);
		insertInt(installation->getUpdateCounter());
		insertByte(0x00); //remove
		insertShort(index);
	}

	void clearHopperItems() {
		startUpdate(0x0D);
		insertInt(1);
		insertInt(installation->getUpdateCounter());
		insertByte(0x04); //clearall?
	}

	void resetHopperItemList() {
		startUpdate(0x0D);
		insertInt(1);
		insertInt(installation->getUpdateCounter());
		insertByte(0x03); //resetall
		insertShort(installation->getHopperListSize());
		for (int i = 0; i < installation->getHopperListSize(); i++) {
			insertLong(installation->getHopperItemID(i));
			insertFloat(installation->getHopperItemQuantity(i));
		}
	}

	void addHopperItem(uint64 resourceid) {
		startUpdate(0x0D); // hopper
		insertInt(1); //list size
		insertInt(installation->getUpdateCounter());
		insertByte(0x01); //add
		insertShort(installation->getHopperListSize());
		insertLong(resourceid); //resource id
		insertFloat(floor(installation->getHopperItemQuantity(resourceid))); // size
	}

	void updateCondition() {
		startUpdate(0x0E);
		insertByte(0x00); //Condition!? of what!?
	}
};

#endif /* INSTALLATIONOBJECTDELTAMESSAGE7_H_ */
