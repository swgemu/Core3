local ObjectManager = require("managers.object.object_manager")
local RaceTrackManager = require("screenplays.racetracks.racetrackengine")


agrilatswap_racetrack_screenplay = ScreenPlay:new {
	numberOfActs = 1,
	
	states = {
	},
	planetName = "corellia",
	badgeToAward=BDG_RACING_AGRILAT_SWAMP,
	trackName="AGSWRT",
	trackCheckpoint="@theme_park/racing/racing:agrilat_waypoint_name_checkpoint",
	trackLaptime="@theme_park/racing/racing:agrilat_waypoint_name_checkpoint",
	waypoints = {{x = 1541, y = 4741}, 
	  {x = 1317, y = 5013}, 
	  {x = 1050,  y = 5066},
	  {x = 805,  y = 4949},
	  {x = 597, y = 4362}, 
	  {x = 602,y = 4202}, 
	  {x = 688, y = 3920},
	  {x = 976,  y = 3770},
	  {x = 922, y = 4261},
	  {x = 1050,  y = 4634}, 
	  {x = 1317, y = 4192}, 
	  {x = 1593, y = 4610},
	  {x = 1781, y = 4544}, 
	  {x = 1680,y = 4700}}

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
	for lc = 1, table.getn(self.waypoints) -1 , 1 do
		RaceTrackManager:spawnActiveArea(self.planetName,self.waypoints[lc],25,lc,false)
	end
	RaceTrackManager:spawnActiveArea(self.planetName,self.waypoints[table.getn(self.waypoints)],25,table.getn(self.waypoints),true)
end
function agrilatswap_racetrack_screenplay:startRace(pObject)
	writeScreenPlayData(pObject, "trackName", "current", self.trackName)
	for lc = 1, table.getn(self.waypoints) , 1 do
		writeScreenPlayData(pObject, self.trackName, "WP"..lc..".X", self.waypoints[lc].x)
		writeScreenPlayData(pObject, self.trackName, "WP"..lc..".Y", self.waypoints[lc].y)
	end
	writeScreenPlayData(pObject, self.trackName, "badgeToAward", self.badgeToAward)
	writeScreenPlayData(pObject, self.trackName, "trackCheckpoint", self.trackCheckpoint)
	writeScreenPlayData(pObject, self.trackName, "trackLaptime", self.trackLaptime)
	writeScreenPlayData(pObject, self.trackName, "planetName", self.planetName)
	writeScreenPlayData(pObject, self.trackName, "numberofwaypoints", table.getn(self.waypoints))
	RaceTrackManager:spawnFirstWaypoint(pObject)
end
function agrilatswap_racetrack_screenplay:displayPersonalBestTime(pObject)
	ObjectManager.withCreatureObject(pObject, function(creatureObject)
		local personalTime = tonumber(readScreenPlayData(pObject, "AGSWRT.STATS", "RecordTime"))
		creatureObject:sendSystemMessage("@theme_park/racing/racing:whats_my_time")
		if personalTime == nil then
			creatureObject:sendSystemMessage("No Time Set!")
		else
			creatureObject:sendSystemMessage("Time " .. personalTime .. "s")
		end 	
	end)
end

function agrilatswap_racetrack_screenplay:displayTrackBestTime(pObject)
	ObjectManager.withCreatureObject(pObject, function(creatureObject)
		local recordTime = tonumber(readSharedMemory("AGSWRT.recordtime"))
		creatureObject:sendSystemMessage("@theme_park/racing/racing:current_record_holder")
		if recordTime == 0 then
			creatureObject:sendSystemMessage("No Time Set!")
		else
			creatureObject:sendSystemMessage(readStringSharedMemory("AGSWRT.recordholder") .. " with a time of " .. recordTime .. "s")
		end 		
	end)
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
		agrilatswap_racetrack_screenplay:startRace(conversingPlayer)
	elseif ( screenID == "cs_jsPlumb_1_181" ) then -- Personal Best
		agrilatswap_racetrack_screenplay:displayPersonalBestTime(conversingPlayer)
	elseif ( screenID == "cs_jsPlumb_1_207" ) then -- Track Best
		agrilatswap_racetrack_screenplay:displayTrackBestTime(conversingPlayer)
	end
	return conversationScreen
end  


