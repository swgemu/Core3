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
end

function JediPadawanTrialArchitechScreenPlay:notifyOkPressed(pCreature, sui, cancelPressed, arg0)
	JediPadawanTrial:initializeTrial(pCreature, SCREEN_PLAY_NAME, MOBILE, WAYPOINT_DESCRIPTION, ZONE_NAME, ZONE_COORDINATES)
end
