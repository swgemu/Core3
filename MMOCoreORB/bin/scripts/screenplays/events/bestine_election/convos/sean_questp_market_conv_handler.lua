local ObjectManager = require("managers.object.object_manager")

seanQuestpMarketConvoHandler = conv_handler:new {}

function seanQuestpMarketConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local curPhase = BestineElection:getCurrentPhase()
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (curPhase == BestineElection.OFFICE_PHASE) then
		return convoTemplate:getScreen("init_not_election_phase")
	elseif (pInventory ~= nil and getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questp_mdisk.iff", true)) then
		return convoTemplate:getScreen("init_already_has_evidence")
	elseif (BestineElection:hadInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_MARKET_EVIDENCE)) then
		return convoTemplate:getScreen("init_inv_was_full")
	elseif (BestineElection:hasJoinedCampaign(pPlayer, BestineElection.SEAN)) then
		return convoTemplate:getScreen("init_joined_sean")
	else
		return convoTemplate:getScreen("init_election_phase")
	end
end

function seanQuestpMarketConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum - 1)

	if (screenID == "init_inv_was_full") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/sean_questp_market:s_c82e9a2f", "inv_still_full") -- Yes, please.
		else
			clonedConversation:addOption("@conversation/sean_questp_market:s_c82e9a2f", "give_evidence") -- Yes, please.
		end

		clonedConversation:addOption("@conversation/sean_questp_market:s_6cd9792d", "return_when_done") -- Haven't had a chance yet.
	elseif (screenID == "lucky_you_came") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/sean_questp_market:s_a4149441", "help_but_inv_full") -- Let me tell you the situation...
		else
			clonedConversation:addOption("@conversation/sean_questp_market:s_a4149441", "love_to_help") -- Let me tell you the situation...
		end
	elseif (screenID == "help_but_inv_full") then
		BestineElection:setInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_MARKET_EVIDENCE)
	elseif (screenID == "give_evidence" or screenID == "love_to_help") then
		BestineElection:clearInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_MARKET_EVIDENCE)

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pEvidence = giveItem(pInventory, "object/tangible/loot/quest/sean_questp_mdisk.iff", -1)

			if (pEvidence == nil) then
				printLuaError("Error creating Sean Market evidence for player " .. CreatureObject(pPlayer):getFirstName())
			end
		end
	end

	return pConvScreen
end
