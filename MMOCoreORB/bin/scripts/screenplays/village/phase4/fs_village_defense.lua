local QuestManager = require("managers.quest.quest_manager")

FsVillageDefense = ScreenPlay:new {
	questData = {
		ranged = {
			questNum = QuestManager.quests.FS_DEFEND_SET_FACTION,
			questName = "fs_defend_set_faction",
			outlaw = {
				questNum = QuestManager.quests.FS_DEFEND_01,
				questName = "fs_defend_01",
				killReq = 50
			},
			pirate = {
				questNum = QuestManager.quests.FS_DEFEND_02,
				questName = "fs_defend_02",
				killReq = 25
			}
		},
		melee = {
			questNum = QuestManager.quests.FS_DEFEND_SET_FACTION_02,
			questName = "fs_defend_set_faction_02",
			outlaw = {
				questNum = QuestManager.quests.FS_DEFEND_03,
				questName = "fs_defend_03",
				killReq = 50
			},
			pirate = {
				questNum = QuestManager.quests.FS_DEFEND_04,
				questName = "fs_defend_04",
				killReq = 25
			}
		}
	}
}

function FsVillageDefense:getVillageHealingCount(pPlayer)
	local count = tonumber(readScreenPlayData(pPlayer, "VillageDefense", "healing"))

	if count == nil then
		count = 0
	end

	return count
end

function FsVillageDefense:setVillageHealingCount(pPlayer, count)
	writeScreenPlayData(pPlayer, "VillageDefense", "healing", tostring(count))
end

function FsVillageDefense:acceptHealingQuest(pPlayer)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_1)
	self:setVillageHealingCount(pPlayer, 0)
end

function FsVillageDefense:checkHealerList(pCreature)
	if (pCreature == nil) then
		return
	end

	local healerList = CreatureObject(pCreature):getHealingThreatList()

	if (healerList == nil or #healerList == 0) then
		return
	end

	for i = 1, #healerList, 1 do
		local pPlayer = healerList[i]

		if (pPlayer ~= nil and SceneObject(pPlayer):isPlayerCreature() and (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_1) or QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_2))) then
			local healReq
			local pQuest

			if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_2)) then
				healReq = 100
				pQuest = getQuestInfo("fs_combat_healing_2")
			else
				healReq = 50
				pQuest = getQuestInfo("fs_combat_healing_1")
			end

			local currentHeals = self:getVillageHealingCount(pPlayer) + 1

			self:setVillageHealingCount(pPlayer, currentHeals)

			if (currentHeals > healReq) then
				return
			end

			if (pQuest ~= nil) then
				local quest = LuaQuestInfo(pQuest)
				local messageString = LuaStringIdChatParameter("@quest/quests:kill_credit")
				messageString:setTO(getStringId(quest:getJournalSummary()))
				messageString:setDI(healReq - currentHeals)
				CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
			end
		end
	end
end

function FsVillageDefense:getVillageDefenseCount(pPlayer, quest, mob)
	return tonumber(readScreenPlayData(pPlayer, "VillageDefense", quest .. mob))
end

function FsVillageDefense:setVillageDefenseCount(pPlayer, quest, mob, count)
	writeScreenPlayData(pPlayer, "VillageDefense", quest .. mob, tostring(count))
end

function FsVillageDefense:acceptRangedQuest(pPlayer)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_01)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_DEFEND_SET_FACTION)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_DEFEND_01)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_DEFEND_02)

	self:setVillageDefenseCount(pPlayer, "ranged", "outlaw", 0)
	self:setVillageDefenseCount(pPlayer, "ranged", "pirate", 0)
end

function FsVillageDefense:acceptMeleeQuest(pPlayer)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_02)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_DEFEND_SET_FACTION_02)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_DEFEND_03)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_DEFEND_04)

	self:setVillageDefenseCount(pPlayer, "melee", "outlaw", 0)
	self:setVillageDefenseCount(pPlayer, "melee", "pirate", 0)
end

function FsVillageDefense:incrementDefenseCredit(pPlayer, questType, mobType)
	if (pPlayer == nil or questType == nil or mobType == nil) then
		return
	end

	if (questType == "melee" and not self:isOnMeleeQuest(pPlayer)) then
		return
	end

	if (questType == "ranged" and not self:isOnRangedQuest(pPlayer)) then
		return
	end

	local currentCount = self:getVillageDefenseCount(pPlayer, questType, mobType)

	local questData = self.questData[questType]
	local mobData = questData[mobType]

	local killReq = mobData.killReq
	local questNum = mobData.questNum
	local questName = mobData.questName

	local pQuest = getQuestInfo(questName)

	if (pQuest == nil) then
		return
	end

	local quest = LuaQuestInfo(pQuest)

	if (currentCount >= killReq) then
		return
	end

	currentCount = currentCount + 1

	self:setVillageDefenseCount(pPlayer, questType, mobType, currentCount)

	if (currentCount < killReq) then
		local messageString = LuaStringIdChatParameter("@quest/quests:kill_credit")
		messageString:setTO(getStringId(quest:getJournalSummary()))
		messageString:setDI(killReq - currentCount)
		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
		return
	end

	QuestManager.completeQuest(pPlayer, questNum)

	if (QuestManager.hasCompletedQuest(pPlayer, questData.outlaw.questNum) and QuestManager.hasCompletedQuest(pPlayer, questData.pirate.questNum)) then
		QuestManager.completeQuest(pPlayer, questData.questNum)

		if (questType == "ranged") then
			QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_01)
			VillageJediManagerCommon.unlockBranch(pPlayer, "force_sensitive_combat_prowess_ranged_speed")

			local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

			if (pInventory ~= nil) then
				local pSculpture = giveItem(pInventory, "object/tangible/item/quest/force_sensitive/fs_sculpture_1.iff", -1, true)

				if (pSculpture == nil) then
					CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
				end
			end
		else
			QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_02)
			VillageJediManagerCommon.unlockBranch(pPlayer, "force_sensitive_enhanced_reflexes_melee_defense")
		end
	end
end

function FsVillageDefense:notifyKilledRaider(pVictim, pKiller)
	if pVictim == nil or pKiller == nil then
		return 1
	end

	local attackerList = CreatureObject(pVictim):getDamageDealerList()

	if attackerList == nil or #attackerList == 0 then
		return 1
	end

	local mobTemplate = SceneObject(pVictim):getObjectName()
	local mobType

	if (string.find(mobTemplate, "pirate") ~= nil) then
		mobType = "pirate"
	elseif (string.find(mobTemplate, "outlaw") ~= nil) then
		mobType  = "outlaw"
	end

	if (mobType == nil) then
		return 1
	end

	self:checkHealerList(pVictim)

	for i = 1, #attackerList, 1 do
		local pAttacker = attackerList[i]

		if (pAttacker ~= nil and self:hasActiveSarguilloQuest(pAttacker)) then
			if (self:isOnMeleeQuest(pAttacker)) then
				self:incrementDefenseCredit(pAttacker, "melee", mobType)
			elseif (self:isOnRangedQuest(pAttacker)) then
				self:incrementDefenseCredit(pAttacker, "ranged", mobType)
			end
		end
	end

	return 1
end

function FsVillageDefense:hasCompletedSarguilloQuest(pPlayer)
	if (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_01) and QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_02)) then
		return true
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_01) or QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_02)) then
		if (not self:hasActiveSarguilloQuest(pPlayer) and not self:canAcceptSarguilloQuest(pPlayer)) then
			return true
		end
	end

	return false
end

function FsVillageDefense:canAcceptSarguilloQuest(pPlayer)
	return self:canAcceptRangedQuest(pPlayer) or self:canAcceptMeleeQuest(pPlayer)
end

function FsVillageDefense:canAcceptRangedQuest(pPlayer)
	return not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_01) and not VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)
end

function FsVillageDefense:canAcceptMeleeQuest(pPlayer)
	return not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_02) and not VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)
end

function FsVillageDefense:hasActiveSarguilloQuest(pPlayer)
	return self:isOnMeleeQuest(pPlayer) or self:isOnRangedQuest(pPlayer)
end

function FsVillageDefense:completedSarguilloQuestPercent(pPlayer)
	if (self:isOnMeleeQuest(pPlayer)) then
		local outlawCount = self:getVillageDefenseCount(pPlayer, "melee", "outlaw")
		local outlawReq = self.questData.melee.outlaw.killReq
		local pirateCount = self:getVillageDefenseCount(pPlayer, "melee", "pirate")
		local pirateReq = self.questData.melee.pirate.killReq
		return (outlawCount + pirateCount) / (outlawReq + pirateReq)
	elseif (self:isOnRangedQuest(pPlayer)) then
		local outlawCount = self:getVillageDefenseCount(pPlayer, "ranged", "outlaw")
		local outlawReq = self.questData.ranged.outlaw.killReq
		local pirateCount = self:getVillageDefenseCount(pPlayer, "ranged", "pirate")
		local pirateReq = self.questData.ranged.pirate.killReq
		return (outlawCount + pirateCount) / (outlawReq + pirateReq)
	else
		return 0
	end
end

function FsVillageDefense:isOnMeleeQuest(pPlayer)
	return QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_02) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_02)
end

function FsVillageDefense:isOnRangedQuest(pPlayer)
	return QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_01) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_01)
end

function FsVillageDefense:doPhaseChangeFail(pPlayer)
	self:setVillageHealingCount(pPlayer, 0)

	self:setVillageDefenseCount(pPlayer, "melee", "outlaw", 0)
	self:setVillageDefenseCount(pPlayer, "melee", "pirate", 0)

	self:setVillageDefenseCount(pPlayer, "ranged", "outlaw", 0)
	self:setVillageDefenseCount(pPlayer, "ranged", "pirate", 0)

	if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_01) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_01)) then
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_01)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_DEFEND_SET_FACTION)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_DEFEND_01)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_DEFEND_02)
	end

	if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_02) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_02)) then
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_DEFEND_WAIT_02)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_DEFEND_SET_FACTION_02)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_DEFEND_03)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_DEFEND_04)
	end

	if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_1) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_1)) then
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_1)
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:combat_quest_failed_timeout")
	end
	if (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_2) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_2)) then
		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_1)
	end
end
