local ObjectManager = require("managers.object.object_manager")
RaceTrack = require("screenplays.racetracks.racetrackengine")


keren_racetrack_screenplay = RaceTrack:new {
	trackConfig={
		debugMode=1, -- 0 = off, 1 = print debug messages
		planetName = "naboo", -- The planet the Track is on
		badgeToAward=BDG_RACING_KEREN_CITY,  -- Badge to be awarded for best daily time
		trackName="KERENRT",  -- Internal trackname , should be unique to the track
		className="keren_racetrack_screenplay", -- Class name of this class
		trackCheckpoint="@theme_park/racing/racing:keren_waypoint_name_checkpoint", --Waypoint names
		trackLaptime="@theme_park/racing/racing:keren_laptime_checkpoint", -- System message sent at each waypoint
		timeResolution=2, -- number of decimal places to use for the laptimes 0 = none, 1 = well 1 etc
		expiryTime = (1*3600), --Amount of time in seconds that a player will be expired from the track (stops silly times over this limit)
		resetTime = (22*3600)+(10*60), --Time of day in seconds that track resets High Scores
		waypointRadius=10, -- size of the waypoint observer
		raceCoordinator = {x=1396,y=2686,z=13}, -- Location of the race coordinator. Note the Z coord is VERY important or conversations break
		waypoints = { {x = 1518, y = 2732}, -- The coords of the waypoints
			{x = 1607, y = 2705},
			{x = 1864, y = 2709},
			{x = 1932, y = 2707},
			{x = 1805, y = 2493},
			{x = 1900, y = 2614},
			{x = 1990, y = 2683},
			{x = 1996, y = 2798},
			{x = 1813, y = 2809},
			{x = 1663, y = 2785},
			{x = 1396, y = 2686}
		}
	}
}

registerScreenPlay("keren_racetrack_screenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function keren_racetrack_screenplay:start()
	if (isZoneEnabled(self.trackConfig.planetName)) then
		self:spawnMobiles()
		self:createRaceTrack()
	end
end

function keren_racetrack_screenplay:spawnMobiles()
	local pCoord = spawnMobile(self.trackConfig.planetName, "keren_race_coordinator", 1, self.trackConfig.raceCoordinator.x, self.trackConfig.raceCoordinator.z, self.trackConfig.raceCoordinator.y, 35, 0)
end

function keren_racetrack_screenplay:enteredWaypoint(pActiveArea, pObject)
	return self:processWaypoint(pActiveArea, pObject)
end

keren_racetrack_convo_handler = Object:new {}

function keren_racetrack_convo_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
	local convosession = CreatureObject(conversingPlayer):getConversationSession()
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
end

function keren_racetrack_convo_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	if ( screenID == "cs_jsPlumb_1_116" ) then
		keren_racetrack_screenplay:startRacing(conversingPlayer)
	elseif ( screenID == "cs_jsPlumb_1_181" ) then -- Personal Best
		keren_racetrack_screenplay:displayPersonalBestTime(conversingPlayer)
	elseif ( screenID == "cs_jsPlumb_1_207" ) then -- Track Best
		keren_racetrack_screenplay:displayTrackBestTime(conversingPlayer)
	end
	return conversationScreen
end


