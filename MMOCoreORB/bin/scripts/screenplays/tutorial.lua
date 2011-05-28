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
	
	createEvent(2000, "TutorialScreenPlay", "openInventory2", creatureObject)
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

	createEvent(16000, "TutorialScreenPlay", "checkInventoryClosed", creatureObject)
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
end

function TutorialScreenPlay:bankerStopConversation(creatureObject, playerObject)
	local player = LuaCreatureObject(playerObject)
	
	createEvent(2000, "TutorialScreenPlay", "activateBankUseCheck", playerObject)
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
	
	player:sendSystemMessage("and this is how it ends")
end

function TutorialScreenPlay:bankUseObserver(bankObject, playerObject, selectedID)
	if selectedID ~= 20 then
		return 0
	end
	
	local player = LuaCreatureObject(playerObject)
	
	player:setScreenPlayState(1024, "tutorial")
	return 1
end

--createObserver(25, "TutorialScreenPlay", "bankUseObserver", spawnedPointer)
