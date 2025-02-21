local QuestManager = require("managers.quest.quest_manager")

JaekVercetConvoHandler = conv_handler:new {

}

function JaekVercetConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pScreenClone = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pScreenClone)
	local questCrc = DefectorQuest.REBEL_CRC
	local taskIndex = DefectorQuest.GO_TO_LOCATION

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ghost = LuaPlayerObject(pGhost)
	local playerID = SceneObject(pPlayer):getObjectID()

	local pDefectorTasks = getQuestTasks(questCrc)

	if pDefectorTasks == nil then
		Logger:log("ERROR: Could not load DefectorQuest Tasks in JaekVercetConvoHandler.", LT_ERROR)
		return 0
	end

	local defectorTasks = LuaQuestTasks(pDefectorTasks)

	if (screenID == "response_deny_neutral" or screenID == "response_deny_imperial") then
		CreatureObject(pPlayer):doAnimation("shrug_shoulders")
		CreatureObject(pNpc):doAnimation("shake_head_no")
	elseif (screenID == "response_start_imperial" or screenID == "response_start_neutral" or screenID == "response_start2") then
		CreatureObject(pPlayer):doAnimation("salute1")
		CreatureObject(pNpc):doAnimation("salute1")

		-- Waypoint to Defector
		local waypointID = ghost:addWaypoint("naboo", "@quest/ground/c_rebdefector:task00_journal_entry_title", "@quest/ground/c_rebdefector:task00_journal_entry_description", 4653, 0, -4412, WAYPOINT_YELLOW, true, true, questCrc)
		writeScreenPlayData(pPlayer, "DefectorQuest", "rebDefectorWaypointID", waypointID)

		-- Waypoint to quest giver
		waypointID = ghost:addWaypoint("naboo", "Jaek Vercet", "Jaek Vercet", 4802, 0, -5002, WAYPOINT_YELLOW, true, true, questCrc)
		writeScreenPlayData(pPlayer, "DefectorQuest", "rebQuestGiverWaypointID", waypointID)

		ghost:activateJournalQuest(questCrc, true)
		ghost:activateJournalQuestTask(questCrc, taskIndex, true)

		writeScreenPlayData(pPlayer, "DefectorQuest", "taskIndex", taskIndex)
	elseif (screenID == "where_defector") then
		CreatureObject(pNpc):doAnimation("sigh_deeply")

		-- Waypoint to Defector
		local waypointID = tonumber(readScreenPlayData(pPlayer, "DefectorQuest", "rebDefectorWaypointID"))

		if (waypointID == nil) then
			local waypointID = ghost:addWaypoint("naboo", "@quest/ground/c_rebdefector:task00_journal_entry_title", "@quest/ground/c_rebdefector:task00_journal_entry_description", 4653, 0, -4412, WAYPOINT_YELLOW, true, true, questCrc)
			writeScreenPlayData(pPlayer, "DefectorQuest", "rebDefectorWaypointID", waypointID)
		end

		-- Check for Quest Journal active task
		if not (DefectorQuest:activeTask(ghost, questCrc, taskIndex)) then
			ghost:activateJournalQuestTask(questCrc, taskIndex, true)
			writeScreenPlayData(pPlayer, "DefectorQuest", "taskIndex", taskIndex)
		end
	end

	return pScreenClone
end

function JaekVercetConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local faction = CreatureObject(pPlayer):getFaction()
	local questCrc = DefectorQuest.REBEL_CRC
	local taskIndex = DefectorQuest.GO_TO_LOCATION

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ghost = LuaPlayerObject(pGhost)

	if ghost:isJournalQuestActive(DefectorQuest.IMPERIAL_CRC) or faction == FACTIONREBEL then
		return convoTemplate:getScreen("rebel_greeting")
	end

	if not PlayerObject(pGhost):isJournalQuestActive(questCrc) then
		-- Check if player has already completed quest
		if PlayerObject(pGhost):isJournalQuestComplete(questCrc) then
			return convoTemplate:getScreen("welcome_back")

		else
			if (faction == FACTIONIMPERIAL) then
				return convoTemplate:getScreen("imperial_greeting")
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
