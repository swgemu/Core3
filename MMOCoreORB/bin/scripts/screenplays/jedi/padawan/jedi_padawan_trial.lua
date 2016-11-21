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
		{ "naboo", "kant_graf", -5632, 78, 4642, 240}, -- Architect 1
		{ "naboo", "trials_gungan_captain", -7152, 78, 4549, 240}, -- Architect 2
		{ "naboo", "sathme_forr", 4983, 78, 6634, 240}, -- Artist 1
		{ "naboo", "trials_artist_contact", 5996, 78, 5585, 240} -- Artist 2
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
	self:spawnMobiles() -- Spawning of global jedi trial npcs (non-killable).
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
		PlayerObject(pGhost):addWaypoint(self.ZONE_NAME, self.WAYPOINT_TITLE, self.WAYPOINT_DESCRIPTION, CreatureObject(pMobile):getPositionX(), CreatureObject(pMobile):getPositionY(), WAYPOINT_COLOR_BLUE, true, true, 0)
		CreatureObject(pPlayer):setScreenPlayState(1, self.SCREEN_PLAY_NAME)
	end

	local msgPrefix = self.FIRST_MESSAGE .. "@jedi_trials:" .. self.ZONE_NAME
	local msgPostfix = self.SECOND_MESSAGE .. self.ZONE_REGION
	local msgFinal = msgPrefix .. " " .. msgPostfix

	local sui = SuiMessageBox.new(self.SCREEN_PLAY_NAME, "notifyOkPressedDoNothing") -- Needed or the Sui will crash
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt(msgFinal)
	sui.sendTo(pPlayer)

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_tell_about_restart")
end

function JediPadawanTrialArchitectScreenPlay:showInfo(pPlayer, pObject)
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
	local sui = SuiMessageBox.new("JediPadawanTrial", "jediPadawanTrialsRestartCallback")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt("@jedi_trials:padawan_trials_restart_confirmation")
	sui.sendTo(pPlayer)
end

function JediPadawanTrial:quitPadawanTrials(pPlayer)
	local sui = SuiMessageBox.new("JediPadawanTrial", "jediPadawanTrialsAbortCallback")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt("@jedi_trials:padawan_trials_abort_confirmation")
	sui.sendTo(pPlayer)
end

function JediPadawanTrial:failCurrentTrial(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local objectID = SceneObject(pPlayer):getObjectID()

	local failAmount = readScreenPlayData(pPlayer, "JediPadawanTrial", "FailureAmount")
	local failAmountMsg = nil

	if (failAmount == 0) then
		readScreenPlayData(pPlayer, "JediPadawanTrial", "FailureAmount", 1)
		failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_first"
	elseif (failAmount == 1) then
		readScreenPlayData(pPlayer, "JediPadawanTrial", "FailureAmount", 2)
		failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_second"
	elseif (failAmount == 2) then
		failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_final"
		deleteScreenPlayData(pPlayer, "JediPadawanTrial", "StartedTrials")
		deleteScreenPlayData(pPlayer, "JediPadawanTrial", "FailureAmount")
	end


	local sui = SuiMessageBox.new("JediPadawanTrial", "notifyOkPressedDoNothing")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt(failAmountMsg)
	sui.sendTo(pPlayer)
end

function JediPadawanTrial:notifyOkPressedDoNothing(pCreature, sui, eventIndex, arg0)
-- Do nothing.
end

function JediPadawanTrial:passCurrentTrial(pPlayer, pNpc, screenPlayName)
	if (pPlayer == nil) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_next_trial") -- You have done well and successfully completed the trial you faced. To undertake your next trial, simply meditate at any Force shrine.
	CreatureObject(pPlayer):setScreenPlayState(8, screenPlayName) -- Complete Trial.
	writeScreenPlayData(pPlayer, "JediPadawanTrial", "CurrentTrial", 0)

	if (pNpc ~= nil) then
		CreatureObject(pNpc):destroyObjectFromWorld()
	end
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
	local pScreenPlay = ForceShrineMenuComponent[trialNumber]
	pScreenPlay:start(pPlayer)
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
	deleteScreenPlayData(pPlayer, "JediPadawanTrial", "CurrentTrial")
	deleteScreenPlayData(pPlayer, "JediPadawanTrial", "FailureAmount")
	
	
	--Remove All States.
	CreatureObject(pPlayer):removeScreenPlayState("JediPadawanTrialArchitectScreenPlay", 8)
	CreatureObject(pPlayer):removeScreenPlayState("JediPadawanTrialArtistScreenPlay", 8)
end


return JediPadawanTrial
