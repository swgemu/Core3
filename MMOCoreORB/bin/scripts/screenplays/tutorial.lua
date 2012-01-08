TutorialScreenPlay = ScreenPlay:new {
	numberOfActs = 1
}

imperial_officer_3_handler = {  }
 
-- imperial officer 3
function imperial_officer_3_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)

	local creature = LuaCreatureObject(conversingPlayer)
	local session = LuaConversationSession(creature:getConversationSession())
	local lastScreenId = ""
	if (session ~= nil) then
		lastScreenId = session:getLastConversationScreenName()
	end
	local conversation = LuaConversationTemplate(conversationTemplate)
	
	local lastConversationScreen = conversation:getScreen(lastScreenId)
	
	local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
	local nextConversationScreen
	
	if (string.len(lastScreenId) > 0) then
		
		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		
		nextConversationScreen = conversation:getScreen(optionLink)
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
	local session = LuaConversationSession(creature:getConversationSession())
	local lastScreenId = ""
	if (session ~= nil) then
		lastScreenId = session:getLastConversationScreenName()
	end
	local conversation = LuaConversationTemplate(conversationTemplate)
	
	local lastConversationScreen = conversation:getScreen(lastScreenId)
	
	local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
	local nextConversationScreen
	
	if (string.len(lastScreenId) > 0) then
		
		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		
		nextConversationScreen = conversation:getScreen(optionLink)
		local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
		
		if (nextLuaConversationScreen:getScreenID() == "convoscreen2") then
			writeData(creature:getObjectID() .. ":tutorial:officer5flag", 1)
			createEvent(1000, "TutorialScreenPlay", "stopOfficer5", conversingPlayer)
		end
	else
		
		--Get the initial screen.
		officer5flag = readData(creature:getObjectID() .. ":tutorial:officer5flag")
		if (officer5flag == 0) then
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
	local session = LuaConversationSession(creature:getConversationSession())
	local lastScreenId = ""
	if (session ~= nil) then
		lastScreenId = session:getLastConversationScreenName()
	end
	local conversation = LuaConversationTemplate(conversationTemplate)
	
	local lastConversationScreen = conversation:getScreen(lastScreenId)
	
	local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
	local nextConversationScreen
	
	if (string.len(lastScreenId) > 0) then
		
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
	local session = LuaConversationSession(creature:getConversationSession())
	local lastScreenId = ""
	if (session ~= nil) then
		lastScreenId = session:getLastConversationScreenName()
	end
	local conversation = LuaConversationTemplate(conversationTemplate)
	
	local lastConversationScreen = conversation:getScreen(lastScreenId)
	
	local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
	local nextConversationScreen
	
	if (string.len(lastScreenId) > 0) then
		
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

	-- ** ROOM 1: Welcome **	
	--spawn stormtroopers
	targetCellObject:_setObject(buildingObject:getCell(1))
	
	spawnedPointer = spawnMobile("tutorial", "stormtrooper_filler_tutorial", -2.4, 0, -17.4, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(1, 0, 0, 0)
	--createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "animTest", spawnedPointer) --move observer
	
	spawnedPointer = spawnMobile("tutorial", "stormtrooper_filler_tutorial", 2.5, 0, -17.4, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(1, 0, 0, 0)
	--createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "animTest2", spawnedPointer) --move observer
	
	-- ** ROOM 2: Conversations & Items **
	targetCellObject:_setObject(buildingObject:getCell(2))
	
	--spawn commoners
	--shared_dressed_commoner_fat_zabrak_male_02.iff says refugee1 darn_empire
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 30.2, 0, -43.1, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(0.9945, -0.103, 0, 0)
	createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "refugees", spawnedPointer)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 1)
	writeData(creature:getObjectID() .. ":tutorial:refugee1", spawnedSceneObject:getObjectID())
	
	--shared_dressed_commoner_naboo_human_female_04.iff says leave_me_alone
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 28.6, 0, -42.9, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(0.835, 0, 0.549, 0)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 1)
	writeData(creature:getObjectID() .. ":tutorial:refugee2", spawnedSceneObject:getObjectID())
	
	--shared_dressed_commoner_naboo_human_male_01.iff says 
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 25, 0, -43.5, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(0.97, 0, 0.249, 0)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 1)
	writeData(creature:getObjectID() .. ":tutorial:refugee3", spawnedSceneObject:getObjectID())

	--spawn officer
	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_1", 26.7, 0, -31.9, targetCellObject:getObjectID())
	createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "officer1", spawnedPointer) --move observer
	
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(-0.71, 0, 0.71, 0)
	
	writeData(creature:getObjectID() .. ":tutorial:officer1", spawnedSceneObject:getObjectID())
	
	--drum
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/container/drum/tatt_drum_1.iff", 19, 0, -23, targetCellObject:getObjectID(), 0.71, 0, -0.71, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	
	writeData(creature:getObjectID() .. ":tutorial:drum", spawnedSceneObject:getObjectID())
	
	-- add the starting items (except weapons) to the drum	
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
	
	-- ** ROOM 3: Banks & Bazaars **
	
	targetCellObject:_setObject(buildingObject:getCell(3))
	
	--spawn second officer banker
	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_2", 44, 0, 2.2, targetCellObject:getObjectID())
	createObserver(STARTCONVERSATION, "TutorialScreenPlay", "bankerStartConversation", spawnedPointer)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(0.418, 0, 0.908, 0)
	writeData(creature:getObjectID() .. ":tutorial:officer2", spawnedSceneObject:getObjectID())
	
	--spawn commoner
	--shared_dressed_commoner_naboo_bothan_male_02.iff
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 51.1, 0, -16, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(0.718, 0, -0.696, 0)
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
	
	targetCellObject:_setObject(buildingObject:getCell(4))
	--shared_dressed_commoner_old_human_female_02.iff
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_1", 51.1, -7, -51, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cdistance", 7)
	
	spawnedSceneObject:updateDirection(0.589, 0, -0.807, 0)
	createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "commoner_spatial", spawnedPointer)
	
	--shared_dressed_commoner_old_zabrak_male_02.iff
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_2", 51.5, -7, -53, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 2)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cdistance", 7)
	
	spawnedSceneObject:updateDirection(0.903, 0, -0.428, 0)
	createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "commoner_spatial", spawnedPointer)

	--shared_dressed_commoner_naboo_moncal_male_02.iff
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_3", 47.4, -7, -58.7, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 3)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cdistance", 6)
	
	spawnedSceneObject:updateDirection(0.813, 0, -0.582, 0)
	createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "commoner_spatial", spawnedPointer)
	
	--shared_dressed_stormtrooper_m.iff (-51.49?)
	spawnedPointer = spawnMobile("tutorial", "stormtrooper_filler_tutorial", 26.2, -7, -51.9, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(0, 0, 1, 0)
	
	--shared_dressed_stormtrooper_m.iff
	spawnedPointer = spawnMobile("tutorial", "stormtrooper_filler_tutorial", 26.2, -7, -61.3, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(1, 0, 0, 0)
		
	--** ROOM 5: Cloning & Insurance **
	targetCellObject:_setObject(buildingObject:getCell(5))
	
	--spawn q-3p0
	spawnedPointer = spawnMobile("tutorial", "protocol_droid_3po_silver", 11.9, -7, -56.4, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)

	createObserver(STOPCONVERSATION, "TutorialScreenPlay", "cloningDroidStopConversation", spawnedPointer)
	writeData(creature:getObjectID() .. ":tutorial:protocol", spawnedSceneObject:getObjectID())
	spawnedSceneObject:updateDirection(0.707, 0, 0.707, 0)
	
	--spawn clone terminal
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_cloning.iff", 3, -7, -56.5, targetCellObject:getObjectID(), 0.707, 0, 0.707, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	
	createObserver(OBJECTRADIALUSED, "TutorialScreenPlay", "cloningUseObserver", spawnedPointer)
	
	writeData(creature:getObjectID() .. ":tutorial:clone", spawnedSceneObject:getObjectID())
	
	--spawn insurance terminal
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_insurance.iff", 8.4, -7, -64, targetCellObject:getObjectID(), 1, 0, 0, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	
	createObserver(OBJECTRADIALUSED, "TutorialScreenPlay", "insuranceUseObserver", spawnedPointer)
	
	writeData(creature:getObjectID() .. ":tutorial:insurance", spawnedSceneObject:getObjectID())
	
	--spawn npc panic 1
	--shared_dressed_commoner_tatooine_bith_male_05.iff
	spawnedPointer = spawnMobile("tutorial", "panic_npc_1", -3.3, -7, -75.6, targetCellObject:getObjectID())
	
	createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "panic1MoveObserver", spawnedPointer) --move observer

	--** ROOM 6 **
	--spawn nervous guy in hallway
	targetCellObject:_setObject(buildingObject:getCell(6))
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner", 20.1, -4, -81.5, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(creature:getObjectID() .. ":tutorial:nervous1npc", spawnedSceneObject:getObjectID())
	spawnedSceneObject:updateDirection(0.4005, 0, -0.916, 0)

	createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "nervous1MoveObserver", spawnedPointer) 

	
	--** ROOM 7 **
	targetCellObject:_setObject(buildingObject:getCell(7))

	--spawn officer3
	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_3", 38.1, -7, -79.7, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(creature:getObjectID() .. ":tutorial:officer3flag", 0)
	writeData(creature:getObjectID() .. ":tutorial:officer3", spawnedSceneObject:getObjectID())
	createObserver(STARTCONVERSATION, "TutorialScreenPlay", "officer3StartConversation", spawnedPointer)
	
	--testing (annoying to walk over there every time):
	--targetCellObject:_setObject(buildingObject:getCell(1))
	--spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_3", 0, 0, -17.4, targetCellObject:getObjectID())
	
	createObserver(STOPCONVERSATION, "TutorialScreenPlay", "officer3StopConversation", spawnedPointer)
	createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "converseWithOfficer3Observer", spawnedPointer) --move observer
	
	-- ** ROOM 14(don't ask) **
	targetCellObject:_setObject(buildingObject:getCell(14))

	--spawn debris	
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/newbie_tutorial/debris.iff", 76.9, -4, -94.3, targetCellObject:getObjectID(), 1, 0, 0, 0)
	createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "nearDebrisObserver", spawnedPointer) --move observer
	createObserver(OBJECTDESTRUCTION, "TutorialScreenPlay", "debrisDestroyedObserver", spawnedPointer) --destroy observer
	
	-- ** ROOM 8 **
	targetCellObject:_setObject(buildingObject:getCell(8))

	--spawn retard to kill
	spawnedPointer = spawnMobile("tutorial", "bandit_tutorial_1", 38.1, -5.9, -113.4, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(0.707, 0, 0.707, 0)
	
	writeData(creature:getObjectID() .. ":tutorial:banditflag", 0)
	
	--register damage observer
	createObserver(DAMAGERECEIVED, "TutorialScreenPlay", "banditDamageObserver", spawnedPointer) --damage observer
	createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "banditMoveObserver", spawnedPointer)
	
	createObserver(POSITIONCHANGED, "TutorialScreenPlay", "part4StartObserver", creatureObject) --move observer
	createObserver(POSITIONCHANGED, "TutorialScreenPlay", "part5StartObserver", creatureObject) --move observer

	--** ROOM 9: Skill Trainers **
	targetCellObject:_setObject(buildingObject:getCell(9))	
	
	--spawn another commoner: celeb_guy1
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", -1, -4.2, -118.2, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(0.838, 0.545, 0, 0)
	writeData(creature:getObjectID() .. ":tutorial:commoner91", spawnedSceneObject:getObjectID())
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 2)
	
	--spawn another commoner: celeb_guy4
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 1.4, -4.2, -132, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(0.97, 0.241, 0, 0)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 3)

	--spawn another commoner: celeb_guy3	
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 13.1, -4.2, -119.8, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(0.927, 0, -0.373, 0)	
	spawnedCreatureObject = LuaCreatureObject(spawnedPointer)
	spawnedCreatureObject:setState(STATESITTINGONCHAIR)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 4)
	
	--spawn another commoner: celeb_guy2
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", 13.145, -4.2, -106.292, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(0.436, 0, -0.899, 0)
	spawnedCreatureObject = LuaCreatureObject(spawnedPointer)
	spawnedCreatureObject:setState(STATESITTINGONCHAIR)
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 5)
	
	--spawn another commoner: celeb_guy5
	spawnedPointer = spawnMobile("tutorial", "tutorial_commoner_talking", -0.8, -4.2, -108.2, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(0.476, 0, 0.879, 0)
	writeData(creature:getObjectID() .. ":tutorial:commoner92", spawnedSceneObject:getObjectID())
	writeData(spawnedSceneObject:getObjectID() .. ":tutorial:cid", 6)
	
	--imperial officer 4
	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_4", 2.1, -4.2, -123.8, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(creature:getObjectID() .. ":tutorial:officer4", spawnedSceneObject:getObjectID())
	
	writeData(creature:getObjectID() .. ":tutorial:officer4flag", 0)
	
	spawnedSceneObject:updateDirection(0.97, 0, 0.241, 0)
	createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "officer4", spawnedPointer) --move observer
	createObserver(SELECTCONVERSATION, "TutorialScreenPlay", "officer4select", spawnedPointer)

	-- trainer
	local player = LuaCreatureObject(creatureObject)
	
	--starting skills:
	  -- social_entertainer_novice
	  -- outdoors_scout_novice
	  -- science_medic_novice
	  -- crafting_artisan_novice
	  -- combat_marksman_novice
	  -- combat_brawler_novice
	if (player:hasSkill("social_entertainer_novice") == 1) then
		trainerTemplate = "trainer_entertainer"
		player:removeSkill("social_entertainer_novice")
		writeData(creature:getObjectID() .. ":tutorial:skill", 0)
	elseif (player:hasSkill("outdoors_scout_novice") == 1) then
		trainerTemplate = "trainer_scout"
		player:removeSkill("outdoors_scout_novice")
		writeData(creature:getObjectID() .. ":tutorial:skill", 1)
	elseif (player:hasSkill("science_medic_novice") == 1) then
		trainerTemplate = "trainer_medic"
		player:removeSkill("science_medic_novice")
		writeData(creature:getObjectID() .. ":tutorial:skill", 2)
	elseif (player:hasSkill("crafting_artisan_novice") == 1) then
		trainerTemplate = "trainer_artisan"
		player:removeSkill("crafting_artisan_novice")
		writeData(creature:getObjectID() .. ":tutorial:skill", 3)
	elseif (player:hasSkill("combat_marksman_novice") == 1) then
		trainerTemplate = "trainer_marksman"
		player:removeSkill("combat_marksman_novice")
		writeData(creature:getObjectID() .. ":tutorial:skill", 4)
	else
		trainerTemplate = "trainer_brawler"
		player:removeSkill("combat_brawler_novice")
		writeData(creature:getObjectID() .. ":tutorial:skill", 5)
	end
	
	spawnedPointer = spawnMobile("tutorial", trainerTemplate, 7.1, -4.2, -128.2, targetCellObject:getObjectID())
	createObserver(STOPCONVERSATION, "TutorialScreenPlay", "stopSkillTrainer", spawnedPointer)
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(creature:getObjectID() .. ":tutorial:skillTrainer", spawnedSceneObject:getObjectID())
	spawnedSceneObject:updateDirection(0.975, 0, -0.220, 0)
	--spawnedCreatureObject = LuaCreatureObject(spawnedPointer)

	--** ROOM 10: Missions **
	targetCellObject:_setObject(buildingObject:getCell(10))
	-- officer 5: mission
	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_5", 19.5, -4.2, -146, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(creature:getObjectID() .. ":tutorial:officer5", spawnedSceneObject:getObjectID())
	spawnedSceneObject:updateDirection(1, 0, 0, 0)
	writeData(creature:getObjectID() .. ":tutorial:officer5flag", 0)
	
	--mission terminal
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_mission_newbie.iff", 19.2, -4.2, -134.2, targetCellObject:getObjectID(), 0, 0, 1, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "missionTerminalMove", spawnedPointer)
	createObserver(OBJECTRADIALUSED, "TutorialScreenPlay", "missionTerminalUse", spawnedPointer)
	
	--** ROOM 11: Travel Terminal **
	targetCellObject:_setObject(buildingObject:getCell(11))
	
	-- officer 6: quartermaster
	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_6", 31.3, -4.2, -164, targetCellObject:getObjectID())
	createObserver(OBJECTINRANGEMOVED, "TutorialScreenPlay", "officer6", spawnedPointer) --move observer
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(0.994, 0.103, 0, 0)
	spawnedCreatureObject = LuaCreatureObject(spawnedPointer)
	spawnedCreatureObject:setCustomObjectName("The Quartermaster")
	writeData(creature:getObjectID() .. ":tutorial:officer6", spawnedSceneObject:getObjectID())
	writeData(creature:getObjectID() .. ":tutorial:officer6flag", 0)
	
	-- travel terminal
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/beta/beta_terminal_warp.iff", 27.0, -3.5, -168.0, targetCellObject:getObjectID(), 0, 0, 1, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:updateDirection(1, 0, 0, 0)
	createObserver(OBJECTRADIALUSED, "TutorialScreenPlay", "travelTerminalUse", spawnedPointer)
	writeData(creature:getObjectID() .. ":tutorial:travelTerminal", spawnedSceneObject:getObjectID())
	
	terminal = readData(creature:getObjectID() .. ":tutorial:travelTerminal")
	local travelTerminal = getSceneObject(terminal)
	setAuthorizationState(travelTerminal, false)
	
	return 1
end


function TutorialScreenPlay:start(creatureObject)	
	--printf("Running introduction\n")
	
	local creature = LuaCreatureObject(creatureObject)
	
	-- check if the tutorial already started
	id = readData(creature:getObjectID() .. ":tutorial:drum")
	
	--state = creature:hasScreenPlayState(262144, "tutorial")
	
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
	
	--lock cell door
	local targetCellObject = LuaSceneObject(creature:getParent())
	local buildingObject = LuaBuildingObject(targetCellObject:getParent())
	--printf("Set local vars\n")
	targetCellObject:_setObject(buildingObject:getCell(9))
	--printf("Set cell to 9\n")
	targetCellObject:updateCellPermission(0, creatureObject)
	
	--printf("updated permission\n")
	
	creature:sendNewbieTutorialEnableHudElement("all", 0)
	creature:sendNewbieTutorialEnableHudElement("buttonbar", 1)

	creature:sendSystemMessage("@newbie_tutorial/system_messages:welcome")
	creature:playMusicMessage("sound/tut_01_welcome.snd")
	
	createEvent(4000, "TutorialScreenPlay", "secondMessage", creatureObject)
end


function TutorialScreenPlay:secondMessage(creatureObject)
	--printf("Runnging TutorialScreenPlay:secondMessage")
	local creature = LuaCreatureObject(creatureObject)

	creature:sendSystemMessage("@newbie_tutorial/system_messages:part_1")
	
	createEvent(2000, "TutorialScreenPlay", "secondAct_1", creatureObject)
end

function TutorialScreenPlay:secondAct_1(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	creature:sendSystemMessage("@newbie_tutorial/system_messages:movement_keyboard")
	creature:playMusicMessage("sound/tut_02_movement.snd")
	
	createEvent(2000, "TutorialScreenPlay", "secondAct_2", creatureObject)
end

function TutorialScreenPlay:secondAct_2(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	creature:sendSystemMessage("@newbie_tutorial/system_messages:movement_mouse")
	
	createEvent(4000, "TutorialScreenPlay", "secondAct_3", creatureObject)
end

function TutorialScreenPlay:secondAct_3(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	creature:sendSystemMessage("@newbie_tutorial/system_messages:lookaround")
	
	createEvent(4000, "TutorialScreenPlay", "thirdAct", creatureObject)
end

function TutorialScreenPlay:thirdAct(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	creature:sendSystemMessage("@newbie_tutorial/system_messages:mousewheel")
	creature:playMusicMessage("sound/tut_00_camera.snd")
	creature:sendNewbieTutorialRequest("zoomCamera")
	
	writeData(creature:getObjectID() .. ":tutorial:zoom", 0)
	
	createObserver(NEWBIETUTORIALZOOMCAMERA, "TutorialScreenPlay", "zoomEvent", creatureObject)
	createEvent(25000, "TutorialScreenPlay", "helperZoom", creatureObject)
	createEvent(30000, "TutorialScreenPlay", "helpZoom", creatureObject)
end

function TutorialScreenPlay:helperZoom(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	writeData(creature:getObjectID() .. ":tutorial:zoom", 1)
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

function TutorialScreenPlay:zoomEvent(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	local done = readData(creature:getObjectID() .. ":tutorial:zoom")
	
	if (done == 0) then
		createEvent(1000, "TutorialScreenPlay", "checkZoom", creatureObject)
	else
		createEvent(1000, "TutorialScreenPlay", "doneZoom", creatureObject)
	end

	return 1
end

function TutorialScreenPlay:checkZoom(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	local done = readData(creature:getObjectID() .. ":tutorial:zoom")
	
	if (done == 0) then
		createEvent(1000, "TutorialScreenPlay", "checkZoom", creatureObject)
	else
		createEvent(1000, "TutorialScreenPlay", "doneZoom", creatureObject)
	end
end

function TutorialScreenPlay:doneZoom(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	creature:setScreenPlayState(1, "tutorial")
	
	creature:sendNewbieTutorialEnableHudElement("chatbox", 1)
	
	creature:playMusicMessage("sound/tut_04_chat.snd")
	creature:sendSystemMessage("@newbie_tutorial/system_messages:chatwindow")
	
	writeData(creature:getObjectID() .. ":tutorial:chat", 0)
	
	creature:sendNewbieTutorialRequest("chatbox")
	
	createEvent(16000, "TutorialScreenPlay", "helpChat", creatureObject)
	createObserver(CHAT, "TutorialScreenPlay", "chatEvent", creatureObject)
	
	createEvent(4000, "TutorialScreenPlay", "nextChat", creatureObject)
	
	return 1
end
	
function TutorialScreenPlay:nextChat(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	creature:sendSystemMessage("@newbie_tutorial/system_messages:chatprompt")
	
	createEvent(4000, "TutorialScreenPlay", "finishChat", creatureObject)
end

function TutorialScreenPlay:finishChat(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	writeData(creature:getObjectID() .. ":tutorial:chat", 1)
end

function TutorialScreenPlay:chatEvent(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:chat")
	
	if finished == 0 then
		createEvent(1000, "TutorialScreenPlay", "checkChat", creatureObject)
	else
		creature:setScreenPlayState(2, "tutorial")
		createEvent(1000, "TutorialScreenPlay", "holocron", creatureObject)	
	end
	
	return 1
end

function TutorialScreenPlay:checkChat(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:chat")
	
	if finished == 0 then
		createEvent(1000, "TutorialScreenPlay", "checkChat", creatureObject)
	else
		creature:setScreenPlayState(2, "tutorial")
		createEvent(1000, "TutorialScreenPlay", "holocron", creatureObject)	
	end
end

function TutorialScreenPlay:helpChat(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	state = creature:hasScreenPlayState(2, "tutorial")
	
	if state == 0 then
		creature:sendNewbieTutorialRequest("chatbox")
		creature:sendSystemMessage("@newbie_tutorial/system_messages:repeatchatprompt")
		creature:playMusicMessage("sound/tut_05_remind_chat.snd")
		--let's not be too annoying
		--createEvent(10000, "TutorialScreenPlay", "helpChat", creatureObject)
	end
end

function TutorialScreenPlay:holocron(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	creature:sendOpenHolocronToPageMessage()
	
	createObserver(NEWBIETUTORIALHOLOCRON, "TutorialScreenPlay", "holocronEvent", creatureObject)
	creature:sendNewbieTutorialRequest("closeHolocron")
	
	writeData(creature:getObjectID() .. ":tutorial:holocron", 0)
	
	creature:playMusicMessage("sound/tut_00_holocron.snd")
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
		createEvent(1000, "TutorialScreenPlay", "checkHolocron", creatureObject)
	else
		createEvent(1000, "TutorialScreenPlay", "moveToItemRoom", creatureObject)
	end
	
	return 1
end

function TutorialScreenPlay:checkHolocron(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:holocron")
	
	if finished == 0 then
		createEvent(1000, "TutorialScreenPlay", "checkHolocron", creatureObject)
	else
		createEvent(1000, "TutorialScreenPlay", "moveToItemRoom", creatureObject)
	end
end

function TutorialScreenPlay:moveToItemRoom(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	creature:sendSystemMessage("@newbie_tutorial/system_messages:move_to_item_room")
	creature:playMusicMessage("sound/tut_06_excellent.snd")
	
	writeData(creature:getObjectID() .. ":tutorial:moveitemroom", 1)
	
	createEvent(1000, "TutorialScreenPlay", "itemRoomCheck", creatureObject)
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

function TutorialScreenPlay:itemRoomCheck(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	cellNumber = creature:getInCellNumber()
	
	moveitemroom = readData(creature:getObjectID() .. ":tutorial:moveitemroom")
	
	if cellNumber < 2 then
		
		if (moveitemroom % 7 == 0) then
			creature:sendSystemMessage("@newbie_tutorial/system_messages:repeat_item_room_prompt")
			creature:playMusicMessage("sound/tut_07_comeon.snd")
		end
		
		writeData(creature:getObjectID() .. ":tutorial:moveitemroom", moveitemroom + 1)
		
		createEvent(1000, "TutorialScreenPlay", "itemRoomCheck", creatureObject)
	else	
		creature:sendSystemMessage("@newbie_tutorial/system_messages:part_2")
		createEvent(1000, "TutorialScreenPlay", "room2", creatureObject)
	end
end

function TutorialScreenPlay:room2(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	creature:sendNewbieTutorialRequest("changeLookAtTarget")
	
	writeData(creature:getObjectID() .. ":tutorial:room2", 0)
	writeData(creature:getObjectID() .. ":tutorial:looked", 0)
	
	createEvent(1000, "TutorialScreenPlay", "part2Start", creatureObject)
	createObserver(PLAYERCHANGEDTARGET, "TutorialScreenPlay", "officerTargetEvent", creatureObject)
end

function TutorialScreenPlay:part2Start(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	creature:sendNewbieTutorialEnableHudElement("chatbox", 1)
	
	creature:playMusicMessage("sound/tut_08_imperialofficer.snd")
	creature:sendSystemMessage("@newbie_tutorial/system_messages:tut_08")
	
	createEvent(7000, "TutorialScreenPlay", "part2StartDone", creatureObject)
end

function TutorialScreenPlay:part2StartDone(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	looked = readData(creature:getObjectID() .. ":tutorial:looked")
	
	if looked == 0 then
		officer1ObjectID = readData(creature:getObjectID() .. ":tutorial:officer1")
		spatialChat(getSceneObject(officer1ObjectID), "@newbie_tutorial/newbie_convo:explain_lookat")
	end
	
	writeData(creature:getObjectID() .. ":tutorial:room2", 1)
end

function TutorialScreenPlay:officerTargetEvent(creatureObject, targetCreature)
	local player = LuaCreatureObject(creatureObject)
	local officer = LuaCreatureObject(targetCreature)
		
	officer1ObjectID = readData(player:getObjectID() .. ":tutorial:officer1")

	if officer:getObjectID() == officer1ObjectID then
		
		finished = readData(player:getObjectID() .. ":tutorial:room2")
		
		if finished == 0 then
			createEvent(1000, "TutorialScreenPlay", "checkTarget", creatureObject)
		else
			createEvent(1000, "TutorialScreenPlay", "checkedTarget", creatureObject)
		end
		
		return 1
	end
	
	return 0	
end

function TutorialScreenPlay:checkTarget(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	finished = readData(creature:getObjectID() .. ":tutorial:room2")
	
	if finished == 0 then
		createEvent(1000, "TutorialScreenPlay", "checkTarget", creatureObject)
	else
		createEvent(100, "TutorialScreenPlay", "checkedTarget", creatureObject)
	end
end

function TutorialScreenPlay:checkedTarget(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_09")
	player:playMusicMessage("sound/tut_09_lookat.snd")
		
	createEvent(5000, "TutorialScreenPlay", "tutorial10", creatureObject)
	
	officer1ObjectID = readData(player:getObjectID() .. ":tutorial:officer1")
	
	createObserver(STARTCONVERSATION, "TutorialScreenPlay", "officerConversation", getCreatureObject(officer1ObjectID))
end
 
--CONTINUE WORK HERE
function TutorialScreenPlay:tutorial10(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	creature:sendSystemMessage("thus far -.-")
	creature:sendSystemMessage("@newbie_tutorial/system_messages:tut_10")
	creature:playMusicMessage("sound/tut_10_radialmenu.snd")
	
	createEvent(5000, "TutorialScreenPlay", "tutorial11", creatureObject)
end

function TutorialScreenPlay:tutorial11(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	creature:sendSystemMessage("@newbie_tutorial/system_messages:tut_11")
	creature:playMusicMessage("sound/tut_11_converse.snd")
	
	--createEvent(5000, "TutorialScreenPlay", "tutorial11", creatureObject)
end

function TutorialScreenPlay:officerConversation(creatureObject, playerObject)
	local player = LuaCreatureObject(playerObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_12")
	player:playMusicMessage("sound/tut_12_conversation.snd")
	
	--createEvent(12000, "TutorialScreenPlay", "tutorial13", playerObject)
	createObserver(SELECTCONVERSATION, "TutorialScreenPlay", "tutorial13", creatureObject)
	
	return 1
end

function TutorialScreenPlay:tutorial13(creatureObject, playerObject)
	local creature = LuaCreatureObject(playerObject)
	
	creature:sendSystemMessage("@newbie_tutorial/system_messages:tut_13")
	creature:playMusicMessage("sound/tut_13_justtype.snd")
	
	createObserver(STOPCONVERSATION, "TutorialScreenPlay", "stopConversation", creatureObject)
	
	return 1
end

function TutorialScreenPlay:stopConversation(creatureObject, playerObject)
	local creature = LuaCreatureObject(playerObject)
	
	creature:sendNewbieTutorialRequest("changeLookAtTarget")
	creature:sendNewbieTutorialEnableHudElement("chatbox", 1)
	
	drumObjectID = readData(creature:getObjectID() .. ":tutorial:drum")
	
	local drumRawPointer = getSceneObject(drumObjectID)
	local drumObject = LuaSceneObject(drumRawPointer)
	drumObject:showFlyText("newbie_tutorial/system_messages", "open_me", 0, 255, 0)
	
	creature:sendSystemMessage("@newbie_tutorial/system_messages:prompt_open_box")
	creature:playMusicMessage("sound/tut_14_openbox.snd")
	
	createObserver(OPENCONTAINER, "TutorialScreenPlay", "openDrumEvent", drumRawPointer)
	
	createEvent(5000, "TutorialScreenPlay", "drumTargetEvent", playerObject)
	
	return 1
end

function TutorialScreenPlay:drumTargetEvent(creatureObject)
	local player = LuaCreatureObject(creatureObject)

	drumObjectID = readData(player:getObjectID() .. ":tutorial:drum")
	
	if player:getTargetID() == drumObjectID then
		player:sendSystemMessage("@newbie_tutorial/system_messages:prompt_choose_open")
		player:playMusicMessage("sound/tut_15_opencontainer.snd")
	else
		player:sendSystemMessage("@newbie_tutorial/system_messages:repeat_open_box")
		local drumObject = LuaSceneObject(getSceneObject(drumObjectID))
		drumObject:showFlyText("newbie_tutorial/system_messages", "open_me", 0, 255, 0)
		createEvent(5000, "TutorialScreenPlay", "drumTargetEvent", creatureObject)
	end
end

function TutorialScreenPlay:openDrumEvent(drumObject, creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:prompt_take_items")
	player:playMusicMessage("sound/tut_16_a_youcantake.snd")
	
	createObserver(CLOSECONTAINER, "TutorialScreenPlay", "closeDrumEvent", drumObject)
	
	return 1
end

function TutorialScreenPlay:closeDrumEvent(drumObject, creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:pickup_complete")
	player:playMusicMessage("sound/tut_18_inventory.snd")
	
	createEvent(2000, "TutorialScreenPlay", "openInventory", creatureObject)
	
	return 1
end

function TutorialScreenPlay:openInventory(creatureObject)
	local player = LuaCreatureObject(creatureObject)

	player:sendSystemMessage("@newbie_tutorial/system_messages:explain_freemouse")
	player:playMusicMessage("sound/tut_19_inventory.snd")
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:explain_freemouse_toggle")
	player:sendSystemMessage("@newbie_tutorial/system_messages:explain_inventory")
	
	player:sendNewbieTutorialRequest("openInventory")
	createObserver(NEWBIEOPENINVENTORY, "TutorialScreenPlay", "openInventoryObserver", creatureObject)
	createEvent(11000, "TutorialScreenPlay", "openInventory2", creatureObject)
end

function TutorialScreenPlay:openInventory2(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:repeat_open_inventory")
	player:playMusicMessage("sound/tut_25_openinventory.snd")
end

function TutorialScreenPlay:openInventoryObserver(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:prompt_find_food")
	player:playMusicMessage("sound/tut_20_selectfooditem.snd")
	
	createObserver(GETATTRIBUTESBATCHCOMMAND, "TutorialScreenPlay", "foodTargetEvent", creatureObject)
	
	return 1

end

function TutorialScreenPlay:foodTargetEvent(creatureObject, targetObject, batch)

	--printf("foodTarget fired\n")
	
	local player = LuaCreatureObject(creatureObject)
	local food = LuaSceneObject(targetObject)
	
	
	state = player:hasScreenPlayState(64, "tutorial")
	
	if state ~= 1 then
		--printf("Checking: " .. batch .. "\n")
		--check if its maroj melon, register use now
		
		
		
		if (food:getGameObjectType() ~= 8202) or (batch > 0) then -- food
			return 0
		end
		
		--createObserver(OBJECTRADIALUSED, "TutorialScreenPlay", "foodUsed", item)
		player:sendSystemMessage("@newbie_tutorial/system_messages:prompt_use_item")
		player:playMusicMessage("sound/tut_21_usefood.snd")
		
		player:setScreenPlayState(64, "tutorial")
		--printf("Set state\n")
	end
	return 1
	
end

function TutorialScreenPlay:closeInventoryObserver(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:setScreenPlayState(256, "tutorial")
	
	createEvent(5000, "TutorialScreenPlay", "activateToolbar", creatureObject)
	
	return 1
end

function TutorialScreenPlay:foodUsed(foodObject, creatureObject, selectedID)
	if selectedID ~= 20 then
		return 0
	end
	
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:explain_item_used")
	player:playMusicMessage("sound/tut_22_attributes.snd")
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:close_inventory")
	
	player:sendNewbieTutorialRequest("closeInventory")
	createObserver(NEWBIECLOSEINVENTORY, "TutorialScreenPlay", "closeInventoryObserver", creatureObject)
	
	return 1
end

function TutorialScreenPlay:activateToolbar(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendNewbieTutorialEnableHudElement("toolbar", 1)
	player:sendSystemMessage("@newbie_tutorial/system_messages:show_toolbar")
	player:playMusicMessage("sound/tut_23_toolbar.snd")

	createEvent(2000, "TutorialScreenPlay", "explainToolbar", creatureObject)
end

function TutorialScreenPlay:explainToolbar(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_00_toolbardrag")
	player:playMusicMessage("sound/tut_00_toolbardrag.snd")

	--player:sendSystemMessage("@newbie_tutorial/system_messages:use_toolbar")
	--player:playMusicMessage("sound/tut_24_toolbarslots.snd")
	

	createEvent(5000, "TutorialScreenPlay", "checkInventoryClosed", creatureObject)
end

function TutorialScreenPlay:checkInventoryClosed(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	state = player:hasScreenPlayState(256, "tutorial") -- closed inventory state
	
	if state == 0 then
	--	player:sendSystemMessage("@newbie_tutorial/system_messages:close_inventory")
	--	player:playMusicMessage("sound/tut_26_closeinventory.snd")
		
	--	player:sendNewbieTutorialRequest("closeInventory")
	--	createEvent(5000, "TutorialScreenPlay", "checkInventoryClosed", creatureObject)
		
	--	return
	
		player:setScreenPlayState(256, "tutorial")
	end
		
	player:sendNewbieTutorialEnableHudElement("toolbar", 1)
	player:sendNewbieTutorialEnableHudElement("chatbox", 1)
	
	createEvent(5000, "TutorialScreenPlay", "checkCommerceRoom", creatureObject) 
end

function TutorialScreenPlay:checkCommerceRoom(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	if player:getInCellNumber() ~= 3 then
		state = player:hasScreenPlayState(512, "tutorial")
		if state ~= 1 then
			player:sendSystemMessage("@newbie_tutorial/system_messages:visit_commerce_room")
			player:playMusicMessage("sound/tut_27_proceed.snd")
			player:setScreenPlayState(512, "tutorial")
			createEvent(5000, "TutorialScreenPlay", "checkCommerceRoom", creatureObject)
			return
		end
		
		
		player:sendSystemMessage("@newbie_tutorial/system_messages:repeat_visit_commerce")
		player:playMusicMessage("sound/tut_27_proceed.snd")
	
		createEvent(5000, "TutorialScreenPlay", "checkCommerceRoom", creatureObject)
		
		return
	end
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:part_3")
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_28")
	player:playMusicMessage("sound/tut_28_converse.snd")
	
	--officer speaks
	local officer2 = getSceneObject(readData(player:getObjectID() .. ":tutorial:officer2"))
	
	spatialChat(officer2, "@newbie_tutorial/newbie_convo:banker_greeting")
end

function TutorialScreenPlay:bankerStartConversation(creatureObject, playerObject)
	local player = LuaCreatureObject(playerObject)
	
	--createEvent(1000, "TutorialScreenPlay", "activateBankUseCheck", playerObject)
	--createEvent(1000, "TutorialScreenPlay", "activateBazaarUseCheck", playerObject)
	
	--createObserver(PLAYERCHANGEDTARGET, "TutorialScreenPlay", "activateBankTargetCheck", playerObject)
	--createObserver(PLAYERCHANGEDTARGET, "TutorialScreenPlay", "activateBazaarTargetCheck", playerObject)
	
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
	player:playMusicMessage("sound/tut_32_bank.snd")
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
	player:playMusicMessage("sound/tut_33_cash.snd")
	createEvent(8000, "TutorialScreenPlay", "explainBank_finished", playerObject)
end

function TutorialScreenPlay:explainBank_finished(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	writeData(player:getObjectID() .. ":tutorial:bankflag", 1)
end

function TutorialScreenPlay:explainBazaar_1(playerObject)
	local player = LuaCreatureObject(playerObject)

	player:sendSystemMessage("@newbie_tutorial/system_messages:bazaar_info_1")
	player:playMusicMessage("sound/tut_29_itemdispenser.snd")
	createEvent(5000, "TutorialScreenPlay", "explainBazaar_2", playerObject)
end

function TutorialScreenPlay:explainBazaar_2(playerObject)
	local player = LuaCreatureObject(playerObject)

	player:sendSystemMessage("@newbie_tutorial/system_messages:bazaar_info_2")
	player:playMusicMessage("sound/tut_00_bazaar_tease.snd")
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
	player:playMusicMessage("sound/tut_36_movedownhall.snd")
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
	player:playMusicMessage("sound/tut_37_cloning.snd")
	
	createEvent(2000, "TutorialScreenPlay", "cloneHereEvent", playerObject)
			
	return 1
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
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:declare_cloned")
	
	protocolDroidOid = readData(player:getObjectID() .. ":tutorial:protocol")
	local droidPointer = getSceneObject(protocolDroidOid)	
			
	spatialChat(droidPointer, "@newbie_tutorial/newbie_convo:convo_3_explain_terminal_1")
	
	createEvent(5000, "TutorialScreenPlay", "explainInsurance", playerObject)
	
	return 1
end

function TutorialScreenPlay:explainInsurance(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	protocolDroidOid = readData(player:getObjectID() .. ":tutorial:protocol")
	local droidPointer = getSceneObject(protocolDroidOid)	
			
	spatialChat(droidPointer, "@newbie_tutorial/newbie_convo:convo_3_explain_terminal_2")
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_38")
	player:playMusicMessage("sound/tut_38_insurance.snd")
	
	createEvent(3000, "TutorialScreenPlay", "insuranceCheckEvent", creatureObject)
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
	player:sendSystemMessage("@newbie_tutorial/system_messages:declare_insured")	
	
	return 1
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
	
	if distance < 8 then
		spatialShout(creatureObject, "@newbie_tutorial/newbie_convo:shout_panic1")
		
		player:sendSystemMessage("@newbie_tutorial/system_messages:radar")
		player:playMusicMessage("sound/tut_41_advancewarning.snd")
		player:sendNewbieTutorialEnableHudElement("radar", 1)
		
		createEvent(1000, "TutorialScreenPlay", "continuePanic1", creatureObject)
		
		return 1
	else
		return 0
	end
end

function TutorialScreenPlay:continuePanic1(creatureObject)
	spatialShout(creatureObject, "@newbie_tutorial/newbie_convo:shout_panic2")
	
	createEvent(1000, "TutorialScreenPlay", "continuePanic2", creatureObject)
end

function TutorialScreenPlay:continuePanic2(creatureObject)
	spatialShout(creatureObject, "@newbie_tutorial/newbie_convo:shout_panic3")
end

function TutorialScreenPlay:part5StartObserver(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	if player:getInCellNumber() == 6 then
		state = player:hasScreenPlayState(131072, "tutorial")
		
		if state == 0 then
			player:sendSystemMessage("@newbie_tutorial/system_messages:part_5")
			player:setScreenPlayState(131072, "tutorial")
			player:sendNewbieTutorialEnableHudElement("radar", 1)
			
			player:sendSystemMessage("@newbie_tutorial/system_messages:radar_more")
			player:playMusicMessage("sound/tut_42_map.snd")
						
			--player:sendNewbieTutorialEnableHudElement("all", 1)
			
			createEvent(9000, "TutorialScreenPlay", "explainOverlayMap", creatureObject)
			
			--createObserver(POSITIONCHANGED, "TutorialScreenPlay", "officer3Start", creatureObject) --move observer
			
			return 1
		end
	end
	
	return 0
end

function TutorialScreenPlay:explainOverlayMap(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_43")
	player:playMusicMessage("sound/tut_43_zoommap.snd")
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
		player:sendSystemMessage("@newbie_tutorial/system_messages:tut_40")
		player:playMusicMessage("sound/tut_40_converse.snd")
		
		return 1
	else
		return 0
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
		player:playMusicMessage("sound/tut_45_proceed.snd")
		
		return 1
	else
		return 0
	end
end

function TutorialScreenPlay:debrisDestroyedObserver(debrisObject, playerObject)
	local player = LuaCreatureObject(playerObject)
	local debris = LuaSceneObject(debrisObject)
	
	player:sendNewbieTutorialEnableHudElement("all", 1)
	
	debris:destroyObjectFromWorld()
	
	player:clearCombatState(1)

	player:sendSystemMessage("@newbie_tutorial/system_messages:part_6")
	
	createEvent(1000, "TutorialScreenPlay", "startExplainCombat", playerObject)
	
	return 1
end

function TutorialScreenPlay:startExplainCombat(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:explain_combat_1")
	player:playMusicMessage("sound/tut_47_defaultattack.snd")
	
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
	player:playMusicMessage("sound/tut_44_attacking.snd")
end

function TutorialScreenPlay:banditMoveObserver(creatureObject, movingCreature)
	local bandit = LuaSceneObject(creatureObject)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)
	
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
		spatialChat(banditObject, "@newbie_tutorial/newbie_convo:pirate_taunt3")
		
		createEvent(2000, "TutorialScreenPlay", "tauntBandit", banditObject)
		
		createEvent(4000, "TutorialScreenPlay", "killBandit", banditObject) 
		createEvent(6000, "TutorialScreenPlay", "lootBanditEvent", playerObject)
				
		return 1		
	end
	
	return 0
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
	player:playMusicMessage("sound/tut_00_congratulations.snd")
	
	--unlock cell door
	local targetCellObject = LuaSceneObject(player:getParent())
	local buildingObject = LuaBuildingObject(targetCellObject:getParent())
	targetCellObject:_setObject(buildingObject:getCell(9))
	targetCellObject:updateCellPermission(1, creatureObject)
	writeData(player:getObjectID() .. ":tutorial:officer3flag", 2)
	
	player:setScreenPlayState(262144, "tutorial")
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
	player:playMusicMessage("sound/tut_28_converse.snd")
end

function TutorialScreenPlay:officer4select(creatureObject, playerObject)
	createEvent(1000, "TutorialScreenPlay", "part7_2", playerObject)
end

function TutorialScreenPlay:part7_2(movingCreature)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
		
	local player = LuaCreatureObject(movingCreature)

	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_49")
	player:playMusicMessage("sound/tut_49_skilltrainer.snd")
	
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
	player:playMusicMessage("sound/tut_50_skillbrowser.snd")
	
	createEvent(22000, "TutorialScreenPlay", "part7_4", movingCreature)
end

function TutorialScreenPlay:part7_4(movingCreature)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)

	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_51")
	player:playMusicMessage("sound/tut_51_charactersheet.snd")
	
	createEvent(9000, "TutorialScreenPlay", "part7_5", movingCreature)
end

function TutorialScreenPlay:part7_5(movingCreature)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)

	player:sendSystemMessage("@newbie_tutorial/system_messages:stat_open")
	player:playMusicMessage("sound/tut_00_stat_open.snd")
	
	createEvent(30000, "TutorialScreenPlay", "part7_6", movingCreature)
end

function TutorialScreenPlay:part7_6(movingCreature)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)

	player:sendSystemMessage("@newbie_tutorial/system_messages:visit_commerce_room")
	player:playMusicMessage("sound/tut_27_proceed.snd")
end

function TutorialScreenPlay:travelTerminalUse(travelTerminal, playerObject, selectedID)

	if selectedID ~= 20 then
		return 0
	end
	
	local player = LuaCreatureObject(playerObject)
	
	officer6flag = readData(player:getObjectID() .. ":tutorial:officer6flag")

	if (officer6flag == 1) then
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
	player:playMusicMessage("sound/tut_00_mission_terminal.snd")
	
	createEvent(8000, "TutorialScreenPlay", "part8_2", playerObject)
	return 1
end

function TutorialScreenPlay:part8_2(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_54")
	player:playMusicMessage("sound/tut_54_npcmission.snd")	

	--officer speaks
	rawOfficer = readData(player:getObjectID() .. ":tutorial:officer5")
	local officer = getSceneObject(rawOfficer)		
	spatialChat(officer, "@newbie_tutorial/newbie_convo:mission_hail")
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
			--part nine
			player:sendSystemMessage("@newbie_tutorial/system_messages:part_8")
			
			createEvent(1000, "TutorialScreenPlay", "part8_1", movingCreature)
		
			return 1
		else
			return 0
		end
	end
end

function TutorialScreenPlay:part8_1(movingCreature)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)

	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_53")
	player:playMusicMessage("sound/tut_53_missions.snd")
end

function TutorialScreenPlay:stopOfficer5(playerObject)
	local player = LuaCreatureObject(playerObject)
	
	local off4 = LuaCreatureObject(getCreatureObject(readData(player:getObjectID() .. ":tutorial:officer5")))
	
	off4:doAnimation("point_right")
	-- found in data_animation_00.tre/appearance/animation as all_b_emt_point_right.ans
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_56")
	player:playMusicMessage("sound/tut_56_quartermaster.snd")
end

function TutorialScreenPlay:officer6(creatureObject, movingCreature)
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
	player:playMusicMessage("sound/tut_57_quartermaster.snd")
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

--animation tests
--[[function TutorialScreenPlay:animTest(creatureObject, movingCreature)
	local officer = LuaSceneObject(creatureObject)
	local movedObject = LuaSceneObject(movingCreature)
	
	if movedObject:isCreatureObject() == false then
		return 0
	end
	
	local player = LuaCreatureObject(movingCreature)
	
	distance = officer:getDistanceTo(movingCreature)
	
	if officer:isCreatureObject() == false then
		return 0
	end
	
	local officerCreature = LuaCreatureObject(creatureObject)
	
	if distance == 0 then
		return 0
	end
	
	if distance < 5 then
		
		
		
		officerCreature:doAnimation("force_choke")
		
		return 1
	else
		return 0
	end
end]]