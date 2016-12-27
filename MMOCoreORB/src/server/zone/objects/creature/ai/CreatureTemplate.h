/*
 * CreatureTemplate.h
 *
 *  Created on: Oct 9, 2010
 *      Author: dannuic
 */

#ifndef CREATURETEMPLATE_H_
#define CREATURETEMPLATE_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/ai/variables/CreatureAttackMap.h"
#include "templates/params/creature/CreatureFlag.h"
#include "templates/tangible/SharedWeaponObjectTemplate.h"
#include "server/zone/managers/loot/lootgroup/LootGroupCollection.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {

class CreatureTemplate : public Object {
protected:
	String templateName;
	String customName;

	unsigned int armor;

	float kinetic;
	float energy;
	float electricity;
	float stun;
	float blast;
	float heat;
	float cold;
	float acid;
	float lightSaber;

	float tamingChance;
	unsigned int ferocity;

	String meatType;
	String boneType;
	String hideType;
	String milkType;

	int milk;
	int hideAmount;
	int boneAmount;
	int meatAmount;

	String objectName;
	uint32 planetMapCategory;
	int randomNameType;
	bool randomNameTag;
	String socialGroup;
	String faction;

	int level;

	float chanceHit;
	int damageMin;
	int damageMax;
	float specialDamageMult;
	int range;

	float scale;

	int baseXp;
	int baseHAM;
	int baseHAMmax;

	int aggroRadius;
	unsigned int pvpBitmask;
	unsigned int creatureBitmask;
	unsigned int diet;


	Vector<String> templates;

	LootGroupCollection lootgroups;

	Vector<String> weapons;

	CreatureAttackMap* attacks;
	uint32 conversationTemplate;
	uint32 optionsBitmask;

	String patrolPathTemplate;

	String outfit;

	String aiTemplate;
	String defaultWeapon;
	String defaultAttack;

	String controlDeviceTemplate;
	String containerComponentTemplate;

	String reactionStf;
	String personalityStf;

public:
	CreatureTemplate();

	virtual ~CreatureTemplate();

	void readObject(LuaObject* templateData);

	inline float getKinetic() {
		if (isSpecialProtection(SharedWeaponObjectTemplate::KINETIC))
			return kinetic - 100;
		else
			return kinetic;
	}

	inline float getEnergy() {
		if (isSpecialProtection(SharedWeaponObjectTemplate::ENERGY))
			return energy - 100;
		else
			return energy;
	}

	inline float getElectricity() {
		if (isSpecialProtection(SharedWeaponObjectTemplate::ELECTRICITY))
			return electricity - 100;
		else
			return electricity;
	}

	inline float getStun() {
		if (isSpecialProtection(SharedWeaponObjectTemplate::STUN))
			return stun - 100;
		else
			return stun;
	}

	inline float getBlast() {
		if (isSpecialProtection(SharedWeaponObjectTemplate::BLAST))
			return blast - 100;
		else
			return blast;
	}

	inline float getHeat() {
		if (isSpecialProtection(SharedWeaponObjectTemplate::HEAT))
			return heat - 100;
		else
			return heat;
	}

	inline float getCold() {
		if (isSpecialProtection(SharedWeaponObjectTemplate::COLD))
			return cold - 100;
		else
			return cold;
	}

	inline float getAcid() {
		if (isSpecialProtection(SharedWeaponObjectTemplate::ACID))
			return acid - 100;
		else
			return acid;
	}

	inline float getLightSaber() {
		if (isSpecialProtection(SharedWeaponObjectTemplate::LIGHTSABER))
			return lightSaber - 100;
		else
			return lightSaber;
	}

	inline bool isStalker() {
		return creatureBitmask & CreatureFlag::STALKER;
	}

	inline bool isBaby() {
		return creatureBitmask & CreatureFlag::BABY;
	}

	inline bool isKiller() {
		return creatureBitmask & CreatureFlag::KILLER;
	}

	inline bool isPack() {
		return creatureBitmask & CreatureFlag::PACK;
	}

	inline bool isHerd() {
		return creatureBitmask & CreatureFlag::HERD;
	}

	inline float getTame() {
		return tamingChance;
	}

	inline String& getMeatType() {
		return meatType;
	}

	inline String& getBoneType() {
		return boneType;
	}

	inline String& getHideType() {
		return hideType;
	}

	inline String& getMilkType() {
		return milkType;
	}

	inline String& getCustomName() {
		return customName;
	}

	inline float getMilk() {
		return milk;
	}

	inline float getHideMax() {
		return hideAmount;
	}

	inline float getBoneMax() {
		return boneAmount;
	}

	inline float getMeatMax() {
		return meatAmount;
	}

	inline unsigned int getFerocity() {
		return ferocity;
	}

	inline unsigned int getArmor() {
		return armor;
	}

	inline String getObjectName() {
		return objectName;
	}

	inline uint32 getPlanetMapCategory() {
		return planetMapCategory;
	}

	inline int getRandomNameType() {
		return randomNameType;
	}

	inline bool getRandomNameTag() {
		return randomNameTag;
	}

	inline String getSocialGroup() {
		return socialGroup;
	}

	inline uint32 getConversationTemplate() {
		return conversationTemplate;
	}

	inline uint32 getOptionsBitmask() {
		return optionsBitmask;
	}

	inline String getFaction() {
		return faction;
	}

	inline int getLevel() {
		return level;
	}

	inline float getChanceHit() {
		return chanceHit;
	}

	inline float getScale() {
		return scale;
	}

	inline int getDamageMin() {
		return damageMin;
	}

	inline int getDamageMax() {
		return damageMax;
	}

	inline float getSpecialDamageMult() {
		return specialDamageMult;
	}

	inline int getRange() {
		return range;
	}

	inline int getBaseXp() {
		return baseXp;
	}

	inline int getBaseHAM() {
		return baseHAM;
	}

	inline int getBaseHAMmax() {
		return baseHAMmax;
	}

	inline int getAggroRadius() {
		return aggroRadius;
	}

	inline uint32 getPvpBitmask() {
		return pvpBitmask;
	}

	inline uint32 getCreatureBitmask() {
		return creatureBitmask;
	}

	inline uint32 getDiet() {
		return diet;
	}

	inline Vector<String>& getTemplates() {
		return templates;
	}

	inline LootGroupCollection* getLootGroups() {
		return &lootgroups;
	}

	inline Vector<String>& getWeapons() {
		return weapons;
	}

	inline CreatureAttackMap* getAttacks() {
		return attacks;
	}

	inline String getPatrolPathTemplate() {
		return patrolPathTemplate;
	}

	void setTemplateName(const String& t) {
		templateName = t;
	}

	inline String getTemplateName() {
		return templateName;
	}

	inline bool hasPatrolPathTemplate() {
		return !patrolPathTemplate.isEmpty();
	}

	inline String getOutfit() {
		return outfit;
	}

	inline String getAiTemplate() {
		return aiTemplate;
	}

	inline String getDefaultWeapon(){
		return defaultWeapon;
	}

	inline String getDefaultAttack(){
		return defaultAttack;
	}

	inline String getControlDeviceTemplate() {
		return controlDeviceTemplate;
	}

	inline String getContainerComponentTemplate() {
		return containerComponentTemplate;
	}

	inline String getReactionStf() {
		return reactionStf;
	}

	inline String getPersonalityStf() {
		return personalityStf;
	}

	inline bool isSpecialProtection(int resistType) {
		switch (resistType) {
		case SharedWeaponObjectTemplate::KINETIC:
			return kinetic > 100;
			break;
		case SharedWeaponObjectTemplate::ENERGY:
			return energy > 100;
			break;
		case SharedWeaponObjectTemplate::ELECTRICITY:
			return electricity > 100;
			break;
		case SharedWeaponObjectTemplate::STUN:
			return stun > 100;
			break;
		case SharedWeaponObjectTemplate::BLAST:
			return blast > 100;
			break;
		case SharedWeaponObjectTemplate::HEAT:
			return heat > 100;
			break;
		case SharedWeaponObjectTemplate::COLD:
			return cold > 100;
			break;
		case SharedWeaponObjectTemplate::ACID:
			return acid > 100;
			break;
		case SharedWeaponObjectTemplate::LIGHTSABER:
			return lightSaber > 100;
			break;
		}

		return false;
	}
};

}
}
}
}
}

using namespace server::zone::objects::creature::ai;

#endif /* CREATURETEMPLATE_H_ */
