ImperialDefectorConvoHandler = conv_handler:new {
	debugNotify = true, -- Send system messages for testing
}

function ImperialDefectorConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pScreenClone = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pScreenClone)
	local questCrc = DefectorQuest.IMPERIAL_CRC

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ghost = LuaPlayerObject(pGhost)
	local playerID = SceneObject(pPlayer):getObjectID()

	local pDefectorTasks = getQuestTasks(questCrc)

	if pDefectorTasks == nil then
		Logger:log("ERROR: Could not load DefectorQuest Tasks.", LT_ERROR)
		return 0
	end

	local defectorTasks = LuaQuestTasks(pDefectorTasks)

	if (screenID == "active_greeting") then
		ghost:completeJournalQuestTask(questCrc, DefectorQuest.WAIT_FOR_SIGNAL1, true)

	elseif (screenID == "response_start") then

		-- Waypoint to quest receiver
		local waypointID = ghost:addWaypoint("corellia", "Bring the Imperial defector's codephrase to Teslo Ten'doora in the Rebel Base.", "Bring the Imperial defector's codephrase to Teslo Ten'doora in the Rebel Base.", -6485, 6017, WAYPOINTYELLOW, true, true, questCrc)
		writeScreenPlayData(pPlayer, "DefectorQuest", "impQuestReceiverWaypointID", waypointID)

		local waypoints = {tonumber(readScreenPlayData(pPlayer, "DefectorQuest", "impQuestGiverWaypointID")), tonumber(readScreenPlayData(pPlayer, "DefectorQuest", "impDefectorWaypointID"))}

		for i = 1, #waypoints do
			ghost:removeWaypoint(waypoints[i], true)
		end

        ghost:activateJournalQuestTask(questCrc, DefectorQuest.WAIT_FOR_SIGNAL2, true)		-- Index: 6
        ghost:activateJournalQuestTask(questCrc, DefectorQuest.TIMER3, false)				-- First encounter timer
        ghost:activateJournalQuestTask(questCrc, DefectorQuest.TIMER4, true)				-- Overall mission timer

		DefectorQuest:startMissionTimer(pPlayer)

		createEvent(getRandomNumber(100, 150) * 1000, "DefectorQuest", "spawnAttack", pPlayer, "")

	elseif (screenID == "get_moving") then

		-- Check for waypoint to the quest receiver, and add if missing
		local waypointID = tonumber(readScreenPlayData(pPlayer, "DefectorQuest", "impQuestReceiverWaypointID"))

		if (waypointID == nil) then
			-- Waypoint to quest receiver
			local waypointID = ghost:addWaypoint("corellia", "Bring the Imperial defector's codephrase to Teslo Ten'doora in the Rebel Base.", "Bring the Imperial defector's codephrase to Teslo Ten'doora in the Rebel Base.", -6485, 6017, WAYPOINTYELLOW, true, true, questCrc)
			writeScreenPlayData(pPlayer, "DefectorQuest", "impQuestReceiverWaypointID", waypointID)
		end

	end

	return pScreenClone
end

function ImperialDefectorConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	local questCrc = DefectorQuest.IMPERIAL_CRC

	if (pGhost == nil) then
		return
	end

	if PlayerObject(pGhost):isJournalQuestActive(questCrc) then
		return convoTemplate:getScreen("active_greeting")
	else
		return convoTemplate:getScreen("inactive_greeting")
	end
end
