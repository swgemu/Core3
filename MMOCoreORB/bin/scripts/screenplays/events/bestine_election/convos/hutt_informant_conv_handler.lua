local ObjectManager = require("managers.object.object_manager")

huttInformantConvoHandler = conv_handler:new {}

function huttInformantConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum)

	local curPhase = BestineElection:getCurrentPhase()
	if (curPhase == BestineElection.ELECTION_PHASE) then
		electionWinner = BestineElection:getElectionWinner(electionNum - 1)
	end

	if (electionWinner == BestineElection.SEAN and BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST) == BestineElection.SEAN_HISTORY_QUEST_SENT_TO_CONTACT and BestineElection:hasItemInInventory(pPlayer, "object/tangible/loot/quest/sean_history_disk.iff")) then
		return convoTemplate:getScreen("init_sean_in_office_has_item")
	else
		return convoTemplate:getScreen("init_default")
	end
end

function huttInformantConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum - 1)

	if (screenID == "dont_blame_me") then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pDisk = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff", true)

			if (pDisk ~= nil) then
				SceneObject(pDisk):destroyObjectFromWorld()
				SceneObject(pDisk):destroyObjectFromDatabase()

				BestineElection:setQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HISTORY_QUEST, BestineElection.SEAN_HISTORY_QUEST_GAVE_TO_HUTT)

				local pReward = giveItem(pInventory, "object/weapon/ranged/grenade/grenade_cryoban.iff", -1)

				if (pReward == nil) then
					printLuaError("Error creating hutt campaign reward for player " .. CreatureObject(pPlayer):getFirstName())
					return
				end
			end
		end

	end

	return pConvScreen
end
