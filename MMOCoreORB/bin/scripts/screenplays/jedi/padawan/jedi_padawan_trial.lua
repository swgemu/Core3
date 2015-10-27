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

	local suiManager = LuaSuiManager()


	local msgPrefix = msg1 .. "@jedi_trials:" .. zone
	local msgPostfix = msg2 .. region
	local msgFinal = msgPrefix .. " " .. msgPostfix


	suiManager:sendMessageBox(pCreature, pCreature, "@jedi_trials:padawan_trials_title", msgFinal, "@ok", screenPlayName, "notifyOkPressed")
end

function JediPadawanTrial:failCurrentTrial(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end
	
	local failAmount = CreatureObject(pCreatureObject):getScreenPlayState("trials:padawan:failedTrials")
	local failAmountMsg = nil
	
	if (failAmount == 0) then
	CreatureObject(pCreatureObject):setScreenPlayState(1, "trials:padawan:failedTrials")
	failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_first"
	elseif (failAmount == 1) then
	CreatureObject(pCreatureObject):setScreenPlayState(2, "trials:padawan:failedTrials")
	failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_second"
	elseif (failAmount == 2) then
	failAmountMsg = "@jedi_trials:padawan_trials_trial_failed_final"
	self:restartTrials(pCreatureObject)
	end
	
	
	local suiManager = LuaSuiManager()
	suiManager:sendMessageBox(pCreatureObject, pCreatureObject, "@jedi_trials:padawan_trials_title", failAmountMsg, "@ok", "JediPadawanTrial", "notifyOkPressedFailedTrial")
end

function JediPadawanTrial:notifyOkPressedFailedTrial(pCreature, sui, cancelPressed, arg0)
-- Do nothing.
end

function JediPadawanTrial:restartTrials(pCreatureObject)
			CreatureObject(pCreatureObject):setScreenPlayState(0, "trials:padawan:failedTrials") -- Reset failed trials counter.
			CreatureObject(pCreatureObject):setScreenPlayState(0, "trials:padawan:currentTrial") -- Reset the current trial.
end

function JediPadawanTrial:passCurrentTrial(pCreatureObject, pNpc, screenPlayName)
CreatureObject(pCreatureObject):sendSystemMessage("@jedi_trials:padawan_trials_next_trial") -- You have done well and successfully completed the trial you faced. To undertake your next trial, simply meditate at any Force shrine.
CreatureObject(pCreatureObject):setScreenPlayState(8, screenPlayName) -- Complete Trial.
CreatureObject(pCreatureObject):setScreenPlayState(0, "trials:padawan:currentTrial") -- Reset Current Trial.

if (pNpc ~= nil) then
				CreatureObject(pNpc):destroyObjectFromWorld()
end

end


return JediPadawanTrial
