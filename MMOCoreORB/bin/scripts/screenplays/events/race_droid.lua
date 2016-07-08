local ObjectManager = require("managers.object.object_manager")

raceDroidEventPerk = ScreenPlay:new {
	racePointRadius = 5
}

function raceDroidEventPerk:setRacePoint(pNpc, pointNum, x, y)
	local droidID = SceneObject(pNpc):getObjectID()
	writeData(droidID .. ":raceDroidPerk:Point" .. pointNum .. ":X", x)
	writeData(droidID .. ":raceDroidPerk:Point" .. pointNum .. ":Y", y)

	local count = readData(droidID .. ":raceDroidPerk:waypointCount")
	writeData(droidID .. ":raceDroidPerk:waypointCount", count + 1)
end

function raceDroidEventPerk:getRacePoint(pNpc, pointNum)
	local droidID = SceneObject(pNpc):getObjectID()
	local x = readData(droidID .. ":raceDroidPerk:Point" .. pointNum .. ":X")
	local y = readData(droidID .. ":raceDroidPerk:Point" .. pointNum .. ":Y")

	return { x, y }
end

function raceDroidEventPerk:getTopRecordName(pNpc)
	local topName = readStringSharedMemory(SceneObject(pNpc):getObjectID() .. ":raceDroidPerk:topRecordName")

	if (topName == "") then
		topName = "Nobody"
	end

	return topName
end

function raceDroidEventPerk:setTopRecordName(pNpc, playerName)
	writeStringSharedMemory(SceneObject(pNpc):getObjectID() .. ":raceDroidPerk:topRecordName", playerName)
end

function raceDroidEventPerk:getTopRecord(pNpc)
	return readData(SceneObject(pNpc):getObjectID() .. ":raceDroidPerk:topRecord")
end

function raceDroidEventPerk:setTopRecord(pNpc, record)
	writeData(SceneObject(pNpc):getObjectID() .. ":raceDroidPerk:topRecord", record)
end

function raceDroidEventPerk:setDroidStatus(pNpc, status)
	writeData(SceneObject(pNpc):getObjectID() .. ":raceDroidPerk:status", status)
end

function raceDroidEventPerk:getDroidStatus(pNpc)
	return readData(SceneObject(pNpc):getObjectID() .. ":raceDroidPerk:status")
end

function raceDroidEventPerk:getPerkOwner(pNpc)
	local ownerID = TangibleObject(pNpc):getLuaStringData("ownerID")

	return getSceneObject(ownerID)
end

function raceDroidEventPerk:setMaxWaypoints(pNpc, waypoints)
	writeData(SceneObject(pNpc):getObjectID() .. ":raceDroidPerk:maxWaypoints", waypoints)
end

function raceDroidEventPerk:getMaxWaypoints(pNpc)
	return readData(SceneObject(pNpc):getObjectID() .. ":raceDroidPerk:maxWaypoints")
end

function raceDroidEventPerk:getTotalWaypoints(pNpc)
	return readData(SceneObject(pNpc):getObjectID() .. ":raceDroidPerk:waypointCount")
end

function raceDroidEventPerk:sendSetupSUI(pNpc, pPlayer)
	local droidID = SceneObject(pNpc):getObjectID()
	local curStep = readData(droidID .. ":setupStep")
	writeData(droidID .. ":settingUpRace", 1)

	local sui = SuiInputBox.new("raceDroidEventPerk", "suiSetupCallback")

	sui.setTargetNetworkId(droidID)

	sui.setTitle("@event_perk:race_setup_title_" .. curStep)
	sui.setPrompt("@event_perk:race_setup_prompt_" .. curStep)

	sui.sendTo(pPlayer)
end

function raceDroidEventPerk:suiSetupCallback(pPlayer, pSui, eventIndex, args)
	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)

	local droidID = suiPageData:getTargetNetworkId()

	local pNpc = getSceneObject(droidID)

	if (pNpc == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		CreatureObject(pPlayer):sendSystemMessage("@event_perk:race_setup_canceled") -- Setup cancelled. You must complete setup before opening the game to the public.
		deleteData(droidID .. ":settingUpRace")
		return
	end

	if (args == nil or args == "") then
		CreatureObject(pPlayer):sendSystemMessage("@event_perk:race_setup_nothing_entered") -- 	Invalid data entered. Please try again or hit "Cancel" to exit setup.
		self:sendSetupSUI(pNpc, pPlayer)
		return
	end

	local curStep = readData(droidID .. ":setupStep")

	if (curStep == 0) then
		local numWaypoints = tonumber(args)

		if (numWaypoints == nil or numWaypoints < 2 or numWaypoints > 15) then
			CreatureObject(pPlayer):sendSystemMessage("@event_perk:racing_setup_waypoint_error") -- You must enter a value between 2 and 15.
			self:sendSetupSUI(pNpc, pPlayer)
			return
		end

		self:setMaxWaypoints(pNpc, numWaypoints)
		writeData(droidID .. ":setupStep", curStep + 1)
		deleteData(droidID .. ":raceDroidPerk:waypointCount")
		self:sendSetupSUI(pNpc, pPlayer)
	elseif (curStep == 1) then
		local tokenizer = self:splitString(args, " ")

		if (#tokenizer ~= 2 or tokenizer[1] == nil or tokenizer[1] == "" or tokenizer[2] == nil or tokenizer[2] == "") then
			CreatureObject(pPlayer):sendSystemMessage("@event_perk:racing_setup_coord_error") -- 	Valid ranges for waypoints are between 8000 and -8000. Enter the waypoints without commas (Example: 1200 -4553).
			self:sendSetupSUI(pNpc, pPlayer)
			return
		end

		local wayX = tonumber(tokenizer[1])
		local wayY = tonumber(tokenizer[2])

		if (wayX == nil or wayX > 8000 or wayX < -8000 or wayY == nil or wayY > 8000 or wayY < -8000) then
			CreatureObject(pPlayer):sendSystemMessage("@event_perk:racing_setup_coord_error") -- 	Valid ranges for waypoints are between 8000 and -8000. Enter the waypoints without commas (Example: 1200 -4553).
			self:sendSetupSUI(pNpc, pPlayer)
			return
		end

		CreatureObject(pPlayer):sendSystemMessage(getStringId("@event_perk:race_waypoint_is") .. " " .. tokenizer[1] .. " " .. tokenizer[2])

		local curWaypoints = self:getTotalWaypoints(pNpc) + 1
		local maxWaypoints = self:getMaxWaypoints(pNpc)

		self:setRacePoint(pNpc, curWaypoints, wayX, wayY)

		if (curWaypoints < maxWaypoints) then
			self:sendSetupSUI(pNpc, pPlayer)
			return
		else
			CreatureObject(pPlayer):sendSystemMessage("@event_perk:race_setup_complete") -- Setup complete. Choose "View Race Parameters" to review your waypoints. If correct, choose "Initialize Droid" to open the course to the public. Otherwise you may return to setup to make changes.
			deleteData(droidID .. ":settingUpRace")
		end
	end
end

function raceDroidEventPerk:startRace(pNpc, pPlayer)
	if (pNpc == nil or pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	writeData(playerID .. ":eventPerkRace:droidID", SceneObject(pNpc):getObjectID())
	writeData(playerID .. ":eventPerkRace:nextRacePoint", 1)
	writeData(playerID .. ":eventPerkRace:startTime", getTimestampMilli())
	writeData(playerID .. ":eventPerkRace:currentlyRacing", 1)

	self:createNextRacePoint(pPlayer, pNpc)
end

function raceDroidEventPerk:doCleanup(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	if (readData(playerID .. ":eventPerkRace:currentlyRacing") == 1) then
		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if pGhost ~= nil then
			local waypointID = readData(playerID .. ":eventPerkRace:nextPointWaypointID")
			PlayerObject(pGhost):removeWaypoint(waypointID, true)
		end

		local areaID = readData(playerID .. ":eventPerkRace:nextPointAreaID")
		local pArea = getSceneObject(areaID)

		if (pArea ~= nil) then
			SceneObject(pArea):destroyObjectFromWorld()
		end

		CreatureObject(pPlayer):playMusicMessage("sound/music_silence.snd")
	end

	deleteData(playerID .. ":eventPerkRace:nextPointWaypointID")
	deleteData(playerID .. ":eventPerkRace:nextPointAreaID")
	deleteData(playerID .. ":eventPerkRace:droidID")
	deleteData(playerID .. ":eventPerkRace:nextRacePoint")
	deleteData(playerID .. ":eventPerkRace:startTime")
	deleteData(playerID .. ":eventPerkRace:currentlyRacing")
end

function raceDroidEventPerk:createNextRacePoint(pPlayer, pNpc)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local nextPointNum = readData(playerID .. ":eventPerkRace:nextRacePoint")
	local maxPoints = self:getMaxWaypoints(pNpc)

	local nextPoint
	if (nextPointNum <= maxPoints) then
		nextPoint = self:getRacePoint(pNpc, nextPointNum)
	else
		nextPoint = { SceneObject(pNpc):getWorldPositionX(), SceneObject(pNpc):getWorldPositionY() }
	end

	local pointZ = getTerrainHeight(pNpc, nextPoint[1], nextPoint[2])
	local pRacePoint = spawnActiveArea(SceneObject(pPlayer):getZoneName(), "object/active_area.iff", nextPoint[1], pointZ, nextPoint[2], self.racePointRadius, 0)

	if pRacePoint == nil then
		return
	end

	local areaID = SceneObject(pRacePoint):getObjectID()
	createObserver(ENTEREDAREA, "raceDroidEventPerk", "notifyEnteredRacePoint", pRacePoint)
	writeData(areaID .. ":raceOwnerID", playerID)
	writeData(playerID .. ":eventPerkRace:nextPointAreaID", areaID)

	local waypointID = PlayerObject(pGhost):addWaypoint(SceneObject(pPlayer):getZoneName(), "@event_perk:racing_waypoint_name", "@theme_park/racing/racing:waypoint_desc_1", nextPoint[1],nextPoint[2], WAYPOINTBLUE, true, true, WAYPOINTRACETRACK, 0)
	writeData(playerID .. ":eventPerkRace:nextPointWaypointID", waypointID)

	if (nextPointNum <= maxPoints) then
		SceneObject(pPlayer):showFlyText("theme_park/racing/racing", "go_fly", 0, 0, 255)
	else
		SceneObject(pPlayer):showFlyText("theme_park/racing/racing", "final_lap_fly", 255, 0, 0)
	end

	CreatureObject(pPlayer):playMusicMessage("sound/music_combat_bfield_lp.snd")
end

function raceDroidEventPerk:notifyEnteredRacePoint(pRacePoint, pPlayer)
	local pointOwnerID = readData(SceneObject(pRacePoint):getObjectID() .. ":raceOwnerID")

	if (SceneObject(pPlayer):getObjectID() ~= pointOwnerID) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return 0
	end

	local currentPoint = readData(pointOwnerID .. ":eventPerkRace:nextRacePoint")
	local waypointID = readData(pointOwnerID .. ":eventPerkRace:nextPointWaypointID")
	PlayerObject(pGhost):removeWaypoint(waypointID, true)

	SceneObject(pRacePoint):destroyObjectFromWorld()

	local droidID = readData(pointOwnerID .. ":eventPerkRace:droidID")
	local pDroid = getSceneObject(droidID)

	if (pDroid == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Unable to locate race droid, ending race.")
		self:doCleanup(pPlayer)
		return 1
	end

	local raceStartTime = readData(pointOwnerID .. ":eventPerkRace:startTime")
	local curTime = getTimestampMilli()
	local timeDelta = curTime - raceStartTime
	local timeDeltaDisplay = timeDelta / 1000
	local maxPoints = self:getMaxWaypoints(pDroid)

	if (currentPoint == maxPoints + 1) then -- End point
		writeData(pointOwnerID .. ":eventPerkRace:currentlyRacing", 0)
		CreatureObject(pPlayer):sendSystemMessage("@event_perk:racing_finish_message")
		local messageString = LuaStringIdChatParameter("@event_perk:racing_total_time")
		messageString:setDF(timeDeltaDisplay)
		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
		self:updateRecords(pDroid, pPlayer, timeDelta)
		self:doCleanup(pPlayer)
		return 1
	end

	CreatureObject(pPlayer):sendSystemMessage("@event_perk:racing_checkpoint_message")
	local messageString = LuaStringIdChatParameter("@event_perk:racing_lap_time")
	messageString:setDF(timeDeltaDisplay)
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
	writeData(pointOwnerID .. ":eventPerkRace:nextRacePoint", currentPoint + 1)
	self:createNextRacePoint(pPlayer, pDroid)

	return 1
end

function raceDroidEventPerk:updateRecords(pNpc, pPlayer, timeDelta)
	local playerName = SceneObject(pPlayer):getDisplayedName()
	local topRecordName = self:getTopRecordName(pNpc)
	local topRecord = self:getTopRecord(pNpc)

	local messageString = LuaStringIdChatParameter("@theme_park/racing/racing:last_time")
	messageString:setTO(playerName .. " " .. (timeDelta / 1000))
	spatialChat(pNpc, messageString:_getObject())

	if (timeDelta < topRecord or topRecordName == "Nobody") then
		self:setTopRecord(pNpc, timeDelta)
		self:setTopRecordName(pNpc, playerName)

		CreatureObject(pPlayer):sendSystemMessage("@theme_park/racing/racing:beat_the_record")
		SceneObject(pPlayer):showFlyText("theme_park/racing/racing", "beat_record_fly", 173, 255, 47)
		CreatureObject(pPlayer):playMusicMessage("sound/music_combat_bfield_vict.snd")
		playClientEffectLoc(SceneObject(pPlayer):getObjectID(), "clienteffect/droid_effect_confetti.cef", SceneObject(pPlayer):getZoneName(), SceneObject(pNpc):getWorldPositionX(), SceneObject(pNpc):getWorldPositionZ(), SceneObject(pNpc):getWorldPositionY(), 0)
	elseif (timeDelta > topRecord) then
		if (topRecordName == playerName) then
			CreatureObject(pPlayer):sendSystemMessage("@theme_park/racing/racing:still_hold_record")
			CreatureObject(pPlayer):playMusicMessage("sound/music_combat_bfield_vict.snd")
		else
			CreatureObject(pPlayer):sendSystemMessage("@theme_park/racing/racing:not_good_enough")
			CreatureObject(pPlayer):playMusicMessage("sound/music_combat_bfield_death.snd")
		end
	elseif (timeDelta == topRecord) then
		if (topRecordName == playerName) then
			CreatureObject(pPlayer):sendSystemMessage("@theme_park/racing/racing:still_hold_record")
			CreatureObject(pPlayer):playMusicMessage("sound/music_combat_bfield_vict.snd")
		else
			CreatureObject(pPlayer):sendSystemMessage("@theme_park/racing/racing:tied_the_record")
			CreatureObject(pPlayer):playMusicMessage("sound/music_combat_bfield_death.snd")
		end
	end

	self:displayLeader(pNpc, pPlayer)
end

function raceDroidEventPerk:displayLeader(pNpc, pPlayer)
	local topRecordName = self:getTopRecordName(pNpc)
	local topRecord = self:getTopRecord(pNpc) / 1000
	CreatureObject(pPlayer):sendSystemMessage("@theme_park/racing/racing:current_record_holder")

	local messageString = LuaStringIdChatParameter("@event_perk:racing_leader_display")
	messageString:setTO(topRecordName)
	messageString:setDF(topRecord)
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
end

function raceDroidEventPerk:sendStoredData(pNpc, pPlayer)
	local totalWaypoints = self:getTotalWaypoints(pNpc)

	local sui = SuiListBox.new("raceDroidEventPerk", "noCallback")

	sui.setTargetNetworkId(SceneObject(pNpc):getObjectID())

	sui.setTitle("@event_perk:race_view_parameters")
	sui.setPrompt("@event_perk:race_show_status0")

	for i = 1, totalWaypoints, 1 do
		local waypoint = self:getRacePoint(pNpc, i)
		sui.add("Point " .. i .. ": " .. waypoint[1] .. ", " .. waypoint[2], "")
	end

	sui.hideCancelButton()

	sui.sendTo(pPlayer)
end

function raceDroidEventPerk:noCallback(pPlayer, pSui, eventIndex, ...)
end

function raceDroidEventPerk:doInitializeCallback(pPlayer, pSui, eventIndex, args)
	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)

	local droidID = suiPageData:getTargetNetworkId()

	local pNpc = getSceneObject(droidID)

	if (pNpc == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	self:setDroidStatus(pNpc, "1")
	SceneObject(pNpc):setObjectMenuComponent("ObjectMenuComponent")
	AiAgent(pNpc):setConvoTemplate("raceDroidConvoTemplate")
	CreatureObject(pNpc):setOptionBit(CONVERSABLE)
end

function raceDroidEventPerk:splitString(string, delimiter)
	local outResults = { }
	local start = 1
	local splitStart, splitEnd = string.find( string, delimiter, start )
	while splitStart do
		table.insert( outResults, string.sub( string, start, splitStart-1 ) )
		start = splitEnd + 1
		splitStart, splitEnd = string.find( string, delimiter, start )
	end
	table.insert( outResults, string.sub( string, start ) )
	return outResults
end

RaceDroidPerkMenuComponent = { }

function RaceDroidPerkMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	local pOwner = raceDroidEventPerk:getPerkOwner(pSceneObject)

	if (pOwner == nil or pPlayer ~= pOwner) then
		return
	end

	if (raceDroidEventPerk:getDroidStatus(pSceneObject) == 1) then
		return
	end

	menuResponse:addRadialMenuItem(120, 3, "@event_perk:race_set_parameters") -- Set Race Parameters

	local totalWaypoints = raceDroidEventPerk:getTotalWaypoints(pSceneObject)
	if (totalWaypoints > 0 and totalWaypoints == raceDroidEventPerk:getMaxWaypoints(pSceneObject)) then
		menuResponse:addRadialMenuItem(121, 3, "@event_perk:race_view_parameters") -- View Race Parameters
		menuResponse:addRadialMenuItem(122, 3, "@event_perk:race_initialize_droid") -- Initialize Droid
	end
end

function RaceDroidPerkMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or pSceneObject == nil) then
		return 0
	end

	local pOwner = raceDroidEventPerk:getPerkOwner(pSceneObject)

	if (pOwner == nil or pPlayer ~= pOwner) then
		return 0
	end

	if (selectedID ~= 120 and selectedID ~= 121 and selectedID ~= 122 and selectedID ~= 25) then
		return 0
	end

	local droidID = SceneObject(pSceneObject):getObjectID()

	if (selectedID == 120) then
		if (raceDroidEventPerk:getDroidStatus(pSceneObject) == 1) then
			return 0
		end

		if (readData(droidID .. ":settingUpRace") == 1) then
			return 0
		end

		writeData(droidID .. ":setupStep", 0)
		raceDroidEventPerk:sendSetupSUI(pSceneObject, pPlayer)
	elseif (selectedID == 121) then
		raceDroidEventPerk:sendStoredData(pSceneObject, pPlayer)
	elseif (selectedID == 122) then
		local sui = SuiMessageBox.new("raceDroidEventPerk", "doInitializeCallback")
		sui.setTitle("@event_perk:race_initialize_droid")
		sui.setPrompt("@event_perk:intialize_droid_warning")
		sui.setTargetNetworkId(SceneObject(pSceneObject):getObjectID())
		sui.setForceCloseDistance(10)
		sui.sendTo(pPlayer)
	end

	return 0
end
