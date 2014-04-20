local ObjectManager = require("managers.object.object_manager")
RaceTrack = require("screenplays.racetracks.racetrackengine")


lok_racetrack_screenplay = RaceTrack:new {
	trackConfig={
	  debugMode=1, -- 0 = off, 1 = print debug messages
		planetName = "lok", -- The planet the Track is on
		badgeToAward=BDG_RACING_LOK_MARATHON,  -- Badge to be awarded for best daily time
		trackName="LOKRT",  -- Internal trackname , should be unique to the track
		className="lok_racetrack_screenplay", -- Class name of this class
		trackCheckpoint="@theme_park/racing/racing:lok_waypoint_name_checkpoint", --Waypoint names
		trackLaptime="@theme_park/racing/racing:lok_laptime_checkpoint", -- System message sent at each waypoint
		timeResolution=2, -- number of decimal places to use for the laptimes 0 = none, 1 = well 1 etc
		expiryTime = (1*3600), --Amount of time in seconds that a player will be expired from the track (stops silly times over this limit)
    resetTime = (22*3600)+(10*60), --Time of day in seconds that track resets High Scores
		waypointRadius=10, -- size of the waypoint observer
		raceCoordinator = {x=630,y=5055,z=12.7}, -- Location of the race coordinator. Note the Z coord is VERY important or conversations break
		waypoints = { {x = 946, y = 4634}, -- The coords of the waypoints
					  {x = 1065, y = 3156},
					  {x = 3828, y = -532},
					  {x = 3337, y = -2425},
					  {x = 3364, y = -3819},
					  {x = 2962, y = -4546},
					  {x = 3080, y = -4671},
					  {x = 3009, y = -4798},
					  {x = 2893, y = -4782},
					  {x = 2744, y = -4458},
					  {x = 509, y = -2924},
					  {x = -497, y = -624},
					  {x = 427, y = 705},
					  {x = 838, y = 2738},
					  {x = -19, y = 4059},
					  {x = -26, y = 4558},
					  {x = 275, y = 5073},
					  {x = 630, y = 5055}
					}
		}
}

registerScreenPlay("lok_racetrack_screenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function lok_racetrack_screenplay:start()
	if (isZoneEnabled(self.trackConfig.planetName)) then
		self:spawnMobiles()
		self:createRaceTrack()
	end
end

function lok_racetrack_screenplay:spawnMobiles()
	local pCoord = spawnMobile(self.trackConfig.planetName, "lok_race_coordinator", 1, self.trackConfig.raceCoordinator.x, self.trackConfig.raceCoordinator.z, self.trackConfig.raceCoordinator.y, 35, 0)
end

function lok_racetrack_screenplay:enteredWaypoint(pActiveArea, pObject)
	self:processWaypoint(pActiveArea, pObject)
end

lok_racetrack_convo_handler = Object:new {}

function lok_racetrack_convo_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
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

function lok_racetrack_convo_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	if ( screenID == "cs_jsPlumb_1_116" ) then
		lok_racetrack_screenplay:startRacing(conversingPlayer)
	elseif ( screenID == "cs_jsPlumb_1_181" ) then -- Personal Best
		lok_racetrack_screenplay:displayPersonalBestTime(conversingPlayer)
	elseif ( screenID == "cs_jsPlumb_1_207" ) then -- Track Best
		lok_racetrack_screenplay:displayTrackBestTime(conversingPlayer)
	end
	return conversationScreen
end
