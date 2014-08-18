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

#ifndef SKILLMODLIST_H_
#define SKILLMODLIST_H_

#include "engine/engine.h"
#include "SkillModEntry.h"
#include "server/zone/objects/scene/variables/DeltaVectorMap.h"
#include "server/zone/managers/skill/SkillModManager.h"

class SkillModGroup : public VectorMap<String, int> {
public:
	SkillModGroup() {
		setAllowOverwriteInsertPlan();
		setNullValue(0);
	}

	SkillModGroup(const SkillModGroup& m) : VectorMap<String, int>(m) {
		setAllowOverwriteInsertPlan();
		setNullValue(0);
	}

	SkillModGroup& operator=(const SkillModGroup& m) {
		if (this == &m)
			return *this;

		VectorMap<String, int>::operator =(m);

		return *this;
	}
};

class SkillModList : public DeltaVectorMap<String, SkillModEntry> {
protected:

	VectorMap<uint32, SkillModGroup> mods;

public:

	SkillModList() {
		mods.setAllowOverwriteInsertPlan();
		addSerializableVariables();
	}

	inline void addSerializableVariables() {
		addSerializableVariable("mods", &mods);
	}

	bool add(const uint32 modType, const String& skillMod, int value) {

		if(!mods.contains(modType)) {
			SkillModGroup newgroup;
			newgroup.put(skillMod, value);
			mods.put(modType, newgroup);
		} else {
			SkillModGroup* group = &mods.get(modType);
			int oldValue = group->get(skillMod);
			int newValue = oldValue + value;
			if(newValue != 0)
				group->put(skillMod, newValue);
			else
				group->drop(skillMod);
		}

		return true;
	}

	SkillModEntry getVisibleSkillMod(const String& skillMod) {

		SkillModEntry newEntry;

		for(int i = 0; i < mods.size(); ++i) {

			uint32 modType = mods.elementAt(i).getKey();
			SkillModGroup* group = &mods.elementAt(i).getValue();

			if(group->contains(skillMod)) {

				int maxSkill = SkillModManager::instance()->getMaxSkill(modType);
				int minSkill = SkillModManager::instance()->getMinSkill(modType);

				if(modType & SkillModManager::BONUSMOD) {
					int newSkillBonus = newEntry.getSkillBonus() + group->get(skillMod);

					if(maxSkill != 0 && minSkill != 0) {
						if(newSkillBonus >= 0)
							newSkillBonus = MIN(newSkillBonus, maxSkill);
						else
							newSkillBonus = MAX(newSkillBonus, minSkill);
					}
					newEntry.setSkillBonus(newSkillBonus);

				} else if(modType & SkillModManager::PERMANENTMOD) {
					int newSkillMod = newEntry.getSkillMod() + group->get(skillMod);

					if(maxSkill != 0 && minSkill != 0) {
						if(newSkillMod >= 0)
							newSkillMod = MIN(newSkillMod, maxSkill);
						else
							newSkillMod = MAX(newSkillMod, minSkill);
					}

					newEntry.setSkillMod(newSkillMod);
				}

			}
		}
		return newEntry;
	}

	SkillModGroup* getSkillModGroup(const uint32 type) {
		if(!mods.contains(type)) {
			SkillModGroup group;
			mods.put(type, group);
		}

		return &mods.get(type);
	}

	int getSkillMod(const String& skillMod) {

		int skill = 0;

		for (int i = 0; i < mods.size(); ++i) {

			uint32 modType = mods.elementAt(i).getKey();
			SkillModGroup* group = &mods.elementAt(i).getValue();

			if (group->contains(skillMod)) {

				int maxSkill = SkillModManager::instance()->getMaxSkill(modType);
				int minSkill = SkillModManager::instance()->getMinSkill(modType);

				int newSkillBonus = group->get(skillMod);

				if(maxSkill != 0 && minSkill != 0) {
					if (newSkillBonus >= 0)
						newSkillBonus = MIN(newSkillBonus, maxSkill);
					else
						newSkillBonus = MAX(newSkillBonus, minSkill);
				}

				skill += newSkillBonus;
			}
		}

		return skill;
	}

	int getSkillModOfType(const String& skillMod, const uint32 modType) {
		SkillModGroup* group = getSkillModGroup(modType);

		if (group->contains(skillMod)) {
			return group->get(skillMod);
		}

		return 0;
	}

	String getPrintableSkillModList() {


		VectorMap<String, int> skills;
		skills.setAllowOverwriteInsertPlan();

		for (int i = 0; i < mods.size(); ++i) {

			uint32 modType = mods.elementAt(i).getKey();
			SkillModGroup* group = &mods.elementAt(i).getValue();

			for(int j = 0; j < group->size(); ++j) {

				String skillMod = group->elementAt(j).getKey();
				int skillModValue = group->get(skillMod);

				int maxSkill = SkillModManager::instance()->getMaxSkill(modType);
				int minSkill = SkillModManager::instance()->getMinSkill(modType);

				if(maxSkill != 0 && minSkill != 0) {
					if (skillModValue >= 0)
						skillModValue = MIN(skillModValue, maxSkill);
					else
						skillModValue = MAX(skillModValue, minSkill);
				}

				if(skills.contains(skillMod))
					skillModValue += skills.get(skillMod);

				skills.put(skillMod, skillModValue);
			}
		}

		StringBuffer skill;
		for(int i = 0; i < skills.size(); ++i) {
			skill << skills.elementAt(i).getKey() << " : " << skills.get(i) << "\n";
		}

		return skill.toString();
	}
};

#endif /*SKILLMODLIST_H_*/
