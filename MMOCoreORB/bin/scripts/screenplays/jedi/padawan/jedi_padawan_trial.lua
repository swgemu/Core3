local ObjectManager = require("managers.object.object_manager")


-- Screenplays states:

--[[
0 - Has not started the quest.
1 - Has started the quest, has not accepted from giver.
2 - Accepted, not finished
4 - Quest Failed
8 - Quest Passed       
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


return JediPadawanTrial
