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
	spawnMobile("dantooine", "rebel_commando", 400, getRandomNumber(5) + -6656.4, 30.0, getRandomNumber(5) + 5552.4, getRandomNumber(360), 0)
	spawnMobile("dantooine", "rebel_commando", 400, getRandomNumber(5) + -6656.4, 30.0, getRandomNumber(5) + 5552.4, getRandomNumber(360), 0)
	spawnMobile("dantooine", "rebel_commando", 400, getRandomNumber(5) + -6656.4, 30.0, getRandomNumber(5) + 5552.4, getRandomNumber(360), 0)
	spawnMobile("dantooine", "rebel_commando", 400, getRandomNumber(5) + -6656.4, 30.0, getRandomNumber(5) + 5552.4, getRandomNumber(360), 0)

	spawnMobile("dantooine", "rebel_recruiter", 0,-6817,46,5511,174,0)

end
