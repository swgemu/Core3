local ObjectManager = require("managers.object.object_manager")

local CRYSTAL_OBJECT = "object/tangible/loot/quest/force_sensitive/force_crystal.iff"

villageElderConvoHandler = Object:new {}

function villageElderConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function villageElderConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local state = CreatureObject(pPlayer):getScreenPlayState("VillageElderScreenPlay")
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (state == 1) then
		return convoTemplate:getScreen("intro")
	else
		return convoTemplate:getScreen("greetings")
	end
end

function villageElderConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "intro") then
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		local pInventory = CreatureObject(pConversingPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local pInvItem = getContainerObjectByTemplate(pInventory, CRYSTAL_OBJECT, true)

			if (pInvItem ~= nil) then
				clonedConversation:addOption("@conversation/village_elder_1:s_9dc8bf5d", "already_have_crystal")
			else
				clonedConversation:addOption("@conversation/village_elder_1:s_9dc8bf5d", "give_new_crystal")
			end
		end
		return conversationScreen
	elseif (screenID == "give_new_crystal") then
		local pInventory = CreatureObject(pConversingPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local pItem = getContainerObjectByTemplate(pInventory, CRYSTAL_OBJECT, true)

			if (pItem == nil) then
				if (SceneObject(pInventory):isContainerFullRecursive()) then
					CreatureObject(pConversingPlayer):sendSystemMessage("@error_message:inv_full")
				else
					pItem = giveItem(pInventory, CRYSTAL_OBJECT, -1)

					if (pItem == nil) then
						CreatureObject(pConversingPlayer):sendSystemMessage("Error: Unable to generate item.")
					end
				end
			end
		end
	elseif (screenID == "yes_you_might") then
		CreatureObject(pConversingPlayer):setScreenPlayState(1, "VillageElderScreenPlay")
		local pGhost = CreatureObject(pConversingPlayer):getPlayerObject()
		PlayerObject(pGhost):setJediState(1)
		awardSkill(pConversingPlayer, "force_title_jedi_novice")
	end

	return pConversationScreen
end
