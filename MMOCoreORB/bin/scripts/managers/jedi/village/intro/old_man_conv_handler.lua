local VillageJediManagerCommon = require("managers.jedi.village.village_jedi_manager_common")
local OldManEncounter = require("managers.jedi.village.intro.old_man_encounter")
local QuestManager = require("managers.quest.quest_manager")
local MellichaeOutroTheater = require("managers.jedi.village.outro.mellichae_outro_theater")

oldManIntroConvoHandler = Object:new {}

function oldManIntroConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pPlayer):getConversationSession()

	local pLastConversationScreen = nil

	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end

	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)

	if (pLastConversationScreen ~= nil) then
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)

		return conversationTemplate:getScreen(optionLink)
	end

	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end

function oldManIntroConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	if OldManEncounter:doesOldManBelongToThePlayer(pPlayer, pNpc) then
		if (VillageJediManagerCommon.hasJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE)) then
			return convoTemplate:getScreen("intro_mellichae")
		else
			return convoTemplate:getScreen("intro")
		end
	else
		return convoTemplate:getScreen("nothing_to_discuss")
	end
end


function oldManIntroConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)

	local screenID = screen:getScreenID()

	if screenID == "perhaps_meet_again" or screenID == "perhaps_another_time" then
		OldManEncounter:scheduleDespawnOfOldMan(pConversingPlayer)
		CreatureObject(pConversingNpc):setOptionsBitmask(128)
	elseif screenID == "here_is_the_crystal" then
		OldManEncounter:scheduleDespawnOfOldMan(pConversingPlayer)
		OldManEncounter:giveForceCrystalToPlayer(pConversingPlayer)
		CreatureObject(pConversingNpc):setOptionsBitmask(128)
	elseif screenID == "where_camp" then
		QuestManager.completeQuest(pConversingPlayer, QuestManager.quests.OLD_MAN_FINAL)
		MellichaeOutroTheater:start(pConversingPlayer)
		CreatureObject(pConversingNpc):setOptionsBitmask(128)
	end

	return pConversationScreen
end
