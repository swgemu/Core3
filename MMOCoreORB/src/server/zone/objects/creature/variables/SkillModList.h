/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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

	SkillModList(const SkillModList& l) : Object(), DeltaVectorMap<String, SkillModEntry>(l) {
		mods.setAllowOverwriteInsertPlan();

		mods = l.mods;

		addSerializableVariables();
	}

/*	SkillModList& operator=(const SkillModList& l) {
		if (this == &l)
			return *this;

		DeltaVectorMap<String, int>::operator =(m);

		mods.setAllowOverwriteInsertPlan();

		mods = l.mods;

		return *this;
	}*/

	inline void addSerializableVariables() {
		addSerializableVariable("mods", &mods);
	}

	bool add(const uint32 modType, const String& skillMod, int value) {
		if (!mods.contains(modType)) {
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

		for (int i = 0; i < mods.size(); ++i) {
			uint32 modType = mods.elementAt(i).getKey();
			SkillModGroup* group = &mods.elementAt(i).getValue();

			if(group->contains(skillMod)) {

				int maxSkill = SkillModManager::instance()->getMaxSkill(modType);
				int minSkill = SkillModManager::instance()->getMinSkill(modType);

				if(modType & SkillModManager::BONUSMOD) {
					int newSkillBonus = newEntry.getSkillBonus() + group->get(skillMod);

					if(maxSkill != 0 && minSkill != 0) {
						if(newSkillBonus >= 0)
							newSkillBonus = Math::min(newSkillBonus, maxSkill);
						else
							newSkillBonus = Math::max(newSkillBonus, minSkill);
					}
					newEntry.setSkillBonus(newSkillBonus);

				} else if(modType & SkillModManager::PERMANENTMOD) {
					int newSkillMod = newEntry.getSkillMod() + group->get(skillMod);

					if(maxSkill != 0 && minSkill != 0) {
						if(newSkillMod >= 0)
							newSkillMod = Math::min(newSkillMod, maxSkill);
						else
							newSkillMod = Math::max(newSkillMod, minSkill);
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
						newSkillBonus = Math::min(newSkillBonus, maxSkill);
					else
						newSkillBonus = Math::max(newSkillBonus, minSkill);
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
						skillModValue = Math::min(skillModValue, maxSkill);
					else
						skillModValue = Math::max(skillModValue, minSkill);
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
