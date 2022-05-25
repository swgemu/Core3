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
	local extraMission = readData(playerID .. "CoA3:extraFloraMission:")
	local winningFaction = tonumber(CriesOfAlderaan:getWinningFaction())

	local append = "_w"

	if (winningFaction ~= faction) then
		append = "_l"
	end

	-- Extra/Repeatable Flore Mission
	if (extraMission >= Coa3Screenplay.FLORA_MISSION_ACCEPTED and extraMission < Coa3Screenplay.FLORA_WAREHOUSE_DESTROYED) then
		return convoTemplate:getScreen("init_has_extra_mission")
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	-- Still on main quest
	if (state == Coa3Screenplay.M3_TACTICAL_OFFICER) then
		return convoTemplate:getScreen("init_sent_by_coordinator" .. append)
	elseif (state >= Coa3Screenplay.M3_SENT_TO_WAREHOUSE and state <= Coa3Screenplay.M3_LOOTED_FLORA) then
		return convoTemplate:getScreen("init_has_main_mission")
	elseif (state >= Coa3Screenplay.M3_WAREHOUSE_DESTROYED and state < Coa3Screenplay.M5_COMPLETE) then
		local wayID = readData(playerID .. ":CoA3:ReturnWaypoint:")

		if (pGhost ~= nil) then
			PlayerObject(pGhost):removeWaypoint(wayID, true)
		end

		return convoTemplate:getScreen("init_completed_flora" .. append)
	end

	if (pGhost ~= nil) then
		-- Repeat Flora Mission
		if (PlayerObject(pGhost):hasBadge(EVENT_COA3_REBEL) or PlayerObject(pGhost):hasBadge(EVENT_COA3_IMPERIAL)) then
			deleteData(playerID .. "CoA3:extraFloraMission:")
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
	local factionString = Coa3Screenplay:getFactionString(pNpc)
	local stateKey = Coa3Screenplay:getStateKey(faction)
	local state = CriesOfAlderaan:getState(pPlayer, stateKey)
	local playerID = SceneObject(pPlayer):getObjectID()
	local winningFaction = tonumber(CriesOfAlderaan:getWinningFaction())

	local append = "_w"

	if (winningFaction == FACTIONIMPERIAL) then
		append = "_l"
	end

	-- Give Warehouse mission
	if (screenID == ("jabba_warehouses")) then
		Coa3Screenplay:abortMission(pPlayer, Coa3Screenplay.FLORA_MISSION, 0)

		CriesOfAlderaan:setState(pPlayer, stateKey, Coa3Screenplay.M3_SENT_TO_WAREHOUSE)
		Coa3Screenplay:setupMission(pPlayer, pNpc, factionString, 3)
	elseif (screenID == ("moisture_farmer")) then
		Coa3Screenplay:abortMission(pPlayer, Coa3Screenplay.FLORA_MISSION, 0)
		CriesOfAlderaan:setState(pPlayer, stateKey, Coa3Screenplay.M3_TACTICAL_OFFICER)

	-- Accepting extra flora mission or resetting
	elseif (screenID == ("go_get_it") or screenID == ("maybe_took_care")) then
		Coa3Screenplay:abortMission(pPlayer, Coa3Screenplay.FLORA_MISSION, 0)

		writeData(playerID .. "CoA3:extraFloraMission:", Coa3Screenplay.FLORA_MISSION_ACCEPTED)
		Coa3Screenplay:setupMission(pPlayer, pNpc, factionString, 3)
	elseif (screenID == ("appreciate_the_offer")) then
		deleteData(playerID .. "CoA3:extraFloraMission:")
		Coa3Screenplay:abortMission(pPlayer, Coa3Screenplay.FLORA_MISSION, 0)
	end

	return pConvScreen
end