JediPadawanTrialArtistScreenPlay = JediPadawanTrial:new {
	FIRST_MESSAGE = "@jedi_trials:artist_01 ",
	SECOND_MESSAGE = "@jedi_trials:artist_02 ",
	SCREEN_PLAY_NAME = "JediPadawanTrialArtistScreenPlay",
	ZONE_NAME = "naboo",
	ZONE_REGION = "Kaadara",
	WAYPOINT_DESCRIPTION = "@jedi_trials:artist_03",
	
	-- Target information.
	TARGET_MOBILE = "trials_artist_contact",
	TARGET_COORDINATES = {x = 5996, y = 5885},
}

registerScreenPlay("JediPadawanTrialArtistScreenPlay", false)

function JediPadawanTrialArtistScreenPlay:startTrial(pPlayer)
	self:sendSuiNotification(pPlayer, "sathme_forr")
end

function JediPadawanTrialArtistScreenPlay:startPart2(pPlayer)
	local pNpc = spawnMobile(self.ZONE_NAME, self.TARGET_MOBILE, 0, self.TARGET_COORDINATES.x, getTerrainHeight(pPlayer, self.TARGET_COORDINATES.x, self.TARGET_COORDINATES.y), self.y, getRandomNumber(180) - 180, 0)

	if (pNpc ~= nil) then
		local pGhost = CreatureObject(pPlayer):getPlayerObject()
		if (pGhost ~= nil) then
			PlayerObject(pGhost):addWaypoint(self.ZONE_NAME, "Jedi Trials", self.WAYPOINT_DESCRIPTION, self.TARGET_COORDINATES.x, self.TARGET_COORDINATES.y, WAYPOINT_COLOR_BLUE, true, true, WAYPOINTQUESTTASK)
		end
	end
end

return JediPadawanTrialArtistScreenPlay
