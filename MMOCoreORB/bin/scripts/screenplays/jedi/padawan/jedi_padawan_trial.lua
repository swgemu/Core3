local ObjectManager = require("managers.object.object_manager")

-- Screenplays states:

--[[
0 - Has not started the quest.
1 - Has started the quest, has not accepted from giver.
2 - Accepted, not finished
4 - Quest Finished.
8 - Quest Passed.      
]]


-- Init
JediPadawanTrial = ScreenPlay:new {
	QuestNpcs = {
		{ "naboo", "kant_graf", -5632, 6, 4642, 240}, -- Architect
		{ "naboo", "sathme_forr", 4983, -192, 6634, 240} -- Artist
	},
	FIRST_MESSAGE = "",
	SECOND_MESSAGE = "",
	SCREEN_PLAY_NAME = "",
	ZONE_NAME = "",
	ZONE_REGION = "",
	WAYPOINT_DESCRIPTION = "",
	WAYPOINT_TITLE = "Jedi Trials"
}

registerScreenPlay("JediPadawanTrial", true)

function JediPadawanTrial:start()
	self:spawnMobiles() -- Spawning of global jedi trial npcs (non-objective).
end

function JediPadawanTrial:spawnMobiles()
	for i=1, #self.QuestNpcs, 1 do
		local mobile = self.QuestNpcs[i]
		local pMobile = spawnMobile(mobile[1], mobile[2], 0, mobile[3],  mobile[4],  mobile[5], mobile[6], 0)
		writeData("jedi:padawan:trials:" .. mobile[2] .. ":objectId", SceneObject(pMobile):getObjectID()) -- ObjectID
	end
end

function JediPadawanTrial:sendSuiNotification(pPlayer, mobileName)
	local objectID = readData("jedi:padawan:trials:" .. mobileName .. ":objectId") -- ObjectId
	local pMobile = getSceneObject(objectID)

	if (pMobile == nil) then
		printf("Could not find scene object mobile in JediPadawanTrial.")
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		PlayerObject(pGhost):addWaypoint(self.ZONE_NAME, self.WAYPOINT_TITLE, self.WAYPOINT_DESCRIPTION, CreatureObject(pMobile):getPositionX(), CreatureObject(pMobile):getPositionY(), WAYPOINT_COLOR_BLUE, true, true, WAYPOINTQUESTTASK)
		CreatureObject(pPlayer):setScreenPlayState(1, self.SCREEN_PLAY_NAME)
	end

	local msgPrefix = self.FIRST_MESSAGE .. "@jedi_trials:" .. self.ZONE_NAME
	local msgPostfix = self.SECOND_MESSAGE .. self.ZONE_REGION
	local msgFinal = msgPrefix .. " " .. msgPostfix

	local sui = SuiMessageBox.new(self.SCREEN_PLAY_NAME, "notifyOkPressedDoNothing") -- Needed or the Sui will crash
	sui.hideCancelButton()
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt(msgFinal)
	sui.sendTo(pPlayer)

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_tell_about_restart")
end

function JediPadawanTrial:showInfo(pPlayer, pObject)
	local sui = SuiMessageBox.new(self.SCREEN_PLAY_NAME, "handleShowInfoChoice")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setTargetNetworkId(SceneObject(pObject):getObjectID())
	sui.setCancelButtonText("@jedi_trials:button_abort_padawan") -- Quit Padawan Trials
	sui.setOtherButtonText("@jedi_trials:button_restart") -- Restart Current Trial
	sui.setOkButtonText("@jedi_trials:button_close") -- Close
	-- Other Button setup subscribe
	sui.setProperty("btnRevert", "OnPress", "RevertWasPressed=1\r\nparent.btnOk.press=t")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onClosedOk, "btnRevert", "RevertWasPressed")
	sui.setPrompt(self.WAYPOINT_DESCRIPTION)

	sui.sendTo(pPlayer)
end

function JediPadawanTrial:handleShowInfoChoice(pPlayer, pSui, eventIndex, ...)
	if (pPlayer == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)
	local args = {...}
	local restart = args[1]

	if (cancelPressed) then
		self:quitPadawanTrials(pPlayer)
	elseif (restart ~= nil) then
		self:restartCurrentPadawanTrial(pPlayer)
	else
		return
	end
end

function JediPadawanTrial:restartCurrentPadawanTrial(pPlayer)
	local sui = SuiMessageBox.new(self.SCREEN_PLAY_NAME, "jediPadawanTrialsRestartCallback")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt("@jedi_trials:padawan_trials_restart_confirmation")
	sui.sendTo(pPlayer)
end

function JediPadawanTrial:quitPadawanTrials(pPlayer)
	local sui = SuiMessageBox.new(self.SCREEN_PLAY_NAME, "jediPadawanTrialsAbortCallback")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt("@jedi_trials:padawan_trials_abort_confirmation")
	sui.sendTo(pPlayer)
end

function JediPadawanTrial:failCurrentTrial(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTQUESTTASK)
	writeScreenPlayData(pPlayer, "JediPadawanTrial", "CurrentTrial", 0)

	local currentState = CreatureObject(pPlayer):getScreenPlayState(self.SCREEN_PLAY_NAME)
	CreatureObject(pPlayer):removeScreenPlayState(self.SCREEN_PLAY_NAME, currentState)

	local failAmount = tonumber(readScreenPlayData(pPlayer, "JediPadawanTrial", "FailureAmount"))
	local failAmountMsg = nil

	if (failAmount == nil or failAmount == 0) then
		writeScreenPlayData(pPlayer, "JediPadawanTrial", "FailureAmount", 1)
		failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_first"
	elseif (failAmount == 1) then
		writeScreenPlayData(pPlayer, "JediPadawanTrial", "FailureAmount", 2)
		failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_second"
	elseif (failAmount == 2) then
		failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_final"
		deleteScreenPlayData(pPlayer, "JediPadawanTrial", "StartedTrials")
		deleteScreenPlayData(pPlayer, "JediPadawanTrial", "FailureAmount")
		self:resetAllTrials(pPlayer)
	end


	local sui = SuiMessageBox.new("JediPadawanTrial", "notifyOkPressedDoNothing")
	sui.hideCancelButton()
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt(failAmountMsg)
	sui.sendTo(pPlayer)
end

function JediPadawanTrial:notifyOkPressedDoNothing(pPlayer, sui, eventIndex, arg0)
-- Do nothing.
end

function JediPadawanTrial:passCurrentTrial(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local trialsCompleted = tonumber(readScreenPlayData(pPlayer, "JediPadawanTrial", "numOfTrialsCompleted"))

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_next_trial") -- You have done well and successfully completed the trial you faced. To undertake your next trial, simply meditate at any Force shrine.
	CreatureObject(pPlayer):setScreenPlayState(8, self.SCREEN_PLAY_NAME) -- Complete Trial.
	writeScreenPlayData(pPlayer, "JediPadawanTrial", "CurrentTrial", 0)
	writeScreenPlayData(pPlayer, "JediPadawanTrial", "numOfTrialsCompleted", trialsCompleted + 1)
	PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTQUESTTASK)

end

function JediPadawanTrial:jediPadawanTrialsRestartCallback(pPlayer, pSui, eventIndex, args)
	if (pPlayer == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_trial_restarted")
	local trialNumber = readScreenPlayData(pPlayer, "JediPadawanTrial", "CurrentTrial")
	local pScreenPlay = ForceShrineMenuComponent:getScreenPlayFromTable(tonumber(trialNumber))
	-- Reset the screenplaystate.
	local state = CreatureObject(pPlayer):getScreenPlayState(self.SCREEN_PLAY_NAME)
	CreatureObject(pPlayer):removeScreenPlayState(self.SCREEN_PLAY_NAME, state)

	pScreenPlay:startTrial(pPlayer)
end

function JediPadawanTrial:jediPadawanTrialsAbortCallback(pPlayer, pSui, eventIndex, args)
	if (pPlayer == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_aborted")
	self:resetAllTrials(pPlayer)

end

function JediPadawanTrial:resetAllTrials(pPlayer)
	--Remove All States.
	for i=1, #ForceShrineMenuComponent.PadawanTrialQuests, 1 do
		local state = CreatureObject(pPlayer):getScreenPlayState(ForceShrineMenuComponent.PadawanTrialQuests[i][1])
		CreatureObject(pPlayer):removeScreenPlayState(ForceShrineMenuComponent.PadawanTrialQuests[i][1], state)
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	deleteScreenPlayData(pPlayer, "JediPadawanTrial", "CurrentTrial")
	deleteScreenPlayData(pPlayer, "JediPadawanTrial", "FailureAmount")
	deleteScreenPlayData(pPlayer, "JediPadawanTrial", "StartedTrials")
	deleteScreenPlayData(pPlayer, "JediPadawanTrial", "numOfTrialsCompleted")
	PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTQUESTTASK)
end

function JediPadawanTrial:despawnNPC02(pCreature)
	if (pCreature ~= nil) then
		CreatureObject(pCreature):destroyObjectFromWorld()
	end
end


return JediPadawanTrial
