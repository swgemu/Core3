BelaVistalScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "BelaVistalScreenPlay"
}

registerScreenPlay("BelaVistalScreenPlay", true)

function BelaVistalScreenPlay:start()
	if (isZoneEnabled("corellia")) then
		self:spawnMobiles()
		self:spawnSceneObjects()
	end
end

function BelaVistalScreenPlay:spawnSceneObjects()

	--Guild Hall regular
	spawnSceneObject("corellia", "object/tangible/loot/simple_kit/paint_cartridge.iff", 5.3, 2.3, 10.2, 2365923, math.rad(-19) )
	--Hotel
	spawnSceneObject("corellia", "object/static/structure/general/droid_r4_powerdown.iff", 6.0, 1.0, 20.2, 2365805, math.rad(143) )

end

function BelaVistalScreenPlay:spawnMobiles()

	--Cloning Facility
	local pNpc = spawnMobile("corellia", "surgical_droid_21b",60,3.1,0.1,11.5,0,2365903)
	self:setMoodString(pNpc, "neutral")

	--Cantina
	spawnMobile("corellia", "noble", 60, 5.80982, -0.894992, -5.41349, 248.205, 3375355)
	spawnMobile("corellia", "businessman", 60, -10.2935, -0.895782, 7.13264, 339.313, 3375355)
	--Guild Hall 6857 -5783
	spawnMobile("corellia", "businessman", 60, 3.32, 1.13306, -8.49, 228.007, 2365769)
	spawnMobile("corellia", "brawler", 300, -14.01, 1.13306, -8.53, 120.004, 2365770)
	spawnMobile("corellia", "trainer_brawler", 0, -11, 1.13306, -14,0, 2365770)
	spawnMobile("corellia", "trainer_marksman", 0, 0, 1.13306, -14, 0, 2365769)
	--Guild Hall regular
	pNpc = spawnMobile("corellia", "artisan",60,4.7,2.3,10.4,-4,2365923)
	self:setMoodString(pNpc, "npc_use_terminal_high")
	pNpc = spawnMobile("corellia", "contractor",60,-8.8,1.7,-14.5,45,2365931)
	self:setMoodString(pNpc, "npc_sitting_table_eating")
	pNpc = spawnMobile("corellia", "businessman",60,-5.7,1.8,-14.7,-39,2365931)
	self:setMoodString(pNpc, "npc_sitting_chair")

	--Hotel
	pNpc = spawnMobile("corellia", "noble",60,18.4,1.6,12.3,180,2365808)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("corellia", "bartender",60,21.2,1.6,12.3,180,2365808)
	self:setMoodString(pNpc, "entertained")
	pNpc = spawnMobile("corellia", "entertainer",60,19.6,1.3,5.8,83,2365808)
	self:setMoodString(pNpc, "happy")
	pNpc = spawnMobile("corellia", "sullustan_male",60,21.0,1.3,6.1,-96,2365808)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("corellia", "commoner_technician",60,-6.7,1.0,19.5,-125,2365805)
	self:setMoodString(pNpc, "npc_use_terminal_high")
	pNpc = spawnMobile("corellia", "mouse_droid",60,-6.4,1.0,16.5,103,2365806)
	self:setMoodString(pNpc, "neutral")

	--Outside
	spawnMobile("corellia", "cll8_binary_load_lifter", 60, 6826.88, 315, -5778.01, 0.0395659, 0)
	spawnMobile("corellia", "commoner", 60, 6832.06, 315, -5606.82, 252.9, 0)
	spawnMobile("corellia", "commoner", 60, 6847.34, 315, -5617.89, 54.6527, 0)
	spawnMobile("corellia", "commoner", 60, 6829.04, 315, -5626.01, 119.354, 0)
	spawnMobile("corellia", "commoner", 60, 6821.55, 314.999, -5611.9, 303.021, 0)
	spawnMobile("corellia", "commoner", 60, 6834.25, 315, -5577.61, 150.226, 0)
	spawnMobile("corellia", "commoner", 60, 6846.25, 315, -5588.75, 54.8409, 0)
	spawnMobile("corellia", "commoner", 60, 6896.18, 330, -5577.91, 290.907, 0)
	spawnMobile("corellia", "commoner", 60, 6867.23, 315, -5758.29, 338.874, 0)
	spawnMobile("corellia", "commoner", 60, 6829.48, 315, -5813.46, 319.91, 0)
	spawnMobile("corellia", "commoner", 60, 6808.93, 315, -5779.16, 282.269, 0)
	spawnMobile("corellia", "commoner", 60, 6829.32, 315, -5745.5, 171.619, 0)
	spawnMobile("corellia", "commoner", 60, 6810.15, 315, -5699.05, 137.601, 0)
	spawnMobile("corellia", "commoner", 60, 6798.04, 315, -5731.94, 209.929, 0)
	spawnMobile("corellia", "commoner", 60, 6760.75, 315, -5733.05, 101.495, 0)
	spawnMobile("corellia", "commoner", 60, 6761.43, 315, -5695.98, 3.51103, 0)
	spawnMobile("corellia", "commoner", 60, 6755.2, 314.926, -5625.98, 139.418, 0)
	spawnMobile("corellia", "commoner", 60, 6740.98, 315, -5674.9, 168.837, 0)
	spawnMobile("corellia", "criminal", 300, 6871.34, 315, -5753.42, 355.947, 0)
	spawnMobile("corellia", "corsec_trooper", 360, 6847.6, 315, -5838.6, -1, 0)
	spawnMobile("corellia", "corsec_trooper", 360, 6852.5, 315, -5838.8, -24, 0)
	spawnMobile("corellia", "corsec_trooper", 360, 6855.7, 315, -5837.1, -34, 0)
	spawnMobile("corellia", "corsec_trooper", 360, 6860.3, 315, -5833.9, -57, 0)
	spawnMobile("corellia", "dark_trooper", 400, 6749.3, 315, -5684, 231.007, 0)
	spawnMobile("corellia", "dark_trooper", 400, 6718.1, 328.537, -5869.6, 186.005, 0)
	spawnMobile("corellia", "imperial_noncom", 400, 6663.8, 330, -5913.3, 134.004, 0)
	spawnMobile("corellia", "scout_trooper", 400, 6832.36, 314.758, -5811.93, 312.353, 0)
	spawnMobile("corellia", "storm_commando", 400, 6752.1, 315, -5823.5, 273.008, 0)
	spawnMobile("corellia", "storm_commando", 400, 6648.54, 330, -5939.32, 280.874, 0)
	spawnMobile("corellia", "stormtrooper", 400, 6852.9, 315, -5826.9, 140.004, 0)
	spawnMobile("corellia", "stormtrooper", 400, 6837.4, 315, -5774, 260.008, 0)
	spawnMobile("corellia", "stormtrooper", 400, 6819.9, 315, -5720.1, 220.006, 0)
	spawnMobile("corellia", "stormtrooper", 400, 6748.9, 315, -5665.2, 279.008, 0)
	spawnMobile("corellia", "stormtrooper", 400, 6855, 315, -5609.3, 280.008, 0)
	spawnMobile("corellia", "stormtrooper", 400, 6685.7, 330, -5943.3, 222.007, 0)
	spawnMobile("corellia", "stormtrooper", 400, 6708, 328.7, -5869.7, 166.005, 0)
	spawnMobile("corellia", "stormtrooper_rifleman", 400, 6845.3, 315, -5826.8, 130.004, 0)
	spawnMobile("corellia", "grondom_muse", 60, 6838.16, 315, -5767.67, 266.732, 0)
	spawnMobile("corellia", "noble",60, 6724.41, 330, -5909.35, 213.723, 0)
	spawnMobile("corellia", "pashna", 60, 6772.57, 315, -5697.8, 245.284, 0)
	spawnMobile("corellia", "stormtrooper_bombardier", 360, 6646.02, 330, -5931.59, 357.677, 0)
	spawnMobile("corellia", "stormtrooper_bombardier", 360, 6644.26, 330, -5937.08, 5.98245, 0)
	spawnMobile("corellia", "stormtrooper_bombardier", 360, 6649.56, 330, -5935.6, 128.564, 0)
	spawnMobile("corellia", "imperial_recruiter", 60,6718.8,315.0,-5804.6,-174,0)

	--Misc
	spawnMobile("corellia", "informant_npc_lvl_1", 0, 20.9951, -0.894992, 21.3608, 100, 3375357)
	spawnMobile("corellia", "informant_npc_lvl_1", 0, 6687, 315, -5594, 0, 0)
	spawnMobile("corellia", "informant_npc_lvl_1", 0, 6733, 314.9, -5609, 90, 0)
	spawnMobile("corellia", "informant_npc_lvl_1", 0, 6832, 315, -5545, 270, 0)
	spawnMobile("corellia", "informant_npc_lvl_1", 0, 6901, 330, -5606, 0, 0)
	spawnMobile("corellia", "informant_npc_lvl_2", 0, 6775, 315, -5487, 150, 0)
	spawnMobile("corellia", "informant_npc_lvl_2", 0, 6876, 330, -5466, 0, 0)
	spawnMobile("corellia", "informant_npc_lvl_3", 0, 6860, 315, -5761, 45 ,0)

	--Trainers
	spawnMobile("corellia", "trainer_architect", 0, 11, 1.13306, -14, 0, 2365800)
	spawnMobile("corellia", "trainer_armorsmith", 0, -12, 1.1, 5, 180, 2365799)
	spawnMobile("corellia", "trainer_artisan", 0, 0, 1.13306, -14, 0, 2365947)
	spawnMobile("corellia", "trainer_droidengineer", 0, -11, 1.13306, -14, 0, 2365802)
	spawnMobile("corellia", "trainer_merchant", 0, 12, 1.13306, 6, 180, 2365798)
	spawnMobile("corellia", "trainer_scout", 0, -12, 1.13306, 5.5, 180, 2365767)
	spawnMobile("corellia", "trainer_weaponsmith", 0, -2.5, 1.13306, -8.4, 91, 2365801)

	--Outside Trainers
	spawnMobile("corellia", "trainer_artisan", 0, 6755.99, 314.994, -5655.01, 269, 0)
	spawnMobile("corellia", "trainer_entertainer", 0, 6829, 330, -5429, 184, 0)
	spawnMobile("corellia", "trainer_marksman", 0,6770,315,-5714,-100,0)
	spawnMobile("corellia", "trainer_scout", 0, 6737.85, 315, -5491.3, 31, 0)
	spawnMobile("corellia", "trainer_scout",  0, 6724, 315, -5682, 0, 0)

	--removed from corellia.lua
	pNpc = spawnMobile("corellia", "bartender",60,8.54,-0.894992,0.14,87.0026,3375355)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("corellia", "businessman",60,-6.56842,-0.894996,21.9012,135.001,3375361)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("corellia", "contractor",60,-5.46842,-0.894996,21.9012,180.003,3375361)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("corellia", "bounty_hunter",60,21.6023,-0.894996,-18.5913,360.011,3375356)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("corellia", "stormtrooper_captain",400,6854.5,315,-5696.6,87,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "stormtrooper_squad_leader",400,6650.38,330,-5938.43,280.869,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "specialist_noncom",400,6830.18,314.823,-5816.91,187.167,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "imperial_army_captain",400,6820.49,315,-5743.53,353.468,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "imperial_army_captain",400,6832.21,315,-5811.19,189.637,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "comm_operator",60,-42.3991,0.105009,-24.3411,360.011,3375367)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("corellia", "commoner",60,-42.3991,0.105009,-23.2411,180.016,3375367)
	BelaVistalScreenPlay:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("corellia", "imperial_sergeant",60,6712.78,315,-5810.38,112.467,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "imperial_sergeant",60,6795.21,315,-5702.92,63.9209,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "imperial_sergeant",60,6823.92,315,-5597.88,121.846,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "imperial_sergeant_major",400,6908.17,330,-5608.54,27.4568,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "imperial_staff_sergeant",400,6909.29,330,-5606.48,204.967,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "info_broker",60,21.6023,-0.894996,-17.4913,180.012,3375356)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("corellia", "medic",60,-43.4991,0.105009,-23.2411,135.007,3375367)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("corellia", "mercenary",60,-5.46842,-0.894998,20.8012,0,3375361)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("corellia", "stormtrooper",60,6727.1,315,-5809.9,165,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "stormtrooper",60,6707.89,315,-5814.25,131.647,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "stormtrooper",60,6794.42,315,-5696.6,90.5594,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "stormtrooper",60,6826.7,315,-5820.68,309.206,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "stormtrooper",60,6825.35,315,-5620.37,277.216,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "stormtrooper",60,6842.92,315,-5604.11,56.0358,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "stormtrooper",60,6852,315,-5831.51,128.695,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "stormtrooper",60,6837.95,315,-5806.84,302.784,0)
	self:setMoodString(pNpc, "npc_imperial")
	pNpc = spawnMobile("corellia", "r4",60,6715.38,330,-5903.81,0.0395659,0)
	self:setMoodString(pNpc, "calm")
	pNpc = spawnMobile("corellia", "r2",60,6857.06,315,-5702.8,0,0)
	self:setMoodString(pNpc, "calm")
	--{"junk_malik",0,6756.1,315,-5778,88,0, "", "Malik Pendron",JUNKCORSEC,JUNKCONVMALIKVISTAL},
	--{"junk_dealer",0,6970,330,-5588,92,0, "", "",JUNKGENERIC,JUNKCONVGENERIC},
	--{"junk_dealer",0,6840,315,-5630,-32,0, "", "",JUNKCLOTHESANDJEWELLERY+JUNKARMOUR,JUNKCONVFINARY},
end
