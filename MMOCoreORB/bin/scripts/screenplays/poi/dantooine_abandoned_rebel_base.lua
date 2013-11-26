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

	spawnMobile("dantooine", "rebel_recruiter", 0,-6817,46,5511,174,0)

end
