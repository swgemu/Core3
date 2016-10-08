local ObjectManager = require("managers.object.object_manager")
RaceTrack = require("screenplays.racetracks.racetrackengine")


nashal_racetrack_screenplay = RaceTrack:new {
	trackConfig={
		debugMode = 0, -- 0 = off, 1 = print debug messages
		planetName = "talus", -- The planet the Track is on
		badgeToAward=BDG_RACING_NASHAL_RIVER,  -- Badge to be awarded for best daily time
		trackName="NASHALRT",  -- Internal trackname , should be unique to the track
		className="nashal_racetrack_screenplay", -- Class name of this class
		trackCheckpoint="@theme_park/racing/racing:nashal_waypoint_name_checkpoint", --Waypoint names
		trackLaptime="@theme_park/racing/racing:nashal_laptime_checkpoint", -- System message sent at each waypoint
		timeResolution=2, -- number of decimal places to use for the laptimes 0 = none, 1 = well 1 etc
		expiryTime = (1*3600), --Amount of time in seconds that a player will be expired from the track (stops silly times over this limit)
		resetTime = (22*3600)+(10*60), --Time of day in seconds that track resets High Scores
		waypointRadius=10, -- size of the waypoint observer
		raceCoordinator = {x=4199,y=5286,z=2}, -- Location of the race coordinator. Note the Z coord is VERY important or conversations break
		waypoints = { {x = 3787, y = 4764}, -- The coords of the waypoints
			{x = 3485, y = 4556},
			{x = 3042, y = 4565},
			{x = 2248, y = 5169},
			{x = 1839, y = 4966},
			{x = 1583, y = 5062},
			{x = 1499, y = 4802},
			{x = 1485, y = 4366},
			{x = 2248, y = 3905},
			{x = 1886, y = 3211},
			{x = 2448, y = 2457},
			{x = 2841, y = 2923},
			{x = 3670, y = 3475},
			{x = 4129, y = 3652},
			{x = 4511, y = 4054},
			{x = 4529, y = 4831},
			{x = 4199, y = 5286}
		}
	}
}

registerScreenPlay("nashal_racetrack_screenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function nashal_racetrack_screenplay:start()
	if (isZoneEnabled(self.trackConfig.planetName)) then
		self:spawnMobiles()
		self:createRaceTrack()
	end
end

function nashal_racetrack_screenplay:spawnMobiles()
	local pCoord = spawnMobile(self.trackConfig.planetName, "nashal_race_coordinator", 1, self.trackConfig.raceCoordinator.x, self.trackConfig.raceCoordinator.z, self.trackConfig.raceCoordinator.y, 35, 0)
end

function nashal_racetrack_screenplay:enteredWaypoint(pActiveArea, pObject)
	return self:processWaypoint(pActiveArea, pObject)
end

nashal_racetrack_convo_handler = conv_handler:new {}

function nashal_racetrack_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	if ( screenID == "cs_jsPlumb_1_116" ) then
		nashal_racetrack_screenplay:startRacing(pPlayer)
	elseif ( screenID == "cs_jsPlumb_1_181" ) then -- Personal Best
		nashal_racetrack_screenplay:displayPersonalBestTime(pPlayer)
	elseif ( screenID == "cs_jsPlumb_1_207" ) then -- Track Best
		nashal_racetrack_screenplay:displayTrackBestTime(pPlayer)
	end
	return pConvScreen
end
