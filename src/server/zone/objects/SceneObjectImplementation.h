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

#ifndef SCENEOBJECTIMPLEMENTATION_H_
#define SCENEOBJECTIMPLEMENTATION_H_

#include "../ZoneProcessServerImplementation.h"
#include "../Zone.h"
#include "../Quaternion.h"
#include "SceneObject.h"

class SceneObjectImplementation : public SceneObjectServant, public QuadTreeEntry, public ContainerObject, public Logger {
protected:
	ZoneProcessServerImplementation* server;
	Zone* zone;

	String stfFile;
	String stfName;
	UnicodeString customName;

	Quaternion* direction;

	uint64 ownerCharacterID;

	uint32 objectCRC;
	uint32 movementCounter;
	uint32 linkType;

	uint8 gameObjectType;

public:
	//Game Object Types

public:
	SceneObjectImplementation();
	virtual ~SceneObjectImplementation();

	void initialize();

	//ORB methods
	void deploy();
	void scheduleRedeploy();
	void undeploy();
	void removeUndeploymentEvent();

	//Saving and loading
	virtual void serialize(String& str);
	virtual void deserialize(const String& str);

	//Sending of data to client
	virtual void sendTo(Player* player, bool doclose = true);
	virtual void sendDestroyTo(Player* player);
	virtual void sendRadialResponseTo(Player* player);
	virtual void sendConversationStopTo(Player* player);
	virtual void sendCustomNamePromptTo(Player* player);

	//Generic Radial Responses
	virtual void onRadialUse(Player* player);
	virtual void onRadialPickup(Player* player);
	virtual void onRadialDrop(Player* player);
	virtual void onRadialDestroy(Player* player);
	virtual void onRadialOpen(Player* player);
	virtual void onRadialActivate(Player* player);
	virtual void onRadialDeactivate(Player* player);
	virtual void onRadialSetName(Player* player);
	virtual void onRadialConverseStart(Player* player);
	virtual void onRadialConverseRespond(Player* player);
	virtual void onRadialConverseResponse(Player* player);
	virtual void onRadialConverseStop(Player* player);
	//Overridible?
	virtual void onRadialMenu1(Player* player);
	virtual void onRadialMenu2(Player* player);
	virtual void onRadialMenu3(Player* player);
	virtual void onRadialMenu4(Player* player);
	virtual void onRadialMenu5(Player* player);
	virtual void onRadialMenu6(Player* player);
	virtual void onRadialMenu7(Player* player);
	virtual void onRadialMenu8(Player* player);
	virtual void onRadialMenu9(Player* player);
	virtual void onRadialMenu10(Player* player);


	//Setters

	//Getters
};

#endif /*SCENEOBJECTIMPLEMENTATION_H_*/
