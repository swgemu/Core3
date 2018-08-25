local ObjectManager = require("managers.object.object_manager")

seanContactConvoHandler = conv_handler:new {}

function seanContactConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum)

	local curPhase = BestineElection:getCurrentPhase()
	if (curPhase == BestineElection.ELECTION_PHASE) then
		electionWinner = BestineElection:getElectionWinner(electionNum - 1)
	end

	if (electionWinner == BestineElection.SEAN and BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST) == BestineElection.SEAN_HISTORY_QUEST_SENT_TO_CONTACT and BestineElection:hasItemInInventory(pPlayer, "object/tangible/loot/quest/sean_history_disk.iff")) then
		return convoTemplate:getScreen("init_sean_in_office_has_item")
	elseif (electionWinner ~= BestineElection.SEAN) then
		return convoTemplate:getScreen("init_sean_not_in_office")
	else
		return convoTemplate:getScreen("init_sean_in_office_no_item")
	end
end

function seanContactConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum - 1)

	if (screenID == "its_finished") then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pDisk = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff" , true)

			if (pDisk ~= nil) then
				SceneObject(pDisk):destroyObjectFromWorld()
				SceneObject(pDisk):destroyObjectFromDatabase()

				BestineElection:setQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST, BestineElection.SEAN_HISTORY_QUEST_DISK_DESTROYED)
			end

			local playerID = SceneObject(pPlayer):getObjectID()
			local wayID = readData(playerID .. ":bestineElection:contactWaypointID")

			local pGhost = CreatureObject(pPlayer):getPlayerObject()

			if (pGhost ~= nil) then
				PlayerObject(pGhost):removeWaypoint(wayID, true)
			end

			deleteData(playerID .. ":bestineElection:historyWaypointID")
		end

	end

	return pConvScreen
end
