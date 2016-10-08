local ObjectManager = require("managers.object.object_manager")

GoruConvoHandler = conv_handler:new {
	themePark = nil
}
-- Goru screenplay states: 1: Quest started, 2: turned in zicx, 4: turned in bile, 8: completed
function GoruConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function GoruConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if screenID == "bombs_are_cool" or screenID == "more_info" or screenID == "see_jowir" then
		CreatureObject(pPlayer):setScreenPlayState(1, "zicx_bug_bomb_goruNpc")

		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if pInventory == nil then
			return
		end

		local pItemCheck = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/quest_item_goru_calling_card.iff", true)

		if pItemCheck == nil then
			local pItem = giveItem(pInventory, "object/tangible/loot/quest/quest_item_goru_calling_card.iff", -1)
			SceneObject(pItem):sendTo(pPlayer)
		end

	elseif screenID == "fine_quit_then" or screenID == "go_away_then" then
		CreatureObject(pPlayer):removeScreenPlayState(1, "zicx_bug_bomb_goruNpc")
		CreatureObject(pPlayer):removeScreenPlayState(2, "zicx_bug_bomb_goruNpc")
		CreatureObject(pPlayer):removeScreenPlayState(4, "zicx_bug_bomb_goruNpc")

		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory == nil) then
			return
		end

		local pItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/quest_item_goru_calling_card.iff", true)

		if pItem ~= nil then
			SceneObject(pItem):destroyObjectFromWorld()
			SceneObject(pItem):destroyObjectFromDatabase()
		end
	elseif screenID == "heres_your_bomb" then
		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory == nil) then
			return
		end

		local pItem = giveItem(pInventory, "object/weapon/ranged/grenade/grenade_bug_bomb.iff", -1)

		if (pItem ~= nil) then
			SceneObject(pItem):sendTo(pPlayer)
		end
		CreatureObject(pPlayer):setScreenPlayState(8, "zicx_bug_bomb_goruNpc")
	end

	return pConvScreen
end

function GoruConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convTemplate = LuaConversationTemplate(pConvTemplate)
	if CreatureObject(pPlayer):hasScreenPlayState(8, "zicx_bug_bomb_goruNpc") then
		return convTemplate:getScreen("please_begone")
	elseif CreatureObject(pPlayer):hasScreenPlayState(2, "zicx_bug_bomb_goruNpc") and CreatureObject(pPlayer):hasScreenPlayState(4, "zicx_bug_bomb_goruNpc") then
		return convTemplate:getScreen("heres_your_bomb")
	elseif CreatureObject(pPlayer):hasScreenPlayState(2, "zicx_bug_bomb_goruNpc") and not CreatureObject(pPlayer):hasScreenPlayState(4, "zicx_bug_bomb_goruNpc") then
		return convTemplate:getScreen("get_the_bile")
	elseif not CreatureObject(pPlayer):hasScreenPlayState(2, "zicx_bug_bomb_goruNpc") and CreatureObject(pPlayer):hasScreenPlayState(4, "zicx_bug_bomb_goruNpc") then
		return convTemplate:getScreen("get_the_bugs")
	elseif CreatureObject(pPlayer):hasScreenPlayState(1, "zicx_bug_bomb_goruNpc") then
		return convTemplate:getScreen("are_you_done")
	else
		-- initial talk
		return convTemplate:getScreen("omg_dont_kill_me")
	end
end
