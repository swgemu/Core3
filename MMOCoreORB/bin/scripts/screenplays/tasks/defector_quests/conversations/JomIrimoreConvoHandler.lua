local QuestManager = require("managers.quest.quest_manager")

JomIrimoreConvoHandler = conv_handler:new {
	debugNotify = true, -- Send system messages for testing
}

function JomIrimoreConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pScreenClone = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pScreenClone)
	local questCrc = DefectorQuest.IMPERIAL_CRC
	local taskIndex = DefectorQuest.GO_TO_LOCATION

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

	if (screenID == "response_deny_neutral" or screenID == "response_deny_rebel") then
		CreatureObject(pPlayer):doAnimation("shrug_shoulders")
		CreatureObject(pNpc):doAnimation("shake_head_no")

	elseif (screenID == "response_start_rebel" or screenID == "response_start_neutral" or screenID == "response_start2") then
		CreatureObject(pPlayer):doAnimation("salute1")
		CreatureObject(pNpc):doAnimation("salute1")

		-- Waypoint to Defector
		local waypointID = ghost:addWaypoint("corellia", "Find the Imperial Defector", "Find the Imperial Defector", -4296, 3801, WAYPOINTYELLOW, true, true, questCrc)
		writeScreenPlayData(pPlayer, "DefectorQuest", "impDefectorWaypointID", waypointID)

		-- Waypoint to quest giver
		waypointID = ghost:addWaypoint("corellia", "Jom Irimore", "Jom Irimore", -5520, -2631, WAYPOINTYELLOW, true, true, questCrc)
		writeScreenPlayData(pPlayer, "DefectorQuest", "impQuestGiverWaypointID", waypointID)
		
		ghost:activateJournalQuest(questCrc, true)
		ghost:activateJournalQuestTask(questCrc, taskIndex, true)
		writeScreenPlayData(pPlayer, "DefectorQuest", "taskIndex", taskIndex)

	elseif (screenID == "where_defector") then
		CreatureObject(pNpc):doAnimation("sigh_deeply")

		-- Waypoint to Defector
		local waypointID = tonumber(readScreenPlayData(pPlayer, "DefectorQuest", "impDefectorWaypointID"))

		if (waypointID == nil) then
			local waypointID = ghost:addWaypoint("corellia", "Find the Imperial Defector", "Find the Imperial Defector", -4296, 3801, WAYPOINTYELLOW, true, true, questCrc)
			writeScreenPlayData(pPlayer, "DefectorQuest", "impDefectorWaypointID", waypointID)
		end

		-- Check for Quest Journal active task
		if not (DefectorQuest:activeTask(ghost, questCrc, taskIndex)) then
			ghost:activateJournalQuestTask(questCrc, taskIndex, true)
			writeScreenPlayData(pPlayer, "DefectorQuest", "taskIndex", taskIndex)
		end
	end

	return pScreenClone
end

function JomIrimoreConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local faction = CreatureObject(pPlayer):getFaction()
	local questCrc = DefectorQuest.IMPERIAL_CRC
	local taskIndex = DefectorQuest.GO_TO_LOCATION

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ghost = LuaPlayerObject(pGhost)

	if ghost:isJournalQuestActive(REBEL_CRC)  or faction == FACTIONIMPERIAL then
		return convoTemplate:getScreen("imperial_greeting")
	end

	if not PlayerObject(pGhost):isJournalQuestActive(questCrc) then

		-- Check if player has already completed quest
		if PlayerObject(pGhost):isJournalQuestComplete(questCrc) then
			return convoTemplate:getScreen("welcome_back")
		
		else
			if (faction == FACTIONREBEL) then
				return convoTemplate:getScreen("rebel_greeting")
			elseif (faction == FACTIONNEUTRAL) then
				return convoTemplate:getScreen("neutral_greeting")
			end
		end

	elseif DefectorQuest:activeTask(ghost, questCrc, taskIndex) then
		return convoTemplate:getScreen("where_defector")
	
	else
		return convoTemplate:getScreen("nice_day")
	end
end
