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

#ifndef OBJECTCONTROLLERMESSAGE_H_
#define OBJECTCONTROLLERMESSAGE_H_

#include "engine/engine.h"

class ZoneProcessServerImplementation;
class GroupManager;
class RadialManager;
class MissionManager;
class PlayerManager;
class PlayerObject;
class CombatManager;
class ItemManager;
class PlanetManager;
class TangibleObject;
class Skill;

class ObjectControllerMessage : public BaseMessage {
public:
	ObjectControllerMessage(uint64 objid, uint32 header1, uint32 header2, bool comp = true);

	static bool parseDataTransform(CreatureObject* player, Message* pack);
	static uint64 parseDataTransformWithParent(CreatureObject* player, Message* pack);

	static void parseCommandQueueEnqueue(CreatureObject* player, Message* pack, ZoneProcessServerImplementation* serv);
	static void parseCommandQueueClear(CreatureObject* player, Message* pack);

	static void parseObjectTargetUpdate(CreatureObject* player, Message* pack);
    static void parseRadialRequest(CreatureObject* player, Message* pack, RadialManager* radialManager);

    static void parseImageDesignChange(CreatureObject* player, Message* pack, ZoneProcessServerImplementation* serv);
    static void parseImageDesignCancel(CreatureObject* player, Message* pack);

    static void parseFlourish(CreatureObject* player, Message* pack);

    static void parseResourceEmptyHopper(CreatureObject* player, Message* pack);

    static void sendErrMsg(uint32 actioncntr, Skill* skill, CreatureObject* player);
    // structures
    //static void parsePermissionListModify(PlayerObject* player, Message* pack);

    // mission
    static void parseMissionListRequest(CreatureObject* player, Message* pack);
    static void parseMissionAccept(CreatureObject* player, Message* pack);
    static void parseMissionAbort(CreatureObject* player, Message* pack);

	// Crafting
	static void parseAddCraftingResource(CreatureObject* player, Message* packet);
	static void parseRemoveCraftingResource(CreatureObject* player, Message* packet);
	static void parseCraftCustomization(CreatureObject* player, Message* packet);
	static void parseExperimentation(CreatureObject* player, Message* packet);


	static void parsePickup(CreatureObject* player, Message* pack);

	static void parseItemDropTrade(CreatureObject* player, Message* pack);

	static void parseRotateItem(CreatureObject* player, Message* pack);

	static void parseTellPet(CreatureObject* player, Message* pack);
};

#endif /*OBJECTCONTROLLERMESSAGE_H_*/

