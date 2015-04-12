TalusNashalScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TalusNashalScreenPlay"
}

registerScreenPlay("TalusNashalScreenPlay", true)

function TalusNashalScreenPlay:start()
	if (isZoneEnabled("talus")) then
		self:spawnMobiles()
	end
end

function TalusNashalScreenPlay:spawnMobiles()
	--thugs
	spawnMobile("talus", "chunker_mooch", 300, 4096, 2, 5299, 54, 0)
	spawnMobile("talus", "chunker_mooch", 300, 4099, 2, 5288, 4, 0)
	spawnMobile("talus", "chunker_mooch", 300, 4093, 2, 5295, 160, 0)
	spawnMobile("talus", "chunker_nitwit", 300, 4253, 2, 5141, 129, 0)
	spawnMobile("talus", "chunker_nitwit", 300, 4252, 2, 5156, 32, 0)
	spawnMobile("talus", "chunker_nitwit", 300, 4249, 2, 5151, 237, 0)
	spawnMobile("talus", "chunker_nitwit", 300, 4245, 2, 5150, 91, 0)
	spawnMobile("talus", "fed_dub_captain", 300, 4149, 2, 5129, 220, 0)
	spawnMobile("talus", "fed_dub_captain", 300, 4520, 2, 5532, 74, 0)
	spawnMobile("talus", "fed_dub_captain", 300, 4525, 2, 5047, 337, 0)
	spawnMobile("talus", "fed_dub_constable", 300, 4178, 2, 5114, 117, 0)
	spawnMobile("talus", "fed_dub_constable", 300, 4356, 2, 5213, 44, 0)
	spawnMobile("talus", "fed_dub_constable", 300, 4370, 2, 5023, 68, 0)
	spawnMobile("talus", "fed_dub_constable", 300, 4521, 2, 5533, 74, 0)
	spawnMobile("talus", "fed_dub_constable", 300, 4529, 2, 5035, 343, 0)
	spawnMobile("talus", "fed_dub_constable", 300, 4367, 2, 5015, 67, 0)
	spawnMobile("talus", "fed_dub_constable", 300, 4369, 2, 5013, 60, 0)
	spawnMobile("talus", "fed_dub_investigator", 300, 4356, 2, 5214, 36, 0)
	spawnMobile("talus", "fed_dub_investigator", 300, 4176, 2, 5114, 296, 0)
	spawnMobile("talus", "fed_dub_investigator", 300, 4524, 2, 5049, 305, 0)
	spawnMobile("talus", "fed_dub_patrolman", 300, 4029, 2, 5241, 232, 0)
	spawnMobile("talus", "fed_dub_patrolman", 300, 4151, 2, 5127, 240, 0)
	spawnMobile("talus", "fed_dub_patrolman", 300, 4355, 2, 5216, 50, 0)
	spawnMobile("talus", "fed_dub_patrolman", 300, 4176, 2, 5115, 117, 0)
	spawnMobile("talus", "fed_dub_patrolman", 300, 4381, 2, 5019, 23, 0)
	spawnMobile("talus", "fed_dub_patrolman", 300, 4367.6, 2, 5013.9, 53, 0)
	spawnMobile("talus", "fed_dub_patrolman", 300, 4531, 2, 5035, 147, 0)
	spawnMobile("talus", "fed_dub_patrolman", 300, 4519, 2, 5532, 74, 0)
	spawnMobile("talus", "fed_dub_patrolman", 300, 4530, 2, 5032, 343, 0)
	spawnMobile("talus", "fed_dub_patrolman", 300, 4518, 2, 5531, 74, 0)
	spawnMobile("talus", "fed_dub_patrolman", 300, 4517, 2, 5532, 174, 0)
	spawnMobile("talus", "fed_dub_patrolman", 300, 4354, 2, 5213, 36, 0)
	spawnMobile("talus", "sleemo_delinquent", 300, 4432, 2, 5439, 166, 0)
	spawnMobile("talus", "sleemo_delinquent", 300, 4432, 2, 5437, 327, 0)
	spawnMobile("talus", "sleemo_delinquent", 300, 4429, 2, 5438, 235, 0)
	spawnMobile("talus", "sleemo_hoodlum", 300, 4510, 2, 5073, 317, 0)
	spawnMobile("talus", "sleemo_hoodlum", 300, 4508, 2, 5079, 301, 0)
	spawnMobile("talus", "sleemo_hoodlum", 300, 4507, 2, 5084, 300, 0)
	spawnMobile("talus", "sleemo_hoodlum", 300, 4516, 2, 5076, 135, 0)

	--misc
	spawnMobile("talus", "informant_npc_lvl_1",0,4214,2,5140,0,0)
	spawnMobile("talus", "informant_npc_lvl_1",0,4224,2,5117,70,0)
	spawnMobile("talus", "informant_npc_lvl_1",0,4277,2,5140,315,0)
	spawnMobile("talus", "informant_npc_lvl_1",0,4290,2,5202,120,0)
	spawnMobile("talus", "informant_npc_lvl_1",0,4350,2,5059,315,0)
	spawnMobile("talus", "informant_npc_lvl_1",0,4353,2,5196,0,0)
	spawnMobile("talus", "informant_npc_lvl_1",0,4519,2,5191,0,0)
	spawnMobile("talus", "informant_npc_lvl_1",0,4530,2,5094,250,0)
	spawnMobile("talus", "informant_npc_lvl_2",0,4542,2,5329,20,0)
	spawnMobile("talus", "informant_npc_lvl_3",0,4529,2,5371,260,0)
	--spawnMobile("talus", "junk_dealer",0,4541.9,2,5278.5,-64,0)
	spawnMobile("talus", "rebel_recruiter",1,4072,2,5289,135,0)

	--quest
	spawnMobile("talus", "durgur_pyne",60,3,0,4.3,342,4265614)
	spawnMobile("talus", "green_laser",60,10.1,-0.9,19.5,293,4265379)
	spawnMobile("talus", "jusani_zhord",60,20,1.3,-1,270,4265423)

	--trainers
	spawnMobile("talus", "trainer_2hsword",1,11,1.1,-11.4,0,4265405)
	spawnMobile("talus", "trainer_architect",1,11,1,-14,0,4265415)
	spawnMobile("talus", "trainer_armorsmith",1,-15,1,0,90,4265414)
	spawnMobile("talus", "trainer_artisan",1,0,1,-14.5,0,4265396)
	spawnMobile("talus", "trainer_artisan",1,4410,2,5309,89,0)
	spawnMobile("talus", "trainer_bioengineer",1,18,1.566,14,90,4265423)
	spawnMobile("talus", "trainer_brawler",1,-11,1,-13,0,4265407)
	spawnMobile("talus", "trainer_chef",1,-11,1,-14,0,4265397)
	spawnMobile("talus", "trainer_chef",1,4283,2,5172,0,0)
	spawnMobile("talus", "trainer_combatmedic",1,4398.7,2,5365.2,200,0)
	spawnMobile("talus", "trainer_combatmedic",1,8,0,5.5,86,4265477)
	spawnMobile("talus", "trainer_commando",1,-3,1,-9,90,4265406)
	spawnMobile("talus", "trainer_creaturehandler",1,4467,2,5482,0,0)
	spawnMobile("talus", "trainer_doctor",1,-1,0.184,-3,83,4265477)
	spawnMobile("talus", "trainer_doctor",1,4491,2,5182,315,0)
	spawnMobile("talus", "trainer_droidengineer",1,-11,1,-14,0,4265417)
	spawnMobile("talus", "trainer_droidengineer",1,4290.5,9.9,5451,140,0)
	spawnMobile("talus", "trainer_entertainer",1,23.5,0,11.6,174,4265375)
	spawnMobile("talus", "trainer_entertainer",1,4331.4,2,5333,90,0)
	spawnMobile("talus", "trainer_imagedesigner",1,4347,2,5054,315,0)
	spawnMobile("talus", "trainer_marksman",1,0,1,-14,0,4265406)
	spawnMobile("talus", "trainer_medic",1,4398,2,5281,180,0)
	spawnMobile("talus", "trainer_medic",1,5,0,-8,28,4265477)
	spawnMobile("talus", "trainer_merchant",1,12,1,6,180,4265413)
	spawnMobile("talus", "trainer_merchant",1,4396,2,5344,250,0)
	spawnMobile("talus", "trainer_musician",1,4365,2,5319,270,0)
	spawnMobile("talus", "trainer_pistol",1,4366,2,5294,270,0)
	spawnMobile("talus", "trainer_polearm",1,4408.3,2,5287.6,90,0)
	spawnMobile("talus", "trainer_ranger",1,4234,0.5,5263,330,0)
	spawnMobile("talus", "trainer_rifleman",1,12,1.1,5.3,180,4265403)
	spawnMobile("talus", "trainer_scout",1,-12,1,5,180,4265404)
	spawnMobile("talus", "trainer_scout",1,4373.71,2,5302.45,89,0)
	spawnMobile("talus", "trainer_smuggler",60,3,1,-8.5,270,4265406)
	spawnMobile("talus", "trainer_tailor",1,-12,1,6,180,4265414)
	spawnMobile("talus", "trainer_tailor",1,11,1,-14,0,4265395)
	spawnMobile("talus", "trainer_weaponsmith",1,0,1,-14,0,4265416)

	--Anything dashed out will need to be added here and removed from spawn manager once the spawnMobiles command is extended.

	--Misc Outside
	--{"agriculturalist",60,4119.69,2,5300.03,180.005,0, "conversation", ""},
	--{"agriculturalist",60,4477.16,2,5155.72,0,0, "conversation", ""},
	--{"agriculturalist",60,4446.01,2,5422.27,0,0, "conversation", ""},
	--{"agriculturalist",60,4446.01,2,5423.27,180.005,0, "conversation", ""},
	--{"artisan",60,4073.98,2,5272.83,0,0, "conversation", ""},
	--{"artisan",60,4376.54,2,5050.29,0,0, "conversation", ""},
	--{"bodyguard",300,4554.99,2,5424.67,180.005,0, "conversation", ""},
	--{"bothan_diplomat",60,4119.69,2,5299.03,0,0, "conversation", ""},
	--{"bothan_diplomat",60,4107.57,2,5309.03,0,0, "conversation", ""},
	--{"bothan_diplomat",60,4379.3,1.75007,5185.72,7.1663,0, "conversation", ""},
	--{"bothan_diplomat",60,4535.24,2,5068.78,0,0, "conversation", ""},
	--{"bounty_hunter",60,4437.59,2,5253.67,180.005,0, "conversation", ""},
	--{"businessman",60,4161.59,2,5292.72,0,0, "conversation", ""},
	--{"commoner",60,4256.4,2,5284.54,180.005,0, "conversation", ""},
	--{"commoner",60,4397.73,2,5291.48,180.005,0, "conversation", ""},
	--{"entertainer",60,4073.98,2,5273.83,180.005,0, "conversation", ""},
	--{"entertainer",60,4256.4,2,5283.54,0,0, "conversation", ""},
	--{"entertainer",60,4292.68,9.9,5407.93,0,0, "conversation", ""},
	--{"entertainer",60,4394.07,2,5397.99,180.005,0, "conversation", ""},
	--{"explorer",60,4305.6,9.9,5364.33,0,0, "conversation", ""},
	--{"farmer",60,4394.07,2,5396.99,0,0, "conversation", ""},
	--{"gambler",60,4379.3,1.62434,5186.72,180.005,0, "conversation", ""},
	--{"gambler",60,4516.71,2,5494.23,0,0, "conversation", ""},
	--{"hunter",300,4501.35,2,5438.72,0,0, "conversation", ""},
	--{"info_broker",60,4535.24,2,5069.78,180.005,0, "conversation", ""},
	--{"info_broker",60,4558.42,2,5302.88,0,0, "conversation", ""},
	--{"medic",60,4161.59,2,5293.72,180.005,0, "conversation", ""},
	--{"medic",60,4437.59,2,5252.67,0,0, "conversation", ""},
	--{"medic",60,4554.99,2,5423.67,0,0, "conversation", ""},
	--{"mercenary",60,4039.56,2,5264.96,180.005,0, "conversation", ""},
	--{"miner",60,4039.56,2,5263.96,0,0, "conversation", ""},
	--{"miner",60,4323.72,2,5292.6,0,0, "conversation", ""},
	--{"miner",60,4501.35,2,5439.72,180.005,0, "conversation", ""},
	--{"noble",60,4249.5,2,5167.3,30,0, "conversation", ""},
	--{"noble",60,4477.16,2,5156.72,180.005,0, "conversation", ""},
	--{"pilot",60,4547.7,2,5094.7,86,0, "conversation", ""},
	--{"protocol_droid_3po",60,4199,2,5286,112.01,0, "calm", "Race Coordinator"},
	--{"r4",60,4267.23,2,5151.46,66.4568,0, "calm", "R4-M7"},
	--{"r4",60,4531.97,2,5111.71,209.78,0, "calm", "R4-T7"},
	--{"rancher",60,4107.57,2,5310.03,180.005,0, "conversation", ""},
	--{"rancher",60,4332.89,2,5052.68,180.005,0, "conversation", ""},
	--{"rancher",60,4550,2,5095.2,260,0, "conversation", ""},
	--{"rancher",60,4513.66,2,5125.31,0,0, "conversation", ""},
	--{"scientist",60,4189.74,2,5154.9,0,0, "conversation", ""},
	--{"scientist",60,4279.23,2,5156.4,0,0, "conversation", ""},
	--{"scientist",60,4516.71,2,5495.23,180.005,0, "conversation", ""},
	--{"scoundrel",60,4397.73,2,5290.48,0,0, "conversation", ""},
	--{"slicer",60,4166,2,5102.7,305,0, "conversation", ""},
	--{"smuggler",300,4305.6,9.9,5365.33,180.005,0, "conversation", ""},
	--{"smuggler",300,4332.89,2,5051.68,0,0, "conversation", ""},
	--{"vendor",60,4279.23,2,5157.4,180.005,0, "conversation", ""},
	spawnMobile("talus", "cll8_binary_load_lifter",60,4217.52,2,5296.68,76.6695,0)
	spawnMobile("talus", "cll8_binary_load_lifter",60,4208.89,2,5145.09,260.13,0)
	spawnMobile("talus", "cll8_binary_load_lifter",60,4346.08,2,5094.9,161.894,0)
	spawnMobile("talus", "cll8_binary_load_lifter",60,4476,2,5203,270,0)
	spawnMobile("talus", "commoner",60,4078.96,2,5278.86,214.643,0)
	spawnMobile("talus", "commoner",60,4074.05,2,5234.8,288.21,0)
	spawnMobile("talus", "commoner",60,4034.88,2,5261.41,113.49,0)
	spawnMobile("talus", "commoner",60,4033.55,2,5229.69,148.075,0)
	spawnMobile("talus", "commoner",60,4164.28,2,5103.98,121.586,0)
	spawnMobile("talus", "commoner",60,4175.7,2,5095.4,0,0)
	spawnMobile("talus", "commoner",60,4166.92,2,5127.65,140.487,0)
	spawnMobile("talus", "commoner",60,4177.46,2,5145.22,146.377,0)
	spawnMobile("talus", "commoner",60,4188.76,2,5139.64,122.872,0)
	spawnMobile("talus", "commoner",60,4195.48,2,5287.32,246.878,0)
	spawnMobile("talus", "commoner",60,4147.54,2,5274.21,241.4,0)
	spawnMobile("talus", "commoner",60,4135.13,2,5308.3,211.556,0)
	spawnMobile("talus", "commoner",60,4123.51,2,5293.84,312.698,0)
	spawnMobile("talus", "commoner",60,4102.2,2,5277.67,39.5119,0)
	spawnMobile("talus", "commoner",60,4207.86,2,5152.88,173.052,0)
	spawnMobile("talus", "commoner",60,4238.06,2,5126.65,255.642,0)
	spawnMobile("talus", "commoner",60,4227.2,2,5116.75,297.654,0)
	spawnMobile("talus", "commoner",60,4223.88,2,5131.2,289.163,0)
	spawnMobile("talus", "commoner",60,4232.36,2,5110.24,59.1226,0)
	spawnMobile("talus", "commoner",60,4251.97,2,5136.77,181.025,0)
	spawnMobile("talus", "commoner",60,4273.97,2,5144.19,270.323,0)
	spawnMobile("talus", "commoner",60,4265.95,2,5153.96,121.121,0)
	spawnMobile("talus", "commoner",60,4250.53,2,5168.77,218.795,0)
	spawnMobile("talus", "commoner",60,4277.51,2,5167.11,224.996,0)
	spawnMobile("talus", "commoner",60,4294.13,2,5184.49,186.727,0)
	spawnMobile("talus", "commoner",60,4298.91,2,5198.36,213.471,0)
	spawnMobile("talus", "commoner",60,4299.49,9.9,5360.88,84.179,0)
	spawnMobile("talus", "commoner",60,4291.34,9.9,5443.67,74.9986,0)
	spawnMobile("talus", "commoner",60,4294.6,9.9,5413.01,332.889,0)
	spawnMobile("talus", "commoner",60,4214.12,2,5329.97,65.9855,0)
	spawnMobile("talus", "commoner",60,4231.38,2,5315.35,345.923,0)
	spawnMobile("talus", "commoner",60,4344.99,2,5202.61,20.8633,0)
	spawnMobile("talus", "commoner",60,4319.51,2,5215.01,41.2601,0)
	spawnMobile("talus", "commoner",60,4337.75,2,5214.84,85.2709,0)
	spawnMobile("talus", "commoner",60,4327.15,2,5201.98,45.3945,0)
	spawnMobile("talus", "commoner",60,4364.05,2,5184.78,32.0968,0)
	spawnMobile("talus", "commoner",60,4367.89,2,5148.11,203.791,0)
	spawnMobile("talus", "commoner",60,4373.46,2,5165.43,352.441,0)
	spawnMobile("talus", "commoner",60,4354.1,2,5181.93,278.144,0)
	spawnMobile("talus", "commoner",60,4354.9,2,5147.42,93.7641,0)
	spawnMobile("talus", "commoner",60,4347.05,2,5112.91,11.1082,0)
	spawnMobile("talus", "commoner",60,4343.94,2,5078.72,40.7068,0)
	spawnMobile("talus", "commoner",60,4353.37,2,5125.93,65.8798,0)
	spawnMobile("talus", "commoner",60,4334.85,2,5058.17,194.667,0)
	spawnMobile("talus", "commoner",60,4338.26,2,5048.56,233.088,0)
	spawnMobile("talus", "commoner",60,4346.26,2,5064.99,353.461,0)
	spawnMobile("talus", "commoner",60,4363.41,2,5087.4,343.951,0)
	spawnMobile("talus", "commoner",60,4388.77,2,5031.19,96.9441,0)
	spawnMobile("talus", "commoner",60,4373.33,2,5019.99,60.2531,0)
	spawnMobile("talus", "commoner",60,4385.1,2,5049.53,303.879,0)
	spawnMobile("talus", "commoner",60,4390.82,2,5421.7,352.903,0)
	spawnMobile("talus", "commoner",60,4346.84,9.9,5434.8,235.38,0)
	spawnMobile("talus", "commoner",60,4341.5,9.9,5386.97,232.581,0)
	spawnMobile("talus", "commoner",60,4351.06,2,5305.44,109.889,0)
	spawnMobile("talus", "commoner",60,4469.92,2,5183.13,338.74,0)
	spawnMobile("talus", "commoner",60,4469.81,2,5211.71,85.2223,0)
	spawnMobile("talus", "commoner",60,4489.46,2,5269.07,193.894,0)
	spawnMobile("talus", "commoner",60,4471.96,2,5465.89,161.466,0)
	spawnMobile("talus", "commoner",60,4441.2,2,5419.9,134.313,0)
	spawnMobile("talus", "commoner",60,4411.54,2,5392.8,293.309,0)
	spawnMobile("talus", "commoner",60,4416.41,2,5382.04,200.516,0)
	spawnMobile("talus", "commoner",60,4423.37,2,5399.32,4.32291,0)
	spawnMobile("talus", "commoner",60,4418.85,2,5271.39,49.0078,0)
	spawnMobile("talus", "commoner",60,4552.86,2,5081.17,153.88,0)
	spawnMobile("talus", "commoner",60,4538.23,2,5066.62,267.587,0)
	spawnMobile("talus", "commoner",60,4526.13,2,5057.36,310.865,0)
	spawnMobile("talus", "commoner",60,4554.59,2,5053.75,49.8274,0)
	spawnMobile("talus", "commoner",60,4554.85,2,5091.06,118.358,0)
	spawnMobile("talus", "commoner",60,4535.93,2,5113.65,200.868,0)
	spawnMobile("talus", "commoner",60,4512.53,2,5129.35,167.263,0)
	spawnMobile("talus", "commoner",60,4523.05,2,5141.12,219.056,0)
	spawnMobile("talus", "commoner",60,4517.5,2,5197.55,99.2433,0)
	spawnMobile("talus", "commoner",60,4551.45,2,5310.32,174.591,0)
	spawnMobile("talus", "commoner",60,4548.45,2,5336.77,142.777,0)
	spawnMobile("talus", "commoner",60,4533.27,2,5286.74,16.7138,0)
	spawnMobile("talus", "commoner",60,4527.96,2,5505.62,305.189,0)
	spawnMobile("talus", "commoner",60,4550.54,2,5436.9,346.678,0)
	spawnMobile("talus", "eg6_power_droid",60,4198.79,2,5292.24,256.749,0)
	spawnMobile("talus", "eg6_power_droid",60,4347.08,2,5093.9,348.335,0)
	spawnMobile("talus", "eg6_power_droid",60,4453.98,2,5284.27,173.875,0)
	spawnMobile("talus", "eg6_power_droid",60,4533.97,2,5111.71,341.356,0)
	spawnMobile("talus", "eg6_power_droid",60,4465.98,2,5278.48,300.387,0)

	--Cloner
	--{"miner",60,1.8,-4.8,0,180,4265616, "conversation", ""},
	--{"scientist",60,1.6,-5.5,-4.8,0,4265616, "conversation", ""},

	--Med Center
	spawnMobile("talus", "surgical_droid_21b",60,-1.19,0.184067,-1.89,27.0574,4265477)

	--Guild Hall 4291 5395
	spawnMobile("talus", "hunter",300,-14.01,1.13306,-8.53,120.004,4265407)

	--Hotel
	--{"farmer",60,-1.7,1,-2.5,37,4265422, "npc_sitting_chair", ""},
	--{"entertainer",60,-17.2742,1,-4.08488,360.011,4265424, "conversation", ""},
	--{"explorer",60,-16.989,1.6,10.4506,0,4265424, "conversation", ""},
	--{"pilot",60,-16.989,1.6,11.4506,179.996,4265424, "conversation", ""},
	--{"scoundrel",300,-17.2742,1.00015,-2.98488,180,4265424, "conversation", ""},
	--{"bothan_information_broker",60,-17.2353,1.6,-13.9646,180.007,4265427, "conversation", ""},
	--{"commoner",60,-17.2353,1.6,-15.0646,0,4265427, "conversation", ""},
	--{"vendor",60,-18.3353,1.6,-13.9646,135.009,4265427, "conversation", ""},
	--{"bothan_diplomat",60,25.8451,1.28309,-1.92994,180.018,4265423, "conversation", ""},
	--{"businessman",60,25.8451,1.28309,-3.02994,360.011,4265423, "conversation", ""},
	--{"explorer",60,25.7677,1.28309,8.41503,360.011,4265423, "conversation", ""},
	--{"hunter",300,16.326,1.28309,10.047,180.01,4265423, "conversation", ""},
	--{"medic",60,25.7677,1.28309,9.41503,180.008,4265423, "conversation", ""},
	--{"mercenary",60,15.226,1.28309,10.047,135.013,4265423, "conversation", ""},

	--Starport
	--{"brawler",60,5.81535,0.639421,60.0653,0,4265359, "conversation", ""},
	--{"comm_operator",300,5.81535,0.639421,61.0653,180.005,4265359, "conversation", ""},
	--{"rancher",60,-5.66994,0.639423,55.6418,179.998,4265359, "conversation", ""},
	--{"smuggler",300,46.424,0.639418,45.4992,0,4265362, "conversation", ""},
	--{"miner",60,-53.4306,2.63942,44.8995,360.011,4265367, "conversation", ""},

	--Cantina
	--{"bounty_hunter",60,35.6665,0.105,2.3343,180.006,4265374, "conversation", ""},
	--{"smuggler",300,35.6665,0.105,1.2343,360.011,4265374, "conversation", ""},
	--{"bodyguard",300,21.4737,-0.894997,-13.904,180.01,4265376, "conversation", ""},
	--{"artisan",60,21.4737,-0.894997,-14.904,360.011,4265376, "conversation", ""},
	--{"artisan",60,2.49489,-0.894992,-5.58394,0,4265375, "conversation", ""},
	spawnMobile("talus", "bartender",60,5.78939,-0.894992,3.21743,198.905,4265375)
	--{"bothan_information_broker",60,11.3604,-0.894992,5.58351,180.01,4265375, "conversation", ""},
	--{"commoner_technician",60,2.49489,-0.894992,-4.58394,179.992,4265375, "conversation", ""},
	--{"info_broker",60,11.3604,-0.894992,4.58351,360.011,4265375, "conversation", ""},
end
