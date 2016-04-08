local ObjectManager = require("managers.object.object_manager")

huttInformantConvoHandler = Object:new {
}

function huttInformantConvoHandler:destroyDisk(pPlayer)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory ~= nil then
		local pDisk = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff" , true)
		if pDisk ~= nil then
			SceneObject(pDisk):destroyObjectFromWorld()
			SceneObject(pDisk):destroyObjectFromDatabase()
		end
		local pLoot = giveItem(pInventory, "object/weapon/ranged/grenade/grenade_cryoban.iff", -1)
		if (pLoot == nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item grenade_cryoban.iff")
		return
		end
	end
	writeScreenPlayData(pPlayer, "BestineElection", "hutt",electionNum)
	return
end

function huttInformantConvoHandler:hasDisk(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	return getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff" , true)
end

function huttInformantConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	if self:hasDisk(pPlayer) then
		return convoTemplate:getScreen("has_item")
	else
		return convoTemplate:getScreen("no_business")
	end
end

function huttInformantConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	if screenID == "take_it" then
		self:destroyDisk(pConversingPlayer)
	end
	return pConversationScreen
end



function huttInformantConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
