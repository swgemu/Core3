local ObjectManager = require("managers.object.object_manager")

victorQuestpSlumsConvoHandler = conv_handler:new {}

function victorQuestpSlumsConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local curPhase = BestineElection:getCurrentPhase()
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (curPhase == BestineElection.OFFICE_PHASE) then
		return convoTemplate:getScreen("init_office_phase")
	elseif (pInventory ~= nil and getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questp_testimony.iff", true)) then
		return convoTemplate:getScreen("init_already_has_evidence")
	elseif (BestineElection:hadInvFull(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_SLUMS_EVIDENCE)) then
		return convoTemplate:getScreen("init_inv_was_full")
	elseif (BestineElection:hasJoinedCampaign(pPlayer, BestineElection.VICTOR)) then
		return convoTemplate:getScreen("init_joined_victor")
	else
		return convoTemplate:getScreen("init_election_phase")
	end
end

function victorQuestpSlumsConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum - 1)

	if (screenID == "init_inv_was_full") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/victor_questp_slums:s_ee6997ba", "inv_still_full") -- I do, thank you.
		else
			clonedConversation:addOption("@conversation/victor_questp_slums:s_ee6997ba", "was_full_give_evidence") -- I do, thank you.
		end

		clonedConversation:addOption("@conversation/victor_questp_slums:s_76cc19da", "come_back_later") -- No, I still don't have room.
	elseif (screenID == "would_do_anything") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/victor_questp_slums:s_67e6df55", "inv_full") -- Okay.
		else
			clonedConversation:addOption("@conversation/victor_questp_slums:s_67e6df55", "give_evidence") -- Okay.
		end
	elseif (screenID == "inv_full") then
		BestineElection:setInvFull(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_SLUMS_EVIDENCE)
	elseif (screenID == "give_evidence" or screenID == "was_full_give_evidence") then
		BestineElection:clearInvFull(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_SLUMS_EVIDENCE)

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pEvidence = giveItem(pInventory, "object/tangible/loot/quest/victor_questp_testimony.iff", -1)

			if (pEvidence == nil) then
				printLuaError("Error creating victor slums evidence for player " .. CreatureObject(pPlayer):getFirstName())
			end
		end
	end

	return pConvScreen
end
