TalusImperialVsRebelBattleScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("TalusImperialVsRebelBattleScreenPlay", true)

function TalusImperialVsRebelBattleScreenPlay:start()
	if (isZoneEnabled("talus")) then
		self:spawnMobiles()
	end
end

function TalusImperialVsRebelBattleScreenPlay:spawnMobiles()

	local pNpc = spawnMobile("talus", "imperial_pilot", 870, -2455.5, 41.1, 3867.2, 155, 0)
	self:setMoodString(pNpc, "worried")
	pNpc = spawnMobile("talus", "imperial_army_captain", 870, -2417.4, 38.0, 3678.8, 130, 0)
	self:setMoodString(pNpc, "angry")
	spawnMobile("talus", "imperial_probe_drone", 870, -2423, 38.0, 3677.7, 125, 0)
	pNpc = spawnMobile("talus", "imperial_pilot", 870, -2571.5, 28.9, 3824.2, -55, 0)
	self:setMoodString(pNpc, "angry")
	pNpc = spawnMobile("talus", "comm_operator", 870, -2415.6, 38.0, 3650.4, -63, 0)
	self:setMoodString(pNpc, "sad")
	pNpc = spawnMobile("talus", "rebel_trooper", 870, -2539.5, 38.0, 3710.5, -27, 0)
	self:setMoodString(pNpc, "happy")
	pNpc = spawnMobile("talus", "rebel_scout", 870, -2543.6, 38.1, 3729.2, -19, 0)
	self:setMoodString(pNpc, "nervous")
	pNpc = spawnMobile("talus", "rebel_major_general", 870, -2538.3, 38.0, 3708.5, 100, 0)
	self:setMoodString(pNpc, "calm")

end

