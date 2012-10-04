includeFile("recruiters/factionperkdata.lua")

recruiter_convo_handler = Object:new {
	rebelHashCode = 370444368, 
	imperialHashCode = 3679112276,
	rebelString = "rebel",
	imperialString = "imperial",
	SUCCESS = 0,
	INVENTORYFULL = 1,
	NOTENOUGHFACTION = 2,
	GENERALERROR = 3

}

	
function recruiter_convo_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption, conversingNPC)
	
	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	lastConversationScreen = nil
	
	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end
		
	local conversation = LuaConversationTemplate(conversationTemplate)
		
	local nextConversationScreen
	
	--printf("last conv screen " .. lastConversationScreen .. "\n")
	
	if (lastConversationScreen ~= nil) then	
		--Get the linked screen for the selected option.
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		
		--print("optionLink " .. optionLink .. "\n")
		
		if ( string.find(optionLink,"armor_",1) ) then
			--print("purchased armor switching the next screen")
			nextConversationScreen = conversation:getScreen("purchased")
		else
			--print("Handling next screen normally")
			nextConversationScreen = conversation:getScreen(optionLink)
		end
		
		
		if (nextConversationScreen == nil) then
			--printf("nextConversationScreen nill for option link = " .. optionLink .. "\n")
		end
	else
		nextConversationScreen = self:getInitialScreen(conversingPlayer, conversingNPC, conversationTemplate)
	end
	
	return nextConversationScreen
end

function recruiter_convo_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	
	local screenID = screen:getScreenID()

	local player = LuaCreatureObject(conversingPlayer)
	local playerObjectPointer = player:getPlayerObject()
	
	if (screenID == "greet_member_start_covert") then
		conversationScreen = self:getInitialScreen(conversingPlayer, conversingNPC, conversationTemplate)
	elseif (screenID == "greet_member_start_overt") then
		conversationScreen = self:getInitialScreen(conversingPlayer, conversingNPC, conversationTemplate)
	elseif (screenID == "accept_join") then
		player:setFaction(self:getRecruiterFactionHashCode())
		
		if (playerObjectPointer ~= nil) then
			local playerObject = LuaPlayerObject(playerObjectPointer)
			playerObject:setFactionStatus(1)
		end
	elseif (screenID == "accepted_go_overt") then
		if (playerObjectPointer ~= nil) then
			local playerObject = LuaPlayerObject(playerObjectPointer)
			playerObject:setFactionStatus(3)
		end
		
		--createEvent(30000, "recruiter_convo_handler", "handleGoOvert", conversingPlayer)
		createEvent(30000, "recruiter_convo_handler", "handleGoOvert", conversingPlayer)
	elseif (screenID == "accepted_go_covert") then
		if (playerObjectPointer ~= nil) then
			local playerObject = LuaPlayerObject(playerObjectPointer)
			playerObject:setFactionStatus(3)
		end
		
		createEvent(300000, "recruiter_convo_handler", "handleGoCovert", conversingPlayer)
	elseif (screenID == "accepted_go_on_leave") then
		if (playerObjectPointer ~= nil) then
			local playerObject = LuaPlayerObject(playerObjectPointer)
			playerObject:setFactionStatus(3)
		end
		
		createEvent(300000, "recruiter_convo_handler", "handleGoOnLeave", conversingPlayer)
	elseif (screenID == "accepted_resign") then
		if (playerObjectPointer ~= nil) then
			local playerObject = LuaPlayerObject(playerObjectPointer)
			
			if (playerObject:isOvert()) then
				playerObject:setFactionStatus(3)
				createEvent(300000, "recruiter_convo_handler", "handleResign", conversingPlayer)
				return conversationScreen
			end
		end
		
		self:handleResign(conversingPlayer)
	elseif (screenID == "accepted_resume_duties") then
		if (playerObjectPointer ~= nil) then
		local playerObject = LuaPlayerObject(playerObjectPointer)
			playerObject:setFactionStatus(3)
		end
		
		createEvent(30000, "recruiter_convo_handler", "handleGoCovert", conversingPlayer)
	elseif (screenID == "confirm_promotion") then
		--printf("in confirm_promotion\n")
		conversationScreen = screen:cloneScreen()
		--printf("screen cloned\n")
		self:setRankName(conversingPlayer, conversationScreen)
		--printf("rank name set\n")
		
		
		local clonedConversation = LuaConversationScreen(conversationScreen)
		
		if (playerObjectPointer ~= nil) then
			local playerObject = LuaPlayerObject(playerObjectPointer)
			
			local rejectString = self:getRejectPromotionString()
			
			if (playerObject:isCovert()) then
				clonedConversation:addOption(rejectString, "greet_member_start_covert")
			elseif (playerObject:isOvert()) then
				clonedConversation:addOption(rejectString, "greet_member_start_overt")
			end
		end
			
	elseif (screenID == "accepted_promotion") then
		if (playerObjectPointer ~= nil) then
			local playerObject = LuaPlayerObject(playerObjectPointer)
			local rank = player:getFactionRank() + 1
			local requiredPoints = getRankCost(rank)
			
			if (playerObject:getFactionStanding(self:getRecruiterFactionString()) < (requiredPoints + self:getMinimumFactionStanding())) then
				local convoTemplate = LuaConversationTemplate(conversationTemplate)
				local notEnoughScreen = convoTemplate:getScreen("not_enough_points")
				local screenObject = LuaConversationScreen(notEnoughScreen)
				
				conversationScreen = screenObject:cloneScreen()
				
				screenObject = LuaConversationScreen(conversationScreen)
				screenObject:setDialogTextTO("faction_recruiter", getRankName(rank))
				screenObject:setDialogTextDI(requiredPoints)
			 else 
				playerObject:decreaseFactionStanding(self:getRecruiterFactionString(), requiredPoints)
				player:setFactionRank(rank)
			end
		end
	elseif (screenID == "confirm_bribe") then
		local playerObject = LuaPlayerObject(playerObjectPointer)
		
		if (player:hasSkill("combat_smuggler_underworld_04") and (player:getCashCredits() >= 100000)
				and (getFactionPointsCap(player:getFactionRank()) >= playerObject:getFactionStanding(self:getRecruiterFactionString()) + 1250)) then
		
			conversationScreen = screen:cloneScreen()
			
			local clonedConversation = LuaConversationScreen(conversationScreen)
			
			self:add100kBribeOption(clonedConversation)
			
		end
	elseif (screenID == "accepted_bribe_20k") then
		local playerObject = LuaPlayerObject(playerObjectPointer)
		
		if (player:hasSkill("combat_smuggler_underworld_04") and (player:getCashCredits() >= 20000)
				and (getFactionPointsCap(player:getFactionRank()) >= playerObject:getFactionStanding(self:getRecruiterFactionString()) + 250)) then
				
			self:grantBribe(conversingPlayer, 20000, 250)
		end
		
	elseif (screenID == "accepted_bribe_100k") then
		local playerObject = LuaPlayerObject(playerObjectPointer)
		
		if (player:hasSkill("combat_smuggler_underworld_04") and (player:getCashCredits() >= 100000)
			and (getFactionPointsCap(player:getFactionRank()) >= playerObject:getFactionStanding(self:getRecruiterFactionString()) + 1250)) then
		
			self:grantBribe(conversingPlayer, 100000, 1250)
		end
	elseif (screenID == "fp_weapons_armor") then
	
		conversationScreen = screen:cloneScreen()
		
		local clonedConversation = LuaConversationScreen(conversationScreen)
				
		if (clonedConversation ~= nil) then
				self:addWeaponsArmor(clonedConversation)
		end
		
	elseif (screenID == "purchased") then
			
		conversationScreen = self:processArmorPurchase(conversingPlayer, conversationTemplate, selectedOption)
				
	end
	
	return conversationScreen
end

function recruiter_convo_handler:grantBribe(creatureObject, cost, factionPoints)		
	local player = LuaCreatureObject(creatureObject)
	local playerObjectPointer = player:getPlayerObject()
	local playerObject = LuaPlayerObject(playerObjectPointer)
	
	if (player:getCashCredits() < cost) then
		return
	end
	
	--if (playerObject:getFactionStanding(self:getRecruiterFactionString()))
	
	player:subtractCashCredits(cost)
	playerObject:increaseFactionStanding(self:getRecruiterFactionString(), factionPoints)
end

function recruiter_convo_handler:handleGoOnLeave(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	local playerObjectPointer = player:getPlayerObject()
	
	if (playerObjectPointer ~= nil) then
		local playerObject = LuaPlayerObject(playerObjectPointer)
		playerObject:setFactionStatus(0)
	end
end

function recruiter_convo_handler:handleGoCovert(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	local playerObjectPointer = player:getPlayerObject()
	
	if (playerObjectPointer ~= nil) then
		local playerObject = LuaPlayerObject(playerObjectPointer)
		playerObject:setFactionStatus(1)
	end
end

function recruiter_convo_handler:handleGoOvert(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	local playerObjectPointer = player:getPlayerObject()
	
	if (playerObjectPointer ~= nil) then
		local playerObject = LuaPlayerObject(playerObjectPointer)
		playerObject:setFactionStatus(2)
	end
end

function recruiter_convo_handler:handleResign(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	local playerObjectPointer = player:getPlayerObject()
	
	player:setFactionRank(0)
	player:setFaction(0)

	if (playerObjectPointer ~= nil) then
		local playerObject = LuaPlayerObject(playerObjectPointer)
		playerObject:setFactionStatus(0)
	end
end

function recruiter_convo_handler:getRejectPromotionString()
	--printf("pure getRejectPromotionString")
	return nil
end

function recruiter_convo_handler:setRankName(player, screen)
	local playerCreatureObject = LuaCreatureObject(player)
	local screenObject = LuaConversationScreen(screen)

	local factionRank = playerCreatureObject:getFactionRank() + 1
	local factionName = getRankName(factionRank)

	--printf("factionName = " .. factionName .. "\n")

	screenObject:setDialogTextTO("faction_recruiter", factionName)
end

function recruiter_convo_handler:getMinimumFactionStanding()
	return 200
end

function recruiter_convo_handler:sendOnLeaveStart(player, conversationTemplate)
	local template = LuaConversationTemplate(conversationTemplate)
	
	return template:getScreen("greet_onleave_start")
end

function recruiter_convo_handler:greetMemberCovert(player, conversationTemplate)
	local template = LuaConversationTemplate(conversationTemplate)

	local screen = template:getScreen("greet_member_start_covert")
	
	if (screen == nil) then
		return nil
	end
	
	local screenObject = LuaConversationScreen(screen)
	local screenCopy = screenObject:cloneScreen()
	
	self:updateScreenWithPromotions(player, conversationTemplate, screenCopy)
	self:updateScreenWithBribe(player, conversationTemplate, screenCopy)
	self:updateScreenWithFactionItems(screenCopy)
	
	return screenCopy
end


function recruiter_convo_handler:greetMemberOvert(player, conversationTemplate)
	local template = LuaConversationTemplate(conversationTemplate)

	local screen = template:getScreen("greet_member_start_overt")
	
	if (screen == nil) then
		return nil
	end
	
	local screenObject = LuaConversationScreen(screen)
	local screenCopy = screenObject:cloneScreen()

	self:updateScreenWithPromotions(player, conversationTemplate, screenCopy)
	self:updateScreenWithBribe(player, conversationTemplate, screenCopy)
	self:updateScreenWithFactionItems(screenCopy)
	
	return screenCopy
end

function recruiter_convo_handler:updateScreenWithFactionItems(screen)
	local tscreenObject = LuaConversationScreen(screen)
	tscreenObject:addOption("@faction_recruiter:faction_purchase", "faction_purchase")
end

function recruiter_convo_handler:updateScreenWithBribe(player, conversationTemplate, screen)
	local creatureObject = LuaCreatureObject(player)
	local screenObject = LuaConversationScreen(screen)
	local playerObjectPointer = creatureObject:getPlayerObject()
	local playerObject = LuaPlayerObject(playerObjectPointer)
	
	if (creatureObject:hasSkill("combat_smuggler_underworld_04") and (creatureObject:getCashCredits() >= 20000)
		and (getFactionPointsCap(creatureObject:getFactionRank()) >= playerObject:getFactionStanding(self:getRecruiterFactionString()) + 250)) then
		
		self:addBribeOption(screenObject)
		
	end
	
end

function recruiter_convo_handler:updateScreenWithPromotions(player, conversationTemplate, screen)
	local creatureObject = LuaCreatureObject(player)
	local screenObject = LuaConversationScreen(screen)
	
	local rank = creatureObject:getFactionRank()
	
	if ((rank < 0)  or (isHighestRank(rank) == true)) then
		--printf("rank < 0 or highest rank reached\n")
		return
	end
	
	local requiredPoints = getRankCost(rank + 1)
	
	--printf("rank = " .. rank .. "\n")
	
	--printf("required points = " .. requiredPoints .. "\n")
	
	local playerObject = LuaPlayerObject(creatureObject:getPlayerObject())
	local currentPoints = playerObject:getFactionStanding(self:getRecruiterFactionString())
	
	--printf("current points = " .. currentPoints .. "\n")
	
	if (currentPoints < requiredPoints + self:getMinimumFactionStanding()) then
		return
	end
		
	--slist->insertOption("conversation/faction_recruiter_imperial", "s_312");
	--screenCopyObject:addOption("@conversation/faction_recruiter_imperial:s", "")
	self:addRankReviewOption(screenObject)
end

function recruiter_convo_handler:sendNeutralStart(player, conversationTemplate)
	local template = LuaConversationTemplate(conversationTemplate)

	return template:getScreen("greet_neutral_start")
end

function recruiter_convo_handler:getRecruiterFactionHashCode()
	return 0
end

function recruiter_convo_handler:addRankReviewOption(screen)
	printf("pure recruiter_convo_handler:addRankReviewOption(screen)")
end

function recruiter_convo_handler:addBribeOption(screen)
	printf("pure recruiter_convo_handler:addBribeOption(screen)")
end

function recruiter_convo_handler:add100kBribeOption(screen)
	printf("pure recruiter_convo_handler:add100kBribeOption(screen)")
end

function recruiter_convo_handler:getRecruiterFactionString()
	return ""
end

function recruiter_convo_handler:getEnemyFactionHashCode()
	return 0
end

function recruiter_convo_handler:getEnemyFactionString()
	return ""
end

function recruiter_convo_handler:addWeaponsArmor(thisConversation)

	if (self:getRecruiterFactionString() == "rebel") then
		
		--go through rebel_weapons_armor table and add them to the converstaion
		for k,v in pairs(rebel_weapons_armor_list) do
			if ( rebel_weapons_armor[v].display ~= nil ) then
				thisConversation:addOption(rebel_weapons_armor[v].display .. " - " .. rebel_weapons_armor[v].cost, v)
			end
		end
	
	else
		for k,v in pairs(imperial_weapons_armor_list) do
			if ( imperial_weapons_armor[v].display ~= nil ) then
				thisConversation:addOption(imperial_weapons_armor[v].display .. " - " .. imperial_weapons_armor[v].cost, v)
			end
		end
	end

end

function recruiter_convo_handler:getInitialScreen(play, npc, conversationTemplate)
	local convoTemplate = LuaConversationTemplate(conversationTemplate)
	local conversingPlayer = LuaCreatureObject(play)
	local faction = conversingPlayer:getFaction()
	local playerObjectPointer = conversingPlayer:getPlayerObject()
	
	if (playerObjectPointer == nil) then
		return nil
	end
	
	local playerObject = LuaPlayerObject(playerObjectPointer)
	
	local factionStanding = playerObject:getFactionStanding(self:getRecruiterFactionString())
	
	if (faction == self:getEnemyFactionHashCode()) then
		return convoTemplate:getScreen("greet_enemy")
	end
	
	if ((playerObject:getFactionStanding(self:getRecruiterFactionString()) < -200) and (playerObject:getFactionStanding(self:getEnemyFactionString()) > 0)) then
		return convoTemplate:getScreen("greet_hated")
	end
	
	if (playerObject:isChangingFactionStatus()) then
		return convoTemplate:getScreen("greet_changing_status")
	end
		
	if (faction == self:getRecruiterFactionHashCode()) then
		if (playerObject:isOnLeave()) then
			return self:sendOnLeaveStart(play, conversationTemplate)
		elseif (playerObject:isCovert()) then
			return self:greetMemberCovert(play, conversationTemplate)
		else
			return self:greetMemberOvert(play, conversationTemplate)
		end
	else
		return self:sendNeutralStart(play, conversationTemplate)
	end
	
	return nil
	
end

function recruiter_convo_handler:getItemCost(itemstring)

	local itemcost = nil
	if (self:getRecruiterFactionString() == "rebel") then
		itemcost = rebel_weapons_armor[itemstring].cost
	elseif (self:getRecruiterFactionString() == "imperial") then
		itemcost = imperial_weapons_armor[itemstring].cost
	end

	return itemcost
end


-- player, convo template, and the option number selected from the previous screen
function recruiter_convo_handler:processArmorPurchase(conversingPlayer, conversationTemplate, selectedOption)

	local player = LuaCreatureObject(conversingPlayer)

	local convosession = player:getConversationSession()
		
	lastConversationScreen = nil
	local conversationScreen = nil
		
	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end

	local itemname = nil
	local conversationScreen = nill
		
	if (lastConversationScreen ~= nil) then	
			
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		
		local convoTemplate = LuaConversationTemplate(conversationTemplate)
		
		itemname = luaLastConversationScreen:getOptionLink(selectedOption)
	
		local awardresult = self:awarditem(conversingPlayer, itemname) 
		
		if (awardresult == self.SUCCESS) then
		
			local purchasedScreen = convoTemplate:getScreen("purchased")  -- Your requisition of the %TT order is complete.
			local screenObject = LuaConversationScreen(purchasedScreen)
			conversationScreen = screenObject:cloneScreen()
			
			screenObject = LuaConversationScreen(conversationScreen)
			screenObject:setDialogTextTT("wearables_name", itemname)
		
		elseif (awardresult == self.NOTENOUGHFACTION) then
		
			conversationScreen = convoTemplate:getScreen("purchased_not_enough") -- don't offer money when you can't afford to pay
			
		elseif (awardresult == self.INVENTORYFULL) then
		
			conversationScreen = convoTemplate:getScreen("inventory_full") -- YOur inventory is full.  YOu must make some room before you can purchase.
		end
		
	end
		
	return conversationScreen

end

function recruiter_convo_handler:awarditem(player, itemstring)
	local obj = LuaSceneObject(player)
	
	local creatureObject = LuaCreatureObject(player)
	
	if ( creatureObject == nil or obj == nil ) then
	
		return self.GENERALERROR
	end
	
	local pPlayer = creatureObject:getPlayerObject()
	
	local playerObject = LuaPlayerObject(pPlayer)
	
	local pInventory = obj:getSlottedObject("inventory")
	
	local factionstanding = playerObject:getFactionStanding(self:getRecruiterFactionString())
		
	local itemcost = self:getItemCost(itemstring)
	
	if ( pInventory ~= nil and playerObject ~= nil ) then 
		
		if (factionstanding  >= itemcost) then
			--print("faction is good")
			local pItem
			
			if (pInventory ~= nil) then
			
				local inventory = LuaSceneObject(pInventory)
				
				if (inventory:hasFullContainerObjects()) then
					--print("inventory is full in awarditem()")
					return self.INVENTORYFULL
				end
			
				if (self:getRecruiterFactionString() == "rebel") then
					pItem = giveItem(pInventory,rebel_weapons_armor[itemstring].item,-1)
				else
					local templatepath = imperial_weapons_armor[itemstring].item
					pItem = giveItem(pInventory,templatepath,-1)
					--print("done giving the item")
				end
			
				if (pItem ~= nil) then
				
					local item = LuaSceneObject(pItem)
					item:sendTo(player)
					playerObject:decreaseFactionStanding(self:getRecruiterFactionString(),itemcost)
							
				else
					--creatureObject:sendSystemMessage("Unable to process that item") 
					return self.GENERALERROR
				end
			end
		
		else
			return self.NOTENOUGHFACTION
		end
	
	else
		return self.GENERALERROR
	end
	
	return self.SUCCESS

end

