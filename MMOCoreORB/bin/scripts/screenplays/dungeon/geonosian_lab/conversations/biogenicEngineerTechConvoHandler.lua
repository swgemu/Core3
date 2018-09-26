local ObjectManager = require("managers.object.object_manager")

--[[
-- Engineer states:
0 - Hasn't talked
1 - Spoke, hasnt accepted
2 - Sent to assistant
3 - Delivered datapad
]]

BiogenicEngineerTechConvoHandler = conv_handler:new {}

function BiogenicEngineerTechConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	if (screenID == "return_didnt_accept") then
		if (GeonosianLab:hasGeoItem(pPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff")) then
			clonedConversation:addOption("@conversation/biogenic_engineertech:s_a7b6a9c7", "oh_yes_codes")
		end
		clonedConversation:addOption("@conversation/biogenic_engineertech:s_a767cb3c", "you_can_help")
		clonedConversation:addOption("@conversation/biogenic_engineertech:s_8e26cc3d", "hope_so_too")
	elseif (screenID == "assistant_codes" or screenID == "find_my_assistant") then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geoEngineerState", 2)
		if (GeonosianLab:hasGeoItem(pPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff")) then
			clonedConversation:addOption("@conversation/biogenic_engineertech:s_da5959ed", "oh_yes_codes")
		end
		clonedConversation:addOption("@conversation/biogenic_engineertech:s_b3d8b98a", "come_back_with_codes")
		clonedConversation:addOption("@conversation/biogenic_engineertech:s_d7f1b726", "thanks_anyway")
	elseif screenID == "init_talk" then
		if (GeonosianLab:hasGeoItem(pPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff")) then
			clonedConversation:addOption("@conversation/biogenic_engineertech:s_a7b6a9c7", "oh_yes_codes")
		end
		clonedConversation:addOption("@conversation/biogenic_engineertech:s_428087e9", "knocked_out_power")
		clonedConversation:addOption("@conversation/biogenic_engineertech:s_56fde3ca", "could_use_help")
		clonedConversation:addOption("@conversation/biogenic_engineertech:s_99c2fa91", "wandered_bad_spot")
		clonedConversation:addOption("@conversation/biogenic_engineertech:s_9d6ccb86", "thanks_for_stopping")
	elseif screenID == "knocked_out_power" or screenID == "could_use_help" or screenID == "wandered_bad_spot" then
		local techState = readData(CreatureObject(pPlayer):getObjectID() .. ":geoEngineerState")
		if (techState == nil or techState == 0) then
			writeData(CreatureObject(pPlayer):getObjectID() .. ":geoEngineerState", 1)
		end
	elseif screenID == "return_init" then
		if (GeonosianLab:hasGeoItem(pPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff")) then
			clonedConversation:addOption("@conversation/biogenic_engineertech:s_da5959ed", "yes_here_are_codes")
		end
		clonedConversation:addOption("@conversation/biogenic_engineertech:s_27707b65", "come_back_when_find")
	elseif (screenID == "yes_here_are_codes" or screenID == "oh_yes_codes") then
		if (GeonosianLab:hasGeoItem(pPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff")) then
			GeonosianLab:removeGeoItem(pPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff")
			GeonosianLab:giveGeoItem(pPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_key.iff")
			writeData(CreatureObject(pPlayer):getObjectID() .. ":geoEngineerState", 3)
		end
	end
	return pConvScreen
end

function BiogenicEngineerTechConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local engineerState = readData(CreatureObject(pPlayer):getObjectID() .. ":geoEngineerState")

	if (engineerState == nil or engineerState == 0) then
		return convoTemplate:getScreen("init_talk")
	elseif (engineerState == 1) then
		return convoTemplate:getScreen("return_didnt_accept")
	elseif (engineerState == 2) then
		return convoTemplate:getScreen("return_init")
	elseif (engineerState == 3) then
		return convoTemplate:getScreen("things_under_control")
	end

	return convoTemplate:getScreen("init_talk")
end
