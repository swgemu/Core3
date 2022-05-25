local ObjectManager = require("managers.object.object_manager")

coa3LeiaConvoHandler = conv_handler:new {}

function coa3LeiaConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local creatureFaction = CreatureObject(pNpc):getFaction()
	local stateKey = Coa3Screenplay:getStateKey(creatureFaction)
	local state = CriesOfAlderaan:getState(pPlayer, stateKey)

	if (state == Coa3Screenplay.M4_COMMANDER) then
		if (not CreatureObject(pPlayer):isRebel() or CreatureObject(pPlayer):isOnLeave()) then
			return convoTemplate:getScreen("wrong_faction")
		end

		return convoTemplate:getScreen("init_sent_by_coordinator")
	elseif (state == Coa3Screenplay.M5_GO_TO_FACILITY or state == Coa3Screenplay.M5_DEFENDING) then
		if (not CreatureObject(pPlayer):isRebel() or CreatureObject(pPlayer):isOnLeave()) then
			return convoTemplate:getScreen("wrong_faction")
		end

		return convoTemplate:getScreen("init_in_progress")
	elseif (state == Coa3Screenplay.M5_COMPLETE) then
		return convoTemplate:getScreen("init_completed_everything")
	end

	return convoTemplate:getScreen("init_default")
end

function coa3LeiaConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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

	if (screenID == "research_stations" or screenID == "datapad_troubles") then
		Coa3Screenplay:abortMission(pPlayer, Coa3Screenplay.COMMANDER_MISSION, 0)
		CriesOfAlderaan:setState(pPlayer, stateKey, Coa3Screenplay.M5_GO_TO_FACILITY)

		Coa3Screenplay:spawnCommanderObjective(pPlayer, pNpc, "rebel")
	elseif (screenID == "sorry_to_hear") then
		Coa3Screenplay:abortMission(pPlayer, Coa3Screenplay.COMMANDER_MISSION, 0)
		CriesOfAlderaan:setState(pPlayer, stateKey, Coa3Screenplay.M4_COMMANDER)
	end

	return pConvScreen
end