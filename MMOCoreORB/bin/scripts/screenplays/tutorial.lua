TutorialScreenPlay = ScreenPlay:new {
	numberOfActs = 1
}

function TutorialScreenPlay:spawnObjects(creatureObject)
	local creature = LuaSceneObject(creatureObject)
	local targetCellObject = LuaSceneObject(creature:getParent())
	local buildingObject = LuaBuildingObject(targetCellObject:getParent())
	local spawnedSceneObject = LuaSceneObject(nil)
	
	if buildingObject:getServerObjectCRC() ~= 3369536646 then
		return 0
	end
	 
	targetCellObject:_setObject(buildingObject:getCell(1))

	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_1", 26.7, 0, -31.9, targetCellObject:getObjectID())
	
	createObserver(17, "TutorialScreenPlay", "officer1", spawnedPointer) --move observer
	
	spawnedSceneObject:_setObject(spawnedPointer)
	
	writeData(creature:getObjectID() .. ":tutorial:officer1", spawnedSceneObject:getObjectID())
	
	--drum
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/container/drum/tatt_drum_1.iff", 19, 0, -23, targetCellObject:getObjectID(), 0.71, 0, -0.71, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	
	writeData(creature:getObjectID() .. ":tutorial:drum", spawnedSceneObject:getObjectID())
	--lets move all the objects from inventory there
	inventory = creature:getSlottedObject("inventory")
	
	local inventoryObj = LuaSceneObject(inventory)
	
	while (inventoryObj:getContainerObjectsSize() > 0) do
		local item = inventoryObj:getContainerObject(0)
		local itemObj = LuaSceneObject(item)
		
		--check if its maroj melon, register use now
		
		if itemObj:getGameObjectType() == 8202 then -- food
			createObserver(25, "TutorialScreenPlay", "foodUsed", item)
		end 
		
		inventoryObj:removeObject(item, 1)
		spawnedSceneObject:addObject(item, -1, 1)
	end
	
	targetCellObject:_setObject(buildingObject:getCell(2))
	
	--spawn second officer banker
	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_2", 44, 0, 2, targetCellObject:getObjectID())
	--create observer to catch when the player stops talking
	createObserver(21, "TutorialScreenPlay", "bankerStopConversation", spawnedPointer)
	
	--spawn bank
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_bank.iff", 50.8, -0.5, -3.5, targetCellObject:getObjectID(), 0.71, 0, -0.71, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	
	writeData(creature:getObjectID() .. ":tutorial:bank", spawnedSceneObject:getObjectID())
	-- create use observer
	createObserver(25, "TutorialScreenPlay", "bankUseObserver", spawnedPointer)
	
	--spawn bazaar
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_bazaar.iff", 38.4, 0, -17.7, targetCellObject:getObjectID(), 0.97, 0, 0.241, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	createObserver(25, "TutorialScreenPlay", "bazaarUseObserver", spawnedPointer)
	
	writeData(creature:getObjectID() .. ":tutorial:bazaar", spawnedSceneObject:getObjectID())
	
	
	--spawn q-3p0
	targetCellObject:_setObject(buildingObject:getCell(4))
	spawnedPointer = spawnMobile("tutorial", "protocol_droid_3po_silver", 11.9, -7, -56.4, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	createObserver(21, "TutorialScreenPlay", "cloningDroidStopConversation", spawnedPointer)
	writeData(creature:getObjectID() .. ":tutorial:protocol", spawnedSceneObject:getObjectID())
	
	--spawn clone terminal
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_cloning.iff", 3, -7, -56.5, targetCellObject:getObjectID(), 0.707, 0, 0.707, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	
	createObserver(25, "TutorialScreenPlay", "cloningUseObserver", spawnedPointer)
	
	writeData(creature:getObjectID() .. ":tutorial:clone", spawnedSceneObject:getObjectID())
	
	--spawn insurance terminal
	
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_insurance.iff", 8.4, -7, -64, targetCellObject:getObjectID(), 1, 0, 0, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	
	createObserver(25, "TutorialScreenPlay", "insuranceUseObserver", spawnedPointer)
	
	writeData(creature:getObjectID() .. ":tutorial:insurance", spawnedSceneObject:getObjectID())
	
	--spawn npc panic 1
	--targetCellObject:_setObject(buildingObject:getCell(5))
	spawnedPointer = spawnMobile("tutorial", "panic_npc_1", -3.3, -7, -75.6, targetCellObject:getObjectID())
	spawnedSceneObject:_setObject(spawnedPointer)
	
	createObserver(17, "TutorialScreenPlay", "panic1MoveObserver", spawnedPointer) --move observer
	
	
	--spawn officer3
	targetCellObject:_setObject(buildingObject:getCell(6))
	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_3", 38.1, -7, -79.7, targetCellObject:getObjectID())
	--create observer to catch when the player stops talking
	createObserver(21, "TutorialScreenPlay", "officer3StopConversation", spawnedPointer)
	--createObserver(20, "TutorialScreenPlay", "officer3SelectConversation", spawnedPointer) -- select convo observer
	createObserver(17, "TutorialScreenPlay", "converseWithOfficer3Observer", spawnedPointer) --move observer
	
	--spawn debris
	targetCellObject:_setObject(buildingObject:getCell(13))
	
	spawnedPointer = spawnSceneObject("tutorial", "object/tangible/newbie_tutorial/debris.iff", 76.9, -4, -94.3, targetCellObject:getObjectID(), 1, 0, 0, 0)
	createObserver(17, "TutorialScreenPlay", "nearDebrisObserver", spawnedPointer) --move observer
	createObserver(4, "TutorialScreenPlay", "debrisDestroyedObserver", spawnedPointer) --destroy observer
	
	--spawn retard to kill
	targetCellObject:_setObject(buildingObject:getCell(7))
	spawnedPointer = spawnMobile("tutorial", "bandit_tutorial_1", 38.1, -5.9, -113.4, targetCellObject:getObjectID())
	--register damage observer
	createObserver(26, "TutorialScreenPlay", "banditDamageObserver", spawnedPointer) --damage observer
	
	--
	createObserver(1, "TutorialScreenPlay", "part4StartObserver", creatureObject) --move observer
	createObserver(1, "TutorialScreenPlay", "part5StartObserver", creatureObject) --move observer
	
	return 1
end

function TutorialScreenPlay:start(creatureObject)	
	--printf("Running introduction\n")
	
	res = TutorialScreenPlay.spawnObjects(creatureObject, creatureObject)
	
	if res == 0 then
		return
	end
		
	local creature = LuaCreatureObject(creatureObject)
	
	creature:sendSystemMessage("@newbie_tutorial/system_messages:part_1")
	creature:sendNewbieTutorialEnableHudElement("all", 0)
	creature:sendNewbieTutorialEnableHudElement("buttonbar", 1)
	
	createEvent(3000, "TutorialScreenPlay", "secondMessage", creatureObject)
end


function TutorialScreenPlay:secondMessage(creatureObject)
	--printf("Runnging TutorialScreenPlay:secondMessage")
	local creature = LuaCreatureObject(creatureObject)

	creature:sendSystemMessage("@newbie_tutorial/system_messages:welcome")
	creature:playMusicMessage("sound/tut_01_welcome.snd")
	
	createEvent(5000, "TutorialScreenPlay", "secondAct", creatureObject)
end

function TutorialScreenPlay:secondAct(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	creature:sendSystemMessage("@newbie_tutorial/system_messages:movement_keyboard")
	creature:playMusicMessage("sound/tut_02_movement.snd")
	creature:sendSystemMessage("@newbie_tutorial/system_messages:movement_mouse")
	creature:sendSystemMessage("@newbie_tutorial/system_messages:lookaround")
	
	createEvent(15000, "TutorialScreenPlay", "thirdAct", creatureObject)
end

function TutorialScreenPlay:thirdAct(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	creature:sendSystemMessage("@newbie_tutorial/system_messages:mousewheel")
	creature:playMusicMessage("sound/tut_00_camera.snd")
	creature:sendNewbieTutorialRequest("zoomCamera")
	
	createObserver(14, "TutorialScreenPlay", "zoomEvent", creatureObject)
	createEvent(5000, "TutorialScreenPlay", "helpZoom", creatureObject)
end

function TutorialScreenPlay:helpZoom(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	state = creature:hasScreenPlayState(1, "tutorial")
	
	if state == 0 then
		creature:sendSystemMessage("@newbie_tutorial/system_messages:mousewheel_repeat")
		creature:playMusicMessage("sound/tut_03_camera.snd")
		createEvent(5000, "TutorialScreenPlay", "helpZoom", creatureObject)
	end
end

function TutorialScreenPlay:zoomEvent(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	creature:setScreenPlayState(1, "tutorial")
	
	--creature:sendSystemMessage("eureka retard")
	
	creature:sendNewbieTutorialEnableHudElement("chatbox", 1)
	creature:sendSystemMessage("@newbie_tutorial/system_messages:chatwindow")
	creature:playMusicMessage("sound/tut_04_chat.snd")
	creature:sendSystemMessage("@newbie_tutorial/system_messages:chatprompt")
	
	creature:sendNewbieTutorialRequest("chatbox")
	createEvent(10000, "TutorialScreenPlay", "helpChat", creatureObject)
	createObserver(15, "TutorialScreenPlay", "chatEvent", creatureObject)
	
	return 1 -- 1 to remove observer from observable
end

function TutorialScreenPlay:chatEvent(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	creature:setScreenPlayState(2, "tutorial")
	--creature:sendNewbieTutorialEnableHudElement("chatbox", 1)
		
	creature:sendOpenHolocronToPageMessage()
	createObserver(16, "TutorialScreenPlay", "holocronEvent", creatureObject)
	creature:sendNewbieTutorialRequest("closeHolocron")
	
	creature:sendSystemMessage("@newbie_tutorial/system_messages:holocube")
	creature:playMusicMessage("sound/tut_00_holocron.snd")

	return 1
end

function TutorialScreenPlay:helpChat(creatureObject)
	local creature = LuaCreatureObject(creatureObject)

	state = creature:hasScreenPlayState(2, "tutorial")
	
	if state == 0 then
		creature:sendSystemMessage("@newbie_tutorial/system_messages:repeatchatprompt")
		creature:playMusicMessage("sound/tut_05_remind_chat.snd")
		createEvent(5000, "TutorialScreenPlay", "helpChat", creatureObject)
	end
end

function TutorialScreenPlay:holocronEvent(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	creature:sendSystemMessage("@newbie_tutorial/system_messages:move_to_item_room")
	creature:playMusicMessage("sound/tut_06_excellent.snd")
	createEvent(5000, "TutorialScreenPlay", "itemRoomCheck", creatureObject)
	
	return 1
end

function TutorialScreenPlay:itemRoomCheck(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	cellNumber = creature:getInCellNumber()
	
	if cellNumber ~= 2 then
		creature:sendSystemMessage("@newbie_tutorial/system_messages:repeat_item_room_prompt")
		creature:playMusicMessage("sound/tut_07_comeon.snd")
		createEvent(7000, "TutorialScreenPlay", "itemRoomCheck", creatureObject)
	else
		creature:sendNewbieTutorialRequest("changeLookAtTarget")
		creature:sendSystemMessage("@newbie_tutorial/system_messages:part_2")
		
		createEvent(1000, "TutorialScreenPlay", "part2Start", creatureObject)
		createObserver(18, "TutorialScreenPlay", "officerTargetEvent", creatureObject)
	end
end

function TutorialScreenPlay:officer1(creatureObject, movingCreature)
	--printf("officer1 fired\n")
	
	local officer = LuaSceneObject(creatureObject)
	local player = LuaCreatureObject(movingCreature)
	
	distance = officer:getDistanceTo(movingCreature)
	
	--printf("distance: " .. distance)
	
	if officer:getParentID() ~= player:getParentID() then
		return 0
	end
	
	if distance > 20 then
		state = player:hasScreenPlayState(8, "tutorial")
		
		if state ~= 1 then
			player:setScreenPlayState(8, "tutorial")
			
			spatialChat(creatureObject, "@newbie_tutorial/newbie_convo:greeter1_bark1")
		end
		
		return 0
	elseif distance > 16 then
		state = player:hasScreenPlayState(16, "tutorial")
	
		if state ~= 1 then
			player:setScreenPlayState(16, "tutorial")
			
			spatialChat(creatureObject, "@newbie_tutorial/newbie_convo:greeter1_bark2")
		end
				
		return 0
	elseif distance > 12 then
		state = player:hasScreenPlayState(32, "tutorial")
	
		if state ~= 1 then
			player:setScreenPlayState(32, "tutorial")
			
			spatialChat(creatureObject, "@newbie_tutorial/newbie_convo:greeter1_bark3")
		end
		
		return 0
	else		
		return 1
	end
	
end

function TutorialScreenPlay:officerTargetEvent(creatureObject, targetCreature)
	local player = LuaCreatureObject(creatureObject)
	local officer = LuaCreatureObject(targetCreature)
	
	--printf("officerTargetEvent\n")
	
	officer1ObjectID = readData(player:getObjectID() .. ":tutorial:officer1")
	
	--printf("officer1ObjectID:" .. officer1ObjectID .. "\n")
	--printf("officer:getObjectID():" .. officer:getObjectID() .. "\n")
	
	if officer:getObjectID() == officer1ObjectID then
		--printf("equal IDS\n")
		
		player:sendSystemMessage("@newbie_tutorial/system_messages:tut_09")
		player:playMusicMessage("sound/tut_09_lookat.snd")
		
		createEvent(5000, "TutorialScreenPlay", "tutorial10", creatureObject)
		createObserver(19, "TutorialScreenPlay", "officerConversation", targetCreature)
		
		return 1
	else
		--printf("not equal IDS\n")
		
		player:sendSystemMessage("@newbie_tutorial/newbie_convo:explain_lookat")
		return 0
	end
	
end 

function TutorialScreenPlay:part2Start(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	creature:sendNewbieTutorialEnableHudElement("chatbox", 1)
	creature:sendSystemMessage("@newbie_tutorial/system_messages:tut_08")
	creature:playMusicMessage("sound/tut_08_imperialofficer.snd")
end

function TutorialScreenPlay:tutorial10(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
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
	createObserver(20, "TutorialScreenPlay", "tutorial13", creatureObject)
	
	return 1
end

function TutorialScreenPlay:tutorial13(creatureObject, playerObject)
	local creature = LuaCreatureObject(playerObject)
	
	creature:sendSystemMessage("@newbie_tutorial/system_messages:tut_13")
	creature:playMusicMessage("sound/tut_13_justtype.snd")
	
	createObserver(21, "TutorialScreenPlay", "stopConversation", creatureObject)
	
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
	
	createObserver(22, "TutorialScreenPlay", "openDrumEvent", drumRawPointer)
	
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
	
	createObserver(2, "TutorialScreenPlay", "closeDrumEvent", drumObject)
	
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
	
	createEvent(5000, "TutorialScreenPlay", "openInventory2", creatureObject)
end

function TutorialScreenPlay:openInventory2(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:repeat_open_inventory")
	player:playMusicMessage("sound/tut_25_openinventory.snd")
	
	player:sendNewbieTutorialRequest("openInventory")
	createObserver(23, "TutorialScreenPlay", "openInventoryObserver", creatureObject)
end

function TutorialScreenPlay:openInventoryObserver(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:prompt_find_food")
	player:playMusicMessage("sound/tut_20_selectfooditem.snd")
	player:sendNewbieTutorialRequest("closeInventory")
	createObserver(24, "TutorialScreenPlay", "closeInventoryObserver", creatureObject)
		
	return 1
end

function TutorialScreenPlay:closeInventoryObserver(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:setScreenPlayState(256, "tutorial")
	
	return 1
end

function TutorialScreenPlay:foodUsed(foodObject, creatureObject, selectedID)
	if selectedID ~= 20 then
		return 0
	end
	
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:explain_item_used")
	player:playMusicMessage("sound/tut_22_attributes.snd")
	
	createEvent(10000, "TutorialScreenPlay", "activateToolbar", creatureObject)
	
	return 1
end

function TutorialScreenPlay:activateToolbar(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendNewbieTutorialEnableHudElement("toolbar", 1)
	player:sendSystemMessage("@newbie_tutorial/system_messages:show_toolbar")
	player:playMusicMessage("sound/tut_23_toolbar.snd")

	createEvent(8000, "TutorialScreenPlay", "explainToolbar", creatureObject)
end

function TutorialScreenPlay:explainToolbar(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_00_toolbardrag")
	player:playMusicMessage("sound/tut_00_toolbardrag.snd")

	createEvent(5000, "TutorialScreenPlay", "checkInventoryClosed", creatureObject)
end

function TutorialScreenPlay:checkInventoryClosed(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	state = player:hasScreenPlayState(256, "tutorial") -- closed inventory state
	
	if state == 0 then
		player:sendSystemMessage("@newbie_tutorial/system_messages:close_inventory")
		player:playMusicMessage("sound/tut_26_closeinventory.snd")
		
		player:sendNewbieTutorialRequest("closeInventory")
		createEvent(5000, "TutorialScreenPlay", "checkInventoryClosed", creatureObject)
		
		return
	end
		
	player:sendNewbieTutorialEnableHudElement("toolbar", 1)
	player:sendNewbieTutorialEnableHudElement("chatbox", 1)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:visit_commerce_room")
	player:playMusicMessage("sound/tut_27_proceed.snd")
	
	createEvent(3000, "TutorialScreenPlay", "checkCommerceRoom", creatureObject) 
end

function TutorialScreenPlay:checkCommerceRoom(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	if player:getInCellNumber() ~= 3 then
		player:sendSystemMessage("@newbie_tutorial/system_messages:visit_commerce_room")
		player:playMusicMessage("sound/tut_27_proceed.snd")
	
		createEvent(3000, "TutorialScreenPlay", "checkCommerceRoom", creatureObject)
		
		return
	end
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:part_3")
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_28")
	player:playMusicMessage("sound/tut_28_converse.snd")
	
	--register move observer to check if we skipped this part
end

function TutorialScreenPlay:bankerStopConversation(creatureObject, playerObject)
	local player = LuaCreatureObject(playerObject)
	
	createEvent(1000, "TutorialScreenPlay", "activateBankUseCheck", playerObject)
	createEvent(1000, "TutorialScreenPlay", "activateBazaarUseCheck", playerObject)
	return 1
end

function TutorialScreenPlay:activateBankUseCheck(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	bankObjectID = readData(player:getObjectID() .. ":tutorial:bank")
	local bankObject = LuaSceneObject(getSceneObject(bankObjectID))
	
	bankObject:showFlyText("newbie_tutorial/system_messages", "bank_flytext", 0, 255, 0)
	
	state = player:hasScreenPlayState(1024, "tutorial")
	
	if state == 0 then
		createEvent(2000, "TutorialScreenPlay", "activateBankUseCheck", creatureObject)
		createObserver(18, "TutorialScreenPlay", "activateBankTargetCheck", creatureObject)
		return
	end

end

function TutorialScreenPlay:activateBazaarUseCheck(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	bazaarObjectID = readData(player:getObjectID() .. ":tutorial:bazaar")
	local bazaarObject = LuaSceneObject(getSceneObject(bazaarObjectID))
	
	bazaarObject:showFlyText("newbie_tutorial/system_messages", "bazaar_flytext", 0, 255, 0)
	
	state = player:hasScreenPlayState(4096, "tutorial")
	
	if state == 0 then
		createEvent(2000, "TutorialScreenPlay", "activateBazaarUseCheck", creatureObject)
		createObserver(18, "TutorialScreenPlay", "activateBazaarTargetCheck", creatureObject)
		return
	end

end

function TutorialScreenPlay:activateBazaarTargetCheck(creatureObject, targetObject)
	local player = LuaCreatureObject(creatureObject)
	local target = LuaSceneObject(targetObject)
	
	bazaarObjectID = readData(player:getObjectID() .. ":tutorial:bazaar")
	
	state = player:hasScreenPlayState(4096, "tutorial")
	state2 = player:hasScreenPlayState(8192, "tutorial")
	
	if state == 1 or state2 == 1 then
		return 1
	end
	
	if bazaarObjectID == target:getObjectID() then
		player:setScreenPlayState(8192, "tutorial")
		player:sendSystemMessage("@newbie_tutorial/system_messages:bazaar_info_1")
		player:playMusicMessage("sound/tut_29_itemdispenser.snd")
		
		createEvent(6000, "TutorialScreenPlay", "displayBazaarInfo", creatureObject)
		
		return 1
	else
		if state == 0 then
			return 0
		end
	end

	return 1
end

function TutorialScreenPlay:activateBankTargetCheck(creatureObject, targetObject)
	local player = LuaCreatureObject(creatureObject)
	local target = LuaSceneObject(targetObject)
	
	bankObjectID = readData(player:getObjectID() .. ":tutorial:bank")
	
	state = player:hasScreenPlayState(1024, "tutorial")
	state2 = player:hasScreenPlayState(2048, "tutorial")
	
	if state == 1 or state2 == 1 then
		return 1
	end
	
	if bankObjectID == target:getObjectID() then
		player:setScreenPlayState(2048, "tutorial")
		player:sendSystemMessage("@newbie_tutorial/system_messages:bank_info_1")
		player:playMusicMessage("sound/tut_32_bank.snd")
		
		createEvent(6000, "TutorialScreenPlay", "displayBankInfo", creatureObject)
		
		return 1
	else
		if state == 0 then
			return 0
		end
	end

	return 1
end

function TutorialScreenPlay:displayBazaarInfo(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:playMusicMessage("sound/tut_00_bazaar_tease.snd")
	player:sendSystemMessage("@newbie_tutorial/system_messages:bazaar_info_2")
	createEvent(7000, "TutorialScreenPlay", "displayBazaarInfo2", creatureObject)
end

function TutorialScreenPlay:displayBazaarInfo2(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:bazaar_info_3")
end

function TutorialScreenPlay:displayBankInfo(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:bank_info_2")
	createEvent(7000, "TutorialScreenPlay", "displayBankInfo3", creatureObject)
end

function TutorialScreenPlay:displayBankInfo3(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:bank_info_3")
	createEvent(7000, "TutorialScreenPlay", "displayBankInfo4", creatureObject)
end

function TutorialScreenPlay:displayBankInfo4(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:bank_info_4")
	--createEvent(7000, "TutorialScreenPlay", "displayBankInfo", creatureObject)
	
	--player:sendSystemMessage("and this is how it ends")
end

function TutorialScreenPlay:bankUseObserver(bankObject, playerObject, selectedID)
	if selectedID ~= 20 then
		return 0
	end
	
	local player = LuaCreatureObject(playerObject)
	
	player:setScreenPlayState(1024, "tutorial")
	
	state = player:hasScreenPlayState(4096, "tutorial")
	
	if state == 1 then
		player:sendSystemMessage("@newbie_tutorial/system_messages:tut_36")
	end
	return 1
end

function TutorialScreenPlay:bazaarUseObserver(bankObject, playerObject, selectedID)
	if selectedID ~= 45 then
		return 0
	end
	
	local player = LuaCreatureObject(playerObject)
	
	player:setScreenPlayState(4096, "tutorial")
	
	state = player:hasScreenPlayState(1024, "tutorial")
	
	if state == 1 then
		player:sendSystemMessage("@newbie_tutorial/system_messages:tut_36")
	end
	
	return 1
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
			
			spatialChat(droidPointer, "@newbie_tutorial/newbie_convo:greeter1_bark2")
			
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

function TutorialScreenPlay:panic1MoveObserver(creatureObject, movingCreature)
	local officer = LuaSceneObject(creatureObject)
	local player = LuaCreatureObject(movingCreature)
	
	distance = officer:getDistanceTo(movingCreature)
	
	if distance == 0 then
		return 0
	end
	
	if distance < 8 then
		spatialChat(creatureObject, "@newbie_tutorial/newbie_convo:shout_panic1")
		
		player:sendSystemMessage("@newbie_tutorial/system_messages:radar")
		player:playMusicMessage("sound/tut_41_advancewarning.snd")
		player:sendNewbieTutorialEnableHudElement("radar", 1)
		spatialChat(creatureObject, "@newbie_tutorial/newbie_convo:shout_panic2")
		
		return 1
	else
		return 0
	end
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
			
			--createObserver(1, "TutorialScreenPlay", "officer3Start", creatureObject) --move observer
			
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

function TutorialScreenPlay:officer3StopConversation(creatureObject, playerObject)
	local player = LuaCreatureObject(playerObject)
		
	
	return 1
end

function TutorialScreenPlay:officer3SelectConversation(creatureObject, playerObject, selectedOption)
	return 1
end

function TutorialScreenPlay:nearDebrisObserver(debrisObject, movingCreature)
	local debris = LuaSceneObject(debrisObject)
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
	--player:sendSystemMessage("good job retard")
	
	debris:removeFromZone()
	
	player:clearCombatState(1)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:explain_combat_1")
	player:playMusicMessage("sound/tut_47_defaultattack.snd")
	
	createEvent(8000, "TutorialScreenPlay", "explainCombat", playerObject)
	
	return 1
end

function TutorialScreenPlay:explainCombat(creatureObject)
	local player = LuaCreatureObject(creatureObject)
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:explain_combat_2")
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:part_6")
	
	player:sendSystemMessage("@newbie_tutorial/system_messages:tut_44_attacking")
	player:playMusicMessage("sound/tut_44_attacking.snd")
end

function TutorialScreenPlay:banditDamageObserver(banditObject, playerObject, damage)
	local player = LuaCreatureObject(playerObject)
	local bandit = LuaCreatureObject(banditObject)
	
	health = bandit:getHAM(0)
	action = bandit:getHAM(1)
	mind = bandit:getHAM(2)
	
	maxHealth = bandit:getMaxHAM(0)
	maxAction = bandit:getMaxHAM(1)
	maxMind = bandit:getMaxHAM(2)
	
	if health <= (maxHealth / 2) or action <= (maxAction / 2) or mind <= (maxAction / 2) then
		spatialChat(banditObject, "@newbie_tutorial/newbie_convo:pirate_taunt3")
		spatialChat(banditObject, "@newbie_tutorial/newbie_convo:pirate_taunt4")
		
		createEvent(500, "TutorialScreenPlay", "killBandit", banditObject) 
		createEvent(2000, "TutorialScreenPlay", "lootBanditEvent", playerObject)
				
		return 1
	end
	
	return 0
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
end
