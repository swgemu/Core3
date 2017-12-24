local ObjectManager = require("managers.object.object_manager")

victorQuestpHospitalConvoHandler = conv_handler:new {}

function victorQuestpHospitalConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local curPhase = BestineElection:getCurrentPhase()
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (curPhase == BestineElection.OFFICE_PHASE) then
		return convoTemplate:getScreen("init_office_phase")
	elseif (pInventory ~= nil and getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questp_receipt.iff", true)) then
		return convoTemplate:getScreen("init_already_has_evidence")
	elseif (BestineElection:hadInvFull(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_HOSPITAL_EVIDENCE)) then
		return convoTemplate:getScreen("init_inv_was_full")
	elseif (BestineElection:hasJoinedCampaign(pPlayer, BestineElection.VICTOR)) then
		return convoTemplate:getScreen("init_joined_victor")
	else
		return convoTemplate:getScreen("init_election_phase")
	end
end

function victorQuestpHospitalConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum - 1)

	if (screenID == "init_inv_was_full") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/victor_questp_hospital:s_90ec63e0", "inv_still_full") -- Yes, I do.
		else
			clonedConversation:addOption("@conversation/victor_questp_hospital:s_90ec63e0", "was_full_give_evidence") -- Yes, I do.
		end

		clonedConversation:addOption("@conversation/victor_questp_hospital:s_da9a29e9", "come_back") -- No, not yet.
	elseif (screenID == "perfect_thing") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/victor_questp_hospital:s_67e6df55", "inv_full") -- Okay.
		else
			clonedConversation:addOption("@conversation/victor_questp_hospital:s_67e6df55", "give_evidence") -- Okay.
		end
	elseif (screenID == "inv_full") then
		BestineElection:setInvFull(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_HOSPITAL_EVIDENCE)
	elseif (screenID == "give_evidence" or screenID == "was_full_give_evidence") then
		BestineElection:clearInvFull(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_HOSPITAL_EVIDENCE)

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pEvidence = giveItem(pInventory, "object/tangible/loot/quest/victor_questp_receipt.iff", -1)

			if (pEvidence == nil) then
				printLuaError("Error creating victor hospital evidence for player " .. CreatureObject(pPlayer):getFirstName())
			end
		end
	end

	return pConvScreen
end
