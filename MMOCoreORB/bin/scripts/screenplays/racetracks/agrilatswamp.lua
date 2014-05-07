local ObjectManager = require("managers.object.object_manager")
RaceTrackManager = require("screenplays.racetracks.racetrackengine")


agrilatswamp_racetrack_screenplay = RaceTrack:new {
	trackConfig={
	  debugMode=1, -- 0 = off, 1 = print debug messages
		planetName = "corellia", -- The planet the Track is on
		badgeToAward=BDG_RACING_AGRILAT_SWAMP,  -- Badge to be awarded for best daily time
		trackName="AGSWRT",  -- Internal trackname , should be unique to the track
		className="agrilatswamp_racetrack_screenplay", -- Class name of this class
		trackCheckpoint="@theme_park/racing/racing:agrilat_waypoint_name_checkpoint", --Waypoint names
		trackLaptime="@theme_park/racing/racing:agrilat_laptime_checkpoint", -- System message sent at each waypoint
		timeResolution=2, -- number of decimal places to use for the laptimes 0 = none, 1 = well 1 etc
		expiryTime = (1*3600), --Amount of time in seconds that a player will be expired from the track (stops silly times over this limit)
		resetTime = (22*3600)+(10*60), --Time of day in seconds that track resets High Scores
		waypointRadius=10, -- size of the waypoint observer
		raceCoordinator = {x=1680,y=4700,z=20}, -- Location of the race coordinator. Note the Z coord is VERY important
		waypoints = { {x = 1541, y = 4741}, -- The coords of the waypoints
					  {x = 1317, y = 5013},
					  {x = 1050, y = 5066},
					  {x = 805,  y = 4949},
					  {x = 597,  y = 4362},
					  {x = 602,  y = 4202},
					  {x = 688,  y = 3920},
					  {x = 976,  y = 3770},
					  {x = 922,  y = 4261},
					  {x = 1050, y = 4634},
					  {x = 1317, y = 4192},
					  {x = 1593, y = 4610},
					  {x = 1781, y = 4544},
					  {x = 1680, y = 4700}
					}
		}
}

registerScreenPlay("agrilatswamp_racetrack_screenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function agrilatswamp_racetrack_screenplay:start()
	if (isZoneEnabled(self.trackConfig.planetName)) then
		self:spawnMobiles()
		self:createRaceTrack()
	end
end

function agrilatswamp_racetrack_screenplay:spawnMobiles()
	local pCoord = spawnMobile(self.trackConfig.planetName, "agrilat_race_coordinator", 1, self.trackConfig.raceCoordinator.x, self.trackConfig.raceCoordinator.z, self.trackConfig.raceCoordinator.y, 35, 0 )
end

function agrilatswamp_racetrack_screenplay:enteredWaypoint(pActiveArea, pObject)
	self:processWaypoint(pActiveArea, pObject)
end

agrilat_swamp_racetrack_convo_handler = Object:new {}

function agrilat_swamp_racetrack_convo_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
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

function agrilat_swamp_racetrack_convo_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
  local screen = LuaConversationScreen(conversationScreen)
  local screenID = screen:getScreenID()
  if ( screenID == "cs_jsPlumb_1_116" ) then
    agrilatswamp_racetrack_screenplay:startRacing(conversingPlayer)
  elseif ( screenID == "cs_jsPlumb_1_181" ) then -- Personal Best
    agrilatswamp_racetrack_screenplay:displayPersonalBestTime(conversingPlayer)
  elseif ( screenID == "cs_jsPlumb_1_207" ) then -- Track Best
    agrilatswamp_racetrack_screenplay:displayTrackBestTime(conversingPlayer)
  end
  return conversationScreen
end



