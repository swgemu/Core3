local ObjectManager = require("managers.object.object_manager")

huttInformantConvoHandler = conv_handler:new {
}

function huttInformantConvoHandler:destroyDisk(pPlayer)
	if pPlayer ~= nil then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if pInventory ~= nil then
			local hDisk = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff" , true)
			if hDisk ~= nil then
				local electionNum = BestineElectionScreenPlay:getElectionNumber()
				SceneObject(hDisk):destroyObjectFromWorld()
				SceneObject(hDisk):destroyObjectFromDatabase()
				writeScreenPlayData(pPlayer, "BestineElection", "hutt", electionNum)
				seanTrenwellConvoHandler:removeHistoryQuest(pPlayer)
			end

			local reward = giveItem(pInventory, "object/weapon/ranged/grenade/grenade_cryoban.iff", -1)
			if (reward == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item grenade_cryoban.iff")
				return
			end
		end
	end
end

function huttInformantConvoHandler:hasDisk(pPlayer)
	if (pPlayer ~= nil) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		return getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff" , true)
	end

	return false
end

function huttInformantConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if screenID == "take_it" then
		self:destroyDisk(pPlayer)
	end

	return pConvScreen
end

function huttInformantConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (not BestineElectionScreenPlay:isElectionEnabled()) then
			return convoTemplate:getScreen("no_business")
	end

	if self:hasDisk(pPlayer) then
		return convoTemplate:getScreen("has_item")
	else
		return convoTemplate:getScreen("no_business")
	end
end
