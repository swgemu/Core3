local ObjectManager = require("managers.object.object_manager")
RaceTrackManager = require("screenplays.racetracks.racetrackengine")


mosespa_racetrack_screenplay = RaceTrack:new {
	trackConfig={
		debugMode = 0, -- 0 = off, 1 = print debug messages
		planetName = "tatooine", -- The planet the Track is on
		badgeToAward=BDG_RACING_MOS_ESPA,  -- Badge to be awarded for best daily time
		trackName="MESPART",  -- Internal trackname , should be unique to the track
		className="mosespa_racetrack_screenplay", -- Class name of this class
		trackCheckpoint="@theme_park/racing/racing:waypoint_name_checkpoint", --Waypoint names
		trackLaptime="@theme_park/racing/racing:laptime_checkpoint", -- System message sent at each waypoint
		timeResolution=2, -- number of decimal places to use for the laptimes 0 = none, 1 = well 1 etc
		expiryTime = (1*3600), --Amount of time in seconds that a player will be expired from the track (stops silly times over this limit)
		resetTime = (22*3600)+(10*60), --Time of day in seconds that track resets High Scores
		waypointRadius=10, -- size of the waypoint observer
		raceCoordinator = {x=2400,y=5000,z=2}, -- Location of the race coordinator. Note the Z coord is VERY important
		waypoints = { {x = 1943, y = 4792}, -- The coords of the waypoints
			{x = 1546, y = 4959},
			{x = 1316, y = 5434},
			{x = 688,  y = 5439},
			{x = 156,  y = 5326},
			{x = -414,  y = 5090},
			{x = -664, y = 4832},
			{x = -769, y = 4340},
			{x = -710, y = 3993},
			{x = 81,   y = 4092},
			{x = 594,  y = 4284},
			{x = 917,  y = 3841},
			{x = 1333,  y = 4457},
			{x = 1630, y = 4326},
			{x = 2132, y = 4346},
			{x = 2400, y = 5000}
		}
	}
}

registerScreenPlay("mosespa_racetrack_screenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function mosespa_racetrack_screenplay:start()
	if (isZoneEnabled(self.trackConfig.planetName)) then
		self:spawnMobiles()
		self:createRaceTrack()
	end
end

function mosespa_racetrack_screenplay:spawnMobiles()
	local pCoord = spawnMobile(self.trackConfig.planetName, "mosespa_race_coordinator", 1, self.trackConfig.raceCoordinator.x, self.trackConfig.raceCoordinator.z, self.trackConfig.raceCoordinator.y, 35, 0 )
end

function mosespa_racetrack_screenplay:enteredWaypoint(pActiveArea, pObject)
	return self:processWaypoint(pActiveArea, pObject)
end

mosespa_racetrack_convo_handler = conv_handler:new {}

function mosespa_racetrack_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	if ( screenID == "cs_jsPlumb_1_116" ) then
		mosespa_racetrack_screenplay:startRacing(pPlayer)
	elseif ( screenID == "cs_jsPlumb_1_181" ) then -- Personal Best
		mosespa_racetrack_screenplay:displayPersonalBestTime(pPlayer)
	elseif ( screenID == "cs_jsPlumb_1_207" ) then -- Track Best
		mosespa_racetrack_screenplay:displayTrackBestTime(pPlayer)
	end
	return pConvScreen
end
