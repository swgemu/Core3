/*
 * LuaCreatureObject.h
 *
 *  Created on: 31/08/2009
 *      Author: victor
 */

#ifndef LUACREATUREOBJECT_H_
#define LUACREATUREOBJECT_H_

#include "engine/engine.h"

#include "server/zone/objects/tangible/LuaTangibleObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class CreatureObject;

	class LuaCreatureObject : public LuaTangibleObject {
	public:
		// Constants
		static const char className[];
		static Luna<LuaCreatureObject>::RegType Register[];

		// Initialize the pointer
		LuaCreatureObject(lua_State *L);
		~LuaCreatureObject();

		int _setObject(lua_State* L);
		// Methods we will need to use
		int getBankCredits(lua_State *L);
		int setBankCredits(lua_State* L);
		int setHAM(lua_State* L);
		int setBaseHAM(lua_State* L);
		int setMaxHAM(lua_State* L);
		int sendSystemMessage(lua_State* L);
		int sendSystemMessageWithDI(lua_State* L);
		int sendSystemMessageWithTO(lua_State* L);
		int sendSystemMessageWithTT(lua_State* L);
		int sendGroupMessage(lua_State* L);
		int playMusicMessage(lua_State *L);
		int sendNewbieTutorialRequest(lua_State *L);
		int hasScreenPlayState(lua_State *L);
		int setScreenPlayState(lua_State *L);
		int getScreenPlayState(lua_State *L);
		int sendNewbieTutorialEnableHudElement(lua_State* L);
		int getInCellNumber(lua_State* L);
		int getBuildingParentID(lua_State* L);
		int sendOpenHolocronToPageMessage(lua_State* L);
		int getTargetID(lua_State* L);
		int clearCombatState(lua_State* L);
		int getHAM(lua_State* L);
		int getMaxHAM(lua_State* L);
		int inflictDamage(lua_State* L);
		//int playEffect(lua_State* L);
		int isFeigningDeath(lua_State* L);
		int hasState(lua_State* L);
		int setState(lua_State* L);
		int setPosture(lua_State* L);
		int setMoodString(lua_State* L);
		int getPosture(lua_State* L);
		int hasSkill(lua_State* L);
		int removeSkill(lua_State* L);
		int surrenderSkill(lua_State* L);
		int getConversationSession(lua_State* L);
		int doAnimation(lua_State* L);
		int engageCombat(lua_State* L);
		int getPlayerObject(lua_State* L);
		int getFaction(lua_State* L);
		int setFaction(lua_State* L);
		int isImperial(lua_State* L);
		int isRebel(lua_State* L);
		int isNeutral(lua_State* L);
		int getFirstName(lua_State* L);
		int isAiAgent(lua_State* L);
		int setFactionRank(lua_State* L);
		int getFactionRank(lua_State* L);
		int getCashCredits(lua_State* L);
		int subtractCashCredits(lua_State* L);
		int addCashCredits(lua_State* L);
		int removeScreenPlayState(lua_State* L);
		int setLootRights(lua_State* L);
		int isGrouped(lua_State* L);
		int isGroupedWith(lua_State* L);
		int getGroupSize(lua_State* L);
		int getGroupMember(lua_State* L);
		int setOptionsBitmask(lua_State* L);
		int addDotState(lua_State* L);
		int checkCooldownRecovery(lua_State* L);
		int addCooldown(lua_State* L);
		int isIncapacitated(lua_State* L);
		int isDead(lua_State* L);
		int getLevel(lua_State* L);
		int getQueueSize(lua_State*L);
		int isDancing(lua_State* L);
		int isPlayingMusic(lua_State* L);
		int getPerformanceName(lua_State* L);
		int getWalkSpeed(lua_State* L);
		int isAttackableBy(lua_State* L);
		int getSpecies(lua_State* L);
		int isDroidPet(lua_State* L);
		int isCombatDroidPet(lua_State* L);
		int awardExperience(lua_State* L);
		int getOwner(lua_State* L);
		int getCurrentSpeed(lua_State* L);
		int isInvisible(lua_State* L);
		int isInCombat(lua_State* L);
		int healDamage(lua_State* L);
		int getGroupID(lua_State* L);
		int enhanceCharacter(lua_State* L);
		int setWounds(lua_State* L);
		int setShockWounds(lua_State* L);
		int getForceSensitiveSkillCount(lua_State* L);
		int villageKnightPrereqsMet(lua_State* L);
		int getDamageDealerList(lua_State* L);
		int getHealingThreatList(lua_State* L);
		int getSkillMod(lua_State* L);
		int getGender(lua_State* L);
	private:
		// The pointer to the 'real object' defined in object.cc
		CreatureObject* realObject;
	};

}
}
}
}

using namespace server::zone::objects::creature;


#endif /* LUACREATUREOBJECT_H_ */
