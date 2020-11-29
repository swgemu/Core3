local ObjectManager = require("managers.object.object_manager")

--[[ Visions Screenplay States
0 - Has not spoken with informant
1 - Accepted to speak with manager on Yavin
2 - Spoken with mannager of faction on yavin and accepted to find items
3 - Turned in Items for rewards
]]

VisionsJohnRoy_convo_handler = conv_handler:new {}

function VisionsJohnRoy_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	local visionsState = readData(CreatureObject(pPlayer):getObjectID() .. ":visionsState")
	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	local playerID = SceneObject(pPlayer):getObjectID()

	if (screenID == "Response_01" or screenID == "Response_02") then

		--deleteData(playerID .. ":visionsState", 1)
		writeData(playerID .. ":visionsState", 2)

		local visionsWpID_2 = PlayerObject(pGhost):addWaypoint("yavin4", "Deathstar Wreckage", "Deathstar Wreckage", 1921, -3040, WAYPOINT_COLOR_PURPLE, true, true, 0)

		if visionsWpID_2 ~= nil then
			writeData(playerID .. ":visionsWpID_2:", visionsWpID_2)
		end
	end

	if (screenID == "Turnin_Response_01" or screenID == "Turnin_Response_02") then
		if VisionsOfThePast:hasCollectionItem(pPlayer) then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

			if SceneObject(pInventory):isContainerFullRecursive() then
				local text = clonedConversation:getOptionText(0)
				clonedConversation:removeAllOptions()
				clonedConversation:addOption(text, "Cant_Give_Reward")
				return pConvScreen
			end

			local wpID_1 = readData(playerID .. ":visionsWpID_1:")
			local wpID_2 = readData(playerID .. ":visionsWpID_2:")

			writeData(playerID .. ":visionsState", 3)
			ThemeParkLogic:giveFaction(pPlayer, "rebel", 2000)
			createLoot(pPlayer, "visions_reward_loot_group", 1, false)
			PlayerObject(pGhost):removeWaypoint(wpID_1, true)
			PlayerObject(pGhost):removeWaypoint(wpID_2, true)
			deleteData(playerID .. ":visionsWpID_1:")
			deleteData(playerID .. ":visionsWpID_2:")
			giveItem(pInventory, "object/tangible/furniture/jedi/frn_all_table_light_01.iff", -1)
						
		end
	end
	return pConvScreen
end

function VisionsJohnRoy_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local playerFaction = CreatureObject(pPlayer):getFaction()
	local playerID = SceneObject(pPlayer):getObjectID()
	local visionsState = readData(playerID .. ":visionsState")
	local visionsImperialStatus = readData(playerID .. ":visionsImperialHelper")

	if (playerFaction == FACTIONIMPERIAL or visionsImperialStatus == 1) then
		return convoTemplate:getScreen("Deny_Faction")
	end

	if visionsState == 3 then
		return convoTemplate:getScreen("Service_Noted")
	elseif (visionsState == 2 and VisionsOfThePast:hasCollectionItem(pPlayer) == true) then
		return convoTemplate:getScreen("TurnIn")
	elseif visionsState == 2 then
		return convoTemplate:getScreen("Time_Wasted")
	elseif visionsState == 1 then
		return convoTemplate:getScreen("InitialConvo")
	end
	return convoTemplate:getScreen("Deny_Faction")
end
