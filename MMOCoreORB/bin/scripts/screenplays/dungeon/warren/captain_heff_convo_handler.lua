local ObjectManager = require("managers.object.object_manager")

CaptainHeffConversationHandler = conv_handler:new {}

function CaptainHeffConversationHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pConvScreen
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "heff_1") then
		PlayerObject(pGhost):awardBadge(39)
		PlayerObject(pGhost):increaseFactionStanding("imperial", 500)

		local pDatapad = SceneObject(pPlayer):getSlottedObject("datapad")

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
	end

	return pConvScreen
end

function CaptainHeffConversationHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("heff_bye")
	end

	if (PlayerObject(pGhost):hasBadge(39)) then
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
end
