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

	SceneObject* parent;

	String stfFile;
	String stfName;
	UnicodeString customName;

	Quaternion* direction;

	uint64 ownerCharacterID;

	uint32 objectCRC;
	uint32 linkType;

	int gameObjectType;

public:
	//Game Object Types
	static const int SCENE = 0x00;
	static const int CELL = 0x00;
	static const int CORPSE = 0x01;

	//Universe Objects
	static const int GROUP = 0x02;
	static const int GUILD = 0x03;

	static const int LAIR = 0x04; //Also appears to be general attackable objects.
	static const int STATIC = 0x05;
	static const int CAMPSPIT = 0x06; //Doesn't appear to be anything else in this category.

	//Tangible Objects - Top level
	static const int ARMOR = 0x100;
	static const int BUILDING = 0x200;
	static const int CREATURE = 0x400;
	static const int INSTALLATION = 0x1000;
	static const int MISC = 0x2000;
	static const int TERMINAL = 0x4000;
	static const int TOOL = 0x8000;
	static const int VEHICLE = 0x10000;
	static const int WEAPON = 0x20000;
	static const int COMPONENT = 0x40000;
	static const int WEAPONPOWERUP = 0x80000;
	static const int ARMORPOWERUP = 0x100000;
	static const int JEWELRY = 0x200000;
	static const int RESOURCECONTAINER = 0x400000;
	static const int DEED = 0x800000;
	static const int WEARABLE = 0x1000000;
	static const int SHIP = 0x20000000;
	static const int SHIPCOMPONENTS = 0x40000000;

	// Intangible (top level)
	static const int INTANGIBLE = 0x800;
	static const int DRAFTSCHEMATIC = 0x801;
	static const int DRAFTSCHEMATIC = 0x801;
	static const int MANUFACTURESCHEMATIC = 0x802;
	static const int MISSION = 0x803;
	static const int WAYPOINT = 0x802;

public:
	SceneObjectImplementation();
	virtual ~SceneObjectImplementation();

	void initialize();

	//ORB methods
	void destroy();
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
	virtual void sendStatusTo(Player* player); //TODO: We can use this for administrative purposes, and of course for structures/camps.

	//SceneObject packets?
	virtual void create(ZoneClientSession* client);
	virtual void destroy(ZoneClientSession* client);

	//General actions.
	virtual void use(Player* player);
	virtual void pickup(Player* player);
	virtual void drop(Player* player);
	virtual void destroy(Player* player); //TODO: Should we name this something else to not confuse it with the ORB method?
	virtual void open(Player* player);
	virtual void activate(Player* player);
	virtual void deactivate(Player* player);

	//These radial responses can be overridden.
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
	bool isObjectType(int type, bool similar = false);
};

#endif /*SCENEOBJECTIMPLEMENTATION_H_*/
