local ObjectManager = require("managers.object.object_manager")
local JediPadawanTrial = require("screenplays.jedi.padawan.jedi_padawan_trial")

FIRST_MESSAGE = "@jedi_trials:artist_01 "
SECOND_MESSAGE = "@jedi_trials:artist_02 "
SCREEN_PLAY_NAME = "JediPadawanTrialArtistScreenPlay"
MOBILE = "sathme_forr"
WAYPOINT_DESCRIPTION = "@jedi_trials:artist_03"
ZONE_NAME = "naboo"
ZONE_REGION = "Kaadara"
ZONE_COORDINATES = {x = 4983, y = 6634}

JediPadawanTrialArtistScreenPlay = JediPadawanTrial:new {
	numberOfActs = 1,

	screenplayName = SCREEN_PLAY_NAME,
}

registerScreenPlay(SCREEN_PLAY_NAME, false)

function JediPadawanTrialArtistScreenPlay:start(pCreature)
	JediPadawanTrial:sendSuiNotification(pCreature, FIRST_MESSAGE, SECOND_MESSAGE, SCREEN_PLAY_NAME, ZONE_NAME, ZONE_REGION)
	CreatureObject(pCreature):setScreenPlayState(1, "JediPadawanTrialArtistScreenPlay")
end

function JediPadawanTrialArtistScreenPlay:restart(pCreature)
	-- Clean up existing trials and set screenplaystate back to 1 (started).
	CreatureObject(pCreature):setScreenPlayState(1, "JediPadawanTrialArtistScreenPlay")
	JediPadawanTrial:sendSuiNotification(pCreature, FIRST_MESSAGE, SECOND_MESSAGE, SCREEN_PLAY_NAME, ZONE_NAME, ZONE_REGION)
end

function JediPadawanTrialArtistScreenPlay:initializeTrialCallback(pCreature, sui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	JediPadawanTrial:initializeTrial(pCreature, SCREEN_PLAY_NAME, MOBILE, WAYPOINT_DESCRIPTION, ZONE_NAME, ZONE_COORDINATES)
end

function JediPadawanTrialArtistScreenPlay:handleShowInfoChoice(pPlayer, pSui, eventIndex, ...)
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

function JediPadawanTrialArtistScreenPlay:startPart2(pCreature)
	local pNpc = spawnMobile(ZONE_NAME, "trials_ileeb_isonocra", 60, 5996, getTerrainHeight(pCreature, 5996, 5885), 5885, getRandomNumber(360) - 180, 0)

	if (pNpc ~= nil) then
		local ghost = CreatureObject(pCreature):getPlayerObject()
		PlayerObject(ghost):addWaypoint(ZONE_NAME, "Jedi Trials", WAYPOINT_DESCRIPTION, -7152, 4549, WAYPOINT_COLOR_BLUE, true, true, 0)
	end
end

function JediPadawanTrialArtistScreenPlay:despawnNPC02(pCreature)

	if (pCreature ~= nil) then
		CreatureObject(pCreature):destroyObjectFromWorld()
	end

end

function JediPadawanTrialArtistScreenPlay:showInfo(pCreature, pObject)
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

return JediPadawanTrialArtistScreenPlay
