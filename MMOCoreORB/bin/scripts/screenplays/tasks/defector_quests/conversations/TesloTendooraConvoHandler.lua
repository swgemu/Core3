TesloTendooraConvoHandler = conv_handler:new {
	debugNotify = true, -- Send system messages for testing
}

function TesloTendooraConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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

	if (screenID == "response_correct_1" or screenID == "response_correct_2") then
		-- Add Rebel faction and credits
		local pQuestTask1 = defectorTasks:getTask(DefectorQuest.REWARD1)
		local pQuestTask2 = defectorTasks:getTask(DefectorQuest.REWARD2)

		if (pQuestTask1 == nil or pQuestTask2 == nil) then
			Logger:log("ERROR: Unable to load Defector Quest REWARD1 or REWARD2 Quest Tasks in TesloTendooraConvoHandler.", LT_ERROR)
			return 0
		end

		local questTask1 = LuaQuestTask(pQuestTask1)
		local questTask2 = LuaQuestTask(pQuestTask2)

		-- Remove the Waypoint
		local waypointID = tonumber(readScreenPlayData(pPlayer, "DefectorQuest", "impQuestReceiverWaypointID"))
		deleteScreenPlayData(pPlayer, "DefectorQuest", "impQuestReceiverWaypointID")

		ghost:removeWaypoint(waypointID, true)

		ghost:completeJournalQuestTask(questCrc, DefectorQuest.WAIT_FOR_SIGNAL2, false)

		ghost:activateJournalQuestTask(questCrc, DefectorQuest.REWARD1, false)
		ghost:activateJournalQuestTask(questCrc, DefectorQuest.REWARD2, false)

		ghost:completeJournalQuestTask(questCrc, DefectorQuest.COMPLETE_QUEST, false)
		ghost:completeJournalQuest(questCrc, true)

		local faction = string.lower(questTask1:getFactionName())
		local amount = questTask1:getFactionAmount()

		ghost:increaseFactionStanding(faction, amount)

		local creditsAmount = questTask1:getBankCredits()
		CreatureObject(pPlayer):addBankCredits(creditsAmount, true)

		CreatureObject(pPlayer):sendSystemMessage("You recieve " .. creditsAmount .. " credits for completing your task.")

		-- Subtract Imperial faction
		faction = string.lower(questTask2:getFactionName())
		amount = questTask2:getFactionAmount()

		ghost:decreaseFactionStanding(faction, -1 * amount)

		DefectorQuest:despawnAmbushMobiles(pPlayer)
		DefectorQuest:cleanUp(pPlayer)
	end

	return pScreenClone
end

function TesloTendooraConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local questCrc = DefectorQuest.IMPERIAL_CRC

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ghost = LuaPlayerObject(pGhost)

	if DefectorQuest:activeTask(ghost, questCrc, DefectorQuest.WAIT_FOR_SIGNAL2) then
		return convoTemplate:getScreen("active_greeting")
	else
		return convoTemplate:getScreen("waiting_delivery")
	end
end
