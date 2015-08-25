NabooDeejaPeakScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "NabooDeejaPeakScreenPlay",

}

registerScreenPlay("NabooDeejaPeakScreenPlay", true)

function NabooDeejaPeakScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
		self:spawnSceneObjects()
	end
end

function NabooDeejaPeakScreenPlay:spawnSceneObjects()

	--Capitol building
	spawnSceneObject("naboo", "object/static/structure/general/droid_probedroid_powerdown.iff", 7.1, 0.3, -12.9, 1245390, math.rad(20) )
	spawnSceneObject("naboo", "object/static/structure/general/droid_probedroid_powerdown.iff", -7.1, 0.3, -12.9, 1245390, math.rad(-50) )
	spawnSceneObject("naboo", "object/static/structure/general/droid_probedroid_powerdown.iff", 20.7, 3.2, 21.9, 1945396, math.rad(173) )
	spawnSceneObject("naboo", "object/static/structure/general/droid_droideka_powerdown.iff", -17.4, 3.2, 21.6, 1945395, math.rad(-90) )
	spawnSceneObject("naboo", "object/static/structure/general/droid_droideka_powerdown.iff", -24.7, 3.2, 21.6, 1945395, math.rad(90) )
	spawnSceneObject("naboo", "object/tangible/furniture/decorative/professor_desk.iff", -21.0, 3.2, 29.7, 1945395, math.rad(180) )

	--random house
	spawnSceneObject("naboo", "object/tangible/furniture/jedi/frn_all_banner_dark.iff", -3.9, 1.1, 1.0, 1714783, math.rad(-90) )
	spawnSceneObject("naboo", "object/tangible/furniture/all/frn_all_tiki_torch_s1.iff", -5.4, 1.1, 5.1, 1714783, math.rad(150) )
	spawnSceneObject("naboo", "object/tangible/furniture/all/frn_all_tiki_torch_s1.iff", -7.5, 1.1, 3.5, 1714783, math.rad(114) )
	spawnSceneObject("naboo", "object/tangible/furniture/all/frn_all_tiki_torch_s1.iff", -8.3, 1.1, 1.0, 1714783, math.rad(77) )
	spawnSceneObject("naboo", "object/tangible/furniture/all/frn_all_tiki_torch_s1.iff", -7.3, 1.1, -1.4, 1714783, math.rad(46) )
	spawnSceneObject("naboo", "object/tangible/furniture/all/frn_all_tiki_torch_s1.iff", -5.3, 1.1, -3.0, 1714783, math.rad(12) )
	spawnSceneObject("naboo", "object/static/structure/general/droid_ra7_powerdown.iff", 2.7, 1.1, 4.5, 1714783, math.rad(-141) )
	spawnSceneObject("naboo", "object/static/structure/general/poi_protocolarm.iff", -8.6, -4.9, -0.1, 1714784, math.rad(-63) )
	spawnSceneObject("naboo", "object/static/structure/general/skeleton_ithorian_headandbody.iff", -4.3, -4.9, 0.1, 1714787, math.rad(110) )
	spawnSceneObject("naboo", "object/tangible/item/quest/force_sensitive/bacta_tank.iff", -3.8, -4.9, -10.7, 1714787, math.rad(-58) )
	spawnSceneObject("naboo", "object/tangible/furniture/all/frn_all_tiki_torch_s1.iff", -7.6, -4.9, -2.1, 1714787, math.rad(-103) )
	--random house b
	spawnSceneObject("naboo", "object/tangible/furniture/jedi/frn_all_banner_light.iff", -4.2, 1.1, 1.0, 1685121, math.rad(90) )
	spawnSceneObject("naboo", "object/static/structure/general/droid_r3_powerdown.iff", -3.8, 1.1, 2.4, 1685121, math.rad(104) )

end

function NabooDeejaPeakScreenPlay:spawnMobiles()

	--Capitol building
	local pNpc = spawnMobile("naboo", "entertainer",60,-0.0,3.1,-9.6,0,1945390)
	self:setMoodString(pNpc, "themepark_music_3")
	pNpc = spawnMobile("naboo", "comm_operator",60,25.8,1.3,-4.5,90,1945390)
	self:setMoodString(pNpc, "npc_use_terminal_low")
	pNpc = spawnMobile("naboo", "commoner_technician",60,-25.8,1.3,-0.9,-90,1945390)
	self:setMoodString(pNpc, "npc_use_terminal_low")
	pNpc = spawnMobile("naboo", "commoner_fat",60,-3.6,0.3,-1.2,155,1945390)
	self:setMoodString(pNpc, "entertained")
	pNpc = spawnMobile("naboo", "mouse_droid",60,-24.3,1.3,0.1,-114,1945390)
	self:setMoodString(pNpc, "worried")
	pNpc = spawnMobile("naboo", "vendor",60,25.5,1.3,-10.8,-89,1945390)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("naboo", "seeker",60,25.5,1.3,-9.7,-90,1945390)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("naboo", "seeker",60,25.5,1.3,-11.8,-91,1945390)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("naboo", "medic",60,-29.1,1.3,2.0,-170,1945394)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("naboo", "surgical_droid_21b",60,-30.5,1.3,-0.1,-3,1945394)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("naboo", "agriculturalist",60,18.7,3.2,-23.3,-5,1945398)
	self:setMoodString(pNpc, "bored")
	pNpc = spawnMobile("naboo", "mercenary",60,-21.3,3.2,21.7,0,1945395)
	self:setMoodString(pNpc, "npc_sitting_ground")
	pNpc = spawnMobile("naboo", "r4",60,-20.3,3.2,20.0,-45,1945395)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("naboo", "r4",60,-21.9,3.2,20.1,34,1945395)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("naboo", "r4",60,-21.9,3.2,23.3,126,1945395)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("naboo", "r4",60,-20.0,3.2,23.4,-148,1945395)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("naboo", "judge",60,-21.0,3.2,26.9,180,1945395)
	self:setMoodString(pNpc, "calm")
	pNpc = spawnMobile("naboo", "commoner_naboo",60,-24.0,3.2,25.4,135,1945395)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("naboo", "commoner_tatooine",60,-18.0,3.2,25.5,-134,1945395)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("naboo", "corellia_times_reporter",60,-18.0,3.2,17.8,-45,1945395)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("naboo", "r5",60,-19.5,3.2,28.8,-147,1945395)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("naboo", "shadowy_figure",60,3.9,7.9,-30.5,0,1945390)
	self:setMoodString(pNpc, "calm")
	pNpc = spawnMobile("naboo", "contractor",60,-1.3,7.9,-40.7,160,1945392)
	self:setMoodString(pNpc, "sad")
	pNpc = spawnMobile("naboo", "businessman",60,-0.1,7.9,-40.9,-90,1945392)
	self:setMoodString(pNpc, "explain")
	pNpc = spawnMobile("naboo", "sullustan_male",60,0.7,3.1,22.5,-90,1945389)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("naboo", "chiss_male",60,-0.5,3.1,22.5,90,1945389)
	self:setMoodString(pNpc, "conversation")

	--random house
	pNpc = spawnMobile("naboo", "shadowy_figure",60,11.3,1.1,-2.4,-158,1714782)
	self:setMoodString(pNpc, "angry")
	pNpc = spawnMobile("naboo", "seeker",60,-10.0,-4.9,-2.5,-2,1714784)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("naboo", "twilek_slave",60,-10.7,-4.9,-10.7,35,1714787)
	self:setMoodString(pNpc, "scared")
	pNpc = spawnMobile("naboo", "dark_jedi_knight",4321,-10.8,-4.9,-7.5,-180,1714787)
	self:setMoodString(pNpc, "npc_accusing")
	pNpc = spawnMobile("naboo", "surgical_droid_21b",60,-3.5,-4.9,-7.6,-95,1714787)
	self:setMoodString(pNpc, "neutral")
	--random house b
	pNpc = spawnMobile("naboo", "mouse_droid",60,10.1,1.1,-4.8,-36,1685120)
	self:setMoodString(pNpc, "neutral")
	--random guild hall
	pNpc = spawnMobile("naboo", "commoner_fat",60,-11.5,1.7,-7.9,-86,8845426)
	self:setMoodString(pNpc, "npc_standing_drinking")
	pNpc = spawnMobile("naboo", "commoner_old",60,-11.4,1.7,-6.5,178,8845426)
	self:setMoodString(pNpc, "npc_angry")
	pNpc = spawnMobile("naboo", "chiss_female",60,8.6,1.7,-14.6,-38,8845426)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("naboo", "chiss_male",60,5.3,1.8,-14.7,47,8845426)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("naboo", "brawler",60,14.2,9.0,14.8,-90,8845420)
	self:setMoodString(pNpc, "npc_accusing")
	pNpc = spawnMobile("naboo", "brawler",60,-14.2,9.0,14.5,90,8845422)
	self:setMoodString(pNpc, "npc_accusing")
	pNpc = spawnMobile("naboo", "judge",60,-20.1,2.3,9.9,0,8845424)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("naboo", "entertainer",60,-20.8,2.3,12.9,92,8845424)
	self:setMoodString(pNpc, "entertained")
	pNpc = spawnMobile("naboo", "entertainer",60,-19.3,2.3,12.9,-95,8845424)
	self:setMoodString(pNpc, "happy")

	--Hotel
	pNpc = spawnMobile("naboo", "commoner_old",60,0.8,1.0,4.4,-160,1419013)
	self:setMoodString(pNpc, "fishing")
	pNpc = spawnMobile("naboo", "bartender",60,20.1,1.6,12.3,180,1419014)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("naboo", "comm_operator",60,-23.6,1.6,8.8,107,1419015)
	self:setMoodString(pNpc, "npc_use_terminal_low")
	pNpc = spawnMobile("naboo", "devaronian_male",60,-14.9,1.6,-18.5,90,1419018)
	self:setMoodString(pNpc, "npc_sitting_table")
	pNpc = spawnMobile("naboo", "ithorian_male",60,-12.6,1.6,-18.5,-90,1419018)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("naboo", "commoner",60,-13.6,1.6,-17.2,-173,1419018)
	self:setMoodString(pNpc, "npc_sitting_ground")
	pNpc = spawnMobile("naboo", "artisan",60,-0.2,1.0,20.6,174,1419011)
	self:setMoodString(pNpc, "npc_use_terminal_high")

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
