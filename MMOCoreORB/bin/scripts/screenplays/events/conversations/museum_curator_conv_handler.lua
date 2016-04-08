local ObjectManager = require("managers.object.object_manager")

MuseumCuratorConvoHandler = Object:new {
	}

function MuseumCuratorConvoHandler:giveSeansTestimony(pPlayer)
	if (pPlayer ~= nil) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local pItem = giveItem(pInventory, "object/tangible/loot/quest/sean_questp_ctestimony.iff", -1)
			if (pItem ~= nil) then
				CreatureObject(pPlayer):sendSystemMessage("@system_msg:give_item_success")
			end
		end
	end
end

function MuseumCuratorConvoHandler:talkAboutSeanTrenwell(pPlayer)
	if (not BestineElectionScreenPlay:isElectionEnabled()) then
		return false
	end
	
	local playerID = CreatureObject(pPlayer):getObjectID()
	if BestineElectionScreenPlay:joinedCampaign(pPlayer, "Sean") then
		if (readData(playerID..":bestine_museum:sean_museum_noroom") == 0) then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			if (pInventory ~= nil) and getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questp_ctestimony.iff", true) then
				return false
			else return true
			end
		end
	end
	return false
end

function MuseumCuratorConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()
	if (screenID == "hello_no_voting") then
		return conversationScreen
	end

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)
	local currentPhase = BestineMuseumScreenPlay:getCurrentPhase()
	local playerID = CreatureObject(conversingPlayer):getObjectID()

	if (currentPhase == 1) then
		local artists = BestineMuseumScreenPlay:getCurrentArtists()
		local currentArtists = BestineMuseumScreenPlay:splitString(artists, ",")
		if (screenID == "init_votephase") then
			if (BestineMuseumScreenPlay:hasAlreadyVoted(conversingPlayer)) then
				clonedConversation:addOption("@conversation/lilas_dinhint:s_537ad9f6", "already_voted")
			else
				clonedConversation:addOption("@conversation/lilas_dinhint:s_26152411", "explain_contest")
				if (BestineMuseumScreenPlay:hasTalkedToAnyArtist(conversingPlayer)) then
					clonedConversation:addOption("@conversation/lilas_dinhint:s_911a27f8", "pick_artist")
				end
			end
			if (BestineMuseumScreenPlay:getWinningPainting() ~= "" and (not BestineMuseumScreenPlay:hasAlreadyPurchased(conversingPlayer) or BestineMuseumScreenPlay.restrictSinglePurchase == false)) then
				clonedConversation:addOption("@conversation/lilas_dinhint:s_e649bf0a", "schematic_cost")
			end
			clonedConversation:addOption("@conversation/lilas_dinhint:s_d543ced9", "enjoy_visit_votephase")
		elseif (screenID == "seek_out_artists" or string.find(screenID, "find_") ~= nil) then
			for i = 1, 3, 1 do
				local artistTemplate = BestineMuseumScreenPlay:getArtistTemplate(tonumber(currentArtists[i]))
				if (string.find(screenID, artistTemplate) == nil) then
					if (tonumber(currentArtists[i]) == 1) then clonedConversation:addOption("@conversation/lilas_dinhint:s_82761006", "find_vanvi_hotne")
					elseif (tonumber(currentArtists[i]) == 2) then clonedConversation:addOption("@conversation/lilas_dinhint:s_c1f9104", "find_kolka_zteht")
					elseif (tonumber(currentArtists[i]) == 3) then clonedConversation:addOption("@conversation/lilas_dinhint:s_bea3d11", "find_giaal_itotr")
					elseif (tonumber(currentArtists[i]) == 4) then clonedConversation:addOption("@conversation/lilas_dinhint:s_2ecc437c", "find_kahfr_oladi")
					elseif (tonumber(currentArtists[i]) == 5) then clonedConversation:addOption("@conversation/lilas_dinhint:s_55e840b3", "find_klepa_laeel")
					elseif (tonumber(currentArtists[i]) == 6) then clonedConversation:addOption("@conversation/lilas_dinhint:s_39a4e8fa", "find_boulo_siesi")
					end
				else
					BestineMuseumScreenPlay:createArtistWaypoint(conversingPlayer, tonumber(currentArtists[i]))
				end
			end
			clonedConversation:addOption("@conversation/lilas_dinhint:s_b9059b2b", "pleasure_all_mine")
			clonedConversation:addOption("@conversation/lilas_dinhint:s_463a0bda", "thanks_for_visiting")
		elseif (screenID == "pick_artist") then
			for i = 1, 3, 1 do
				if BestineMuseumScreenPlay:hasTalkedToArtist(conversingPlayer, currentArtists[i]) then
					if (tonumber(currentArtists[i]) == 1) then clonedConversation:addOption("@conversation/lilas_dinhint:s_e09f0f8", "picked_vanvi_hotne")
					elseif (tonumber(currentArtists[i]) == 2) then clonedConversation:addOption("@conversation/lilas_dinhint:s_b824fcc0", "picked_kolka_zteht")
					elseif (tonumber(currentArtists[i]) == 3) then clonedConversation:addOption("@conversation/lilas_dinhint:s_ce4aa2ab", "picked_giaal_itotr")
					elseif (tonumber(currentArtists[i]) == 4) then clonedConversation:addOption("@conversation/lilas_dinhint:s_84e3c8d2", "picked_kahfr_oladi")
					elseif (tonumber(currentArtists[i]) == 5) then clonedConversation:addOption("@conversation/lilas_dinhint:s_55773f3", "picked_klepa_laeel")
					elseif (tonumber(currentArtists[i]) == 6) then clonedConversation:addOption("@conversation/lilas_dinhint:s_4443365b", "picked_boulo_siesi")
					end
				end
			end
			clonedConversation:addOption("@conversation/lilas_dinhint:s_463a0bda", "thanks_for_visiting")
		elseif (string.find(screenID, "picked") ~= nil) then
			local pickedArtist = string.sub(screenID, 8)
			local pickedArtistID = BestineMuseumScreenPlay:getArtistID(pickedArtist)
			BestineMuseumScreenPlay:doVote(conversingPlayer, pickedArtistID)
		end
	elseif (currentPhase == 2) then
		local timeLeftInSecs = BestineMuseumScreenPlay:getPhaseTimeLeft() / 1000
		if (screenID == "init_buyphase" or screenID == "hello_already_purchased") then
			if (screenID == "init_buyphase" or BestineMuseumScreenPlay.restrictSinglePurchase == false) then
				clonedConversation:addOption("@conversation/lilas_dinhint:s_47df8332", "schematic_cost")
			end
			if (timeLeftInSecs <= 3600) then -- Less than an hour
				clonedConversation:addOption("@conversation/lilas_dinhint:s_9558d37a", "in_less_than_an_hour")
			elseif (timeLeftInSecs <= 14400) then -- Less than 4 hours
				clonedConversation:addOption("@conversation/lilas_dinhint:s_9558d37a", "in_a_few_hours")
			elseif (timeLeftInSecs < 86400) then -- Less than 24 hours
				clonedConversation:addOption("@conversation/lilas_dinhint:s_9558d37a", "in_less_than_a_day")
			elseif (timeLeftInSecs >= 86400 and timeLeftInSecs <= 604800) then -- More than 24 hours, less than a week
				clonedConversation:addOption("@conversation/lilas_dinhint:s_9558d37a", "in_more_than_a_day")
			elseif (timeLeftInSecs < 604800) then -- Less than a week
				clonedConversation:addOption("@conversation/lilas_dinhint:s_9558d37a", "in_less_than_a_week")
			elseif (timeLeftInSecs >= 604800) then -- More than a week
				clonedConversation:addOption("@conversation/lilas_dinhint:s_9558d37a", "in_more_than_a_week")
			end

			if (screenID == "init_buyphase") then
				clonedConversation:addOption("@conversation/lilas_dinhint:s_6b5b28b2", "thanks_for_visiting")
			end
		end
	end
	if (screenID == "schematic_cost") then
		if(CreatureObject(conversingPlayer):getCashCredits() >= 48000) then
			local pInventory = SceneObject(conversingPlayer):getSlottedObject("inventory")

			if (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
				clonedConversation:addOption("@conversation/lilas_dinhint:s_90b0871f", "full_inventory")
			else
				clonedConversation:addOption("@conversation/lilas_dinhint:s_90b0871f", "schematic_purchased")
			end
		else
			clonedConversation:addOption("@conversation/lilas_dinhint:s_90b0871f", "not_enough_credits")
		end
		clonedConversation:addOption("@conversation/lilas_dinhint:s_3f115c47", "thanks_for_visiting")
	elseif (screenID == "schematic_purchased") then
		BestineMuseumScreenPlay:doSchematicPurchase(conversingPlayer)
	end
	
	if self:talkAboutSeanTrenwell(conversingPlayer) then
		if readData(playerID..":bestine_museum:sean_museum_noroom") == 1 then
				clonedConversation:addOption("@conversation/lilas_dinhint:s_26c02ad3", "back_for_testimony")--I'm back for the testimonial for Sean Trenwell you had offered..
		else
				clonedConversation:addOption("@conversation/lilas_dinhint:s_8b3d6e46", "about_sean_trenwell")--Can you tell me anything about Sean Trenwell?
		end
	end

	if (screenID == "about_sean_trenwell") then
		clonedConversation:addOption("@conversation/lilas_dinhint:s_6d1148d8", "ask_for_testimony")
		clonedConversation:addOption("@conversation/lilas_dinhint:s_7552be07", "whatever_im_leaving")
	elseif (screenID == "giveSeansTestimony") then
		self:giveSeansTestimony(conversingPlayer)
	elseif (screenID == "ask_for_testimony" or screenID == "back_for_testimony") then
		if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
			clonedConversation:addOption("@conversation/lilas_dinhint:s_b67247f1", "NoRoomSeanTestimony")
			writeData(playerID..":bestine_museum:sean_museum_noroom",1)
		else
			clonedConversation:addOption("@conversation/lilas_dinhint:s_b67247f1", "giveSeansTestimony")
			deleteData(playerID..":bestine_museum:sean_museum_noroom")
		end
	end
	
	return conversationScreen
end


function MuseumCuratorConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (BestineMuseumScreenPlay:isMuseumEnabled() == false) then
		return convoTemplate:getScreen("hello_no_voting")
	end

	local currentPhase = BestineMuseumScreenPlay:getCurrentPhase()

	if (currentPhase == 1) then
		return convoTemplate:getScreen("init_votephase")
	elseif (currentPhase == 2) then
		if BestineMuseumScreenPlay:hasAlreadyPurchased(pPlayer) then
			return convoTemplate:getScreen("hello_already_purchased")
		else
			return convoTemplate:getScreen("init_buyphase")
		end
	end
	return convoTemplate:getScreen("hello_no_voting")
end

function MuseumCuratorConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
