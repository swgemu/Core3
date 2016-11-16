JediPadawanTrialArtistScreenPlay = JediPadawanTrial:new {
	FIRST_MESSAGE = "@jedi_trials:artist_01 ",
	SECOND_MESSAGE = "@jedi_trials:artist_02 ",
	SCREEN_PLAY_NAME = "JediPadawanTrialArtistScreenPlay",

	ZONE_NAME = "naboo",
	ZONE_REGION = "Kaadara",
	WAYPOINT_DESCRIPTION = "@jedi_trials:artist_03",

	MOBILE = "sathme_forr",
	ZONE_COORDINATES = {x = 4983, y = 6634},

	TARGET_MOBILE = "trials_artist_contact",
	TARGET_COORDINATES = {x = 5996, y = 5885},

	screenplayName = "JediPadawanTrialArtistScreenPlay",
}

registerScreenPlay(JediPadawanTrialArtistScreenPlay.SCREEN_PLAY_NAME, false)

function JediPadawanTrialArtistScreenPlay:start(pCreature)
	if (pCreature ~= nil) then
		JediPadawanTrial:sendSuiNotification(pCreature, self.FIRST_MESSAGE, self.SECOND_MESSAGE, self.SCREEN_PLAY_NAME, self.ZONE_NAME, self.ZONE_REGION)
		CreatureObject(pCreature):setScreenPlayState(1, "JediPadawanTrialArtistScreenPlay")
	end
end

function JediPadawanTrialArtistScreenPlay:restart(pCreature)
	if (pCreature ~= nil) then
		-- Clean up existing trials and set screenplaystate back to 1 (started).
		CreatureObject(pCreature):setScreenPlayState(1, "JediPadawanTrialArtistScreenPlay")
		JediPadawanTrial:sendSuiNotification(pCreature, self.FIRST_MESSAGE, self.SECOND_MESSAGE, self.SCREEN_PLAY_NAME, self.ZONE_NAME, self.ZONE_REGION)
	end
end

function JediPadawanTrialArtistScreenPlay:initializeTrialCallback(pCreature, sui, eventIndex, args)
	if (pCreature == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	JediPadawanTrial:initializeTrial(pCreature, self.SCREEN_PLAY_NAME, self.MOBILE, self.WAYPOINT_DESCRIPTION, self.ZONE_NAME, self.ZONE_COORDINATES)
end

function JediPadawanTrialArtistScreenPlay:handleShowInfoChoice(pPlayer, pSui, eventIndex, ...)
	if (pPlayer == nil) then
		return
	end

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
	local pNpc = spawnMobile(self.ZONE_NAME, self.TARGET_MOBILE, 0, self.TARGET_COORDINATES.x, getTerrainHeight(pCreature, self.TARGET_COORDINATES.x, self.TARGET_COORDINATES.y), self.y, getRandomNumber(180) - 180, 0)

	if (pNpc ~= nil) then
		local pGhost = CreatureObject(pCreature):getPlayerObject()
		if (pGhost ~= nil) then
			PlayerObject(pGhost):addWaypoint(self.ZONE_NAME, "Jedi Trials", self.WAYPOINT_DESCRIPTION, self.TARGET_COORDINATES.x, self.TARGET_COORDINATES.y, WAYPOINT_COLOR_BLUE, true, true, 0)
		end
	end
end

function JediPadawanTrialArtistScreenPlay:despawnNPC02(pCreature)

	if (pCreature ~= nil) then
		CreatureObject(pCreature):destroyObjectFromWorld()
	end

end

function JediPadawanTrialArtistScreenPlay:showInfo(pCreature, pObject)
	if (pCreature ==  nil) then
		return
	end

	local msgPrefix = self.FIRST_MESSAGE .. "@jedi_trials:" .. self.ZONE_NAME
	local msgPostfix = self.SECOND_MESSAGE .. self.ZONE_REGION
	local msgFinal = msgPrefix .. " " .. msgPostfix

	local sui = SuiMessageBox.new(self.SCREEN_PLAY_NAME, "handleShowInfoChoice")
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
