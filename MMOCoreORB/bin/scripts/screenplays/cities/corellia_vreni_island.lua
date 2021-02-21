CorelliaVreniIslandScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CorelliaVreniIslandScreenPlay",

	planet = "corellia",

	gcwMobs = {
		{"rebel_specforce_pathfinder", -5538.4, 16.4902, -6054.7, 182.005, 0, "", true},
		{"specforce_master_sergeant", -5533.2, 23.4, -6202.2, 46, 0, "", true},
		{"specforce_technician", -5405, 25, -6220, 37, 0, "", true},
		{"rebel_specforce_pathfinder", -5534.1, 23.4, -6217.9, 138.004, 0, "", true},
		{"rebel_recruiter", 0, -5516.1, 23.4, -6204.0, 0, 0, "", true},
		{"specforce_infiltrator", -5549.5, 23.4, -6202.1, 310.009, 0, "", true},
		{"specforce_procurement_specialist", -5549, 23.4, -6217.8, -139, 0, "", true},
		{"rebel_specforce_pathfinder", -5429.8, 24, -6218.9, 0, 0, "", true},
		{"rebel_specforce_captain", -5411.4, 24.9599, -6219.3, 5.00012, 0, "", true},
		{"specforce_marine", -5398, 24.2, -6242.9, 81, 0, "", true},
		{"specforce_marine", -5443.6, 24, -6243, 282.008, 0, "", true},
		{"specforce_marine", -5716.1, 14.6, -6153.1, 269.008, 0, "", true},
		{"specforce_infiltrator", -5716.1, 14.6, -6147.5, 271.008, 0, "", true},
		{"specforce_marine", -5664, 14.6, -6179.3, 94.0028, 0, "", true},
		{"rebel_specforce_pathfinder", -5664, 14.7566, -6185.3, 94.0028, 0, "", true},
		{"specforce_marine", -5290.0, 4.0, -6421.6, 0, 0, "", true},
		{"specforce_marine", -5290.0, 4.0, -6432.9, 180, 0, "", true},
		{"specforce_marine", -5149.3, 4.2, -6418.8, -90, 0, "", true},
		{"specforce_marine", -5160.1, 4.0, -6413.2, 90, 0, "", true},
	},

	patrolNpcs = {"businessman_patrol", "commoner_fat_patrol", "commoner_old_patrol", "commoner_patrol", "noble_patrol", "scientist_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, level, x, z, y, direction, cell, mood, combatPatrol},

		--Droids
		{"cll8_1", "cll8_binary_load_lifter", 1, -5696, 14.6, -6154.2, 75, 0, "", false},
		{"eg6_1", "eg6_power_droid", 1, -5690.7, 14.6, -6154.2, -87, 0, "", false},
		{"eg6_2", "eg6_power_droid" , 1, -5692.6, 14.6, -6151.3, 179.6, 0, "", false},

		--NPCs
		{"npc_1", "patrolNpc", 1, -5505, 23, -6118, 272, 0, "", false},
		{"npc_2", "patrolNpc", 1, -5519, 23, -6224, 134, 0, "", false},
		{"npc_3", "patrolNpc", 1, -5385, 24, -6239, 118, 0, "", false},
		{"npc_4", "patrolNpc", 1, -5480, 23, -6133, 182, 0, "", false},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}
		cll8_1 ={{-5696, 14.6, -6154, 0, false}, {-5693, 14.6, -6163, 0, false}, {-5688, 14.6, -6180, 0, false}, {-5673, 14.6, -6180, 0, false}, {-5688, 14.6, -6180, 0, false}},
		eg6_1 = {{-5690, 14.6, -6154, 0, false}, {-5686, 14.6, -6154, 0, false}, {-5685, 14.6, -6166, 0, false}},
		eg6_2 = {{-5692, 14.6, -6151, 0, false}, {-5693, 14.6, -6137, 0, false}, {-5686, 14.6, -6142, 0, false}},

		npc_1 = {{-5505, 23, -6118, 0, true}, {-5514, 23, -6107, 0, true}, {-5552, 23, -6112, 0, true}, {-5551, 23, -6123, 0, true}},
		npc_2 = {{-5519, 23, -6224, 0, true}, {-5503, 23, -6224, 0, true}, {-5490, 23, -6241, 0, true}},
		npc_3 = {{-5385, 24, -6239, 0, true}, {-5366, 23, -6232, 0, true}, {-5370, 23, -6239, 0, true}, {-5365, 23, -6245, 0, true}, {-5393, 23, -6240, 0, true}},
		npc_4 = {{-5480, 23, -6133, 0, true}, {-5480, 23, -6181, 0, true}, {-5469, 23, -6170, 0, true}},
	},
}

registerScreenPlay("CorelliaVreniIslandScreenPlay", true)

function CorelliaVreniIslandScreenPlay:start()
	if (isZoneEnabled("corellia")) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
		self:spawnSceneObjects()
		self:spawnGcwMobiles()
	end
end

function CorelliaVreniIslandScreenPlay:spawnSceneObjects()

	--Hotel
	spawnSceneObject("corellia", "object/static/structure/general/droid_probedroid_powerdown.iff", -6.2, 1.0, 21.7, 2775411, math.rad(-163) )
	--Cantina
	spawnSceneObject("corellia", "object/static/structure/general/escape_pod.iff", -29.2, -0.9, 3.2, 3005705, math.rad(118) )
	spawnSceneObject("corellia", "object/static/structure/general/skeleton_bith_headandbody.iff", -29.3, -0.9, 1.2, 3005705, math.rad(-9) )

end

function CorelliaVreniIslandScreenPlay:spawnMobiles()

	local pNpc = spawnMobile("corellia", "commoner_technician",60,7.1,1.0,19.3,137,2775411)
	self:setMoodString(pNpc, "npc_use_terminal_high")
	spawnMobile("corellia", "businessman",60,-5428.59,24.1812,-6228.31,140.458,0)
	spawnMobile("corellia", "commoner",60,-5495.01,23.4,-6190.5,325.039,0)
	spawnMobile("corellia", "commoner",60,-5504.22,23.4,-6211.56,1.34408,0)
	spawnMobile("corellia", "commoner",60,-5488.87,23.8964,-6242.6,304.866,0)
	spawnMobile("corellia", "commoner",60,-5551.88,23.4,-6221.48,124.882,0)
	spawnMobile("corellia", "commoner",60,-5549.18,23.4,-6189.25,119.296,0)
	spawnMobile("corellia", "commoner",60,-5571.88,23.4,-6129.85,97.3312,0)
	spawnMobile("corellia", "commoner",60,-5708.22,14.6,-6157.68,63.8572,0)
	spawnMobile("corellia", "commoner",60,-5686.69,14.6,-6148.05,214.943,0)
	spawnMobile("corellia", "commoner",60,-5693.27,14.6,-6177.12,293.479,0)
	spawnMobile("corellia", "bounty_hunter",300,24.9055,1.28309,5.31569,360.011,2775414)
	spawnMobile("corellia", "corellia_times_investigator",300,8.4,1.0,10.8,-172,2775413)
	spawnMobile("corellia", "chiss_female",300,8.2,1.0,8.7,7,2775413)
	spawnMobile("corellia", "twilek_slave",300,24.9055,1.28309,6.41569,180.019,2775414)
	spawnMobile("corellia", "entertainer",60,-22.5021,1.6,4.63468,179.972,2775415)
	spawnMobile("corellia", "info_broker",60,-22.5017,1.59973,3.53494,359.971,2775415)
	spawnMobile("corellia", "informant_npc_lvl_3",0,-5559,23.4,-6220,90,0)
	spawnMobile("corellia", "noble",60,-24.96,1.6,-4.79578,14.5444,2775419)
	spawnMobile("corellia", "r2",60,-5528,23.4,-6195.05,84.2678,0)                -- "R2-P2" When/if option customName is available to spawnMobile function
	spawnMobile("corellia", "scientist",60,-5557.29,23.4,-6203.08,226.081,0)
	spawnMobile("corellia", "scientist",60,-5691.18,14.6,-6133.32,248.134,0)
	spawnMobile("corellia", "trainer_entertainer",0,22.0446,-0.894993,11.7787,189,3005697)
	spawnMobile("corellia", "trainer_doctor",0,-2.9,0.7,2.5,132,7615446)
	spawnMobile("corellia", "trainer_musician",0,-5408,24.7288,-6260,50,0)
	spawnMobile("corellia", "junk_dealer", 0, -5664.12, 14.6, -6171.81, 123, 0)
	spawnMobile("corellia", "junk_dealer", 0, -5439.78, 23.91, -6225.42, -84, 0)

	pNpc = spawnMobile("corellia", "commoner_technician",60,-32.3,-0.1,-19.0,-177,3005708)
	self:setMoodString(pNpc, "sad")
	pNpc = spawnMobile("corellia", "mouse_droid",60,-32.8,-0.1,-21.0,-16,3005708)
	self:setMoodString(pNpc, "sad")
	pNpc = spawnMobile("corellia", "patron_devaronian",60,-31.6,0.1,-9.7,10,3005708)
	self:setMoodString(pNpc, "sad")
	pNpc = spawnMobile("corellia", "bartender",60,8.5,-0.9,0.1,82,3005697)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("corellia", "scientist",60,10.5,-0.9,2.0,-119,3005697)
	self:setMoodString(pNpc, "npc_standing_drinking")
	pNpc = spawnMobile("corellia", "devaronian_male",60,-31.2,-0.9,20.3,87,3005706)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("corellia", "bounty_hunter",60,-21.4,-0.9,19.0,-84,3005706)
	self:setMoodString(pNpc, "calm")
	pNpc = spawnMobile("corellia", "entertainer",60,-30.5,-0.9,19.9,-22,3005706)
	self:setMoodString(pNpc, "happy")
	pNpc = spawnMobile("corellia", "chiss_female",60,-30.6,-0.9,20.8,178,3005706)
	self:setMoodString(pNpc, "entertained")
	pNpc = spawnMobile("corellia", "seeker",60,-32.2,-0.9,19.6,76,3005706)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("corellia", "shadowy_figure",60,-27.8,-0.9,0.1,-56,3005705)
	self:setMoodString(pNpc, "worried")
	pNpc = spawnMobile("corellia", "mercenary",60,-16.3,-0.9,3.2,106,3005697)
	self:setMoodString(pNpc, "angry")
	pNpc = spawnMobile("corellia", "mercenary",60,-16.3,-0.9,-2.9,65,3005697)
	self:setMoodString(pNpc, "angry")
	pNpc = spawnMobile("corellia", "medic",60,1.4,0.7,2.0,167,7615445)
	self:setMoodString(pNpc, "npc_use_terminal_high")

	--newb grind starter spawns
	spawnMobile("corellia", "durni", 300, getRandomNumber(10) + -5379, 5.7, getRandomNumber(10) + -6418, getRandomNumber(360), 0)
	spawnMobile("corellia", "durni", 300, getRandomNumber(10) + -5379, 5.7, getRandomNumber(10) + -6418, getRandomNumber(360), 0)
	spawnMobile("corellia", "durni", 300, getRandomNumber(10) + -5379, 5.7, getRandomNumber(10) + -6418, getRandomNumber(360), 0)
	spawnMobile("corellia", "durni", 300, getRandomNumber(10) + -5379, 5.7, getRandomNumber(10) + -6418, getRandomNumber(360), 0)
	spawnMobile("corellia", "durni", 300, getRandomNumber(10) + -5379, 5.7, getRandomNumber(10) + -6418, getRandomNumber(360), 0)
	spawnMobile("corellia", "meatlump_fool", 300, getRandomNumber(10) + -5529, 11.4, getRandomNumber(10) + -6353, getRandomNumber(360), 0)
	spawnMobile("corellia", "meatlump_fool", 300, getRandomNumber(10) + -5529, 11.4, getRandomNumber(10) + -6353, getRandomNumber(360), 0)
	spawnMobile("corellia", "meatlump_fool", 300, getRandomNumber(10) + -5529, 11.4, getRandomNumber(10) + -6353, getRandomNumber(360), 0)

end
