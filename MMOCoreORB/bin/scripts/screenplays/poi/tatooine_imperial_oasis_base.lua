TatooineImperialOasisBaseScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("TatooineImperialOasisBaseScreenPlay", true)

function TatooineImperialOasisBaseScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
	end
end

function TatooineImperialOasisBaseScreenPlay:spawnMobiles()

	local pNpc = spawnMobile("tatooine", "artisan",60,-1.1,1.0,10.0,142,6016532)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("tatooine", "agriculturalist",60,1.4,1.0,9.7,-134,6016532)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("tatooine", "commoner_tatooine",60,7.7,-3.4,9.5,-42,6016536)
	self:setMoodString(pNpc, "npc_sitting_table_eating")
	pNpc = spawnMobile("tatooine", "commoner_fat",60,10.0,-4.0,-1.6,-88,6016537)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("tatooine", "entertainer",60,8.9,-4.0,-1.5,90,6016537)
	self:setMoodString(pNpc, "happy")
	pNpc = spawnMobile("tatooine", "scientist",60,-7.6,-10.0,-9.6,175,6016539)
	self:setMoodString(pNpc, "npc_use_terminal_high")
	pNpc = spawnMobile("tatooine", "r5",60,-8.7,-10.0,-9.6,106,6016539)
	self:setMoodString(pNpc, "happy")
	pNpc = spawnMobile("tatooine", "imperial_stealth_operative",60,-1.9,-9.5,-3.8,65,6016541)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("tatooine", "shadowy_figure",60,-0.3,-9.5,-2.4,-157,6016541)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("tatooine", "seeker",60,-1.0,-9.5,1.8,-120,6016538)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("tatooine", "scientist",60,-7.3,-10.0,-10.3,177,6016507)
	self:setMoodString(pNpc, "npc_use_terminal_low")
	pNpc = spawnMobile("tatooine", "chiss_male",60,8.0,-3.4,7.4,169,6016504)
	self:setMoodString(pNpc, "happy")
	pNpc = spawnMobile("tatooine", "chiss_female",60,8.1,-3.4,6.2,0,6016504)
	self:setMoodString(pNpc, "nervous")
	pNpc = spawnMobile("tatooine", "noble",60,10.4,0.4,5.6,-141,6016499)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("tatooine", "info_broker",60,10.4,0.4,4.4,0,6016499)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("tatooine", "rebel_obscureops_agent",60,5.3,0.1,-4.2,88,1289937)
	self:setMoodString(pNpc, "npc_use_terminal_low")
	pNpc = spawnMobile("tatooine", "imperial_stealth_operative",60,4.3,0.1,-3.2,130,1289937)
	self:setMoodString(pNpc, "threaten")
	pNpc = spawnMobile("tatooine", "contractor",60,-2.3,0.1,-3.1,8,1289938)
	self:setMoodString(pNpc, "npc_use_terminal_low")
	pNpc = spawnMobile("tatooine", "medic",60,-5.0,0.1,1.7,-145,1289934)
	self:setMoodString(pNpc, "npc_use_terminal_low")
	--Outside
	pNpc = spawnMobile("tatooine", "bounty_hunter",60,-5284.9,7.1,2714.4,-97,0)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("tatooine", "seeker",60,-5285.6,7.2,2713.7,-100,0)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("tatooine", "farmer_rancher",60,-5250,0,2733.3,-13,0)
	self:setMoodString(pNpc, "fishing")
	pNpc = spawnMobile("tatooine", "bounty_hunter",60,-5284.9,9.1,2675.2,48,0)
	self:setMoodString(pNpc, "angry")
	spawnMobile("tatooine", "trainer_commando",0,-5292,6.76132,2718,183,0)
	spawnMobile("tatooine", "informant_npc_lvl_2",0,-5284,9.1,2676,240,0)
	spawnMobile("tatooine", "informant_npc_lvl_1",0,-5296,8.5,2654,0,0)
	spawnMobile("tatooine", "imperial_recruiter",0,-5340,4.7,2736,149,0)
	spawnMobile("tatooine", "dark_trooper",360,-5360,8.0,2748.6,130,0)
	spawnMobile("tatooine", "dark_trooper",360,-5357.5,8.0,2751.4,130,0)
	spawnMobile("tatooine", "elite_sand_trooper",360,-5343.4,4.7,2733,120,0)
	spawnMobile("tatooine", "imperial_probe_drone",360,-5322.4,7.1,2711.5,179,0)
	--Corvette rescue mission npc to be added later...
	--spawnMobile("tatooine", "colonel_darkstone",0,-5321.4,6.8,2702,158,0)
	spawnMobile("tatooine", "sand_trooper",360,-5289.8,7.5,2707,30,0)
	spawnMobile("tatooine", "sand_trooper",360,-5292.8,7.2,2709.2,40,0)
	spawnMobile("tatooine", "storm_commando",600,-5310.7,8.5,2660.7,3,0)
	spawnMobile("tatooine", "storm_commando",600,-5304.0,8.5,2660.6,-7,0)
	spawnMobile("tatooine", "sand_trooper",360,-5361.6,8.5,2661.8,-93,0)
	spawnMobile("tatooine", "sand_trooper",360,-5362.5,7.6,2673.5,-120,0)
	spawnMobile("tatooine", "stormtrooper_sniper",360,-5339.1,7.5,2673.3,-97,0)

end

