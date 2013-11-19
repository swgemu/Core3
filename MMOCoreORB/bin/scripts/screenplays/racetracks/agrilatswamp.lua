agrilatswap_racetrack_screenplay = ScreenPlay:new {
	numberOfActs = 1,
	
	states = {
	},
	planetName = "corellia",

	waypoints = {{x = 1541, y = 4741,wpName = "@theme_park/racing/racing:agrilat_waypoint_name_checkpoint0"}, 
	  {x = 1317, y = 5013,wpName = "@theme_park/racing/racing:agrilat_waypoint_name_checkpoint1"}, 
	  {x = 1050,  y = 5066,wpName = "@theme_park/racing/racing:agrilat_waypoint_name_checkpoint2"},
	  {x = 805,  y = 4949,wpName = "@theme_park/racing/racing:agrilat_waypoint_name_checkpoint3"},
	  {x = 597, y = 4362,wpName = "@theme_park/racing/racing:agrilat_waypoint_name_checkpoint4"}, 
	  {x = 602,y = 4202,wpName = "@theme_park/racing/racing:agrilat_waypoint_name_checkpoint5"}, 
	  {x = 688, y = 3920,wpName = "@theme_park/racing/racing:agrilat_waypoint_name_checkpoint6"},
	  {x = 976,  y = 3770,wpName = "@theme_park/racing/racing:agrilat_waypoint_name_checkpoint7"},
	  {x = 922, y = 4261,wpName = "@theme_park/racing/racing:agrilat_waypoint_name_checkpoint8"},
	  {x = 1050,  y = 4634,wpName = "@theme_park/racing/racing:agrilat_waypoint_name_checkpoint9"}, 
	  {x = 1317, y = 4192,wpName = "@theme_park/racing/racing:agrilat_waypoint_name_checkpoint10"}, 
	  {x = 1593, y = 4610,wpName = "@theme_park/racing/racing:agrilat_waypoint_name_checkpoint11"},
	  {x = 1781, y = 4544,wpName = "@theme_park/racing/racing:agrilat_waypoint_name_checkpoint12"}, 
	  {x = 1680,y = 4700, wpName = "@theme_park/racing/racing:agrilat_waypoint_name_checkpoint13"}}

}

registerScreenPlay("agrilatswap_racetrack_screenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function agrilatswap_racetrack_screenplay:start()
	if (isZoneEnabled(self.planetName)) then
		self:spawnMobiles()
		self:spawnObservers()
		printf("Launching agrilat\n")
	end
end

function agrilatswap_racetrack_screenplay:spawnMobiles()
	local pCoord = spawnMobile(self.planetName, "agrilat_race_coordinator", 1, 1680, 20.0, 4700, 35, 0 )
end

function agrilatswap_racetrack_screenplay:spawnObservers()
	local pWaypoint1AA = spawnSceneObject(self.planetName, "object/active_area.iff", self.waypoints[1].x, 0, self.waypoints[1].y, 0, 0, 0, 0, 0)
	if (pWaypoint1AA ~= nil) then
		local activeArea = LuaActiveArea(pWaypoint1AA)
		activeArea:setRadius(25)
		createObserver(ENTEREDAREA, "agrilatswap_racetrack_screenplay", "spawnWaypoint1", pWaypoint1AA)
	end
	local pWaypoint2AA = spawnSceneObject(self.planetName, "object/active_area.iff", self.waypoints[2].x, 0, self.waypoints[2].y, 0, 0, 0, 0, 0)
	if (pWaypoint2AA ~= nil) then
		local activeArea = LuaActiveArea(pWaypoint2AA)
		activeArea:setRadius(25)
		createObserver(ENTEREDAREA, "agrilatswap_racetrack_screenplay", "spawnWaypoint2", pWaypoint2AA)
	end
	local pWaypoint3AA = spawnSceneObject(self.planetName, "object/active_area.iff", self.waypoints[3].x, 0, self.waypoints[3].y, 0, 0, 0, 0, 0)
	if (pWaypoint3AA ~= nil) then
		local activeArea = LuaActiveArea(pWaypoint3AA)
		activeArea:setRadius(25)
		createObserver(ENTEREDAREA, "agrilatswap_racetrack_screenplay", "spawnWaypoint3", pWaypoint3AA)
	end
	local pWaypoint4AA = spawnSceneObject(self.planetName, "object/active_area.iff", self.waypoints[4].x, 0, self.waypoints[4].y, 0, 0, 0, 0, 0)
	if (pWaypoint4AA ~= nil) then
		local activeArea = LuaActiveArea(pWaypoint4AA)
		activeArea:setRadius(25)
		createObserver(ENTEREDAREA, "agrilatswap_racetrack_screenplay", "spawnWaypoint4", pWaypoint4AA)
	end
	local pWaypoint5AA = spawnSceneObject(self.planetName, "object/active_area.iff", self.waypoints[5].x, 0, self.waypoints[5].y, 0, 0, 0, 0, 0)
	if (pWaypoint5AA ~= nil) then
		local activeArea = LuaActiveArea(pWaypoint5AA)
		activeArea:setRadius(25)
		createObserver(ENTEREDAREA, "agrilatswap_racetrack_screenplay", "spawnWaypoint5", pWaypoint5AA)
	end
	local pWaypoint6AA = spawnSceneObject(self.planetName, "object/active_area.iff", self.waypoints[6].x, 0, self.waypoints[6].y, 0, 0, 0, 0, 0)
	if (pWaypoint6AA ~= nil) then
		local activeArea = LuaActiveArea(pWaypoint6AA)
		activeArea:setRadius(25)
		createObserver(ENTEREDAREA, "agrilatswap_racetrack_screenplay", "spawnWaypoint6", pWaypoint6AA)
	end
	local pWaypoint7AA = spawnSceneObject(self.planetName, "object/active_area.iff", self.waypoints[7].x, 0, self.waypoints[7].y, 0, 0, 0, 0, 0)
	if (pWaypoint7AA ~= nil) then
		local activeArea = LuaActiveArea(pWaypoint7AA)
		activeArea:setRadius(25)
		createObserver(ENTEREDAREA, "agrilatswap_racetrack_screenplay", "spawnWaypoint7", pWaypoint7AA)
	end
	local pWaypoint8AA = spawnSceneObject(self.planetName, "object/active_area.iff", self.waypoints[8].x, 0, self.waypoints[8].y, 0, 0, 0, 0, 0)
	if (pWaypoint8AA ~= nil) then
		local activeArea = LuaActiveArea(pWaypoint8AA)
		activeArea:setRadius(25)
		createObserver(ENTEREDAREA, "agrilatswap_racetrack_screenplay", "spawnWaypoint8", pWaypoint8AA)
	end
	local pWaypoint9AA = spawnSceneObject(self.planetName, "object/active_area.iff", self.waypoints[9].x, 0, self.waypoints[9].y, 0, 0, 0, 0, 0)
	if (pWaypoint9AA ~= nil) then
		local activeArea = LuaActiveArea(pWaypoint9AA)
		activeArea:setRadius(25)
		createObserver(ENTEREDAREA, "agrilatswap_racetrack_screenplay", "spawnWaypoint9", pWaypoint9AA)
	end
	local pWaypoint10AA = spawnSceneObject(self.planetName, "object/active_area.iff", self.waypoints[10].x, 0, self.waypoints[10].y, 0, 0, 0, 0, 0)
	if (pWaypoint10AA ~= nil) then
		local activeArea = LuaActiveArea(pWaypoint10AA)
		activeArea:setRadius(25)
		createObserver(ENTEREDAREA, "agrilatswap_racetrack_screenplay", "spawnWaypoint10", pWaypoint10AA)
	end
	local pWaypoint11AA = spawnSceneObject(self.planetName, "object/active_area.iff", self.waypoints[11].x, 0, self.waypoints[11].y, 0, 0, 0, 0, 0)
	if (pWaypoint11AA ~= nil) then
		local activeArea = LuaActiveArea(pWaypoint11AA)
		activeArea:setRadius(25)
		createObserver(ENTEREDAREA, "agrilatswap_racetrack_screenplay", "spawnWaypoint11", pWaypoint11AA)
	end
	local pWaypoint12AA = spawnSceneObject(self.planetName, "object/active_area.iff", self.waypoints[12].x, 0, self.waypoints[12].y, 0, 0, 0, 0, 0)
	if (pWaypoint12AA ~= nil) then
		local activeArea = LuaActiveArea(pWaypoint12AA)
		activeArea:setRadius(25)
		createObserver(ENTEREDAREA, "agrilatswap_racetrack_screenplay", "spawnWaypoint12", pWaypoint12AA)
	end
	local pWaypoint13AA = spawnSceneObject(self.planetName, "object/active_area.iff", self.waypoints[13].x, 0, self.waypoints[13].y, 0, 0, 0, 0, 0)
	if (pWaypoint13AA ~= nil) then
		local activeArea = LuaActiveArea(pWaypoint13AA)
		activeArea:setRadius(25)
		createObserver(ENTEREDAREA, "agrilatswap_racetrack_screenplay", "spawnWaypoint13", pWaypoint13AA)
	end
	local pWaypoint14AA = spawnSceneObject(self.planetName, "object/active_area.iff", self.waypoints[14].x, 0, self.waypoints[14].y, 0, 0, 0, 0, 0)
	if (pWaypoint14AA ~= nil) then
		local activeArea = LuaActiveArea(pWaypoint14AA)
		activeArea:setRadius(25)
		createObserver(ENTEREDAREA, "agrilatswap_racetrack_screenplay", "spawnFinish", pWaypoint14AA)
	end	
end


function agrilatswap_racetrack_screenplay:spawnFirstWaypoint(pObject)
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local playerCreature = LuaCreatureObject(pObject)
		clearScreenPlayData(pObject,"AGSWRT")
		playerCreature:sendSystemMessage("@theme_park/racing/racing:go_fly")
		local player = LuaPlayerObject(pObject)
		--local waypointID = player:addWaypoint(self.planetName,self.waypoints[1].wpName,planetName,self.waypoints[1].wpName,self.waypoints[1].x,self.waypoints[1].y,WAYPOINTWHITE,true,true)
		local waypointID = playerCreature:setClientWaypoint(self.planetName,self.waypoints[1].wpName,self.waypoints[1].x,self.waypoints[1].y)
		time = os.time()
		writeScreenPlayData(pObject, "AGSWRT", "starttime", time)
		writeScreenPlayData(pObject, "AGSWRT", "waypointID", waypointID)
		printf("WaypointID :" .. waypointID)
		writeScreenPlayData(pObject, "AGSWRT", "waypoint", 1)
		--seconds = os.difftime(currenttime, receivedtime)
		playerCreature:sendSystemMessage("@theme_park/racing/racing:go_fly")

	end
end

function agrilatswap_racetrack_screenplay:processWaypoint(pObject,index)
	local playerCreature = LuaCreatureObject(pObject)
	local lastWaypointID =  readScreenPlayData(pObject, "AGSWRT", "waypointID")
	if lastWaypointID=="" then
		return false -- Somethings gone wrong
	end 
	printf("lastWaypointID :" .. lastWaypointID)
	--local player = LuaPlayerObject(pObject)
	playerCreature:removeClientWaypoint(tonumber(lastWaypointID))
	--local waypointID = player:addWaypoint(self.planetName,self.waypoints[index+1].wpName,"",self.waypoints[index+1].x,self.waypoints[index+1].y,WAYPOINTWHITE,true,true)
	local waypointID = playerCreature:setClientWaypoint(self.planetName,self.waypoints[index+1].wpName,self.waypoints[index+1].x,self.waypoints[index+1].y)
	local startTime = readScreenPlayData(pObject, "AGSWRT", "starttime")
	local seconds = os.difftime(os.time(), startTime)
	playerCreature:sendSystemMessage("@theme_park/racing/racing:agrilat_laptime_checkpoint"..index)
	playerCreature:sendSystemMessage("Time " .. seconds .. "s")
	writeScreenPlayData(pObject, "AGSWRT", "waypointID", waypointID)
	writeScreenPlayData(pObject, "AGSWRT", "waypoint", index+1)
end


function agrilatswap_racetrack_screenplay:spawnWaypoint1(pActiveArea, pObject)
	printf("in Waypoint1")
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local lastIndex =  readScreenPlayData(pObject, "AGSWRT", "waypoint")
		if lastIndex ~= "" then
			printf("WP1 :"..lastIndex ..":")
			if tonumber(lastIndex)==1 then
				agrilatswap_racetrack_screenplay:processWaypoint(pObject,tonumber(lastIndex))
			end
		end
	end
end
function agrilatswap_racetrack_screenplay:spawnWaypoint2(pActiveArea, pObject)
	printf("in Waypoint2")
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local lastIndex =  readScreenPlayData(pObject, "AGSWRT", "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==2 then
				agrilatswap_racetrack_screenplay:processWaypoint(pObject,tonumber(lastIndex))
			end
		end
	end
end
function agrilatswap_racetrack_screenplay:spawnWaypoint3(pActiveArea, pObject)
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local lastIndex =  readScreenPlayData(pObject, "AGSWRT", "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==3 then
				agrilatswap_racetrack_screenplay:processWaypoint(pObject,tonumber(lastIndex))
			end
		end
	end
end
function agrilatswap_racetrack_screenplay:spawnWaypoint4(pActiveArea, pObject)
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local lastIndex =  readScreenPlayData(pObject, "AGSWRT", "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==4 then
				agrilatswap_racetrack_screenplay:processWaypoint(pObject,tonumber(lastIndex))
			end
		end
	end
end
function agrilatswap_racetrack_screenplay:spawnWaypoint5(pActiveArea, pObject)
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local lastIndex =  readScreenPlayData(pObject, "AGSWRT", "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==5 then
				agrilatswap_racetrack_screenplay:processWaypoint(pObject,tonumber(lastIndex))
			end
		end
	end
end
function agrilatswap_racetrack_screenplay:spawnWaypoint6(pActiveArea, pObject)
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local lastIndex =  readScreenPlayData(pObject, "AGSWRT", "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==6 then
				agrilatswap_racetrack_screenplay:processWaypoint(pObject,tonumber(lastIndex))
			end
		end
	end
end
function agrilatswap_racetrack_screenplay:spawnWaypoint7(pActiveArea, pObject)
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local lastIndex =  readScreenPlayData(pObject, "AGSWRT", "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==7 then
				agrilatswap_racetrack_screenplay:processWaypoint(pObject,tonumber(lastIndex))
			end
		end
	end
end
function agrilatswap_racetrack_screenplay:spawnWaypoint8(pActiveArea, pObject)
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local lastIndex =  readScreenPlayData(pObject, "AGSWRT", "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==8 then
				agrilatswap_racetrack_screenplay:processWaypoint(pObject,tonumber(lastIndex))
			end
		end
	end
end
function agrilatswap_racetrack_screenplay:spawnWaypoint9(pActiveArea, pObject)
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local lastIndex =  readScreenPlayData(pObject, "AGSWRT", "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==9 then
				agrilatswap_racetrack_screenplay:processWaypoint(pObject,tonumber(lastIndex))
			end
		end
	end
end
function agrilatswap_racetrack_screenplay:spawnWaypoint10(pActiveArea, pObject)
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local lastIndex =  readScreenPlayData(pObject, "AGSWRT", "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==10 then
				agrilatswap_racetrack_screenplay:processWaypoint(pObject,tonumber(lastIndex))
			end
		end
	end
end
function agrilatswap_racetrack_screenplay:spawnWaypoint11(pActiveArea, pObject)
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local lastIndex =  readScreenPlayData(pObject, "AGSWRT", "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==11 then
				agrilatswap_racetrack_screenplay:processWaypoint(pObject,tonumber(lastIndex))
			end
		end
	end
end
function agrilatswap_racetrack_screenplay:spawnWaypoint12(pActiveArea, pObject)
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local lastIndex =  readScreenPlayData(pObject, "AGSWRT", "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==12 then
				agrilatswap_racetrack_screenplay:processWaypoint(pObject,tonumber(lastIndex))
			end
		end
	end
end
function agrilatswap_racetrack_screenplay:spawnWaypoint13(pActiveArea, pObject)
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local lastIndex =  readScreenPlayData(pObject, "AGSWRT", "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==13 then
				agrilatswap_racetrack_screenplay:processWaypoint(pObject,tonumber(lastIndex))
			end
		end
	end
end
function agrilatswap_racetrack_screenplay:spawnFinish(pActiveArea, pObject)
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local lastIndex =  readScreenPlayData(pObject, "AGSWRT", "waypoint")
		if lastIndex ~= "" then
			if tonumber(lastIndex)==14 then
				local startTime = readScreenPlayData(pObject, "AGSWRT", "starttime")
				local seconds = os.difftime(os.time(), startTime)
				local playerCreature = LuaCreatureObject(pObject)
				local player = LuaPlayerObject(pObject)
				local lastWaypointID =  readScreenPlayData(pObject, "AGSWRT", "waypointID")
				if lastWaypointID~="" then
					playerCreature:removeClientWaypoint(tonumber(lastWaypointID))
				end 				
				playerCreature:sendSystemMessage("@theme_park/racing/racing:finish_message")
				playerCreature:sendSystemMessage("Time " .. seconds .. "s")	
				local personalTime = tonumber(readScreenPlayData(pObject, "AGSWRT.STATS", "RecordTime"))
				if personalTime == nil then
					personalTime = 99999999
				end
				if personalTime > seconds then
					writeScreenPlayData(pObject, "AGSWRT.STATS", "RecordTime",seconds )
					playerCreature:sendSystemMessage("@theme_park/racing/racing:new_record")
				end
				local recordTime = readSharedMemory("agrilat.swamp.track.recordtime")
				if recordTime == 0 then
					recordTime = 99999999
				end 
				
				if recordTime > seconds then
					playerCreature:sendSystemMessage("@theme_park/racing/racing:beat_the_record")
					writeSharedMemory("agrilat.swamp.track.recordtime",seconds)
					writeSharedStringMemory("agrilat.swamp.track.recordholder",player:getFirstName())
					player:awardBadge(BDG_RACING_AGRILAT_SWAMP)
				end 
				clearScreenPlayData(pObject,"AGSWRT")
			end
		end
	end
end

function agrilatswap_racetrack_screenplay:displayPersonalBestTime(pObject)
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local playerCreature = LuaCreatureObject(pObject)
		local personalTime = tonumber(readScreenPlayData(pObject, "AGSWRT.STATS", "RecordTime"))
		playerCreature:sendSystemMessage("@theme_park/racing/racing:whats_my_time")
		if personalTime == nil then
			playerCreature:sendSystemMessage("No Time Set!")
		else
			playerCreature:sendSystemMessage("Time " .. personalTime .. "s")
		end 
		
	end
end

function agrilatswap_racetrack_screenplay:displayTrackBestTime(pObject)
	local pSo = LuaSceneObject(pObject)
	if (pSo:isPlayerCreature()) then
		local playerCreature = LuaCreatureObject(pObject)
		local recordTime = tonumber(readSharedMemory("agrilat.swamp.track.recordtime"))
		playerCreature:sendSystemMessage("@theme_park/racing/racing:current_record_holder")
		if recordTime == 0 then
			playerCreature:sendSystemMessage("No Time Set!")
		else
			playerCreature:sendSystemMessage(readSharedMemory("agrilat.swamp.track.recordholder") .. " with a time of " .. recordTime .. "s")
		end 
		
	end
end


agrilat_swamp_racetrack_convo_handler = Object:new {
	
	
 }

function agrilat_swamp_racetrack_convo_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	lastConversation = nil
	local conversation = LuaConversationTemplate(conversationTemplate)
	local nextConversationScreen 
	if ( conversation ~= nil ) then
		-- checking to see if we have a next screen
		if ( convosession ~= nil ) then 
			 local session = LuaConversationSession(convosession)
			 if ( session ~= nil ) then
			 	lastConversationScreen = session:getLastConversationScreen()
			 else
			 	print("session was not good in getNextScreen")
			 end
		end
		if ( lastConversationScreen == nil ) then
		 	nextConversationScreen = conversation:getInitialScreen()	
		else
			local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
			local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)	
			nextConversationScreen = conversation:getScreen(optionLink)
		end
	end	
	return nextConversationScreen
end


function agrilat_swamp_racetrack_convo_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	if ( screenID == "cs_jsPlumb_1_116" ) then
		agrilatswap_racetrack_screenplay:spawnFirstWaypoint(conversingPlayer)
	elseif ( screenID == "cs_jsPlumb_1_181" ) then -- Personal Best
		agrilatswap_racetrack_screenplay:displayPersonalBestTime(conversingPlayer)
	elseif ( screenID == "cs_jsPlumb_1_207" ) then -- Track Best
		agrilatswap_racetrack_screenplay:displayTrackBestTime(conversingPlayer)
	end
	return conversationScreen
end


