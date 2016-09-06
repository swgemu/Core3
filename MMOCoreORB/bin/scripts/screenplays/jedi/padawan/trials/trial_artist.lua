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
	CreatureObject(pCreature):setScreenPlayState(1, "JediPadawanTrial")
end

function JediPadawanTrialArtistScreenPlay:notifyOkPressed(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)
	local revertPressed = (eventIndex == 2)
	local suiBox = LuaSuiBox(pSui)
	local suiUsingObject = suiBox:getUsingObject()

	if (cancelPressed) then
		JediPadawanTrial:restartCurrentPadawanTrial(suiUsingObject, pPlayer)
	elseif (revertPressed) then
		JediPadawanTrial:quitPadawanTrials(suiUsingObject, pPlayer)
	else
		JediPadawanTrial:initializeTrial(pPlayer, SCREEN_PLAY_NAME, MOBILE, WAYPOINT_DESCRIPTION, ZONE_NAME, ZONE_COORDINATES)
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

function JediPadawanTrialArtistScreenPlay:showInfo(pCreature)
	local msgPrefix = msg1 .. "@jedi_trials:" .. ZONE_NAME
	local msgPostfix = msg2 .. ZONE_REGION
	local msgFinal = msgPrefix .. " " .. msgPostfix

	local sui = SuiMessageBox.new("JediPadawanTrial", "notifyOkPressedDoNothing")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt(msgFinal)
	sui.sendTo(pCreature)
end

return JediPadawanTrialArtistScreenPlay
