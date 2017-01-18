local ObjectManager = require("managers.object.object_manager")

paemosConvoHandler = conv_handler:new {}

function paemosConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	CreatureObject(pNpc):doAnimation("beckon")

	if (VillageJediManagerCommon.isVillageEligible(pPlayer)) then
		return convoTemplate:getScreen("intro")
	else
		return convoTemplate:getScreen("cant_convert")
	end
end

function paemosConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (string.find(screenID, "learn_")) then
		local learnType = string.sub(screenID, 7)
		ExperienceConverter:sendConversionSUI(pPlayer, pNpc, learnType)
	elseif (screenID == "what_aspects") then
		local branchList = ExperienceConverter:getBranchLearnList(pPlayer)
		clonedConversation:setDialogTextTO(branchList)
	end

	return pConvScreen
end
