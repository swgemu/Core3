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

#ifndef CELLOBJECTIMPLEMENTATION_H_
#define CELLOBJECTIMPLEMENTATION_H_

#include "../../../packets.h"

#include "CellObject.h"
#include "../../scene/SceneObject.h"

#include "../../player/Player.h"
#include "../../player/PlayerImplementation.h"
#include "../../../Zone.h"

#include "../../../ZoneClientSessionImplementation.h"

class Player;
class BuildingObject;
class Zone;

class CellObjectImplementation : public CellObjectServant {
	SortedVector<SceneObject*> children;
	uint64 cellID;

public:
	CellObjectImplementation(uint64 objID, BuildingObject* buio);
	CellObjectImplementation(uint64 objID, BuildingObject* buio, uint64 cid);
	~CellObjectImplementation();

	void addChild(SceneObject* obj, bool doLock = true);
	void removeChild(SceneObject* obj, bool doLock = true);

	void sendTo(Player* player, bool doClose = true) {
		/*ZoneClient* client = player->getClient();
+		if (client == NULL)
+			return;
+
+		SceneObjectImplementation::create(client);
+
+		UpdateContainmentMessage* link = new UpdateContainmentMessage(objectID, parent->getObjectID(), 0xFFFFFFFF);
+		player->sendMessage(link);
+
+		CellObjectMessage3* cellMsg3 = new CellObjectMessage3(objectID, cellID);
+		player->sendMessage(cellMsg3);
+
+		CellObjectMessage6* cellMsg6 = new CellObjectMessage6(objectID);
+		player->sendMessage(cellMsg6);
+
+		UpdateCellPermissionsMessage* perm = new UpdateCellPermissionsMessage(objectID);
+		player->sendMessage(perm);
+
+		if (doClose)
+				SceneObjectImplementation::close(client);*/
	}

	void sendDestroyTo(Player* player) {
	}

	inline SceneObject* getChild(int idx) {
		return children.get(idx);
	}

	inline int getChildrenSize() {
		return children.size();
	}

	inline uint64 getCellID() {
		return cellID;
	}


};

#endif /*CELLOBJECTIMPLEMENTATION_H_*/
