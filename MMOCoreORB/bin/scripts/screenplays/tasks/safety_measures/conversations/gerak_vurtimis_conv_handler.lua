local QuestManager = require("managers.quest.quest_manager")

GerakVurtimisConvoHandler = conv_handler:new {}

function GerakVurtimisConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ghost = LuaPlayerObject(pGhost)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	print("Safety Measures -- screenID = " .. screenID)

	if (screenID == "init") then
		CreatureObject(pNpc):doAnimation("stamp_feet")
	elseif (screenID == "giveQuest1_1" or screenID == "giveQuest1_2") then
		SafetyMeasures:startQuest(pPlayer, pNpc, SafetyMeasures.KILLWORRTS)
	elseif (screenID == "give_quest2") then
		SafetyMeasures:startQuest(pPlayer, pNpc, SafetyMeasures.KILLRILLS)
	elseif (screenID == "give_quest3" or screenID == "new_loc3") then
		SafetyMeasures:startQuest(pPlayer, pNpc, SafetyMeasures.KILLBRIGANDS)
	elseif (screenID == "give_quest4") then
		SafetyMeasures:startQuest(pPlayer, pNpc, SafetyMeasures.BRIGANDCAMP)
	elseif (screenID == "give_quest5_1" or screenID == "giveQuest5_2") then
		SafetyMeasures:startQuest(pPlayer, pNpc, SafetyMeasures.BRIGANDLEADER)

	-- Statuses
	elseif (screenID == "quest1_status" and ghost:isJournalQuestTaskComplete(QuestManager.questCRC.QUEST_LF_SAFETY1, 0)) then
		clonedConversation:addOption("@conversation/lf_safetyquestgiver:s_166", "turn_in1")
	elseif (screenID == "quest2_status" and ghost:isJournalQuestTaskComplete(QuestManager.questCRC.QUEST_LF_SAFETY2, 0)) then
		clonedConversation:addOption("@conversation/lf_safetyquestgiver:s_214", "turn_in2")
	elseif (screenID == "quest3_status" and ghost:isJournalQuestTaskComplete(QuestManager.questCRC.QUEST_LF_SAFETY3, 0)) then
		clonedConversation:addOption("@conversation/lf_safetyquestgiver:s_276", "turn_in3")
	elseif (screenID == "quest4_status" and ghost:isJournalQuestTaskComplete(QuestManager.questCRC.QUEST_LF_SAFETY4, 0)) then
		clonedConversation:addOption("@conversation/lf_safetyquestgiver:s_348", "turn_in4")
	elseif (screenID == "quest5_status" and ghost:isJournalQuestTaskComplete(QuestManager.questCRC.QUEST_LF_SAFETY4, 0)) then
		clonedConversation:addOption("@conversation/lf_safetyquestgiver:s_368", "turn_in5_1")
		clonedConversation:addOption("@conversation/lf_safetyquestgiver:s_372", "turn_in5_2")
		clonedConversation:addOption("@conversation/lf_safetyquestgiver:s_376", "turn_in5_3")
	elseif (screenID == "not_interested") then
		CreatureObject(pNpc):doAnimation("shake_head_disgust")

	elseif (screenID == "turn_in1") then
		SafetyMeasures:completeQuest(pPlayer, pNpc, SafetyMeasures.KILLWORRTS)
	elseif (screenID == "turn_in2") then
		SafetyMeasures:completeQuest(pPlayer, pNpc, SafetyMeasures.KILLRILLS)
	elseif (screenID == "turn_in3") then
		SafetyMeasures:completeQuest(pPlayer, pNpc, SafetyMeasures.KILLBRIGANDS)
	elseif (screenID == "turn_in4") then
		SafetyMeasures:completeQuest(pPlayer, pNpc, SafetyMeasures.BRIGANDCAMP)
	elseif (screenID == "turn_in5") then
		SafetyMeasures:completeQuest(pPlayer, pNpc, SafetyMeasures.BRIGANDLEADER)
	end

	return pConvScreen
end

function GerakVurtimisConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ghost = LuaPlayerObject(pGhost)

	print("get initial screen called ")

	local convTemplate = LuaConversationTemplate(pConvTemplate)

	-- reset
	if (pGhost ~= nil) then
		--return convTemplate:getScreen("prompt_quest2")
	end


	-- Quest 5 Completed
	if (ghost:isJournalQuestComplete(QuestManager.questCRC.QUEST_LF_SAFETY5)) then
		return convTemplate:getScreen("thank_you")
	-- Quest 5 active
	elseif (ghost:isJournalQuestActive(QuestManager.questCRC.QUEST_LF_SAFETY5)) then
		return convTemplate:getScreen("quest5_status")

	-- Quest 4 Completed
	elseif (ghost:isJournalQuestComplete(QuestManager.questCRC.QUEST_LF_SAFETY4)) then
		return convTemplate:getScreen("prompt_quest5")
	-- Quest 4 active
	elseif (ghost:isJournalQuestActive(QuestManager.questCRC.QUEST_LF_SAFETY4)) then
		return convTemplate:getScreen("quest3_status")

	-- Quest 3 Completed
	elseif (ghost:isJournalQuestComplete(QuestManager.questCRC.QUEST_LF_SAFETY3)) then
		return convTemplate:getScreen("prompt_quest4")
	-- Quest 3 active
	elseif (ghost:isJournalQuestActive(QuestManager.questCRC.QUEST_LF_SAFETY3)) then
		return convTemplate:getScreen("quest3_status")

	-- Quest 2 Completed
	elseif (ghost:isJournalQuestComplete(QuestManager.questCRC.QUEST_LF_SAFETY2)) then
		return convTemplate:getScreen("prompt_quest3")
	-- Quest 2 active
	elseif (ghost:isJournalQuestActive(QuestManager.questCRC.QUEST_LF_SAFETY2)) then
		return convTemplate:getScreen("quest2_status")

	-- Quest 1 Completed
	elseif (ghost:isJournalQuestComplete(QuestManager.questCRC.QUEST_LF_SAFETY1)) then
		return convTemplate:getScreen("prompt_quest2")
	-- Quest 1 active
	elseif (ghost:isJournalQuestActive(QuestManager.questCRC.QUEST_LF_SAFETY1)) then
		return convTemplate:getScreen("init")
	end

	return convTemplate:getScreen("init")
end
