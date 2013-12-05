local ObjectManager = require("managers.object.object_manager")

RaceTrack =ScreenPlay:new {}

function RaceTrack:createRaceTrack(callBackClassName)
	for lc = 1, table.getn(self.trackConfig.waypoints) , 1 do
		local pWaypointAA = spawnSceneObject(self.trackConfig.planetName, "object/active_area.iff", self.trackConfig.waypoints[lc].x, 0, self.trackConfig.waypoints[lc].y, 0, 0, 0, 0, 0)
		if (pWaypointAA ~= nil) then
			local activeArea = LuaActiveArea(pWaypointAA)
			activeArea:setRadius(self.trackConfig.waypointRadius)
			createObserver(ENTEREDAREA, callBackClassName, "enteredWaypoint" , pWaypointAA)
			--printf(" : x=" .. waypoint.x .. " y=" .. waypoint.y .. " Planet :"..planetName.." Radius :"..radius .. "\n")
		end
	end
end

function RaceTrack:startRacing(pObject)
  ObjectManager.withCreatureAndPlayerObject(pObject, function(creatureObject, playerObject)
  		clearScreenPlayData(pObject,self.trackConfig.trackName )
		local waypointID = playerObject:addWaypoint(self.trackConfig.planetName,self.trackConfig.trackCheckpoint .. "0",self.trackConfig.trackCheckpoint .. "0",self.trackConfig.waypoints[1].x,self.trackConfig.waypoints[1].y,WAYPOINTWHITE,true,true)
		--local time = os.time()
		local time = getTimestampMilli()
		writeScreenPlayData(pObject, self.trackConfig.trackName, "starttime", time)
		writeScreenPlayData(pObject, self.trackConfig.trackName, "waypointID", waypointID)
		writeScreenPlayData(pObject, self.trackConfig.trackName, "waypoint", 1)
		creatureObject:sendSystemMessage("@theme_park/racing/racing:go_fly")
		creatureObject:playMusicMessage("sound/music_combat_bfield_lp.snd")
   end)
end

function RaceTrack:processWaypoint(pActiveArea, pObject)
	ObjectManager.withCreaturePlayerObject(pObject, function(playerObject)
		local lastIndex =  readScreenPlayData(pObject, self.trackConfig.trackName, "waypoint")
		if lastIndex ~= "" then
			local index = self:getWaypointIndex(pActiveArea)
			if tonumber(lastIndex)==index then
				local lastWaypointID =  readScreenPlayData(pObject, self.trackConfig.trackName, "waypointID")
				if lastWaypointID=="" then
					return nil -- Somethings gone wrong
				end
				playerObject:removeWaypoint(tonumber(lastWaypointID),true)
				if tonumber(index)==table.getn(self.trackConfig.waypoints) then
					self:finalWaypoint(pActiveArea, pObject)
				else
					self:actuallyProcessWaypoint(pObject,index)
				end 
			end
		end
	end)
end

function RaceTrack:roundNumber(num)
  local mult = 10 ^ (self.trackConfig.timeResolution or 0 )
  return math.floor(num * mult + 0.5) / mult
end


function RaceTrack:actuallyProcessWaypoint(pObject,index)
	ObjectManager.withCreatureAndPlayerObject(pObject, function(creatureObject,playerObject)
		local waypointID = playerObject:addWaypoint(self.trackConfig.planetName,self.trackConfig.trackCheckpoint .. index,self.trackConfig.trackCheckpoint .. index,self.trackConfig.waypoints[index+1].x,self.trackConfig.waypoints[index+1].y,WAYPOINTWHITE,true,true)
		local seconds = self:getLaptime(pObject)
		creatureObject:sendSystemMessage(self.trackConfig.trackLaptime .. index)
		creatureObject:sendSystemMessage("Time " .. self:roundNumber(seconds/1000) .. "s")
		writeScreenPlayData(pObject, self.trackConfig.trackName, "waypointID", waypointID)
		writeScreenPlayData(pObject,self.trackConfig.trackName, "waypoint", index+1)
		creatureObject:playMusicMessage("sound/music_combat_bfield_lp.snd")
	end)
end

function  RaceTrack:finalWaypoint(pActiveArea, pObject)
	ObjectManager.withCreatureObject(pObject, function(creatureObject)
		creatureObject:playMusicMessage("sound/music_combat_bfield_vict.snd")
		self:checkPersonalTime(pObject)
		self:checkServerRecordTime(pObject)
		clearScreenPlayData(pObject,self.trackConfig.trackName )
	end)
end
function RaceTrack:getLaptime(pObject)
	local startTime = readScreenPlayData(pObject, self.trackConfig.trackName, "starttime")
	local seconds = getTimestampMilli() - tonumber(startTime)
	return seconds
end


function RaceTrack:checkPersonalTime(pObject)
	ObjectManager.withCreatureAndPlayerObject(pObject, function(creatureObject,playerObject)
		local seconds = self:getLaptime(pObject)
		creatureObject:sendSystemMessage("@theme_park/racing/racing:finish_message")
		creatureObject:sendSystemMessage("Time " .. self:roundNumber(seconds/1000) .. "s")
		local personalTime = tonumber(readScreenPlayData(pObject, self.trackConfig.trackName ..".STATS", "PersonalRecordTime"))
		if personalTime == nil then
			personalTime = 9999999999
		end
		if personalTime > seconds then
			writeScreenPlayData(pObject, self.trackConfig.trackName ..".STATS", "PersonalRecordTime",seconds)
			creatureObject:sendSystemMessage("@theme_park/racing/racing:new_record")
		end
	end)
end
function RaceTrack:checkServerRecordTime(pObject)
	ObjectManager.withCreatureAndPlayerObject(pObject, function(creatureObject,playerObject)
		local recordTime = readSharedMemory(self.trackConfig.trackName ..".recordtime")
		if recordTime == 0 then
			recordTime = 9999999999
		end
		local seconds = self:getLaptime(pObject)
		if recordTime > seconds then
			creatureObject:sendSystemMessage("@theme_park/racing/racing:beat_the_record")
			writeSharedMemory(self.trackConfig.trackName ..".recordtime",seconds)
			local playername = creatureObject:getFirstName()
			if playername ~= nil then
				writeStringSharedMemory(self.trackConfig.trackName ..".recordholder",playername)
			end
			if playerObject:hasBadge(self.trackConfig.badgeToAward) == false then
				playerObject:awardBadge(self.trackConfig.badgeToAward)
			end
		end
	end)
end
function RaceTrack:getWaypointIndex(pActiveArea)
	return ObjectManager.withSceneObject(pActiveArea, function(sceneObject)
		local index = 0
		local wpX = sceneObject:getPositionX()
		local wpY = sceneObject:getPositionY()
		for lc = 1, table.getn(self.trackConfig.waypoints) , 1 do
			if self.trackConfig.waypoints[lc].x==wpX and self.trackConfig.waypoints[lc].y==wpY then
				index = lc
				break
			end
		end
		return index
	end)
end
function RaceTrack:displayPersonalBestTime(pObject,trackConfig)
	ObjectManager.withCreatureObject(pObject, function(creatureObject)
		local personalTime = tonumber(readScreenPlayData(pObject, self.trackConfig.trackName ..".STATS", "PersonalRecordTime"))
		creatureObject:sendSystemMessage("@theme_park/racing/racing:whats_my_time")
		if personalTime == nil then
			creatureObject:sendSystemMessage("No Time Set!")
		else
			creatureObject:sendSystemMessage("Time " .. self:roundNumber(personalTime/1000) .. "s")
		end
	end)
end

function RaceTrack:displayTrackBestTime(pObject,trackConfig)
	ObjectManager.withCreatureObject(pObject, function(creatureObject)
		local recordTime = tonumber(readSharedMemory(self.trackConfig.trackName ..".recordtime"))
		creatureObject:sendSystemMessage("@theme_park/racing/racing:current_record_holder")
		if recordTime == 0 then
			creatureObject:sendSystemMessage("No Time Set!")
		else
			creatureObject:sendSystemMessage(readStringSharedMemory(self.trackConfig.trackName ..".recordholder") .. " with a time of " .. self:roundNumber(recordTime/1000) .. "s")
		end
	end)
end

return RaceTrack