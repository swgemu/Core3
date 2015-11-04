TatooineImperialOasisBaseScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("TatooineImperialOasisBaseScreenPlay", true)

function TatooineImperialOasisBaseScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
		self:spawnSceneObjects()
	end
end

function TatooineImperialOasisBaseScreenPlay:spawnMobiles()

	local pNpc = spawnMobile("tatooine", "stranded_imperial_pilot", 870, -2455.5, 41.1, 3867.2, 155, 0)
	self:setMoodString(pNpc, "worried")
	pNpc = spawnMobile("tatooine", "stranded_imperial_officer", 870, -2417.4, 38.0, 3678.8, 130, 0)
	self:setMoodString(pNpc, "angry")
	spawnMobile("tatooine", "imperial_probe_drone", 870, -2423, 38.0, 3677.7, 125, 0)

end
