NabooDeejaPeakScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "NabooDeejaPeakScreenPlay",

}

registerScreenPlay("NabooDeejaPeakScreenPlay", true)

function NabooDeejaPeakScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
	end
end

function NabooDeejaPeakScreenPlay:spawnMobiles()

	--Screenplay needs more added.

	--Guild Hall 4731 -1294
	spawnMobile("naboo", "trainer_architect", 0,11,1.133,-14.5,0,1685238)
	spawnMobile("naboo", "trainer_armorsmith", 0,-15,1.1,0,90,1685237)
	spawnMobile("naboo", "trainer_droidengineer", 0,-11.3655,1.13306,-13.793,236,1685240)
	spawnMobile("naboo", "trainer_merchant", 0,14,1.1,5.7,-169,1685236)
	spawnMobile("naboo", "trainer_weaponsmith", 0,-2.5,1.13306,-8.4,91,1685239)

	--Guild Hall/Theater 4963 -1475
	spawnMobile("naboo", "trainer_dancer", 0,17.8577,2.12873,53.8179,2,2725360)
	spawnMobile("naboo", "trainer_entertainer", 0,28.1,2.1,73.1,-138,2725360)
	spawnMobile("naboo", "trainer_imagedesigner", 0,-22.2396,2.12878,72.4933,181,2725361)
	spawnMobile("naboo", "trainer_musician", 0,21.8956,2.12814,63.5,0,2725360)

	--Outside
	spawnMobile("naboo", "imperial_recruiter", 0,5307,326,-1584,74,0)
	spawnMobile("naboo", "informant_npc_lvl_2", 0,5332,327,-1568,225,0)
	spawnMobile("naboo", "informant_npc_lvl_2", 0,4980,360,-1489,270,0)
	spawnMobile("naboo", "informant_npc_lvl_2", 0,4923,360,-1411,180,0)
	spawnMobile("naboo", "informant_npc_lvl_2", 0,4754,330,-1358,0,0)
	spawnMobile("naboo", "informant_npc_lvl_2", 0,4688,330,-1342,135,0)
	spawnMobile("naboo", "informant_npc_lvl_1", 0,4700,330,-1406,153,0)
	spawnMobile("naboo", "trainer_artisan", 0,4715,330,-1393,77,0)
	spawnMobile("naboo", "trainer_politician", 0,4702,330,-1368,84,0)
	spawnMobile("naboo", "trainer_marksman", 0,4980,360,-1425,-100,0)

end	
