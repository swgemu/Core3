#ifndef SKILL_H_
#define SKILL_H_

#include "engine/engine.h"
#include "server/zone/templates/datatables/DataTableRow.h"

namespace server {
namespace zone {
namespace managers {
namespace skill {
	class SkillManager;
}
}
}
}

using namespace server::zone::managers::skill;

class Skill : public Object {
protected:
	Reference<Skill*> parentNode;
	Vector<Reference<Skill*> > childNodes;

	String skillName;
	String parentName;
	int graphType;

	bool godOnly;
	bool title;
	bool profession;
	bool hidden;
	bool searchable;

	int moneyRequired;
	int pointsRequired;
	int skillsRequiredCount;

	Vector<String> skillsRequired;
	Vector<String> preclusionSkills;

	String xpType;

	int xpCost;
	int xpCap;

	Vector<String> missionsRequired;

	int apprenticeshipsRequired;

	Vector<String> statsRequired;
	Vector<String> speciesRequired;

	int jediStateRequired;

	Vector<String> skillAbility;
	Vector<String> commands;
	VectorMap<String, int> skillModifiers;
	Vector<String> schematicsGranted;
	Vector<String> schematicsRevoked;

public:
	Skill() {
		skillName = "root";
	}

	~Skill() {
	}

	int compareTo(const Skill& s) {
		return skillName.compareTo(s.skillName);
	}

	int compareTo(Skill* s) {
		return skillName.compareTo(s->skillName);
	}

	void parseDataTableRow(DataTableRow* row) {
		row->getValue(0, skillName);
		row->getValue(1, parentName);
		row->getValue(2, graphType);
		row->getValue(3, godOnly);
		row->getValue(4, title);
		row->getValue(5, profession);
		row->getValue(6, hidden);
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
		row->getValue(17, statsRequired);
		row->getValue(18, speciesRequired);
		row->getValue(19, jediStateRequired);
		row->getValue(20, skillAbility);
		row->getValue(21, commands);

		String skillmodstring;
		row->getValue(22, skillmodstring);
		parseSkillMods(skillmodstring);

		row->getValue(23, schematicsGranted);
		row->getValue(24, schematicsRevoked);
		row->getValue(25, searchable);
	}

	inline String& getSkillName() {
		return skillName;
	}

	inline bool isGodOnly() {
		return godOnly;
	}

	inline bool isTitle() {
		return title;
	}

	inline bool isSkill() {
		return profession;
	}

	inline bool isHidden() {
		return hidden;
	}

	inline bool isSearchable() {
		return searchable;
	}

	inline Skill* getParent() {
		return parentNode;
	}

	inline int getTotalChildren() {
		return childNodes.size();
	}

	inline Skill* getChildNode(int idx) {
		return childNodes.get(idx);
	}

	inline bool containsChildNode(Skill* skill) {
		return childNodes.contains(skill);
	}

	inline String& getParentName() {
		return parentName;
	}

	inline void addChild(Skill* skill) {
		skill->setParentNode(this);
		childNodes.add(skill);
	}

	inline Vector<String>* getAbilities() {
		return &commands;
	}

	inline Vector<String>* getSchematicsGranted() {
		return &schematicsGranted;
	}

	inline VectorMap<String, int>* getSkillModifiers() {
		return &skillModifiers;
	}

	inline Vector<String>* getSkillsRequired() {
		return &skillsRequired;
	}

	inline bool isRequiredSkillOf(Skill* skill) {
		return skillsRequired.contains(skill->getSkillName());
	}

	inline String getXpType() {
		return xpType;
	}

	inline int getXpCap() {
		return xpCap;
	}

private:
	inline void setParentNode(Skill* skill) {
		parentNode = skill;
	}

	void parseSkillMods(const String& modstring) {
		StringTokenizer tokenizer(modstring);
		tokenizer.setDelimeter(",");

		while (tokenizer.hasMoreTokens()) {
			String token;
			tokenizer.getStringToken(token);

			int pos = token.indexOf("=");

			if (pos == -1)
				continue;

			String k = token.subString(0, pos);
			String v = token.subString(pos + 1);

			skillModifiers.put(k, Integer::valueOf(v));
		}
	}

	friend class server::zone::managers::skill::SkillManager;
};

#endif /* SKILL_H_ */
