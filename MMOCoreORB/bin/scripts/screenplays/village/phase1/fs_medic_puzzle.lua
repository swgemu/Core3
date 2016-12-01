local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

FsMedicPuzzle = ScreenPlay:new {
	totalSymptoms = 12
}

function FsMedicPuzzle:giveSymptoms(pPlayer, pNpc)
	local playerID = SceneObject(pPlayer):getObjectID()
	local npcID = SceneObject(pNpc):getObjectID()
	local maxSymptoms = getRandomNumber(3, self.totalSymptoms - 3)
	for i = 1, maxSymptoms, 1 do
		local symptomNum = getRandomNumber(0, self.totalSymptoms - 1)

		while self:hasSpecificSymptom(playerID, npcID, symptomNum) do
			symptomNum = getRandomNumber(0, self.totalSymptoms - 1)
		end

		writeData(playerID .. ":fs_medic_puzzle_npc:" .. npcID .. ":symptom" .. symptomNum, 1)
	end
end

function FsMedicPuzzle:hasSpecificSymptom(playerID, npcID, symptom)
	return readData(playerID .. ":fs_medic_puzzle_npc:" .. npcID .. ":symptom" .. symptom) == 1
end

function FsMedicPuzzle:hasAnySymptoms(pPlayer, pNpc)
	local playerID = SceneObject(pPlayer):getObjectID()
	local npcID = SceneObject(pNpc):getObjectID()
	for i = 0, self.totalSymptoms - 1, 1 do
		if self:hasSpecificSymptom(playerID, npcID, i) then
			return true
		end
	end

	return false
end

function FsMedicPuzzle:cleanupNpc(pPlayer, pNpc)
	local playerID = SceneObject(pPlayer):getObjectID()
	local npcID = SceneObject(pNpc):getObjectID()
	for i = 0, self.totalSymptoms - 1, 1 do
		deleteData(playerID .. ":fs_medic_puzzle_npc:" .. npcID .. ":symptom" .. i)
	end
end

function FsMedicPuzzle:getSymptoms(pPlayer, pNpc)
	local playerID = SceneObject(pPlayer):getObjectID()
	local npcID = SceneObject(pNpc):getObjectID()
	local numSymptoms = 0
	local symptomString = ""
	local lastSymptom = self:getLastSymptom(pPlayer, pNpc)

	for i = 0, self.totalSymptoms - 1, 1 do
		if self:hasSpecificSymptom(playerID, npcID, i) then
			numSymptoms = numSymptoms + 1
			if (numSymptoms == 1) then
				symptomString = getStringId("@quest/force_sensitive/fs_medic:symptom" .. i)
			else
				if (i == lastSymptom) then
					symptomString = symptomString .. " and " .. getStringId("@quest/force_sensitive/fs_medic:symptom" .. i)
				else
					symptomString = symptomString .. ", " .. getStringId("@quest/force_sensitive/fs_medic:symptom" .. i)
				end
			end
		end
	end

	return symptomString
end

function FsMedicPuzzle:getCuredVillagerCount(pPlayer)
	local count = QuestManager.getStoredVillageValue(pPlayer, "FsMedicPuzzleVillagerCount")

	if (count == "") then
		count = 0
	end

	return tonumber(count)
end

function FsMedicPuzzle:setCuredVillagerCount(pPlayer, count)
	QuestManager.setStoredVillageValue(pPlayer, "FsMedicPuzzleVillagerCount", count)
end

function FsMedicPuzzle:getPatientsLeftToTreat(pPlayer)
	local count = self:getCuredVillagerCount(pPlayer)
	if QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_03) then
		return 15 - count
	elseif QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02) then
		return 10 - count
	elseif QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01) then
		return 5 - count
	end
end

function FsMedicPuzzle:getSymptomCount(pPlayer, pNpc)
	local playerID = SceneObject(pPlayer):getObjectID()
	local npcID = SceneObject(pNpc):getObjectID()
	local symptomCount = 0
	for i = 0, self.totalSymptoms - 1, 1 do
		if self:hasSpecificSymptom(playerID, npcID, i) then
			symptomCount = symptomCount + 1
		end
	end
	return symptomCount
end

function FsMedicPuzzle:getLastSymptom(pPlayer, pNpc)
	local playerID = SceneObject(pPlayer):getObjectID()
	local npcID = SceneObject(pNpc):getObjectID()
	local lastSymptom = -1
	for i = 0, self.totalSymptoms - 1, 1 do
		if self:hasSpecificSymptom(playerID, npcID, i) then
			lastSymptom = i
		end
	end
	return lastSymptom
end

function FsMedicPuzzle:cureSymptoms(pPlayer, pNpc, pPack)
	local puzzlePack = LuaFsPuzzlePack(pPack)
	local cureSymptomOne = puzzlePack:getCureSymptomOne()
	local cureSymptomTwo = puzzlePack:getCureSymptomTwo()
	local giveSymptomOne = puzzlePack:getGiveSymptomOne()
	local playerID = SceneObject(pPlayer):getObjectID()
	local npcID = SceneObject(pNpc):getObjectID()

	spatialChat(pNpc, "@quest/force_sensitive/fs_medic:admin_meds")
	if (cureSymptomOne >= 0) then
		deleteData(playerID .. ":fs_medic_puzzle_npc:" .. npcID .. ":symptom" .. cureSymptomOne)
	end

	if (cureSymptomTwo >= 0) then
		deleteData(playerID .. ":fs_medic_puzzle_npc:" .. npcID .. ":symptom" .. cureSymptomTwo)
	end

	if (giveSymptomOne >= 0) then
		writeData(playerID .. ":fs_medic_puzzle_npc:" .. npcID .. ":symptom" .. giveSymptomOne, 1)
	end

	local symptomCount = self:getSymptomCount(pPlayer, pNpc)

	if (symptomCount == 0) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_medic:npc_cured")
		local villagerCount = self:getCuredVillagerCount(pPlayer)
		self:setCuredVillagerCount(pPlayer, villagerCount + 1)

		for i = 0, self.totalSymptoms - 1, 1 do
			deleteData(playerID .. ":fs_medic_puzzle_npc:" .. npcID .. ":symptom" .. i)
		end
	end

	SceneObject(pPack):destroyObjectFromWorld()
	SceneObject(pPack):destroyObjectFromDatabase()
end

function FsMedicPuzzle:cleanUp(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):removeRewardedSchematic("object/draft_schematic/item/quest_item/fs_medic_puzzle_heal_pack.iff", true)
end

function FsMedicPuzzle:doPhaseChange(pPlayer)
	local hasActiveQuest = false
	for i = 1, 3, 1 do
		local questName = "fs_medic_puzzle_quest_0" .. i
		local questID = getPlayerQuestID(questName)

		if QuestManager.hasActiveQuest(pPlayer, questID) and not QuestManager.hasCompletedQuest(pPlayer, questID) then
			hasActiveQuest = true
			QuestManager.resetQuest(pPlayer, questID)
		end
	end

	if QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01) then
		hasActiveQuest = false
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_FINISH)
	end

	if (hasActiveQuest) then
		CreatureObject(pPlayer):sendSystemMessage("@fs_quest_village:combat_quest_failed_timeout")
	end

	self:cleanUp(pPlayer)
end

return FsMedicPuzzle
