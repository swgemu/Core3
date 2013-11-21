RaceTrack = {}

-- for creation of new instances
function RaceTrack:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

local ObjectManager = require("managers.object.object_manager")

local RaceTrackManager = RaceTrack:new {
	planetName ="",
	waypoints = {},
	trackName ="",
	badgeToAward=0,
	trackCheckpoint="",
	trackLaptime="",
	numOfWPs=0

}

function RaceTrackManager:spawnActiveArea(planetName,waypoint,radius,index,final)
	local pWaypointAA = spawnSceneObject(planetName, "object/active_area.iff", waypoint.x, 0, waypoint.y, 0, 0, 0, 0, 0)
	if (pWaypointAA ~= nil) then
		local activeArea = LuaActiveArea(pWaypointAA)
		activeArea:setRadius(radius)
		if final == false then
			createObserver(ENTEREDAREA, "RaceTrackManager", "enteredWaypoint" .. index, pWaypointAA)
		else 
			createObserver(ENTEREDAREA, "RaceTrackManager", "finalWaypoint", pWaypointAA)
		end

	end
end
function RaceTrackManager:loadVariablesFromScreenPlay(pObject)
	self.trackName =  readScreenPlayData(pObject, "trackName", "current")
	self.badgeToAward =  readScreenPlayData(pObject, self.trackName, "badgeToAward")
	self.trackCheckpoint =  readScreenPlayData(pObject, self.trackName, "trackCheckpoint")
	self.trackLaptime =  readScreenPlayData(pObject, self.trackName, "trackLaptime")
	self.planetName =  readScreenPlayData(pObject, self.trackName, "planetName")
	self.numOfWPs =  tonumber(readScreenPlayData(pObject, self.trackName, "numberofwaypoints"))
	for lc = 1, numOfWPs, 1 do
		table.insert(self.waypoints,{x=tonumber(readScreenPlayData(pObject, self.trackName,"WP"..lc..".X")),y=tonumber(readScreenPlayData(pObject, self.trackName, "WP"..lc..".Y"))})
	end
end
function RaceTrackManager:spawnFirstWaypoint(pObject)
  ObjectManager.withCreatureAndPlayerObject(pObject, function(creatureObject, playerObject)
  		printf("about to load")
  		RaceTrackManager:loadVariablesFromScreenPlay(pObject)
		clearScreenPlayData(pObject,self.trackName)
		printf("ToT sp:" .. table.getn(self.waypoints))
		printf("WP" .. self.waypoints[1].x)
		local waypointID = playerObject:addWaypoint(self.planetName,self.trackCheckpoint .. "0",self.trackCheckpoint .. "0",self.waypoints[1].x,self.waypoints[1].y,WAYPOINTWHITE,true,true)
		local time = os.time()
		writeScreenPlayData(pObject, self.trackName, "starttime", time)
		writeScreenPlayData(pObject, self.trackName, "waypointID", waypointID)
		writeScreenPlayData(pObject, self.trackName, "waypoint", 1)
		creatureObject:sendSystemMessage("@theme_park/racing/racing:go_fly")
   end)
end
function RaceTrackManager:processWaypoint(pObject,index)
	ObjectManager.withCreatureObject(pObject, function(creatureObject)
	  ObjectManager.withCreaturePlayerObject(pObject, function(playerObject)
	   printf("PW about to load")
	    RaceTrackManager:loadVariablesFromScreenPlay(pObject)
	    printf("PW  loaded")
		local lastIndex =  readScreenPlayData(pObject, self.trackName, "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==tonumber(index) then
				local lastWaypointID =  readScreenPlayData(pObject, self.trackName, "waypointID")
				if lastWaypointID=="" then
					return nil -- Somethings gone wrong
				end 
				printf("lastWaypointID :" .. lastWaypointID)
				playerObject:removeWaypoint(tonumber(lastWaypointID),true)
				local waypointID = playerObject:addWaypoint(self.planetName,self.trackCheckpoint .. index,self.trackCheckpoint .. index,self.waypoints[index+1].x,self.waypoints[index+1].y,WAYPOINTWHITE,true,true)
				local startTime = readScreenPlayData(pObject, self.trackName, "starttime")
				local seconds = os.difftime(os.time(), startTime)
				creatureObject:sendSystemMessage(trackLaptime .. index)
				creatureObject:sendSystemMessage("Time " .. seconds .. "s")
				writeScreenPlayData(pObject, self.trackName, "waypointID", waypointID)
				writeScreenPlayData(pObject,self.trackName, "waypoint", index+1)
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
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint3(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint4(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint5(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint6(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint7(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint8(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint9(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint10(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint11(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint12(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint13(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint14(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint15(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint16(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end
function RaceTrackManager:enteredWaypoint17(pActiveArea, pObject)
	ObjectManager.withPlayerObject(pObject, function(playerObject)
		RaceTrackManager:processWaypoint(pObject,1)
	end)
end

function RaceTrackManager:finalWaypoint(pActiveArea, pObject)
	ObjectManager.withCreatureObject(pObject, function(creatureObject)
	  ObjectManager.withCreaturePlayerObject(pObject, function(playerObject)
	    RaceTrackManager:loadVariablesFromScreenPlay(pObject)
		local lastIndex =  readScreenPlayData(pObject, self.trackName, "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==self.numOfWPs then
				local startTime = readScreenPlayData(pObject, self.trackName, "starttime")
				local seconds = os.difftime(os.time(), startTime)
				local lastWaypointID =  readScreenPlayData(pObject, self.trackName, "waypointID")
				if lastWaypointID~="" then
					playerObject:removeWaypoint(tonumber(lastWaypointID),true)
				end 				
				creatureObject:sendSystemMessage("@theme_park/racing/racing:finish_message")
				creatureObject:sendSystemMessage("Time " .. seconds .. "s")	
				local personalTime = tonumber(readScreenPlayData(pObject, self.trackName ..".STATS", "RecordTime"))
				if personalTime == nil then
					personalTime = 99999999
				end
				if personalTime > seconds then
					writeScreenPlayData(pObject, self.trackName ..".STATS", "RecordTime",seconds )
					creatureObject:sendSystemMessage("@theme_park/racing/racing:new_record")
				end
				local recordTime = readSharedMemory(self.trackName ..".recordtime")
				if recordTime == 0 then
					recordTime = 99999999
				end 
				
				if recordTime > seconds then
					creatureObject:sendSystemMessage("@theme_park/racing/racing:beat_the_record")
					writeSharedMemory(self.trackName ..".recordtime",seconds)
					local playername = creatureObject:getFirstName()
					if playername ~= nil then
						writeStringSharedMemory(self.trackName ..".recordholder",playername)
					end
					if playerObject:hasBadge(self.badge) == false then
						playerObject:awardBadge(self.badge)
					end
				end 
				clearScreenPlayData(pObject,self.trackName )
				clearScreenPlayData(pObject,"trackName")
			end
		end
	  end)
	end)
end


return RaceTrackManager