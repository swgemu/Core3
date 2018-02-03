local ObjectManager = require("managers.object.object_manager")

victorQuestnCapitolConvoHandler = conv_handler:new {}

function victorQuestnCapitolConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local curPhase = BestineElection:getCurrentPhase()
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (curPhase == BestineElection.OFFICE_PHASE) then
		return convoTemplate:getScreen("init_office_phase")
	elseif (pInventory ~= nil and getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questn_hlist.iff", true)) then
		return convoTemplate:getScreen("init_already_has_evidence")
	elseif (BestineElection:hadInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_RIVAL_CAPITOL_EVIDENCE)) then
		return convoTemplate:getScreen("init_inv_was_full")
	elseif (BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_RIVAL_QUEST) == BestineElection.SEAN_RIVAL_QUEST_ACCEPTED) then
		return convoTemplate:getScreen("init_on_rival_quest")
	else
		return convoTemplate:getScreen("init_election_phase")
	end
end

function victorQuestnCapitolConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum - 1)

	if (screenID == "init_inv_was_full") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/victor_questn_capitol:s_90ec63e0", "inv_still_full") -- Yes, I do.
		else
			clonedConversation:addOption("@conversation/victor_questn_capitol:s_90ec63e0", "was_full_give_evidence") -- Yes, I do.
		end

		clonedConversation:addOption("@conversation/victor_questn_capitol:s_da9a29e9", "wasting_my_time") -- No, not yet.
	elseif (screenID == "looking_for_evidence") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/victor_questn_capitol:s_b9b27823", "inv_full") -- Thank you.
		else
			clonedConversation:addOption("@conversation/victor_questn_capitol:s_b9b27823", "give_evidence") -- Thank you.
		end
	elseif (screenID == "inv_full") then
		BestineElection:setInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_RIVAL_CAPITOL_EVIDENCE)
	elseif (screenID == "give_evidence" or screenID == "was_full_give_evidence") then
		BestineElection:clearInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_RIVAL_CAPITOL_EVIDENCE)

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pEvidence = giveItem(pInventory, "object/tangible/loot/quest/victor_questn_hlist.iff", -1)

			if (pEvidence == nil) then
				printLuaError("Error creating victor capitol evidence for player " .. CreatureObject(pPlayer):getFirstName())
			end
		end
	end

	return pConvScreen
end
