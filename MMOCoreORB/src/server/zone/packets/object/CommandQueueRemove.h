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

#ifndef COMMANDQUEUEREMOVE_H_
#define COMMANDQUEUEREMOVE_H_

#include "ObjectControllerMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "ObjectControllerMessageCallback.h"

class CommandQueueRemove : public ObjectControllerMessage {
public:
	CommandQueueRemove(CreatureObject* creo, uint32 actioncnt, float timer, uint32 tab1, uint32 tab2) 
			: ObjectControllerMessage(creo->getObjectID(), 0x1B, 0x117) {
		insertInt(actioncnt);
		insertFloat(timer);
		insertInt(tab1);
		insertInt(tab2);
	}

};

class CommandQueueRemoveCallback : public MessageCallback {
	uint32 size;
	uint32 actionCount;
	uint32 actionCRC;

	ObjectControllerMessageCallback* objectControllerMain;

public:

	CommandQueueRemoveCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
	}

	void parse(Message* message) {
		size = message->parseInt(); //?

		actionCount = message->parseInt();
		actionCRC = message->parseInt();
	}

	void run() {
		ManagedReference<CreatureObject*> player = (CreatureObject*) client->getPlayer();

		if (player == NULL)
			return;

		//ObjectController* objectController = server->getZoneServer()->getObjectController();
		player->deleteQueueAction(actionCount);
	}

};

#endif /*COMMANDQUEUEREMOVE_H_*/
