local ObjectManager = require("managers.object.object_manager")

--[[
Assistant states
0 - Hasn't spoken to
1 - Spoke but didnt accept datapad
2 - Has datapad, sent to engineer
]]
BiogenicAssistantConvoHandler = conv_handler:new {}

function BiogenicAssistantConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local engineerState = readData(CreatureObject(pPlayer):getObjectID() .. ":geoEngineerState")

	if (engineerState == nil) then
		engineerState = 0
	end

	if screenID == "i_have_these_codes" or screenID == "dont_know_much" then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geoAssistantState", 1)

		if (screenID == "i_have_these_codes") then
			if (engineerState == 2) then
				clonedConversation:addOption("@conversation/biogenic_assistant:s_114e560", "really_take_them_back")
			else
				clonedConversation:addOption("@conversation/biogenic_assistant:s_33eb85b5", "really_fantastic")
			end

			clonedConversation:addOption("@conversation/biogenic_assistant:s_eeaf9e0b", "ok_i_understand")
		end
	elseif screenID == "codes_for_reactor" then
		if (engineerState == 2) then
			clonedConversation:addOption("@conversation/biogenic_assistant:s_89ca9e86", "really_take_them_back")
		else
			clonedConversation:addOption("@conversation/biogenic_assistant:s_761ee240", "really_fantastic")
		end

		clonedConversation:addOption("@conversation/biogenic_assistant:s_72510ac3", "i_hope_so")
	elseif screenID == "really_fantastic" or screenID == "really_take_back_datapad" or screenID == "really_take_them_back" then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geoAssistantState", 2)
		GeonosianLab:giveGeoItem(pPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff")
	end
	return pConvScreen
end

function BiogenicAssistantConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local assistantState = readData(CreatureObject(pPlayer):getObjectID() .. ":geoAssistantState")
	local engineerState = readData(CreatureObject(pPlayer):getObjectID() .. ":geoEngineerState")

	if (assistantState == nil) then
		assistantState = 0
	end

	if (engineerState == nil) then
		engineerState = 0
	end

	if (assistantState == 0) then
		return convoTemplate:getScreen("init_talk")
	elseif (engineerState == 3) then
		return convoTemplate:getScreen("thanks_for_delivering")
	elseif (assistantState == 2 and engineerState ~= 3) then
		return convoTemplate:getScreen("please_deliver_codes")
	elseif (assistantState == 1) then
		return convoTemplate:getScreen("back_ask_favor")
	end

	return convoTemplate:getScreen("init_talk")
end
