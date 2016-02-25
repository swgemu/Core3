local ObjectManager = require("managers.object.object_manager")
local JediPadawanTrial = require("screenplays.jedi.padawan.jedi_padawan_trial")

FIRST_MESSAGE = "@jedi_trials:architect_01 "
SECOND_MESSAGE = "@jedi_trials:architect_02 "
SCREEN_PLAY_NAME = "JediPadawanTrialArchitechScreenPlay"
MOBILE = "kant_graf"
WAYPOINT_DESCRIPTION = "@jedi_trials:architect_03"
ZONE_NAME = "naboo"
ZONE_REGION = "Theed"
ZONE_COORDINATES = {x = -5632, y = 4642}

JediPadawanTrialArchitechScreenPlay = JediPadawanTrial:new {
	numberOfActs = 1,

	screenplayName = SCREEN_PLAY_NAME,
}

registerScreenPlay(SCREEN_PLAY_NAME, false)

function JediPadawanTrialArchitechScreenPlay:start(pCreature)
	JediPadawanTrial:sendSuiNotification(pCreature, FIRST_MESSAGE, SECOND_MESSAGE, SCREEN_PLAY_NAME, ZONE_NAME, ZONE_REGION)
	CreatureObject(pCreature):setScreenPlayState(1, "trials:padawan:currentTrial")
end

function JediPadawanTrialArchitechScreenPlay:notifyOkPressed(pCreature, sui, cancelPressed, arg0)
	JediPadawanTrial:initializeTrial(pCreature, SCREEN_PLAY_NAME, MOBILE, WAYPOINT_DESCRIPTION, ZONE_NAME, ZONE_COORDINATES)
end

function JediPadawanTrialArchitechScreenPlay:startPart2(pCreature)
	local pNpc = spawnMobile("naboo", "trials_gungan_captain", 60, -7152, getTerrainHeight(pCreature, -7152, 4549), 4549, getRandomNumber(360) - 180, 0)
	
	if (pNpc ~= nil) then
		local ghost = CreatureObject(pCreature):getPlayerObject()
		PlayerObject(ghost):addWaypoint("naboo", "Jedi Trials", WAYPOINT_DESCRIPTION, -7152, 4549, WAYPOINT_COLOR_BLUE, true, true, 0)
	end
end

function JediPadawanTrialArchitechScreenPlay:despawnNPC02(pCreature)

if (pCreature ~= nil) then
				CreatureObject(pCreature):destroyObjectFromWorld()
end

end