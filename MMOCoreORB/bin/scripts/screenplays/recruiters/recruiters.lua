includeFile("recruiters/factionperkdata.lua")

recruiter_convo_handler = Object:new {
	rebelHashCode = 370444368, 
	imperialHashCode = 3679112276,
	rebelString = "rebel",
	imperialString = "imperial",
	SUCCESS = 0,
	INVENTORYFULL = 1,
	NOTENOUGHFACTION = 2,
	GENERALERROR = 3,
	ITEMCOST = 4,
	INVENTORYERROR = 5,
	TEMPLATEPATHERROR = 6,
	GIVEERROR = 7,

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
		--print("optionlink is " .. optionLink)
		if ( self:isWeapon(optionLink) or self:isArmor(optionLink) or self:isUniform(optionLink) or self:isFurniture(optionLink)  or self:isInstallation(optionLink) )then
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
				self:addWeaponsArmor(clonedConversation, getGCWDiscount(conversingPlayer))
		end
	elseif ( screenID == "fp_uniforms" ) then
		conversationScreen = screen:cloneScreen()
		
		local clonedConversation = LuaConversationScreen(conversationScreen)
		
		if ( clonedConversation ~= nil ) then
			self:addUniforms(clonedConversation, getGCWDiscount(conversingPlayer))
		end
	elseif ( screenID == "fp_furniture" ) then
		conversationScreen = screen:cloneScreen()
		
		local clonedConversation = LuaConversationScreen(conversationScreen)
			
		if ( clonedConversation ~= nil ) then
			self:addFurniture(clonedConversation, getGCWDiscount(conversingPlayer))
		end
		
	elseif (screenID == "purchased") then
		conversationScreen = self:processPurchase(conversingPlayer, conversationTemplate, selectedOption, conversingNPC)
	elseif (screenID == "fp_installations") then
		conversationScreen = screen:cloneScreen()
		
		local clonedConversation = LuaConversationScreen(conversationScreen)
			
		if (clonedConversation ~= nil) then
			self:addInstallations(clonedConversation, getGCWDiscount(conversingPlayer))
		end
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
	--self:updateScreenWithBribe(player, conversationTemplate, screenCopy)
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

function recruiter_convo_handler:addUniforms(thisConversation, gcwDiscount)
	printf("pure recruiter_convo_handler:addUniforms(thisConversation)")
end

function recruiter_convo_handler:addFurniture(thisConversation, gcwDiscount)
	printf("pure recruiter_convo_handler:addFurniture(thisConversation)")
end

function recruiter_convo_handler:addWeaponsArmor(thisConversation, gcwDiscount)
	printf("pure recruiter_convo_handler:addWeaponsArmor(thisConversation, gcwDiscount)")
end

function recruiter_convo_handler:addInstallations(thisConversation, gcwDiscount)
	printf("pure recruiter_convo_handler:addInstallations(thisConversation, gcwDiscount)")
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
	
	if (faction == self:getEnemyFactionHashCode() or (faction == self:getRecruiterFactionHashCode() and playerObject:getFactionStanding(self:getRecruiterFactionString()) < 200 )) then
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
	elseif (playerObject:getFactionStanding(self:getRecruiterFactionString()) < 200 ) then
		return convoTemplate:getScreen("greet_enemy")
	else
		return self:sendNeutralStart(play, conversationTemplate)
	end
	
	return nil
	
end

-- player, convo template, and the option number selected from the previous screen

function recruiter_convo_handler:processPurchase(conversingPlayer, conversationTemplate, selectedOption, conversingNPC)
	--print("processing armor/weapon purchase")
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
			
			-- if it's a weapon, use weapons_name if it's armor, use wearables_name
			if ( self:isArmor(itemname) or self:isUniform(itemname) ) then
				screenObject:setDialogTextTT("wearables_name", itemname)
			elseif ( self:isWeapon(itemname) ) then
				screenObject:setDialogTextTT("weapon_name", itemname)
			elseif ( self:isFurniture(itemname) ) then
			
				if ( self:isContainer(itemname) ) then
					screenObject:setDialogTextTT("container_name",itemname)
				else
					if (self:isTerminal(itemname)) then
						itemname = "frn_data_terminal"
					end
					screenObject:setDialogTextTT("frn_n",itemname)
				end
			elseif ( self:isInstallation(itemname)) then
				screenObject:setDialogTextTT("deed",itemname)
			else
				spatialChat(conversingNPC, "I'm sorry.  We were unable to determine the TYPE of item you are requesting")
			end
			
		
		elseif (awardresult == self.NOTENOUGHFACTION) then
		        local notEnoughScreen = convoTemplate:getScreen("purchased_not_enough")
				local screenObject = LuaConversationScreen(notEnoughScreen)
				conversationScreen = screenObject:cloneScreen()
								
				local screen = LuaConversationScreen(conversationScreen)
				screen:setDialogTextTO("@ui_charsheet:" .. self:getRecruiterFactionString() .. "faction")
				screen:setDialogTextDI(200)
				
		elseif (awardresult == self.INVENTORYFULL) then
		
			conversationScreen = convoTemplate:getScreen("inventory_full") -- Your inventory is full.  YOu must make some room before you can purchase.
		elseif ( awardresult == self.ITEMCOST ) then
			spatialChat(conversingNPC, "I'm sorry.  We were unable to price this item " .. selectedOption)
		elseif ( awardresult == self.INVENTORYERROR) then
			spatialChat(conversingNPC, "I don't see where you can put this item.")
		elseif (awardresult == self.TEMPLATEPATHERROR) then
			spatialChat(conversingNPC, "Sorry.  I was unable to locate the item ERROR: " .. selectedOption)
		elseif (awardresult == self.TEMPLATEPATHERROR ) then
			spatialChat(conversingNPC, "Sorry, I cannot GIVE this item to you at the moment.")
		end
	else
		spatialChat(converstingNPC, "I'm sorry.  I forgot what we were talking about")
	end
		
	return conversationScreen

end

function recruiter_convo_handler:awarditem(player, itemstring)
	local obj = LuaSceneObject(player)
	
	--print("awarding item " .. itemstring)
	local creatureObject = LuaCreatureObject(player)
	
	if ( creatureObject == nil or obj == nil ) then
		return self.GENERALERROR
	end
	
	local pPlayer = creatureObject:getPlayerObject()
	
	local playerObject = LuaPlayerObject(pPlayer)
	
	local pInventory = obj:getSlottedObject("inventory")
	
	local factionstanding = playerObject:getFactionStanding(self:getRecruiterFactionString())
		
	local itemcost = self:getItemCost(itemstring)

	-- additional error message
	if ( itemcost == nil ) then
		return self.ITEMCOST
	end
	
	if(itemcost > 4 and creatureObject:hasSkill("combat_smuggler_master") ) then
		--print("give a 25% discount")
		itemcost = itemcost * .75
	end
	
	itemcost  = itemcost * (1 - (getGCWDiscount(player)/100))
	
	if ( pInventory ~= nil and playerObject ~= nil and itemcost ~= nil ) then 
		--print("itemcost is " .. itemcost)
		if (factionstanding  >= (itemcost + 200)) then
			--print("faction is good")
			local pItem
			
			if (pInventory ~= nil) then
			
				local inventory = LuaSceneObject(pInventory)
				
				local slotsremaining = inventory:getContainerVolumeLimit() - inventory:getContainerObjectsSize()
				
				local bonusItemCount = self:getBonusItemCount(itemstring)
				
				if (slotsremaining < (1 + bonusItemCount)) then
					return self.INVENTORYFULL
				end	
			
				local res =  self:transferItem(player, pInventory, itemstring)
				if(res ~= self.SUCCESS) then
					return res
				end
							
				playerObject:decreaseFactionStanding(self:getRecruiterFactionString(),itemcost)
				
				if(bonusItemCount) then
					local bonusItems = self:getBonusItems(itemstring)
					if(bonusItems ~= nil) then
						for k, v in pairs(bonusItems) do
							res = self:transferItem(player, pInventory, v)
							if(res ~= self.SUCCESS) then
								return res
							end
						end
					end
				end	

				
			else
				-- temp message for additional item requisition failure
				creatureObject:sendSystemMessage("unable to get inventory")
				return self.INVENTORYERROR
			end
		
		else
			
			return self.NOTENOUGHFACTION
		end
	
	else
		return self.GENERALERROR
	end
	
	return self.SUCCESS

end


function recruiter_convo_handler:transferItem(player, pInventory, itemstring)
	--print("giving " .. itemstring)
	local templatePath = self:getTemplatePath(itemstring)
	
	if(templatePath == nil ) then
		return self.TEMPLATEPATHERROR
	end
	
	local inventoryObject = LuaSceneObject(pInventory)
	pItem = giveItem(pInventory, templatePath, -1)
	
	if (pItem ~= nil) then
	
		local item = LuaSceneObject(pItem)
	
		if ( item == nil ) then
			return self.GIVEERROR
		end
		
		if (self:isInstallation(itemstring)) then
			item:setObjectName("deed", itemstring)				
			local deed = LuaDeed(pItem)
			local genPath = self:getGeneratedObjectTemplate(itemstring)
			
			if (genPath == nil ) then
				return self.TEMPLATEPATHERROR
			end
						
			deed:setGeneratedObjectTemplate(genPath)
			
			local tano = LuaTangibleObject(pItem)
			if (tano == nil )  then
				print("unable to get tano.  can't set faction")
			else
				tano:setFaction(self:getRecruiterFactionHashCode())
			end
		end
		
		
		item:sendTo(player)

	else
		return self.GIVEERROR
	end
	
	return self.SUCCESS
end

function recruiter_convo_handler:getItemCost(itemstring)
	printf("pure recruiter_convo_handler:getItemCost(itemstring)")
end

function recruiter_convo_handler:getTemplatePath(strItem)
	printf("pure recruiter_convo_handler:getTemplatePath(strItem)")
end
function recruiter_convo_handler:isWeapon(strItem)

	printf("pure recruiter_convo_handler:isWeapon(strItem)")

end

function recruiter_convo_handler:isArmor(strItem)
	printf("pure recruiter_convo_handler:isArmor(strItem)")
end

function recruiter_convo_handler:isUniform(strItem)
	printf("pure recruiter_convo_handler:isUniform(strItem)")
	
end

function recruiter_convo_handler:isFurniture(strItem)
	printf("pure recruiter_convo_handler:isFurtinture(strItem)")
end

function recruiter_convo_handler:isContainer(strItem)
	printf("pure recruiter_convo_handler:isContainer(strItem)")
end

function recruiter_convo_handler:isTerminal(strItem)
	printf("pure recruiter_convo_handler:isTerminal(strItem)")
end

function recruiter_convo_handler:getBonusItems(strItem)
	printf("pure recruiter_convo_handler:getBonusItems(strItem)")
end

function recruiter_convo_handler:getBonusItemCount(strItem)
	printf("pure recruiter_convo_handler:getBonusItemCount(strItem)")
end