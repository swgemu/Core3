local ObjectManager = require("managers.object.object_manager")

RaceTrack = {}

-- for creation of new instances
function RaceTrack:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

local RaceTrackManager = RaceTrack:new {}


function RaceTrackManager:createRaceTrack(trackConfig)
	for lc = 1, table.getn(trackConfig.waypoints) -1 , 1 do
		RaceTrackManager:spawnActiveArea(trackConfig.planetName,trackConfig.waypoints[lc],trackConfig.waypointRadius,lc,false)
	end
	RaceTrackManager:spawnActiveArea(trackConfig.planetName,trackConfig.waypoints[table.getn(trackConfig.waypoints)],radius,table.getn(trackConfig.waypoints),true)
end

function RaceTrackManager:spawnActiveArea(planetName,waypoint,radius,index,final)
	local pWaypointAA = spawnSceneObject(planetName, "object/active_area.iff", waypoint.x, 0, waypoint.y, 0, 0, 0, 0, 0)
	if (pWaypointAA ~= nil) then
		local activeArea = LuaActiveArea(pWaypointAA)
		activeArea:setRadius(radius)
		if final == false then
			createObserver(ENTEREDAREA, "RaceTrackManager", "enteredWaypoint" .. index, pWaypointAA)
			printf("WPs : enteredWaypoint" .. index)
		else 
			createObserver(ENTEREDAREA, "RaceTrackManager", "finalWaypoint", pWaypointAA)
			printf("WPs : finalWaypoint x=" .. waypoint.x .. " y=" .. waypoint.y)
		end

	end
end
function RaceTrackManager:saveVariablesToScreenPlay(pObject,trackConfig)
	clearScreenPlayData(pObject,trackConfig.trackName)
	writeScreenPlayData(pObject, "trackName", "current", trackConfig.trackName)
	for lc = 1, table.getn(trackConfig.waypoints) , 1 do
		writeScreenPlayData(pObject, trackConfig.trackName, "WP"..lc..".X", trackConfig.waypoints[lc].x)
		writeScreenPlayData(pObject, trackConfig.trackName, "WP"..lc..".Y", trackConfig.waypoints[lc].y)
	end
	writeScreenPlayData(pObject, trackConfig.trackName, "badgeToAward", trackConfig.badgeToAward)
	writeScreenPlayData(pObject, trackConfig.trackName, "trackCheckpoint", trackConfig.trackCheckpoint)
	writeScreenPlayData(pObject, trackConfig.trackName, "trackLaptime", trackConfig.trackLaptime)
	writeScreenPlayData(pObject, trackConfig.trackName, "planetName", trackConfig.planetName)
	writeScreenPlayData(pObject, trackConfig.trackName, "numberofwaypoints", table.getn(trackConfig.waypoints))
end
function RaceTrackManager:loadVariablesFromScreenPlay(pObject)
	local trackConfig = {
		planetName ="",
		waypoints = {},
		trackName ="",
		badgeToAward=0,
		trackCheckpoint="",
		trackLaptime="",
		numOfWPs=0}
	trackConfig.trackName =  readScreenPlayData(pObject, "trackName", "current")
	trackConfig.badgeToAward =  readScreenPlayData(pObject, trackConfig.trackName, "badgeToAward")
	trackConfig.trackCheckpoint =  readScreenPlayData(pObject, trackConfig.trackName, "trackCheckpoint")
	trackConfig.trackLaptime =  readScreenPlayData(pObject, trackConfig.trackName, "trackLaptime")
	trackConfig.planetName =  readScreenPlayData(pObject, trackConfig.trackName, "planetName")
	trackConfig.numOfWPs =  tonumber(readScreenPlayData(pObject, trackConfig.trackName, "numberofwaypoints"))
	for lc = 1, trackConfig.numOfWPs, 1 do
		table.insert(trackConfig.waypoints,{x=tonumber(readScreenPlayData(pObject, trackConfig.trackName,"WP"..lc..".X")),y=tonumber(readScreenPlayData(pObject, trackConfig.trackName, "WP"..lc..".Y"))})
		printf("Loading : X=" .. tonumber(readScreenPlayData(pObject, trackConfig.trackName,"WP"..lc..".X")))
	end
	return trackConfig
end
function RaceTrackManager:spawnFirstWaypoint(pObject)
  ObjectManager.withCreatureAndPlayerObject(pObject, function(creatureObject, playerObject)
  		printf("about to load")
  		local trackConfig = RaceTrackManager:loadVariablesFromScreenPlay(pObject)
		printf("ToT sp:" .. table.getn(trackConfig.waypoints))
		printf("WP" .. trackConfig.waypoints[1].x)
		local waypointID = playerObject:addWaypoint(trackConfig.planetName,trackConfig.trackCheckpoint .. "0",trackConfig.trackCheckpoint .. "0",trackConfig.waypoints[1].x,trackConfig.waypoints[1].y,WAYPOINTWHITE,true,true)
		local time = os.time()
		writeScreenPlayData(pObject, trackConfig.trackName, "starttime", time)
		writeScreenPlayData(pObject, trackConfig.trackName, "waypointID", waypointID)
		writeScreenPlayData(pObject, trackConfig.trackName, "waypoint", 1)
		creatureObject:sendSystemMessage("@theme_park/racing/racing:go_fly")
   end)
end
function RaceTrackManager:processWaypoint(pObject,index)
	ObjectManager.withCreatureObject(pObject, function(creatureObject)
	  ObjectManager.withCreaturePlayerObject(pObject, function(playerObject)
	   printf("PW about to load")
	    local trackConfig = RaceTrackManager:loadVariablesFromScreenPlay(pObject)
	    printf("PW  loaded")
		local lastIndex =  readScreenPlayData(pObject, trackConfig.trackName, "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==tonumber(index) then
				local lastWaypointID =  readScreenPlayData(pObject, trackConfig.trackName, "waypointID")
				if lastWaypointID=="" then
					return nil -- Somethings gone wrong
				end 
				printf("lastWaypointID :" .. lastIndex)
				playerObject:removeWaypoint(tonumber(lastWaypointID),true)
				local waypointID = playerObject:addWaypoint(trackConfig.planetName,trackConfig.trackCheckpoint .. index,trackConfig.trackCheckpoint .. index,trackConfig.waypoints[index+1].x,trackConfig.waypoints[index+1].y,WAYPOINTWHITE,true,true)
				local startTime = readScreenPlayData(pObject, trackConfig.trackName, "starttime")
				local seconds = os.difftime(os.time(), startTime)
				creatureObject:sendSystemMessage(trackConfig.trackLaptime .. index)
				creatureObject:sendSystemMessage("Time " .. seconds .. "s")
				writeScreenPlayData(pObject, trackConfig.trackName, "waypointID", waypointID)
				printf("writing WP IDX :"..(index+1))
				writeScreenPlayData(pObject,trackConfig.trackName, "waypoint", index+1)
			end
		end
	  end)
	end)
end

function RaceTrackManager:enteredWaypoint1(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint2(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,2)
	end)
end
function RaceTrackManager:enteredWaypoint3(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,3)
	end)
end
function RaceTrackManager:enteredWaypoint4(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,4)
	end)
end
function RaceTrackManager:enteredWaypoint5(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,5)
	end)
end
function RaceTrackManager:enteredWaypoint6(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,6)
	end)
end
function RaceTrackManager:enteredWaypoint7(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,7)
	end)
end
function RaceTrackManager:enteredWaypoint8(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,8)
	end)
end
function RaceTrackManager:enteredWaypoint9(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,9)
	end)
end
function RaceTrackManager:enteredWaypoint10(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,10)
	end)
end
function RaceTrackManager:enteredWaypoint11(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,11)
	end)
end
function RaceTrackManager:enteredWaypoint12(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,12)
	end)
end
function RaceTrackManager:enteredWaypoint13(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,13)
	end)
end
function RaceTrackManager:enteredWaypoint14(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,14)
	end)
end
function RaceTrackManager:enteredWaypoint15(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,15)
	end)
end
function RaceTrackManager:enteredWaypoint16(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,16)
	end)
end
function RaceTrackManager:enteredWaypoint17(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,17)
	end)
end

function RaceTrackManager:finalWaypoint(pActiveArea, pObject)
	printf("ok -FWP")
	ObjectManager.withCreatureObject(pObject, function(creatureObject)
  	  ObjectManager.withCreaturePlayerObject(pObject, function(playerObject)
	   	local trackConfig = RaceTrackManager:loadVariablesFromScreenPlay(pObject)
		local lastIndex =  readScreenPlayData(pObject, trackConfig.trackName, "waypoint")
		printf("lastWaypointID :" .. lastIndex .. "hmm " .. trackConfig.numOfWPs )
		if lastIndex ~= "" then
			if tonumber(lastIndex)==trackConfig.numOfWPs then
				local startTime = readScreenPlayData(pObject, trackConfig.trackName, "starttime")
				local seconds = os.difftime(os.time(), startTime)
				local lastWaypointID =  readScreenPlayData(pObject, trackConfig.trackName, "waypointID")
				if lastWaypointID~="" then
					playerObject:removeWaypoint(tonumber(lastWaypointID),true)
				end 				
				creatureObject:sendSystemMessage("@theme_park/racing/racing:finish_message")
				creatureObject:sendSystemMessage("Time " .. seconds .. "s")	
				local personalTime = tonumber(readScreenPlayData(pObject, trackConfig.trackName ..".STATS", "RecordTime"))
				if personalTime == nil then
					personalTime = 99999999
				end
				if personalTime > seconds then
					writeScreenPlayData(pObject, trackConfig.trackName ..".STATS", "PersonalRecordTime",seconds )
					creatureObject:sendSystemMessage("@theme_park/racing/racing:new_record")
				end
				local recordTime = readSharedMemory(trackConfig.trackName ..".recordtime")
				if recordTime == 0 then
					recordTime = 99999999
				end 
				
				if recordTime > seconds then
					creatureObject:sendSystemMessage("@theme_park/racing/racing:beat_the_record")
					writeSharedMemory(trackConfig.trackName ..".recordtime",seconds)
					local playername = creatureObject:getFirstName()
					if playername ~= nil then
						writeStringSharedMemory(trackConfig.trackName ..".recordholder",playername)
					end
					if playerObject:hasBadge(trackConfig.badge) == false then
						playerObject:awardBadge(trackConfig.badge)
					end
				end 
				clearScreenPlayData(pObject,trackConfig.trackName )
				clearScreenPlayData(pObject,"trackName")
			end
		end
	  end)
	end)
end
function RaceTrackManager:displayPersonalBestTime(pObject,trackConfig)
	ObjectManager.withCreatureObject(pObject, function(creatureObject)
		local personalTime = tonumber(readScreenPlayData(pObject, trackConfig.trackName ..".STATS", "PersonalRecordTime"))
		creatureObject:sendSystemMessage("@theme_park/racing/racing:whats_my_time")
		if personalTime == nil then
			creatureObject:sendSystemMessage("No Time Set!")
		else
			creatureObject:sendSystemMessage("Time " .. personalTime .. "s")
		end 	
	end)
end

function RaceTrackManager:displayTrackBestTime(pObject,trackConfig)
	ObjectManager.withCreatureObject(pObject, function(creatureObject)
		local recordTime = tonumber(readSharedMemory(trackConfig.trackName ..".recordtime"))
		creatureObject:sendSystemMessage("@theme_park/racing/racing:current_record_holder")
		if recordTime == 0 then
			creatureObject:sendSystemMessage("No Time Set!")
		else
			creatureObject:sendSystemMessage(readStringSharedMemory(trackConfig.trackName ..".recordtime") .. " with a time of " .. recordTime .. "s")
		end 		
	end)
end

return RaceTrackManager