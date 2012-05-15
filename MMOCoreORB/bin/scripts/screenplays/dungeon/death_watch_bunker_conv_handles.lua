-- Foreman Quest
death_watch_foreman_handler = {  }
 
function death_watch_foreman_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	lastConversationScreen = nil
	
	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end
	
	local conversation = LuaConversationTemplate(conversationTemplate)
		
	local nextConversationScreen
	
	if (lastConversationScreen ~= nil) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		
		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		
		nextConversationScreen = conversation:getScreen(optionLink)
		
		if nextConversationScreen ~= nil then
			local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
			
			screenID = nextLuaConversationScreen:getScreenID()
			
			if (screenID == "convoscreen7_1" or screenID == "convoscreen6_1" or screenID == "convoscreen8") then
				creature:setScreenPlayState(1, "death_watch_foreman_stage")
			end
			
			if (screenID == "convoscreen7_1" or screenID == "convoscreen6_1" or screenID == "convoscreen9_1") then
				creature:setScreenPlayState(2, "death_watch_foreman_stage")
				DWB:startForemanQuestStage(1, conversingPlayer)				
			end
			
			if (screenID == "convoscreen16") then
				creature:setScreenPlayState(8, "death_watch_foreman_stage")
			end
			
			if (screenID == "convoscreen24" or screenID == "convoscreen26_1") then
				creature:setScreenPlayState(32, "death_watch_foreman_stage")
				creature:removeScreenPlayState(3, "death_watch_foreman_stage_failed")
			end
			
			if (screenID == "convoscreen30") then
				local creo = LuaSceneObject(conversingPlayer)
				pinventory = creo:getSlottedObject("inventory")
				local inventory = LuaSceneObject(pinventory)
				if (inventory:hasFullContainerObjects() == true) then
					nextConversationScreen = conversation:getScreen("convoscreen31")
				else
					creature:setScreenPlayState(128, "death_watch_foreman_stage")
					DWB:storeTime(conversingPlayer)					
					local pmineral = giveItem(pinventory, "object/tangible/loot/dungeon/death_watch_bunker/mining_drill_reward.iff", -1)
					
					if (pmineral == nil) then
						return 0
					end
					
					local mineral = LuaSceneObject(pmineral)
					mineral:sendTo(conversingPlayer)
				end
			end
		end
	else
		haldo_busy = readData(5996314 .. ":dwb:haldo_busy")
		haldo_failed = creature:hasScreenPlayState(1, "death_watch_foreman_stage_failed")
		haldo_killed = creature:hasScreenPlayState(2, "death_watch_foreman_stage_failed")
		pumps_failed = creature:hasScreenPlayState(3, "death_watch_foreman_stage_failed")
			
		spoken_to_foreman = creature:hasScreenPlayState(1, "death_watch_foreman_stage")
		started_haldo = creature:hasScreenPlayState(2, "death_watch_foreman_stage")
		finished_haldo = creature:hasScreenPlayState(4, "death_watch_foreman_stage")
		started_battery = creature:hasScreenPlayState(8, "death_watch_foreman_stage")
		finished_battery = creature:hasScreenPlayState(16, "death_watch_foreman_stage")
		started_pumps = creature:hasScreenPlayState(32, "death_watch_foreman_stage")
		finished_pumps = creature:hasScreenPlayState(64, "death_watch_foreman_stage")
		received_mineral = creature:hasScreenPlayState(128, "death_watch_foreman_stage")
		received_mineral_time_passed = DWB:checkTime(conversingPlayer)
		
		if haldo_failed == 1 then
			nextConversationScreen = conversation:getScreen("convoscreen12")
		elseif spoken_to_foreman == 0 then
			if haldo_busy == 0 then
				nextConversationScreen = conversation:getInitialScreen()
			else
				nextConversationScreen = conversation:getScreen("convoscreen11")
			end
		elseif started_haldo == 0 then
			if haldo_busy == 0 then
				nextConversationScreen = conversation:getScreen("convoscreen9")
			else
				nextConversationScreen = conversation:getScreen("convoscreen11")
			end
		elseif finished_haldo == 0 then
			local creo = LuaSceneObject(conversingPlayer)
			inventory = creo:getSlottedObject("inventory")
			pBattery = getContainerObjectByTemplate(inventory, "object/tangible/dungeon/death_watch_bunker/drill_battery.iff", true)
			if pBattery == nil then
				nextConversationScreen = conversation:getScreen("convoscreen10")
			else
				creature:setScreenPlayState(4, "death_watch_foreman_stage")
				writeData(5996314 .. ":dwb:haldo_busy", 0)
				writeData(5996314 .. ":dwb:haldo_player", 0)
				if haldo_killed == 1 then
					nextConversationScreen = conversation:getScreen("convoscreen13")
				else
					nextConversationScreen = conversation:getScreen("convoscreen14")
				end
			end
		elseif started_battery == 0 then
			nextConversationScreen = conversation:getScreen("convoscreen17")
		elseif finished_battery == 0 then
			local creo = LuaSceneObject(conversingPlayer)
			inventory = creo:getSlottedObject("inventory")
			pBattery = getContainerObjectByTemplate(inventory, "object/tangible/dungeon/death_watch_bunker/drill_battery_clean.iff", true)
			if pBattery == nil then
				nextConversationScreen = conversation:getScreen("convoscreen18")
			else
				creature:setScreenPlayState(16, "death_watch_foreman_stage")
				battery = LuaSceneObject(pBattery)
				battery:destroyObjectFromWorld()
				nextConversationScreen = conversation:getScreen("convoscreen19")
			end
		elseif started_pumps == 0 then	
			nextConversationScreen = conversation:getScreen("convoscreen26")
		elseif finished_pumps == 0 then
			if pumps_failed == 1 then
				nextConversationScreen = conversation:getScreen("convoscreen26")
			else
				nextConversationScreen = conversation:getScreen("convoscreen25")
			end			
		elseif received_mineral == 0 then
			nextConversationScreen = conversation:getScreen("convoscreen27")
		elseif received_mineral_time_passed == false then
			nextConversationScreen = conversation:getScreen("convoscreen32")
		elseif received_mineral_time_passed == true then
			local creo = LuaSceneObject(conversingPlayer)
			pinventory = creo:getSlottedObject("inventory")
			local inventory = LuaSceneObject(pinventory)
			if (inventory:hasFullContainerObjects() == true) then
				nextConversationScreen = conversation:getScreen("convoscreen34")
			else
				DWB:storeTime(conversingPlayer)
				nextConversationScreen = conversation:getScreen("convoscreen33")
				
				local pmineral = giveItem(pinventory, "object/tangible/loot/dungeon/death_watch_bunker/mining_drill_reward.iff", -1)
				
				if (pmineral == nil) then
					return 0
				end
				
				local mineral = LuaSceneObject(pmineral)
				mineral:sendTo(conversingPlayer)
			end
		else
			printf("[ERROR] Invalid else case in DWB: Foreman Conversation\n")
		end
	end
	return nextConversationScreen

end

function death_watch_foreman_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

-- Haldo Sub-Quest
death_watch_insane_miner_handler = {  }
 
function death_watch_insane_miner_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	lastConversationScreen = nil
	
	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end
	
	local conversation = LuaConversationTemplate(conversationTemplate)
		
	local nextConversationScreen
	
	if (lastConversationScreen ~= nil) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		
		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		
		nextConversationScreen = conversation:getScreen(optionLink)
		
		if nextConversationScreen ~= nil then
			local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
			
			screenID = nextLuaConversationScreen:getScreenID()
			
			if (screenID == "convoscreen7") then
				creature:setScreenPlayState(4, "death_watch_insane_miner_stage")
				local creo = LuaSceneObject(conversingPlayer)
				inventory = creo:getSlottedObject("inventory")
				pCure = getContainerObjectByTemplate(inventory, "object/tangible/dungeon/death_watch_bunker/crazed_miner_medicine.iff", true)
				if pCure ~= nil then
					local cure = LuaSceneObject(pCure)
					cure:destroyObjectFromWorld()
					
					local pbattery = giveItem(inventory,"object/tangible/dungeon/death_watch_bunker/drill_battery.iff", -1)
					
					if (pbattery == nil) then
						return 0
					end
					
					local obattery = LuaSceneObject(pbattery)
					obattery:sendTo(conversingPlayer)
				end
			end
			
			if (screenID == "convoscreen2_2") then
				minerid = readData(5996314 .. ":dwb:haldo")
				local minero = getSceneObject(minerid)
				local miner = LuaCreatureObject(minero)
				miner:setOptionsBitmask(128)
				miner:setPvpStatusBitmask(21)
				miner:engageCombat(conversingPlayer)			
			end
		end
	else
		haldo_failed = creature:hasScreenPlayState(1, "death_watch_foreman_stage_failed")
		started_haldo = creature:hasScreenPlayState(2, "death_watch_foreman_stage")
		spoken_to_haldo = creature:hasScreenPlayState(1, "death_watch_miner_spoken")
		finished_haldo = creature:hasScreenPlayState(4, "death_watch_foreman_stage")
		
		if haldo_failed == 1 or started_haldo == 0 then
			nextConversationScreen = conversation:getScreen("convoscreen8")
		elseif finished_haldo == 1 then
			nextConversationScreen = conversation:getScreen("convoscreen7")
		else
			local creo = LuaSceneObject(conversingPlayer)
			inventory = creo:getSlottedObject("inventory")
			pCure = getContainerObjectByTemplate(inventory, "object/tangible/dungeon/death_watch_bunker/crazed_miner_medicine.iff", true)
			if pCure == nil then
				if spoken_to_haldo == 0 then
					nextConversationScreen = conversation:getScreen("convoscreen1")
					creature:setScreenPlayState(1, "death_watch_miner_spoken")
				else
					nextConversationScreen = conversation:getScreen("convoscreen5")
				end
			else
				if spoken_to_haldo == 0 then
					nextConversationScreen = conversation:getScreen("convoscreen8")
					creature:setScreenPlayState(1, "death_watch_miner_spoken")
				else
					nextConversationScreen = conversation:getScreen("convoscreen6")
				end
			end
		end
	end
	return nextConversationScreen

end

function death_watch_insane_miner_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

--G12-4J Medical Droid
death_watch_g12_4j_handler = {  }
 
function death_watch_g12_4j_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	lastConversationScreen = nil
	
	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end
	
	local conversation = LuaConversationTemplate(conversationTemplate)
		
	local nextConversationScreen
	
	if (lastConversationScreen ~= nil) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		
		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		
		nextConversationScreen = conversation:getScreen(optionLink)
		
		if nextConversationScreen ~= nil then
			local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
			
			screenID = nextLuaConversationScreen:getScreenID()
			
			if (screenID == "convoscreen4") then
				local creo = LuaSceneObject(conversingPlayer)
				inventory = creo:getSlottedObject("inventory")
				
				local pcure = giveItem(inventory, "object/tangible/dungeon/death_watch_bunker/crazed_miner_medicine.iff", -1)
				
				if (pcure == nil) then
					return 0
				end
				
				local ocure = LuaSceneObject(pcure)
				ocure:sendTo(conversingPlayer)
			end
		end
	else
		haldo_failed = creature:hasScreenPlayState(1, "death_watch_foreman_stage_failed")
		started_haldo = creature:hasScreenPlayState(2, "death_watch_foreman_stage")
		finished_haldo = creature:hasScreenPlayState(4, "death_watch_foreman_stage")
		
		if haldo_failed == 1 or finished_haldo == 1 or started_haldo == 0 then
			nextConversationScreen = conversation:getInitialScreen()
		else
			local creo = LuaSceneObject(conversingPlayer)
			pinventory = creo:getSlottedObject("inventory")
			local inventory = LuaSceneObject(pinventory)
			if (inventory:hasFullContainerObjects() == true) then
				nextConversationScreen = conversation:getScreen("convoscreen5")
			else
				nextConversationScreen = conversation:getScreen("convoscreen3")
			end
		end
	end
	return nextConversationScreen

end

function death_watch_g12_4j_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

-- Treadwell Workshop Droid
death_watch_workshop_droid_handler = {  }
 
function death_watch_workshop_droid_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	lastConversationScreen = nil
	
	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end
	
	local conversation = LuaConversationTemplate(conversationTemplate)
		
	local nextConversationScreen
	
	if (lastConversationScreen ~= nil) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		
		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		
		nextConversationScreen = conversation:getScreen(optionLink)
		
		if nextConversationScreen ~= nil then
			local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
			
			screenID = nextLuaConversationScreen:getScreenID()
			
			if (screenID == "convoscreen4") then
				local creo = LuaSceneObject(conversingPlayer)
				inventory = creo:getSlottedObject("inventory")

				pOld = getContainerObjectByTemplate(inventory, "object/tangible/dungeon/death_watch_bunker/drill_battery.iff", true)
				if pOld ~= nil then
					local old = LuaSceneObject(pOld)
					old:destroyObjectFromWorld()
					
					local pbattery = giveItem(inventory, "object/tangible/dungeon/death_watch_bunker/drill_battery_clean.iff", -1)
					
					if (pbattery == nil) then
						return 0
					end
					
					local obattery = LuaSceneObject(pbattery)
					creature:sendSystemMessage("@dungeon/death_watch:battery_cleaned")
					obattery:sendTo(conversingPlayer)
				end
			end
		end
	else
		started_battery = creature:hasScreenPlayState(8, "death_watch_foreman_stage")
		finished_battery = creature:hasScreenPlayState(16, "death_watch_foreman_stage")
		
		if finished_battery == 1 then
			nextConversationScreen = conversation:getInitialScreen()
		elseif started_battery == 0 then
			nextConversationScreen = conversation:getInitialScreen()
			creature:sendSystemMessage("@dungeon/death_watch:not_authorized")
		else
			local creo = LuaSceneObject(conversingPlayer)
			pinventory = creo:getSlottedObject("inventory")
			
			pCure = getContainerObjectByTemplate(pinventory, "object/tangible/dungeon/death_watch_bunker/drill_battery.iff", true)
			
			if pCure == nil then
				nextConversationScreen = conversation:getInitialScreen()
				creature:sendSystemMessage("@dungeon/death_watch:need_battery")
			else
				nextConversationScreen = conversation:getScreen("convoscreen3")	
			end
		end
	end
	return nextConversationScreen

end

function death_watch_workshop_droid_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

-- Rescue Scientist: Rebel Sidequest
death_watch_rescue_scientist_handler = {  }
 
function death_watch_rescue_scientist_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	lastConversationScreen = nil
	
	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end
	
	local conversation = LuaConversationTemplate(conversationTemplate)
		
	local nextConversationScreen
	
	if (lastConversationScreen ~= nil) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		
		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		
		nextConversationScreen = conversation:getScreen(optionLink)
		
		if nextConversationScreen ~= nil then
			local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
			
		end
		
	else
		
		finished_quest = creature:hasScreenPlayState(2, "death_watch_bunker_rebel_sidequest")
		spoken_to_lutin = creature:hasScreenPlayState(1, "death_watch_bunker_rebel_sidequest")
				
		if (finished_quest == 1) then
			nextConversationScreen = conversation:getScreen("convoscreen2")
		elseif (spoken_to_lutin == 1) then
			nextConversationScreen = conversation:getInitialScreen()
			creature:setScreenPlayState(2, "death_watch_bunker_rebel_sidequest")
			--message = createParameterMessage(conversingPlayer, "@theme_park/messages:theme_park_credits_pp")
			--if message ~= nil then
			--	setParameterDI(message, 487)
			--	sendParameterMessage(message)
			--end
			creature:addCashCredits(487, true)
		else
			nextConversationScreen = conversation:getScreen("convoscreen3")
		end
	end
	return nextConversationScreen

end

function death_watch_rescue_scientist_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

-- Lutin Nightstalker: Rebel Sidequest
lutin_nightstalker_handler = {  }
 
function lutin_nightstalker_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	lastConversationScreen = nil
	
	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end
	
	local conversation = LuaConversationTemplate(conversationTemplate)
		
	local nextConversationScreen
	
	if (lastConversationScreen ~= nil) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		
		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		
		nextConversationScreen = conversation:getScreen(optionLink)
		
		if nextConversationScreen ~= nil then
			local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
			
			if (nextLuaConversationScreen:getScreenID() == "excellent" or nextLuaConversationScreen:getScreenID() == "location" or (nextLuaConversationScreen:getScreenID() == "maytheforce" and luaLastConversationScreen:getScreenID() == "convoscreen4")) then
				creature:setScreenPlayState(1, "death_watch_bunker_rebel_sidequest")--gain entry permission
			elseif (nextLuaConversationScreen:getScreenID() == "quit") then
				creature:removeScreenPlayState(1, "death_watch_bunker_rebel_sidequest")
			end
		end		
	else
		
		finished_quest = creature:hasScreenPlayState(2, "death_watch_bunker_rebel_sidequest")
		spoken_to_lutin = creature:hasScreenPlayState(1, "death_watch_bunker_rebel_sidequest")

		-- NEED TO FIGURE OUT WHAT KIND OF QUESTS BLOCK EACH OTHER
		--busy = readScreenPlayData(conversingPlayer, "global", "occupied")
		--if busy ~= "death_watch_bunker_rebel_sidequest" and busy ~= "" then
		--	busy = 1
		--else
		--	busy = 0
		--end 

		factionmatch = 0

		local playerObjectPointer = creature:getPlayerObject()
		
		if (playerObjectPointer ~= nil) then
			local playerObject = LuaPlayerObject(playerObjectPointer)
			if (not playerObject:isOnLeave() and creature:isRebel()) then
				factionmatch = 1
			end
		end  
				
		if (finished_quest == 1) then
			nextConversationScreen = conversation:getScreen("return_successful")
		elseif (spoken_to_lutin == 1) then
			nextConversationScreen = conversation:getScreen("return_unsuccessful")
		--elseif (busy == 1) then
		--	nextConversationScreen = conversation:getScreen("busy")
		elseif (factionmatch == 0) then
			nextConversationScreen = conversation:getScreen("notaligned")
		else
			nextConversationScreen = conversation:getInitialScreen()
		end
	end
	return nextConversationScreen

end

function lutin_nightstalker_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

-- Commander D'krn: Imperial Sidequest
commander_dkrn_handler = {  }
 
function commander_dkrn_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	lastConversationScreen = nil
	
	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end
	
	local conversation = LuaConversationTemplate(conversationTemplate)
		
	local nextConversationScreen
	
	if (lastConversationScreen ~= nil) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		
		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		
		nextConversationScreen = conversation:getScreen(optionLink)
		
		if nextConversationScreen ~= nil then
			local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
		
			if (nextLuaConversationScreen:getScreenID() == "rightaway" or nextLuaConversationScreen:getScreenID() == "location") then
				creature:setScreenPlayState(1, "death_watch_bunker_imperial_sidequest")--gain entry permission
			elseif (nextLuaConversationScreen:getScreenID() == "finish") then
				local creo = LuaSceneObject(conversingPlayer)
				inventory = creo:getSlottedObject("inventory")
				pSample = getContainerObjectByTemplate(inventory, "object/tangible/loot/dungeon/death_watch_bunker/blood_vial.iff", true)
		
				if pSample ~= nil then	
					local sample = LuaSceneObject(pSample)
					sample:destroyObjectFromWorld()
				
					local playerObjectPointer = creature:getPlayerObject()
				
					if (playerObjectPointer ~= nil) then
						local playerObject = LuaPlayerObject(playerObjectPointer)
						playerObject:increaseFactionStanding("imperial", 500)
					end
			
					creature:setScreenPlayState(2, "death_watch_bunker_imperial_sidequest")
				end
			elseif (nextLuaConversationScreen:getScreenID() == "quit") then
				creature:removeScreenPlayState(1, "death_watch_bunker_imperial_sidequest")
			end
		end
		
	else
		
		finished_quest_before = creature:hasScreenPlayState(2, "death_watch_bunker_imperial_sidequest")
		spoken_to_dkrn = creature:hasScreenPlayState(1, "death_watch_bunker_imperial_sidequest")
		local creo = LuaSceneObject(conversingPlayer)
		inventory = creo:getSlottedObject("inventory")
		pSample = getContainerObjectByTemplate(inventory, "object/tangible/loot/dungeon/death_watch_bunker/blood_vial.iff", true)

		if (pSample ~= nil) then
			finished_quest = true
		else
			finished_quest = false
		end

		-- NEED TO FIGURE OUT WHAT KIND OF QUESTS BLOCK EACH OTHER
		--busy = readScreenPlayData(conversingPlayer, "global", "occupied")
		--if busy ~= "death_watch_bunker_rebel_sidequest" and busy ~= "" then
		--	busy = 1
		--else
		--	busy = 0
		--end 

		factionmatch = 0

		local playerObjectPointer = creature:getPlayerObject()
		
		if (playerObjectPointer ~= nil) then
			local playerObject = LuaPlayerObject(playerObjectPointer)
			if (not playerObject:isOnLeave() and creature:isImperial()) then
				factionmatch = 1
			end
		end  
		
				
		if (finished_quest == true and finished_quest_before == 0) then
			nextConversationScreen = conversation:getScreen("return_successful")
		elseif (finished_quest == true and finished_quest_before == 1) then
			nextConversationScreen = conversation:getScreen("more_samples")
		elseif (spoken_to_dkrn == 1) then
			nextConversationScreen = conversation:getScreen("return_unsuccessful")
		--elseif (busy == 1) then
		--	nextConversationScreen = conversation:getScreen("busy")
		elseif (factionmatch == 0) then
			nextConversationScreen = conversation:getScreen("notaligned")
		else
			nextConversationScreen = conversation:getInitialScreen()
		end
	end
	return nextConversationScreen

end

function commander_dkrn_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

-- Boba Fett
boba_fett_handler = {  }
 
function boba_fett_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	lastConversationScreen = nil
	
	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end
	
	local conversation = LuaConversationTemplate(conversationTemplate)
		
	local nextConversationScreen
	
	if (lastConversationScreen ~= nil) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		
		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		
		nextConversationScreen = conversation:getScreen(optionLink)
		
		if nextConversationScreen ~= nil then
			local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
			
			if (nextLuaConversationScreen:getScreenID() == "convoscreen4" or nextLuaConversationScreen:getScreenID() == "convoscreen5") then
				creature:setScreenPlayState(1, "death_watch_bunker")--gain entry permission
			end
		end
	else
		
		jabba_themepark_completed = creature:hasScreenPlayState(1024, "themepark_jabba")
		spoken_to_boba = creature:hasScreenPlayState(1, "death_watch_bunker")
		
		--TESTING!! REMOVE THIS ONCE JABBA'S THEMEPARK IS IN!
		jabba_themepark_completed = 1
				
		if (jabba_themepark_completed == 0) then
			nextConversationScreen = conversation:getScreen("convoscreen8")
		elseif (spoken_to_boba == 1) then
			nextConversationScreen = conversation:getScreen("convoscreen6")
		else
			nextConversationScreen = conversation:getInitialScreen()
		end
	end
	return nextConversationScreen

end

function boba_fett_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end