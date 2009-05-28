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

#ifndef CREATUREOBJECTIMPLEMENTATION_H_
#define CREATUREOBJECTIMPLEMENTATION_H_

#include "CreatureObject.h"
#include "modifiers/ModifierEffect.h"
#include "modifiers/ModifierList.h"
#include "../SkillModList.h"
#include "../instrument/InstrumentObject.h"
#include "../weapon/WeaponObject.h"
#include "../../universe/group/GroupObject.h"
#include "../../universe/guild/GuildObject.h"

class CreatureObjectImplementation : public CreatureObjectServant {
protected:
	ManagedReference<InstrumentObject> instrument;
	ManagedReference<TangibleObject> target; //For targetID?
	ManagedReference<WeaponObject> weapon;
	ManagedReference<GroupObject> group;
	ManagedReference<GuildObject> guild;
	ManagedReference<CreatureObject> linkedCreature; //TODO: Is this only used for Mount?

	SkillModList skillMods;
	ModifierList modifiers;

	String performanceAnimation;

	float height;
	float speed;
	float turnRadius;
	float terrainNegotiation;
	float acceleration;
	float deceleration;

	uint64 statesBitmask;
	uint64 listeningToID;
	uint64 groupInviteCounter;
	uint64 groupInviterID;

	uint32 level;

	uint32 creditsBank;
	uint32 creditsCash;

	uint32 factionRank;

	uint32 updateCounterHAMBase;
	uint32 updateCounterWounds;
	uint32 updateCounterEncumbrance;
	uint32 updateCounterPerformance;

	int32 attributesBase[9];
	int32 attributes[9];
	int32 attributesMax[9];
	int32 wounds[9];
	int32 shockWounds;

	int32 healthEncumbrance;
	int32 actionEncumbrance;
	int32 mindEncumbrance;

	uint8 moodID;
	uint8 posture;

public:
	static const float DEFAULT_SPEED = 5.376f;
	static const float DEFAULT_ACCEL = 1.549f;

public:
	CreatureObjectImplementation();
	~CreatureObjectImplementation();

	//Saving and loading

	//Modifiers
	virtual void addModifierEffect(ModifierEffect* modeffect, bool activate = true);
	virtual void removeModifierEffect(ModifierEffect* modeffect);
	virtual ModifierEffect* getModifierEffect(const String& modeffectname);
	virtual bool hasModifierEffect(const String& modeffectname);
	virtual float getModifier(const String& modname);
	virtual bool hasModifier(const String& modname);

	//General Commands
	virtual void groupInvite(Player* player);
	virtual void groupJoin(Player* player);
	virtual void groupLeave(Player* player);
	virtual void groupKick(Player* player);
	virtual void groupDisband(Player* player);
	virtual void groupDecline(Player* player);
	virtual void follow(TangibleObject* target);
	virtual void stopFollowing(TangibleObject* target);
	virtual void imageDesign(CreatureObject* target);
	virtual void diagnose(CreatureObject* target);
	virtual void tendDamage(CreatureObject* target);
	virtual void tendWound(CreatureObject* target);
	virtual void healWound(CreatureObject* target, uint8 woundtype);
	virtual void healDamage(CreatureObject* target);
	virtual void healState(CreatureObject* target, uint8 statetype);
	virtual void healEnhance(CreatureObject* target, uint8 enhancetype);
	virtual void healFirstAid(CreatureObject* target);
	virtual void healCurePoison(CreatureObject* target);
	virtual void healCureDisease(CreatureObject* target);
	virtual void healApplyPoison(CreatureObject* target);
	virtual void healApplyDisease(CreatureObject* target);
	virtual void performanceListen(CreatureObject* target);
	virtual void performanceWatch(CreatureObject* target);
	virtual void performanceStopListening(CreatureObject* target);
	virtual void performanceStopWatching(CreatureObject* target);

	//Setters

	//Getters
};

#endif /*CREATUREOBJECTIMPLEMENTATION_H_*/
