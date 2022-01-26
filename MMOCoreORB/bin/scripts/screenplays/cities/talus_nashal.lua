TalusNashalScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TalusNashalScreenPlay",

	planet = "talus",

	patrolNpcs = {"businessman_patrol", "commoner_fat_patrol", "commoner_old_patrol", "commoner_patrol", "noble_patrol", "scientist_patrol"},

	patrolMobiles = {
		--{patrolPoints, template, x, z, y, direction, cell, mood, combatPatrol},

		--Droids
		{"cll8_1", "cll8_binary_load_lifter", 4217.52, 2, 5296.68, 76.6695, 0, "", false},
		{"cll8_2", "cll8_binary_load_lifter", 4208.89, 2, 5145.09, 260.13, 0, "", false},
		{"cll8_3", "cll8_binary_load_lifter", 4346.08, 2, 5094.9, 161.894, 0, "", false},
		{"cll8_4", "cll8_binary_load_lifter", 4476, 2, 5203, 270, 0, "", false},
		{"eg6_1", "eg6_power_droid", 4198.79, 2, 5292.24, 256.749, 0, "", false},
		{"eg6_2", "eg6_power_droid", 4347.08, 2, 5093.9, 348.335, 0, "", false},
		{"eg6_3", "eg6_power_droid", 4453.98, 2, 5284.27, 173.875, 0, "", false},
		{"eg6_4", "eg6_power_droid", 4533.97, 2, 5111.71, 341.356, 0, "", false},
		{"eg6_5", "eg6_power_droid", 4465.98, 2, 5278.48, 300.387, 0, "", false},
		{"r4_1", "r4", 4267.23, 2, 5151.46, 66.4568, 0, "", false},
		{"r4_2", "r4", 4531.97, 2, 5111.71, 209.78, 0, "", false},

		--NPCs
		{"npc_1", "patrolNpc", 4418, 2, 5271, 49, 0, "", false},
		{"npc_2", "patrolNpc", 4533, 2, 5286, 16, 0, "", false},
		{"npc_3", "patrolNpc", 4554, 2, 5053, 49, 0, "", false},
		{"npc_4", "patrolNpc", 4385, 2, 5049, 303, 0, "", false},
		{"npc_5", "patrolNpc", 4353, 2, 5125, 65, 0, "", false},
		{"npc_6", "patrolNpc", 4373, 2, 5165, 352, 0, "", false},
		{"npc_7", "patrolNpc", 4327, 2, 5201, 45, 0, "", false},
		{"npc_8", "patrolNpc", 4238, 2, 5126, 255, 0, "", false},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}
		cll8_1 = {{4217, 2, 5296, 0, false}, {4234.2, 2, 5287.9, 0, true}, {4334.1, 2, 5287.8, 0, false}, {4234.2, 2, 5287.9, 0, false}, {4223, 2, 5328, 0, false}},
		cll8_2 = {{4208, 2, 5154, 0, false}, {4177.0, 2, 5132.1, 0, true}, {4161, 2, 5116, 0, false}, {4162, 2, 5134, 0, false}, {4187.7, 2, 5143.2, 0, true}},
		cll8_3 = {{4354, 2, 5093, 0, false}, {4372.1, 2, 5105.9, 0, false}, {4478.9, 2.1, 5145.1, 0, false}, {4477.7, 2, 5147.7, 0, false}, {4371.1, 2, 5108.2, 0, false}},
		cll8_4 = {{4476, 2, 5203, 0, false}, {4462, 2, 5207, 0, false}, {4420, 2, 5254, 0, false}, {4431, 2, 5276, 0, true}, {4465, 2, 5264, 0, 1}, {4464.9, 2, 5230, 0, false}},
		eg6_1 = {{4198, 2, 5292, 0, false}, {4185, 2, 5288, 0, false}, {4187, 2, 5279, 0, false}, {4164, 2, 5292, 0, false}},
		eg6_2 = {{4346, 2, 5090, 0, false}, {4348, 2, 5077, 0, false}, {4339, 2, 5067, 0, false}, {4337, 2, 5053, 0, false}, {4355, 2, 5067, 0, false}},
		eg6_3 = {{4453, 2, 5284, 0, false}, {4439, 2, 5283, 0, false}, {4426, 2, 5291, 0, false}, {4411.4, 2, 5323.7, 0, false}, {4367.2, 2, 5283.0, false}, {4398, 2, 5270, 0, false}},
		eg6_4 = {{4533, 2, 5111, 0, false}, {4526, 2, 5134, 0, false}, {4526, 2, 5146, 0, true}, {4518, 2, 5143, false}},
		eg6_5 = {{4465, 2, 5278, 0, false}, {4458, 2, 5276, 0, false}, {4490, 2, 5258, 0, false}, {4533, 2, 5280, 0, false}, {4498, 2, 5271, 0, false}},
		r4_1 = {{4267, 2, 5151, 0, false}, {4276, 2, 5153, 0, false}, {4276, 2, 5165, 0, false}, {4253, 2, 5173, 0, false}, {4258, 2, 5150, 0, false}},
		r4_2 = {{4531, 2, 5111, 0, false}, {4523, 2, 5109, 0, true}, {4529, 2, 5095, 0, false}, {4520, 2, 5118, 0, true}, {4521, 2, 5128, 0, false}},

		npc_1 = {{4418, 2, 5271, 0, true}, {4336, 2, 5249, 0, true}, {4440, 2, 5238, 0, true}, {4426, 2, 5252, 0, true}},
		npc_2 = {{4533, 2, 5286, 0, true}, {4509, 2, 5276, 0, true}, {4494, 2, 5277, 0, true}, {4497, 2, 5249, 0, true}, {4520, 0, 5284, 0, true}},
		npc_3 = {{4554, 2, 5053, 0, true}, {4538, 2, 5045, 0, true}, {4517, 2, 5062, 0, true}, {4537, 2, 5054, 0, true}},
		npc_4 = {{4385, 2, 5049, 0, true}, {4368, 2, 5061, 0, true}, {4370, 2, 5077, 0, true}, {4387, 2, 5064, 0, true}, {4390, 2, 5040, 0, true}},
		npc_5 = {{4353, 2, 5125, 0, true}, {4363, 2, 5136, 0, true}, {4363, 2, 5115, 0, true}, {4345, 2, 5120, 0, true}},
		npc_6 = {{4373, 2, 5165, 0, true}, {4381, 2, 5168, 0, true}, {4377, 2, 5172, 0, true}, {4366, 2, 5180, 0, true}, {4364, 2, 5156, 0, true}},
		npc_7 = {{4327, 2, 5201, 0, true}, {4343, 2, 5209, 0, true}, {4351, 2, 5201, 0, true}, {4300, 2, 5201, 0, true}, {4287, 2, 5192, 0, true}},
		npc_8 = {{4238, 2, 5126, 0, true}, {4223, 2, 5131, 0, true}, {4244, 2, 5124, 0, true}, {4244, 2, 5137, 0, true}, {4233, 2, 5146, 0, true}},
	},

	stationaryCommoners = {"commoner", "commoner_fat", "commoner_old"},
	stationaryNpcs = {"agriculturalist", "artisan", "bodyguard", "bothan_diplomat", "bounty_hunter", "businessman", "commoner_technician", "contractor", "entertainer", "explorer", "farmer", "farmer_rancher", "fringer",
			"gambler", "info_broker", "insurgent", "ithorian_male", "medic", "mercenary", "miner", "noble", "official", "pilot", "rancher", "scientist", "slicer", "smuggler", "vendor", "weak_mercenary"},

	--{respawn, x, z, y, direction, cell, mood}
	stationaryMobiles = {
		{ 1, 4119.69, 2, 5300.03, 180, 0, "conversation"}, { 1, 4477.16, 2, 5155.72, 0, 0, "conversation"}, { 1, 4446.01, 2, 5422.27, 0, 0, "conversation"}, { 1, 4446.01, 2, 5423.27, 180, 0, "conversation"},
		{ 1, 4073.98, 2, 5272.83, 0, 0, "conversation"}, { 1, 4376.54, 2, 5050.29, 0, 0, "conversation"}, { 1, 4554.99, 2, 5424.67, 180, 0, "angry"}, { 1, 4119.69, 2, 5299.03, 0, 0, "conversation"},
		{ 1, 4107.57, 2, 5309.03, 0, 0, "conversation"}, { 1, 4379.3, 1.7, 5185.72, 7, 0, "conversation"}, { 1, 4535.24, 2, 5068.78, 0, 0, "conversation"}, { 1, 4437.59, 2, 5253.67, 180, 0, "conversation"},
		{ 1, 4161.59, 2, 5292.72, 0, 0, "conversation"}, { 1, 4256.4, 2, 5284.54, 180, 0, "conversation"}, { 1, 4397.73, 2, 5291.48, 180, 0, "conversation"}, { 1, 4256.4, 2, 5283.54, 0, 0, "conversation"},
		{ 1, 4292.68, 9.9, 5407.93, 0, 0, "conversation"}, { 1, 4394.07, 2, 5397.99, 180, 0, "conversation"}, { 1, 4305.6, 9.9, 5364.33, 0, 0, "conversation"}, { 1, 4394.07, 2, 5396.99, 0, 0, "conversation"},
		{ 1, 4379.3, 1.6, 5186.72, 180, 0, "conversation"}, { 1, 4516.71, 2, 5494.23, 0, 0, "conversation"}, { 1, 4535.24, 2, 5069.78, 180, 0, "conversation"}, { 1, 4558.42, 2, 5302.88, 0, 0, "conversation"},
		{ 1, 4161.59, 2, 5293.72, 180, 0, "conversation"}, { 1, 4437.59, 2, 5252.67, 0, 0, "conversation"}, { 1, 4554.99, 2, 5423.67, 0, 0, "conversation"}, { 1, 4039.56, 2, 5264.96, 180, 0, "conversation"},
		{ 1, 4039.56, 2, 5263.96, 0, 0, "conversation"}, { 1, 4323.72, 2, 5292.6, 0, 0, "conversation"}, { 1, 4501.35, 2, 5439.72, 180, 0, "conversation"}, { 1, 4249.5, 2, 5167.3, 30, 0, "conversation"},
		{ 1, 4477.16, 2, 5156.72, 180, 0, "conversation"}, { 1, 4547.7, 2, 5094.7, 86, 0, "conversation"}, { 1, 4107.57, 2, 5310.03, 180, 0, "conversation"}, { 1, 4332.89, 2, 5052.68, 180, 0, "conversation"},
		{ 1, 4550, 2, 5095.2, 260, 0, "conversation"}, { 1, 4513.66, 2, 5125.31, 0, 0, "conversation"}, { 1, 4189.74, 2, 5154.9, 0, 0, "worried"}, { 1, 4279.23, 2, 5156.4, 0, 0, "conversation"},
		{ 1, 4516.71, 2, 5495.23, 180, 0, "conversation"}, { 1, 4397.73, 2, 5290.48, 0, 0, "conversation"}, { 1, 4166, 2, 5102.7, 305, 0, "conversation"}, { 1, 4305.6, 9.9, 5365.33, 180, 0, "conversation"},
		{ 1, 4332.89, 2, 5051.68, 0, 0, "conversation"}, { 1, 4279.23, 2, 5157.4, 180, 0, "conversation"}, { 1, 4078.96, 2, 5278.86, 214, 0, ""}, { 1, 4074.05, 2, 5234.8, 288, 0, ""},
		{ 1, 4034.88, 2, 5261.41, 113, 0, ""}, { 1, 4033.55, 2, 5229.69, 148, 0, ""}, { 1, 4164.28, 2, 5103.98, 121, 0, ""}, { 1, 4175.7, 2, 5095.4, 0, 0, ""},
		{ 1, 4166.92, 2, 5127.65, 140, 0, ""}, { 1, 4177.46, 2, 5145.22, 146, 0, ""}, { 1, 4195.48, 2, 5287.32, 246, 0, ""}, { 1, 4147.54, 2, 5274.21, 241, 0, ""},
		{ 1, 4135.13, 2, 5308.3, 211, 0, ""}, { 1, 4123.51, 2, 5293.84, 312, 0, ""}, { 1, 4102.2, 2, 5277.67, 39, 0, ""}, { 1, 4207.86, 2, 5152.88, 173, 0, ""},
		{ 1, 4232.36, 2, 5110.24, 59, 0, ""}, { 1, 4251.97, 2, 5136.77, 181, 0, ""}, { 1, 4273.97, 2, 5144.19, 270, 0, ""}, { 1, 4265.95, 2, 5153.96, 121, 0, ""},
		{ 1, 4250.53, 2, 5168.77, 218, 0, ""}, { 1, 4277.51, 2, 5167.11, 224, 0, ""}, { 1, 4294.13, 2, 5184.49, 186, 0, ""}, { 1, 4299.49, 9.9, 5360.88, 84, 0, ""},
		{ 1, 4291.34, 9.9, 5443.67, 74, 0, ""}, { 1, 4294.6, 9.9, 5413.01, 332, 0, ""}, { 1, 4214.12, 2, 5329.97, 65, 0, ""}, { 1, 4231.38, 2, 5315.35, 345, 0, ""},
		{ 1, 4319.51, 2, 5215.01, 41, 0, ""}, { 1, 4337.75, 2, 5214.84, 85, 0, ""}, { 1, 4354.1, 2, 5181.93, 278, 0, ""}, { 1, 4354.9, 2, 5147.42, 93, 0, ""},
		{ 1, 4347.05, 2, 5112.91, 11, 0, ""}, { 1, 4343.94, 2, 5078.72, 40, 0, ""}, { 1, 4334.85, 2, 5058.17, 194, 0, ""}, { 1, 4338.26, 2, 5048.56, 233, 0, ""},
		{ 1, 4346.26, 2, 5064.99, 353, 0, ""}, { 1, 4363.41, 2, 5087.4, 343, 0, ""}, { 1, 4388.77, 2, 5031.19, 96, 0, ""}, { 1, 4373.33, 2, 5019.99, 60, 0, ""},
		{ 1, 4390.82, 2, 5421.7, 352, 0, ""}, { 1, 4346.84, 9.9, 5434.8, 235, 0, ""}, { 1, 4341.5, 9.9, 5386.97, 232, 0, ""}, { 1, 4351.06, 2, 5305.44, 109, 0, ""},
		{ 1, 4469.92, 2, 5183.13, 338, 0, ""}, { 1, 4469.81, 2, 5211.71, 85, 0, ""}, { 1, 4489.46, 2, 5269.07, 193, 0, ""}, { 1, 4471.96, 2, 5465.89, 161, 0, ""},
		{ 1, 4441.2, 2, 5419.9, 134, 0, ""}, { 1, 4411.54, 2, 5392.8, 293, 0, ""}, { 1, 4416.41, 2, 5382.04, 200, 0, ""}, { 1, 4423.37, 2, 5399.32, 4, 0, ""},
		{ 1, 4552.86, 2, 5081.17, 153, 0, ""}, { 1, 4538.23, 2, 5066.62, 267, 0, ""}, { 1, 4554.85, 2, 5091.06, 118, 0, ""}, { 1, 4535.93, 2, 5113.65, 200, 0, ""},
		{ 1, 4512.53, 2, 5129.35, 167, 0, ""}, { 1, 4523.05, 2, 5141.12, 219, 0, ""}, { 1, 4517.5, 2, 5197.55, 99, 0, ""}, { 1, 4551.45, 2, 5310.32, 174, 0, ""},
		{ 1, 4548.45, 2, 5336.77, 142, 0, ""}, { 1, 4527.96, 2, 5505.62, 305, 0, ""},
	},

	mobiles = {
		--starport interior
		{"pilot",60,-54.5,2.6,44.7,69,4265367, "npc_consoling"},
		{"devaronian_male",60,-25.9,1.6,50.9,-87,4265364, "npc_sitting_table_eating"},

		--misc
		{"informant_npc_lvl_1",0,4214,2,5140,0,0, ""},
		{"informant_npc_lvl_1",0,4224,2,5117,70,0, ""},
		{"informant_npc_lvl_1",0,4277,2,5140,315,0, ""},
		{"informant_npc_lvl_1",0,4290,2,5202,120,0, ""},
		{"informant_npc_lvl_1",0,4350,2,5059,315,0, ""},
		{"informant_npc_lvl_1",0,4353,2,5196,0,0, ""},
		{"informant_npc_lvl_1",0,4519,2,5191,0,0, ""},
		{"informant_npc_lvl_1",0,4530,2,5094,250,0, ""},
		{"informant_npc_lvl_2",0,4542,2,5329,20,0, ""},
		{"informant_npc_lvl_3",0,4529,2,5371,260,0, ""},
		{"rebel_recruiter",1,4072,2,5289,135,0, ""},
		{"junk_dealer", 0, 4541.9, 2, 5278.5, -64, 0, ""},
		{"junk_dealer", 0, -14.6, 1.1, 2.6, 115, 4265404, ""},
		{"junk_dealer", 0, 4142.2, 2, 5313.48, -144, 0, ""},


		--trainers
		{"trainer_2hsword",1,11,1.1,-11.4,0,4265405, ""},
		{"trainer_architect",1,11,1,-14,0,4265415, ""},
		{"trainer_armorsmith",1,-15,1,0,90,4265414, ""},
		{"trainer_artisan",1,0,1,-14.5,0,4265396, ""},
		{"trainer_artisan",1,4410,2,5309,89,0, ""},
		{"trainer_bioengineer",1,18,1.566,14,90,4265423, ""},
		{"trainer_brawler",1,-11,1,-13,0,4265407, ""},
		{"trainer_chef",1,-11,1,-14,0,4265397, ""},
		{"trainer_chef",1,4283,2,5172,0,0, ""},
		{"trainer_combatmedic",1,4398.7,2,5365.2,200,0, ""},
		{"trainer_combatmedic",1,8,0,5.5,86,4265477, ""},
		{"trainer_commando",1,-3,1,-9,90,4265406, ""},
		{"trainer_creaturehandler",1,4467,2,5482,0,0, ""},
		{"trainer_doctor",1,-1,0.184,-3,83,4265477, ""},
		{"trainer_doctor",1,4491,2,5182,315,0, ""},
		{"trainer_droidengineer",1,-11,1,-14,0,4265417, ""},
		{"trainer_droidengineer",1,4290.5,9.9,5451,140,0, ""},
		{"trainer_entertainer",1,23.5,0,11.6,174,4265375, ""},
		{"trainer_entertainer",1,4331.4,2,5333,90,0, ""},
		{"trainer_imagedesigner",1,4347,2,5054,315,0, ""},
		{"trainer_marksman",1,0,1,-14,0,4265406, ""},
		{"trainer_medic",1,4398,2,5281,180,0, ""},
		{"trainer_medic",1,5,0,-8,28,4265477, ""},
		{"trainer_merchant",1,12,1,6,180,4265413, ""},
		{"trainer_merchant",1,4396,2,5344,250,0, ""},
		{"trainer_musician",1,4365,2,5319,270,0, ""},
		{"trainer_pistol",1,4366,2,5294,270,0, ""},
		{"trainer_polearm",1,4408.3,2,5287.6,90,0, ""},
		{"trainer_ranger",1,4234,0.5,5263,330,0, ""},
		{"trainer_rifleman",1,12,1.1,5.3,180,4265403, ""},
		{"trainer_scout",1,-12,1,5,180,4265404, ""},
		{"trainer_scout",1,4373.71,2,5302.45,89,0, ""},
		{"trainer_smuggler",60,3,1,-8.5,270,4265406, ""},
		{"trainer_tailor",1,-12,1,6,180,4265414, ""},
		{"trainer_tailor",1,11,1,-14,0,4265395, ""},
		{"trainer_weaponsmith",1,0,1,-14,0,4265416, ""},

		--Misc Outside
		{"hunter",300,4501.35,2,5438.72,0,0, "conversation"},
		--Cloner
		{"medic",60,1.8,-4.8,0,180,4265616, "conversation"},
		{"scientist",60,1.6,-5.5,-4.8,0,4265616, "conversation"},

		--Med Center
		{"surgical_droid_21b",60,-1.19,0.184067,-1.89,27.0574,4265477, ""},

		--Guild Hall 4291 5395
		{"chiss_male",300,-14.01,1.13306,-8.53,120.004,4265407, ""},

		--Hotel
		{"farmer",60,-1.7,1,-2.5,37,4265422, "npc_sitting_chair"},
		{"entertainer",60,-17.2742,1,-4.08488,360.011,4265424, "conversation"},
		{"devaronian_male",60,-16.989,1.6,10.4506,0,4265424, "conversation"},
		{"pilot",60,-16.989,1.6,11.4506,179.996,4265424, "conversation"},
		{"mercenary",300,-17.2742,1.00015,-2.98488,180,4265424, "npc_accusing"},
		{"info_broker",60,-17.2353,1.6,-13.9646,180.007,4265427, "conversation"},
		{"commoner",60,-17.2353,1.6,-15.0646,0,4265427, "conversation"},
		{"vendor",60,-18.3353,1.6,-13.9646,135.009,4265427, "worried"},
		{"noble",60,25.8451,1.28309,-1.92994,180.018,4265423, "conversation"},
		{"businessman",60,25.8451,1.28309,-3.02994,360.011,4265423, "conversation"},
		{"corellia_times_investigator",60,25.7677,1.28309,8.41503,360.011,4265423, "conversation"},
		{"bounty_hunter",300,16.326,1.28309,10.047,180.01,4265423, "conversation"},
		{"medic",60,25.7677,1.28309,9.41503,180.008,4265423, "conversation"},
		{"mercenary",300,15.226,1.28309,10.047,135.013,4265423, "conversation"},

		--Starport
		{"brawler",60,5.81535,0.639421,60.0653,0,4265359, "angry"},
		{"comm_operator",300,5.81535,0.639421,61.0653,180.005,4265359, "npc_imperial"},
		{"farmer_rancher",60,-5.66994,0.639423,55.6418,179.998,4265359, "conversation"},
		{"sullustan_male",300,46.424,0.639418,45.4992,0,4265362, "conversation"},
		{"ithorian_male",300,46.4,0.6,46.7,-177,4265362, "explain"},
		{"chiss_female",60,-53.4306,2.63942,44.8995,360.011,4265367, "conversation"},

		--Cantina
		{"bounty_hunter",60,35.6665,0.105,2.3343,180.006,4265374, "angry"},
		{"seeker",300,35.6665,0.105,1.2343,360.011,4265374, "neutral"},
		{"ithorian_male",300,21.4737,-0.894997,-13.904,180.01,4265376, "conversation"},
		{"artisan",60,21.4737,-0.894997,-14.904,360.011,4265376, "conversation"},
		{"artisan",60,2.49489,-0.894992,-5.58394,0,4265375, "conversation"},
		{"bartender",60,5.78939,-0.894992,3.21743,198.905,4265375, "conversation"},
		{"info_broker",60,11.3604,-0.894992,5.58351,180.01,4265375, "conversation"},
		{"commoner_technician",60,2.49489,-0.894992,-4.58394,179.992,4265375, "conversation"},
		{"insurgent",60,11.3604,-0.894992,4.58351,360.011,4265375, "nervous"}
	}
}

registerScreenPlay("TalusNashalScreenPlay", true)

function TalusNashalScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
		self:spawnStationaryMobiles()
		self:spawnSceneObjects()
	end
end

function TalusNashalScreenPlay:spawnSceneObjects()
	--outside starport
	spawnSceneObject(self.planet, "object/tangible/crafting/station/public_space_station.iff", 4433.46, 2, 5300.02, 0, math.rad(-125) )
end

function TalusNashalScreenPlay:spawnMobiles()
	local mobiles = self.mobiles

	for i = 1, #mobiles, 1 do
		local mob = mobiles[i]

		-- {template, respawn, x, z, y, direction, cell, mood}
		local pMobile = spawnMobile(self.planet, mob[1], mob[2], mob[3], mob[4], mob[5], mob[6], mob[7])

		if (pMobile ~= nil) then
			if mob[8] ~= "" then
				CreatureObject(pMobile):setMoodString(mob[8])
			end

			AiAgent(pMobile):addCreatureFlag(AI_STATIC)

			if CreatureObject(pMobile):getPvpStatusBitmask() == 0 then
				CreatureObject(pMobile):clearOptionBit(AIENABLED)
			end
		end
	end

	local pNpc = spawnMobile(self.planet, "junk_dealer", 0, 4262.49, 2, 5146.93, 0, 0)
	if pNpc ~= nil then
		AiAgent(pNpc):setConvoTemplate("junkDealerFineryConvoTemplate")
	end

	--thugs
	spawnMobile(self.planet, "chunker_mooch", 300, 4096, 2, 5299, 54, 0)
	spawnMobile(self.planet, "chunker_mooch", 300, 4099, 2, 5288, 4, 0)
	spawnMobile(self.planet, "chunker_mooch", 300, 4093, 2, 5295, 160, 0)
	spawnMobile(self.planet, "chunker_nitwit", 300, 4253, 2, 5141, 129, 0)
	spawnMobile(self.planet, "chunker_nitwit", 300, 4252, 2, 5156, 32, 0)
	spawnMobile(self.planet, "chunker_nitwit", 300, 4249, 2, 5151, 237, 0)
	spawnMobile(self.planet, "chunker_nitwit", 300, 4245, 2, 5150, 91, 0)
	spawnMobile(self.planet, "fed_dub_captain", 300, 4149, 2, 5129, 220, 0)
	spawnMobile(self.planet, "fed_dub_captain", 300, 4520, 2, 5532, 74, 0)
	spawnMobile(self.planet, "fed_dub_captain", 300, 4525, 2, 5047, 337, 0)
	spawnMobile(self.planet, "fed_dub_constable", 300, 4178, 2, 5114, 117, 0)
	spawnMobile(self.planet, "fed_dub_constable", 300, 4356, 2, 5213, 44, 0)
	spawnMobile(self.planet, "fed_dub_constable", 300, 4370, 2, 5023, 68, 0)
	spawnMobile(self.planet, "fed_dub_constable", 300, 4521, 2, 5533, 74, 0)
	spawnMobile(self.planet, "fed_dub_constable", 300, 4529, 2, 5035, 343, 0)
	spawnMobile(self.planet, "fed_dub_constable", 300, 4367, 2, 5015, 67, 0)
	spawnMobile(self.planet, "fed_dub_constable", 300, 4369, 2, 5013, 60, 0)
	spawnMobile(self.planet, "fed_dub_investigator", 300, 4356, 2, 5214, 36, 0)
	spawnMobile(self.planet, "fed_dub_investigator", 300, 4176, 2, 5114, 296, 0)
	spawnMobile(self.planet, "fed_dub_investigator", 300, 4524, 2, 5049, 305, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 4035, 2, 5220, 232, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 4151, 2, 5127, 240, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 4355, 2, 5216, 50, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 4176, 2, 5115, 117, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 4381, 2, 5019, 23, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 4367.6, 2, 5013.9, 53, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 4531, 2, 5035, 147, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 4519, 2, 5532, 74, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 4530, 2, 5032, 343, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 4518, 2, 5531, 74, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 4517, 2, 5532, 174, 0)
	spawnMobile(self.planet, "fed_dub_patrolman", 300, 4354, 2, 5213, 36, 0)
	spawnMobile(self.planet, "sleemo_delinquent", 300, 4432, 2, 5439, 166, 0)
	spawnMobile(self.planet, "sleemo_delinquent", 300, 4432, 2, 5437, 327, 0)
	spawnMobile(self.planet, "sleemo_delinquent", 300, 4429, 2, 5438, 235, 0)
	spawnMobile(self.planet, "sleemo_hoodlum", 300, 4510, 2, 5073, 317, 0)
	spawnMobile(self.planet, "sleemo_hoodlum", 300, 4508, 2, 5079, 301, 0)
	spawnMobile(self.planet, "sleemo_hoodlum", 300, 4507, 2, 5084, 300, 0)
	spawnMobile(self.planet, "sleemo_hoodlum", 300, 4516, 2, 5076, 135, 0)

	--newb grind starter spawns
	spawnMobile(self.planet, "clipped_fynock", 300, getRandomNumber(10) + 4563, 2.8, getRandomNumber(10) + 5503, getRandomNumber(360), 0)
	spawnMobile(self.planet, "clipped_fynock", 300, getRandomNumber(10) + 4563, 2.8, getRandomNumber(10) + 5503, getRandomNumber(360), 0)
	spawnMobile(self.planet, "clipped_fynock", 300, getRandomNumber(10) + 4563, 2.8, getRandomNumber(10) + 5503, getRandomNumber(360), 0)
	spawnMobile(self.planet, "clipped_fynock", 300, getRandomNumber(10) + 4563, 2.8, getRandomNumber(10) + 5503, getRandomNumber(360), 0)
	spawnMobile(self.planet, "clipped_fynock", 300, getRandomNumber(10) + 4563, 2.8, getRandomNumber(10) + 5503, getRandomNumber(360), 0)

	spawnMobile(self.planet, "song_rasp", 300, getRandomNumber(10) + 4237.4, 28.6, getRandomNumber(10) + 5389.7, getRandomNumber(360), 0)
	spawnMobile(self.planet, "song_rasp", 300, getRandomNumber(10) + 4237.4, 28.6, getRandomNumber(10) + 5389.7, getRandomNumber(360), 0)
	spawnMobile(self.planet, "song_rasp", 300, getRandomNumber(10) + 4237.4, 28.6, getRandomNumber(10) + 5389.7, getRandomNumber(360), 0)
	spawnMobile(self.planet, "song_rasp", 300, getRandomNumber(10) + 4237.4, 28.6, getRandomNumber(10) + 5389.7, getRandomNumber(360), 0)
	spawnMobile(self.planet, "song_rasp", 300, getRandomNumber(10) + 4237.4, 28.6, getRandomNumber(10) + 5389.7, getRandomNumber(360), 0)
end
