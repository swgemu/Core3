TutorialScreenPlay = ScreenPlay:new {
	numberOfActs = 1
}

registerScreenPlay("TutorialScreenPlay", false);

imperial_officer_3_handler = {  }
 
-- imperial officer 3
function imperial_officer_3_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	local lastConversationScreen = nil
	
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
		
		if (nextConversationScreen ~= nil) then
			local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)

			if (nextLuaConversationScreen:getScreenID() == "convoscreen5") then
				--give player weapons
				local creatureSceneObject = LuaSceneObject(conversingPlayer)
				inventory = creatureSceneObject:getSlottedObject("inventory")
				local inventoryObj = LuaSceneObject(inventory)
						
				addStartingWeaponsInto(conversingPlayer, inventory)
			
				--testing datapad
				--addTestItem(conversingPlayer, inventory)
			
				creature:sendSystemMessage("@newbie_tutorial/system_messages:receive_weapon")
				
			end
		
			if (nextLuaConversationScreen:getScreenID() == "convoscreen6") then
				writeData(creature:getObjectID() .. ":tutorial:officer3flag", 1)
			end
		
		end
	else
		
		--Get the initial screen.
		officer3flag = readData(creature:getObjectID() .. ":tutorial:officer3flag")
		
		if (officer3flag == 0) then
			nextConversationScreen = conversation:getInitialScreen()
			
		elseif (officer3flag == 1) then
			nextConversationScreen = conversation:getScreen("altscreen1")		
		else
			nextConversationScreen = conversation:getScreen("altscreen2")
		end
	end
	return nextConversationScreen

end

function imperial_officer_3_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

-- imperial officer 5
imperial_officer_5_handler = {  }
 
function imperial_officer_5_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	local lastConversationScreen = nil
	
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
		
		if (nextConversationScreen ~= nil) then
			local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
		
			if (nextLuaConversationScreen:getScreenID() == "convoscreen2") then
				writeData(creature:getObjectID() .. ":tutorial:officer5flag", 1)
				createEvent(1000, "TutorialScreenPlay", "stopOfficer5", conversingPlayer)
			end
		end
	else
		
		--Get the initial screen.
		officer5flag = readData(creature:getObjectID() .. ":tutorial:officer5flag")
		off5ready = readData(creature:getObjectID() .. ":tutorial:off5ready")
			
		if (off5ready == 0) then
			nextConversationScreen = conversation:getScreen("convoscreen4")
		elseif (officer5flag == 0) then
			nextConversationScreen = conversation:getInitialScreen() 
		else
			nextConversationScreen = conversation:getScreen("convoscreen3")
		end
	end
	return nextConversationScreen

end

function imperial_officer_5_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

-- imperial officer 6
imperial_officer_6_handler = {  }
 
function imperial_officer_6_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	local lastConversationScreen = nil
	
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
		local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
		
		if (nextLuaConversationScreen:getScreenID() == "convoscreen2") then
			writeData(creature:getObjectID() .. ":tutorial:officer6flag", 1)
		end
	else
		
		--Get the initial screen.
		officer5flag = readData(creature:getObjectID() .. ":tutorial:officer5flag")
		
		if (officer5flag == 0) then
			nextConversationScreen = conversation:getScreen("convoscreen3")
		else
			nextConversationScreen = conversation:getInitialScreen()
			
			terminal = readData(creature:getObjectID() .. ":tutorial:travelTerminal")
			local travelTerminal = getSceneObject(terminal)
			setAuthorizationState(travelTerminal, true)		
		end
	end
	return nextConversationScreen

end

function imperial_officer_6_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

-- commoner
commoner_handler = {  }
 
function commoner_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	local lastConversationScreen = nil
	
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
		local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
	else
		local commonerID = creature:getTargetID()
		
		cid = readData(commonerID .. ":tutorial:cid")

		--Get the initial screen.
		
		if (cid == 1) then
			nextConversationScreen = conversation:getScreen("convoscreen1")
		elseif cid == 2 then
			nextConversationScreen = conversation:getScreen("convoscreen2")
		elseif cid == 3 then
			nextConversationScreen = conversation:getScreen("convoscreen3")
		elseif cid == 4 then
			nextConversationScreen = conversation:getScreen("convoscreen4")
		elseif cid == 5 then
			nextConversationScreen = conversation:getScreen("convoscreen5")
		elseif cid == 6 then
			nextConversationScreen = conversation:getScreen("convoscreen6")
		elseif cid == 7 then
			nextConversationScreen = conversation:getScreen("convoscreen7")	
		else
			nextConversationScreen = conversation:getInitialScreen()			
		end
	end
	return nextConversationScreen

end

function commoner_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

function TutorialScreenPlay:spawnObjects(creatureObject)
	local creature = LuaSceneObject(creatureObject)
	local targetCellObject = LuaSceneObject(creature:getParent())
	local buildingObject = LuaBuildingObject(targetCellObject:getParent())
	local spawnedSceneObject = LuaSceneObject(nil)
	local spawnedCreatureObject = LuaCreatureObject(nil)
	
	if buildingObject:getServerObjectCRC() ~= 3369536646 then
		return 0
	end

	writeData(creature:getObjectID() .. ":tutorial:sound", 1)
	writeData(creature:getObjectID() .. ":tutorial:banditdebug", 0)

	-- ** ROOM 1: Welcome **	
	--spawn stormtroopers
	targetCellObject:_setObject(buildingObject:getCell(1))
	
	spawnedPointer = spawnMobile("tutorial", "stormtrooper_filler_tutorial", 0, -2.4, 0, -17.4, 0, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(1, 0, 0, 0)
	
	spawnedPointer = spawnMobile("tutorial", "stormtrooper_filler_tutorial", 0, 2.5, 0, -17.4, 0, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(1, 0, 0, 0)
	
	
	-- ** ROOM 2: Conversations & Items **
	-- ROOM3 STATE
	--state = creature:hasScreenPlayState(512, "tutorial")
	
	targetCellObject:_setObject(buildingObject:getCell(2))
	
	writeData(creature:getObjectID() .. ":tutorial:moveitemroom", 0)
	writeData(creature:getObjectID() .. ":tutorial:movecommerceroom", 0)
	
	--spawn commoners
	--shared_dressed_commoner_fat_zabrak_male_02.iff says refugee1 darn_empire
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 0, 30.2, 0, -43.1, -11.81, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(0.9945, -0.103, 0, 0)
	
	--if state == 0 then
		createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "refugees", spawnedPointer)	
	--end

	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 1)
	writeData(creature:getObjectID() .. ":tutorial:refugee1", spawnedSceneObject:getObjectID())
	
	--shared_dressed_commoner_naboo_human_female_04.iff says leave_me_alone
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 0, 28.6, 0, -42.9, -66.58, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(0.835, 0, 0.549, 0)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 1)
	writeData(creature:getObjectID() .. ":tutorial:refugee2", spawnedSceneObject:getObjectID())
	
	--shared_dressed_commoner_naboo_human_male_01.iff says 
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 0, 25, 0, -43.5, -28.87, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(0.97, 0, 0.249, 0)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 1)
	writeData(creature:getObjectID() .. ":tutorial:refugee3", spawnedSceneObject:getObjectID())

	--spawn officer
	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_1", 0, 26.7, 0, -31.9, -90.47, targetCellObject:getObjectID())
	
	--if state == 0 then
		createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "officer1", spawnedPointer) --move observer
	--end
	
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(-0.71, 0, 0.71, 0)
	
	writeData(creature:getObjectID() .. ":tutorial:officer1", spawnedSceneObject:getObjectID())
	
	--drum
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/container/drum/tatt_drum_1.iff", 19, 0, -23, targetCellObject:getObjectID(), 0.71, 0, -0.71, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setContainerAllowPermission("player", OPEN + MOVEOUT);
	spawnedSceneObject:setContainerInheritPermissionsFromParent(false)
	
	writeData(creature:getObjectID() .. ":tutorial:drum", spawnedSceneObject:getObjectID())
	
	-- add the starting items (except weapons) to the drum	
	
	--if state == 0 then
		addStartingItemsInto(creatureObject, spawnedPointer)
	
		local i = 0
	
		while (spawnedSceneObject:getContainerObjectsSize() > i) do
			local item = spawnedSceneObject:getContainerObject(i)
			local itemObj = LuaSceneObject(item)
		
			--check if its maroj melon, register use now		
			if itemObj:getGameObjectType() == 8202 then -- food
				createObserver(OBJECTRADIALUSED, "TutorialScreenPlay", "foodUsed", item)
			end 
			i = i + 1
		end
		
		--creature:setScreenPlayState(1, "tutorial")
	--end
	
	
	-- ** ROOM 3: Banks & Bazaars **
	-- ROOM4 STATE	
	targetCellObject:_setObject(buildingObject:getCell(3))
	
	--spawn second officer banker
	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_2", 0, 44, 0, 2.2, 130.53, targetCellObject:getObjectID())
	
	createObserver(STARTCONVERSATION, "TutorialScreenPlay", "bankerStartConversation", spawnedPointer)
	
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(0.418, 0, 0.908, 0)
	writeData(creature:getObjectID() .. ":tutorial:officer2", spawnedSceneObject:getObjectID())
	
	--spawn commoner
	--shared_dressed_commoner_naboo_bothan_male_02.iff
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 0, 51.1, 0, -16, -88.21, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(0.718, 0, -0.696, 0)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 7)
	
	--spawn bank
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_bank.iff", 50.8, -0.5, -3.5, targetCellObject:getObjectID(), 0.71, 0, -0.71, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	
	writeData(creature:getObjectID() .. ":tutorial:bank", spawnedSceneObject:getObjectID())
	writeData(creature:getObjectID() .. ":tutorial:bankflag", 0)
	writeData(creature:getObjectID() .. ":tutorial:bankfly", 0)
	
	--spawn bazaar
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_bazaar.iff", 38.4, 0, -17.7, targetCellObject:getObjectID(), 0.97, 0, 0.241, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	
	writeData(creature:getObjectID() .. ":tutorial:bazaar", spawnedSceneObject:getObjectID())
	writeData(creature:getObjectID() .. ":tutorial:bazaarflag", 0)
	writeData(creature:getObjectID() .. ":tutorial:bazaarfly", 0)
	
	
	-- ** ROOM 4 **
	-- ROOM5 State
	targetCellObject:_setObject(buildingObject:getCell(4))
	--shared_dressed_commoner_old_human_female_02.iff
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_1", 0, 51.1, -7, -51, -107.65, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cdistance", 7)
	
	--spawnedSceneObject:updateDirection(0.589, 0, -0.807, 0)
	
	--if state == 0 then
		createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "commoner_spatial", spawnedPointer)
	--end
	
	--shared_dressed_commoner_old_zabrak_male_02.iff
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_2", 0, 51.5, -7, -53, -50.66, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 2)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cdistance", 7)
	
	--spawnedSceneObject:updateDirection(0.903, 0, -0.428, 0)
	
	createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "commoner_spatial", spawnedPointer)


	--shared_dressed_commoner_naboo_moncal_male_02.iff
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_3", 0, 47.4, -7, -58.7, -71.18, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 3)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cdistance", 6)
	
	--spawnedSceneObject:updateDirection(0.813, 0, -0.582, 0)
	
	--if state == 0 then
		createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "commoner_spatial", spawnedPointer)
	--end
	
	--shared_dressed_stormtrooper_m.iff (-51.49?)
	spawnedPointer = spawnMobile("tutorial", "stormtrooper_filler_tutorial", 0, 26.2, -7, -51.9, 180, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(0, 0, 1, 0)
	
	--shared_dressed_stormtrooper_m.iff
	spawnedPointer = spawnMobile("tutorial", "stormtrooper_filler_tutorial", 0, 26.2, -7, -61.3, 0, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(1, 0, 0, 0)
		
	--** ROOM 5: Cloning & Insurance **
	-- ROOM6 STATE
	--state = creature:hasScreenPlayState(65536, "tutorial")
	
	targetCellObject:_setObject(buildingObject:getCell(5))
	
	--spawn q-3p0
	spawnedPointer = spawnMobile("tutorial", "protocol_droid_3po_silver", 0, 11.9, -7, -56.4, 90, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)

	--if state == 0 then
		createObserver(STOPCONVERSATION, "TutorialScreenPlay", "cloningDroidStopConversation", spawnedPointer)
	--end
	
	writeData(creature:getObjectID() .. ":tutorial:protocol", spawnedSceneObject:getObjectID())
	--spawnedSceneObject:updateDirection(0.707, 0, 0.707, 0)
	
	--spawn clone terminal
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_cloning.iff", 3, -7, -56.5, targetCellObject:getObjectID(), 0.707, 0, 0.707, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	
	--if state == 0 then
		createObserver(OBJECTRADIALUSED, "TutorialScreenPlay", "cloningUseObserver", spawnedPointer)
	--end
	
	writeData(creature:getObjectID() .. ":tutorial:clone", spawnedSceneObject:getObjectID())
	
	--spawn insurance terminal
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_insurance.iff", 8.4, -7, -64, targetCellObject:getObjectID(), 1, 0, 0, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	
	--if state == 0 then
		createObserver(OBJECTRADIALUSED, "TutorialScreenPlay", "insuranceUseObserver", spawnedPointer)
	--end
	
	writeData(creature:getObjectID() .. ":tutorial:insurance", spawnedSceneObject:getObjectID())
	
	--spawn npc panic 1
	--shared_dressed_commoner_tatooine_bith_male_05.iff
	spawnedPointer = spawnMobile("tutorial", "panic_npc_1", 0, -3.3, -7, -75.6, 0, targetCellObject:getObjectID())
	
	--if state == 0 then
		createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "panic1MoveObserver", spawnedPointer) --move observer
	--end

	--** ROOM 6 **
	--spawn nervous guy in hallway
	-- ROOM7 STATE
	--state = creature:hasScreenPlayState(262144, "tutorial")
	
	targetCellObject:_setObject(buildingObject:getCell(6))
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner", 0, 20.1, -4, -81.5, -132.74, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(creature:getObjectID() .. ":tutorial:nervous1npc", spawnedSceneObject:getObjectID())
	--spawnedSceneObject:updateDirection(0.4005, 0, -0.916, 0)

	--if state == 0 then
		createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "nervous1MoveObserver", spawnedPointer) 
	--end
	
	--** ROOM 7 **
	-- ROOM8 STATE
	--state = creature:hasScreenPlayState(262144, "tutorial")
	
	targetCellObject:_setObject(buildingObject:getCell(7))

	--spawn officer3
	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_3", 0, 38.1, -7, -79.7, 0, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(creature:getObjectID() .. ":tutorial:officer3flag", 0)
	writeData(creature:getObjectID() .. ":tutorial:officer3", spawnedSceneObject:getObjectID())
	
	--if state == 0 then
		createObserver(STARTCONVERSATION, "TutorialScreenPlay", "officer3StartConversation", spawnedPointer)
		createObserver(STOPCONVERSATION, "TutorialScreenPlay", "officer3StopConversation", spawnedPointer)
		createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "converseWithOfficer3Observer", spawnedPointer) --move observer
	--end
	
	-- ** ROOM 14(don't ask) **
	targetCellObject:_setObject(buildingObject:getCell(14))

	--spawn debris	
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/newbie_tutorial/debris.iff", 76.9, -4, -94.3, targetCellObject:getObjectID(), 1, 0, 0, 0)
	
	--if state == 0 then
		createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "nearDebrisObserver", spawnedPointer) --move observer
		createObserver(OBJECTDESTRUCTION, "TutorialScreenPlay", "debrisDestroyedObserver", spawnedPointer) --destroy observer
	--end
	
	spawnedSceneObject:_setObject(spawnedPointer)			
	writeData(creature:getObjectID() .. ":tutorial:debrisoid", spawnedSceneObject:getObjectID()) 
	
	-- ** ROOM 8 **
	-- ROOM9 STATE
	--state = creature:hasScreenPlayState(524288, "tutorial")
	
	targetCellObject:_setObject(buildingObject:getCell(8))

	--spawn retard to kill
	spawnedPointer = spawnMobile("tutorial", "bandit_tutorial_1", 0, 38.1, -5.9, -113.4, 90, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(0.707, 0, 0.707, 0)
	
	writeData(creature:getObjectID() .. ":tutorial:banditflag", 0)
	writeData(creature:getObjectID() .. ":tutorial:banditdead", 0)
	
	--register damage observer
	--if state == 0 then
		createObserver(DAMAGERECEIVED, "TutorialScreenPlay", "banditDamageObserver", spawnedPointer) --damage observer
		createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "banditMoveObserver", spawnedPointer)
		createObserver(OBJECTDESTRUCTION, "TutorialScreenPlay", "banditDestroyObserver", spawnedPointer)
		createObserver(POSITIONCHANGED, "TutorialScreenPlay", "part4StartObserver", creatureObject) --move observer
		createObserver(POSITIONCHANGED, "TutorialScreenPlay", "part5StartObserver", creatureObject) --move observer
	--end

	--** ROOM 9: Skill Trainers **
	-- ROOM10 STATE
	--state = creature:hasScreenPlayState(1048576, "tutorial")
	
	targetCellObject:_setObject(buildingObject:getCell(9))	
	
	--spawn another commoner: celeb_guy1
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 0, -1, -4.2, -118.2, 47.08, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(0.838, 0.545, 0, 0)
	writeData(creature:getObjectID() .. ":tutorial:commoner91", spawnedSceneObject:getObjectID())
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 2)
	
	--spawn another commoner: celeb_guy4
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 0, 1.4, -4.2, -132, 27.88, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(0.97, 0.241, 0, 0)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 3)

	--spawn another commoner: celeb_guy3	
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 0, 13.1, -4.2, -119.8, -43.78, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(0.927, 0, -0.373, 0)	
	spawnedCreatureObject = LuaCreatureObject(spawnedPointer)
	spawnedCreatureObject:setState(STATESITTINGONCHAIR)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 4)
	
	--spawn another commoner: celeb_guy2
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 0, 13.145, -4.2, -106.292, -128.18, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(0.436, 0, -0.899, 0)
	spawnedCreatureObject = LuaCreatureObject(spawnedPointer)
	spawnedCreatureObject:setState(STATESITTINGONCHAIR)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 5)
	
	--spawn another commoner: celeb_guy5
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 0, -0.8, -4.2, -108.2, 123.09, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(0.476, 0, 0.879, 0)
	writeData(creature:getObjectID() .. ":tutorial:commoner92", spawnedSceneObject:getObjectID())
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 6)
	
	--imperial officer 4
	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_4", 0, 2.1, -4.2, -123.8, 27.88, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(creature:getObjectID() .. ":tutorial:officer4", spawnedSceneObject:getObjectID())
	
	writeData(creature:getObjectID() .. ":tutorial:officer4flag", 0)
	
	--spawnedSceneObject:updateDirection(0.97, 0, 0.241, 0)
	
	--if state == 0 then
		createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "officer4", spawnedPointer) --move observer
		createObserver(SELECTCONVERSATION, "TutorialScreenPlay", "officer4select", spawnedPointer)
	--end

	-- trainer
	local player = LuaCreatureObject(creatureObject)
	
	--starting skills:
	  -- social_entertainer_novice
	  -- outdoors_scout_novice
	  -- science_medic_novice
	  -- crafting_artisan_novice
	  -- combat_marksman_novice
	  -- combat_brawler_novice

	if (player:hasSkill("social_entertainer_novice")) then
		trainerTemplate = "trainer_entertainer"
		player:removeSkill("social_entertainer_novice")
		writeData(creature:getObjectID() .. ":tutorial:skill", 0)
	elseif (player:hasSkill("outdoors_scout_novice")) then
		trainerTemplate = "trainer_scout"
		player:removeSkill("outdoors_scout_novice")
		writeData(creature:getObjectID() .. ":tutorial:skill", 1)
	elseif (player:hasSkill("science_medic_novice")) then
		trainerTemplate = "trainer_medic"
		player:removeSkill("science_medic_novice")
		writeData(creature:getObjectID() .. ":tutorial:skill", 2)
	elseif (player:hasSkill("crafting_artisan_novice")) then
		trainerTemplate = "trainer_artisan"
		player:removeSkill("crafting_artisan_novice")
		writeData(creature:getObjectID() .. ":tutorial:skill", 3)
	elseif (player:hasSkill("combat_marksman_novice")) then
		trainerTemplate = "trainer_marksman"
		player:removeSkill("combat_marksman_novice")
		writeData(creature:getObjectID() .. ":tutorial:skill", 4)
	else
		trainerTemplate = "trainer_brawler"
		player:removeSkill("combat_brawler_novice")
		writeData(creature:getObjectID() .. ":tutorial:skill", 5)
	end
	
	spawnedPointer = spawnMobile("tutorial", trainerTemplate, 0, 7.1, -4.2, -128.2, -25.41, targetCellObject:getObjectID())
	
	--if state == 0 then
		createObserver(STOPCONVERSATION, "TutorialScreenPlay", "stopSkillTrainer", spawnedPointer)
	--end
	
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(creature:getObjectID() .. ":tutorial:skillTrainer", spawnedSceneObject:getObjectID())
	--spawnedSceneObject:updateDirection(0.975, 0, -0.220, 0)

	--** ROOM 10: Missions **
	-- ROOM11 STATE
	--state = creature:hasScreenPlayState(2097152, "tutorial")
	
	targetCellObject:_setObject(buildingObject:getCell(10))
	-- officer 5: mission
	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_5", 0, 19.5, -4.2, -146, 0, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(creature:getObjectID() .. ":tutorial:officer5", spawnedSceneObject:getObjectID())
	--spawnedSceneObject:updateDirection(1, 0, 0, 0)
	writeData(creature:getObjectID() .. ":tutorial:officer5flag", 0)
	writeData(player:getObjectID() .. ":tutorial:off5ready", 0)
	
	--mission terminal
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_mission_newbie.iff", 19.2, -4.2, -134.2, targetCellObject:getObjectID(), 0, 0, 1, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	
	--if state == 0 then
		createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "missionTerminalMove", spawnedPointer)
		createObserver(OBJECTRADIALUSED, "TutorialScreenPlay", "missionTerminalUse", spawnedPointer)
	--end
	
	--** ROOM 11: Travel Terminal **
	-- ROOM11DONE STATE
	--state = creature:hasScreenPlayState(4194304, "tutorial")
	
	targetCellObject:_setObject(buildingObject:getCell(11))
	
	-- officer 6: quartermaster
	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_6", 0, 31.3, -4.2, -164, 11.82, targetCellObject:getObjectID())
	
	--if state == 0 then
		createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "officer6", spawnedPointer) --move observer
	--end
	
	spawnedSceneObject:_setObject(spawnedPointer)
	--spawnedSceneObject:updateDirection(0.994, 0.103, 0, 0)
	spawnedCreatureObject = LuaCreatureObject(spawnedPointer)
	spawnedCreatureObject:setCustomObjectName("The Quartermaster")
	writeData(creature:getObjectID() .. ":tutorial:officer6", spawnedSceneObject:getObjectID())
	writeData(creature:getObjectID() .. ":tutorial:officer6flag", 0)
	
	-- travel terminal
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/beta/beta_terminal_warp.iff", 27.0, -3.5, -168.0, targetCellObject:getObjectID(), 0, 0, 1, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(1, 0, 0, 0)
	
	--if state == 0 then
		createObserver(OBJECTRADIALUSED, "TutorialScreenPlay", "travelTerminalUse", spawnedPointer)
	--end
	
	writeData(creature:getObjectID() .. ":tutorial:travelTerminal", spawnedSceneObject:getObjectID())
	
	terminal = readData(creature:getObjectID() .. ":tutorial:travelTerminal")
	local travelTerminal = getSceneObject(terminal)
	
	--if state == 0 then
		setAuthorizationState(travelTerminal, false)
	--end
	
	return 1
end

function TutorialScreenPlay:start(creatureObject)	
	--printf("Running introduction\n")
	
	
	
	
	local creature = LuaCreatureObject(creatureObject)
	local targetCellObject = LuaSceneObject(creature:getParent())
	local buildingObject = LuaBuildingObject(targetCellObject:getParent())
	
	-- check if the tutorial already started
	id = readData(creature:getObjectID() .. ":tutorial:drum")
	
	--state = creature:hasScreenPlayState(1, "tutorial")
	
	if id ~= 0 then
		return
	end
	
	if creature:getParentID() == 0 then
		return
	end
	
	res = TutorialScreenPlay.spawnObjects(creatureObject, creatureObject)
	
	if res == 0 then
		return
	end
	
	--createObserver(OBJECTREMOVEDFROMZONE, "TutorialScreenPlay", "deleteWorld", creatureObject)
	
	--lock cell door
	updateCellPermission(buildingObject:getCell(9), 0, creatureObject)
		
	creature:sendNewbieTutorialEnableHudElement("all", 0)
	
	creature:sendNewbieTutorialEnableHudElement("buttonbar", 1)
	creature:sendSystemMessage("@newbie_tutorial/system_messages:welcome")
	creature:playMusicMessage("sound/tut_01_welcome.snd")
	writeData(creature:getObjectID() .. ":tutorial:message1",0)
	createEvent(4000, "TutorialScreenPlay", "firstMessage", creatureObject)	
	
end


-- FIRST ROOM

-- Part 1: Welcome / Movement and Camera Controls
function TutorialScreenPlay:firstMessage(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	message1 = readData(creature:getObjectID() .. ":tutorial:message1")
	
	if message1 == 0 then 
		creature:sendSystemMessage("@newbie_tutorial/system_messages:part_1")
		writeData(creature:getObjectID() .. ":tutorial:message1",1)
		createEvent(2000, "TutorialScreenPlay", "firstMessage", creatureObject)
	elseif message1 == 1 then
		creature:sendSystemMessage("@newbie_tutorial/system_messages:movement_keyboard")
		creature:playMusicMessage("sound/tut_02_movement.snd")
		writeData(creature:getObjectID() .. ":tutorial:message1",2)
		createEvent(2000, "TutorialScreenPlay", "firstMessage", creatureObject)
	elseif message1 == 2 then
		creature:sendSystemMessage("@newbie_tutorial/system_messages:movement_mouse")
		writeData(creature:getObjectID() .. ":tutorial:message1",3)
		createEvent(4000, "TutorialScreenPlay", "firstMessage", creatureObject)
	elseif message1 == 3 then
		creature:sendSystemMessage("@newbie_tutorial/system_messages:lookaround")
		writeData(creature:getObjectID() .. ":tutorial:message1",4)
		createEvent(4000, "TutorialScreenPlay", "firstMessage", creatureObject)
	elseif message1 == 4 then	
		creature:sendSystemMessage("@newbie_tutorial/system_messages:mousewheel")
		creature:playMusicMessage("sound/tut_00_camera.snd")
		creature:sendNewbieTutorialRequest("zoomCamera")
		
		writeData(creature:getObjectID() .. ":tutorial:zoom", 0)
		writeData(creature:getObjectID() .. ":tutorial:message1",5)
		createObserver(NEWBIETUTORIALZOOMCAMERA, "TutorialScreenPlay", "zoomEvent", creatureObject)
		--createEvent(25000, "TutorialScreenPlay", "firstMessage", creatureObject)
		createEvent(500, "TutorialScreenPlay", "firstMessage", creatureObject)
		createEvent(30000, "TutorialScreenPlay", "helpZoom", creatureObject)		
	elseif message1 == 5 then
		writeData(creature:getObjectID() .. ":tutorial:zoom", 1)
	end
end


function TutorialScreenPlay:helpZoom(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	state = creature:hasScreenPlayState(1, "tutorial")
	
	if state == 0 then
		creature:sendNewbieTutorialRequest("zoomCamera")
		creature:sendSystemMessage("@newbie_tutorial/system_messages:mousewheel_repeat")
		creature:playMusicMessage("sound/tut_03_scroll_out.snd")
		--let's not be too annoying
		--createEvent(15000, "TutorialScreenPlay", "helpZoom", creatureObject)
	end
end

-- Part 2: The Chat Box
function TutorialScreenPlay:zoomEvent(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	local done = readData(creature:getObjectID() .. ":tutorial:zoom")
	
	if done < 2 then
		if done == 1 then
			writeData(creature:getObjectID() .. ":tutorial:zoom", 2)
		end
		createEvent(1000, "TutorialScreenPlay", "zoomEvent", creatureObject)
	else
		creature:setScreenPlayState(1, "tutorial")
		creature:sendNewbieTutorialEnableHudElement("chatbox", 1)
	
		creature:playMusicMessage("sound/tut_04_chat.snd")
		creature:sendSystemMessage("@newbie_tutorial/system_messages:chatwindow")
	
		writeData(creature:getObjectID() .. ":tutorial:chat", 0)
	
		creature:sendNewbieTutorialRequest("chatbox")
	
		createEvent(16000, "TutorialScreenPlay", "helpChat", creatureObject)
		createObserver(CHAT, "TutorialScreenPlay", "chatEvent", creatureObject)
	
		createEvent(4000, "TutorialScreenPlay", "nextChat", creatureObject)
	end

	return 1
end
	
function TutorialScreenPlay:nextChat(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	finished = readData(creature:getObjectID() .. ":tutorial:chat")
	
	if finished == 0 then 
		creature:sendSystemMessage("@newbie_tutorial/system_messages:chatprompt")
		writeData(creature:getObjectID() .. ":tutorial:chat",1)
		createEvent(4000, "TutorialScreenPlay", "nextChat", creatureObject)
	elseif finished == 1 then
		writeData(creature:getObjectID() .. ":tutorial:chat", 2)
	end	
end

function TutorialScreenPlay:chatEvent(creatureObject, nothing, test)
	local creature = LuaCreatureObject(creatureObject)
	
	message = string.lower(getChatMessage(nothing))
	
	if message == "silence" then
		writeData(creature:getObjectID() .. ":tutorial:sound", 0)
	elseif message == "banditdebug" then
		creature:sendNewbieTutorialEnableHudElement("all", 1)
		writeData(creature:getObjectID() .. ":tutorial:banditdebug", 1)
		local debris = LuaSceneObject(getSceneObject(readData(creature:getObjectID() .. ":tutorial:debrisoid")))
		debris:destroyObjectFromWorld()
		return 1
	end
	
	createEvent(100, "TutorialScreenPlay", "checkChat", creatureObject)
	
	return 1
end
--this can be moved into chatEvent once banditdebug is no longer needed
function TutorialScreenPlay:checkChat(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:chat")
	
	if finished < 2 then
		createEvent(1000, "TutorialScreenPlay", "checkChat", creatureObject)
	else
		creature:setScreenPlayState(2, "tutorial")
		createEvent(1000, "TutorialScreenPlay", "holocron", creatureObject)	
	end
end

function TutorialScreenPlay:helpChat(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	banditdebug = readData(creature:getObjectID() .. ":tutorial:banditdebug")
	
	if state == 0 and banditdebug == 0 then
		creature:sendNewbieTutorialRequest("chatbox")
		creature:sendSystemMessage("@newbie_tutorial/system_messages:repeatchatprompt")
		creature:playMusicMessage("sound/tut_05_remind_chat.snd")
		--let's not be too annoying
		--createEvent(10000, "TutorialScreenPlay", "helpChat", creatureObject)
	end
end

-- Part 3: The Holocron
function TutorialScreenPlay:holocron(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	creature:sendOpenHolocronToPageMessage()
	
	createObserver(NEWBIETUTORIALHOLOCRON, "TutorialScreenPlay", "holocronEvent", creatureObject)
	creature:sendNewbieTutorialRequest("closeHolocron")
	
	writeData(creature:getObjectID() .. ":tutorial:holocron", 0)
	
	playSound = readData(creature:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		creature:playMusicMessage("sound/tut_00_holocron.snd")
	end
	
	creature:sendSystemMessage("@newbie_tutorial/system_messages:holocube")
	
	createEvent(16000, "TutorialScreenPlay", "finishHolocron", creatureObject)
end

function TutorialScreenPlay:finishHolocron(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	writeData(creature:getObjectID() .. ":tutorial:holocron", 1)
end

function TutorialScreenPlay:holocronEvent(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:holocron")
	
	if finished == 0 then
		createEvent(1000, "TutorialScreenPlay", "holocronEvent", creatureObject)
	else
		createEvent(1000, "TutorialScreenPlay", "moveToItemRoom", creatureObject)
	end
	
	return 1
end

-- Room 1 finished: Move on to the next room
function TutorialScreenPlay:moveToItemRoom(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:moveitemroom")
	
	if finished == 0 then
		creature:sendSystemMessage("@newbie_tutorial/system_messages:move_to_item_room")
	
		playSound = readData(creature:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			creature:playMusicMessage("sound/tut_06_excellent.snd")
		end
	
		writeData(creature:getObjectID() .. ":tutorial:moveitemroom", 1)
	
		writeData(creature:getObjectID() .. ":tutorial:excellent", 0)
	
		createEvent(1000, "TutorialScreenPlay", "itemRoomCheck", creatureObject)
		createEvent(4000, "TutorialScreenPlay", "moveToItemRoom", creatureObject)
	elseif finished == 1 then
		writeData(creature:getObjectID() .. ":tutorial:excellent", 1)
	end
end

-- ROOM 2
function TutorialScreenPlay:itemRoomCheck(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	excellent = readData(creature:getObjectID() .. ":tutorial:excellent")
	
	if excellent == 0 then
		createEvent(1000, "TutorialScreenPlay", "itemRoomCheck", creatureObject)
		return
	end
	
	cellNumber = creature:getInCellNumber()
	
	moveitemroom = readData(creature:getObjectID() .. ":tutorial:moveitemroom")
	
	if cellNumber < 2 then
		
		if (moveitemroom % 7 == 0) then
			creature:sendSystemMessage("@newbie_tutorial/system_messages:repeat_item_room_prompt")
			playSound = readData(creature:getObjectID() .. ":tutorial:sound")
			if playSound == 1 then
				creature:playMusicMessage("sound/tut_07_comeon.snd")
			end
		end
		
		writeData(creature:getObjectID() .. ":tutorial:moveitemroom", moveitemroom + 1)
		if moveitemroom < 15 then
			createEvent(1000, "TutorialScreenPlay", "itemRoomCheck", creatureObject)
		else
			creature:sendSystemMessage("@newbie_tutorial/system_messages:part_2")
			createEvent(1000, "TutorialScreenPlay", "room2", creatureObject)
			creature:setScreenPlayState(4, "tutorial")
		end			
	else	
		creature:sendSystemMessage("@newbie_tutorial/system_messages:part_2")
		createEvent(1000, "TutorialScreenPlay", "room2", creatureObject)
		creature:setScreenPlayState(4, "tutorial")
	end
end

function TutorialScreenPlay:officer1(creatureObject, movingCreature)
	--printf("officer1 fired\n")
	
	local officer = LuaSceneObject(creatureObject)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0	
	end
	
	local player = LuaCreatureObject(movingCreature)
	
	distance = officer:getDistanceTo(movingCreature)
	
	--printf("distance: " .. distance)
	
	if officer:getParentID() ~= player:getParentID() then
		return 0
	end
	
	if distance == 0 then
		return 0
	end
	
	if distance > 10 and distance < 15 then
		state = player:hasScreenPlayState(8, "tutorial")
		
		if state ~= 1 then
			player:setScreenPlayState(8, "tutorial")
			
			spatialChat(creatureObject, "@newbie_tutorial/newbie_convo:greeter1_bark1")
		end
		
		return 0
	elseif distance > 7 and distance < 10 then
		state = player:hasScreenPlayState(16, "tutorial")
	
		if state ~= 1 then
			player:setScreenPlayState(16, "tutorial")
			
			spatialChat(creatureObject, "@newbie_tutorial/newbie_convo:greeter1_bark2")
		end
				
		return 0
	elseif distance > 5 and distance < 7 then
		state = player:hasScreenPlayState(32, "tutorial")
	
		if state ~= 1 then
			player:setScreenPlayState(32, "tutorial")
			
			spatialChat(creatureObject, "@newbie_tutorial/newbie_convo:greeter1_bark3")
		end
		
		return 1
	else		
		return 0
	end	
end


function TutorialScreenPlay:room2(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	creature:sendNewbieTutorialRequest("changeLookAtTarget")
	
	writeData(creature:getObjectID() .. ":tutorial:room2", 0)
	writeData(creature:getObjectID() .. ":tutorial:looked", 0)
	
	createEvent(1000, "TutorialScreenPlay", "secondMessage", creatureObject)
	createObserver(PLAYERCHANGEDTARGET, "TutorialScreenPlay", "officerTargetEvent", creatureObject)
end

function TutorialScreenPlay:secondMessage(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	room2 = readData(creature:getObjectID() .. ":tutorial:room2")
	
	if room2 == 0 then
		creature:sendNewbieTutorialEnableHudElement("chatbox", 1)
		playSound = readData(creature:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			creature:playMusicMessage("sound/tut_08_imperialofficer.snd")
		end
	
		creature:sendSystemMessage("@newbie_tutorial/system_messages:tut_08")
		writeData(creature:getObjectID() .. ":tutorial:room2", 1)
		createEvent(7000, "TutorialScreenPlay", "secondMessage", creatureObject)
	elseif room2 == 1 then
		looked = readData(creature:getObjectID() .. ":tutorial:looked")
	
		if looked == 0 then
			officer1ObjectID = readData(creature:getObjectID() .. ":tutorial:officer1")
			spatialChat(getSceneObject(officer1ObjectID), "@newbie_tutorial/newbie_convo:explain_lookat")
		end
	
		writeData(creature:getObjectID() .. ":tutorial:room2", 2)
	end
end

function TutorialScreenPlay:officerTargetEvent(creatureObject, targetCreature)
	local player = LuaCreatureObject(creatureObject)
	local officer = LuaCreatureObject(targetCreature)
		
	officer1ObjectID = readData(player:getObjectID() .. ":tutorial:officer1")

	if officer:getObjectID() == officer1ObjectID then
		
		finished = readData(player:getObjectID() .. ":tutorial:room2")
		
		if finished < 2 then
			writeData(player:getObjectID() .. ":tutorial:looked", 1)
		end
		
		createEvent(1000, "TutorialScreenPlay", "checkTarget", creatureObject)
		
		return 1
	end
	
	return 0	
end

function TutorialScreenPlay:checkTarget(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:room2")
	
	if finished < 2 then
		createEvent(1000, "TutorialScreenPlay", "checkTarget", creatureObject)
	else
		creature:sendSystemMessage("@newbie_tutorial/system_messages:tut_09")
		
		playSound = readData(creature:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			creature:playMusicMessage("sound/tut_09_lookat.snd")
		end
		
		officer1ObjectID = readData(creature:getObjectID() .. ":tutorial:officer1")
		writeData(creature:getObjectID() .. ":tutorial:message3", 0)
		createObserver(OBJECTRADIALOPENED, "TutorialScreenPlay", "radialOpened", getCreatureObject(officer1ObjectID))
		
		createEvent(5000, "TutorialScreenPlay", "thirdMessage", creatureObject)
	end
end
  
function TutorialScreenPlay:thirdMessage(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:message3")
	
	if finished == 0 then
		creature:sendSystemMessage("@newbie_tutorial/system_messages:tut_10")
		playSound = readData(creature:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			creature:playMusicMessage("sound/tut_10_radialmenu.snd")
		end
	
		writeData(creature:getObjectID() .. ":tutorial:message3", 1)
		createEvent(5000, "TutorialScreenPlay", "thirdMessage", creatureObject)
	else
		writeData(creature:getObjectID() .. ":tutorial:message3", 2)
	end
end

--x10 z-1. y-32 cellid2 ow=0.717025 oy=0.697048

function TutorialScreenPlay:radialOpened(sceneObject, creatureObject)
	createEvent(1000, "TutorialScreenPlay", "radialOpenedMessage", creatureObject)
	return 1
end

function TutorialScreenPlay:radialOpenedMessage(creatureObject)
	local creature = LuaCreatureObject(creatureObject)	
	finished = readData(creature:getObjectID() .. ":tutorial:message3")
	
	if finished < 2 then
		createEvent(1000, "TutorialScreenPlay", "radialOpenedMessage", creatureObject)
	elseif finished == 2 then
		creature:sendSystemMessage("@newbie_tutorial/system_messages:tut_11")
	
		playSound = readData(creature:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			creature:playMusicMessage("sound/tut_11_converse.snd")
		end
	
		writeData(creature:getObjectID() .. ":tutorial:message3", 3)
		writeData(creature:getObjectID() .. ":tutorial:converse1", 0)
		writeData(creature:getObjectID() .. ":tutorial:converse2", 0)
		writeData(creature:getObjectID() .. ":tutorial:converse3", 0)
		createEvent(9000, "TutorialScreenPlay", "radialOpenedMessage", creatureObject) 
	
		officer1ObjectID = readData(creature:getObjectID() .. ":tutorial:officer1")	
		createObserver(STARTCONVERSATION, "TutorialScreenPlay", "officer1Conversation", getCreatureObject(officer1ObjectID))
		createObserver(SELECTCONVERSATION, "TutorialScreenPlay", "officer1ConversationSelect", getCreatureObject(officer1ObjectID))
		createObserver(STOPCONVERSATION, "TutorialScreenPlay", "stopOfficer1Conversation", getCreatureObject(officer1ObjectID))
	else
		writeData(creature:getObjectID() .. ":tutorial:converse1", 1)
	end
end

function TutorialScreenPlay:officer1Conversation(creatureObject, playerObject)
	local player = LuaCreatureObject(playerObject)
	
	createEvent(1000, "TutorialScreenPlay", "officer1ConversationMessage", playerObject)	
	return 1
end

function TutorialScreenPlay:officer1ConversationMessage(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:converse1")
	
	if finished == 0 then
		createEvent(1000, "TutorialScreenPlay", "officer1ConversationMessage", creatureObject)
	elseif finished == 1 then
		creature:sendSystemMessage("@newbie_tutorial/system_messages:tut_12")
	
		playSound = readData(creature:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			creature:playMusicMessage("sound/tut_12_conversation.snd")
		end
	
		writeData(creature:getObjectID() .. ":tutorial:converse1", 2)
		createEvent(6000, "TutorialScreenPlay", "officer1ConversationMessage", creatureObject)
		officer1ObjectID = readData(creature:getObjectID() .. ":tutorial:officer1")
	elseif finished == 2 then
		writeData(creature:getObjectID() .. ":tutorial:converse2", 1)
	end
end

function TutorialScreenPlay:officer1ConversationSelect(creatureObject, playerObject)
	local creature = LuaCreatureObject(playerObject)
	
	createEvent(1000, "TutorialScreenPlay", "officer1ConversationSelectMessage", playerObject)
	
	return 1
end

function TutorialScreenPlay:officer1ConversationSelectMessage(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:converse2")
	
	if finished == 0 then
		createEvent(1000, "TutorialScreenPlay", "officer1ConversationSelectMessage", creatureObject)
	elseif finished == 1 then
		creature:sendSystemMessage("@newbie_tutorial/system_messages:tut_13")
	
		playSound = readData(creature:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			creature:playMusicMessage("sound/tut_13_justtype.snd")
		end
		writeData(creature:getObjectID() .. ":tutorial:converse2", 2)
		createEvent(12000, "TutorialScreenPlay", "officer1ConversationSelectMessage", creatureObject)
	elseif finished == 2 then
		writeData(creature:getObjectID() .. ":tutorial:converse3", 1)
	end
end

function TutorialScreenPlay:stopOfficer1Conversation(creatureObject, playerObject)
	local creature = LuaCreatureObject(playerObject)
	
	createEvent(1000, "TutorialScreenPlay", "drumFly", playerObject)
	createEvent(1000, "TutorialScreenPlay", "stopOfficer1ConversationMessage", playerObject)
	
	return 1
end

function TutorialScreenPlay:stopOfficer1ConversationMessage(creatureObject)
	if creatureObject == nil then
		return
	end
	
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:converse3")
	
	if finished == 0 then
		createEvent(1000, "TutorialScreenPlay", "stopOfficer1ConversationMessage", creatureObject)
	elseif finished == 1 then
		createEvent(1000, "TutorialScreenPlay", "stopOfficer1ConversationMessage", creatureObject)
		writeData(creature:getObjectID() .. ":tutorial:drummessage", 0)
		writeData(creature:getObjectID() .. ":tutorial:converse3", 2)
	elseif finished == 2 then
		creature:sendNewbieTutorialRequest("changeLookAtTarget")
		creature:sendNewbieTutorialEnableHudElement("chatbox", 1)
		
		creature:sendSystemMessage("@newbie_tutorial/system_messages:prompt_open_box")
	
		playSound = readData(creature:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			creature:playMusicMessage("sound/tut_14_openbox.snd")
		end
		drumObjectID = readData(creature:getObjectID() .. ":tutorial:drum")
		local drumRawPointer = getSceneObject(drumObjectID)
		createObserver(OPENCONTAINER, "TutorialScreenPlay", "openDrumEvent", drumRawPointer)
		createObserver(OBJECTRADIALOPENED, "TutorialScreenPlay", "drumRadial", drumRawPointer)
		writeData(creature:getObjectID() .. ":tutorial:converse3", 3)
		createEvent(5000, "TutorialScreenPlay", "stopOfficer1ConversationMessageTwo", creatureObject)
	end
end

function TutorialScreenPlay:stopOfficer1ConversationMessageTwo(creatureObject)
	if creatureObject == nil then
		return
	end
	
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:converse3")
	
	if finished == 3 then
		writeData(creature:getObjectID() .. ":tutorial:drummessage", 1)
		writeData(creature:getObjectID() .. ":tutorial:converse3", 4)
		createEvent(10000, "TutorialScreenPlay", "stopOfficer1ConversationMessageTwo", creatureObject)
	
	elseif finished == 4 then
		status = readData(creature:getObjectID() .. ":tutorial:drummessage")
		if status == 3 then
			creature:sendSystemMessage("@newbie_tutorial/system_messages:repeat_open_box")
	
			playSound = readData(creature:getObjectID() .. ":tutorial:sound")
			if playSound == 1 then
				creature:playMusicMessage("sound/tut_16_intheboxyouneed.snd")
			end
			
			createEvent(10000, "TutorialScreenPlay", "stopOfficer1ConversationMessageTwo", creatureObject)
		end
	end
	
end

function TutorialScreenPlay:drumFly(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:drummessage")
	
	if finished < 4 then
		drumObjectID = readData(creature:getObjectID() .. ":tutorial:drum")
		local drumObject = LuaSceneObject(getSceneObject(drumObjectID))
		drumObject:showFlyText("newbie_tutorial/system_messages", "open_me", 0, 255, 0)
		createEvent(2000, "TutorialScreenPlay", "drumFly", creatureObject)
	end
end

function TutorialScreenPlay:drumRadial(sceneObject, creatureObject)
	createEvent(1000, "TutorialScreenPlay", "drumRadialMessage", creatureObject)
	return 1
end

function TutorialScreenPlay:drumRadialMessage(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:drummessage")
	
	if finished == 0 then
		createEvent(1000, "TutorialScreenPlay", "drumRadialMessage", creatureObject)
	elseif finished == 1 then
		playSound = readData(creature:getObjectID() .. ":tutorial:sound")
	
		if creature:getTargetID() == drumObjectID then
			creature:sendSystemMessage("@newbie_tutorial/system_messages:prompt_choose_open")
		
			if playSound == 1 then
				creature:playMusicMessage("sound/tut_15_opencontainer.snd")
			end

		end
		writeData(creature:getObjectID() .. ":tutorial:drummessage", 2)
		createEvent(5000, "TutorialScreenPlay", "drumRadialMessage", creatureObject)
	elseif finished == 2 then
		writeData(creature:getObjectID() .. ":tutorial:drummessage", 3)
	end
end

function TutorialScreenPlay:openDrumEvent(drumObject, creatureObject)	
	createEvent(1000, "TutorialScreenPlay", "openDrumEventMessage", creatureObject)
	createObserver(CLOSECONTAINER, "TutorialScreenPlay", "closeDrumEvent", drumObject)	
	return 1
end

function TutorialScreenPlay:openDrumEventMessage(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:drummessage")
	
	state = creature:hasScreenPlayState(128, "tutorial")
	
	if state ~= 0 then
		writeData(creature:getObjectID() .. ":tutorial:drummessage", 5)
		return
	end
	
	if finished < 3 then
		createEvent(1000, "TutorialScreenPlay", "openDrumEventMessage", creatureObject)
	elseif finished == 3 then	
		creature:sendSystemMessage("@newbie_tutorial/system_messages:prompt_take_items")
	
		playSound = readData(creature:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			creature:playMusicMessage("sound/tut_16_a_youcantake.snd")
		end
		
		writeData(creature:getObjectID() .. ":tutorial:drummessage", 4)
		createEvent(13000, "TutorialScreenPlay", "openDrumEventMessage", creatureObject)
	elseif finished == 4 then
		writeData(creature:getObjectID() .. ":tutorial:drummessage", 5)
	end	
end

function TutorialScreenPlay:closeDrumEvent(drumObject, creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	creature:setScreenPlayState(128, "tutorial")
	createEvent(1000, "TutorialScreenPlay", "closeDrumEventMessage", creatureObject)
	
	return 1
end

function TutorialScreenPlay:closeDrumEventMessage(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:drummessage")
	
	if finished < 5 then
		createEvent(1000, "TutorialScreenPlay", "closeDrumEventMessage", creatureObject)
	elseif finished == 5 then
		creature:sendSystemMessage("@newbie_tutorial/system_messages:pickup_complete")
	
		creature:sendNewbieTutorialRequest("openInventory")
		createObserver(NEWBIEOPENINVENTORY, "TutorialScreenPlay", "openInventoryObserver", creatureObject)
	
		creature:sendNewbieTutorialRequest("closeInventory")
		createObserver(NEWBIECLOSEINVENTORY, "TutorialScreenPlay", "closeInventoryObserver", creatureObject)
	
		playSound = readData(creature:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			creature:playMusicMessage("sound/tut_18_inventory.snd")
		end
		writeData(creature:getObjectID() .. ":tutorial:drummessage", 6)
		createEvent(3000, "TutorialScreenPlay", "closeDrumEventMessage", creatureObject)
	elseif finished == 6 then
		createObserver(GETATTRIBUTESBATCHCOMMAND, "TutorialScreenPlay", "foodTargetEvent", creatureObject)
		creature:sendSystemMessage("@newbie_tutorial/system_messages:explain_freemouse")
	
		playSound = readData(creature:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			creature:playMusicMessage("sound/tut_19_inventory.snd")
		end
		
		writeData(creature:getObjectID() .. ":tutorial:drummessage", 7)
		createEvent(4000, "TutorialScreenPlay", "closeDrumEventMessage", creatureObject)
	elseif finished == 7 then
		creature:sendSystemMessage("@newbie_tutorial/system_messages:explain_freemouse_toggle")
		writeData(creature:getObjectID() .. ":tutorial:drummessage", 8)
		createEvent(4000, "TutorialScreenPlay", "closeDrumEventMessage", creatureObject)
	elseif finished == 8 then
		creature:sendSystemMessage("@newbie_tutorial/system_messages:explain_inventory")
		writeData(creature:getObjectID() .. ":tutorial:drummessage", 9)
		createEvent(4000, "TutorialScreenPlay", "closeDrumEventMessage", creatureObject)
	elseif finished == 9 then
		writeData(creature:getObjectID() .. ":tutorial:drummessage", 10)
	end
end

function TutorialScreenPlay:openInventoryObserver(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:drummessage")
	
	if finished < 10 then
		createEvent(1000, "TutorialScreenPlay", "openInventoryObserver", creatureObject)
	elseif finished == 10 then
		creature:sendSystemMessage("@newbie_tutorial/system_messages:prompt_find_food")
	
		playSound = readData(creature:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			creature:playMusicMessage("sound/tut_20_selectfooditem.snd")
		end
	
		writeData(creature:getObjectID() .. ":tutorial:drummessage", 11)
		createEvent(5000, "TutorialScreenPlay", "openInventoryObserver", creatureObject)
	elseif finished == 11 then
		writeData(creature:getObjectID() .. ":tutorial:drummessage", 12)
	end
	
	return 1

end

function TutorialScreenPlay:foodTargetEvent(creatureObject, targetObject, batch)
	local player = LuaCreatureObject(creatureObject)
	local food = LuaSceneObject(targetObject)

	if (food:getGameObjectType() ~= 8202) or (batch > 0) then -- food
		return 0
	end
		
	createEvent(1000, "TutorialScreenPlay", "foodTargetMessage", creatureObject)
	
	return 1	
end

function TutorialScreenPlay:foodTargetMessage(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	finished = readData(player:getObjectID() .. ":tutorial:drummessage")
	
	if finished < 12 then
		createEvent(1000, "TutorialScreenPlay", "foodTargetMessage", creatureObject)
	elseif finished == 12 then
		player:sendSystemMessage("@newbie_tutorial/system_messages:prompt_use_item")
		
		playSound = readData(player:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			player:playMusicMessage("sound/tut_21_usefood.snd")
		end
		
		writeData(player:getObjectID() .. ":tutorial:drummessage", 13)
		createEvent(8500, "TutorialScreenPlay", "foodTargetMessage", creatureObject)
	elseif finished == 13 then
		writeData(player:getObjectID() .. ":tutorial:drummessage", 14)
	end
end

function TutorialScreenPlay:foodUsed(foodObject, creatureObject, selectedID)
	if selectedID ~= 20 then
		return 0
	end
	
	local player = LuaCreatureObject(creatureObject)
	
	banditdebug = readData(player:getObjectID() .. ":tutorial:banditdebug")
	
	if banditdebug == 1	then
		return 1
	end
	
	createEvent(100, "TutorialScreenPlay", "foodUsedMessage", creatureObject)
	
	return 1
end

function TutorialScreenPlay:foodUsedMessage(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	finished = readData(player:getObjectID() .. ":tutorial:drummessage")
	
	if finished < 14 then
		createEvent(1000, "TutorialScreenPlay", "foodUsedMessage", creatureObject)
	elseif finished == 14 then
		player:sendSystemMessage("@newbie_tutorial/system_messages:explain_item_used")
	
		playSound = readData(player:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			player:playMusicMessage("sound/tut_22_attributes.snd")
		end
		
		writeData(player:getObjectID() .. ":tutorial:drummessage", 15)
		createEvent(9000, "TutorialScreenPlay", "foodUsedMessage", creatureObject)
	elseif finished == 15 then
		writeData(player:getObjectID() .. ":tutorial:drummessage", 16)
		--player:sendSystemMessage("@newbie_tutorial/system_messages:close_inventory")
	end
end

function TutorialScreenPlay:closeInventoryObserver(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	finished = readData(player:getObjectID() .. ":tutorial:drummessage")
	--printf(finished .. "\n")
	if finished < 16 then
		createEvent(1000, "TutorialScreenPlay", "closeInventoryObserver", creatureObject)
	elseif finished == 16 then
		player:setScreenPlayState(256, "tutorial")
		writeData(player:getObjectID() .. ":tutorial:toolbarmessage", 0)
		createEvent(1000, "TutorialScreenPlay", "activateToolbar", creatureObject)
	end
	return 1
end

function TutorialScreenPlay:activateToolbar(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	message = readData(player:getObjectID() .. ":tutorial:toolbarmessage")
	
	if message == 0 then
		player:sendNewbieTutorialEnableHudElement("toolbar", 1)
		player:sendSystemMessage("@newbie_tutorial/system_messages:show_toolbar")
		
		playSound = readData(player:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			player:playMusicMessage("sound/tut_23_toolbar.snd")
		end
		
		writeData(player:getObjectID() .. ":tutorial:toolbarmessage", 1)
		createEvent(5000, "TutorialScreenPlay", "activateToolbar", creatureObject)
	elseif message == 1 then
		player:sendSystemMessage("@newbie_tutorial/system_messages:tut_00_toolbardrag")
	
		playSound = readData(player:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			player:playMusicMessage("sound/tut_00_toolbardrag.snd")
		end
		
		writeData(player:getObjectID() .. ":tutorial:toolbarmessage", 2)
		createEvent(12000, "TutorialScreenPlay", "activateToolbar", creatureObject)
	elseif message == 2 then
		player:sendSystemMessage("@newbie_tutorial/system_messages:use_toolbar")
		playSound = readData(player:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			player:playMusicMessage("sound/tut_24_toolbarslots.snd")
		end
		
		writeData(player:getObjectID() .. ":tutorial:toolbarmessage", 3)
		createEvent(11000, "TutorialScreenPlay", "activateToolbar", creatureObject)
	elseif message == 3 then
		player:sendNewbieTutorialEnableHudElement("toolbar", 1)
		player:sendNewbieTutorialEnableHudElement("chatbox", 1)
		writeData(player:getObjectID() .. ":tutorial:toolbarmessage", 4)
		player:setScreenPlayState(256, "tutorial")
		createEvent(1000, "TutorialScreenPlay", "checkCommerceRoom", creatureObject)
	end
end

function TutorialScreenPlay:checkCommerceRoom(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	
	movecommerceroom = readData(player:getObjectID() .. ":tutorial:movecommerceroom")
	
	if player:getInCellNumber() ~= 3 then
		if (movecommerceroom % 7 == 0) then
			player:sendSystemMessage("@newbie_tutorial/system_messages:visit_commerce_room")
			if playSound == 1 then
				player:playMusicMessage("sound/tut_27_proceed.snd")
			end
			player:setScreenPlayState(512, "tutorial")
		end
		
		writeData(player:getObjectID() .. ":tutorial:movecommerceroom", movecommerceroom + 1)
		createEvent(1000, "TutorialScreenPlay", "checkCommerceRoom", creatureObject)
		return
	end
	
	writeData(player:getObjectID() .. ":tutorial:room3", 0)
	createEvent(1000, "TutorialScreenPlay", "room3", creatureObject)
end

function TutorialScreenPlay:room3(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	finished = readData(player:getObjectID() .. ":tutorial:room3")
	
	if finished == 0 then
		player:sendSystemMessage("@newbie_tutorial/system_messages:part_3")
		writeData(player:getObjectID() .. ":tutorial:room3", 1)
		createEvent(1000, "TutorialScreenPlay", "room3", creatureObject)
	elseif finished == 1 then
		player:sendSystemMessage("@newbie_tutorial/system_messages:tut_28")
	
		if playSound == 1 then
			player:playMusicMessage("sound/tut_28_converse.snd")
		end
	
		--officer speaks
		local officer2 = getSceneObject(readData(player:getObjectID() .. ":tutorial:officer2"))
	
		spatialChat(officer2, "@newbie_tutorial/newbie_convo:banker_greeting")
	end
end

function TutorialScreenPlay:bankerStartConversation(creatureObject, playerObject)
	local player = LuaCreatureObject(playerObject)
	
	createEvent(1000, "TutorialScreenPlay", "bankMoveCheck", playerObject)
	createEvent(1000, "TutorialScreenPlay", "bazaarMoveCheck", playerObject)
	createEvent(1000, "TutorialScreenPlay", "commerceDoneCheck", playerObject)
	
	return 1
end

function TutorialScreenPlay:bankMoveCheck(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	local bankPointer = readData(player:getObjectID() .. ":tutorial:bank")
	local bank = LuaSceneObject(getSceneObject(bankPointer))
	
	distance = bank:getDistanceTo(playerObject)

	bazaarflag = readData(player:getObjectID() .. ":tutorial:bazaarflag")
	
	if distance == 0 or distance > 6 or bazaarflag == 2 then
	
		-- only show every other second
		showFly = readData(player:getObjectID() .. ":tutorial:bankfly")
		
		if (showFly == 0) then
			bank:showFlyText("newbie_tutorial/system_messages", "bank_flytext", 0, 255, 0)
			writeData(player:getObjectID() .. ":tutorial:bankfly", 1)
		else
			writeData(player:getObjectID() .. ":tutorial:bankfly", 0)
		end
	
		createEvent(1000, "TutorialScreenPlay", "bankMoveCheck", playerObject)
	else
		writeData(player:getObjectID() .. ":tutorial:bankflag", 2)
		createEvent(100, "TutorialScreenPlay", "explainBank_1", playerObject)
	end
end

function TutorialScreenPlay:bazaarMoveCheck(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	local bazaarPointer = readData(player:getObjectID() .. ":tutorial:bazaar")
	local bazaar = LuaSceneObject(getSceneObject(bazaarPointer))
	
	distance = bazaar:getDistanceTo(playerObject)

	bankflag = readData(player:getObjectID() .. ":tutorial:bankflag")
	
	if distance == 0 or distance > 7 or bankflag == 2 then
		
		-- only show every other second
		showFly = readData(player:getObjectID() .. ":tutorial:bazaarfly")
		
		if (showFly == 0) then
			bazaar:showFlyText("newbie_tutorial/system_messages", "bazaar_flytext", 0, 255, 0)
			writeData(player:getObjectID() .. ":tutorial:bazaarfly", 1)
		else
			writeData(player:getObjectID() .. ":tutorial:bazaarfly", 0)
		end
		
		createEvent(1000, "TutorialScreenPlay", "bazaarMoveCheck", playerObject)
	else
		writeData(player:getObjectID() .. ":tutorial:bazaarflag", 2)
		createEvent(100, "TutorialScreenPlay", "explainBazaar_1", playerObject)
	end
end

function TutorialScreenPlay:explainBank_1(playerObject)
	local player = LuaCreatureObject(playerObject)

	player:sendSystemMessage("@newbie_tutorial/system_messages:bank_info_1")
	
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_32_bank.snd")
	end
	
	createEvent(6000, "TutorialScreenPlay", "explainBank_2", playerObject)
end

function TutorialScreenPlay:explainBank_2(playerObject)
	local player = LuaCreatureObject(playerObject)

	player:sendSystemMessage("@newbie_tutorial/system_messages:bank_info_2")
	createEvent(7500, "TutorialScreenPlay", "explainBank_3", playerObject)
end

function TutorialScreenPlay:explainBank_3(playerObject)
	local player = LuaCreatureObject(playerObject)

	player:sendSystemMessage("@newbie_tutorial/system_messages:bank_info_3")
	createEvent(6000, "TutorialScreenPlay", "explainBank_4", playerObject)
end

function TutorialScreenPlay:explainBank_4(playerObject)
	local player = LuaCreatureObject(playerObject)

	player:sendSystemMessage("@newbie_tutorial/system_messages:bank_info_4")
	createEvent(5000, "TutorialScreenPlay", "explainBank_5", playerObject)
end

function TutorialScreenPlay:explainBank_5(playerObject)
	local player = LuaCreatureObject(playerObject)

	player:sendSystemMessage("@newbie_tutorial/system_messages:bank_info_5")
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_33_cash.snd")
	end
	createEvent(8000, "TutorialScreenPlay", "explainBank_finished", playerObject)
end

function TutorialScreenPlay:explainBank_finished(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	writeData(player:getObjectID() .. ":tutorial:bankflag", 1)
end

function TutorialScreenPlay:explainBazaar_1(playerObject)
	local player = LuaCreatureObject(playerObject)

	player:sendSystemMessage("@newbie_tutorial/system_messages:bazaar_info_1")
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_29_itemdispenser.snd")
	end
	createEvent(5000, "TutorialScreenPlay", "explainBazaar_2", playerObject)
end

function TutorialScreenPlay:explainBazaar_2(playerObject)
	local player = LuaCreatureObject(playerObject)

	player:sendSystemMessage("@newbie_tutorial/system_messages:bazaar_info_2")
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_00_bazaar_tease.snd")
	end
	createEvent(7000, "TutorialScreenPlay", "explainBazaar_3", playerObject)
end

function TutorialScreenPlay:explainBazaar_3(playerObject)
	local player = LuaCreatureObject(playerObject)

	player:sendSystemMessage("@newbie_tutorial/system_messages:bazaar_info_3")
	createEvent(7000, "TutorialScreenPlay", "explainBazaar_finished", playerObject)
end

function TutorialScreenPlay:explainBazaar_finished(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	writeData(player:getObjectID() .. ":tutorial:bazaarflag", 1)
end

function TutorialScreenPlay:commerceDoneCheck(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	local bankCheck = readData(player:getObjectID() .. ":tutorial:bankflag")
	local bazaarCheck = readData(player:getObjectID() .. ":tutorial:bazaarflag")
	
	if bankCheck == 1 and bazaarCheck == 1 then
		createEvent(2000, "TutorialScreenPlay", "moveToCloning", playerObject)
	else
		createEvent(1000, "TutorialScreenPlay", "commerceDoneCheck", playerObject)
	end		 
end

function TutorialScreenPlay:moveToCloning(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_36")
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_36_movedownhall.snd")
	end
	player:setScreenPlayState(1024, "tutorial")
end

function TutorialScreenPlay:commoner_spatial(creatureObject, movingCreature)
	local commoner = LuaSceneObject(creatureObject)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false or commoner:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)
	local commonerCreature = LuaCreatureObject(creatureObject)
	
	distance = commoner:getDistanceTo(movingCreature)
	
	if distance == 0 then
		return 0
	end
	
	cdistance = readData(commoner:getObjectID() .. ":tutorial:cdistance")
	cid = readData(commoner:getObjectID() .. ":tutorial:cid")
	
	if (cdistance == 0) then
		cdistance = 8
	end
	
	if player:getPositionZ() > -5 then
		return 0
	end
	
	if distance < cdistance then
		--commoner speaks
		if cid == 1 then
			spatialChat(creatureObject, "@newbie_tutorial/newbie_convo:ins_user_bark_1")
		elseif cid == 2 then
			spatialChat(creatureObject, "@newbie_tutorial/newbie_convo:ins_user_bark_2")
		else -- only 3 for now
			spatialChat(creatureObject, "@newbie_tutorial/newbie_convo:ins_user_bark_3")
		end
		
		return 1
	else
		return 0
	end
end

function TutorialScreenPlay:part4StartObserver(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	if player:getInCellNumber() == 5 then
		state = player:hasScreenPlayState(16384, "tutorial")
		
		if state == 0 then
			player:sendSystemMessage("@newbie_tutorial/system_messages:part_4")
			player:setScreenPlayState(16384, "tutorial")
			
			protocolDroidOid = readData(player:getObjectID() .. ":tutorial:protocol")
			local droidPointer = getSceneObject(protocolDroidOid)	
			
			spatialChat(droidPointer, "@newbie_tutorial/newbie_convo:clone_greeting")
			
			--player:sendNewbieTutorialEnableHudElement("all", 1)
			
			return 1
		end
	end
	
	return 0
end

function TutorialScreenPlay:cloningDroidStopConversation(creatureObject, playerObject)
	local player = LuaCreatureObject(playerObject)
	
	--cloneTerminalObjectId = readData(player:getObjectID() .. ":tutorial:clone")
	--local clonePointer = getSceneObject(cloneTerminalObjectId)
	--local cloneTerminal = LuaSceneObject(clonePointer)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_37")
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_37_cloning.snd")
	end
	
	writeData(player:getObjectID() .. ":tutorial:clonetalk", 0)
	
	createEvent(9000, "TutorialScreenPlay", "cloneHereDone", playerObject)
	
	createEvent(1000, "TutorialScreenPlay", "cloneHereEvent", playerObject)
			
	return 1
end

function TutorialScreenPlay:cloneHereDone(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	writeData(player:getObjectID() .. ":tutorial:clonetalk", 1)
end

function TutorialScreenPlay:cloneHereEvent(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	cloneTerminalObjectId = readData(player:getObjectID() .. ":tutorial:clone")
	clonePointer = getSceneObject(cloneTerminalObjectId)
	
	local cloneTerminal = LuaSceneObject(clonePointer)
	
	cloneTerminal:showFlyText("newbie_tutorial/system_messages", "clone_here", 0, 255, 0)
	
	state = player:hasScreenPlayState(32768, "tutorial")
	
	if state == 0 then
		createEvent(2000, "TutorialScreenPlay", "cloneHereEvent", creatureObject)
	end
end

function TutorialScreenPlay:cloningUseObserver(cloningTerminal, playerObject, selectedID)
	if selectedID ~= 20 then
		return 0
	end
	
	local player = LuaCreatureObject(playerObject)
	
	player:setScreenPlayState(32768, "tutorial")
	
	--player:sendSystemMessage("@newbie_tutorial/system_messages:declare_cloned")
	
	createEvent(4000, "TutorialScreenPlay", "explainInsurance", playerObject)
	
	return 1
end

function TutorialScreenPlay:explainInsurance(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	cloneTalk = readData(player:getObjectID() .. ":tutorial:clonetalk")
	
	if cloneTalk == 1 then
		player:sendSystemMessage("@newbie_tutorial/system_messages:tut_38")
		playSound = readData(player:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			player:playMusicMessage("sound/tut_38_insurance.snd")
		end
	
		createEvent(3000, "TutorialScreenPlay", "insuranceCheckEvent", creatureObject)
	else
		createEvent(1000, "TutorialScreenPlay", "explainInsurance", creatureObject)
	end
end

function TutorialScreenPlay:insuranceCheckEvent(creatureObject)
	local player = LuaCreatureObject(creatureObject)

	insuranceOid = readData(player:getObjectID() .. ":tutorial:insurance")
	insurancePointer = getSceneObject(insuranceOid)
	insuranceObject = LuaSceneObject(insurancePointer)
	
	insuranceObject:showFlyText("newbie_tutorial/system_messages", "insure_here", 0, 255, 0)
	
	
	state = player:hasScreenPlayState(65536, "tutorial")
	
	if state == 0 then
		createEvent(2000, "TutorialScreenPlay", "insuranceCheckEvent", creatureObject)
	end

end

function TutorialScreenPlay:insuranceUseObserver(insuranceTerminal, playerObject, selectedID)
	if selectedID ~= 20 then
		return 0
	end
	
	local player = LuaCreatureObject(playerObject)
	
	player:setScreenPlayState(65536, "tutorial")
	--player:sendSystemMessage("@newbie_tutorial/system_messages:declare_insured")	
	
	createEvent(4000, "TutorialScreenPlay", "insuranceMoveForward", playerObject)
	
	return 1
end

function TutorialScreenPlay:insuranceMoveForward(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	cloneTalk = readData(player:getObjectID() .. ":tutorial:clonetalk")
	
	cellNumber = player:getInCellNumber()
	
	if cellNumber < 6 then
		if cloneTalk == 0 then
			createEvent(1000, "TutorialScreenPlay", "insuranceMoveForward", creatureObject)
		else
			player:sendSystemMessage("@newbie_tutorial/system_messages:visit_commerce_room")
			playSound = readData(player:getObjectID() .. ":tutorial:sound")
			if playSound == 1 then
				player:playMusicMessage("sound/tut_27_proceed.snd")
			end
		end
	end
end

function TutorialScreenPlay:nervous1MoveObserver(creatureObject, movingCreature)
	local player = LuaCreatureObject(movingCreature)
	local guy = LuaSceneObject(creatureObject)
	
	distance = guy:getDistanceTo(movingCreature)
	
	if distance == 0 then
		return 0
	end
	
	if distance < 6 then
		spatialChat(creatureObject, "@newbie_tutorial/newbie_convo:nervous_guy1")
		writeData(player:getObjectID() .. ":tutorial:nervous1", 0)
		createEvent(1500, "TutorialScreenPlay", "nervous1", movingCreature)
		
		return 1
	end
	
	return 0
end

function TutorialScreenPlay:nervous1(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	state = readData(player:getObjectID() .. ":tutorial:nervous1")
	npc = readData(player:getObjectID() .. ":tutorial:nervous1npc")
	
	local nervousguy = getSceneObject(npc)
	
	if state == 0 then
		spatialChat(nervousguy, "@newbie_tutorial/newbie_convo:nervous_guy2")
		writeData(player:getObjectID() .. ":tutorial:nervous1", 1)
		createEvent(1500, "TutorialScreenPlay", "nervous1", creatureObject)
	elseif state == 1 then
		spatialChat(nervousguy, "@newbie_tutorial/newbie_convo:nervous_guy3")
		writeData(player:getObjectID() .. ":tutorial:nervous1", 2)
		createEvent(1500, "TutorialScreenPlay", "nervous1", creatureObject)
	elseif state == 2 then
		spatialChat(nervousguy, "@newbie_tutorial/newbie_convo:nervous_guy4")
		writeData(player:getObjectID() .. ":tutorial:nervous1", 3)
		createEvent(1500, "TutorialScreenPlay", "nervous1", creatureObject)
	else	
		spatialChat(nervousguy, "@newbie_tutorial/newbie_convo:nervous_guy5")
	end						
end

function TutorialScreenPlay:panic1MoveObserver(creatureObject, movingCreature)
	local officer = LuaSceneObject(creatureObject)
	
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0	
	end
	
	local player = LuaCreatureObject(movingCreature)
	
	distance = officer:getDistanceTo(movingCreature)
	
	if distance == 0 then
		return 0
	end
	
	if distance < 9 then
		panic1part = readData(player:getObjectID() .. ":tutorial:panic1part")
		
		if panic1part == 0 then
			player:sendSystemMessage("@newbie_tutorial/system_messages:part_5")
			writeData(player:getObjectID() .. ":tutorial:panic1part", 1 )
			return 0
		else 
			spatialMoodChat(creatureObject, "@newbie_tutorial/newbie_convo:shout_panic1", 80)
		
			player:sendSystemMessage("@newbie_tutorial/system_messages:radar")
			playSound = readData(player:getObjectID() .. ":tutorial:sound")
			if playSound == 1 then
				player:playMusicMessage("sound/tut_41_advancewarning.snd")
			end
			player:sendNewbieTutorialEnableHudElement("radar", 1)
			writeData(player:getObjectID() .. ":tutorial:radartalk", 0)
			createEvent(1000, "TutorialScreenPlay", "continuePanic1", creatureObject)
			
			return 1
		end
	else
		return 0
	end
end

function TutorialScreenPlay:continuePanic1(creatureObject)
	spatialMoodChat(creatureObject, "@newbie_tutorial/newbie_convo:shout_panic2", 80)
	
	createEvent(1000, "TutorialScreenPlay", "continuePanic2", creatureObject)
end

function TutorialScreenPlay:continuePanic2(creatureObject)
	spatialMoodChat(creatureObject, "@newbie_tutorial/newbie_convo:shout_panic3", 80)
	createEvent(2000, "TutorialScreenPlay", "continuePanic3", creatureObject)
end

function TutorialScreenPlay:continuePanic3(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	writeData(player:getObjectID() .. ":tutorial:radartalk", 1)
end

function TutorialScreenPlay:part5StartObserver(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	if player:getInCellNumber() == 6 then
		state = player:hasScreenPlayState(131072, "tutorial")
		radartalk = readData(player:getObjectID() .. ":tutorial:radartalk")
		
		if radartalk == 0 then
			return 0
		end
		
		if state == 0 then
			player:setScreenPlayState(131072, "tutorial")
			createEvent(1000, "TutorialScreenPlay", "explainRadar", creatureObject)
			
			--createObserver(POSITIONCHANGED, "TutorialScreenPlay", "officer3Start", creatureObject) --move observer
			
			return 1
		end
	end
	
	return 0
end

function TutorialScreenPlay:explainRadar(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendNewbieTutorialEnableHudElement("radar", 1)
			
	player:sendSystemMessage("@newbie_tutorial/system_messages:radar_more")
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_42_map.snd")
	end
				
	--player:sendNewbieTutorialEnableHudElement("all", 1)
	
	createEvent(15000, "TutorialScreenPlay", "explainOverlayMap", creatureObject)
end

function TutorialScreenPlay:explainOverlayMap(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_43")
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_43_zoommap.snd")
	end
	writeData(player:getObjectID() .. ":tutorial:radartalk", 2)
end

function TutorialScreenPlay:converseWithOfficer3Observer(creatureObject, movingCreature)
	local officer = LuaSceneObject(creatureObject)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0	
	end
	
	local player = LuaCreatureObject(movingCreature)
	
	distance = officer:getDistanceTo(movingCreature)
	
	if distance == 0 then
		return 0
	end
	
	if distance < 8 then
		createEvent(100, "TutorialScreenPlay", "converseWithOfficer3", movingCreature)
		
		return 1
	else
		return 0
	end
end

function TutorialScreenPlay:converseWithOfficer3(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	radartalk = readData(player:getObjectID() .. ":tutorial:radartalk")
	
	if radartalk < 2 then
		createEvent(1000, "TutorialScreenPlay", "converseWithOfficer3", creatureObject)
	else
		player:sendSystemMessage("@newbie_tutorial/system_messages:tut_40")
	
		playSound = readData(player:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			player:playMusicMessage("sound/tut_40_converse.snd")
		end
	end
end

function TutorialScreenPlay:officer3StartConversation(creatureObject, playerObject)
	local player = LuaCreatureObject(playerObject)
	local officer = LuaCreatureObject(creatureObject)
	
	officer:doAnimation("embarrassed")

	return 1
end

function TutorialScreenPlay:officer3StopConversation(creatureObject, playerObject)
	local player = LuaCreatureObject(playerObject)
	local officer = LuaCreatureObject(creatureObject)
	
		
	
	return 1
end

function TutorialScreenPlay:officer3SelectConversation(creatureObject, playerObject, selectedOption)
	return 1
end

function TutorialScreenPlay:nearDebrisObserver(debrisObject, movingCreature)
	local debris = LuaSceneObject(debrisObject)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0	
	end
	
	local player = LuaCreatureObject(movingCreature)
	
	distance = debris:getDistanceTo(movingCreature)
	
	if distance == 0 then
		return 0
	end
	
	if distance < 15 then
		player:sendSystemMessage("@newbie_tutorial/system_messages:tut_45")
		
		playSound = readData(player:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			player:playMusicMessage("sound/tut_45_proceed.snd")
		end
		
		return 1
	else
		return 0
	end
end

function TutorialScreenPlay:debrisDestroyedObserver(debrisObject, playerObject)
	local player = LuaCreatureObject(playerObject)
	local debris = LuaSceneObject(debrisObject)

	banditdebug = readData(player:getObjectID() .. ":tutorial:banditdebug")
	
	if banditdebug == 1 then
		return 1
	end
	
	player:sendNewbieTutorialEnableHudElement("all", 1)
	
	debris:destroyObjectFromWorld()
	
	player:clearCombatState(1)
	player:setScreenPlayState(262144, "tutorial")
	player:sendSystemMessage("@newbie_tutorial/system_messages:part_6")
	
	createEvent(1000, "TutorialScreenPlay", "startExplainCombat", playerObject)
	
	return 1
end

function TutorialScreenPlay:startExplainCombat(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:explain_combat_1")
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_47_defaultattack.snd")
	end
	
	createEvent(5000, "TutorialScreenPlay", "explainCombat", playerObject)
	
	return 1
end

function TutorialScreenPlay:explainCombat(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	player:sendSystemMessage("@newbie_tutorial/system_messages:explain_combat_2")
	
	createEvent(7000, "TutorialScreenPlay", "explainCombatNext", creatureObject)
end

function TutorialScreenPlay:explainCombatNext(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_44_attacking")
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_44_attacking.snd")
	end
end

function TutorialScreenPlay:banditMoveObserver(creatureObject, movingCreature)
	local bandit = LuaSceneObject(creatureObject)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)
	
	banditdead = readData(player:getObjectID() .. ":tutorial:banditdead")
	
	if banditdead == 1 then
		return 1
	end
	
	if bandit:isCreatureObject() == false then
		return 0
	end
	
	local banditCreature = LuaCreatureObject(creatureObject)
	
	distance = bandit:getDistanceTo(movingCreature)
	
	if distance == 0 or distance > 30 then
		return 0
	end
	
	banditflag = readData(player:getObjectID() .. ":tutorial:banditflag")
	
	if distance < 15 then
		
		if (banditflag >= 2) then
			--bandit speaks
			spatialChat(creatureObject, "@newbie_tutorial/newbie_convo:pirate_attack")
		
			--attack
			banditCreature:engageCombat(movingCreature)
			
			return 1
		end
		
		return 0
	elseif distance < 20 then
		if (banditflag < 2) then
			--bandit speaks
			spatialChat(creatureObject, "@newbie_tutorial/newbie_convo:pirate_taunt2")
			writeData(player:getObjectID() .. ":tutorial:banditflag", 2)
		end
		
		return 0
	elseif distance < 25 then
		if (banditflag < 1) then
	
			--bandit speaks
			spatialChat(creatureObject, "@newbie_tutorial/newbie_convo:pirate_taunt1")
		
			banditCreature:doAnimation("slit_throat")
			writeData(player:getObjectID() .. ":tutorial:banditflag", 1)
		end
		
		return 0 
	else
		return 0
	end
end

function TutorialScreenPlay:banditDamageObserver(banditObject, playerObject, damage)
	local player = LuaCreatureObject(playerObject)
	local bandit = LuaCreatureObject(banditObject)
	
	health = bandit:getHAM(0)
	action = bandit:getHAM(3)
	mind = bandit:getHAM(6)
	
	maxHealth = bandit:getMaxHAM(0)
	maxAction = bandit:getMaxHAM(3)
	maxMind = bandit:getMaxHAM(6)
	
	--printf("Health: " .. health .. " Action: " .. action .. " Mind: " .. mind .. "\n")
	
	if ((health <= (maxHealth * 0.6)) or (action <= (maxAction * 0.6)) or (mind <= (maxMind * 0.6))) then
		banditdead = readData(player:getObjectID() .. ":tutorial:banditdead")
		
		if banditdead == 1 then
			return 1
		end
		
		writeData(player:getObjectID() .. ":tutorial:banditdead", 1)
		
		spatialChat(banditObject, "@newbie_tutorial/newbie_convo:pirate_taunt3")
		
		createEvent(2000, "TutorialScreenPlay", "tauntBandit", banditObject)
		
		createEvent(4000, "TutorialScreenPlay", "killBandit", banditObject) 
		createEvent(6000, "TutorialScreenPlay", "lootBanditEvent", playerObject)
				
		return 1		
	end
	
	return 0
end

function TutorialScreenPlay:banditDestroyObserver(banditObject, playerObject)
	local player = LuaCreatureObject(playerObject)
	local bandit = LuaCreatureObject(playerObject)
	
	--printf("bandit destroy\n")
	
	banditdead = readData(player:getObjectID() .. ":tutorial:banditdead")
		
	if banditdead == 1 then
		return 1
	end
		
	writeData(player:getObjectID() .. ":tutorial:banditdead", 1)
		
	createEvent(2000, "TutorialScreenPlay", "lootBanditEvent", playerObject)
	
	return 1
end

function TutorialScreenPlay:tauntBandit(banditObject)
	spatialChat(banditObject, "@newbie_tutorial/newbie_convo:pirate_taunt4")
end

function TutorialScreenPlay:killBandit(banditObject)
	local bandit = LuaCreatureObject(banditObject)
	
	bandit:playEffect("clienteffect/combat_grenade_proton.cef", "")
	bandit:inflictDamage(banditObject, 0, 1000000, 1)
end

function TutorialScreenPlay:lootBanditEvent(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:loot_pirate")
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_00_congratulations.snd")
	end
	
	local playerParent = player:getParent()
	
	if (playerParent == nil) then
		return
	end
	
	--unlock cell door
	local targetCellObject = LuaSceneObject(playerParent)
	local buildingObject = LuaBuildingObject(targetCellObject:getParent())
	
	updateCellPermission(buildingObject:getCell(9), 1, creatureObject)
	writeData(player:getObjectID() .. ":tutorial:officer3flag", 2)
	
	player:setScreenPlayState(524288, "tutorial")
end

function TutorialScreenPlay:officer4(creatureObject, movingCreature)
	local officer = LuaSceneObject(creatureObject)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)
	
	distance = officer:getDistanceTo(movingCreature)
	
	flag = readData(player:getObjectID() .. ":tutorial:officer4flag")
	
	if distance == 0 then
		return 0
	end
	
	if distance < 11 then
		createEvent(1000, "TutorialScreenPlay", "part7_1", movingCreature)
	
		--officer speaks
		rawOfficer = readData(player:getObjectID() .. ":tutorial:officer4")
	
		local officerObject = getSceneObject(rawOfficer)
		spatialChat(officerObject, "@newbie_tutorial/newbie_convo:off_1_greeting")
		
		writeData(player:getObjectID() .. ":tutorial:stattalk", 0)
		writeData(player:getObjectID() .. ":tutorial:instage8", 0)
		
		return 1
	elseif distance < 17 and player:getInCellNumber() == 9 then
		if flag == 0 then
		
			--part seven
			player:sendSystemMessage("@newbie_tutorial/system_messages:part_7")
			
			-- people celebrate
			local npc1 = LuaCreatureObject(getCreatureObject(readData(player:getObjectID() .. ":tutorial:commoner91")))
			local npc2 = LuaCreatureObject(getCreatureObject(readData(player:getObjectID() .. ":tutorial:commoner92")))

			npc1:doAnimation("celebrate1")
			npc2:doAnimation("celebrate1")
			
			writeData(player:getObjectID() .. ":tutorial:officer4flag", 1)
		end
		
		return 0
	else 
		return 0
	end
end

function TutorialScreenPlay:part7_1(movingCreature)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)

	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_28")
	
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_28_converse.snd")
	end
end

function TutorialScreenPlay:officer4select(creatureObject, playerObject)
	createEvent(1000, "TutorialScreenPlay", "part7_2", playerObject)
	return 0
end

function TutorialScreenPlay:part7_2(movingCreature)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
		
	local player = LuaCreatureObject(movingCreature)

	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_49")
	
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_49_skilltrainer.snd")
	end
	
	--make officer4 point to the right
	local a = readData(player:getObjectID() .. ":tutorial:officer4")
	local b = getCreatureObject(a)
	local c = LuaCreatureObject(b)
	
	c:doAnimation("point_right")
	
	createEvent(500, "TutorialScreenPlay", "part7_2_huh", movingCreature)
end

function TutorialScreenPlay:part7_2_huh(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	local trainer = getSceneObject(readData(player:getObjectID() .. ":tutorial:skillTrainer"))
	spatialChat(trainer, "@newbie_tutorial/newbie_convo:trainer_grunt")
end

function TutorialScreenPlay:stopSkillTrainer(creatureObject, playerObject)
	local player = LuaCreatureObject(playerObject)

	skill = readData(player:getObjectID() .. ":tutorial:skill")

	if skill == 0 then
	  s = "social_entertainer_novice"
	elseif skill == 1 then
	  s = "outdoors_scout_novice"
	elseif skill == 2 then
	  s = "science_medic_novice"
	elseif skill == 3 then
	  s = "crafting_artisan_novice"
	elseif skill == 4 then
	  s = "combat_marksman_novice"
	else
	  s = "combat_brawler_novice"
	end

	if player:hasSkill(s) == 1 then 
		createEvent(1000, "TutorialScreenPlay", "part7_3", playerObject)
	
		return 1
	else
		return 0
	end
end

function TutorialScreenPlay:part7_3(movingCreature)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)

	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_50")
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_50_skillbrowser.snd")
	end
	
	createEvent(22000, "TutorialScreenPlay", "part7_4", movingCreature)
end

function TutorialScreenPlay:part7_4(movingCreature)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)

	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_51")
	
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_51_charactersheet.snd")
	end
	
	createEvent(9000, "TutorialScreenPlay", "part7_5", movingCreature)
end

function TutorialScreenPlay:part7_5(movingCreature)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)

	player:sendSystemMessage("@newbie_tutorial/system_messages:stat_open")
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_00_stat_open.snd")
	end
	
	createEvent(30000, "TutorialScreenPlay", "part7_6", movingCreature)
end

function TutorialScreenPlay:part7_6(movingCreature)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)

	instage8 = readData(player:getObjectID() .. ":tutorial:instage8")
	writeData(player:getObjectID() .. ":tutorial:stattalk", 1)
	
	if instage8 == 0 then
		player:sendSystemMessage("@newbie_tutorial/system_messages:visit_commerce_room")
		playSound = readData(player:getObjectID() .. ":tutorial:sound")
		if playSound == 1 then
			player:playMusicMessage("sound/tut_27_proceed.snd")
		end
	end
	
	player:setScreenPlayState(1048576, "tutorial")
end

function TutorialScreenPlay:travelTerminalUse(travelTerminal, playerObject, selectedID)

	if selectedID ~= 20 then
		return 0
	end
	
	local player = LuaCreatureObject(playerObject)
	
	officer6flag = readData(player:getObjectID() .. ":tutorial:officer6flag")

	if (officer6flag == 1) then
		player:setScreenPlayState(4194304, "tutorial")
	
		return 1
	else 	
		rawOfficer = readData(player:getObjectID() .. ":tutorial:officer6")
	
		local officer = getSceneObject(rawOfficer)
		spatialChat(officer, "@newbie_tutorial/newbie_convo:quarter_wait")
		return 0
	end
end	
	
function TutorialScreenPlay:missionTerminalUse(missionTerminal, playerObject, selectedID)
	if selectedID ~= 20 then
		return 0
	end
	
	local player = LuaCreatureObject(playerObject)
	
	--player:setScreenPlayState(65536, "tutorial")
	player:sendSystemMessage("@newbie_tutorial/system_messages:mission_terminal")
	
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_00_mission_terminal.snd")
	end
	
	createEvent(8000, "TutorialScreenPlay", "part8_2", playerObject)
	return 1
end

function TutorialScreenPlay:part8_2(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_54")
	
	writeData(player:getObjectID() .. ":tutorial:off5ready", 1)
	
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_54_npcmission.snd")
	end	

	--officer speaks
	rawOfficer = readData(player:getObjectID() .. ":tutorial:officer5")
	local officer = getSceneObject(rawOfficer)		
	spatialChat(officer, "@newbie_tutorial/newbie_convo:mission_hail")
	
	createEvent(6000, "TutorialScreenPlay", "part8_2_done", playerObject)
end

function TutorialScreenPlay:part8_2_done(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	writeData(player:getObjectID() .. ":tutorial:instage8", 2)
end

function TutorialScreenPlay:missionTerminalMove(creatureObject, movingCreature)
	local terminal = LuaSceneObject(creatureObject)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)
	
	distance = terminal:getDistanceTo(movingCreature)
	
	if distance == 0 then
		return 0
	end
	
	if player:getInCellNumber() == 10 then
		if distance < 10 then
			stattalk = readData(player:getObjectID() .. ":tutorial:stattalk")
			writeData(player:getObjectID() .. ":tutorial:instage8", 1)
			
			if stattalk == 1 then
				createEvent(100, "TutorialScreenPlay", "part8_0", movingCreature)
			else
				createEvent(1000, "TutorialScreenPlay", "part8_check", movingCreature)
			end
		
			return 1
		else
			return 0
		end
	end
	
	return 0
end

function TutorialScreenPlay:part8_check(movingCreature)
	local player = LuaCreatureObject(movingCreature)
	
	stattalk = readData(player:getObjectID() .. ":tutorial:stattalk")
	
	if stattalk == 1 then
		createEvent(100, "TutorialScreenPlay", "part8_0", movingCreature)
	else
		createEvent(1000, "TutorialScreenPlay", "part8_check", movingCreature)
	end
end

function TutorialScreenPlay:part8_0(movingCreature)
	local player = LuaCreatureObject(movingCreature)

	--part nine
	player:sendSystemMessage("@newbie_tutorial/system_messages:part_8")
			
	createEvent(1000, "TutorialScreenPlay", "part8_1", movingCreature)
end	
	
function TutorialScreenPlay:part8_1(movingCreature)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)

	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_53")
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_53_missions.snd")
	end
end

function TutorialScreenPlay:stopOfficer5(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	instage8 = readData(player:getObjectID() .. ":tutorial:instage8")
	
	if instage8 == 2 then
		createEvent(100, "TutorialScreenPlay", "stopOfficer5talk", playerObject)
	else
		createEvent(1000, "TutorialScreenPlay", "stopOfficer5", playerObject)
	end
end

function TutorialScreenPlay:stopOfficer5talk(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	local off4 = LuaCreatureObject(getCreatureObject(readData(player:getObjectID() .. ":tutorial:officer5")))
	
	off4:doAnimation("point_right")
	-- found in data_animation_00.tre/appearance/animation as all_b_emt_point_right.ans
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_56")
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_56_quartermaster.snd")
	end
	
	writeData(player:getObjectID() .. ":tutorial:instage8", 3)
	player:setScreenPlayState(2097152, "tutorial")
end

function TutorialScreenPlay:officer6(creatureObject, movingCreature)
	local officer = LuaSceneObject(creatureObject)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)
	
	instage8 = readData(player:getObjectID() .. ":tutorial:instage8")
	
	if instage8 ~= 3 then
		return 0
	end
	
	distance = officer:getDistanceTo(movingCreature)
	
	if distance == 0 then
		return 0
	end
	
	if distance < 8 then
		--part nine
		player:sendSystemMessage("@newbie_tutorial/system_messages:part_9")
		
		createEvent(1000, "TutorialScreenPlay", "part9_1", movingCreature)
	
		--officer speaks
		rawOfficer = readData(player:getObjectID() .. ":tutorial:officer6")
	
		local officerObject = getSceneObject(rawOfficer)
		spatialChat(officerObject, "@newbie_tutorial/newbie_convo:quarter_greeting")
		
		return 1
	else
		return 0
	end
end

function TutorialScreenPlay:part9_1(movingCreature)
	local player = LuaCreatureObject(movingCreature)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_57")
	playSound = readData(player:getObjectID() .. ":tutorial:sound")
	if playSound == 1 then
		player:playMusicMessage("sound/tut_57_quartermaster.snd")
	end
end
	
function TutorialScreenPlay:refugees(creatureObject, movingCreature)
	local refugee = LuaSceneObject(creatureObject)
	local player = LuaCreatureObject(movingCreature)
	
	distance = refugee:getDistanceTo(movingCreature)
	
	if distance == 0 then
		return 0
	end
	
	if distance < 7 then
		createEvent(500, "TutorialScreenPlay", "refugee1", movingCreature)
		return 1
	end
	
	return 0
end

function TutorialScreenPlay:refugee1(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	local refugee = getSceneObject(readData(player:getObjectID() .. ":tutorial:refugee1"))
	
	spatialChat(refugee, "@newbie_tutorial/newbie_convo:refugee1")

	createEvent(2500, "TutorialScreenPlay", "refugee2", creatureObject)
end

function TutorialScreenPlay:refugee2(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	local refugee = getSceneObject(readData(player:getObjectID() .. ":tutorial:refugee2"))
	
	spatialChat(refugee, "@newbie_tutorial/newbie_convo:refugee5")

	createEvent(2500, "TutorialScreenPlay", "refugee3", creatureObject)
end

function TutorialScreenPlay:refugee3(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	local refugee = getSceneObject(readData(player:getObjectID() .. ":tutorial:refugee3"))
	
	spatialChat(refugee, "@newbie_tutorial/newbie_convo:refugee3")
	createEvent(2500, "TutorialScreenPlay", "refugee4", creatureObject)
end

function TutorialScreenPlay:refugee4(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	local refugee = getSceneObject(readData(player:getObjectID() .. ":tutorial:refugee1"))
	spatialChat(refugee, "@newbie_tutorial/newbie_convo:refugee2")
	createEvent(2500, "TutorialScreenPlay", "refugee5", creatureObject)
end

function TutorialScreenPlay:refugee5(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	local refugee = getSceneObject(readData(player:getObjectID() .. ":tutorial:refugee2"))
	spatialChat(refugee, "@newbie_tutorial/newbie_convo:darn_empire")
	createEvent(2500, "TutorialScreenPlay", "refugee6", creatureObject)
end

function TutorialScreenPlay:refugee6(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	local refugee = getSceneObject(readData(player:getObjectID() .. ":tutorial:refugee3"))
	spatialChat(refugee, "@newbie_tutorial/newbie_convo:refugee4")
end
