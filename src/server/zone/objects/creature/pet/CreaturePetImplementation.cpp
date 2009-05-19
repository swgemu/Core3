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

#include "CreaturePetImplementation.h"
#include "CreaturePet.h"

#include "../Creature.h"
#include "../CreatureImplementation.h"
#include "../CreatureObject.h"
#include "../CreatureObjectImplementation.h"

#include "../../player/Player.h"

#include "../../intangible/IntangibleObject.h"
#include "../../intangible/IntangibleObjectImplementation.h"

#include "../../../packets.h"
#include "../../../packets/creature/CreatureObjectMessage3.h"

#include "../../../ZoneClientSession.h"
#include "../../tangible/Datapad.h"

#include "../../../managers/creature/CreatureManagerImplementation.h"
#include "../../../ZoneProcessServerImplementation.h"

#include "events/CreaturePetIncapacitationRecoveryEvent.h"
#include "events/CreaturePetGrowEvent.h"

#include "../../../objects.h"
#include "../../../managers/combat/CommandQueueAction.h"
#include "../../../managers/combat/CombatManager.h"
#include "../../../managers/item/ItemManager.h"
#include "../../../managers/group/GroupManager.h"
#include "../buffs/Buff.h"

CreaturePetImplementation::CreaturePetImplementation(Player* owner, uint64 oid) : CreaturePetServant(oid) ,VehicleObject(owner){
	creatureLinkID = owner->getObjectID();

	setLinkedCreature(owner);

	objectCRC  = 0;

	objectType = NONPLAYERCREATURE;
	setCreatureType("PET");
	StringBuffer loggingname;
	loggingname << "Pet = 0x" << oid;
	setLoggingName(loggingname.toString());

	pvpStatusBitmask = 0x01;

	setHeight(growth);
	setLastGrowth(lastGrowth.getTime());

	setInternalNPCDamageModifier(1.0f);
	init();
}

CreaturePetImplementation::~CreaturePetImplementation() {

	delete itemAttributes;

	itemAttributes = NULL;

	delete commandHelper;

	commandHelper = NULL;

	delete befriendList;

	befriendList = NULL;

	followTarget = NULL;
}

void CreaturePetImplementation::init() {
	commandHelper = new PetCommandHelper();
	commandToTrain = -1;
	setZone(getLinkedCreature()->getZone());
	setZoneProcessServer(getLinkedCreature()->getZoneProcessServer());

	inventory = NULL;

	lootContainer = NULL;

	nextAttack = -1;

	befriendList = new PetFriendSet();

	trainingPhase = -1;
	trainingPhaseCounter = 0;

	positionCounter = 0;
	formation = FORMATIONNONE;

	//nextPatrolPoint = 0;
	attackGrowth = 0;
}

void CreaturePetImplementation::init(Creature* creature, float growth) {
	if (creature == NULL)
		return;

	setCreatureType("PET");

	setGrowth(growth);
	setHeight(growth);

	// init species
	setObjectCRC(creature->getObjectCRC());

	setStfFile(creature->getStfFile());
	setStfName(creature->getStfName());
	setCustomName(creature->getCustomName());
	setPetType(CHPET);

	//copy ham & bar stat
	setBaseHealth(creature->getBaseHealth());
	setHealthMax((int) ((float)getBaseHealth() * growth));
	setHealth((int) ((float)getBaseHealth() * growth));

	setBaseStrength(creature->getBaseStrength());
	setStrengthMax(getBaseStrength());
	setStrength(getBaseStrength());

	setBaseConstitution(creature->getBaseConstitution());
	setConstitutionMax(getBaseConstitution());
	setConstitution(getBaseConstitution());

	setBaseAction(creature->getBaseAction());
	setActionMax((int) ((float)getBaseAction() * growth));
	setAction((int) ((float)getBaseAction() * growth));

	setBaseQuickness(creature->getBaseQuickness());
	setQuicknessMax(getBaseQuickness());
	setQuickness(getBaseQuickness());

	setBaseStamina(creature->getBaseStamina());
	setStaminaMax(getBaseStamina());
	setStamina(getBaseStamina());

	setBaseMind(creature->getBaseMind());
	setMindMax((int) ((float)getBaseMind() * growth));
	setMind((int) ((float)getBaseMind() * growth));

	setBaseFocus(creature->getBaseFocus());
	setFocusMax(getBaseFocus());
	setFocus(getBaseFocus());

	setBaseWillpower(creature->getBaseWillpower());
	setWillpowerMax(getBaseWillpower());
	setWillpower(getBaseWillpower());

	// copy armor
	setArmor(creature->getArmor());
	setKinetic(creature->getArmorResist(1));
	setEnergy(creature->getArmorResist(2));
	setElectricity(creature->getArmorResist(3));
	setStun(creature->getArmorResist(4));
	setBlast(creature->getArmorResist(5));
	setHeat(creature->getArmorResist(6));
	setCold(creature->getArmorResist(7));
	setAcid(creature->getArmorResist(8));
	setLightSaber(creature->getArmorResist(9));

	if (zone == NULL)
		return;

	loadItems();

	if (server == NULL)
		return;


	SkillManager* sManager = server->getSkillManager();

	if (sManager == NULL) {
		return;
	}

	Skill* skill;

	for (int i = 0; i < creature->getNumberOfSkills() ;i++) {
		skill = sManager->getSkill(creature->getSkill(i));
		if (skill != NULL) {
			addSkill(skill);
		}
	}

	String defaultAttack = "attack";
	skill = sManager->getSkill(defaultAttack);

	if (skill != NULL) {
		setDefaultSkill(skill);
	}

	CreatureManager* creatureManager = zone->getCreatureManager();

	if (creatureManager == NULL) {
		return;
	}

	creatureManager->setPetDefaultAttributes(_this,true,false);


	createItemAttributes();
}

void CreaturePetImplementation::createItemAttributes() {
	String attr;

	//init species
	attr = "petType";
	itemAttributes->setIntAttribute(attr, petType);

	attr = "stfFile";
	itemAttributes->setStringAttribute(attr, getStfFile());

	attr = "stfName";
	itemAttributes->setStringAttribute(attr, getStfName());

	attr = "health";
	itemAttributes->setIntAttribute(attr, getBaseHealth());
	attr = "strength";
	itemAttributes->setIntAttribute(attr, getBaseStrength());
	attr = "constitution";
	itemAttributes->setIntAttribute(attr, getBaseConstitution());
	attr = "action";
	itemAttributes->setIntAttribute(attr, getBaseAction());
	attr = "quickness";
	itemAttributes->setIntAttribute(attr, getBaseQuickness());
	attr = "stamina";
	itemAttributes->setIntAttribute(attr, getBaseStamina());
	attr = "mind";
	itemAttributes->setIntAttribute(attr, getBaseMind());
	attr = "focus";
	itemAttributes->setIntAttribute(attr, getBaseFocus());
	attr = "willpower";
	itemAttributes->setIntAttribute(attr, getBaseWillpower());

	attr = "numSkill";
	itemAttributes->setIntAttribute(attr, getNumberOfSkills());
	for (int i = 0 ;  i < getNumberOfSkills() ; i++) {
		StringBuffer skillAttr;
		skillAttr << "skill_" << i;
		itemAttributes->setStringAttribute(skillAttr.toString(), getSkill(i));
	}

	for (int i = 0 ;  i < 20 ; i++) {
		StringBuffer customCommand;
		customCommand << "command_" << i;
		itemAttributes->setStringAttribute(customCommand.toString(), commandHelper->getBaseCommand(i));
	}

}

void CreaturePetImplementation::parseItemAttributes() {
	String attr;

	attr = "growth";
	setGrowth(itemAttributes->getFloatAttribute(attr));
	setHeight(growth);

	attr = "lastGrowth";
	setLastGrowth(itemAttributes->getUnsignedLongAttribute(attr));

	attr = "attackGrowth";
	setAttackGrowth(itemAttributes->getUnsignedLongAttribute(attr));

	attr = "petType";
	setPetType(itemAttributes->getIntAttribute(attr));

	//init species
	attr = "stfFile";
	setStfFile(itemAttributes->getStringAttribute(attr));

	attr = "stfName";
	setStfName(itemAttributes->getStringAttribute(attr));

	attr = "petType";
	setPetType((uint8)itemAttributes->getIntAttribute(attr));

	attr = "maxLevel";
	setMaxLevel(itemAttributes->getIntAttribute(attr));

	attr = "health";
	int health = itemAttributes->getIntAttribute(attr);
	setBaseHealth(health);
	setHealthMax((int) ((float)health * growth));
	setHealth((int) ((float)health * growth));

	attr = "strength";
	int strength = itemAttributes->getIntAttribute(attr);
	setBaseStrength(strength);
	setStrengthMax(strength);
	setStrength(strength);

	attr = "constitution";
	int constitution = itemAttributes->getIntAttribute(attr);
	setBaseConstitution(constitution);
	setConstitutionMax(constitution);
	setConstitution(constitution);

	attr = "action";
	int action = itemAttributes->getIntAttribute(attr);
	setBaseAction(action);
	setActionMax((int) ((float)action * growth));
	setAction((int) ((float)action * growth));

	attr = "quickness";
	int quickness = itemAttributes->getIntAttribute(attr);
	setBaseQuickness(quickness);
	setQuicknessMax(quickness);
	setQuickness(quickness);

	attr = "stamina";
	int stamina = itemAttributes->getIntAttribute(attr);
	setBaseStamina(stamina);
	setStaminaMax(stamina);
	setStamina(stamina);

	attr = "mind";
	int mind = itemAttributes->getIntAttribute(attr);
	setBaseMind(mind);
	setMindMax((int) ((float)mind * growth));
	setMind((int) ((float)mind * growth));

	attr = "focus";
	int focus = itemAttributes->getIntAttribute(attr);
	setBaseFocus(focus);
	setFocusMax(focus);
	setFocus(focus);

	attr = "willpower";
	int willpower = itemAttributes->getIntAttribute(attr);
	setBaseWillpower(willpower);
	setWillpowerMax(willpower);
	setWillpower(willpower);

	if (zone == NULL)
		return;

	CreatureManager* creatureManager = zone->getCreatureManager();

	loadItems();

	if (server == NULL)
		return;

	SkillManager* sManager = server->getSkillManager();

	if (sManager == NULL) {
		return;
	}

	Skill* skill;
	attr = "numSkill";
	String skillName;

	int skillNumber = itemAttributes->getIntAttribute(attr);
	for (int i = 0 ;  i < skillNumber ; i++) {
		StringBuffer skillAttr;
		skillAttr << "skill_" << i;
		skillName = itemAttributes->getStringAttribute(skillAttr.toString());
		skill = sManager->getSkill(skillName);
		if (skill != NULL) {
			addSkill(skill);
		}
	}

	String defaultAttack = "attack";
	skill = sManager->getSkill(defaultAttack);

	if (skill != NULL) {
		setDefaultSkill(skill);
	}

	String customCommand;
	for (int i = 0 ;  i < 20 ; i++) {
		StringBuffer commandAttr;
		commandAttr << "command_" << i;
		customCommand = itemAttributes->getStringAttribute(commandAttr.toString());
		commandHelper->trainCommand(i,customCommand);
	}


	if (creatureManager == NULL) {
		return;
	}

	creatureManager->setPetDefaultAttributes(_this,false,false);

	if (isMount()) {
		trainMount();
	}
}

void CreaturePetImplementation::loadItems() {
	inventory = NULL;
	lootContainer = NULL;

	Weapon* weapon = NULL;

	String wpName = getCreatureWeaponName();
	if (wpName != "") {
		try {
			String wpObject = getCreatureWeapon();
			String wpName = getCreatureWeaponName();
			String wpTemp = getCreatureWeaponTemp();
			bool wpEq = (bool) getCreatureWeaponEquipped();
			int wpMinDamage = (int)((float) getCreatureWeaponMinDamage() * growth);
			int wpMaxDamage = (int)((float) getCreatureWeaponMaxDamage() * growth);
			float wpAttackSpeed = getCreatureWeaponAttackSpeed();
			String wpDamType = getCreatureWeaponDamageType();
			String wpArmorPiercing = getCreatureWeaponArmorPiercing();
			String wpClass = getCreatureWeaponClass();

			if (wpClass == "CarbineRangedWeapon")
				weapon = new CarbineRangedWeapon(_this, wpObject, UnicodeString(
						wpName), wpTemp, wpEq);
			else if (wpClass == "RifleRangedWeapon")
				weapon
						= new RifleRangedWeapon(_this, wpObject, UnicodeString(wpName), wpTemp, wpEq);
			else if (wpClass == "PistolRangedWeapon")
				weapon
						= new PistolRangedWeapon(_this, wpObject, UnicodeString(
								wpName), wpTemp, wpEq);
			else if (wpClass == "UnarmedMeleeWeapon")
				weapon
						= new UnarmedMeleeWeapon(_this, wpObject, UnicodeString(
								wpName), wpTemp, wpEq);
			else if (wpClass == "OneHandedMeleeWeapon")
				weapon = new OneHandedMeleeWeapon(_this, wpObject, UnicodeString(
						wpName), wpTemp, wpEq);
			else if (wpClass == "TwoHandedMeleeWeapon")
				weapon = new TwoHandedMeleeWeapon(_this, wpObject, UnicodeString(
						wpName), wpTemp, wpEq);
			else if (wpClass == "PolearmMeleeWeapon")
				weapon
						= new PolearmMeleeWeapon(_this, wpObject, UnicodeString(
								wpName), wpTemp, wpEq);
			else if (wpClass == "OneHandedJediWeapon")
				weapon = new OneHandedJediWeapon(_this, wpObject, UnicodeString(
						wpName), wpTemp, wpEq);
			else if (wpClass == "TwoHandedJediWeapon")
				weapon = new TwoHandedJediWeapon(_this, wpObject, UnicodeString(
						wpName), wpTemp, wpEq);
			else if (wpClass == "PolearmJediWeapon")
				weapon
						= new PolearmJediWeapon(_this, wpObject, UnicodeString(wpName), wpTemp, wpEq);
			else if (wpClass == "SpecialHeavyRangedWeapon")
				weapon = new SpecialHeavyRangedWeapon(_this, wpObject, UnicodeString(
						wpName), wpTemp, wpEq);
			else if (wpClass == "HeavyRangedWeapon")
				weapon
						= new HeavyRangedWeapon(_this, wpObject, UnicodeString(wpName), wpTemp, wpEq);

			//DAMAGE TYPE
			if (wpDamType == "ENERGY")
				weapon->setDamageType(WeaponImplementation::ENERGY);
			else if (wpDamType == "KINECTIC")
				weapon->setDamageType(WeaponImplementation::KINETIC);
			else if (wpDamType == "ELECTRICITY")
				weapon->setDamageType(WeaponImplementation::ELECTRICITY);
			else if (wpDamType == "STUN")
				weapon->setDamageType(WeaponImplementation::STUN);
			else if (wpDamType == "BLAST")
				weapon->setDamageType(WeaponImplementation::BLAST);
			else if (wpDamType == "HEAT")
				weapon->setDamageType(WeaponImplementation::HEAT);
			else if (wpDamType == "COLD")
				weapon->setDamageType(WeaponImplementation::COLD);
			else if (wpDamType == "ACID")
				weapon->setDamageType(WeaponImplementation::ACID);
			else if (wpDamType == "LIGHTSABER")
				weapon->setDamageType(WeaponImplementation::LIGHTSABER);

			//ARMOR PIERCING
			if (wpArmorPiercing == "NONE")
				weapon->setArmorPiercing(WeaponImplementation::NONE);
			else if (wpArmorPiercing == "LIGHT")
				weapon->setArmorPiercing(WeaponImplementation::LIGHT);
			else if (wpArmorPiercing == "MEDIUM")
				weapon->setArmorPiercing(WeaponImplementation::MEDIUM);
			else if (wpArmorPiercing == "HEAVY")
				weapon->setArmorPiercing(WeaponImplementation::HEAVY);

			//MODFIERS
			weapon->setMinDamage(wpMinDamage);
			weapon->setMaxDamage(wpMaxDamage);
			weapon->setAttackSpeed(wpAttackSpeed);
			weapon->setEquipped(true);

			setWeapon(weapon);
		} catch (...) {
			System::out
					<< "exception CreaturePetImplementation::loadItems()  -  Weaponloading for creature "
					<< objectID << "\n";
			return;
		}
	} else
		return;
}

void CreaturePetImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::sendRadialResponseTo() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	if (!commandHelper->getBaseCommand(PetCommandHelper::PETGROUP).isEmpty()) {
		if (getGroupID() != 0 && player->getGroupID() == getGroupID()) {
			if (player == player->getGroupObject()->getLeader()) {
				if (getGroupID() == player->getGroupID()) {
					RadialMenuParent* kick = new RadialMenuParent(40, 1, "Kick from Group");
					kick->addRadialMenuItem(41, 3, "Disband");
					omr->addRadialParent(kick);
				}
				else
					omr->addRadialParent(37, 3, "Group Invite");
			}
		} else if ((player == getLinkedCreature() && getLinkedCreature()->getGroupID() == 0) ||
				(getLinkedCreature()->getGroupID() != 0 && player->getGroupID() == getLinkedCreature()->getGroupID() && player == getLinkedCreature()->getGroupObject()->getLeader())) {
				omr->addRadialParent(37, 3, "Group Invite");
		}
	}

	if (player == getLinkedCreature() && isMount()) {
		if (isMountedCreature())
			omr->addRadialParent(206, 1, "@pet/pet_menu:menu_dismount");
		else
			omr->addRadialParent(205, 1, "@pet/pet_menu:menu_mount");
	}

	String skillBox = "outdoors_creaturehandler_novice";
	if (!player->hasSkillBox(skillBox)) {
		omr->finish();

		player->sendMessage(omr);
		return;
	}
	if (player == getLinkedCreature()) {
		omr->addRadialParent(59, 3, "");

		RadialMenuParent* training = new RadialMenuParent(141, 1, "Training");
		training->addRadialMenuItem(146, 3, commandHelper->getStfDesc(PetCommandHelper::PETATTACK));
		training->addRadialMenuItem(142, 3, commandHelper->getStfDesc(PetCommandHelper::PETFOLLOW));
		training->addRadialMenuItem(160, 3, commandHelper->getStfDesc(PetCommandHelper::PETSTORE));

		String skillBox = "outdoors_creaturehandler_taming_03";
		if (player->hasSkillBox(skillBox))
			training->addRadialMenuItem(161, 3, commandHelper->getStfDesc(PetCommandHelper::PETSPECIALATTACK1));

		skillBox = "outdoors_creaturehandler_taming_04";
		if (player->hasSkillBox(skillBox))
			training->addRadialMenuItem(162, 3, commandHelper->getStfDesc(PetCommandHelper::PETSPECIALATTACK2));

		skillBox = "outdoors_creaturehandler_training_01";
		if (player->hasSkillBox(skillBox))
			training->addRadialMenuItem(143, 3, commandHelper->getStfDesc(PetCommandHelper::PETSTAY));

		skillBox = "outdoors_creaturehandler_training_02";
		if (player->hasSkillBox(skillBox))
			training->addRadialMenuItem(144, 3, commandHelper->getStfDesc(PetCommandHelper::PETGUARD));

		skillBox = "outdoors_creaturehandler_training_03";
		if (player->hasSkillBox(skillBox)) {
			training->addRadialMenuItem(147, 3, commandHelper->getStfDesc(PetCommandHelper::PETPATROL));
			training->addRadialMenuItem(148, 3, commandHelper->getStfDesc(PetCommandHelper::PETPATROLPOINTADD));
			training->addRadialMenuItem(149, 3, commandHelper->getStfDesc(PetCommandHelper::PETPATROLPOINTCLEAR));
		}
		skillBox = "outdoors_creaturehandler_training_04";
		if (getLinkedCreature()->hasSkillBox(skillBox)) {
			training->addRadialMenuItem(150, 3, commandHelper->getStfDesc(PetCommandHelper::PETFORMATION1));
			training->addRadialMenuItem(151, 3, commandHelper->getStfDesc(PetCommandHelper::PETFORMATION2));
		}
		skillBox = "outdoors_creaturehandler_healing_01";
		if (player->hasSkillBox(skillBox))
			training->addRadialMenuItem(154, 3, commandHelper->getStfDesc(PetCommandHelper::PETTRICK1));

		skillBox = "outdoors_creaturehandler_healing_03";
		if (player->hasSkillBox(skillBox))
			training->addRadialMenuItem(155, 3, commandHelper->getStfDesc(PetCommandHelper::PETTRICK2));

		skillBox = "outdoors_creaturehandler_support_01";
		if (player->hasSkillBox(skillBox))
			training->addRadialMenuItem(158, 3, commandHelper->getStfDesc(PetCommandHelper::PETGROUP));

		skillBox = "outdoors_creaturehandler_support_01";
		if (player->hasSkillBox(skillBox) && !isMount() && isMountTrainable())
			omr->addRadialParent(157, 3, "Train Mount");

		skillBox = "outdoors_creaturehandler_support_02";
		if (getLinkedCreature()->hasSkillBox(skillBox))
			training->addRadialMenuItem(156, 3, commandHelper->getStfDesc(PetCommandHelper::PETFOLLOWOTHER));

		skillBox = "outdoors_creaturehandler_support_03";
		if (player->hasSkillBox(skillBox))
			training->addRadialMenuItem(145, 3, commandHelper->getStfDesc(PetCommandHelper::PETFRIEND));

		skillBox = "outdoors_creaturehandler_master";
		if (player->hasSkillBox(skillBox)){
			training->addRadialMenuItem(163, 3, commandHelper->getStfDesc(PetCommandHelper::PETRANGEDATTACK));
			//training->addRadialMenuItem(153, 3, commandHelper->getStfDesc(PetCommandHelper::PETRELEASE));
			training->addRadialMenuItem(159, 3, commandHelper->getStfDesc(PetCommandHelper::PETTRANSFER));
		}
		omr->addRadialParent(training);
	}

	omr->finish();

	player->sendMessage(omr);
}

void CreaturePetImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	create(client);

	BaseMessage* creo3 = new CreatureObjectMessage3(_this);
	client->sendMessage(creo3);

	BaseMessage* creo6 = new CreatureObjectMessage6(_this);
	client->sendMessage(creo6);

	sendFactionStatusTo(player);

	if (isMountedCreature()) {
		getLinkedCreature()->sendTo(player);
		getLinkedCreature()->sendItemsTo(player);
	}

	if (doClose)
		SceneObjectImplementation::close(client);
}

void CreaturePetImplementation::addAttributes(AttributeListMessage* alm) {
	alm->insertAttribute("@obj_attr_n:creature_vitality" ,":)");
	for (int i = 0 ; i < commandHelper->size() ; i++) {
		String cmd = commandHelper->getBaseCommand(i);

		if (!cmd.isEmpty())
			alm->insertAttribute(commandHelper->getStfDesc(i),cmd);
	}
}


void CreaturePetImplementation::createDataPad(uint32 datapadCRC) {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::createDatapadItem() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	 Datapad* datapad = getLinkedCreature()->getDatapad();

	 if (datapadCRC == 0)
		 datapadCRC = 0x413FB544;

	 String cName = customName.toString();

	 setDatapadItem(new IntangibleObject(getLinkedCreature()->getNewItemID(), cName, stfFile,
			 stfName, datapadCRC, (SceneObject*) datapad));

	try {
		getDatapadItem()->setWorldObject(_this);
		getDatapadItem()->setParent(datapad);

		getLinkedCreature()->addDatapadItem(getDatapadItem());

		getDatapadItem()->sendTo(getLinkedCreature(), true);
		getLinkedCreature()->sendSystemMessage("pet/pet_menu","device_added");

	} catch(...) {
		System::out << "Unreported exception caught in CreaturePetImplementation::createDataPad\n";
		return;
	}
}

void CreaturePetImplementation::call() {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::call() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	if (!canCall())
		return;

	if (isInQuadTree())
		return;

	try {
		parent = NULL;
		getLinkedCreature()->wlock(_this);

		if (getLinkedCreature()->getParent() != NULL) {
			getLinkedCreature()->unlock();
			return;
		}

		if (getLinkedCreature()->isInCombat()) {
			getLinkedCreature()->unlock();
			return;
		}

		zone = getLinkedCreature()->getZone();

		if (zone == NULL) {
			getLinkedCreature()->unlock();
			return;
		}
		getLinkedCreature()->unlock();

		handleFollowCommand(getLinkedCreature());

		Coordinate* pos = calculateRelativePosition();

		initializePosition(pos->getPositionX(),
				zone->getHeight(pos->getPositionX(), pos->getPositionY()),
				pos->getPositionY());

		if (getDatapadItem() != NULL) {
			getDatapadItem()->wlock();
			getDatapadItem()->updateStatus(1);
			getDatapadItem()->unlock();
		}

		setFaction(getLinkedCreature()->getFaction());

		befriendList->add(getLinkedCreature());
		getLinkedCreature()->registerPet(_this);
		getLinkedCreature()->setNumberOfCHPets(getLinkedCreature()->getNumberOfCHPets() + 1);
		getLinkedCreature()->setLevelOfCHPets(getLinkedCreature()->getLevelOfCHPets() + getLevel());

		if (zone == NULL) {
			getLinkedCreature()->unlock();
			return;
		}
		CreatureManager* cManager = zone->getCreatureManager();

		if (cManager == NULL) {
			getLinkedCreature()->unlock();
			return;
		}

		cManager->insertCreaturePet(_this);

		if (growth < 1.0f)	{
			doGrowUp();
		}
		cManager->insertCreaturePet(_this);

	} catch (Exception& e) {
		getLinkedCreature()->unlock();

		error("calling CreaturePet");
		error(e.getMessage());
	}
}

void CreaturePetImplementation::store(bool doLock) {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::store() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	//System::out << "store\n";
	if (zone == NULL || getLinkedCreature() == NULL || !isInQuadTree())
		return;

	if (isInCombat() || getLinkedCreature()->isInCombat() || isIncapacitated() || getLinkedCreature()->isIncapacitated())
		return;

	try {
		if (isMountedCreature()) {
			getLinkedCreature()->dismount(false,true);
		}

		if (getDatapadItem() != NULL) {
			getDatapadItem()->wlock();

			getDatapadItem()->updateStatus(0);

			getDatapadItem()->unlock();
		}
		if (isQueued() && creatureManager != NULL)
			creatureManager->dequeueActivity(this);

		removeFromZone();
		for (int i = 0 ; i < befriendList->size() ; i++) {
			Player* petFriend = befriendList->get(i);
			petFriend->unregisterPet(_this);
		}
		befriendList->removeAll();

		if (doLock)
			getLinkedCreature()->lock();
		getLinkedCreature()->unregisterPet(_this);
		getLinkedCreature()->setNumberOfCHPets(getLinkedCreature()->getNumberOfCHPets() - 1);
		getLinkedCreature()->setLevelOfCHPets(getLinkedCreature()->getLevelOfCHPets() - getLevel());
		if (doLock)
			getLinkedCreature()->unlock();

		if (getGroupObject() != NULL) {
			GroupManager* groupManager = server->getGroupManager();
			if (groupManager == NULL)
				return;
			try {
			if(!doLock)
				getLinkedCreature()->unlock();
			groupManager->leaveGroup(getGroupObject(),_this);
			if(!doLock)
				getLinkedCreature()->lock();
			}catch (...) {
				error("CreaturePetImplementation::store()");
				if(!doLock)
					getLinkedCreature()->lock();
			}
		}
	} catch (Exception& e) {
		if (doLock)
			getLinkedCreature()->unlock();
		error("storing CreaturePet");
		error(e.getMessage());
	}
}

bool CreaturePetImplementation::canCall() {
	if (getLinkedCreature() == NULL)
		return false;

	if (isDead()) {
		getLinkedCreature()->sendSystemMessage("pet/pet_menu","dead_pet");
		return false;
	}
	if (isCHPet()) {
		int chSkill = getLinkedCreature()->getSkillMod("tame_level");
		//System::out << "ch level ("<< getLevel() <<")" << chSkill <<"\n";
		if (chSkill < 10)
			chSkill = 10;

		chSkill -= getLinkedCreature()->getLevelOfCHPets();
		//System::out << "ch level rest" << chSkill <<"\n";

		if (isAggressive() && chSkill < 12) {
			getLinkedCreature()->sendSystemMessage("pet/pet_menu","lack_skill");
			return false;
		}

		if (getLevel() > chSkill) {
			getLinkedCreature()->sendSystemMessage("pet/pet_menu","lack_skill");
			return false;
		}

		int chNum = getLinkedCreature()->getSkillMod("keep_creature");
		//System::out << "ch number " << chNum <<"\n";
		if (chNum < 1)
			chNum = 1;

		if (chNum > getLinkedCreature()->getNumberOfCHPets())
			return true;

		getLinkedCreature()->sendSystemMessage("pet/pet_menu","too_many");
		return false;
	}
	else if (isDroid()) {
		return !getLinkedCreature()->hasDroidCalled();
	}
	else if (isFactionPet() && getFaction() == getLinkedCreature()->getFaction()) {
		return !getLinkedCreature()->hasFactionPetCalled();
	}

	return false;
}

bool CreaturePetImplementation::isAttackable() {
	if (getLinkedCreature() == NULL)
		return false;
	return getLinkedCreature()->isAttackable();
}

bool CreaturePetImplementation::isAttackableBy(CreatureObject* creature) {
	if (getLinkedCreature() == NULL)
		return false;
	return getLinkedCreature()->isAttackableBy(creature);
}

void CreaturePetImplementation::setFaction(uint32 fac) {
	if (isFactionPet())
		return;

	faction = fac;
}

void CreaturePetImplementation::onIncapacitated(SceneObject* attacker) {
	deaggro();

	if (isMountedCreature()) {
			getLinkedCreature()->dismount(false,true);
	}

	setPosture(CreaturePosture::INCAPACITATED);

	if (isQueued()) {
		if (creatureManager != NULL)
			creatureManager->dequeueActivity(this);
	}

	CreaturePetIncapacitationRecoveryEvent* incapRecovery = new CreaturePetIncapacitationRecoveryEvent(_this);
	server->addEvent(incapRecovery);
}

void CreaturePetImplementation::recoverFromIncapacitation() {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::recoverFromIncapacitation() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	setPosture(CreaturePosture::UPRIGHT);
	onIncapacitationRecovery();

	doRecovery();

	if (zone != NULL)
		creatureManager->queueActivity(this,10);
}

void CreaturePetImplementation::notifyPositionUpdate(QuadTreeEntry* obj) {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::notifyPositionUpdate() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	if (creatureManager == NULL)
		return;

	if (obj == NULL || obj == this)
		return;

	if (isInStayState() || isMountedCreature()) {
		//System::out << "\ttnotifyPositionUpdate stay || mount\n";
	//	handleStayCommand();
		return;
	}

	SceneObject* scno = (SceneObject*) (((SceneObjectImplementation*) obj)->_getStub());

	if (isInPatrolState()) {
		if (!isInCombat()) {

			if (scno->isPlayer() || scno->isNonPlayerCreature()) {
				System::out << "\tnotifyPositionUpdate : patrol is player\n" ;
				CreatureObject* creature = (CreatureObject*) scno;
				if (creature->isAttackableBy(getLinkedCreature())) {
					if (isInRange(creature,45.0f)) {
						//System::out << "\tnotifyPositionUpdate : attack patrol\n" ;

						aggroedCreature = creature;
						targetObject = aggroedCreature;
					}
				}
			}
		}
		return;
	}

	//System::out << "CreaturePetImplementation::notifyPositionUpdate\n";

	if (isInGuardState()) {
		if (scno != NULL && scno->isNonPlayerCreature() && scno != getLinkedCreature()) {
			CreatureObject* creature = (CreatureObject*) scno;
			if (creature->isInCombat() && creature->getTarget() == followTarget) {
				aggroedCreature = creature;
				targetObject = aggroedCreature;

				if (aggroedCreature != NULL) {
					if (isQueued())
						creatureManager->dequeueActivity(this);

					creatureManager->queueActivity(this, 10);
					return;
				}
			}
		}
	}

	if (scno->isPlayer()) {
		//System::out << "\tnotifyPositionUpdate : is player\n" ;
		Player* player = (Player*) scno;

		if (player == followTarget) {

			//System::out << "\tnotifyPositionUpdate : is owner\n" ;
			if (!followTarget->isInCombat() && aggroedCreature == NULL) {
				//System::out << "\tnotifyPositionUpdate : not aggro\n" ;

				if (aggroedCreature == NULL) {
					//System::out << "\tnotifyPositionUpdate : move to player\n";
					updateNextMovementPosition(calculateRelativePosition());

					//resetPatrolPoints(false);

					//addPatrolPoint(pos->getPositionX(), pos->getPositionX(),false);
				}
			} /*if (isFriend(followTarget) && followTarget->isInCombat() && (aggroedCreature == NULL)) {
				//System::out << "\tnotifyPositionUpdate : aggro player combat\n";

				SceneObject* scno = followTarget->getTarget();
				if (scno != NULL && (scno->isNonPlayerCreature() || scno->isPlayer())) {
					//System::out << "\tnotifyPositionUpdate :aggro more\n";

					if (aggroedCreature != targetObject) {
						//System::out << "\tnotifyPositionUpdate : new target\n";

						aggroedCreature = (CreatureObject*) scno;
					}
					targetObject = aggroedCreature;
					if (isQueued())
						creatureManager->dequeueActivity(this);
					creatureManager->queueActivity(this, 10);
				}
			}*/
		}
	}
}

bool CreaturePetImplementation::activate() {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::activate() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	if (!isInQuadTree())
		return false;
	//System::out << "activate\n";
	if (isIncapacitated()) {
		return false;
	}
	bool needMoreActivity = false;

	try {
		wlock();

		//System::out << "\tactivate : zone check\n";

		if (!checkState() || zone == NULL) {
			unlock();
			return false;
		}

		if (isMountedCreature()) {
			//System::out << "\tactivate : riding recovery\n";

			needMoreActivity |= doRecovery();

			if (zone != NULL && needMoreActivity && creatureManager != NULL) {
				//info("queuing more activities");
				//System::out << "\tactivate : queue\n";
				creatureManager->queueActivity(this);
			}
			unlock();
			return needMoreActivity;
		}

		needMoreActivity |= doMovement();

		if (!isInStayState() && !isMountedCreature()) {
			if (!isInPatrolState() && !isInCombat() && !needMoreActivity && !isInPatrolState()) {
				updateNextMovementPosition(calculateRelativePosition());
			}

			if (!isInPatrolState() && isFriend(followTarget) && followTarget->isInCombat() && !isInCombat()) {
				//System::out << "\tactivate : player is attack\n";
				SceneObject* scno = followTarget->getTarget();
				if (scno != NULL && (scno->isNonPlayerCreature() || scno->isPlayer())) {
					//System::out << "\tactivate :aggro player target\n";

					aggroedCreature = (CreatureObject*) scno;

					if (aggroedCreature != targetObject) {
						//System::out << "\tactivate : new target\n";

						updateTarget(aggroedCreature);
					}
					//updateTarget(aggroedCreature);
				}
			}

			if (aggroedCreature != NULL) {
				if(!aggroedCreature->isAttackableBy(getLinkedCreature())) {
					//System::out << "\tactivate : deaggro\n";
					deaggro();
				} else {
					//System::out << "\tactivate : attack(" << aggroedCreature->getStfName()<<","<< aggroedCreature->getStfFile() <<")\n";
					//System::out << "\tactivate : attack , num skills = " << getNumberOfSkills() <<"\n";

					needMoreActivity |= attack(aggroedCreature);
				}
				if(!isInPatrolState() && !followTarget->isInCombat() && !isInRange(followTarget,70.0f)) {
					//System::out << "\tactivate : abort combat retun to owner\n";
					deaggro();
					updateNextMovementPosition(calculateRelativePosition());
				}

			} else if (isInCombat()) {
				//System::out << "activate : clear combat\n";
				clearCombatState();
				aggroedCreature == NULL;
			}
		}
		//System::out << "\tactivate : recovery\n";
		needMoreActivity |= doRecovery();

		if (zone != NULL && needMoreActivity && creatureManager != NULL) {
			//info("queuing more activities");
			//System::out << "\tactivate : queue\n";
			creatureManager->queueActivity(this);
		}

		unlock();
	} catch (...) {
		System::out << "exception CreaturePetImplementation::activate()\n";

		unlock();
	}

	return needMoreActivity;
}

bool CreaturePetImplementation::attack(CreatureObject* target) {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::attack() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	//info("attacking target");

	if (isMountedCreature()) {
		deaggro();
		return false;
	}
	// Not ready to attack yet
	if (!nextAttackDelay.isPast()) {
		return true;
	}

	if (target == NULL || !target->isAttackableBy(getLinkedCreature())) {
		deaggro();
		return false;
	}

	if (!isInRange(target, 100)) {
		if (((parent != NULL) && (nextPosition->getCellID() == 0)) || (parent
				== NULL && nextPosition->getCellID() != 0))
			return true;
		else {
			deaggro();

			return false;
		}
	}

	if (isDead() || isKnockedDown()) {
		return false;
	}

	Skill* skill = NULL;

	if (nextAttack != -1 && getNumberOfSkills() > nextAttack) {
		skill = getSkillAt(nextAttack);
		nextAttack = -1;
	}

	if (skill == NULL)
		skill = getDefaultSkill();

	uint32 actionCRC = skill->getNameCRC();

	if (weaponObject != NULL
			&& (!isInRange(target, weaponObject->getMaxRange()))) {
		if (!isInRange(target, skill->getRange())) {
			return true;
		}
	} /*else if (!isInRange(target, skill->getRange())) {
		System::out << "PET not in skill range\n";
		return true;
	}*/

	//info("queuing attacking");

	String modifier = "";
	CommandQueueAction* action =
					new CommandQueueAction(_this, target->getObjectID(), 0, actionCRC, modifier);

	action->setSkill(skill);
	action->setTarget(target);

	CombatManager* combatManager = server->getCombatManager();
	combatManager->handleAction(action);

	delete action;

	if (target->isIncapacitated() || target->isDead()) {
		deaggro();
		return false;
	}

	//if (target->isNonPlayerCreature() && target->isMount() && target->isDisabled()) {

	if (target->isVehicle() && target->isDisabled()) {
		deaggro();
		return false;
	}

	lastCombatAction.update();

	float delay = skill->getSpeedRatio();

	if (weaponObject != NULL)
		delay = delay * weaponObject->getAttackSpeed();

	nextAttackDelay.update();
	nextAttackDelay.addMiliTime((uint64) (delay * 1000));

	setAttackGrowth(++attackGrowth);
	return true;
}

void CreaturePetImplementation::deaggro() {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::deaggro() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	CreatureImplementation::deaggro();

	if (!isInStayState()) {
		updateNextMovementPosition(calculateRelativePosition());
	}
}

void CreaturePetImplementation::doGrowUp(bool updateTime) {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::doGrowUp() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}

	Time currentTime;

	uint32 elapsedTime = currentTime.getTime() - lastGrowth.getTime();

	float growCycles = (float)(elapsedTime / 86400);
	if (growCycles < 0.05f)
		return;

	growth += 0.1 * growCycles;
	if (growth > 1.0f)
		growth = 1.0f;

	setHeight(growth);
	setGrowth(growth);
	setBaby(false);

	setHealthMax((int) ((float)getBaseHealth() * growth));
	setHealth(getHealthMax() - getHealthWounds());

	setActionMax((int) ((float)getBaseAction() * growth));
	setAction(getActionMax() - getActionWounds());

	setMindMax((int) ((float)getBaseMind() * growth));
	setMind(getMindMax() - getMindWounds());

	int oldLevel = level;

	setLevel((uint32) ((float)maxLevel * growth));
	getLinkedCreature()->setLevelOfCHPets(getLinkedCreature()->getLevelOfCHPets() -oldLevel + level);

	loadItems();

	if (growth > 0.7) {
		int babyPos = customName.indexOf(UnicodeString(" (baby)"));

		if (babyPos != -1) {
			String newName = customName.subString(0,baby).toString();
			setPetName(newName);
		}
	}

	if (isInQuadTree()) {
		updateHAMBars();

		CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
		dcreo3->updateHeight();
		dcreo3->close();
		broadcastMessage(dcreo3);
	}

	if (growth < 1.0f)	{
		lastGrowth.update();
		setLastGrowth(lastGrowth.getTime() + System::random(13000) - (attackGrowth * 6));
		setAttackGrowth(0);
		CreaturePetGrowEvent* growEvent = new CreaturePetGrowEvent(_this);
		server->addEvent(growEvent);
	}
	getDatapadItem()->setUpdated(true);
}


void CreaturePetImplementation::initTrainingState(int command) {
	//say("?");
	commandToTrain = command;
	if (commandToTrain != trainingPhase) {
		trainingPhaseCounter = 0;
		trainingPhase = commandToTrain;
	}
	showFlyText("npc_reaction/flytext", "alert", 0xFF, 0xFF, 0xFF);

}

void CreaturePetImplementation::setPetName(String& name) {

	customName = name;

	TangibleObjectDeltaMessage3* nameChangeMessage = new TangibleObjectDeltaMessage3(_this);
	nameChangeMessage->updateName(name);
	nameChangeMessage->close();
	broadcastMessage(nameChangeMessage);

	getDatapadItem()->setCustomName(name);
	IntangibleObjectDeltaMessage3* datapadChangeMessage = new IntangibleObjectDeltaMessage3(getDatapadItem());
	datapadChangeMessage->updateName(name);
	datapadChangeMessage->close();

	getLinkedCreature()->sendMessage((StandaloneBaseMessage*)datapadChangeMessage->clone());

}

void CreaturePetImplementation::parseCommandMessage(Player* player, const UnicodeString& message) {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::parseCommandMessage() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}

	if (player != getLinkedCreature()) {
		if (!isFriend(player))
			return;
	}

	//System::out << getObjectID() << " : " << customName.toString() << " says, " << message.toString() << "\n";

	String command = message.toString();
	//System::out << customName.toString() << " command : -" << command << "-\n";
	int namePos = message.indexOf(customName.toString() +" ");

	if (namePos == 0) {
		command = message.subString(customName.length()+1,message.length()).toString();
	}
	//System::out << customName.toString() << " command : -" << command << "-\n";

	if (isInTrainingState()) {
		if (player != getLinkedCreature())
			return;

		if(command.indexOf("\\") != -1 || (System::random(1) == 1 && trainingPhaseCounter < 3)) {
			trainingPhase = commandToTrain;
			trainingPhaseCounter++;
			showFlyText("npc_reaction/flytext", "confused", 0xFF, 0xFF, 0xFF);

			commandToTrain = -1;
			getLinkedCreature()->sendSystemMessage("pet/pet_menu","pet_nolearn");
			return;
		}
		showFlyText("npc_reaction/flytext", "threaten", 0xFF, 0xFF, 0xFF);

		getLinkedCreature()->sendSystemMessage("pet/pet_menu","pet_learn");

		bool newCommand = commandHelper->getBaseCommand(commandToTrain).isEmpty();

		commandHelper->trainCommand(commandToTrain,command);
		commandHelper->trainName(_this);
		commandToTrain = -1;
		trainingPhaseCounter = 0;

		createItemAttributes();
		getDatapadItem()->setUpdated(true);

		if (newCommand) {
			String chType = "creaturehandler";
			getLinkedCreature()->addXp(chType, (200 + 10 * (getLevel() - getLinkedCreature()->getLevel())),true);
		}

		return;
	}

	if (command == commandHelper->getBaseCommand(PetCommandHelper::PETSTORE) && player == getLinkedCreature()) {
		handleStoreCommand();
	} else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETGROUP) && player == getLinkedCreature()) {
		handleGroupCommand(player);
	}

	if (isMountedCreature())
		return;

	if (command == commandHelper->getBaseCommand(PetCommandHelper::PETATTACK)) {
		handleAttackCommand(player);
	}
	else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETFOLLOW)) {
		handleFollowCommand(player);
	}
	else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETGUARD)) {
		handleGuardCommand();
	}
	else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETSTAY)) {
		handleStayCommand();
	}
	else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETTRANSFER) && player == getLinkedCreature()) {
		handleTransferCommand();
	}
	else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETTRICK1) && player == getLinkedCreature()) {
		handleTrickCommand("trick_1",20,-100);
	}
	else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETTRICK2) && player == getLinkedCreature()) {
		handleTrickCommand("trick_2",10,-200);
	}
	else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETSPECIALATTACK1)) {
		handleSpecialAttackCommand(player,0);
	}
	else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETSPECIALATTACK2)) {
		handleSpecialAttackCommand(player,1);
	}
	else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETFOLLOWOTHER)) {
		SceneObject* target = player->getTarget();
		if (target != NULL && target->isPlayer()) {
			handleFollowCommand((Player*) target);
		}
	}
	else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETFRIEND) && player == getLinkedCreature()) {
		handleFriendCommand();
	}
	else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETFORMATION1)) {
		handleFormationCommand(FORMATIONWEDGE);
	}
	else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETFORMATION2)) {
		handleFormationCommand(FORMATIONCOLUM);
	}
	else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETPATROLPOINTADD) && player == getLinkedCreature()) {
		handleAddPatrolPointCommand(player);
	}
	else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETPATROLPOINTCLEAR) && player == getLinkedCreature()) {
		handleClearPatrolPointsCommand();
	}
	else if (command == commandHelper->getBaseCommand(PetCommandHelper::PETPATROL) && player == getLinkedCreature()) {
		handleActivatePatrolCommand();
	}


	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::parseCommandMessage() done " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}

}

void CreaturePetImplementation::handleAttackCommand(Player* player) {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::handleAttackCommand() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	if (player == NULL || creatureManager == NULL)
		return;

	SceneObject* scno = player->getTarget();
	if (scno != NULL && (scno->isNonPlayerCreature() || scno->isPlayer())) {
		//System::out << "\thandleAttackCommand : aggro attack target\n";
		CreatureObject* creo = (CreatureObject*)scno;
		if(!creo->isAttackableBy(getLinkedCreature())) {
			return;
		}
		aggroedCreature = creo;

		if (aggroedCreature != targetObject) {
			//System::out << "\thandleAttackCommand : new target\n";

			updateTarget(aggroedCreature);
		}
		setCombatState();
		if (isQueued())
			creatureManager->dequeueActivity(this);
		creatureManager->queueActivity(this, 10);
	}
}

void CreaturePetImplementation::handleFollowCommand(Player* target) {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::handleFollowCommand() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	setCommmandState(STATEFOLLOW);

	if (aggroedCreature != NULL)
		deaggro();
	aggroedCreature = NULL;
	patrolMode = false;
	followTarget = target;
}

void CreaturePetImplementation::handleStayCommand() {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::handleStayCommand() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	nextMovementPosition = NULL;
	setCommmandState(STATESTAY);
}

void CreaturePetImplementation::handleGuardCommand() {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::handleGuardCommand() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	setCommmandState(STATEGUARD);
}

void CreaturePetImplementation::handleStoreCommand() {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::handleStoreCommand() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	store(false);
}

void CreaturePetImplementation::handleTransferCommand() {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::handleTransferCommand() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	if (getLinkedCreature() == NULL)
		return;

	SceneObject* scno = getLinkedCreature()->getTarget();
	if (scno == NULL)
		return;

	Player* newOwner = NULL;
	if (scno->isPlayer())
		newOwner = (Player*) scno;

	if (newOwner == NULL) {
		return;
	}

	if (!newOwner->isInRange(getLinkedCreature(),10.0f)) {
		getLinkedCreature()->sendSystemMessage("That person is too far away. Transfer failed.");
		return;
	}

	if (isAggressive() && newOwner->getSkillMod("tame_level") < 12) {
		getLinkedCreature()->sendSystemMessage("pet/pet_menu","bad_type");

		return;
	}

	if (!newOwner->canStoreMorePets()) {
		getLinkedCreature()->sendSystemMessage("pet/pet_menu","targ_too_many_stored");
		return;
	}
	getLinkedCreature()->sendSystemMessage("pet/pet_menu","pet_transfer_succeed");

	store(false);

	ItemManager* itemManager = getLinkedCreature()->getZone()->getZoneServer()->getItemManager();

	if (itemManager == NULL) {
		System::out << "Error: CreaturePetImplementation::handleTransferCommand()\n";
		return;
	}
	uint32 datapadCRC = getDatapadItem()->getObjectCRC();
	getDatapadItem()->sendDestroyTo(getLinkedCreature());
	getLinkedCreature()->removeDatapadItem(getDatapadItem()->getObjectID());
	itemManager->deleteDatapadItem(getLinkedCreature(), getDatapadItem(), true);

	setDatapadItem(NULL);

	creatureLinkID = newOwner->getObjectID();
	setLinkedCreature(newOwner);

	createDataPad(datapadCRC);
}

void CreaturePetImplementation::handleTrickCommand(String anim,int mod,int cost) {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::handleTrickCommand() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	if (getLinkedCreature() == NULL)
		return;

	if (isInCombat() || getLinkedCreature()->isInCombat()) {
		getLinkedCreature()->sendSystemMessage("pet/pet_menu","sys_cant_trick");
		return;
	}

	if (!consumeOwnerHam(0,cost,0)) {
		getLinkedCreature()->sendSystemMessage("pet/pet_menu","cant_trick");
		return;
	}
	healPetMind(mod);
	doAnimation(anim);
}

void CreaturePetImplementation::healPetMind(int mod) {
	int woundPower = 0;
	if (getMindWounds() > 0) {
		woundPower = getMindMax() / mod;
		healWound(_this, CreatureAttribute::MIND, woundPower);
	}
	if (getWillpowerWounds() > 0) {
		woundPower = getWillpowerMax() / mod;
		healWound(_this, CreatureAttribute::WILLPOWER, woundPower);
	}
	if (getFocusWounds() > 0) {
		woundPower = getFocusMax() / mod;
		healWound(_this, CreatureAttribute::FOCUS, woundPower);
	}

	changeShockWounds(-100);
}

void CreaturePetImplementation::handleFormationCommand(uint8 form) {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::handleTrickCommand() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	if (getLinkedCreature() == NULL)
		return;

	if (formation == form) {
		formation = FORMATIONNONE;
		return;
	}

	if (formation < 3)
		formation = form;
}

bool CreaturePetImplementation::consumeOwnerHam(int h,int a, int m) {
	if (!getLinkedCreature()->changeHAMBars(h,a,m)) {
		return false;
	}

	return true;
}

void CreaturePetImplementation::handleEnrageCommand() {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::handleEnrageCommand() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}

	if (getWeapon() == NULL) {
		return;
	}
	setBerserkDamage((int) (getWeapon()->getMinDamage() / 4.0f));
	setBerserkedState(30*1000);
}
void CreaturePetImplementation::handleEmboldenCommand() {
	if (debug) {
			StringBuffer ss;
			ss << "CreaturePetImplementation::handleEmboldenCommand() " << getLinkedCreature()->getCharacterName().toString();
			info(ss.toString());
		}

		if (hasBuff(0x58F5818C))
			return;

		int healthBoost = getHealthMax() / 10;
		int actionBoost = getActionMax() / 10;
		int mindBoost = getMindMax() / 10;

		Buff* buff = new Buff(0x58F5818C, 0, 60);
		buff->setHealthBuff(healthBoost);
		buff->setActionBuff(actionBoost);
		buff->setMindBuff(mindBoost);

		BuffObject* bo = new BuffObject(buff);
		applyBuff(bo);

}
void CreaturePetImplementation::handleSpecialAttackCommand(Player* player, int att) {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::handleSpecialCommand() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}
	handleAttackCommand(player);

	nextAttack = att;
}

void CreaturePetImplementation::handleGroupCommand(Player* player) {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::handleGroupCommand() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}

	if (getGroupID() != 0)
		return;

	GroupManager* groupManager = server->getGroupManager();
	if (groupManager == NULL)
		return;

	GroupObject* group = player->getGroupObject();

	if (group != NULL && group->getLeader() != player) {
		player->sendSystemMessage("group", "must_be_leader");
		return;
	}

	try {
		unlock();
		groupManager->invitePetToGroup(getLinkedCreature(),_this);
		lock();
	} catch (...) {
		error("CreaturePetImplementation::handleGroupCommand()");
		lock();
	}

}

void CreaturePetImplementation::handleFriendCommand() {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::handleFriendCommand() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}

	SceneObject* scno = getLinkedCreature()->getTarget();

	if (scno == NULL)
		return;

	if (!scno->isPlayer())
		return;

	Player* newFriend = (Player*) scno;

	if (newFriend == getLinkedCreature())
		return;

	if (isFriend(newFriend)) {
		befriendList->drop(newFriend);
		newFriend->unregisterPet(_this);
		if (followTarget == newFriend)
			followTarget == getLinkedCreature();
		return;
	} else {
		befriendList->add(newFriend);
		newFriend->registerPet(_this);
	}
}
void CreaturePetImplementation::handleAddPatrolPointCommand(Player* player) {
	addPatrolPoint(player->getPositionX(),player->getPositionY(),false);
}

void CreaturePetImplementation::handleActivatePatrolCommand() {
	if (patrolPoints.isEmpty()) {
		handleFollowCommand(followTarget);
		return;
	}

	if (isInPatrolState()) {
		handleFollowCommand(followTarget);
		return;
	}

	setCommmandState(STATEPATROL);
	startPatrol(false);
}

void CreaturePetImplementation::handleClearPatrolPointsCommand() {
	if (isInPatrolState()) {
		handleFollowCommand(followTarget);
	}
	clearPatrolPoints(false);
}

void CreaturePetImplementation::trainMount() {
	if (debug) {
		StringBuffer ss;
		ss << "CreaturePetImplementation::trainMount() " << getLinkedCreature()->getCharacterName().toString();
		info(ss.toString());
	}

	CreatureManager* creatureManager = zone->getCreatureManager();

	if (creatureManager == NULL) {
		return;
	}

	creatureManager->convertPetToMount(_this,false);
}

Coordinate* CreaturePetImplementation::calculateRelativePosition() {
	if (formation == FORMATIONNONE) {
		if (followTarget->numberOfPetsCalled() == 2) {
			if (positionNumber == 1)
				return followTarget->getCoordinate(getLinkedCreature() , 3.0f, 155.0f);
			if (positionNumber == 0)
				return followTarget->getCoordinate(getLinkedCreature() , 3.0f, -155.0f);
		} else {
			switch (positionNumber % 3) {
			case 0:
				return followTarget->getCoordinate(getLinkedCreature() , (1 + (positionNumber / 3)) * 3.0f, 180.0f);
			case 1:
				return followTarget->getCoordinate(getLinkedCreature() , (1 + (positionNumber / 3)) * 3.0f, 135.0f);
			case 2:
				return followTarget->getCoordinate(getLinkedCreature() , (1 + (positionNumber / 3)) * 3.0f, -135.0f);
			}
		}
	}
	if (formation == FORMATIONCOLUM) {
		return followTarget->getCoordinate(getLinkedCreature() , (1 + positionNumber) * 3.0f, -180.0f);
	}
	if (formation == FORMATIONWEDGE) {
		if ((positionCounter % 2) == 0) {
			return followTarget->getCoordinate(getLinkedCreature() , (1 + (positionNumber / 2)) * 3.0f, 160.0f);
		} else {
			return followTarget->getCoordinate(getLinkedCreature() , (1 + (positionNumber / 2)) * 3.0f, -160.0f);
		}
	}
	return getCoordinate(getLinkedCreature() , 3.0f, 180.0f);
}

void CreaturePetImplementation::updateNextMovementPosition(Coordinate* nextPostition) {
	setNextMovementPosition(nextPostition->getPositionX(), nextPostition->getPositionY(),false);
}
