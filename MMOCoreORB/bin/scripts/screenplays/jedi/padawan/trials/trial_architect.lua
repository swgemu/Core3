JediPadawanTrialArchitectScreenPlay = JediPadawanTrial:new {
	FIRST_MESSAGE = "@jedi_trials:architect_01 ",
	SECOND_MESSAGE = "@jedi_trials:architect_02 ",
	SCREEN_PLAY_NAME = "JediPadawanTrialArchitectScreenPlay",
	ZONE_NAME = "naboo",
	ZONE_REGION = "Theed",
	WAYPOINT_DESCRIPTION = "@jedi_trials:architect_03",
}

registerScreenPlay(JediPadawanTrialArchitectScreenPlay.SCREEN_PLAY_NAME, false)

function JediPadawanTrial:start(pPlayer)
	self:sendSuiNotification(pPlayer, "kant_graf")
end

function JediPadawanTrialArchitectScreenPlay:startPart2(pCreature)
	local pNpc = spawnMobile(self.ZONE_NAME, self.TARGET_MOBILE, 0, self.TARGET_COORDINATES.x, getTerrainHeight(pCreature, self.TARGET_COORDINATES.x, self.TARGET_COORDINATES.y), self.TARGET_COORDINATES.y, getRandomNumber(180) - 180, 0)

	if (pNpc ~= nil) then
		local pGhost = CreatureObject(pCreature):getPlayerObject()
		if (pGhost ~= nil) then
			PlayerObject(ghost):addWaypoint(self.ZONE_NAME, "Jedi Trials", self.WAYPOINT_DESCRIPTION, self.TARGET_COORDINATES.x, self.TARGET_COORDINATES.y, WAYPOINT_COLOR_BLUE, true, true, 0)
			CreatureObject(pCreature):setScreenPlayState(2, "JediPadawanTrialArchitectScreenPlay")
		end
	end
end

function JediPadawanTrialArchitectScreenPlay:despawnNPC02(pCreature)
	if (pCreature ~= nil) then
		CreatureObject(pCreature):destroyObjectFromWorld()
	end

end

return JediPadawanTrialArchitectScreenPlay
