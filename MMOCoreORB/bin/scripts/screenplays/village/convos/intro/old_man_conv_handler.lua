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
		-- Clear conversable option bit and schedule Removal of old man agent
		CreatureObject(pNpc):clearOptionBit(CONVERSABLE)
		OldManIntroEncounter:scheduleDespawnOfOldMan(pPlayer)
	elseif screenID == "here_is_the_crystal" then
		-- Clear conversable option bit and schedule Removal of old man agent
		CreatureObject(pNpc):clearOptionBit(CONVERSABLE)
		OldManIntroEncounter:scheduleDespawnOfOldMan(pPlayer)

		-- Give the FS force crystal to the player
		OldManIntroEncounter:giveForceCrystalToPlayer(pPlayer)
	elseif screenID == "where_camp" then
		-- Update player FS Progression
		FsOutro:setCurrentStep(pPlayer, 3)

		-- Clear conversable option bit and schedule Removal of old man agent
		CreatureObject(pNpc):clearOptionBit(CONVERSABLE)
		OldManOutroEncounter:scheduleDespawnOfOldMan(pPlayer)

		-- Update players quest status
		QuestManager.completeQuest(pPlayer, QuestManager.quests.OLD_MAN_FINAL)

		-- Start the Mellicae Village Outro
		MellichaeOutroTheater:start(pPlayer)
	end

	return pConvScreen
end
