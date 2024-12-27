rheaConvoHandler = conv_handler:new {}

function rheaConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local faction = CreatureObject(pPlayer):getFaction()
	--local playerFactionStatus = CreatureObject(pPlayer):getFactionStatus()
	local playerID = CreatureObject(pPlayer):getObjectID()
	--local playerGender = CreatureObject(pPlayer):getGender()

	-- JTL is disabled
	if (not isJtlEnabled()) then
		CreatureObject(pNpc):doAnimation("shake_head_no")

		return convoTemplate:getScreen("no_jtl") -- Sorry, but you don't look like a pilot to me.
	end

	-- Player is Rebel Pilot
	if (SpaceHelpers:isRebelPilot(pPlayer)) then
		CreatureObject(pNpc):doAnimation("wave_on_dismissing")

		return convoTemplate:getScreen("rebel_pilot") -- Greetings, citizen.  Keep your nose clean and we won't have any trouble.
	end

	-- Player is Imperial Pilots
	if (SpaceHelpers:isImperiallPilot(pPlayer)) then
		CreatureObject(pNpc):doAnimation("standing_placate")

		return convoTemplate:getScreen("imperial_pilot") -- Nothing to worry about here, sir.  CorSec has the area well secured.
	end

	if (SpaceHelpers:isNeutralPilot(pPlayer) and not SpaceHelpers:isCorsecSquadron(pPlayer)) then
		CreatureObject(pNpc):doAnimation("point_accusingly")

		return convoTemplate:getScreen("non_corsec_pilot") -- Ah, I've heard of you!  You're not a bad pilot from what I understand. What can the CorSec do for you?
	end


































--[[	//-- [NOTE]
	if (corellia_privateer_trainer_condition_hasVeryFirstQuest (player, npc))
	{
		doAnimationAction (npc, "point_away");

		//-- NPC: You've got your assignment and the control device for your ship in your datapad.  Go to the Starport and access the terminal to launch into space.
		string_id message = new string_id (c_stringFile, "s_9e5f75be");
		int numberOfResponses = 0;

		boolean hasResponse = false;

		//-- PLAYER: An assignment?
		boolean hasResponse0 = false;
		if (corellia_privateer_trainer_condition__defaultCondition (player, npc))
		{
			++numberOfResponses;
			hasResponse = true;
			hasResponse0 = true;
		}

		//-- PLAYER: What ship?
		boolean hasResponse1 = false;
		if (corellia_privateer_trainer_condition__defaultCondition (player, npc))
		{
			++numberOfResponses;
			hasResponse = true;
			hasResponse1 = true;
		}

		//-- PLAYER: Where do I go?
		boolean hasResponse2 = false;
		if (corellia_privateer_trainer_condition__defaultCondition (player, npc))
		{
			++numberOfResponses;
			hasResponse = true;
			hasResponse2 = true;
		}

		//-- PLAYER: And when I'm done?
		boolean hasResponse3 = false;
		if (corellia_privateer_trainer_condition__defaultCondition (player, npc))
		{
			++numberOfResponses;
			hasResponse = true;
			hasResponse3 = true;
		}

		if (hasResponse)
		{
			int responseIndex = 0;
			string_id responses [] = new string_id [numberOfResponses];

			if (hasResponse0)
				responses [responseIndex++] = new string_id (c_stringFile, "s_95d0a1f6");

			if (hasResponse1)
				responses [responseIndex++] = new string_id (c_stringFile, "s_bdd269be");

			if (hasResponse2)
				responses [responseIndex++] = new string_id (c_stringFile, "s_60c4f974");

			if (hasResponse3)
				responses [responseIndex++] = new string_id (c_stringFile, "s_5e4ebfca");

			utils.setScriptVar (player, "conversation.corellia_privateer_trainer.branchId", 1);

			npcStartConversation (player, npc, "corellia_privateer_trainer", message, responses);
		}
		else
		{
			chat.chat (npc, player, message);
		}

		return SCRIPT_CONTINUE;
	}

			]]





	return convoTemplate:getScreen("hey_ive_heard")
end

function rheaConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local stringFile = "@conversation/rhea"
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)


	return pConvScreen
end

