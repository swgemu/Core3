local QuestManager = require("managers.quest.quest_manager")

oldManIntroConvoHandler = conv_handler:new {}

function oldManIntroConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if OldManOutroEncounter:doesOldManBelongToThePlayer(pPlayer, pNpc) then
		return convoTemplate:getScreen("intro_mellichae")
	elseif OldManIntroEncounter:doesOldManBelongToThePlayer(pPlayer, pNpc) then
		return convoTemplate:getScreen("intro")
	else
		return convoTemplate:getScreen("nothing_to_discuss")
	end
end

function oldManIntroConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	if screenID == "perhaps_meet_again" or screenID == "perhaps_another_time" then
		OldManIntroEncounter:scheduleDespawnOfOldMan(pPlayer)
		CreatureObject(pNpc):clearOptionBit(CONVERSABLE)
	elseif screenID == "here_is_the_crystal" then
		OldManIntroEncounter:scheduleDespawnOfOldMan(pPlayer)
		OldManIntroEncounter:giveForceCrystalToPlayer(pPlayer)
		CreatureObject(pNpc):clearOptionBit(CONVERSABLE)
	elseif screenID == "where_camp" then
		OldManOutroEncounter:scheduleDespawnOfOldMan(pPlayer)
		QuestManager.completeQuest(pPlayer, QuestManager.quests.OLD_MAN_FINAL)
		MellichaeOutroTheater:start(pPlayer)
		CreatureObject(pNpc):clearOptionBit(CONVERSABLE)
		FsOutro:setCurrentStep(pPlayer, 3)
	end

	return pConvScreen
end
