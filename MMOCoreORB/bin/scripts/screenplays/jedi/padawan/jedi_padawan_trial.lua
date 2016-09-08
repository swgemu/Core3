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

	CreatureObject(pCreature):sendSystemMessage("@jedi_trials:padawan_trials_tell_about_restart")
end

function JediPadawanTrial:sendSuiNotification(pCreature, msg1, msg2, screenPlayName, zone, region)
	local msgPrefix = msg1 .. "@jedi_trials:" .. zone
	local msgPostfix = msg2 .. region
	local msgFinal = msgPrefix .. " " .. msgPostfix

	local sui = SuiMessageBox.new(screenPlayName, "initializeTrialCallback")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt(msgFinal)
	sui.sendTo(pCreature)
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

function JediPadawanTrial:failCurrentTrial(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	local failAmount = getQuestStatus(SceneObject(pCreatureObject):getObjectID() .. ":padawan:trial:fail:amount")
	local failAmountMsg = nil

	if (failAmount == 0) then
		setQuestStatus(SceneObject(pCreatureObject):getObjectID() .. ":padawan:trial:fail:amount", 1)
		failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_first"
	elseif (failAmount == 1) then
		setQuestStatus(SceneObject(pCreatureObject):getObjectID() .. ":padawan:trial:fail:amount", 2)
		failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_second"
	elseif (failAmount == 2) then
		failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_final"
		removeQuestStatus(SceneObject(pCreatureObject):getObjectID() .. ":padawan:trial")
		CreatureObject(pCreatureObject):removeScreenPlayState("JediPadawanTrials")
		removeQuestStatus(SceneObject(pCreatureObject):getObjectID() .. ":padawan:trial:fail:amount")
	end


	local sui = SuiMessageBox.new("JediPadawanTrial", "notifyOkPressedDoNothing")
	sui.setTitle("@jedi_trials:force_shrine_title")
	sui.setPrompt(failAmountMsg)
	sui.sendTo(pCreatureObject)
end

function JediPadawanTrial:notifyOkPressedDoNothing(pCreature, sui, eventIndex, arg0)
-- Do nothing.
end

function JediPadawanTrial:passCurrentTrial(pCreatureObject, pNpc, screenPlayName)
	CreatureObject(pCreatureObject):sendSystemMessage("@jedi_trials:padawan_trials_next_trial") -- You have done well and successfully completed the trial you faced. To undertake your next trial, simply meditate at any Force shrine.
	CreatureObject(pCreatureObject):setScreenPlayState(8, screenPlayName) -- Complete Trial.
	CreatureObject(pCreatureObject):removeScreenPlayState("JediPadawanTrial") -- Reset Current Trial.

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
	local pScreenPlay = ForceShrineMenuComponent[trialNumber]
	pScreenPlay:restart(pPlayer)
end

function JediPadawanTrial:jediPadawanTrialsAbortCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@jedi_trials:padawan_trials_aborted")
	removeQuestStatus(SceneObject(pPlayer):getObjectID() .. ":padawan:trial")
	CreatureObject(pPlayer):removeScreenPlayState("JediPadawanTrials")
	removeQuestStatus(SceneObject(pCreatureObject):getObjectID() .. ":padawan:trial:fail:amount")
end


return JediPadawanTrial
