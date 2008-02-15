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

#include "../../../managers/item/ItemManager.h"

#include "../TangibleObject.h"

#include "engine/engine.h"

#include "AttachmentImplementation.h"

#include "../../../packets.h"

AttachmentImplementation::AttachmentImplementation(uint64 objID, int type) :
	AttachmentServant(objID, attachmentType) {

	attachmentType = type;
	objectID = objID;
	
	initialize();
}

AttachmentImplementation::~AttachmentImplementation()
{
}

void AttachmentImplementation::initialize() { 
 	
	skillMod0Type = 0;
	skillMod0Value = 0;
	
	skillMod1Type = 0;
	skillMod1Value = 0;
	
	skillMod2Type = 0;
	skillMod2Value = 0;
	
	objectType = SceneObjectImplementation::TANGIBLE;

	if (attachmentType == ARMOR) {
		objectCRC = 0xDF144F5C;
		objectSubType = TangibleObjectImplementation::ARMORATTACHMENT;
		name = unicode("\\#ffff00Armor Attachment");
		templateName = "object/tangible/gem/shared_armor.iff";
	} else {
		objectCRC = 0xC0FCFE34;
		objectSubType = TangibleObjectImplementation::CLOTHINGATTACHMENT;
		name = unicode("\\#ffff00Clothing Attachment");
		templateName = "object/tangible/gem/shared_clothing.iff";
	}
	
	templateTypeName = "weapon_name";

	persistent = false;
	updated = false;
	equipped = false;
}

void AttachmentImplementation::parseItemAttributes() {
	
	string name = "skillMod0Type";
	skillMod0Type = itemAttributes->getIntAttribute(name);
	name = "skillMod0Value";
	skillMod0Value = itemAttributes->getIntAttribute(name);

	name = "skillMod1Type";
	skillMod1Type = itemAttributes->getIntAttribute(name);
	name = "skillMod1Value";
	skillMod1Value = itemAttributes->getIntAttribute(name);
	
	name = "skillMod2Type";
	skillMod2Type = itemAttributes->getIntAttribute(name);
	name = "skillMod2Value";
	skillMod2Value = itemAttributes->getIntAttribute(name);
	
}

void AttachmentImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;
		
	Player* player = (Player*) obj;
	
	AttributeListMessage* alm = new AttributeListMessage(_this);
	
	if (skillMod0Value > 0)
		generateSkillMods(alm,skillMod0Type,skillMod0Value);
	if (skillMod1Value > 0)
		generateSkillMods(alm,skillMod1Type,skillMod1Value);
	if (skillMod2Value > 0)
		generateSkillMods(alm,skillMod2Type,skillMod2Value);
	
	player->sendMessage(alm);
}

void AttachmentImplementation::generateSkillMods(AttributeListMessage* alm, int skillModType, int skillModValue) {
	switch (skillModType) {
	case 1:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:melee_defense", skillModValue);
		break;
	case 2:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:ranged_defense", skillModValue);
		break;
	case 3:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:stun_defense", skillModValue);
		break;
	case 4:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:dizzy_defense", skillModValue);
		break;
	case 5:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:blind_defense", skillModValue);
		break;
	case 6:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:knockdown_defense", skillModValue);
		break;
	case 7:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:intimidate_defense", skillModValue);
		break;
	case 8:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:pistol_speed", skillModValue);
		break;
	case 9:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:carbine_speed", skillModValue);
		break;
	case 10:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:rifle_speed", skillModValue);
		break;
	case 11:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:unarmed_speed", skillModValue);
		break;
	case 12:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:onehandmelee_speed", skillModValue);
		break;
	case 13:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:twohandmelee_speed", skillModValue);
		break;
	case 14:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:polearm_speed", skillModValue);
		break;
	case 15:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:pistol_accuracy", skillModValue);
		break;
	case 16:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:carbine_accuracy", skillModValue);
		break;
	case 17:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:rifle_accuracy", skillModValue);
		break;
	case 18:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:unarmed_accuracy", skillModValue);
		break;
	case 19:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:onehandmelee_accuracy", skillModValue);
		break;
	case 20:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:twohandmelee_accuracy", skillModValue);
		break;
	case 21:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:polearm_accuracy", skillModValue);
		break;
	case 22:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:dodge", skillModValue);
		break;
	case 23:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:block", skillModValue);
		break;
	case 24:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:counterattack", skillModValue);
		break;
	case 25:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:resistance_bleeding", skillModValue);
		break;
	case 26:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:resistance_disease", skillModValue);
		break;
	case 27:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:resistance_fire", skillModValue);
		break;
	case 28:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:resistance_poison", skillModValue);
		break;
	case 29:
		alm->insertAttribute("cat_skill_mod_bonus.@stat_n:slope_move", skillModValue);
		break;
	}
}

void AttachmentImplementation::setSkillModValue(int index, int value) {
	switch (index) {
	case 0:
		setSkillMod0Value(value);
		break;
	case 1:
		setSkillMod1Value(value);
		break;
	case 2:
		setSkillMod2Value(value);
		break;
	}
}

void AttachmentImplementation::setSkillModType(int index, int type) {
	switch (index) {
	case 0:
		setSkillMod0Type(type);
		break;
	case 1:
		setSkillMod1Type(type);
		break;
	case 2:
		setSkillMod2Type(type);
		break;
	}
}

int AttachmentImplementation::getSkillModType(int index) {
	switch (index) {
	case 0:
		return skillMod0Type;
		break;
	case 1:
		return skillMod1Type;
		break;
	case 2:
		return skillMod2Type;
		break;
	}
	return -1;
}

int AttachmentImplementation::getSkillModValue(int index) {
	switch (index) {
	case 0:
		return skillMod0Value;
		break;
	case 1:
		return skillMod1Value;
		break;
	case 2:
		return skillMod2Value;
		break;
	}
	return 0;
}

int AttachmentImplementation::getBestSkillMod() {
	int index = -1;
	int skillModValue = 0;
	
	if (skillMod0Value > skillModValue) {
		skillModValue = skillMod0Value;
		index = 0;
	}
	if (skillMod1Value > skillModValue) {
		skillModValue = skillMod1Value;
		index = 1;
	}
	if (skillMod2Value > skillModValue) {
		skillModValue = skillMod2Value;
		index = 2;
	}
	return index;
}

void AttachmentImplementation::setSkillMods(int modifier) {
	int luck = (System::random(100)) + (modifier/4);
		
	if (System::random(1000) == 7)
		luck = luck * 2;
	
	if (System::random(50000) == 77)
		luck = luck * 5;
		
	if (System::random(1000000) == 777)
		luck = luck * 10;
	
	if (System::random(100) == 6)
		luck = 0;
		
	modifier = modifier + System::random(10);
	
	int playerRoll = System::random(1000) * modifier * luck / 1000;
	
	if (playerRoll > 200000) {
		luck = luck + 150;
	} else if (playerRoll > 45000) {
		luck = luck + 100;
	} else if (playerRoll > 12500) {
		luck = luck + 50;
	}
	
	setSkillMod0Type(System::random(28) + 1);
	setSkillMod0Value((luck / (System::random(3) + 10)) + 1);
	
	if (System::random(4) == 1) {
		setSkillMod1Type(System::random(28) + 1);
		setSkillMod1Value((luck / (System::random(3) + 10)) + 1);
	}
	if (System::random(8) == 1) {
		setSkillMod2Type(System::random(28) + 1);
		setSkillMod2Value((luck / (System::random(3) + 10)) + 1);
	}
	if (skillMod0Value > 25)
		setSkillMod0Value(25);

	if (skillMod1Value > 25)
		setSkillMod1Value(25);

	if (skillMod2Value > 25)
		setSkillMod2Value(25);
	
	if (skillMod2Type == skillMod1Type || skillMod2Type == skillMod0Type) {
		setSkillMod2Type(0);
		setSkillMod2Value(0);
	}
	
	if (skillMod1Type == skillMod0Type || skillMod1Type == skillMod2Type) {
		setSkillMod1Type(0);
		setSkillMod1Value(0);
	}
}

void AttachmentImplementation::remove(Player* player) {
	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();
	
	itemManager->deletePlayerItem(player, _this, false);
	
	player->removeInventoryItem(objectID);
	
	BaseMessage* msg = new SceneObjectDestroyMessage(objectID);
	player->sendMessage(msg);
	
}
