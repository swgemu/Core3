local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

FsSurvey = {  }

function FsSurvey:sampleEventHandler(pPlayer, pResourceSpawn, density)
	if (pPlayer == nil or pResourceSpawn == nil) then
		return 0
	end

	local chance = getRandomNumber(1,5)

	if (chance ~= 1) then
		return 0
	end

	local phase = VillageJediManagerTownship:getCurrentPhase()
	
	if (phase ~= 2 and phase ~= 3) then
		return 0
	end

	local questName = self:hasSurveyorQuest(pPlayer, phase)

	if (questName == "") then
		return 1
	end

	if (density < 50) then
		return 0
	end

	local spawn = LuaResourceSpawn(pResourceSpawn)

	if (spawn == nil) then
		return 0
	end

	local pQuest = getQuestInfo(questName)

	if (pQuest == nil) then
		return 0
	end

	local quest = LuaQuestInfo(pQuest)

	local resourceNeeded = quest:getQuestTarget()

	if (not spawn:isType(resourceNeeded)) then
		return 0
	end

	local completeTask = quest:getTaskOnComplete()

	local pCompleteQuest = getQuestInfo(completeTask)

	if (pCompleteQuest == nil) then
		return 0
	end

	local completeQuest = LuaQuestInfo(pCompleteQuest)

	local questReward = completeQuest:getQuestTarget()

	local mainQuestID = getPlayerQuestID(questName)
	local rewardQuestID = getPlayerQuestID(completeTask)

	QuestManager.completeQuest(pPlayer, mainQuestID)
	QuestManager.completeQuest(pPlayer, rewardQuestID)

	local nextQuest = completeQuest:getTaskOnComplete()

	local rewardTemplate = completeQuest:getQuestTarget()
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory ~= nil) then
		local pReward = giveItem(pInventory, rewardTemplate, -1, true)

		if (pReward == nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
		else
			if (nextQuest ~= "fs_survey_phase2_reward" and nextQuest ~= "fs_survey_phase3_reward") then
				self:giveResourceStats(pReward, density)
			end
		end
	end

	local nextQuestID = getPlayerQuestID(nextQuest)
	QuestManager.activateQuest(pPlayer, nextQuestID)

	if (nextQuest == "fs_survey_phase2_reward" or nextQuest == "fs_survey_phase3_reward") then
		QuestManager.completeQuest(pPlayer, nextQuestID)
		VillageJediManagerCommon.setCompletedQuestThisPhase(pPlayer)

		if (nextQuest == "fs_survey_phase2_reward") then
			QuestManager.completeQuest(pPlayer, QuestManager.quests.SURVEY_PHASE2_MAIN)
			VillageJediManagerCommon.unlockBranch(pPlayer, "force_sensitive_heightened_senses_surveying")
		else
			QuestManager.completeQuest(pPlayer, QuestManager.quests.SURVEY_PHASE3_MAIN)
			VillageJediManagerCommon.unlockBranch(pPlayer, "force_sensitive_heightened_senses_luck")
		end

		return 1
	end

	return 0
end

function FsSurvey:giveResourceStats(pResource, density)
	if (pResource == nil) then
		return
	end

	local average = density * 10

	local objTemplate = SceneObject(pResource):getTemplateObjectPath()
	local resource = LuaCustomIngredient(pResource)

	-- Clear default attributes to set custom ones
	resource:clearAttributes()
	
	if (objTemplate == "object/tangible/loot/quest/ardanium_ii.iff") then
		resource:addAttribute("res_potential_energy", self:getResourceValue(average));
		resource:addAttribute("res_quality", self:getResourceValue(average));
	elseif (objTemplate == "object/tangible/loot/quest/wind_crystal.iff") then
		resource:addAttribute("res_potential_energy", self:getResourceValue(average));
	elseif (objTemplate == "object/tangible/loot/quest/ostrine.iff") then
		resource:addAttribute("res_malleability", self:getResourceValue(average));
		resource:addAttribute("res_quality", self:getResourceValue(average));
	elseif (objTemplate == "object/tangible/loot/quest/endrine.iff") then
		resource:addAttribute("res_malleability", self:getResourceValue(average));
		resource:addAttribute("res_quality", self:getResourceValue(average));
		resource:addAttribute("res_toughness", self:getResourceValue(average));
	elseif (objTemplate == "object/tangible/loot/quest/rudic.iff") then
		resource:addAttribute("res_conductivity", self:getResourceValue(average));
		resource:addAttribute("res_decay_resist", self:getResourceValue(average));
		resource:addAttribute("res_quality", self:getResourceValue(average));
		resource:addAttribute("res_shock_resistance", self:getResourceValue(average));
	end
end

function FsSurvey:getResourceValue(average)
	local rand = getRandomNumber(average - 50, average + 50)

	if (rand > 1000) then
		rand = 1000
	elseif (rand < 150) then
		rand = 150
	end

	return rand
end

function FsSurvey:hasSurveyorQuest(pPlayer, phase)
	local hasQuest = ""
	for i = 1, 8, 1 do
		local questName = "survey_phase" .. phase .. "_0" .. i
		local questID = getPlayerQuestID(questName)

		if QuestManager.hasActiveQuest(pPlayer, questID) then
			hasQuest = questName
		end
	end

	return hasQuest
end
