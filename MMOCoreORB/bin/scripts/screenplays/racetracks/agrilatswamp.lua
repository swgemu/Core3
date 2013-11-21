local ObjectManager = require("managers.object.object_manager")
RaceTrackManager = require("screenplays.racetracks.racetrackengine")


agrilatswap_racetrack_screenplay = ScreenPlay:new {
	numberOfActs = 1,
	
	states = {
	},
	trackConfig={
		planetName = "corellia",
		badgeToAward=BDG_RACING_AGRILAT_SWAMP,
		trackName="AGSWRT",
		trackCheckpoint="@theme_park/racing/racing:agrilat_waypoint_name_checkpoint",
		trackLaptime="@theme_park/racing/racing:agrilat_laptime_checkpoint",
		waypointRadius=25,
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
}

registerScreenPlay("agrilatswap_racetrack_screenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function agrilatswap_racetrack_screenplay:start()
	if (isZoneEnabled(self.trackConfig.planetName)) then
		self:spawnMobiles()
		self:spawnObservers()
		printf("Launching agrilat\n")
	end
end

function agrilatswap_racetrack_screenplay:spawnMobiles()
	local pCoord = spawnMobile(self.trackConfig.planetName, "agrilat_race_coordinator", 1, 1680, 20.0, 4700, 35, 0 )
end

function agrilatswap_racetrack_screenplay:spawnObservers()
	RaceTrackManager:createRaceTrack(self.trackConfig)
end
function agrilatswap_racetrack_screenplay:startRace(pObject)
	RaceTrackManager:saveVariablesToScreenPlay(pObject,self.trackConfig)
	RaceTrackManager:spawnFirstWaypoint(pObject)
end
function agrilatswap_racetrack_screenplay:displayPersonalBestTime(pObject)
	RaceTrackManager:displayPersonalBestTime(pObject,self.trackConfig)
end

function agrilatswap_racetrack_screenplay:displayTrackBestTime(pObject)
	RaceTrackManager:displayTrackBestTime(pObject,self.trackConfig)
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


