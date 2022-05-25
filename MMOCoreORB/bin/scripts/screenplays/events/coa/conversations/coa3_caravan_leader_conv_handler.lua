local ObjectManager = require("managers.object.object_manager")

coa3CaravanLeaderConvoHandler = conv_handler:new {}

function coa3CaravanLeaderConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local playerID = SceneObject(pPlayer):getObjectID()

	local faction = Coa3Screenplay:getFactionString(pPlayer)
	local stateKey = Coa3Screenplay:getStateKey(faction)
	local state = CriesOfAlderaan:getState(pPlayer, stateKey)
	local partStatus = readData(playerID .. ":CoA3:partStatus:")

	if (state == 7) then
		if (partStatus == 0) then
			return convoTemplate:getScreen("init_has_mission")
		elseif (partStatus == 1) then
			if (Coa3Screenplay:hasRepairedGravUnit(pPlayer)) then
				return convoTemplate:getScreen("init_has_part_repaired")
			else
				return convoTemplate:getScreen("init_has_part_not_repaired")
			end
		end
	elseif (state > 7) then
		return convoTemplate:getScreen("init_returned_part")
	end

	return convoTemplate:getScreen("init_wrong_person")
end

function coa3CaravanLeaderConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local playerID = SceneObject(pPlayer):getObjectID()

	local faction = Coa3Screenplay:getFactionString(pPlayer)
	local stateKey = Coa3Screenplay:getStateKey(faction)

	if (screenID == "heres_the_part") then
		writeData(playerID .. ":CoA3:partStatus:", 1)
		Coa3Screenplay:giveBrokenUnit(pPlayer)
	elseif (screenID == "take_this_disc") then
		Coa3Screenplay:giveDisk(pPlayer)
		CriesOfAlderaan:setState(pPlayer, "coa3_" .. faction, Coa3Screenplay.M2_RETURNED_UNIT)

		ThemeParkLogic:giveFaction(pPlayer, "jabba", 200)
		Coa3Screenplay:abortMission(pPlayer, 1, 1)
	end

	return pConvScreen
end