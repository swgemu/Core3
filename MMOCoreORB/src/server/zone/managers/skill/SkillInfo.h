/*
 * SkillInfo.h
 *
 *  Created on: Apr 25, 2011
 *      Author: crush
 */

#ifndef SKILLINFO_H_
#define SKILLINFO_H_

#include "templates/datatables/DataTableRow.h"

class SkillInfo : public Object {
	WeakReference<SkillInfo*> parentSkill;

	SortedVector<String> speciesRequired;
	SortedVector<String> skillsRequired;
	SortedVector<String> preclusionSkills;
	SortedVector<String> missionsRequired;

	SortedVector<String> commands;
	SortedVector<String> schematicsGranted;
	SortedVector<String> schematicsRevoked;

	VectorMap<String, int> skillMods;

	String xpType;
	String skillName;

	int skillsRequiredCount;
	int jediStateRequired;
	int apprenticeshipsRequired;
	int xpCost;
	int xpCap;
	int moneyRequired;
	int pointsRequired;
	int graphType;

	bool searchable;
	bool godOnly;
	bool isTitle;
	bool isProfession;
	bool isHidden;

public:
	SkillInfo() {
		skillsRequiredCount = 0;
		jediStateRequired = 0;
		apprenticeshipsRequired = 0;
		xpCost = 0;
		xpCap = 0;
		moneyRequired = 0;
		pointsRequired = 0;
		graphType = 0;

		searchable = false;
		godOnly = false;
		isTitle = false;
		isProfession = false;
		isHidden = false;
	}

	SkillInfo(const String& name, SkillInfo* parent) {
		skillName = name;
		parentSkill = parent;

		skillsRequiredCount = 0;
		jediStateRequired = 0;
		apprenticeshipsRequired = 0;
		xpCost = 0;
		xpCap = 0;
		moneyRequired = 0;
		pointsRequired = 0;
		graphType = 0;

		searchable = false;
		godOnly = false;
		isTitle = false;
		isProfession = false;
		isHidden = false;
	}

	SkillInfo(const SkillInfo& si) : Object() {
		skillsRequiredCount = si.skillsRequiredCount;
		jediStateRequired = si.jediStateRequired;
		apprenticeshipsRequired = si.apprenticeshipsRequired;
		xpCost = si.xpCost;
		xpCap = si.xpCap;
		moneyRequired = si.moneyRequired;
		pointsRequired = si.pointsRequired;
		graphType = si.graphType;

		searchable = si.searchable;
		godOnly = si.godOnly;
		isTitle = si.isTitle;
		isProfession = si.isProfession;
		isHidden = si.isHidden;
	}

	SkillInfo& operator= (const SkillInfo& si) {
		if (this == &si)
			return *this;

		return *this;
	}

	void parseFromDataTableRow(DataTableRow* row) {
		try {
			row->getValue(0, skillName);
			//row->getValue(1, parentSkill);
			row->getValue(2, graphType);
			row->getValue(3, godOnly);
			row->getValue(4, isTitle);
			row->getValue(5, isProfession);
			row->getValue(6, isHidden);
			row->getValue(7, moneyRequired);
			row->getValue(8, pointsRequired);
			row->getValue(9, skillsRequiredCount);
			row->getValue(10, skillsRequired);
			row->getValue(11, preclusionSkills);
			row->getValue(12, xpType);
			row->getValue(13, xpCost);
			row->getValue(14, xpCap);
			row->getValue(15, missionsRequired);
			row->getValue(16, apprenticeshipsRequired);
			//row->getValue(17, statsRequired);
			row->getValue(18, speciesRequired);
			row->getValue(19, jediStateRequired);
			//row->getValue(20, skillAbility);
			row->getValue(21, commands);

			SortedVector<String> skillModTokens;
			row->getValue(22, skillModTokens);

			for (int i = 0; i < skillModTokens.size(); ++i) {
				String token = skillModTokens.get(i);

				String k = token.subString(0, token.indexOf('='));
				int v = Integer::valueOf(token.subString(k.length() + 1));

				skillMods.put(k, v);
			}

			row->getValue(23, schematicsGranted);
			row->getValue(24, schematicsRevoked);
			row->getValue(25, searchable);
			//row->getValue(26, ender); //What is ender?

		} catch (Exception& e) {

		}
	}
};


#endif /* SKILLINFO_H_ */
