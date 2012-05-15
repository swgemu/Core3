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

#ifndef WAYPOINTLIST_H_
#define WAYPOINTLIST_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/variables/DeltaVectorMap.h"
#include "server/zone/objects/waypoint/WaypointObject.h"

class WaypointList : public DeltaVectorMap<uint64, ManagedReference<WaypointObject*> > {
public:

	int set(uint64 key, WaypointObject* value, DeltaMessage* message = NULL, int updates = 1) {
		int pos = vectorMap.put(key, value);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(0);

			message->insertLong(key);
			value->insertToMessage(message);
		}

		return pos;
	}

	bool drop(const uint64& key, DeltaMessage* message = NULL, int updates = 1) {
		if (!vectorMap.contains(key))
			return false;

		ManagedReference<WaypointObject*> value = vectorMap.get(key);

		vectorMap.drop(key);

		if (message != NULL) {
			if (updates != 0)
				message->startList(updates, updateCounter += updates);

			message->insertByte(1);

			message->insertLong(key);
			value->insertToMessage(message);
		}

		return true;
	}

	void insertToMessage(BaseMessage* msg) {
		msg->insertInt(size());
		msg->insertInt(getUpdateCounter());

		for (int i = 0; i < size(); ++i) {
			uint64& key = getKeyAt(i);
			ManagedReference<WaypointObject*> value = getValueAt(i);

			msg->insertByte(0);
			msg->insertLong(key);
			value->insertToMessage(msg);
		}
	}

	uint64 find(const String& name) {
		if (name.isEmpty())
			return 0;

		for (int i = 0; i < size(); ++i) {
			uint64& key = getKeyAt(i);
			ManagedReference<WaypointObject*> value = getValueAt(i);

			if (name == value->getCustomObjectName().toString())
				return key;
		}

		return 0;
	}

	uint64 getWaypointBySpecialType(const uint8 specialTypeID) {
		if (specialTypeID == 0)
			return 0;

		for (int i = 0; i < vectorMap.size(); ++i) {
			ManagedReference<WaypointObject*> value = vectorMap.elementAt(i).getValue();

			if (value->getSpecialTypeID() == specialTypeID)
				return value->getObjectID();
		}

		return 0;

	}

};


#endif /* WAYPOINTLIST_H_ */
