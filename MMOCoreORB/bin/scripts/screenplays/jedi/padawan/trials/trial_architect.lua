local ObjectManager = require("managers.object.object_manager")
local JediPadawanTrial = require("screenplays.jedi.padawan.jedi_padawan_trial")

FIRST_MESSAGE = "@jedi_trials:architect_01 "
SECOND_MESSAGE = "@jedi_trials:architect_02 "
SCREEN_PLAY_NAME = "JediPadawanTrialArchitechScreenPlay"

ZONE_NAME = "naboo"
ZONE_REGION = "Theed"
WAYPOINT_DESCRIPTION = "@jedi_trials:architect_03"

MOBILE = "kant_graf"
ZONE_COORDINATES = {x = -5632, y = 4642}

TARGET_MOBILE = "trials_gungan_captain"
TARGET_COORDINATES = {x = -7152, y = 4549}

JediPadawanTrialArchitechScreenPlay = JediPadawanTrial:new {
	numberOfActs = 1,

	screenplayName = SCREEN_PLAY_NAME,
}

registerScreenPlay(SCREEN_PLAY_NAME, false)

function JediPadawanTrialArchitechScreenPlay:start(pCreature)
	JediPadawanTrial:sendSuiNotification(pCreature, FIRST_MESSAGE, SECOND_MESSAGE, SCREEN_PLAY_NAME, ZONE_NAME, ZONE_REGION)
	CreatureObject(pCreature):setScreenPlayState(1, "JediPadawanTrialArchitechScreenPlay")
end

function JediPadawanTrialArchitechScreenPlay:restart(pCreature)
	-- Clean up existing trials and set screenplaystate back to 1 (started).
	CreatureObject(pCreature):setScreenPlayState(1, "JediPadawanTrialArchitechScreenPlay")
	JediPadawanTrial:sendSuiNotification(pCreature, FIRST_MESSAGE, SECOND_MESSAGE, SCREEN_PLAY_NAME, ZONE_NAME, ZONE_REGION)
end

function JediPadawanTrialArchitechScreenPlay:initializeTrialCallback(pCreature, sui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	JediPadawanTrial:initializeTrial(pCreature, SCREEN_PLAY_NAME, MOBILE, WAYPOINT_DESCRIPTION, ZONE_NAME, ZONE_COORDINATES)
end

function JediPadawanTrialArchitechScreenPlay:handleShowInfoChoice(pPlayer, pSui, eventIndex, ...)
	local closePressed = (eventIndex == 1)
	local args = {...}
	local restart = args[1]

	if (closePressed) then
		JediPadawanTrial:quitPadawanTrials(pPlayer)
	elseif (restart ~= nil) then
		JediPadawanTrial:restartCurrentPadawanTrial(pPlayer)
	else
		return
	end
end

function JediPadawanTrialArchitechScreenPlay:startPart2(pCreature)
	local pNpc = spawnMobile(ZONE_NAME, TARGET_MOBILE, 0, TARGET_COORDINATES.x, getTerrainHeight(pCreature, TARGET_COORDINATES.x, TARGET_COORDINATES.y), TARGET_COORDINATES.y, getRandomNumber(180) - 180, 0)

	if (pNpc ~= nil) then
		local ghost = CreatureObject(pCreature):getPlayerObject()
		PlayerObject(ghost):addWaypoint(ZONE_NAME, "Jedi Trials", WAYPOINT_DESCRIPTION, TARGET_COORDINATES.x, TARGET_COORDINATES.y, WAYPOINT_COLOR_BLUE, true, true, 0)
	end
end

function JediPadawanTrialArchitechScreenPlay:despawnNPC02(pCreature)

	if (pCreature ~= nil) then
		CreatureObject(pCreature):destroyObjectFromWorld()
	end

end

function JediPadawanTrialArchitechScreenPlay:showInfo(pCreature, pObject)
	local msgPrefix = FIRST_MESSAGE .. "@jedi_trials:" .. ZONE_NAME
	local msgPostfix = SECOND_MESSAGE .. ZONE_REGION
	local msgFinal = msgPrefix .. " " .. msgPostfix

	local sui = SuiMessageBox.new(SCREEN_PLAY_NAME, "handleShowInfoChoice")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setTargetNetworkId(SceneObject(pObject):getObjectID())
	sui.setCancelButtonText("@jedi_trials:button_abort_padawan") -- Quit Padawan Trials
	sui.setOtherButtonText("@jedi_trials:button_restart") -- Restart Current Trial
	sui.setOkButtonText("@jedi_trials:button_close") -- Close
	-- Other Button setup subscribe
	sui.setProperty("btnRevert", "OnPress", "RevertWasPressed=1\r\nparent.btnOk.press=t")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onClosedOk, "btnRevert", "RevertWasPressed")
	sui.setPrompt(msgFinal)

	sui.sendTo(pCreature)
end

return JediPadawanTrialArchitechScreenPlay
