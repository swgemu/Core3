local ObjectManager = require("managers.object.object_manager")
RaceTrackManager = require("screenplays.racetracks.racetrackengine")


mosespa_racetrack_screenplay = RaceTrack:new {
	trackConfig={
		planetName = "tatooine", -- The planet the Track is on
		badgeToAward=BDG_RACING_MOS_ESPA,  -- Badge to be awarded for best daily time
		trackName="MESPART",  -- Internal trackname , should be unique to the track
		trackCheckpoint="@theme_park/racing/racing:waypoint_name_checkpoint", --Waypoint names
		trackLaptime="@theme_park/racing/racing:laptime_checkpoint", -- System message sent at each waypoint
		waypointRadius=25, -- size of the waypoint observer
		raceCoordinator = {x=2380,y=5000,z=2}, -- Location of the race coordinator. Note the Z coord is VERY important
		waypoints = { {x = 1980, y = 4823}, -- The coords of the waypoints
					  {x = 1540, y = 4984},
					  {x = 1364, y = 5429},
					  {x = 709,  y = 5429},
					  {x = 167,  y = 5330},
					  {x = 416,  y = 5077},
					  {x = -672, y = 4842},
					  {x = -770, y = 4327},
					  {x = -717, y = 3993},
					  {x = 64,   y = 4074},
					  {x = 602,  y = 4293},
					  {x = 926,  y = 3853},
					  {x = 133,  y = 4469},
					  {x = 1637, y = 4336},
					  {x = 2136, y = 4344},
					  {x = 2380, y = 5000}
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
		self:createRaceTrack("mosespa_racetrack_screenplay")
	end
end

function mosespa_racetrack_screenplay:spawnMobiles()
	local pCoord = spawnMobile(self.trackConfig.planetName, "mosespa_race_coordinator", 1, self.trackConfig.raceCoordinator.x, self.trackConfig.raceCoordinator.z, self.trackConfig.raceCoordinator.y, 35, 0 )
end

function mosespa_racetrack_screenplay:enteredWaypoint(pActiveArea, pObject)
	self:processWaypoint(pActiveArea, pObject)
end

mosespa_conversationtemplate = Object:new {}

function mosespa_conversationtemplate:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
	return ObjectManager.withCreatureObject(conversingPlayer, function(creatureObject)
		local convosession = creatureObject:getConversationSession()
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
	end)
end

function mosespa_conversationtemplate:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	if ( screenID == "cs_jsPlumb_1_116" ) then
		mosespa_racetrack_screenplay:startRacing(conversingPlayer)
	elseif ( screenID == "cs_jsPlumb_1_181" ) then -- Personal Best
		mosespa_racetrack_screenplay:displayPersonalBestTime(conversingPlayer)
	elseif ( screenID == "cs_jsPlumb_1_207" ) then -- Track Best
		mosespa_racetrack_screenplay:displayTrackBestTime(conversingPlayer)
	end
	return conversationScreen
end


