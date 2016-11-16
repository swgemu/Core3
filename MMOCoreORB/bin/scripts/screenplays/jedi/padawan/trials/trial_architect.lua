JediPadawanTrialArchitectScreenPlay = JediPadawanTrial:new {
	FIRST_MESSAGE = "@jedi_trials:architect_01 ",
	SECOND_MESSAGE = "@jedi_trials:architect_02 ",
	SCREEN_PLAY_NAME = "JediPadawanTrialArchitectScreenPlay",

	ZONE_NAME = "naboo",
	ZONE_REGION = "Theed",
	WAYPOINT_DESCRIPTION = "@jedi_trials:architect_03",

	MOBILE = "kant_graf",
	ZONE_COORDINATES = {x = -5632, y = 4642},

	TARGET_MOBILE = "trials_gungan_captain",
	TARGET_COORDINATES = {x = -7152, y = 4549},

	screenplayName = "JediPadawanTrialArchitectScreenPlay"
}

registerScreenPlay(JediPadawanTrialArchitectScreenPlay.SCREEN_PLAY_NAME, false)

function JediPadawanTrialArchitectScreenPlay:start(pCreature)
	if (pCreature ~= nil) then
		JediPadawanTrial:sendSuiNotification(pCreature, self.FIRST_MESSAGE, self.SECOND_MESSAGE, self.SCREEN_PLAY_NAME, self.ZONE_NAME, self.ZONE_REGION)
		CreatureObject(pCreature):setScreenPlayState(1, "JediPadawanTrialArchitectScreenPlay")
	end
end

function JediPadawanTrialArchitectScreenPlay:restart(pCreature)
	if (pCreature ~= nil) then
		-- Clean up existing trials and set screenplaystate back to 1 (started).
		CreatureObject(pCreature):setScreenPlayState(1, "JediPadawanTrialArchitectScreenPlay")
		JediPadawanTrial:sendSuiNotification(pCreature, self.FIRST_MESSAGE, self.SECOND_MESSAGE, self.SCREEN_PLAY_NAME, self.ZONE_NAME, self.ZONE_REGION)
	end
end

function JediPadawanTrialArchitectScreenPlay:initializeTrialCallback(pCreature, sui, eventIndex, args)
	if (pCreature == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	JediPadawanTrial:initializeTrial(pCreature, self.SCREEN_PLAY_NAME, self.MOBILE, self.WAYPOINT_DESCRIPTION, self.ZONE_NAME, self.ZONE_COORDINATES)
end

function JediPadawanTrialArchitectScreenPlay:handleShowInfoChoice(pPlayer, pSui, eventIndex, ...)
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

function JediPadawanTrialArchitectScreenPlay:startPart2(pCreature)
	local pNpc = spawnMobile(self.ZONE_NAME, self.TARGET_MOBILE, 0, self.TARGET_COORDINATES.x, getTerrainHeight(pCreature, self.TARGET_COORDINATES.x, self.TARGET_COORDINATES.y), self.TARGET_COORDINATES.y, getRandomNumber(180) - 180, 0)

	if (pNpc ~= nil) then
		local pGhost = CreatureObject(pCreature):getPlayerObject()
		if (pGhost ~= nil) then
			PlayerObject(ghost):addWaypoint(self.ZONE_NAME, "Jedi Trials", self.WAYPOINT_DESCRIPTION, self.TARGET_COORDINATES.x, self.TARGET_COORDINATES.y, WAYPOINT_COLOR_BLUE, true, true, 0)
		end
	end
end

function JediPadawanTrialArchitectScreenPlay:despawnNPC02(pCreature)
	if (pCreature ~= nil) then
		CreatureObject(pCreature):destroyObjectFromWorld()
	end

end

function JediPadawanTrialArchitectScreenPlay:showInfo(pCreature, pObject)
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

return JediPadawanTrialArchitectScreenPlay
