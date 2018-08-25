local ObjectManager = require("managers.object.object_manager")

seanQuestpHouseConvoHandler = conv_handler:new {}

function seanQuestpHouseConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local curPhase = BestineElection:getCurrentPhase()
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (curPhase == BestineElection.OFFICE_PHASE) then
		return convoTemplate:getScreen("init_not_election_phase")
	elseif (pInventory ~= nil and getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questp_htestimony.iff", true)) then
		return convoTemplate:getScreen("init_already_has_evidence")
	elseif (BestineElection:hadInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HOUSE_EVIDENCE)) then
		return convoTemplate:getScreen("init_inv_was_full")
	elseif (BestineElection:hasJoinedCampaign(pPlayer, BestineElection.SEAN)) then
		return convoTemplate:getScreen("init_joined_sean")
	else
		return convoTemplate:getScreen("init_election_phase")
	end
end

function seanQuestpHouseConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum - 1)

	if (screenID == "init_inv_was_full") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/sean_questp_house:s_e69937da", "still_no_room") -- Yes. Thank you.
		else
			clonedConversation:addOption("@conversation/sean_questp_house:s_e69937da", "here_you_are_then") -- Yes. Thank you.
		end

		clonedConversation:addOption("@conversation/sean_questp_house:s_48b343d3", "return_when_done") -- Actually, no I don't.
	elseif (screenID == "write_a_testimony") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/sean_questp_house:s_67e6df55", "inv_full") -- Okay.
		else
			clonedConversation:addOption("@conversation/sean_questp_house:s_67e6df55", "come_for_dinner") -- Okay.
		end
	elseif (screenID == "inv_full") then
		BestineElection:setInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HOUSE_EVIDENCE)
	elseif (screenID == "here_you_are_then" or screenID == "come_for_dinner") then
		BestineElection:clearInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_HOUSE_EVIDENCE)

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pEvidence = giveItem(pInventory, "object/tangible/loot/quest/sean_questp_htestimony.iff", -1)

			if (pEvidence == nil) then
				printLuaError("Error creating Sean House evidence for player " .. CreatureObject(pPlayer):getFirstName())
			end
		end
	end

	return pConvScreen
end
