local ObjectManager = require("managers.object.object_manager")
RaceTrack = require("screenplays.racetracks.racetrackengine")


narmle_racetrack_screenplay = RaceTrack:new {
	trackConfig={
    debugMode=1, -- 0 = off, 1 = print debug messages
		planetName = "rori", -- The planet the Track is on
		badgeToAward=BDG_RACING_NARMLE_MEMORIAL,  -- Badge to be awarded for best daily time
		trackName="NARMLERT",  -- Internal trackname , should be unique to the track
		className="narmle_racetrack_screenplay", -- Class name of this class
		trackCheckpoint="@theme_park/racing/racing:narmle_waypoint_name_checkpoint", --Waypoint names
		trackLaptime="@theme_park/racing/racing:narmle_laptime_checkpoint", -- System message sent at each waypoint
		timeResolution=2, -- number of decimal places to use for the laptimes 0 = none, 1 = well 1 etc
		expiryTime = (1*3600), --Amount of time in seconds that a player will be expired from the track (stops silly times over this limit)
    resetTime = (22*3600)+(10*60), --Time of day in seconds that track resets High Scores
		waypointRadius=10, -- size of the waypoint observer
		raceCoordinator = {x=-4975,y=-2227,z=79.9}, -- Location of the race coordinator. Note the Z coord is VERY important or conversations break
		waypoints = { {x = -4987, y = -2417}, -- The coords of the waypoints
					  {x = -5031, y = -2425},
					  {x = -5081, y = -2393},
					  {x = -5172, y = -2398},
					  {x = -5222, y = -2317},
					  {x = -5149, y = -2286},
					  {x = -5114, y = -2254},
					  {x = -5148, y = -2274},
					  {x = -5186, y = -2216},
					  {x = -5328, y = -2093},
					  {x = -5441, y = -2098},
					  {x = -5529, y = -2137},
					  {x = -5475, y = -2348},
					  {x = -5205, y = -2614},
					  {x = -4995, y = -2484},
					  {x = -4975, y = -2227}
					}
		}
}

registerScreenPlay("narmle_racetrack_screenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function narmle_racetrack_screenplay:start()
	if (isZoneEnabled(self.trackConfig.planetName)) then
		self:spawnMobiles()
		self:createRaceTrack()
	end
end

function narmle_racetrack_screenplay:spawnMobiles()
	local pCoord = spawnMobile(self.trackConfig.planetName, "narmle_race_coordinator", 1, self.trackConfig.raceCoordinator.x, self.trackConfig.raceCoordinator.z, self.trackConfig.raceCoordinator.y, 35, 0)
end

function narmle_racetrack_screenplay:enteredWaypoint(pActiveArea, pObject)
	return self:processWaypoint(pActiveArea, pObject)
end

narmle_racetrack_convo_handler = Object:new {}

function narmle_racetrack_convo_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
	return ObjectManager.withCreatureObject(conversingPlayer, function(creatureObject)
		local convosession = creatureObject:getConversationSession()
		local lastConversationScreen = nil
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
	end)
end

function narmle_racetrack_convo_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	if ( screenID == "cs_jsPlumb_1_116" ) then
		narmle_racetrack_screenplay:startRacing(conversingPlayer)
	elseif ( screenID == "cs_jsPlumb_1_181" ) then -- Personal Best
		narmle_racetrack_screenplay:displayPersonalBestTime(conversingPlayer)
	elseif ( screenID == "cs_jsPlumb_1_207" ) then -- Track Best
		narmle_racetrack_screenplay:displayTrackBestTime(conversingPlayer)
	end
	return conversationScreen
end
