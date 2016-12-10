JediPadawanTrialArchitectScreenPlay = JediPadawanTrial:new {
	FIRST_MESSAGE = "@jedi_trials:architect_01 ",
	SECOND_MESSAGE = "@jedi_trials:architect_02 ",
	SCREEN_PLAY_NAME = "JediPadawanTrialArchitectScreenPlay",
	ZONE_NAME = "naboo",
	ZONE_REGION = "Theed",
	WAYPOINT_DESCRIPTION = "@jedi_trials:architect_03",

	-- Target information.
	TARGET_MOBILE = "trials_gungan_captain",
	TARGET_COORDINATES = {x = -7152, y = 4549}
}

registerScreenPlay("JediPadawanTrialArchitectScreenPlay", false)

function JediPadawanTrialArchitectScreenPlay:startTrial(pPlayer)
	self:sendSuiNotification(pPlayer, "kant_graf")
end

function JediPadawanTrialArchitectScreenPlay:startPart2(pPlayer)
	local pNpc = spawnMobile(self.ZONE_NAME, self.TARGET_MOBILE, 0, self.TARGET_COORDINATES.x, getTerrainHeight(pPlayer, self.TARGET_COORDINATES.x, self.TARGET_COORDINATES.y), self.TARGET_COORDINATES.y, getRandomNumber(180) - 180, 0)

	if (pNpc ~= nil) then
		CreatureObject(pNpc):setPvpStatusBitmask(0) -- Prevent attacking.

		local pGhost = CreatureObject(pPlayer):getPlayerObject()
		if (pGhost ~= nil) then
			PlayerObject(pGhost):addWaypoint(self.ZONE_NAME, "Jedi Trials", self.WAYPOINT_DESCRIPTION, self.TARGET_COORDINATES.x, self.TARGET_COORDINATES.y, WAYPOINT_COLOR_BLUE, true, true, WAYPOINTQUESTTASK)
			CreatureObject(pPlayer):setScreenPlayState(2, "JediPadawanTrialArchitectScreenPlay")
		end
	end
end

return JediPadawanTrialArchitectScreenPlay
