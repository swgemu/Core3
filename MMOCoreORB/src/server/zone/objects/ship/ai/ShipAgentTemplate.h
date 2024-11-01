/*
 * ShipAgentTemplate.h
 *
 *  Created on: 2024/11/01
 *  Author: Hakry
 */

#ifndef ShipAgentTemplate_H_
#define ShipAgentTemplate_H_

#include "engine/engine.h"
#include "templates/params/ship/ShipFlag.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {

class ShipAgentTemplate : public Object {
protected:
	String templateName;

	String shipTemplate;
	String pilotTemplate;
	String shipType;

	int experience;

	float lootChance;
	int lootRolls;
	String lootTable;

	int minCredits;
	int maxCredits;

	int aggressive;

	String spaceFaction;
	Vector<String> alliedFactions;
	Vector<String> enemyFactions;

	int imperialFactionReward;
	int rebelFactionReward;

	int color1;
	int color2;
	String texture;

	String questLoot;
	String interiorChassis;
	int formationLocation;
	String appearance;

	String tauntType;
	float tauntAttackChance;
	float tauntDefendChance;
	float tauntDieChance;
	float tauntAggressiveness;

public:
	ShipAgentTemplate();

	virtual ~ShipAgentTemplate();

	void readObject(LuaObject* templateData);

	void setTemplateName(const String& t) {
		templateName = t;
	}

	// Accessors
	String getTemplateName() {
		return templateName;
	}

	String getShipTemplate() {
		return shipTemplate;
	}

	String getPilotTemplate() {
		return pilotTemplate;
	}

	String getShipType() {
		return shipType;
	}

	int getExperience() {
		return experience;
	}

	float getLootChance() {
		return lootChance;
	}

	int getLootRolls() {
		return lootRolls;
	}

	String getLootTable() {
		return lootTable;
	}

	int getMinCredits() {
		return minCredits;
	}

	int getMaxCredits() {
		return maxCredits;
	}

	int getAggressive() {
		return aggressive;
	}

	String getSpaceFaction() {
		return spaceFaction;
	}

	int getTotalAlliedFactions() {
		return alliedFactions.size();
	}

	String getAlliedFaction(int index) {
		return alliedFactions.get(index);
	}

	int getTotalEnemyFactions() {
		return enemyFactions.size();
	}

	String getEnemyFaction(int index) {
		return enemyFactions.get(index);
	}

	int getImperialFactionReward() {
		return imperialFactionReward;
	}

	int getRebelFactionReward() {
		return rebelFactionReward;
	}

	int getColor1() {
		return color1;
	}

	int getColor2() {
		return color2;
	}

	String getTexture() {
		return texture;
	}

	String getQuestLoot() {
		return questLoot;
	}

	String getInteriorChassis() {
		return interiorChassis;
	}

	int getFormationLocation() {
		return formationLocation;
	}

	String getAppearance() {
		return appearance;
	}

	String getTauntType() {
		return tauntType;
	}

	float getTauntAttackChance() {
		return tauntAttackChance;
	}

	float getTauntDefendChance() {
		return tauntDefendChance;
	}

	float getTauntDieChance() {
		return tauntDieChance;
	}

	float getTauntAggressiveness() {
		return tauntAggressiveness;
	}
};

} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::ship::ai;

#endif /* ShipAgentTemplate_H_ */
