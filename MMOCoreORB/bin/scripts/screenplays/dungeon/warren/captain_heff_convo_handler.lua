local ObjectManager = require("managers.object.object_manager")

CaptainHeffConversationHandler = Object:new {}

function CaptainHeffConversationHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "heff_1") then
		ObjectManager.withCreaturePlayerObject(pConversingPlayer, function(playerObject)
			playerObject:awardBadge(39)

			local pDatapad = SceneObject(pConversingPlayer):getSlottedObject("datapad")

			if (pDatapad ~= nil) then
				for i = 1, 4, 1 do
					local pEvidence = getContainerObjectByTemplate(pDatapad, "object/intangible/data_item/warren_evidence_0" .. i .. ".iff", false)
					if (pEvidence ~= nil) then
						SceneObject(pEvidence):destroyObjectFromWorld()
						SceneObject(pEvidence):destroyObjectFromDatabase()
					end
				end

				local pKey = getContainerObjectByTemplate(pDatapad, "object/intangible/data_item/warren_encryption_key.iff", false)

				if (pKey ~= nil) then
					SceneObject(pKey):destroyObjectFromWorld()
					SceneObject(pKey):destroyObjectFromDatabase()
				end
			end
		end)
	end

	return pConversationScreen
end

function CaptainHeffConversationHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	return ObjectManager.withCreaturePlayerObject(pPlayer, function(playerObject)
		if (playerObject:hasBadge(39)) then
			return convoTemplate:getScreen("heff_done")
		else
			local pDatapad = SceneObject(pPlayer):getSlottedObject("datapad")

			if (pDatapad ~= nil) then
				local pEvidence1 = getContainerObjectByTemplate(pDatapad, "object/intangible/data_item/warren_evidence_01.iff", false)
				local pEvidence2 = getContainerObjectByTemplate(pDatapad, "object/intangible/data_item/warren_evidence_02.iff", false)
				local pEvidence3 = getContainerObjectByTemplate(pDatapad, "object/intangible/data_item/warren_evidence_03.iff", false)
				local pEvidence4 = getContainerObjectByTemplate(pDatapad, "object/intangible/data_item/warren_evidence_04.iff", false)
				local pEvidence5 = getContainerObjectByTemplate(pDatapad, "object/intangible/data_item/warren_encryption_key.iff", false)

				if (pEvidence1 ~= nil) and (pEvidence2 ~= nil) and (pEvidence3 ~= nil) and (pEvidence4 ~= nil) and (pEvidence5 ~= nil) then
					return convoTemplate:getScreen("heff_start")
				end
			end
		end
		return convoTemplate:getScreen("heff_bye")
	end)
end

function CaptainHeffConversationHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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