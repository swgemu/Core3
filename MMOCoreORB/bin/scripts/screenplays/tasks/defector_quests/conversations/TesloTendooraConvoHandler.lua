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
		ghost:completeJournalQuestTask(questCrc, DefectorQuest.WAIT_FOR_SIGNAL2, false)
		ghost:activateJournalQuestTask(questCrc, DefectorQuest.REWARD1, false)
		ghost:activateJournalQuestTask(questCrc, DefectorQuest.REWARD2, false)
		ghost:completeJournalQuestTask(questCrc, DefectorQuest.COMPLETE_QUEST, false)
		ghost:completeJournalQuest(questCrc, true)

		-- Add Rebel faction and credits
		local pQuestTask = defectorTasks:getTask(DefectorQuest.REWARD1)

		if pQuestTask == nil then
			Logger:log("ERROR: Could not load Defector Quest Task - REWARD1", LT_ERROR)
			return 0
		end

		local questTask = LuaQuestTask(pQuestTask)
		local faction = string.lower(questTask:getFactionName())

		ghost:increaseFactionStanding(faction, questTask:getFactionAmount())

		local creditsAmount = questTask:getBankCredits()
		CreatureObject(pPlayer):addBankCredits(creditsAmount, true)

		CreatureObject(pPlayer):sendSystemMessage("You recieve " .. creditsAmount .. " credits for completing your task.")

		-- Subtract Imperial faction
		pQuestTask = defectorTasks:getTask(DefectorQuest.REWARD2)

		if pQuestTask == nil then
			Logger:log("ERROR: Could not load Defector Quest Task - REWARD2", LT_ERROR)
			return 0
		end

		questTask = LuaQuestTask(pQuestTask)
		faction = string.lower(questTask:getFactionName())

		ghost:decreaseFactionStanding(faction, -(questTask:getFactionAmount()))

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
