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

#ifndef SKILLBOX_H_
#define SKILLBOX_H_

#include "../../../objects/creature/skills/Skill.h"
#include "../../../objects/creature/skillmods/SkillModList.h"

#include "Certification.h"

#include "Profession.h"

class SkillBox {
	string name;
	int skillBoxId;

	SkillBox* parent;
	Profession* profession;

	bool skillGodOnly;
	bool skillIsTitle;
	bool skillIsHidden;

	int skillMoneyRequired;
	int skillPointsRequired;
	int skillRequirementsCount;

	Vector<string> skillRequirements;
	SortedVector<SkillBox*> requiredSkills;
	Vector<string> skillPreclusions;
	string skillXpType;

	int skillXpCost;
	int skillXpCap;

	Vector<string> skillSpeciesRequired;
	string skillJediStateRequired;

	Vector<string> skillSchematicsGranted;

	bool skillIsSearchable;

	Vector<Skill*> skillCommands;
	Vector<Certification*> skillCertifications;
	SkillModList skillMods;


public:
	SkillBox(const string& s, int id, Profession* prof) {
		name = s;
		skillBoxId = id;
		profession = prof;

		parent = NULL;

		skillGodOnly = false;
		skillIsTitle = false;
		skillIsHidden = false;

		skillMoneyRequired = 0;
		skillPointsRequired = 0;

		skillXpCost = 0;
		skillXpCap = 0;

		skillIsSearchable = false;
	}

	int compareTo(SkillBox* obj) {
		if (skillBoxId < obj->skillBoxId)
			return 1;
		else if (skillBoxId > obj->skillBoxId)
			return -1;
		else
			return 0;
	}

	void setSkillGodOnly(bool god) {
		skillGodOnly = god;
	}

	void setSkillIsTitle(bool title) {
		skillIsTitle = title;
	}

	void setSkillIsHidden(bool isHidden) {
		skillIsHidden = isHidden;
	}

	void setSkillMoneyRequired(int money) {
		skillMoneyRequired = money;
	}

	void setSkillPointsRequired(int points) {
		skillPointsRequired = points;
	}

	void addSkillCommand(Skill* skill) {
		skillCommands.add(skill);
	}

	void addRequirementSkill(string skill) {
		skillRequirements.add(skill);
	}

	void addPreclusionSkill(string skill) {
		skillPreclusions.add(skill);
	}

	void addRequiredSpecies(string race) {
		skillSpeciesRequired.add(race);
	}

	void addSkillMod(string mod, int val) {
		skillMods.put(mod, val);
	}

	void addGrantedSchematic(string schematic) {
		skillSchematicsGranted.add(schematic);
	}

	inline Skill* getSkillCommand(int index) {
		return skillCommands.get(index);
	}

	inline int getGrantedSchematicListSize() {
		return skillSchematicsGranted.size();
	}

	inline void getGrantedSchematic(string& schematic, int index) {
		schematic = skillSchematicsGranted.get(index);
	}

	inline int getSkillMod(string mod) {
		return skillMods.get(mod);
	}

	inline void getRequiredSpeces(string& race, int index) {
		race = skillSpeciesRequired.get(index);
	}

	void setSkillXpType(const string& skill) {
		skillXpType = skill;
	}

	void setSkillXpCost(int xp) {
		skillXpCost = xp;
	}

	void setSkillXpCap(int cap) {
		skillXpCap = cap;
	}

	void setSkillJediStateRequired(const string& state) {
		skillJediStateRequired = state;
	}

	inline void getRequiredSkill(string& skill, int index) {
		skill = skillRequirements.get(index);
	}

	void setSkillIsSearchable(bool searchable) {
		skillIsSearchable = searchable;
	}

	void setParent(SkillBox* pr) {
		parent = pr;
	}

	inline string& getName() {
		return name;
	}

	inline SkillBox* getParent() {
		return parent;
	}

	inline int getSkillBoxId() {
		return skillBoxId;
	}

	inline Profession* getProfession() {
		return profession;
	}

	inline bool isMasterBox() {
		return profession->getMasterBox() == this;
	}

	inline bool isNoviceBox() {
		return profession->getNoviceBox() == this;
	}

	inline int getSkillPointsRequired() {
		return skillPointsRequired;
	}

	inline string& getSkillXpType() {
		return skillXpType;
	}

	inline int getSkillXpCost() {
		return skillXpCost;
	}

	int getRequiredSkillsSize() {
		return requiredSkills.size();
	}

	SkillBox* getRequiredSkill(int idx) {
		return requiredSkills.get(idx);
	}

	friend class SkillManager;
	friend class ProfessionManager;
	friend class CreatureObjectMessage1;

};

#endif /*SKILLBOXIMPLEMENTATION_H_*/
