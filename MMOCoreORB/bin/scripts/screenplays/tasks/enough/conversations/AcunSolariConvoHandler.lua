AcunSolariConvoHandler = conv_handler:new {}

function AcunSolariConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pScreenClone = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pScreenClone)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ghost = LuaPlayerObject(pGhost)
	local playerID = SceneObject(pPlayer):getObjectID()

	local pEnoughTasks = getQuestTasks(EnoughQuest.REBEL_CRC)

	if pEnoughTasks == nil then
		Logger:log("ERROR: Could not load EnoughQuest Tasks.", LT_ERROR)
		return 0
	end

	local enoughTasks = LuaQuestTasks(pEnoughTasks)

	if (screenID == "response_deny") then
		CreatureObject(pPlayer):doAnimation("shrug_shoulders")
		CreatureObject(pNpc):doAnimation("shake_head_disgust")
	elseif (screenID == "response_1") then
		CreatureObject(pNpc):doAnimation("point_up")
	elseif (screenID == "response_start") then
		CreatureObject(pPlayer):doAnimation("salute1")
		CreatureObject(pNpc):doAnimation("salute1")

		-- Waypoint to Pilot
		local waypointID = ghost:addWaypoint("corellia", "Escape Pod Crash Site", "Escape Pod Crash Site", -5463, -930, WAYPOINTYELLOW, true, true, EnoughQuest.REBEL_CRC)
		writeScreenPlayData(pPlayer, "EnoughQuest", "PilotWaypointID", waypointID)

		-- Waypoint to quest giver
		waypointID = ghost:addWaypoint("corellia", "Acun Solari", "Acun Solari", -5200, -2575, WAYPOINTYELLOW, true, true, EnoughQuest.REBEL_CRC)
		writeScreenPlayData(pPlayer, "EnoughQuest", "QuestGiverWaypointID", waypointID)

		ghost:activateJournalQuest(EnoughQuest.REBEL_CRC, true)
	elseif (screenID == "new_waypoint") then
		CreatureObject(pNpc):doAnimation("sigh_deeply")

		-- Waypoint to Pilot
		local waypointID = ghost:addWaypoint("corellia", "Escape Pod Crash Site", "Escape Pod Crash Site", -5463, -930, WAYPOINTYELLOW, true, true, EnoughQuest.REBEL_CRC)
		writeScreenPlayData(pPlayer, "EnoughQuest", "PilotWaypointID", waypointID)

	-- Give reward if the player has not yet received it
	elseif (screenID == "no_pilot" and EnoughQuest:activeTask(ghost, EnoughQuest.REBEL_CRC, EnoughQuest.WAIT_FOR_SIGNAL1)) then
		ghost:completeJournalQuestTask(EnoughQuest.REBEL_CRC, EnoughQuest.WAIT_FOR_SIGNAL1, true)
		ghost:activateJournalQuestTask(EnoughQuest.REBEL_CRC, EnoughQuest.REWARD1, true)

		local pQuestTask = enoughTasks:getTask(EnoughQuest.REWARD1)

		if (pQuestTask == nil) then
			Logger:log("ERROR: Could not load Enough Quest Task - REWARD1.", LT_ERROR)
			return 0
		end

		local questTask = LuaQuestTask(pQuestTask)
		local faction = string.lower(questTask:getFactionName())

		-- Give reward
		ghost:increaseFactionStanding(faction, questTask:getFactionAmount())

		local creditsAmount = questTask:getBankCredits()
		CreatureObject(pPlayer):addBankCredits(creditsAmount, true)

		CreatureObject(pPlayer):sendSystemMessage("You recieve " .. creditsAmount .. " credits for completing your task.")
	elseif (screenID == "help_accept") then
		-- Waypoint to Flail Camp
		local waypointID = ghost:addWaypoint("corellia", "Flail Camp", "Flail Camp", -4737, -1519, WAYPOINTYELLOW, true, true, EnoughQuest.REBEL_CRC)
		writeScreenPlayData(pPlayer, "EnoughQuest", "KilllWaypointID", waypointID)

		-- Waypoint to Binayre Camp
		waypointID = ghost:addWaypoint("talus", "Binayre Camp", "Binayre Camp", -1622, 618, WAYPOINTYELLOW, true, true, EnoughQuest.REBEL_CRC)
		writeScreenPlayData(pPlayer, "EnoughQuest", "BinayreWaypointID", waypointID)

		ghost:completeJournalQuestTask(EnoughQuest.REBEL_CRC, EnoughQuest.REWARD1, true)
		ghost:activateJournalQuestTask(EnoughQuest.REBEL_CRC, EnoughQuest.DESTROY_MULTI, true)

		-- Add observer to player to track the Flail kills
		createObserver(KILLEDCREATURE, "EnoughQuest", "notifyKilledCreature", pPlayer, 1)
	elseif (screenID == "ground_kill") then
		local flailCount = getQuestStatus(playerID .. ":EnoughQuest:DestroyMultiCount:")
		local gangSymbols = getQuestStatus(playerID .. ":EnoughQuest:DestroyMultiLootCount:")

		if (flailCount == nil) then
			flailCount = 0
		else
			flailCount = tonumber(flailCount)
		end

		if (gangSymbols == nil) then
			gangSymbols = 0
		else
			gangSymbols = tonumber(gangSymbols)
		end

		local pTaskFlails = enoughTasks:getTask(EnoughQuest.DESTROY_MULTI)
		local pTaskBinayre = enoughTasks:getTask(EnoughQuest.DESTROY_MULTI_AND_LOOT)

		if (pTaskFlails == nil or pTaskBinayre == nil) then
			Logger:log("ERROR: Could not load Enough Quest Task - REWARD1.", LT_ERROR)
			return 0
		end

		local flailTask = LuaQuestTask(pTaskFlails)
		local binayreTask = LuaQuestTask(pTaskBinayre)

		-- Player has killed flails and looted all binayre gang symbols
		if (flailCount >= flailTask:getCount() and gangSymbols >= binayreTask:getLootItemsRequired()) then
			clonedConversation:addOption("@conversation/c_sink_reb:s_1180", "ground_finished") -- I have the marks and you have heard about the Flails, I assume.
		elseif (flailCount > 0 or gangSymbols > 0 ) then -- Some or all killed but still needs more loot binayre gang symbols
			clonedConversation:addOption("@conversation/c_sink_reb:s_1176", "ground_progress") -- I'm still working my way through the bad guys.
		else
			-- No flails killed and no looted Bynayre gang symbols
			clonedConversation:addOption("@conversation/c_sink_reb:s_1172", "ground_failing") -- I haven't started yet.
		end
	elseif (screenID == "ground_finished") then
		ghost:completeJournalQuestTask(EnoughQuest.REBEL_CRC, EnoughQuest.WAIT_FOR_SIGNAL2, true)
		ghost:activateJournalQuestTask(EnoughQuest.REBEL_CRC, EnoughQuest.WAIT_FOR_SIGNAL3, true)

		-- Remove quest statuses
		removeQuestStatus(playerID .. ":EnoughQuest:DestroyMultiCount:")
		removeQuestStatus(playerID .. ":EnoughQuest:DestroyMultiLootCount:")

		-- Here the ground quest portion is finished. Players will not be able to finish until JTL is further in development.
		if (EnoughQuest.ENABLE_SPACE) then
			clonedConversation:addOption("@conversation/c_sink_reb:s_1184", "space_start") -- I'd like to do more to help.
		else
			clonedConversation:addOption("@conversation/c_sink_reb:s_1184", "space_wait") -- I am happy to do my part.
		end
	elseif (screenID == "space_start") then
		-- Add space kill Observer here
		-- Ensure original waypoint to quest giver is removed upon completion readScreenPlayData(pPlayer, "EnoughQuest", "QuestGiverWaypointID")
	end

	return pScreenClone
end

function AcunSolariConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil) then
		return
	end

	local faction = CreatureObject(pPlayer):getFaction()

	if (faction == FACTIONIMPERIAL) then
		return convoTemplate:getScreen("imperial_greeting")
	elseif (faction == FACTIONNEUTRAL) then
		return convoTemplate:getScreen("neutral_greeting")
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ghost = LuaPlayerObject(pGhost)

	if not PlayerObject(pGhost):isJournalQuestActive(EnoughQuest.REBEL_CRC) then
		return convoTemplate:getScreen("rebel_greeting")
	elseif EnoughQuest:activeTask(ghost, EnoughQuest.REBEL_CRC, EnoughQuest.GO_TO_LOCATION) then
		return convoTemplate:getScreen("where_friend")
	elseif EnoughQuest:activeTask(ghost, EnoughQuest.REBEL_CRC, EnoughQuest.WAIT_FOR_SIGNAL1) or EnoughQuest:activeTask(ghost, EnoughQuest.REBEL_CRC, EnoughQuest.REWARD1) then
		return convoTemplate:getScreen("no_pilot")
	elseif EnoughQuest:activeTask(ghost, EnoughQuest.REBEL_CRC, EnoughQuest.DESTROY_MULTI) or
		EnoughQuest:activeTask(ghost, EnoughQuest.REBEL_CRC, EnoughQuest.DESTROY_MULTI_AND_LOOT) or
		EnoughQuest:activeTask(ghost, EnoughQuest.REBEL_CRC, EnoughQuest.WAIT_FOR_SIGNAL2) then

		return convoTemplate:getScreen("ground_kill")
	elseif EnoughQuest:activeTask(ghost, EnoughQuest.REBEL_CRC, EnoughQuest.WAIT_FOR_SIGNAL3) then
		if not EnoughQuest.ENABLE_SPACE then
			return convoTemplate:getScreen("space_wait")
		end

		return convoTemplate:getScreen("space_start")
	end

	return convoTemplate:getScreen("neutral_greeting")
end