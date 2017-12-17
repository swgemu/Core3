AbandonedRebelBaseScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "AbandonedRebelBaseScreenPlay",

}

registerScreenPlay("AbandonedRebelBaseScreenPlay", true)

function AbandonedRebelBaseScreenPlay:start()
	if (isZoneEnabled("dantooine")) then
		self:spawnMobiles()
	end
end

function AbandonedRebelBaseScreenPlay:spawnMobiles()
	--inside perimeter near east building area
	spawnMobile("dantooine", "rebel_commando", 400, -6656.4, 30.0, 5552.4, -1, 0)
	spawnMobile("dantooine", "rebel_commando", 400, -6661.4, 30.0, 5557.4, -1, 0)
	spawnMobile("dantooine", "rebel_commando", 400, -6651.4, 30.0, 5547.4, -1, 0)
	spawnMobile("dantooine", "rebel_commando", 400, -6663.4, 30.0, 5562.4, -1, 0)

	spawnMobile("dantooine", "rebel_recruiter", 0, -6817, 46, 5511, 174, 0)
end
