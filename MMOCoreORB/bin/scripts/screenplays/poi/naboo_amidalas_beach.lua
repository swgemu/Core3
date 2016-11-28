NabooAmidalasBeachScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "NabooAmidalasBeachScreenPlay",

}

registerScreenPlay("NabooAmidalasBeachScreenPlay", true)

function NabooAmidalasBeachScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()

	end
end

function NabooAmidalasBeachScreenPlay:spawnMobiles()

	--Outside
	spawnMobile("naboo", "informant_npc_lvl_2", 0,-5548,-150,-13,225,0)
	spawnMobile("naboo", "informant_npc_lvl_2", 0,-5476,-150,-76,270,0)
	spawnMobile("naboo", "junk_sheani", 0, -5496.62, -150, -71.39, -4, 0)
end
