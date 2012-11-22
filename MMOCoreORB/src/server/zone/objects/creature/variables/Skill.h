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

	void parseLuaObject(LuaObject* templateData) {

		if (!templateData->isValidTable())
			return;

		skillName = templateData->getStringField("skillName");
		parentName = templateData->getStringField("parentName");
		graphType = templateData->getIntField("graphType");
		godOnly = templateData->getIntField("godOnly");
		title = templateData->getIntField("title");
		profession = templateData->getIntField("profession");
		hidden = templateData->getIntField("hidden");
		moneyRequired = templateData->getIntField("moneyRequired");
		pointsRequired = templateData->getIntField("pointsRequired");
		skillsRequiredCount = templateData->getIntField("skillsRequiredCount");

		LuaObject skillsRequiredTable = templateData->getObjectField("skillsRequired");
		for(int i = 1; i <= skillsRequiredTable.getTableSize(); i++) {
			skillsRequired.add(skillsRequiredTable.getStringAt(i));
		}
		skillsRequiredTable.pop();

		LuaObject preclusionSkillsTable = templateData->getObjectField("preclusionSkills");
		for(int i = 1; i <= preclusionSkillsTable.getTableSize(); i++) {
			preclusionSkills.add(preclusionSkillsTable.getStringAt(i));
		}
		preclusionSkillsTable.pop();

		xpType = templateData->getStringField("xpType");
		xpCost = templateData->getIntField("xpCost");
		xpCap = templateData->getIntField("xpCap");

		LuaObject missionsRequiredTable = templateData->getObjectField("missionsRequired");
		for(int i = 1; i <= missionsRequiredTable.getTableSize(); i++) {
			missionsRequired.add(missionsRequiredTable.getStringAt(i));
		}
		missionsRequiredTable.pop();

		apprenticeshipsRequired = templateData->getIntField("apprenticeshipsRequired");

		LuaObject statsRequiredTable = templateData->getObjectField("statsRequired");
		for(int i = 1; i <= statsRequiredTable.getTableSize(); i++) {
			statsRequired.add(statsRequiredTable.getStringAt(i));
		}
		statsRequiredTable.pop();

		LuaObject speciesRequiredTable = templateData->getObjectField("speciesRequired");
		for(int i = 1; i <= statsRequiredTable.getTableSize(); i++) {
			speciesRequired.add(statsRequiredTable.getStringAt(i));
		}
		speciesRequiredTable.pop();

		jediStateRequired = templateData->getIntField("jediStateRequired");

		LuaObject skillAbilityTable = templateData->getObjectField("skillAbility");
		for(int i = 1; i <= skillAbilityTable.getTableSize(); i++) {
			skillAbility.add(skillAbilityTable.getStringAt(i));
		}
		skillAbilityTable.pop();

		LuaObject commandsTable = templateData->getObjectField("commands");
		for(int i = 1; i <= commandsTable.getTableSize(); i++) {
			commands.add(commandsTable.getStringAt(i));
		}
		commandsTable.pop();

		LuaObject skillModifiersTable = templateData->getObjectField("skillModifiers");
		for(int i = 1; i <= skillModifiersTable.getTableSize(); i++) {
			LuaObject skillMod = skillModifiersTable.getObjectAt(i);
			String skillModName = skillMod.getStringAt(1);
			int skillModValue = skillMod.getIntAt(2);
			skillModifiers.put(skillModName, skillModValue);
		}
		skillModifiersTable.pop();

		LuaObject schematicsGrantedTable = templateData->getObjectField("schematicsGranted");
		for(int i = 1; i <= schematicsGrantedTable.getTableSize(); i++) {
			schematicsGranted.add(schematicsGrantedTable.getStringAt(i));
		}
		schematicsGrantedTable.pop();

		LuaObject schematicsRevokedTable = templateData->getObjectField("schematicsRevoked");
		for(int i = 1; i <= schematicsRevokedTable.getTableSize(); i++) {
			schematicsRevoked.add(schematicsRevokedTable.getStringAt(i));
		}
		schematicsRevokedTable.pop();

		searchable = templateData->getIntField("searchable");

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

	/**
	 * Returns the XP cost for the skill.
	 * @return XP cost for the skill.
	 */
	inline int getXpCost() {
		return xpCost;
	}

	/**
	 * Returns the credits required for training the skill at a trainer.
	 * @return the credits required for training the skill at a trainer.
	 */
	inline int getMoneyRequired() {
		return moneyRequired;
	}

	/**
	 * Returns the number of skill points required for the skill.
	 * @return the number of skill points required for the skill.
	 */
	inline int getSkillPointsRequired() {
		return pointsRequired;
	}

	/**
	 * Returns the species required for the skill.
	 * @return the species required for the skill.
	 */
	inline Vector<String>* getSpeciesRequired() {
		return &speciesRequired;
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
