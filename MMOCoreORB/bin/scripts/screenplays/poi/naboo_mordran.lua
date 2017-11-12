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
	local pNpc = spawnMobile("naboo", "mordran", 1200, -1969, 6.4, -5295, 45, 0)
	spawnMobile("naboo", "outcast_gungan", 300, -1967, 6.4, -5296, 45, 0)
	spawnMobile("naboo", "outcast_gungan", 300, -1964, 6.4, -5292, 45, 0)
	spawnMobile("naboo", "outcast_gungan", 300, -1966, 6.4, -5301, 45, 0)
	spawnMobile("naboo", "gungan_reject", 360, -1969, 6.4, -5291, 45, 0)
	spawnMobile("naboo", "gungan_reject", 360, -1969, 6.4, -5297, 45, 0)
	spawnMobile("naboo", "exiled_gungan", 360, -1966, 6.4, -5295, 45, 0)
	spawnMobile("naboo", "exiled_gungan", 360, -1963, 6.4, -5299, 45, 0)
end
