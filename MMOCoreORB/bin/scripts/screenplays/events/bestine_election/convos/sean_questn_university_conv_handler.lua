local ObjectManager = require("managers.object.object_manager")

seanQuestnUniversityConvoHandler = conv_handler:new {}

function seanQuestnUniversityConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local curPhase = BestineElection:getCurrentPhase()
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (curPhase == BestineElection.OFFICE_PHASE) then
		return convoTemplate:getScreen("init_office_phase")
	elseif (pInventory ~= nil and getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questn_gpapers.iff", true)) then
		return convoTemplate:getScreen("init_has_evidence")
	elseif (BestineElection:hadInvFull(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_RIVAL_UNIVERSITY_EVIDENCE)) then
		return convoTemplate:getScreen("init_inv_was_full")
	elseif (BestineElection:getQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_RIVAL_QUEST) == BestineElection.VICTOR_RIVAL_QUEST_ACCEPTED) then
		return convoTemplate:getScreen("init_on_rival_quest")
	else
		return convoTemplate:getScreen("init_election_phase")
	end
end

function seanQuestnUniversityConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local electionNum = BestineElection:getElectionNumber()
	local electionWinner = BestineElection:getElectionWinner(electionNum - 1)

	if (screenID == "init_inv_was_full") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/sean_questn_university:s_7e78bf8f", "inv_still_full") -- Yes, can I have the evidence, please?
		else
			clonedConversation:addOption("@conversation/sean_questn_university:s_7e78bf8f", "was_full_give_evidence") -- Yes, can I have the evidence, please?
		end

		clonedConversation:addOption("@conversation/sean_questn_university:s_7291fe2e", "theres_no_hurry") -- Not yet. I still need to make room.
	elseif (screenID == "use_as_evidence") then
		if (BestineElection:hasFullInventory(pPlayer)) then
			clonedConversation:addOption("@conversation/sean_questn_university:s_b9b27823", "inv_full") -- Thank you.
		else
			clonedConversation:addOption("@conversation/sean_questn_university:s_b9b27823", "good_day") -- Thank you.
		end
	elseif (screenID == "inv_full") then
		BestineElection:setInvFull(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_RIVAL_UNIVERSITY_EVIDENCE)
	elseif (screenID == "good_day" or screenID == "was_full_give_evidence") then
		BestineElection:clearInvFull(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_RIVAL_UNIVERSITY_EVIDENCE)

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pEvidence = giveItem(pInventory, "object/tangible/loot/quest/sean_questn_gpapers.iff", -1)

			if (pEvidence == nil) then
				printLuaError("Error creating Sean university evidence for player " .. CreatureObject(pPlayer):getFirstName())
			end
		end
	end

	return pConvScreen
end
