local ObjectManager = require("managers.object.object_manager")

GoruConvoHandler = Object:new {
	themePark = nil
}
-- Goru screenplay states: 1: Quest started, 2: turned in zicx, 4: turned in bile, 8: completed
function GoruConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function GoruConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	return ObjectManager.withCreatureObject(conversingPlayer, function(player)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)

		if screenID == "bombs_are_cool" or screenID == "more_info" or screenID == "see_jowir" then
			self.themePark:setState(player, 1, "zicx_bug_bomb_goruNpc")
			local pInventory = player:getSlottedObject("inventory")
			if pInventory == nil then
				return false
			end
			local pItemCheck = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/quest_item_goru_calling_card.iff", true)
			if pItemCheck == nil then
				local pItem = giveItem(pInventory, "object/tangible/loot/quest/quest_item_goru_calling_card.iff", -1)
				SceneObject(pItem):sendTo(conversingPlayer)
			end
		elseif screenID == "fine_quit_then" or screenID == "go_away_then" then
			self.themePark:removeState(player, 1, "zicx_bug_bomb_goruNpc")
			self.themePark:removeState(player, 2, "zicx_bug_bomb_goruNpc")
			self.themePark:removeState(player, 4, "zicx_bug_bomb_goruNpc")
			local pInventory = player:getSlottedObject("inventory")
			local pItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/quest_item_goru_calling_card.iff", true)
			if pItem ~= nil then
				SceneObject(pItem):destroyObjectFromWorld()
				SceneObject(pItem):destroyObjectFromDatabase()
			end
		elseif screenID == "heres_your_bomb" then
			local pInventory = player:getSlottedObject("inventory")
			local pItem = giveItem(pInventory, "object/weapon/ranged/grenade/grenade_bug_bomb.iff", -1)
			if (pItem ~= nil) then
				SceneObject(pItem):sendTo(conversingPlayer)
			end
			self.themePark:setState(player, 8, "zicx_bug_bomb_goruNpc")
		end
		return conversationScreen
	end)
end


function GoruConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureObject(pPlayer, function(conversingPlayer)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)
		if conversingPlayer:hasScreenPlayState(8, "zicx_bug_bomb_goruNpc") == 1 then
			return convoTemplate:getScreen("please_begone")
		elseif conversingPlayer:hasScreenPlayState(2, "zicx_bug_bomb_goruNpc") == 1 and conversingPlayer:hasScreenPlayState(4, "zicx_bug_bomb_goruNpc") == 1 then
			return convoTemplate:getScreen("heres_your_bomb")
		elseif conversingPlayer:hasScreenPlayState(2, "zicx_bug_bomb_goruNpc") == 1 and conversingPlayer:hasScreenPlayState(4, "zicx_bug_bomb_goruNpc") ~= 1 then
			return convoTemplate:getScreen("get_the_bile")
		elseif conversingPlayer:hasScreenPlayState(2, "zicx_bug_bomb_goruNpc") ~= 1 and conversingPlayer:hasScreenPlayState(4, "zicx_bug_bomb_goruNpc") == 1 then
			return convoTemplate:getScreen("get_the_bugs")
		elseif conversingPlayer:hasScreenPlayState(1, "zicx_bug_bomb_goruNpc") == 1 then
			return convoTemplate:getScreen("are_you_done")
		else
			-- initial talk
			return convoTemplate:getScreen("omg_dont_kill_me")
		end
	end)
end

function GoruConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local pConversationSession = player:getConversationSession()
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
	end)
end

function GoruConvoHandler:writeObjectData(objectID, key, value, questGiver)
	writeData(objectID .. ":" .. questGiver .. ":" .. key, value)
end

function GoruConvoHandler:readObjectData(objectID, key, questGiver)
	return readData(objectID .. ":" .. questGiver .. ":" .. key)
end

function GoruConvoHandler:deleteObjectData(objectID, key, questGiver)
	deleteData(objectID .. ":" .. questGiver .. ":" .. key)
end