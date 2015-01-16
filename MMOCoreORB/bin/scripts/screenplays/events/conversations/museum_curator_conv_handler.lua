local ObjectManager = require("managers.object.object_manager")

MuseumCuratorConvoHandler = Object:new {
	themePark = nil
}

function MuseumCuratorConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function MuseumCuratorConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()
	if (screenID == "hello_no_voting") then
		return conversationScreen
	end

	return ObjectManager.withCreatureAndPlayerObject(conversingPlayer, function(player,playerObject)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		local currentPhase = BestineMuseumScreenPlay:getCurrentPhase()

		if (currentPhase == 1) then
			local artists = BestineMuseumScreenPlay:getCurrentArtists()
			local currentArtists = BestineMuseumScreenPlay:splitString(artists, ",")
			if (screenID == "init_votephase") then
				clonedConversation:addOption("@conversation/lilas_dinhint:s_26152411", "explain_contest")
				if (BestineMuseumScreenPlay:hasTalkedToAnyArtist(conversingPlayer)) then
					clonedConversation:addOption("@conversation/lilas_dinhint:s_911a27f8", "pick_artist")
				end
				if (BestineMuseumScreenPlay:getWinningPainting() ~= "" and (not BestineMuseumScreenPlay:hasAlreadyPurchased(conversingPlayer) or BestineMuseumScreenPlay.restrictSinglePurchase == false)) then
					clonedConversation:addOption("@conversation/lilas_dinhint:s_e649bf0a", "schematic_cost")
				end
				clonedConversation:addOption("@conversation/lilas_dinhint:s_6b5b28b2", "enjoy_visit_votephase")
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
			if(player:getCashCredits() >= 48000) then
				local pInventory = player:getSlottedObject("inventory")
				local inventory = LuaSceneObject(pInventory)
				if (inventory == nil or inventory:hasFullContainerObjects()) then
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
		return conversationScreen
	end)
end


function MuseumCuratorConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (BestineMuseumScreenPlay:isMuseumEnabled() == false) then
		return convoTemplate:getScreen("hello_no_voting")
	end

	local currentPhase = BestineMuseumScreenPlay:getCurrentPhase()

	if (currentPhase == 1) then
		if (BestineMuseumScreenPlay:hasAlreadyVoted(pPlayer)) then
			return convoTemplate:getScreen("already_voted")
		else
			return convoTemplate:getScreen("init_votephase")
		end
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
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local pConversationSession = player:getConversationSession()
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
	end)
end