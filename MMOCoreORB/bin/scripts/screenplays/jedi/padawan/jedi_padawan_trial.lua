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
	numberOfActs = 1,

}

function JediPadawanTrial:initializeTrial(pCreature, pScreenPlayName, mobile, waypointDesc, zoneName, spawn)
	local pNpc = spawnMobile(zoneName, mobile, 60, spawn.x, getTerrainHeight(pCreature, spawn.x, spawn.y), spawn.y, getRandomNumber(360) - 180, 0)

	if (pNpc ~= nil) then
		local ghost = CreatureObject(pCreature):getPlayerObject()
		PlayerObject(ghost):addWaypoint(zoneName, "Jedi Trials", waypointDesc, spawn.x, spawn.y, WAYPOINT_COLOR_BLUE, true, true, 0)
		CreatureObject(pCreature):setScreenPlayState(1, pScreenPlayName)
	end

end

function JediPadawanTrial:sendSuiNotification(pCreature, msg1, msg2, screenPlayName, zone, region)
	local msgPrefix = msg1 .. "@jedi_trials:" .. zone
	local msgPostfix = msg2 .. region
	local msgFinal = msgPrefix .. " " .. msgPostfix
	
	local sui = SuiMessageBox.new(screenPlayName, "notifyOkPressed")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt(msgFinal)
	sui.setCancelButtonText("@jedi_trials:button_abort_padawan") -- Quit Padawan Trials
	sui.setRevertButtonText("@jedi_trials:button_restart") -- Restart Current Trial
	sui.sendTo(pCreature)
end

function JediPadawanTrial:restartCurrentPadawanTrial(pObject, pPlayer)
	local sui = SuiMessageBox.new("JediPadawanTrial", "jediPadawanTrialsRestartCallback")
	sui.setTargetNetworkId(SceneObject(pObject):getObjectID())
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt("@jedi_trials:padawan_trials_restart_confirmation")
	sui.sendTo(pPlayer)
end

function JediPadawanTrial:quitPadawanTrials(pObject, pPlayer)
	local sui = SuiMessageBox.new("JediPadawanTrial", "jediPadawanTrialsAbortCallback")
	sui.setTargetNetworkId(SceneObject(pObject):getObjectID())
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt("@jedi_trials:padawan_trials_abort_confirmation")
	sui.sendTo(pPlayer)
end

function JediPadawanTrial:failCurrentTrial(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	local failAmount = CreatureObject(pCreatureObject):getScreenPlayState("JediPadawanTrialsFailed")
	local failAmountMsg = nil

	if (failAmount == 0) then
		CreatureObject(pCreatureObject):setScreenPlayState(1, "JediPadawanTrialsFailed")
		failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_first"
	elseif (failAmount == 1) then
		CreatureObject(pCreatureObject):setScreenPlayState(2, "JediPadawanTrialsFailed")
		failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_second"
	elseif (failAmount == 2) then
		failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_final"
		self:restartTrials(pCreatureObject)
	end


	local sui = SuiMessageBox.new("JediPadawanTrial", "notifyOkPressedDoNothing")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt(failAmountMsg)
	sui.sendTo(pCreatureObject)
end

function JediPadawanTrial:notifyOkPressedDoNothing(pCreature, sui, cancelPressed, arg0)
-- Do nothing.
end

function JediPadawanTrial:restartTrials(pCreatureObject)
	CreatureObject(pCreatureObject):setScreenPlayState(0, "JediPadawanTrialsFailed") -- Reset failed trials counter.
	CreatureObject(pCreatureObject):setScreenPlayState(0, "JediPadawanTrial") -- Reset the current trial.
	CreatureObject(pCreatureObject):setScreenPlayState(0, "JediPadawanTrials")
end

function JediPadawanTrial:passCurrentTrial(pCreatureObject, pNpc, screenPlayName)
	CreatureObject(pCreatureObject):sendSystemMessage("@jedi_trials:padawan_trials_next_trial") -- You have done well and successfully completed the trial you faced. To undertake your next trial, simply meditate at any Force shrine.
	CreatureObject(pCreatureObject):setScreenPlayState(8, screenPlayName) -- Complete Trial.
	CreatureObject(pCreatureObject):setScreenPlayState(0, "JediPadawanTrial") -- Reset Current Trial.

	local ghost = CreatureObject(pCreatureObject):getPlayerObject()
	PlayerObject(ghost):completePadawanTrial(screenPlayName)

	if (pNpc ~= nil) then
		CreatureObject(pNpc):destroyObjectFromWorld()
	end
end


function JediPadawanTrial:jediPadawanTrialsRestartCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_trial_restarted")
	local trialNumber = CreatureObject(pPlayer):getScreenPlayState("JediPadawanTrial")
	local pScreenPlay = self[trialNumber]
	pScreenPlay:start(pPlayer)
end

function JediPadawanTrial:jediPadawanTrialsAbortCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_aborted")
	CreatureObject(pPlayer):setScreenPlayState(0, "JediPadawanTrial")
	CreatureObject(pPlayer):setScreenPlayState(0, "JediPadawanTrials")
end


return JediPadawanTrial
