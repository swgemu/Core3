c3tc_convo_handler = conv_handler:new {}

local quest1Crc = 3408891851 --CRC of "quest/c_darndroid1"
local quest2Crc = 3329009938 --CRC of "quest/c_darndroid2"

function c3tc_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):isJournalQuestComplete(quest2Crc) == true) then
		return convoTemplate:getScreen("mem_wiped")
	elseif (PlayerObject(pGhost):isJournalQuestActive(quest1Crc) == true) then
		return convoTemplate:getScreen("not_done")
	else
		return convoTemplate:getScreen("first_screen")
	end
end

function c3tc_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pClonedConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pClonedConvScreen)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

    if (screenID == "ill_help" or screenID == "find_master" or screenID == "start_looking")  then
		DarnDroid1:giveQuest(pPlayer)
	elseif(screenID == "not_done") then
		if (PlayerObject(pGhost):isJournalQuestTaskActive(quest2Crc, 6)) then
			clonedConversation:addOption("@conversation/c_ddroid_droid:s_108","on_talus") --I have seen him.  He is on Talus.
		end
        clonedConversation:addOption("@conversation/c_ddroid_droid:s_140","no_use") --There's nothing that I can tell you that would be of any use right now.
		clonedConversation:addOption("@conversation/c_ddroid_droid:s_136","maybe_no_tell") --Maybe.  I don't think I want to tell you though.
	end

	return pClonedConvScreen
end