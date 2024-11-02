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
	int texture;

	String questLoot;
	String interiorChassis;
	int formationLocation;
	String appearance;

	String tauntType;
	float tauntAttackChance;
	float tauntDefendChance;
	float tauntDieChance;
	float tauntAggressiveness;

	unsigned int pvpBitmask;
	unsigned int shipBitmask;
	uint32 optionsBitmask;

	uint64 customShipAiMap;

	uint32 conversationTemplate;
	uint32 conversationMobile;
	uint32 conversationMessage; // Too Far Message

public:
	ShipAgentTemplate();

	virtual ~ShipAgentTemplate();

	void readObject(LuaObject* templateData);

	void setTemplateName(const String& t) {
		templateName = t;
	}

	// Accessors
	inline String getTemplateName() const {
		return templateName;
	}

	inline String getShipTemplate() const {
		return shipTemplate;
	}

	inline String getPilotTemplate() const {
		return pilotTemplate;
	}

	inline String getShipType() const {
		return shipType;
	}

	inline int getExperience() const {
		return experience;
	}

	inline float getLootChance() const {
		return lootChance;
	}

	inline int getLootRolls() const {
		return lootRolls;
	}

	inline String getLootTable() const {
		return lootTable;
	}

	inline int getMinCredits() const {
		return minCredits;
	}

	inline int getMaxCredits() const {
		return maxCredits;
	}

	inline int getAggressive() const {
		return aggressive;
	}

	inline String getSpaceFaction() const {
		return spaceFaction;
	}

	inline int getTotalAlliedFactions() const {
		return alliedFactions.size();
	}

	inline String getAlliedFaction(int index) const {
		return alliedFactions.get(index);
	}

	inline int getTotalEnemyFactions() const {
		return enemyFactions.size();
	}

	inline String getEnemyFaction(int index) const {
		return enemyFactions.get(index);
	}

	inline int getImperialFactionReward() const {
		return imperialFactionReward;
	}

	inline int getRebelFactionReward() const {
		return rebelFactionReward;
	}

	inline int getColor1() const {
		return color1;
	}

	inline int getColor2() const {
		return color2;
	}

	inline int getTexture() const {
		return texture;
	}

	inline String getQuestLoot() const {
		return questLoot;
	}

	inline String getInteriorChassis() const {
		return interiorChassis;
	}

	inline int getFormationLocation() const {
		return formationLocation;
	}

	inline String getAppearance() const {
		return appearance;
	}

	inline String getTauntType() const {
		return tauntType;
	}

	inline float getTauntAttackChance() const {
		return tauntAttackChance;
	}

	inline float getTauntDefendChance() const {
		return tauntDefendChance;
	}

	inline float getTauntDieChance() const {
		return tauntDieChance;
	}

	inline float getTauntAggressiveness() const {
		return tauntAggressiveness;
	}

	inline uint32 getPvpBitmask() const {
		return pvpBitmask;
	}

	inline uint32 getShipBitmask() const {
		return shipBitmask;
	}

	inline uint32 getOptionsBitmask() const {
		return optionsBitmask;
	}

	inline uint64 getCustomShipAiMap() const {
		return customShipAiMap;
	}

	inline uint32 getConversationTemplate() const {
		return conversationTemplate;
	}

	inline uint32 getConversationMobile() const {
		return conversationMobile;
	}

	inline uint32 getConversationMessage() const {
		return conversationMessage;
	}
};

} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::ship::ai;

#endif /* ShipAgentTemplate_H_ */
