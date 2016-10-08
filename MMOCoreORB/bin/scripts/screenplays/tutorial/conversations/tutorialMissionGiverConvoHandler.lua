local ObjectManager = require("managers.object.object_manager")

tutorialMissionGiverConvoHandler = conv_handler:new {}

function tutorialMissionGiverConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local playerID = SceneObject(pPlayer):getObjectID()
	if (screenID == "get_moving") then
		writeData(playerID .. ":tutorial:hasGottenMission", 1)
		local pGhost = CreatureObject(pPlayer):getPlayerObject()
		local quartermasterID = readData(playerID .. ":tutorial:roomElevenQuartermaster")
		local pQuartermaster = getSceneObject(quartermasterID)

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if pInventory == nil then
			return pConvScreen
		end

		local pInvItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/dungeon/death_watch_bunker/viewscreen_s2.iff", false)

		if pGhost ~= nil and pQuartermaster ~= nil and pInvItem == nil then
			local pItem = giveItem(pInventory, "object/tangible/loot/dungeon/death_watch_bunker/viewscreen_s2.iff", -1)
			
			if (pItem ~= nil) then
				SceneObject(pItem):setCustomObjectName("Release Documents")
			end
		end
		CreatureObject(pNpc):clearOptionBit(CONVERSABLE)
		TutorialScreenPlay:handleRoomTen(pPlayer)
	end

	return pConvScreen
end
