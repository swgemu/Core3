local ObjectManager = require("managers.object.object_manager")

coa3TacticalOfficerConvoHandler = conv_handler:new {}

function coa3TacticalOfficerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil) then
		return convoTemplate:getScreen("init_default")
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local faction = CreatureObject(pNpc):getFaction()
	local stateKey = Coa3Screenplay:getStateKey(faction)
	local state = CriesOfAlderaan:getState(pPlayer, stateKey)
	local playerID = SceneObject(pPlayer):getObjectID()

	local append = "_w"

	if (CriesOfAlderaan:getWinningFaction() ~= faction) then
		append = "_l"
	end

	print("coa3TacticalOfficerConvoHandler  -- state: " .. state .. " with append " .. append)

	if (state == Coa3Screenplay.M3_TACTICAL_OFFICER) then
		return convoTemplate:getScreen("init_sent_by_coordinator" .. append)
	elseif (state >= Coa3Screenplay.M3_SENT_TO_WAREHOUSE and state <= Coa3Screenplay.M3_LOOTED_FLORA) then
		return convoTemplate:getScreen("init_has_main_mission")
	elseif (state >= Coa3Screenplay.M3_WAREHOUSE_DESTROYED) then
		return convoTemplate:getScreen("init_completed_flora" .. append)
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		-- Repeat Flora Mission
		if (PlayerObject(pGhost):hasBadge(EVENT_COA3_REBEL) or PlayerObject(pGhost):hasBadge(EVENT_COA3_IMPERIAL)) then
			return convoTemplate:getScreen("init_completed_everything" .. append)
		end
	end

	return convoTemplate:getScreen("init_default")
end

function coa3TacticalOfficerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local faction = CreatureObject(pNpc):getFaction()
	local stateKey = Coa3Screenplay:getStateKey(faction)
	local state = CriesOfAlderaan:getState(pPlayer, stateKey)
	local playerID = SceneObject(pPlayer):getObjectID()

	local append = "_w"

	if (CriesOfAlderaan:getWinningFaction() == FACTIONIMPERIAL) then
		append = "_l"
	end

	-- Give Warehouse mission
	if (screenID == ("jabba_warehouses") or screenID == ("maybe_took_care")) then
		Coa3Screenplay:abortMission(pPlayer,  Coa3Screenplay.FLORA_MISSION, 0)

		CriesOfAlderaan:setState(pPlayer, stateKey, Coa3Screenplay.M3_SENT_TO_WAREHOUSE)
		Coa3Screenplay:setupMission(pPlayer, pNpc, "rebel", 3)
	elseif (screenID == ("moisture_farmer")) then
		Coa3Screenplay:abortMission(pPlayer,  Coa3Screenplay.FLORA_MISSION, 0)
		CriesOfAlderaan:setState(pPlayer, stateKey, Coa3Screenplay.M3_TACTICAL_OFFICER)
	end

	return pConvScreen
end