TutorialScreenPlay = ScreenPlay:new {
	numberOfActs = 1
}

function TutorialScreenPlay:spawnObjects(creatureObject)
	local creature = LuaSceneObject(creatureObject)
	local targetCellObject = LuaSceneObject(creature:getParent())
	local buildingObject = LuaBuildingObject(targetCellObject:getParent())
	local spawndCreatureObject = LuaSceneObject(nil)
	
	if buildingObject:getServerObjectCRC() ~= 3369536646 then
		return 0
	end
	 
	targetCellObject:_setObject(buildingObject:getCell(1))

	spawnedPointer = spawnMobile("tutorial", "imperial_officer_tutorial_1", 26.7, 0, -31.9, targetCellObject:getObjectID())
	
	createObserver(17, "TutorialScreenPlay", "officer1", spawnedPointer) --move observer
	
	spawndCreatureObject:_setObject(spawnedPointer)
	
	writeData(creature:getObjectID() .. ":tutorial:officer1", spawndCreatureObject:getObjectID())
	
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
		createEvent(5000, "TutorialScreenPlay", "itemRoomCheck", creatureObject)
	else
		creature:sendSystemMessage("youre in the room retard")
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
		player:sendNewbieTutorialRequest("changeLookAtTarget")
		player:sendSystemMessage("@newbie_tutorial/system_messages:part_2")
		
		createEvent(1000, "TutorialScreenPlay", "part2Start", movingCreature)
		createObserver(18, "TutorialScreenPlay", "officerTargetEvent", movingCreature)
	
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
	
	if tostring(officer:getObjectID()) == officer1ObjectID then
		--printf("equal IDS\n")
		
		player:sendSystemMessage("@newbie_tutorial/system_messages:tut_09")
		player:playMusicMessage("sound/tut_09_lookat.snd")
		
		createEvent(5000, "TutorialScreenPlay", "tutorial10", creatureObject)
		
		return 1
	else
		--printf("not equal IDS\n")
		
		player:sendSystemMessage("@newbie_tutorial/newbie_convo:explain_lookat")
		return 0
	end
	
end 

function TutorialScreenPlay:part2Start(creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
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
