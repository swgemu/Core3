local SpaceHelpers = require("utils.space_helpers")

arkonConvoHandler = conv_handler:new {}

function arkonConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	-- Player is a Rebel Pilot but not Havoc Squadron
	if (isRebelPilot and not SpaceHelpers:isHavocSquadron(pPlayer)) then
		return convoTemplate:getScreen("non_havoc_pilot")
	-- Player is not a Rebel pilot
	elseif (not isRebelPilot) then
		return convoTemplate:getScreen("not_rebel_pilot")
	end

	-- Check if player has completed Tier 2
	if (not SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 2)) then
		return convoTemplate:getScreen("not_ready")
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("no_jtl")
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return convoTemplate:getScreen("no_jtl")
	end

	local questOneStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_1.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_1.name)
	local questTwoStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_2.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_2.name)
	local questThreeStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_3.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_3.name)
	local questFourStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_4.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_4.name)

	local questOneComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_1.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_1.name)
	local questTwoComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_2.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_2.name)
	local questThreeComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_3.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_3.name)
	local questFourComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_4.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_4.name)

	-- Player has an active quest from Arkon
	if ((questOneStarted and not questOneComplete) or (questTwoStarted and not questTwoComplete) or (questThreeStarted and not questThreeComplete) or (questFourStarted and not questFourComplete)) then
		return convoTemplate:getScreen("has_mission")
	-- Check if players have all the tier3 skill boxes, send them to next trainer
	elseif (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 3)) then
		return convoTemplate:getScreen("completed_arkon")
	-- Player has finished quest 4 and has received the reward (skill)
	elseif (questFourComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":reward") == "1") then
		return convoTemplate:getScreen("all_missions_complete")
	-- Player has completed quest 4 and needs skill reward
	elseif (questFourComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":reward", 1)

		-- Tier 3 grants skill box directly (no XP deduction)
		SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_weapons_03", false)

		-- Grant Faction Standing
		CreatureObject(pPlayer):addFactionPoints("rebel", 250, false)

		-- Check if all Tier 3 complete, increment tier
		if (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 3) and ghost:getPilotTier() == 3) then
			ghost:incrementPilotTier()
		end

		return convoTemplate:getScreen("all_missions_complete")
	-- Player has finished quest 3 and needs to start quest 4
	elseif (questThreeComplete and not questFourStarted and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work3")
	-- Player has completed quest 3 and needs skill reward
	elseif (questThreeComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":reward", 1)

		-- Grant skill directly
		SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_starships_03", false)

		CreatureObject(pPlayer):addFactionPoints("rebel", 200, false)

		return convoTemplate:getScreen("excellent_work3")
	-- Player has finished quest 2 and needs to start quest 3
	elseif (questTwoComplete and not questThreeStarted and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work2")
	-- Player has completed quest 2 and needs skill reward
	elseif (questTwoComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":reward", 1)

		-- Grant skill directly
		SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_procedures_03", false)

		CreatureObject(pPlayer):addFactionPoints("rebel", 200, false)

		return convoTemplate:getScreen("excellent_work2")
	-- Player has finished quest 1 and needs to start quest 2
	elseif (questOneComplete and not questTwoStarted and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work")
	-- Player has finished quest 1 and needs skill reward
	elseif (questOneComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":reward", 1)

		-- Grant skill directly
		SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_droid_03", false)

		CreatureObject(pPlayer):addFactionPoints("rebel", 150, false)

		return convoTemplate:getScreen("excellent_work")
	-- New pilot to Arkon
	elseif (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":attempted") ~= "1") then
		return convoTemplate:getScreen("introduction")
	-- Player needs to start/restart quest 1
	elseif (not questOneComplete) then
		return convoTemplate:getScreen("start_mission1")
	end

	return convoTemplate:getScreen("no_jtl")
end

function arkonConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pConvScreen == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pClonedScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pClonedScreen)

	clonedConversation:setDialogTextTU(CreatureObject(pPlayer):getFirstName())

	local playerID = CreatureObject(pPlayer):getObjectID()

	if (screenID == "accept_mission") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":attempted", 1)

		recovery_corellia_rebel_tier3_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission2") then
		inspect_corellia_rebel_tier3_2:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission3") then
		delivery_corellia_rebel_tier3_3:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission4") then
		assassinate_corellia_rebel_tier3_4:startQuest(pPlayer, pNpc)
	elseif (screenID == "goodbye") then
		CreatureObject(pNpc):doAnimation("goodbye")
	end

	return pClonedScreen
end
