local ObjectManager = require("managers.object.object_manager")

RaceTrack =ScreenPlay:new {}

function RaceTrack:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end


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
		local waypointID = playerObject:addWaypoint(self.trackConfig.planetName,self.trackConfig.trackCheckpoint .. "0",self.trackConfig.trackCheckpoint .. "0",self.trackConfig.waypoints[1].x,self.trackConfig.waypoints[1].y,WAYPOINTWHITE,true,true)
		local time = os.time()
		writeScreenPlayData(pObject, self.trackConfig.trackName, "starttime", time)
		writeScreenPlayData(pObject, self.trackConfig.trackName, "waypointID", waypointID)
		writeScreenPlayData(pObject, self.trackConfig.trackName, "waypoint", 1)
		creatureObject:sendSystemMessage("@theme_park/racing/racing:go_fly")
   end)
end
function RaceTrack:processWaypoint(pActiveArea, pObject)
	ObjectManager.withCreatureObject(pObject, function(creatureObject)
	  	ObjectManager.withCreaturePlayerObject(pObject, function(playerObject)
	   		ObjectManager.withSceneObject(pActiveArea, function(sceneObject)
				local lastIndex =  readScreenPlayData(pObject, self.trackConfig.trackName, "waypoint")
				if lastIndex ~= "" then
					-- Okay time to look at the listie :)
					local index = 0
					local wpX = sceneObject:getPositionX()
					local wpY = sceneObject:getPositionY()
					for lc = 1, table.getn(self.trackConfig.waypoints) , 1 do
						if self.trackConfig.waypoints[lc].x==wpX and self.trackConfig.waypoints[lc].y==wpY then
							index = lc
							break
						end
					end
					if tonumber(lastIndex)==tonumber(index) then
						if tonumber(index)==table.getn(self.trackConfig.waypoints) then
							self:finalWaypoint(pActiveArea, pObject)
						else
							local lastWaypointID =  readScreenPlayData(pObject, self.trackConfig.trackName, "waypointID")
							if lastWaypointID=="" then
								return nil -- Somethings gone wrong
							end
							--printf("lastWaypointID :" .. lastIndex)
							playerObject:removeWaypoint(tonumber(lastWaypointID),true)
							local waypointID = playerObject:addWaypoint(self.trackConfig.planetName,self.trackConfig.trackCheckpoint .. index,self.trackConfig.trackCheckpoint .. index,self.trackConfig.waypoints[index+1].x,self.trackConfig.waypoints[index+1].y,WAYPOINTWHITE,true,true)
							local startTime = readScreenPlayData(pObject, self.trackConfig.trackName, "starttime")
							local seconds = os.difftime(os.time(), startTime)
							creatureObject:sendSystemMessage(self.trackConfig.trackLaptime .. index)
							creatureObject:sendSystemMessage("Time " .. seconds .. "s")
							writeScreenPlayData(pObject, self.trackConfig.trackName, "waypointID", waypointID)
							--printf("writing WP IDX :"..(index+1))
							writeScreenPlayData(pObject,self.trackConfig.trackName, "waypoint", index+1)
						end 
					end
				end
			end)
		end)
	end)
end

function  RaceTrack:finalWaypoint(pActiveArea, pObject)
	ObjectManager.withCreatureObject(pObject, function(creatureObject)
  	  	ObjectManager.withCreaturePlayerObject(pObject, function(playerObject)
			local startTime = readScreenPlayData(pObject, self.trackConfig.trackName, "starttime")
			local seconds = os.difftime(os.time(), startTime)
			local lastWaypointID =  readScreenPlayData(pObject, self.trackConfig.trackName, "waypointID")
			if lastWaypointID~="" then
				playerObject:removeWaypoint(tonumber(lastWaypointID),true)
			end
			creatureObject:sendSystemMessage("@theme_park/racing/racing:finish_message")
			creatureObject:sendSystemMessage("Time " .. seconds .. "s")
			local personalTime = tonumber(readScreenPlayData(pObject, self.trackConfig.trackName ..".STATS", "RecordTime"))
			if personalTime == nil then
				personalTime = 99999999
			end
			if personalTime > seconds then
				writeScreenPlayData(pObject, self.trackConfig.trackName ..".STATS", "PersonalRecordTime",seconds )
				creatureObject:sendSystemMessage("@theme_park/racing/racing:new_record")
			end
			local recordTime = readSharedMemory(self.trackConfig.trackName ..".recordtime")
			if recordTime == 0 then
				recordTime = 99999999
			end
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
			clearScreenPlayData(pObject,self.trackConfig.trackName )
			clearScreenPlayData(pObject,"trackName")
	  	end)
	end)
end
function RaceTrack:displayPersonalBestTime(pObject,trackConfig)
	ObjectManager.withCreatureObject(pObject, function(creatureObject)
		local personalTime = tonumber(readScreenPlayData(pObject, self.trackConfig.trackName ..".STATS", "PersonalRecordTime"))
		creatureObject:sendSystemMessage("@theme_park/racing/racing:whats_my_time")
		if personalTime == nil then
			creatureObject:sendSystemMessage("No Time Set!")
		else
			creatureObject:sendSystemMessage("Time " .. personalTime .. "s")
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
			creatureObject:sendSystemMessage(readStringSharedMemory(self.trackConfig.trackName ..".recordholder") .. " with a time of " .. recordTime .. "s")
		end
	end)
end

return RaceTrack