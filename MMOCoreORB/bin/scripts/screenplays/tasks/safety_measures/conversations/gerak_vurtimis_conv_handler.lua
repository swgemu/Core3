local ObjectManager = require("managers.object.object_manager")

GerakVurtimisConvoHandler = conv_handler:new {
	themePark = nil
}

function GerakVurtimisConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil) then
		return
	end

	local ghost = CreatureObject(pPlayer):getPlayerObject()

	if (ghost == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "giveQuest1_1" or screenID == "giveQuest1_2") then
		CreatureObject(pNpc):doAnimation("nod")
		PlayerObject(pGhost):activateJournalQuestTask(SafetyMeasures.questCRCs[1], SafetMeasures.KILLWORTS, true)
	elseif (screenID == "giveQuest2") then
		CreatureObject(pNpc):doAnimation("nod")
		PlayerObject(pGhost):activateJournalQuestTask(SafetyMeasures.questCRCs[2], SafetMeasures.KILLRILLS, true)
	elseif (screenID == "giveQuest3") then
		CreatureObject(pNpc):doAnimation("nod")
		PlayerObject(pGhost):activateJournalQuestTask(SafetyMeasures.questCRCs[3], SafetMeasures.KLLBRIGANDS, true)
	elseif (screenID == "giveQuest4") then
		CreatureObject(pNpc):doAnimation("nod")
		PlayerObject(pGhost):activateJournalQuestTask(SafetyMeasures.questCRCs[4], SafetMeasures.BRIGANDCAMP, true)
	elseif (screenID == "giveQuest5_1" or screenID == "giveQuest5_2") then
		CreatureObject(pNpc):doAnimation("nod")
		PlayerObject(pGhost):activateJournalQuestTask(SafetyMeasures.questCRCs[5], SafetMeasures.BRIGANDLEADER, true)

	-- Statuses
	elseif (screenID == "quest1_status") then

		-- if has worrts killed
		clonedConversation:addOption("@conversation/lf_safetyquestgiver:s_166", "turn_in1")
	elseif (screenID == "quest2_status") then

		-- if has rills killed
		clonedConversation:addOption("@conversation/lf_safetyquestgiver:s_214", "turn_in2")
	elseif (screenID == "quest3_status") then

		clonedConversation:addOption("@conversation/lf_safetyquestgiver:s_276", "turn_in3")
	elseif (screenID == "quest4_status") then

		clonedConversation:addOption("@conversation/lf_safetyquestgiver:s_348", "turn_in4")

	elseif (screenID == "quest5_status") then
		clonedConversation:addOption("@conversation/lf_safetyquestgiver:s_368", "turn_in5_1")
		clonedConversation:addOption("@conversation/lf_safetyquestgiver:s_372", "turn_in5_2")
		clonedConversation:addOption("@conversation/lf_safetyquestgiver:s_376", "turn_in5_3")
	elseif (screenID == "not_interested") then
		CreatureObject(pNpc):doAnimation("shake_head_disgust")

	elseif (screenID == "turn_in1") then
		CreatureObject(pNpc):doAnimation("applause_excited")
		PlayerObject(pGhost):completeJournalQuestTask(SafetyMeasures.questCRCs[1], SafetMeasures.KILLWORRTS, true)
	elseif (screenID == "turn_in2") then
		CreatureObject(pNpc):doAnimation("applause_excited")
		PlayerObject(pGhost):completeJournalQuestTask(SafetyMeasures.questCRCs[2], SafetMeasures.KILLRILLS, true)
	elseif (screenID == "turn_in3") then
		CreatureObject(pNpc):doAnimation("applause_excited")
		PlayerObject(pGhost):completeJournalQuestTask(SafetyMeasures.questCRCs[3], SafetMeasures.KILLBRIGANDS, true)
	elseif (screenID == "turn_in4") then
		CreatureObject(pNpc):doAnimation("applause_excited")
		PlayerObject(pGhost):completeJournalQuestTask(SafetyMeasures.questCRCs[4], SafetMeasures.BRIGANDCAMP, true)
	elseif (screenID == "turn_in5") then
		CreatureObject(pNpc):doAnimation("applause_excited")
		PlayerObject(pGhost):completeJournalQuestTask(SafetyMeasures.questCRCs[5], SafetMeasures.BRIGANDLEADER, true)
	end

	return pConvScreen
end

function GerakVurtimisConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	local convTemplate = LuaConversationTemplate(pConvTemplate)



	CreatureObject(pNpc):doAnimation("stamp_feet")
	return convTemplate:getScreen("init")
end
