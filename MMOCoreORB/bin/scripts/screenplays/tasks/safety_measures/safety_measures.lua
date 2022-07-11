local QuestManager = require("managers.quest.quest_manager")

SafetyMeasures = ScreenPlay:new {
	numberOfActs = 1,
	screenplayName = "SafetyMeasures",

	KILLWORRTS = 1,
	KILLRILLS = 2,
	KILLBRIGANDS = 3,
	LOOTDATAPAD = 4,
	BRIGANDLEADER = 5,

	questGiver = "gerak_vurtimis",
	planet = "tatooine",
	questGiverLocation = {-1254, 12, -3617},
	brigandCampLocation1 = {1144, 151, -3920},
	brigandCampLocation2 = {1002, 187, -3019},
	brigandLeaderLocation = {1500, 180, -2000},

	mobiles = {
		-- Quest Gives
		{"gerak_vurtimis", -1254, 12, -3617, 0, 0},

		-- Brigand Camp 1
		{"brigand", 1150, 151, -3920},
		{"brigand", 1145, 151, -3927},
		{"brigand", 1140, 151, -3922},
		{"brigand_assassin", 1138, 151, -3920},
		-- outside of camp
		{"brigand_scout", 1127, 158, -3904},

		-- Brigand Camp 2
		{"brigand", 1010, 187, -3015},
		{"brigand", 1008, 187, -3012},
		{"brigand", 1003, 187, -3027},
		{"brigand", 997, 187, -3028},
		{"brigand", 988, 187, -3020},
		{"brigand_assassin", 995, 187, -3020},
		{"brigand_assassin", 997, 187, -3024},
		{"brigand_assassin", 1002, 187, -3024},
		-- outside of camp
		{"brigand_scout", 1045, 182, -3015},
		{"brigand_scout", 1047, 182, -3019},
		{"brigand_scout", 987, 182, -2973},
		{"brigand_scout", 982, 183, -2974},

		-- Brigand Leader Camp
		{"brigand_leader", 1500, 180, -2000},
		{"brigand_assassin", 1500, 180, -2000},
		{"brigand_assassin", 1500, 180, -2000},
	},

	brigandCampObjects = {
		{"object/static/structure/general/trash_pile_s01.iff", -0.900, -0.103, 0.959, 0},
		{"object/static/structure/corellia/corl_tent_hut_s01.iff", -1.393, 0.011, 2.875, 0 },
		{"object/static/structure/general/camp_lawn_chair_s01.iff", -0.205, -0.145, -1.388, -145.141},
		{"object/static/structure/general/campfire_smoldering.iff", 2.029, 0.303, -3.361, 0},
		{"object/static/structure/general/camp_cot_s01.iff", 0.468, -0.066, 0.915, 123.759}
	},
}

registerScreenPlay("SafetyMeasures", true)

function SafetyMeasures:start()
	if (not isZoneEnabled(self.planet)) then
		return
	end

	self:spawnBrigandCamp1()
	self:spawnBrigandCamp2()
	self:spawnBrigandLeaderCamp()

	self:spawnMobiles()
end

function SafetyMeasures:spawnBrigandCamp1()
	local x = self.brigandCampLocation1[1]
	local y = self.brigandCampLocation1[3]

	-- Spawn Theater for terrain
	spawnTheaterObject(self.planet, x, getWorldFloor(x, y, self.planet), y, true)

	-- Spawn Camp Area Decor
	for i = 1, #self.brigandCampObjects, 1 do
		local object = self.brigandCampObjects[i]

		spawnSceneObject(self.planet, object[1], object[2] + x, object[3] + 151, object[4] + y, 0, object[5])
	end

	createNavMesh(self.planet, x, y, 64, true, "brigand_camp1")
end

function SafetyMeasures:spawnBrigandCamp2()
	local x = self.brigandCampLocation2[1]
	local y = self.brigandCampLocation2[3]

	-- Spawn Theater for terrain
	spawnTheaterObject(self.planet, x, getWorldFloor(x, y, self.planet), y, true)

	-- Spawn Camp Area Decor
	for i = 1, #self.brigandCampObjects, 1 do
		local object = self.brigandCampObjects[i]

		spawnSceneObject(self.planet, object[1], object[2] + x, object[3] + 188, object[4] + y, 0, object[5])
	end

	createNavMesh(self.planet, x, y, 64, true, "brigand_camp2")
end

function SafetyMeasures:spawnBrigandLeaderCamp()
	local x = self.brigandLeaderLocation[1]
	local y = self.brigandLeaderLocation[3]

	-- Spawn Theater for terrain
	spawnTheaterObject(self.planet, x, getWorldFloor(x, y, self.planet), y, true)

	-- Spawn Camp Area Decor
	for i = 1, #self.brigandCampObjects, 1 do
		local object = self.brigandCampObjects[i]

		spawnSceneObject(self.planet, object[1], object[2] + x, object[3] + 180, object[4] + y, 0, object[5])
	end

	createNavMesh(self.planet, x, y, 64, true, "brigand_leader_camp")
end

function SafetyMeasures:spawnMobiles()
	for i = 1, #self.mobiles, 1 do
		local mobile = self.mobiles[i]

		local pMobile = spawnMobile(self.planet, mobile[1], -1, mobile[2], mobile[3], mobile[4], 0, 0)

		if (pMobile ~= nil and string.find(mobile[1], "brigand")) then
			createObserver(CREATUREDESPAWNED, "SafetyMeasures", "onDespawn", pMobile)

			local mobID = SceneObject(pMobile):getObjectID()
			writeData(mobID .. ":SafetyMeasures:mobID:", i)
		end
	end
end

function SafetyMeasures:startQuest(pPlayer, pNpc, quest)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ghost = LuaPlayerObject(pGhost)
	local playerID = SceneObject(pPlayer):getObjectID()

	dropObserver(KILLEDCREATURE, "SafetyMeasures", "notifyKilledCreature", pPlayer)
	createObserver(KILLEDCREATURE, "SafetyMeasures", "notifyKilledCreature", pPlayer)

	if (quest == self.KILLWORRTS) then
		ghost:activateJournalQuest(QuestManager.questCRC.QUEST_LF_SAFETY1, true)

		CreatureObject(pNpc):doAnimation("nod")
	elseif (quest == self.KILLRILLS) then
		ghost:activateJournalQuest(QuestManager.questCRC.QUEST_LF_SAFETY2, true)

		CreatureObject(pNpc):doAnimation("nod")
	elseif (quest == self.KILLBRIGANDS) then
		ghost:activateJournalQuest(QuestManager.questCRC.QUEST_LF_SAFETY3, true)

		local waypointID = ghost:addWaypoint(self.planet, "Brigand Camp 1", "Brigand Camp 1", self.brigandCampLocation1[1], self.brigandCampLocation1[3], WAYPOINTYELLOW, true, true, 0, 0)
		writeData(playerID .. ":SafetyMeasures:waypointID:", waypointID)
		CreatureObject(pNpc):doAnimation("bow")
	elseif (quest == self.LOOTDATAPAD) then
		ghost:activateJournalQuest(QuestManager.questCRC.QUEST_LF_SAFETY4, true)

		local waypointID = ghost:addWaypoint(self.planet, "Brigand Camp 2", "Brigand Camp 2", self.brigandCampLocation2[1], self.brigandCampLocation2[3], WAYPOINTYELLOW, true, true, 0, 0)
		writeData(playerID .. ":SafetyMeasures:waypointID:", waypointID)
		CreatureObject(pNpc):doAnimation("bow")
	elseif (quest == self.BRIGANDLEADER) then
		ghost:activateJournalQuest(QuestManager.questCRC.QUEST_LF_SAFETY5, true)

		local waypointID = ghost:addWaypoint(self.planet, "Brigand Leader Camp", "Brigand Leader Camp", self.brigandLeaderLocation[1], self.brigandLeaderLocation[3], WAYPOINTYELLOW, true, true, 0, 0)
		writeData(playerID .. ":SafetyMeasures:waypointID:", waypointID)

		CreatureObject(pNpc):doAnimation("applause_excited")
	end
end

function SafetyMeasures:completeQuest(pPlayer, pNpc, quest)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ghost = LuaPlayerObject(pGhost)
	local playerID = SceneObject(pPlayer):getObjectID()

	if (quest == self.KILLWORRTS) then
		ghost:completeJournalQuest(QuestManager.questCRC.QUEST_LF_SAFETY1, true)
	elseif (quest == self.KILLRILLS) then
		ghost:completeJournalQuest(QuestManager.questCRC.QUEST_LF_SAFETY2, true)
	elseif (quest == self.KILLBRIGANDS) then
		ghost:completeJournalQuest(QuestManager.questCRC.QUEST_LF_SAFETY3, true)
	elseif (quest == self.LOOTDATAPAD) then
		ghost:completeJournalQuest(QuestManager.questCRC.QUEST_LF_SAFETY4, true)
	elseif (quest == self.BRIGANDLEADER) then
		ghost:completeJournalQuest(QuestManager.questCRC.QUEST_LF_SAFETY5, true)
	end

	self:grantReward(pPlayer, quest)
	self:removeWaypoint(pPlayer, 0)

	if (pNpc ~= nil) then
		CreatureObject(pNpc):doAnimation("applause_excited")
	end
end

function SafetyMeasures:grantReward(pPlayer, quest)
	if (pPlayer == nil) then
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return
	end

	local credits = 100
	local experience = 100

	if (quest == self.KILLWORRTS) then
		experience = 250
		credits = 500
	elseif (quest == self.KILLRILLS) then
		experience = 250
		credits = 500
	elseif (quest == self.KILLBRIGANDS) then
		giveItem(pInventory, "object/tangible/skill_buff/skill_buff_pistol_speed.iff", -1)

		experience = 500
		credits = 750
	elseif (quest == self.LOOTDATAPAD) then
		experience = 750
		credits = 1000
	elseif (quest == self.BRIGANDLEADER) then
		giveItem(pInventory, "object/tangible/skill_buff/skill_buff_pistol_speed.iff", -1)

		experience = 750
		credits = 2500
	end

	local messageString = LuaStringIdChatParameter("@base_player:prose_grant_xp")
	messageString:setDI(experience)
	messageString:setTO("@exp_n:combat_general")
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())

	ThemeParkLogic:giveCredits(pPlayer, credits)
	CreatureObject(pPlayer):awardExperience("combat_general", experience, true)
end

function SafetyMeasures:respawn(mob, spawnNumber)
	local mobile = self.mobiles[tonumber(spawnNumber)]

	local pMobile = spawnMobile(self.planet, mobile[1], -1, mobile[2], mobile[3], mobile[4], 0, 0)

	if (pMobile ~= nil and string.find(mobile[1], "brigand")) then
		createObserver(CREATUREDESPAWNED, "SafetyMeasures", "onDespawn", pMobile)

		local mobID = SceneObject(pMobile):getObjectID()
		writeData(mobID .. ":SafetyMeasures:mobID:", spawnNumber)
	end
end

function SafetyMeasures:removeWaypoint(pPlayer, giveReturn)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ghost = LuaPlayerObject(pGhost)

	local playerID = SceneObject(pPlayer):getObjectID()
	local currentID = readData(playerID .. ":SafetyMeasures:waypointID:")

	if (currentID > 0) then
		ghost:removeWaypoint(currentID, true)
	end

	if (giveReturn > 0) then
		local waypointID = ghost:addWaypoint(self.planet, "Gerak Vertimis", "Gerak Vertimis", self.questGiverLocation[1], self.questGiverLocation[3], WAYPOINTYELLOW, true, true, 0, 0)

		writeData(playerID .. ":SafetyMeasures:waypointID:", waypointID)
	end
end

--[[

	========== Observers ==========

]]

function SafetyMeasures:notifyKilledCreature(pPlayer, pVictim)
	if (pPlayer == nil or pVictim == nil) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return 0
	end

	local victimName = SceneObject(pVictim):getObjectName()
	local playerID = SceneObject(pPlayer):getObjectID()

	if (ghost:isJournalQuestActive(QuestManager.questCRC.QUEST_LF_SAFETY1) and (victimName == "worrt" or victimName == "minor_worrt")) then
		local totalKilled = readData(playerID .. ":SafetyMeasures:killCount:") + 1

		if (totalKilled >= 10) then
			ghost:completeJournalQuestTask(QuestManager.questCRC.QUEST_LF_SAFETY1, 0, true)
			ghost:activateJournalQuestTask(QuestManager.questCRC.QUEST_LF_SAFETY1, 1, true)

			self:removeWaypoint(pPlayer, 1)

			deleteData(playerID .. ":SafetyMeasures:killCount:")
			return 1
		end

		writeData(playerID .. ":SafetyMeasures:killCount:", totalKilled)
	elseif (ghost:isJournalQuestActive(QuestManager.questCRC.QUEST_LF_SAFETY2) and victimName == "rill") then
		local totalKilled = readData(playerID .. ":SafetyMeasures:killCount:") + 1

		if (totalKilled >= 10) then
			ghost:completeJournalQuestTask(QuestManager.questCRC.QUEST_LF_SAFETY2, 0, true)
			ghost:activateJournalQuestTask(QuestManager.questCRC.QUEST_LF_SAFETY2, 1, true)

			self:removeWaypoint(pPlayer, 1)

			deleteData(playerID .. ":SafetyMeasures:killCount:")
			return 1
		end

		writeData(playerID .. ":SafetyMeasures:killCount:", totalKilled)
	elseif (ghost:isJournalQuestActive(QuestManager.questCRC.QUEST_LF_SAFETY3) and (string.find(victimName, "brigand") or string.find(victimName, "assassin"))) then
		local totalKilled = readData(playerID .. ":SafetyMeasures:killCount:") + 1

		if (totalKilled >= 12) then
			ghost:completeJournalQuestTask(QuestManager.questCRC.QUEST_LF_SAFETY3, 0, true)
			ghost:activateJournalQuestTask(QuestManager.questCRC.QUEST_LF_SAFETY3, 1, true)

			self:removeWaypoint(pPlayer, 1)

			deleteData(playerID .. ":SafetyMeasures:killCount:")
			return 1
		end

		writeData(playerID .. ":SafetyMeasures:killCount:", totalKilled)
	elseif (ghost:isJournalQuestActive(QuestManager.questCRC.QUEST_LF_SAFETY4) and (string.find(victimName, "brigand") or string.find(victimName, "assassin"))) then
		if (getRandomNumber(100) <= 20) then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

			if pInventory ~= nil then
				local pDatapad = giveItem(pInventory, "object/tangible/loot/misc/damaged_datapad.iff", -1)

				if (pDatapad == nil) then
					return 0
				end

				SceneObject(pDatapad):setCustomObjectName("A Datapad")

				ghost:completeJournalQuestTask(QuestManager.questCRC.QUEST_LF_SAFETY4, 0, true)
				ghost:activateJournalQuestTask(QuestManager.questCRC.QUEST_LF_SAFETY4, 1, true)

				self:removeWaypoint(pPlayer, 1)

				return 1
			end
		end

		return 0
	elseif (ghost:isJournalQuestActive(QuestManager.questCRC.QUEST_LF_SAFETY5) and string.find(victimName, "brigand_leader")) then
		ghost:completeJournalQuestTask(QuestManager.questCRC.QUEST_LF_SAFETY5, 0, true)
		ghost:activateJournalQuestTask(QuestManager.questCRC.QUEST_LF_SAFETY5, 1, true)

		self:removeWaypoint(pPlayer, 1)

		return 1
	end

	return 0
end

function SafetyMeasures:onDespawn(pMobile)
	if pMobile == nil or not SceneObject(pMobile):isAiAgent() then
		return
	end

	local mobID = SceneObject(pMobile):getObjectID()
	local mobNum = readData(mobID .. ":SafetyMeasures:mobID:")

	createEvent(300 * 1000, "SafetyMeasures", "respawn", nil, mobNum)

	deleteData(mobID .. ":SafetyMeasures:mobID:")

	return 1
end
