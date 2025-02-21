AllardLissaraConvoHandler = conv_handler:new {

}

function AllardLissaraConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pScreenClone = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pScreenClone)
	local questCrc = DefectorQuest.REBEL_CRC

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
		local pQuestTask1 = defectorTasks:getTask(DefectorQuest.REWARD1)
		local pQuestTask2 = defectorTasks:getTask(DefectorQuest.REWARD2)

		if (pQuestTask1 == nil or pQuestTask2 == nil) then
			Logger:log("ERROR: Unable to load Defector Quest REWARD1 or REWARD2 Quest Tasks in AllardLissaraConvoHandler.", LT_ERROR)
			return 0
		end

		local questTask1 = LuaQuestTask(pQuestTask1)
		local questTask2 = LuaQuestTask(pQuestTask2)

		-- Remove the Waypoint
		local waypointID = tonumber(readScreenPlayData(pPlayer, "DefectorQuest", "rebQuestReceiverWaypointID"))
		deleteScreenPlayData(pPlayer, "DefectorQuest", "rebQuestReceiverWaypointID")

		ghost:completeJournalQuestTask(questCrc, DefectorQuest.WAIT_FOR_SIGNAL2, false)

		ghost:activateJournalQuestTask(questCrc, DefectorQuest.REWARD1, false)
		ghost:activateJournalQuestTask(questCrc, DefectorQuest.REWARD2, false)
		ghost:activateJournalQuestTask(questCrc, DefectorQuest.COMPLETE_QUEST, false)

		ghost:completeJournalQuest(questCrc, true)

		-- Add Imperial faction and credits
		local faction = string.lower(questTask1:getFactionName())
		local amount = questTask1:getFactionAmount()

		ghost:increaseFactionStanding(faction, amount)

		local creditsAmount = questTask1:getBankCredits()
		CreatureObject(pPlayer):addBankCredits(creditsAmount, true)

		CreatureObject(pPlayer):sendSystemMessage("You recieve " .. creditsAmount .. " credits for completing your task.")

		-- Subtract Rebel faction
		faction = string.lower(questTask2:getFactionName())
		amount = questTask2:getFactionAmount()

		ghost:decreaseFactionStanding(faction, -1 * amount)

		DefectorQuest:despawnAmbushMobiles(pPlayer)
		DefectorQuest:cleanUp(pPlayer)
	end

	return pScreenClone
end

function AllardLissaraConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local questCrc = DefectorQuest.REBEL_CRC

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
