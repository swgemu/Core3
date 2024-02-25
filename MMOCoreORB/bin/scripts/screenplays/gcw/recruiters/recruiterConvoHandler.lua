local ObjectManager = require("managers.object.object_manager")

RecruiterConvoHandler = conv_handler:new {}

function RecruiterConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pConvScreen
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "greet_member_start_covert" or screenID == "stay_covert" or screenID == "dont_resign_covert") then
		self:updateScreenWithPromotions(pPlayer, pConvTemplate, pConvScreen, recruiterScreenplay:getRecruiterFaction(pNpc))

		if (recruiterScreenplay:getFactionFromHashCode(CreatureObject(pPlayer):getFaction()) == "rebel") then
			clonedConversation:addOption("@conversation/faction_recruiter_rebel:s_480", "faction_purchase")
		else
			clonedConversation:addOption("@conversation/faction_recruiter_imperial:s_324", "faction_purchase")
		end
	elseif (screenID == "greet_member_start_overt" or screenID == "stay_special_forces" or screenID == "stay_overt" or screenID == "dont_resign_overt") then
		self:updateScreenWithPromotions(pPlayer, pConvTemplate, pConvScreen, recruiterScreenplay:getRecruiterFaction(pNpc))
		self:updateScreenWithBribe(pPlayer, pNpc, pConvTemplate, pConvScreen, recruiterScreenplay:getRecruiterFaction(pNpc))

		if (recruiterScreenplay:getFactionFromHashCode(CreatureObject(pPlayer):getFaction()) == "rebel") then
			clonedConversation:addOption("@conversation/faction_recruiter_rebel:s_480", "faction_purchase")
		else
			clonedConversation:addOption("@conversation/faction_recruiter_imperial:s_324", "faction_purchase")
		end
	elseif (screenID == "accept_join") then
		CreatureObject(pPlayer):setFaction(recruiterScreenplay:getRecruiterFactionHashCode(pNpc))
		CreatureObject(pPlayer):setFactionStatus(1)

	elseif (screenID == "accepted_go_overt") then
		CreatureObject(pPlayer):setFutureFactionStatus(2)
		writeData(CreatureObject(pPlayer):getObjectID() .. ":changingFactionStatus", 1)
		createEvent(30000, "recruiterScreenplay", "handleGoOvert", pPlayer, "")
	elseif (screenID == "accepted_go_covert") then
		if (CreatureObject(pPlayer):hasSkill("force_rank_light_novice") or CreatureObject(pPlayer):hasSkill("force_rank_dark_novice")) then
			CreatureObject(pPlayer):sendSystemMessage("@faction_recruiter:jedi_cant_go_covert")
			return
		end

		CreatureObject(pPlayer):setFutureFactionStatus(1)
		writeData(CreatureObject(pPlayer):getObjectID() .. ":changingFactionStatus", 1)
		createEvent(300000, "recruiterScreenplay", "handleGoCovert", pPlayer, "")
	elseif (screenID == "accepted_go_on_leave") then
		if (CreatureObject(pPlayer):hasSkill("force_rank_light_novice") or CreatureObject(pPlayer):hasSkill("force_rank_dark_novice")) then
			CreatureObject(pPlayer):sendSystemMessage("@faction_recruiter:jedi_cant_go_covert")
			return
		end

		CreatureObject(pPlayer):setFutureFactionStatus(0)
		writeData(CreatureObject(pPlayer):getObjectID() .. ":changingFactionStatus", 1)
		createEvent(300000, "recruiterScreenplay", "handleGoOnLeave", pPlayer, "")

	elseif (screenID == "accepted_resign") then
		if (CreatureObject(pPlayer):hasSkill("force_rank_light_novice") or CreatureObject(pPlayer):hasSkill("force_rank_dark_novice")) then
			CreatureObject(pPlayer):sendSystemMessage("@faction_recruiter:jedi_cant_resign")
			return
		end

		CreatureObject(pPlayer):setFutureFactionStatus(0)
		writeData(CreatureObject(pPlayer):getObjectID() .. ":changingFactionStatus", 1)
		createEvent(300000, "recruiterScreenplay", "handleResign", pPlayer, "")
		return pConvScreen

	elseif (screenID == "accepted_resume_duties") then
		CreatureObject(pPlayer):setFutureFactionStatus(1)
		createEvent(30000, "recruiterScreenplay", "handleGoCovert", pPlayer, "")
		writeData(CreatureObject(pPlayer):getObjectID() .. ":changingFactionStatus", 1)

	elseif (screenID == "confirm_promotion") then
		local rank = CreatureObject(pPlayer):getFactionRank() + 1
		clonedConversation:setDialogTextTO("faction_recruiter", getRankName(rank))

	elseif (screenID == "accepted_promotion") then
		local rank = CreatureObject(pPlayer):getFactionRank() + 1
		local requiredPoints = getRankCost(rank)

		if (PlayerObject(pGhost):getFactionStanding(recruiterScreenplay:getRecruiterFaction(pNpc)) < (requiredPoints + recruiterScreenplay:getMinimumFactionStanding())) then
			local convoTemplate = LuaConversationTemplate(pConvTemplate)
			local notEnoughScreen = convoTemplate:getScreen("not_enough_points")
			local screenObject = LuaConversationScreen(notEnoughScreen)

			pConvScreen = screenObject:cloneScreen()

			screenObject = LuaConversationScreen(pConvScreen)
			screenObject:setDialogTextTO("faction_recruiter", getRankName(rank))
			screenObject:setDialogTextDI(requiredPoints)
		else
			PlayerObject(pGhost):decreaseFactionStanding(recruiterScreenplay:getRecruiterFaction(pNpc), requiredPoints)
			CreatureObject(pPlayer):setFactionRank(rank)
		end

	elseif screenID == "confirm_bribe" and CreatureObject(pPlayer):hasSkill("combat_smuggler_underworld_04") and (CreatureObject(pPlayer):getCashCredits() >= 100000)
		and (getFactionPointsCap(CreatureObject(pPlayer):getFactionRank()) >= PlayerObject(pGhost):getFactionStanding(recruiterScreenplay:getRecruiterFaction(pNpc)) + 1250) then
		self:add100kBribeOption(pNpc, clonedConversation)

	elseif (screenID == "accepted_bribe_20k") and CreatureObject(pPlayer):hasSkill("combat_smuggler_underworld_04") and (CreatureObject(pPlayer):getCashCredits() >= 20000)
		and (getFactionPointsCap(CreatureObject(pPlayer):getFactionRank()) >= PlayerObject(pGhost):getFactionStanding(recruiterScreenplay:getRecruiterFaction(pNpc)) + 250) then
		recruiterScreenplay:grantBribe(pNpc, pPlayer, 20000, 250)

	elseif (screenID == "accepted_bribe_100k") and CreatureObject(pPlayer):hasSkill("combat_smuggler_underworld_04") and (CreatureObject(pPlayer):getCashCredits() >= 100000)
		and (getFactionPointsCap(CreatureObject(pPlayer):getFactionRank()) >= PlayerObject(pGhost):getFactionStanding(recruiterScreenplay:getRecruiterFaction(pNpc)) + 1250) then
		recruiterScreenplay:grantBribe(pNpc, pPlayer, 100000, 1250)

	elseif (screenID == "fp_furniture" or screenID == "fp_weapons_armor" or screenID == "fp_installations" or screenID == "fp_uniforms" or screenID == "fp_hirelings" or screenID == "fp_schematics") then
		recruiterScreenplay:sendPurchaseSui(pNpc, pPlayer, screenID, getGCWDiscount(pPlayer))

	elseif (screenID == "greet_neutral_start") then
		self:addJoinMilitaryOption(recruiterScreenplay:getRecruiterFaction(pNpc), clonedConversation, PlayerObject(pGhost), pNpc)

	elseif (screenID == "show_gcw_score") then
		local zoneName = SceneObject(pNpc):getZoneName()
		clonedConversation:setDialogTextDI(getImperialScore(zoneName))
		clonedConversation:setDialogTextTO(getRebelScore(zoneName))

	-- Covert/Overt System
	elseif (screenID == "accept_join2") then
		local recruiterFaction = recruiterScreenplay:getRecruiterFaction(pNpc)
		local convoTemplate = LuaConversationTemplate(pConvTemplate)

		if (PlayerObject(pGhost):getFactionStanding(recruiterFaction) < recruiterScreenplay.minimumFactionStanding) then
			local notEnoughScreen = convoTemplate:getScreen("neutral_need_more_points2")
			local screenObject = LuaConversationScreen(notEnoughScreen)

			pConvScreen = screenObject:cloneScreen()

			screenObject = LuaConversationScreen(pConvScreen)
			screenObject:setDialogTextTO(recruiterFaction)
			screenObject:setDialogTextDI(recruiterScreenplay.minimumFactionStanding)

			return pConvScreen
		else
			recruiterFaction = recruiterFaction:gsub("^%l", string.upper)
			clonedConversation:setDialogTextTO(recruiterFaction)

			CreatureObject(pPlayer):setFaction(recruiterScreenplay:getRecruiterFactionHashCode(pNpc))
			CreatureObject(pPlayer):setFactionStatus(1)
		end
	elseif (screenID == "neutral_need_more_points2") then
		clonedConversation:setDialogTextDI(recruiterScreenplay.minimumFactionStanding)
		clonedConversation:setDialogTextTO(recruiterScreenplay:getRecruiterFaction(pNpc))
	elseif (screenID == "resign_faction") then
		clonedConversation:setDialogTextTU(CreatureObject(pPlayer):getFirstName())
		clonedConversation:setDialogTextDI(recruiterScreenplay.covertOvertResignTime)
	elseif (screenID == "confirm_resign") then
		local convoTemplate = LuaConversationTemplate(pConvTemplate)

		if (CreatureObject(pPlayer):hasSkill("force_rank_light_novice") or CreatureObject(pPlayer):hasSkill("force_rank_dark_novice")) then
			CreatureObject(pPlayer):sendSystemMessage("@faction_recruiter:jedi_cant_resign")
			return
		end

		writeData(CreatureObject(pPlayer):getObjectID() .. ":changingFactionStatus", 1)

		if (SceneObject(pPlayer):hasPendingTask("recruiterScreenplay", "handleResign")) then
			SceneObject(pPlayer):cancelPendingTask("recruiterScreenplay", "handleResign")
		end

		local timer = recruiterScreenplay.covertOvertResignTime * 60 * 1000 -- Minutes

		SceneObject(pPlayer):addPendingTask(timer, "recruiterScreenplay", "handleResign")

		return pConvScreen
	elseif (screenID == "greet_member_start_covert2" or screenID == "greet_member_start_overt2" or screenID == "dont_resign") then
		if (screenID == "dont_resign") then
			clonedConversation:setDialogTextStringId("@faction_recruiter:resign_faction_no")
		else
			clonedConversation:setDialogTextTO(CreatureObject(pPlayer):getFirstName())
		end

		-- Cancel current resignation
		if (SceneObject(pPlayer):hasPendingTask("recruiterScreenplay", "handleResign")) then
			clonedConversation:addOption("@faction_recruiter:option_recind_resignation", "cancel_resignation")
		else
			if (screenID == "greet_member_start_covert2") then
				clonedConversation:addOption("@faction_recruiter:option_go_declared", "confirm_declare")
			elseif (screenID == "greet_member_start_overt2") then
				clonedConversation:addOption("@faction_recruiter:option_go_covert", "confirm_covert")
			end

			clonedConversation:addOption("@faction_recruiter:option_resign_from_faction", "resign_faction")
		end

		if (recruiterScreenplay:getRecruiterFaction(pNpc) == "imperial") then
			clonedConversation:addOption("@conversation/faction_recruiter_imperial:s_410", "show_gcw_score")
		else
			clonedConversation:addOption("@conversation/faction_recruiter_rebel:s_562", "show_gcw_score")
		end

		self:updateScreenWithPromotions(pPlayer, pConvTemplate, pConvScreen, recruiterScreenplay:getRecruiterFaction(pNpc))

		if (screenID == "greet_member_start_overt2") then
			self:updateScreenWithBribe(pPlayer, pNpc, pConvTemplate, pConvScreen, recruiterScreenplay:getRecruiterFaction(pNpc))
		end

		clonedConversation:addOption("@faction_recruiter:option_purchase_items", "faction_purchase")
	elseif (screenID == "cancel_resignation") then
		deleteData(CreatureObject(pPlayer):getObjectID() .. ":changingFactionStatus")
		SceneObject(pPlayer):cancelPendingTask("recruiterScreenplay", "handleResign")
	elseif (screenID == "declare_complete") then
		CreatureObject(pPlayer):setFutureFactionStatus(2)
		writeData(CreatureObject(pPlayer):getObjectID() .. ":changingFactionStatus", 1)
		createEvent(1000, "recruiterScreenplay", "handleGoOvert", pPlayer, "")
	elseif (screenID == "covert_complete") then
		if (CreatureObject(pPlayer):hasSkill("force_rank_light_novice") or CreatureObject(pPlayer):hasSkill("force_rank_dark_novice")) then
			CreatureObject(pPlayer):sendSystemMessage("@faction_recruiter:jedi_cant_go_covert")
			return
		end

		if (SceneObject(pPlayer):hasPendingTask("recruiterScreenplay", "handleGoCovert")) then
			SceneObject(pPlayer):cancelPendingTask("recruiterScreenplay", "handleGoCovert")
		end

		local timer = recruiterScreenplay.covertOvertResignTime * 60 * 1000 -- Minutes

		SceneObject(pPlayer):addPendingTask(timer, "recruiterScreenplay", "handleGoCovert")
	end

	return pConvScreen
end

function RecruiterConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("greet_neutral_start")
	end

	local faction = CreatureObject(pPlayer):getFaction()
	local factionStanding = PlayerObject(pGhost):getFactionStanding(recruiterScreenplay:getRecruiterFaction(pNpc))

	if (CreatureObject(pPlayer):isChangingFactionStatus() and readData(CreatureObject(pPlayer):getObjectID() .. ":changingFactionStatus") ~= 1) then
		recruiterScreenplay:handleGoCovert(pPlayer)
	end

	local covertOvert = useCovertOvert()

	if (faction == recruiterScreenplay:getRecruiterEnemyFactionHashCode(pNpc)) then
		return convoTemplate:getScreen("greet_enemy")
	elseif factionStanding < -200 and PlayerObject(pGhost):getFactionStanding(recruiterScreenplay:getRecruiterEnemyFaction(pNpc)) > 0 then
		return convoTemplate:getScreen("greet_hated")
	elseif (CreatureObject(pPlayer):isChangingFactionStatus() and not covertOvert) then
		return convoTemplate:getScreen("greet_changing_status")
	elseif (faction == recruiterScreenplay:getRecruiterFactionHashCode(pNpc)) then
		if (CreatureObject(pPlayer):isOnLeave()) then
			return convoTemplate:getScreen("greet_onleave_start")
		elseif (CreatureObject(pPlayer):isCovert()) then
			if (covertOvert) then
				return convoTemplate:getScreen("greet_member_start_covert2")
			else
				return convoTemplate:getScreen("greet_member_start_covert")
			end
		else
			if (covertOvert) then
				return convoTemplate:getScreen("greet_member_start_overt2")
			else
				return convoTemplate:getScreen("greet_member_start_overt")
			end
		end
	else
		if (covertOvert) then
			return convoTemplate:getScreen("greet_neutral_start2")
		else
			return convoTemplate:getScreen("greet_neutral_start")
		end
	end
	return nil
end

function RecruiterConvoHandler:addRankReviewOption(faction, screen)
	if (faction == "rebel") then
		screen:addOption("@conversation/faction_recruiter_rebel:s_468", "confirm_promotion")
	elseif (faction == "imperial") then
		screen:addOption("@conversation/faction_recruiter_imperial:s_312", "confirm_promotion")
	end
end

function RecruiterConvoHandler:addJoinMilitaryOption(faction, screen, playerObject, pNpc)
	if (faction == "rebel") then
		if (playerObject:getFactionStanding(recruiterScreenplay:getRecruiterFaction(pNpc)) < recruiterScreenplay.minimumFactionStanding) then
			screen:addOption("@conversation/faction_recruiter_rebel:s_580", "neutral_need_more_points")
		else
			screen:addOption("@conversation/faction_recruiter_rebel:s_580", "join_military")
		end
	elseif (faction == "imperial") then
		if (playerObject:getFactionStanding(recruiterScreenplay:getRecruiterFaction(pNpc)) < recruiterScreenplay.minimumFactionStanding) then
			screen:addOption("@conversation/faction_recruiter_imperial:s_428", "neutral_need_more_points")
		else
			screen:addOption("@conversation/faction_recruiter_imperial:s_428", "join_military")
		end
	end
end

function RecruiterConvoHandler:getRejectPromotionString(faction)
	if (faction == "rebel") then
		return "@conversation/faction_recruiter_rebel:s_476"
	elseif (faction == "imperial") then
		return "@conversation/faction_recruiter_imperial:s_320"
	end
end

function RecruiterConvoHandler:addBribeOption(pNpc, screen)
	local faction = recruiterScreenplay:getRecruiterFaction(pNpc)
	if (faction == "rebel") then
		screen:addOption("@conversation/faction_recruiter_rebel:s_568", "confirm_bribe")
	elseif (faction == "imperial") then
		screen:addOption("@conversation/faction_recruiter_imperial:s_398", "confirm_bribe")
	end
end

function RecruiterConvoHandler:add100kBribeOption(pNpc, screen)
	local faction = recruiterScreenplay:getRecruiterFaction(pNpc)
	if (faction == "rebel") then
		screen:addOption("@conversation/faction_recruiter_rebel:s_576", "accepted_bribe_100k")
	elseif (faction == "imperial") then
		screen:addOption("@conversation/faction_recruiter_imperial:s_406", "accepted_bribe_100k")
	end
end

function RecruiterConvoHandler:updateScreenWithBribe(pPlayer, pNpc, pConvTemplate, pConvScreen, faction)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local screenObject = LuaConversationScreen(pConvScreen)

	if (CreatureObject(pPlayer):hasSkill("combat_smuggler_underworld_04") and (CreatureObject(pPlayer):getCashCredits() >= 20000)
		and (getFactionPointsCap(CreatureObject(pPlayer):getFactionRank()) >= PlayerObject(pGhost):getFactionStanding(faction) + 250)) then
		self:addBribeOption(pNpc, screenObject)
	end
end

function RecruiterConvoHandler:updateScreenWithPromotions(pPlayer, pConvTemplate, pConvScreen, faction)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local screenObject = LuaConversationScreen(pConvScreen)
	local rank = CreatureObject(pPlayer):getFactionRank()

	if rank < 0 or isHighestRank(rank) == true then
		return
	end

	local requiredPoints = getRankCost(rank + 1)
	local currentPoints = PlayerObject(pGhost):getFactionStanding(faction)

	if (currentPoints < requiredPoints + recruiterScreenplay:getMinimumFactionStanding()) then
		return
	end

	self:addRankReviewOption(faction, screenObject)
end
