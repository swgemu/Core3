local QuestManager = require("managers.quest.quest_manager")
local Logger = require("utils.logger")

local Syren = {}
Syren.act1 = {}
Syren.act1.IMPERIAL_CRC = QuestManager.questCRC.QUEST_C_STORY1_1_IMP
Syren.act1.NEUTRAL_CRC = QuestManager.questCRC.QUEST_C_STORY1_1_NEU
Syren.act1.REBEL_CRC = QuestManager.questCRC.QUEST_C_STORY1_1_REB
Syren.act1.LOOK_FOR_PILOT = 0
Syren.act1.CRASH_SITE_FOUND = 1
Syren.act1.FOUND_DATAPAD = 2
Syren.act1.TALK_TO_CONTACT = 3
Syren.act1.TALK_TO_DOCTOR = 4
Syren.act1.TALK_TO_MOXXAR = 5
Syren.act1.SECOND_DATAPAD = 6
Syren.act1.RETURN_TO_CONTACT = 7
Syren.act1.SPICE_FOUND = 8
Syren.act2 = {}
Syren.act2.IMPERIAL_CRC = QuestManager.questCRC.QUEST_C_STORY1_2_IMP
Syren.act2.NEUTRAL_CRC = QuestManager.questCRC.QUEST_C_STORY1_2_NEU
Syren.act2.REBEL_CRC = QuestManager.questCRC.QUEST_C_STORY1_2_REB
Syren.act2.TALK_TO_KAILA = 0
Syren.act2.GO_TO_AMBUSH = 1
Syren.act2.AMBUSH_1 = 2
Syren.act2.AMBUSH_2 = 3
Syren.act2.AMBUSH_3 = 4
Syren.act2.AMBUSH_COMPLETE = 5
Syren.act2.GO_TO_BASE = 6
Syren.act2.TALK_TO_TOVAR = 7
Syren.act2.REWARD = 8
Syren.act2.CLIFFHANGER = 9
Syren.act2.FAILED_AMBUSH_3 = 10
Syren.act2.FAILED_AMBUSH_2 = 11
Syren.act2.FAILED_AMBUSH_1 = 12

SecretsOfTheSyren = ScreenPlay:new {
	SCREEN_PLAY_NAME = "secrets_of_the_syren",

	className = "SecretsOfTheSyren",
	staticNpcs = {
		{"syren_veega_madish", "corellia", -5203, 21, -2572, 180, 0},
		{"syren_tyla_jinn", "naboo", 6.4, -0.9, -6.5, 50, 91},
		{"syren_jevan_monsul", "tatooine", 7, -0.9, -5, 50, 1028647},
		{"syren_edvar_vang", "rori", -22, 0, -10, 0, 4635424},
		{"syren_kaila_min", "rori", 22.3, 1.3, 10.6, 180, 4635594},
		{"syren_tovar_blackmoor", "rori", 48, -20, 157.5, 180, 3566235}
	},
}

registerScreenPlay("SecretsOfTheSyren", true)

function SecretsOfTheSyren:start()
	self:spawnStaticNpcs()
	self:spawnActiveAreas(Syren.act1.REBEL_CRC)
	self:spawnActiveAreas(Syren.act1.IMPERIAL_CRC)
	self:spawnActiveAreas(Syren.act1.NEUTRAL_CRC)
	self:spawnActiveAreas(Syren.act2.REBEL_CRC)
	self:spawnActiveAreas(Syren.act2.IMPERIAL_CRC)
	self:spawnActiveAreas(Syren.act2.NEUTRAL_CRC)
end

function SecretsOfTheSyren:spawnStaticNpcs()
	for i = 1, # self.staticNpcs do
		local npc = self.staticNpcs[i]
		if isZoneEnabled(npc[2]) then
			spawnMobile(npc[2], npc[1], 0, npc[3], npc[4], npc[5], npc[6], npc[7])
		end
	end
end

function SecretsOfTheSyren:spawnActiveAreas(questCrc)
	local pSyrenTasks = getQuestTasks(questCrc)

	if pSyrenTasks == nil then
		Logger:log("ERROR: Could not load Secrets of the Syren correctly. Quest line will not function correctly.", LT_ERROR)
		return
	end

	local syrenTasks = LuaQuestTasks(pSyrenTasks)

	for taskIndex = 0, syrenTasks:getNumberOfTasks() - 1 do
		local pQuestTask = syrenTasks:getTask(taskIndex)

		if pQuestTask == nil then
			Logger:log("Secrets of the Syren: pQuestTask is nil", LT_ERROR)
			return
		end

		local questTask = LuaQuestTask(pQuestTask)

		if questTask:getAttachScript() == "quest.task.ground.go_to_location" then
			if isZoneEnabled(questTask:getPlanetName()) then
				local cellid = 0
				if questTask:getPlanetName() == "tatooine" then
					cellid = 1498879
				end
				local pQuestArea = spawnActiveArea(questTask:getPlanetName(), "object/active_area.iff", questTask:getLocationX(), questTask:getLocationY(), questTask:getLocationZ(), questTask:getRadius(), cellid)

				if pQuestArea == nil then
					Logger:log("Secrets of the Syren: pQuestArea is nil.", LT_ERROR)
					return
				end

				ActiveArea(pQuestArea):setNoBuildArea(true)
				ActiveArea(pQuestArea):setNoSpawnArea(true)

				createObserver(ENTEREDAREA, self.className, "notifyEnteredQuestArea", pQuestArea)
				local questAreaID = SceneObject(pQuestArea):getObjectID()
				writeData(questAreaID .. ":questCrc", questCrc)
				writeData(questAreaID .. ":taskIndex", taskIndex)
			else
				Logger:log(questTask:getPlanetName() .. "is not loaded. Could not load Secrets of the Syren. Quest line will not function correctly", LT_ERROR)
			end
		end
	end
end

function SecretsOfTheSyren:notifyEnteredQuestArea(pActiveArea, pPlayer)
	if (pActiveArea == nil) or (pPlayer == nil) or (not SceneObject(pActiveArea):isActiveArea()) or
		(not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end

	local activeAreaID = SceneObject(pActiveArea):getObjectID()
	local questCrc = readData(activeAreaID .. ":questCrc")
	local taskIndex = readData(activeAreaID .. ":taskIndex")
	local creature = LuaCreatureObject(pPlayer)
	local pGhost = creature:getPlayerObject()
	if pGhost ~= nil then
		local ghost = LuaPlayerObject(pGhost)
		if self:activeTask(ghost, questCrc, taskIndex) then
			ghost:completeJournalQuestTask(questCrc, taskIndex, true)
			ghost:activateJournalQuestTask(questCrc, taskIndex + 1, true)
			if taskIndex == Syren.act1.CRASH_SITE_FOUND and self:act1(questCrc) then
				ghost:activateJournalQuestTask(questCrc, Syren.act1.FOUND_DATAPAD, true)
				ghost:completeJournalQuestTask(questCrc, Syren.act1.FOUND_DATAPAD, true)
				ghost:activateJournalQuestTask(questCrc, Syren.act1.SPICE_FOUND, true)
				ghost:completeJournalQuestTask(questCrc, Syren.act1.SPICE_FOUND, true)
				ghost:activateJournalQuestTask(questCrc, Syren.act1.TALK_TO_CONTACT, true)
				self:giveItems(pPlayer, taskIndex, questCrc)
				self:returnToContactWaypoint(questCrc, pPlayer, ghost)
			elseif taskIndex == Syren.act1.TALK_TO_MOXXAR and self:act1(questCrc)  then
				ghost:activateJournalQuestTask(questCrc, Syren.act1.SECOND_DATAPAD, true)
				ghost:completeJournalQuestTask(questCrc, Syren.act1.SECOND_DATAPAD, true)
				ghost:activateJournalQuestTask(questCrc, Syren.act1.RETURN_TO_CONTACT, true)
				self:giveItems(pPlayer, taskIndex, questCrc)
				self:returnToContactWaypoint(questCrc, pPlayer, ghost)
			elseif taskIndex == Syren.act2.GO_TO_AMBUSH and self:act2(questCrc)  then
				self:startAmbush(questCrc, pPlayer, creature, ghost)
			elseif taskIndex == Syren.act2.GO_TO_BASE and self:act2(questCrc)  then
				ghost:completeJournalQuestTask(questCrc, Syren.act2.GO_TO_BASE, true)
				ghost:activateJournalQuestTask(questCrc, Syren.act2.TALK_TO_TOVAR, true)
			end
		end
	end
	return 0
end

function SecretsOfTheSyren:startAmbush(questCrc, pPlayer, creature, ghost)
	local pSyrenTasks = getQuestTasks(questCrc)

	if pSyrenTasks == nil then
		Logger:log("ERROR: Could not load Secrets of the Syren correctly. Quest line will not function correctly.", LT_ERROR)
		return
	end

	local syrenTasks = LuaQuestTasks(pSyrenTasks)

	if self:activeTask(ghost, questCrc, Syren.act2.AMBUSH_1) then
		self:spawnAmbushNpcs(pPlayer, creature, syrenTasks:getTask(Syren.act2.AMBUSH_1), questCrc)
	elseif self:activeTask(ghost, questCrc, Syren.act2.AMBUSH_2) then
		self:spawnAmbushNpcs(pPlayer, creature, syrenTasks:getTask(Syren.act2.AMBUSH_2), questCrc)
	elseif self:activeTask(ghost, questCrc, Syren.act2.AMBUSH_3) then
		self:spawnAmbushNpcs(pPlayer, creature, syrenTasks:getTask(Syren.act2.AMBUSH_3), questCrc)
	end

	creature:sendSystemMessage("You have been ambushed!")
end

function SecretsOfTheSyren:spawnAmbushNpcs(pPlayer, creature, pQuestTask, questCrc)
	if pQuestTask == nil then
		Logger:log("ERROR: Could not load Secrets of the Syren correctly. Quest line will not function correctly.", LT_ERROR)
		return
	end

	local questTask = LuaQuestTask(pQuestTask)
	local playerID = creature:getObjectID()
	writeData(playerID .. ":ambushNpcs", questTask:getCount())
	writeData(playerID .. ":questCrc", questCrc)
	createObserver(OBJECTDESTRUCTION, self.className, "notifyPlayerKilled", pPlayer)

	for i = 1, questTask:getCount() do
		local spawnPoint = getSpawnPoint("rori", creature:getWorldPositionX(), creature:getWorldPositionY(), questTask:getMinDistance(), questTask:getMaxDistance(), true)
		if spawnPoint == nil then
			Logger:log("ERROR: Could not load Secrets of the Syren correctly. Quest line will not function correctly.", LT_ERROR)
			return
		else
			local pNpc = spawnMobile("rori", questTask:getCreatureType(), 0, spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, 0)
			if pNpc == nil then
				Logger:log("ERROR: Could not load Secrets of the Syren correctly. Quest line will not function correctly.", LT_ERROR)
				return
			else
				local aiAgent = LuaAiAgent(pNpc)
				local npcID = aiAgent:getObjectID()
				writeData(playerID .. ":ambushNpc" .. i, npcID)
				writeData(npcID .. ":playerID", playerID)
				writeData(npcID .. ":npcNo", i)
				createObserver(OBJECTDESTRUCTION, self.className, "notifyDefeatedTarget", pNpc)

				aiAgent:setDefender(pPlayer)
			end
		end
	end
end

function SecretsOfTheSyren:notifyDefeatedTarget(pVictim, pAttacker)
	if (pVictim == nil) or (pAttacker == nil) or (not SceneObject(pVictim):isCreatureObject()) or (not SceneObject(pAttacker):isCreatureObject()) then
		return 0
	end

	local victimID = CreatureObject(pVictim):getObjectID()
	local attackerID = CreatureObject(pAttacker):getObjectID()
	local npcNo = readData(victimID .. ":npcNo")
	local playerID = readData(victimID .. ":playerID")

	if npcNo ~= 0 and playerID ~= 0 then
		writeData(playerID .. ":ambushNpc" .. npcNo, 0)
		self:allAmbushNpcsKilled(attackerID)
	end

	return 1
end

function SecretsOfTheSyren:allAmbushNpcsKilled(playerID)
	local numberOfNpcs = readData(playerID .. ":ambushNpcs")
	local questCrc = readData(playerID .. ":questCrc")
	local pSyrenTasks = getQuestTasks(questCrc)

	if pSyrenTasks == nil then
		Logger:log("ERROR: Could not load Secrets of the Syren correctly. Quest line will not function correctly.", LT_ERROR)
		return
	end

	local syrenTasks = LuaQuestTasks(pSyrenTasks)

	local npcsLeft = 0
	for i = 1, numberOfNpcs do
		local npcID = readData(playerID .. ":ambushNpc" .. i)
		if npcID ~= 0 then
			npcsLeft = npcsLeft + 1
		end
	end
	if npcsLeft == 0 then
		local pPlayer = getCreatureObject(playerID)
		if pPlayer ~= nil then
			dropObserver(OBJECTDESTRUCTION, pPlayer)
			local creature = LuaCreatureObject(pPlayer)
			local pGhost = creature:getPlayerObject()
			if pGhost ~= nil then
				local ghost = LuaPlayerObject(pGhost)
				if self:activeTask(ghost, questCrc, Syren.act2.AMBUSH_3) then
					ghost:completeJournalQuestTask(questCrc, Syren.act2.AMBUSH_1, true)
					ghost:completeJournalQuestTask(questCrc, Syren.act2.AMBUSH_3, false)
					ghost:activateJournalQuestTask(questCrc, Syren.act2.AMBUSH_COMPLETE, true)
					ghost:completeJournalQuestTask(questCrc, Syren.act2.AMBUSH_COMPLETE, true)
					ghost:activateJournalQuestTask(questCrc, Syren.act2.GO_TO_BASE, true)
					self:giveItems(pPlayer, Syren.act2.AMBUSH_COMPLETE, questCrc)
					self:updateWaypoint(pPlayer, ghost, "rori", "Go to the location found on the datapad", 4846, -1084)
				elseif self:activeTask(ghost, questCrc, Syren.act2.AMBUSH_2) then
					ghost:completeJournalQuestTask(questCrc, Syren.act2.AMBUSH_2, false)
					ghost:activateJournalQuestTask(questCrc, Syren.act2.AMBUSH_3, false)
					self:spawnAmbushNpcs(pPlayer, creature, syrenTasks:getTask(Syren.act2.AMBUSH_3), questCrc)
				elseif self:activeTask(ghost, questCrc, Syren.act2.AMBUSH_1) then
					ghost:activateJournalQuestTask(questCrc, Syren.act2.AMBUSH_2, false)
					self:spawnAmbushNpcs(pPlayer, creature, syrenTasks:getTask(Syren.act2.AMBUSH_2), questCrc)
				else
					Logger:log("### No task active: " .. questCrc .. "", LT_ERROR)
				end
			else
				Logger:log("### pGhost is nil", LT_ERROR)
			end
		else
			Logger:log("### pPlayer is nil", LT_ERROR)
		end
	end
end

function SecretsOfTheSyren:notifyPlayerKilled(pVictim, pAttacker)
	if (pVictim == nil) or (pAttacker == nil) or (not SceneObject(pVictim):isCreatureObject()) or (not SceneObject(pAttacker):isCreatureObject()) then
		return 0
	end

	local victimID = CreatureObject(pVictim):getObjectID()
	local attackerID = CreatureObject(pAttacker):getObjectID()

	if victimID ~= 0 and attackerID ~= 0 then
		if self:playerKilledByAmbushNpc(victimID, attackerID) then
			self:failAmbush(victimID)
			return 1
		end
	end

	return 0
end

function SecretsOfTheSyren:playerKilledByAmbushNpc(victimID, attackerID)
	if (victimID == 0) or (attackerID == 0) then
		return false
	end

	local numberOfNpcs = readData(victimID .. ":ambushNpcs")

	for i = 1, numberOfNpcs do
		local npcID = readData(victimID .. ":ambushNpc" .. i)

		if npcID == attackerID then
			return true;
		end
	end

	return false
end

function SecretsOfTheSyren:failAmbush(playerID)
	local pPlayer = getCreatureObject(playerID)
	SceneObject(pPlayer):addPendingTask((60 * 1000), "SecretsOfTheSyren", "despawnAmbushNpcs")
	if pPlayer ~= nil then
		local player = LuaCreatureObject(pPlayer)
		local pGhost = player:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)

			if self:activeTask(ghost, questCrc, Syren.act2.AMBUSH_1) then
				ghost:activateJournalQuestTask(questCrc, Syren.act2.FAILED_AMBUSH_1, true)
				ghost:completeJournalQuestTask(questCrc, Syren.act2.FAILED_AMBUSH_1, true)
			elseif self:activeTask(ghost, questCrc, Syren.act2.AMBUSH_2) then
				ghost:activateJournalQuestTask(questCrc, Syren.act2.FAILED_AMBUSH_2, true)
				ghost:completeJournalQuestTask(questCrc, Syren.act2.FAILED_AMBUSH_2, true)
			elseif self:activeTask(ghost, questCrc, Syren.act2.AMBUSH_3) then
				ghost:activateJournalQuestTask(questCrc, Syren.act2.FAILED_AMBUSH_3, true)
				ghost:completeJournalQuestTask(questCrc, Syren.act2.FAILED_AMBUSH_3, true)
			end
			ghost:clearJournalQuestTask(questCrc, Syren.act2.TALK_TO_KAILA, true)
			ghost:clearJournalQuestTask(questCrc, Syren.act2.GO_TO_AMBUSH, true)
			ghost:clearJournalQuestTask(questCrc, Syren.act2.AMBUSH_2, true)
			ghost:clearJournalQuestTask(questCrc, Syren.act2.AMBUSH_3, true)
			ghost:clearJournalQuestTask(questCrc, Syren.act2.AMBUSH_3, true)
			ghost:activateJournalQuestTask(questCrc, Syren.act2.TALK_TO_KAILA, true)
		end
	end
end

function SecretsOfTheSyren:despawnAmbushNpcs(pPlayer)
	if pPlayer ~= nil then
		local player = LuaCreatureObject(pPlayer)
		local playerID = player:getObjectID()

		local numberOfNpcs = readData(playerID .. ":ambushNpcs")
		for i = 1, numberOfNpcs do
			local npcID = readData(playerID .. ":ambushNpc" .. i)
			if npcID ~= 0 then
				local pNpc = getCreatureObject(npcID)

				if (pNpc ~= nil) then
					local npc = LuaCreatureObject(pNpc)
					npc:destroyObjectFromWorld()
					deleteData(playerID .. ":ambushNpc" .. i)
				end
			end
		end
	end
end

function SecretsOfTheSyren:act1(questCrc)
	return questCrc == Syren.act1.IMPERIAL_CRC or questCrc == Syren.act1.NEUTRAL_CRC or questCrc == Syren.act1.REBEL_CRC
end

function SecretsOfTheSyren:act2(questCrc)
	return questCrc == Syren.act2.IMPERIAL_CRC or questCrc == Syren.act2.NEUTRAL_CRC or questCrc == Syren.act2.REBEL_CRC
end

function SecretsOfTheSyren:giveItems(pPlayer, taskIndex, questCrc)
	local creature = LuaCreatureObject(pPlayer)
	local pInventory = creature:getSlottedObject("inventory")
	if pInventory == nil then
		printLuaError("Unable to giveItems in SecretsOfTheSyren to player " .. creature:getObjectID())
		return
	end

	if taskIndex == Syren.act1.CRASH_SITE_FOUND then
		local pItem = giveItem(pInventory, "object/tangible/mission/quest_item/syren1_locked_data.iff", -1, true)
		if pItem == nil then
			printLuaError("Unable to give syren1_locked_data in SecretsOfTheSyren to player " .. creature:getObjectID())
		end
		local pItem = giveItem(pInventory, "object/tangible/mission/quest_item/syren1_spice.iff", -1, true)
		if pItem == nil then
			printLuaError("Unable to give syren1_spice in SecretsOfTheSyren to player " .. creature:getObjectID())
		end
	elseif taskIndex == Syren.act1.TALK_TO_MOXXAR and self:act1(questCrc) then
		local pItem = giveItem(pInventory, "object/tangible/mission/quest_item/syren1_warning.iff", -1, true)
		if pItem == nil then
			printLuaError("Unable to give syren1_warning in SecretsOfTheSyren to player " .. creature:getObjectID())
		end
	elseif taskIndex == Syren.act2.AMBUSH_COMPLETE and self:act2(questCrc) then
		local pItem = giveItem(pInventory, "object/tangible/mission/quest_item/syren2_blacksun_base.iff", -1, true)
		if pItem == nil then
			printLuaError("Unable to give syren1_warning in SecretsOfTheSyren to player " .. creature:getObjectID())
		end
	elseif taskIndex == Syren.act2.REWARD then
		local pItem = giveItem(pInventory, "object/tangible/loot/loot_schematic/shisa_schematic.iff", -1, true)
		if pItem == nil then
			printLuaError("Unable to give syren1_warning in SecretsOfTheSyren to player " .. creature:getObjectID())
		end
		creature:addCashCredits(5000, true)
		creature:sendSystemMessage("Tovar Blackmoor gave you 5000 credits and a Shisha schematic.")
		local faction = creature:getFaction()
		if faction == FACTIONREBEL or faction == FACTIONIMPERIAL then
			local pGhost = creature:getPlayerObject()
			if pGhost == nil then
				printLuaError("Unable to give faction points to player " .. creature:getObjectID())
			else
				local ghost = LuaPlayerObject(pGhost)
				ghost:increaseFactionStanding(creature:getFaction(), 100)
			end
		end
	end
end

function SecretsOfTheSyren:returnToContactWaypoint(questCrc, pPlayer, ghost)
	if questCrc == Syren.act1.REBEL_CRC then
		self:updateWaypoint(pPlayer, ghost, "corellia", "Return to your contact", -5203, -2572)
	elseif questCrc == Syren.act1.IMPERIAL_CRC then
		self:updateWaypoint(pPlayer, ghost, "tatooine", "Return to your contact", -1399, -3675)
	elseif questCrc == Syren.act1.NEUTRAL_CRC then
		self:updateWaypoint(pPlayer, ghost, "naboo", "Return to your contact", -5181, 4258)
	end
end

function SecretsOfTheSyren:updateWaypoint(pPlayer, ghost, planet, text, x, y)
	local playerID = SceneObject(pPlayer):getObjectID()
	local previousWaypointID = readData(playerID .. ":syrent:waypointID")
	if previousWaypointID ~= nil then
		ghost:removeWaypoint(previousWaypointID, true)
	end
	local waypointID = ghost:addWaypoint(planet, text, "", x, y, WAYPOINTPURPLE, true, true, WAYPOINTQUESTTASK, 0)
	writeData(playerID .. ":syrent:waypointID", waypointID)
end

function SecretsOfTheSyren:activeTask(ghost, questCrc, taskIndex)
	return ghost:isJournalQuestActive(questCrc) and ghost:isJournalQuestTaskActive(questCrc, taskIndex) and
			   not ghost:isJournalQuestComplete(questCrc) and not ghost:isJournalQuestTaskComplete(questCrc, taskIndex)
end

function SecretsOfTheSyren:acceptQuestLookingForPilot(pPlayer, questCrc)
	if pPlayer ~= nil and SceneObject(pPlayer):isPlayerCreature() then
		local creature = LuaCreatureObject(pPlayer)
		local pGhost = creature:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)
			ghost:activateJournalQuest(questCrc, true)
			ghost:activateJournalQuestTask(questCrc, Syren.act1.LOOK_FOR_PILOT, true)
			self:updateWaypoint(pPlayer, ghost, "rori", "Search for the pilot", 0, 2012)
		end
	end
end

function SecretsOfTheSyren:acceptQuestTalkToDoctor(pPlayer, questCrc)
	if pPlayer ~= nil and SceneObject(pPlayer):isPlayerCreature() then
		local creature = LuaCreatureObject(pPlayer)
		local pGhost = creature:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)
			ghost:completeJournalQuestTask(questCrc, Syren.act1.TALK_TO_CONTACT, true)
			ghost:activateJournalQuestTask(questCrc, Syren.act1.TALK_TO_DOCTOR, true)
			self:updateWaypoint(pPlayer, ghost, "rori", "Talk to Dr. Vang", -5108, -2202)
		end
	end
end

function SecretsOfTheSyren:acceptQuestLookingForMoxxar(pPlayer, questCrc)
	if pPlayer ~= nil and SceneObject(pPlayer):isPlayerCreature() then
		local creature = LuaCreatureObject(pPlayer)
		local pGhost = creature:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)
			ghost:completeJournalQuestTask(questCrc, Syren.act1.TALK_TO_DOCTOR, true)
			ghost:activateJournalQuestTask(questCrc, Syren.act1.TALK_TO_MOXXAR, true)
			self:updateWaypoint(pPlayer, ghost, "tatooine", "Talk to Moxxar Krieg", 3292, -4542)
		end
	end
end

function SecretsOfTheSyren:acceptQuestGoToAmbush(pPlayer, questCrc)
	if pPlayer ~= nil and SceneObject(pPlayer):isPlayerCreature() then
		local creature = LuaCreatureObject(pPlayer)
		local pGhost = creature:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)
			ghost:completeJournalQuestTask(questCrc, Syren.act2.TALK_TO_KAILA, true)
			ghost:activateJournalQuestTask(questCrc, Syren.act2.GO_TO_AMBUSH, true)
			self:updateWaypoint(pPlayer, ghost, "rori", "Pirates Last Known Location", -2970, 947)
		end
	end
end

function SecretsOfTheSyren:getReward(pPlayer, questCrc)
	if pPlayer ~= nil and SceneObject(pPlayer):isPlayerCreature() then
		local creature = LuaCreatureObject(pPlayer)
		local pGhost = creature:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)
			ghost:completeJournalQuestTask(questCrc, Syren.act2.TALK_TO_TOVAR, true)
			ghost:activateJournalQuestTask(questCrc, Syren.act2.REWARD, true)
			ghost:completeJournalQuestTask(questCrc, Syren.act2.REWARD, true)
			ghost:activateJournalQuestTask(questCrc, Syren.act2.CLIFFHANGER, true)
			ghost:completeJournalQuestTask(questCrc, Syren.act2.CLIFFHANGER, true)
			ghost:completeJournalQuest(questCrc, true)
			self:giveItems(pPlayer, Syren.act2.REWARD, questCrc)
		end
	end
end

function SecretsOfTheSyren:finishAct1(pPlayer, questCrc)
	if pPlayer ~= nil and SceneObject(pPlayer):isPlayerCreature() then
		local creature = LuaCreatureObject(pPlayer)
		local pGhost = creature:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)
			ghost:completeJournalQuestTask(questCrc, Syren.act1.RETURN_TO_CONTACT, true)
			ghost:completeJournalQuest(questCrc, true)
		end
	end
end

function SecretsOfTheSyren:acceptQuestGoToKailaMin(pPlayer, questCrc)
	if pPlayer ~= nil and SceneObject(pPlayer):isPlayerCreature() then
		local creature = LuaCreatureObject(pPlayer)
		local pGhost = creature:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)
			ghost:activateJournalQuest(questCrc, true)
			ghost:activateJournalQuestTask(questCrc, Syren.act2.TALK_TO_KAILA, true)
			self:updateWaypoint(pPlayer, ghost, "rori", "Talk to Kaila Min", -5264, -2290)
		end
	end
end

return Syren