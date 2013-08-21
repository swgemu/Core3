NabooMordranScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "NabooMordranScreenPlay",

}

registerScreenPlay("NabooMordranScreenPlay", true)

function NabooMordranScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()

	end
end

function NabooMordranScreenPlay:spawnMobiles()

		--mordran respawns between 15-20 minutes
	spawnMobile("naboo", "mordran", math.random(300) + 900, -1969, 6.4, -5295, 45, 0)
	spawnMobile("naboo", "gungan_outcast", 210, math.random(32) + -1985, 6.4, math.random(12) + -5302, 45, 0)
	spawnMobile("naboo", "gungan_outcast", 210, math.random(32) + -1985, 6.4, math.random(12) + -5302, 45, 0)
	spawnMobile("naboo", "gungan_outcast", 210, math.random(32) + -1985, 6.4, math.random(12) + -5302, 45, 0)
	spawnMobile("naboo", "gungan_reject", 300, math.random(8) + -1971, 6.4, math.random(12) + -5302, 45, 0)
	spawnMobile("naboo", "gungan_reject", 300, math.random(8) + -1971, 6.4, math.random(12) + -5302, 45, 0)
	spawnMobile("naboo", "exiled_gungan", 300, math.random(8) + -1971, 6.4, math.random(12) + -5302, 45, 0)
	spawnMobile("naboo", "exiled_gungan", 300, math.random(8) + -1971, 6.4, math.random(12) + -5302, 45, 0)
	
end
