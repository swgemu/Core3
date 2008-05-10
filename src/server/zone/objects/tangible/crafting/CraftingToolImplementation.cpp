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
 
#include "../../../packets.h"
#include "../../../objects.h"
#include "CraftingTool.h"
#include "CraftingToolImplementation.h"
#include "../../../ZoneClient.h"
 
CraftingToolImplementation::CraftingToolImplementation(uint64 object_id, uint32 tempCRC, 
		const unicode& n, const string& tempn) : CraftingToolServant(object_id, n, tempn, tempCRC, 
				CRAFTINGTOOL) {
	objectCRC = tempCRC;
	templateTypeName = "obj_n";
	templateName = tempn;
	name = n;
	init();
}
 
CraftingToolImplementation::CraftingToolImplementation(CreatureObject* creature, uint32 tempCRC, 
		const unicode& n, const string& tempn) : CraftingToolServant(creature, n, tempn, tempCRC, 
				CRAFTINGTOOL) {
	objectCRC = tempCRC;
	templateTypeName = "obj_n";
	templateName = tempn;
	name = n;
	init();
}
 
CraftingToolImplementation::~CraftingToolImplementation(){ 
 
}
 
void CraftingToolImplementation::init() {
	
	setToolEffectiveness(-15.0f);
	setCraftingState(0);
	currentDs = NULL;
	currentTano = NULL;
}
 
int CraftingToolImplementation::useObject(Player* player) {
	cout << "Use Crafting Tool\n";
	return 0;
}
 
void CraftingToolImplementation::sendTo(Player* player, bool doClose) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;
	SceneObjectImplementation::create(client);
	if (container != NULL)
		link(client, container);
	TangibleObjectMessage3* tano3 = new TangibleObjectMessage3((TangibleObject*) _this);
	client->sendMessage(tano3);
	TangibleObjectMessage6* tano6 = new TangibleObjectMessage6((TangibleObject*) _this);
	client->sendMessage(tano6);
	if (doClose)
		SceneObjectImplementation::close(client);
	generateAttributes(player);
}
 
void CraftingToolImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;
	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage(_this);
	addAttributes(alm);
	
	player->sendMessage(alm);
}
 
void CraftingToolImplementation::sendToolStart(Player* player) {
	// Craft Start
	// Tano7
	
	TangibleObjectMessage7* tano7 = new TangibleObjectMessage7(_this);
	player->sendMessage(tano7);
	
	// DPlay9
	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
	dplay9->setCraftingState(1);
	setCraftingState(1);
	dplay9->close();
	player->sendMessage(dplay9);
	
	// Tool Start
	// Obj Controller Msg
	ObjectControllerMessage* ocm = new ObjectControllerMessage(player->getObjectID(),0x0B, 0x102);
	
	ocm->insertLong(getObjectID());
	ocm->insertLong(0x00);
	
	uint32 draftSchematicListSize = player->getDraftSchematicListSize();
	ocm->insertInt(draftSchematicListSize);
	
	for(int i = 0; i < draftSchematicListSize; i++) {
		DraftSchematic* ds = player->getDraftSchematic(i);
		ocm->insertInt(ds->getSchematicID());
		ocm->insertInt(ds->getSchematicCRC());
		ocm->insertInt(ds->getCraftingToolTab());		// this number decides what tab the schematic goes in (ex: 4 = food tab in crafting window)
	}
	player->sendMessage(ocm);

	// This is inefficent but for now it works fine
	// Sends all the ingredients and experimental props to the player
	
	for(int i = 0; i < draftSchematicListSize; i++) {
		DraftSchematic* ds = player->getDraftSchematic(i);
		if(ds != NULL) {
			ds->sendIngredientsToPlayer(player);
			ds->sendExperimentalPropertiesToPlayer(player);
		}
	}
	
	player->setCurrentCraftingTool(_this);
}

void CraftingToolImplementation::addAttributes(AttributeListMessage* alm) {

	alm->insertAttribute("condition", "100/100");
	alm->insertAttribute("volume", "1");
	alm->insertAttribute("craft_tool_effectiveness", effectiveness);
	if (isReady())
		alm->insertAttribute("craft_tool_status", "@crafting:tool_status_ready");
	alm->insertAttribute("crafter", "Kyle");
	alm->insertAttribute("serial_number", "(98u1p5d5)");
	
}
