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

#ifndef SKILL_H_
#define SKILL_H_

#include "engine/engine.h"

#include "Animations.h"

#include "../../../ZoneProcessServerImplementation.h"
#include "../../../managers/combat/CombatManager.h"

class Skill {
protected:
	String skillName;
	uint32 nameCRC;
	int type;
	int category;

	uint32 animCRC;
	String effectName;

	float range;
	float speedRatio;

	ZoneProcessServerImplementation* server;

public:
	static const int OTHER = 0;
	static const int ATTACK = 1;
	static const int HEAL = 2;
	static const int ENHANCE = 3;
	static const int PASSIVE = 4;
	static const int MEDITATE = 5;
	static const int ENTERTAIN = 6;
	static const int DANCE = 7;
	static const int MUSIC = 8;
	static const int DIAGNOSE = 9;
	static const int REVIVE = 10;
	static const int CAMO = 11;
	static const int THROW = 12;
	static const int FORAGE = 13;

	static const int TARGET = 1;
	static const int SELF = 2;

public:
	Skill(const String& name, int tp, int cat, ZoneProcessServerImplementation* serv) {
		server = serv;

		nameCRC = name.hashCode();

		skillName = name;
		type = tp;
		category = cat;

		animCRC = 0;

		range = 0.0;
		speedRatio = 1.0;
	}

	virtual ~Skill() {
	}

	virtual int getRequiredWeaponType() {
		return -1;
	}

	virtual int getAreaRange() {
		return -1;
	}

	void setAnimation(const String& ename) {
		animCRC = ename.hashCode();
	}

	void setEffect(const String& ename) {
		effectName = ename;
	}

	inline void setRange(float r) {
		range = r;
	}

	inline void setSpeedRatio(float s) {
		speedRatio = s;
	}

	bool hasAnimation() {
		return animCRC != 0;
	}

	bool hasEffect() {
		return !effectName.isEmpty();
	}

	inline bool isAttackSkill() {
		return type == ATTACK || type == THROW;
	}

	inline bool isHealSkill() {
		return type == HEAL || type == DIAGNOSE || type == REVIVE;
	}

	inline bool isEnhanceSkill() {
		return type == ENHANCE;
	}

	inline bool isPassiveSkill() {
		return type == PASSIVE;
	}

	inline bool isMeditateSkill() {
		return type == MEDITATE;
	}

	inline bool isEntertainSkill() {
		return type == ENTERTAIN;
	}

	inline bool isDanceSkill() {
		return type == DANCE;
	}

	inline bool isMusicSkill() {
		return type == MUSIC;
	}

	inline bool isDiagnoseSkill() {
		return type == DIAGNOSE;
	}

	inline bool isReviveSkill() {
		return type == REVIVE;
	}

	inline uint32 getNameCRC() {
		return nameCRC;
	}

	inline uint32 getAnimCRC() {
		return animCRC;
	}

	inline uint32 getAnimCRC(CreatureObject* creature, const String& actionModifier) {
		return animCRC;
	}

	inline String& getEffectName() {
		return effectName;
	}

	inline float getRange() {
		return range;
	}

	inline float getSpeedRatio() {
		return speedRatio;
	}

	inline bool isSelfSkill() {
		return category == SELF;
	}

	inline bool isTargetSkill() {
		return category == TARGET;
	}

	inline String& getSkillName() {
		return skillName;
	}

	inline bool isCamoSkill(){
		return type == CAMO;
	}

	inline bool isThrowSkill(){
		return type == THROW;
	}

};

#endif /*SKILL_H_*/
