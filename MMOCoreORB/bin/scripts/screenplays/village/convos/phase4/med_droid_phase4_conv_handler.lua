local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageMedicalDroidPhase4ConvoHandler = conv_handler:new {}

function villageMedicalDroidPhase4ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_1) and not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_2) then
		return convoTemplate:getScreen("intro_no_quest")
	end
	
	return convoTemplate:getScreen("medical_records")
end

function villageMedicalDroidPhase4ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "medical_records") then
		local healCount = FsVillageDefense:getVillageHealingCount(pPlayer)
		clonedConversation:setDialogTextTO(healCount)
	end

	return pConvScreen
end
