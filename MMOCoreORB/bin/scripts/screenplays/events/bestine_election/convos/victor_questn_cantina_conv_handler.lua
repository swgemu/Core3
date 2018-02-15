local ObjectManager = require("managers.object.object_manager")

victorQuestnCantinaConvoHandler = conv_handler:new {}

function victorQuestnCantinaConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local curPhase = BestineElection:getCurrentPhase()
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (curPhase == BestineElection.OFFICE_PHASE) then
		return convoTemplate:getScreen("init_office_phase")
	elseif (pInventory ~= nil and getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questn_dseal.iff", true)) then
		return convoTemplate:getScreen("init_already_has_evidence")
	elseif (BestineElection:hadInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_RIVAL_CANTINA_EVIDENCE)) then
		return convoTemplate:getScreen("init_inv_was_full")
	elseif (BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_RIVAL_QUEST) == BestineElection.SEAN_RIVAL_QUEST_ACCEPTED) then
		return convoTemplate:getScreen("init_on_rival_quest")
	else
		return convoTemplate:getScreen("init_election_phase")
	end
end

function victorQuestnCantinaConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum - 1)

	if (screenID == "init_inv_was_full") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/victor_questn_cantina:s_90ec63e0", "inv_still_full") -- Yes, I do.
		else
			clonedConversation:addOption("@conversation/victor_questn_cantina:s_90ec63e0", "was_full_give_evidence") -- Yes, I do.
		end

		clonedConversation:addOption("@conversation/victor_questn_cantina:s_62bf3631", "go_away_then") -- No, I haven't made room yet.
	elseif (screenID == "init_on_rival_quest") then
		if (CreatureObject(pPlayer):getCashCredits() >= 200) then
			if (BestineElection:hasFullInventory(pPlayer)) then
				clonedConversation:addOption("@conversation/victor_questn_cantina:s_51ac4991", "inv_full") -- Hmm. Here you go.
			else
				clonedConversation:addOption("@conversation/victor_questn_cantina:s_51ac4991", "give_evidence") -- Hmm. Here you go.
			end
		else
			clonedConversation:addOption("@conversation/victor_questn_cantina:s_19d90991", "cheapskate") -- I don't have that kind of money.
		end
	elseif (screenID == "inv_full") then
		BestineElection:setInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_RIVAL_CANTINA_EVIDENCE)
	elseif (screenID == "give_evidence" or screenID == "was_full_give_evidence") then
		if (CreatureObject(pPlayer):getCashCredits() >= 200) then
			CreatureObject(pPlayer):subtractCashCredits(200)
		end

		BestineElection:clearInvFull(pPlayer, BestineElection.SEAN, BestineElection.SEAN_RIVAL_CANTINA_EVIDENCE)

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pEvidence = giveItem(pInventory, "object/tangible/loot/quest/victor_questn_dseal.iff", -1)

			if (pEvidence == nil) then
				printLuaError("Error creating victor cantina evidence for player " .. CreatureObject(pPlayer):getFirstName())
			end
		end
	end

	return pConvScreen
end
