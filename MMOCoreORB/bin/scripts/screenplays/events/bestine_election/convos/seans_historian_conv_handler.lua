local ObjectManager = require("managers.object.object_manager")

seansHistorianConvoHandler = conv_handler:new {}

function seansHistorianConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum)

	if (BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST) == BestineElection.SEAN_HISTORY_QUEST_ACCEPTED) then
		return convoTemplate:getScreen("init_on_quest")
	elseif (BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST) == BestineElection.SEAN_HISTORY_QUEST_STARTED_SEARCH or BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST) == BestineElection.SEAN_HISTORY_QUEST_FOUND_DISK) then
		return convoTemplate:getScreen("init_started_searching")
	elseif (electionWinner == BestineElection.SEAN) then
		return convoTemplate:getScreen("init_sean_in_office_no_quest")
	else
		return convoTemplate:getScreen("init_sean_not_in_office_no_quest")
	end
end

function seansHistorianConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum - 1)

	if (screenID == "init_started_searching") then
		if (BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST) == BestineElection.SEAN_HISTORY_QUEST_FOUND_DISK and BestineElection:hasItemInInventory(pPlayer, "object/tangible/loot/quest/sean_history_disk.iff")) then
			clonedConversation:addOption("@conversation/seans_historian:s_b30bd73c", "interesting_piece") -- Yes, I did.
		end
	elseif (screenID == "interesting_piece") then
		BestineElection:setQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST, BestineElection.SEAN_HISTORY_QUEST_DISK_SCREENED)
	elseif (screenID == "be_careful") then
		local playerID = SceneObject(pPlayer):getObjectID()
		local wayID = readData(playerID .. ":bestineElection:historyWaypointID")

		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if (pGhost ~= nil) then
			PlayerObject(pGhost):removeWaypoint(wayID, true)
		end

		deleteData(playerID .. ":bestineElection:historyWaypointID")

		BestineElection:setQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST, BestineElection.SEAN_HISTORY_QUEST_STARTED_SEARCH)
	end

	return pConvScreen
end
