local SpaceHelpers = require("utils.space_helpers")

v3fxConvoHandler = conv_handler:new {}

function v3fxConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil or pConvTemplate == nil) then
		return nil
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local faction = CreatureObject(pPlayer):getFaction()
	local playerID = CreatureObject(pPlayer):getObjectID()

	-- JTL is disabled
	if (not isJtlEnabled()) then
		return convoTemplate:getScreen("no_jtl")
	end

	-- Player is Imperial Pilot
	if (SpaceHelpers:isImperialPilot(pPlayer)) then
		return convoTemplate:getScreen("imperial_pilot")
	-- Player is Neutral Pilot
	elseif (SpaceHelpers:isNeutralPilot(pPlayer)) then
		return convoTemplate:getScreen("neutral_pilot")
	end

	local isRebelPilot = SpaceHelpers:isRebelPilot(pPlayer)

	-- Player is a Rebel Pilot but not Vortex Squadron
	if (isRebelPilot and not SpaceHelpers:isVortexSquadron(pPlayer)) then
		return convoTemplate:getScreen("non_vortex_pilot")
	end

	-- Not a Rebel pilot yet
	if (not isRebelPilot) then
		return convoTemplate:getScreen("not_yet_pilot")
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("no_jtl")
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return convoTemplate:getScreen("no_jtl")
	end

	-- Player hasn't completed Tier 2
	if (not SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 2)) then
		return convoTemplate:getScreen("not_tier2_complete")
	end

	local questOneStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, VortexSquadronScreenplay.TIER3_QUEST_STRING_1.type, VortexSquadronScreenplay.TIER3_QUEST_STRING_1.name)
	local questTwoStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, VortexSquadronScreenplay.TIER3_QUEST_STRING_2.type, VortexSquadronScreenplay.TIER3_QUEST_STRING_2.name)
	local questThreeStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, VortexSquadronScreenplay.TIER3_QUEST_STRING_3.type, VortexSquadronScreenplay.TIER3_QUEST_STRING_3.name)
	local questFourStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, VortexSquadronScreenplay.TIER3_QUEST_STRING_4.type, VortexSquadronScreenplay.TIER3_QUEST_STRING_4.name)

	local questOneComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, VortexSquadronScreenplay.TIER3_QUEST_STRING_1.type, VortexSquadronScreenplay.TIER3_QUEST_STRING_1.name)
	local questTwoComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, VortexSquadronScreenplay.TIER3_QUEST_STRING_2.type, VortexSquadronScreenplay.TIER3_QUEST_STRING_2.name)
	local questThreeComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, VortexSquadronScreenplay.TIER3_QUEST_STRING_3.type, VortexSquadronScreenplay.TIER3_QUEST_STRING_3.name)
	local questFourComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, VortexSquadronScreenplay.TIER3_QUEST_STRING_4.type, VortexSquadronScreenplay.TIER3_QUEST_STRING_4.name)

	-- Player has an active story quest from V3-FX
	if ((questOneStarted and not questOneComplete) or (questTwoStarted and not questTwoComplete) or (questThreeStarted and not questThreeComplete) or (questFourStarted and not questFourComplete)) then
		return convoTemplate:getScreen("has_mission")
	-- Check if players have all the tier3 skill boxes, send them to next trainer
	elseif (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 3)) then
		return convoTemplate:getScreen("completed_v3fx")
	-- Player has finished quest 4 and has received the reward (last tier 3 skill box)
	elseif (questFourComplete and getQuestStatus(playerID .. VortexSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":reward") == "1") then
		return convoTemplate:getScreen("missions_complete")
	-- Player has completed quest 4 and needs skill reward
	elseif (questFourComplete and getQuestStatus(playerID .. VortexSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. VortexSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":reward", 1)

		-- Grant Tier 3 skill box (no XP deduction for Tier 3)
		SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_droid_03", false)

		-- Grant Faction Standing
		CreatureObject(pPlayer):addFactionPoints("rebel", 300, false)

		-- Increment pilot tier if all tier 3 skills are complete
		if (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 3) and ghost:getPilotTier() == 3) then
			ghost:incrementPilotTier()
		end

		return convoTemplate:getScreen("missions_complete")
	-- Player has finished quest 3 and needs to start quest 4
	elseif (questThreeComplete and not questFourStarted and getQuestStatus(playerID .. VortexSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work3")
	-- Player has completed quest 3 and needs reward
	elseif (questThreeComplete and getQuestStatus(playerID .. VortexSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. VortexSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":reward", 1)

		-- Grant Tier 3 skill box (no XP deduction for Tier 3)
		SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_procedures_03", false)

		CreatureObject(pPlayer):addFactionPoints("rebel", 200, false)

		-- Increment pilot tier if all tier 3 skills are complete
		if (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 3) and ghost:getPilotTier() == 3) then
			ghost:incrementPilotTier()
		end

		return convoTemplate:getScreen("excellent_work3")
	-- Player has finished quest 2 and needs to start quest 3
	elseif (questTwoComplete and not questThreeStarted and getQuestStatus(playerID .. VortexSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work2")
	-- Player has completed quest 2 and needs reward
	elseif (questTwoComplete and getQuestStatus(playerID .. VortexSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. VortexSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":reward", 1)

		-- Grant Tier 3 skill box (no XP deduction for Tier 3)
		SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_weapons_03", false)

		CreatureObject(pPlayer):addFactionPoints("rebel", 150, false)

		-- Increment pilot tier if all tier 3 skills are complete
		if (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 3) and ghost:getPilotTier() == 3) then
			ghost:incrementPilotTier()
		end

		return convoTemplate:getScreen("excellent_work2")
	-- Player has finished quest 1 and needs to start quest 2
	elseif (questOneComplete and not questTwoStarted and getQuestStatus(playerID .. VortexSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work")
	-- Player has finished quest 1 and needs reward
	elseif (questOneComplete and getQuestStatus(playerID .. VortexSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. VortexSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":reward", 1)

		-- Grant Tier 3 skill box (no XP deduction for Tier 3)
		SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_starships_03", false)

		CreatureObject(pPlayer):addFactionPoints("rebel", 100, false)

		-- Increment pilot tier if all tier 3 skills are complete
		if (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 3) and ghost:getPilotTier() == 3) then
			ghost:incrementPilotTier()
		end

		return convoTemplate:getScreen("excellent_work")
	-- Player is new to V3-FX
	elseif (not questOneComplete) then
		return convoTemplate:getScreen("introduction")
	end

	return convoTemplate:getScreen("no_jtl")
end

function v3fxConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pConvScreen == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pClonedScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pClonedScreen)

	clonedConversation:setDialogTextTU(CreatureObject(pPlayer):getFirstName())

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pClonedScreen
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return pClonedScreen
	end

	local playerID = CreatureObject(pPlayer):getObjectID()

	if (screenID == "accept_mission") then
		recovery_naboo_rebel_tier3_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission2") then
		inspect_naboo_rebel_tier3_2:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission3") then
		delivery_naboo_rebel_tier3_3:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission4") then
		assassinate_naboo_rebel_tier3_4:startQuest(pPlayer, pNpc)
	elseif (screenID == "goodbye") then
		CreatureObject(pNpc):doAnimation("goodbye")
	end

	return pClonedScreen
end
