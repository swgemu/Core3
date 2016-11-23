FortTuskenScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "FortTuskenScreenPlay",

	lootContainers = {
		7875788,
		7875790,
		7875792,
		7875791,
		7875789
	},

	lootLevel = 26,

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 3500000},
				{group = "junk", chance = 3500000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 8000000
		}
	},

	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("FortTuskenScreenPlay", true)

function FortTuskenScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function FortTuskenScreenPlay:notifyDefeatedTusken(pVictim, pAttacker)
	if pVictim == nil or pAttacker == nil or not SceneObject(pVictim):isCreatureObject() or not SceneObject(pAttacker):isCreatureObject() then
		return 0
	end

	if (not BestineElectionScreenPlay:isElectionEnabled()) then
			return 0
	end

	if victorVisalisConvoHandler:onTuskenQuest(pAttacker) then
		if (SceneObject(pVictim):getObjectName() == "tusken_executioner") then
			local pInventory = CreatureObject(pVictim):getSlottedObject("inventory")
			if (pInventory ~= nil) then
				createLoot(pInventory, "bestine_election_tusken_head", 0, true)
			end
		else
			local chance = getRandomNumber(0,300)
			if (chance <= 100) or (chance >= 200) then
				local pInventory = CreatureObject(pVictim):getSlottedObject("inventory")
				if pInventory ~= nil then
					createLoot(pInventory, "bestine_election_tusken_loot", 0, true)
				end
			end
		end
	end
	return 0
end

function FortTuskenScreenPlay:spawnMobiles()
	--On top of Tusken Pool
	spawnMobile("tatooine", "tusken_berserker",300,-3996.8,60,6285.7,74,0)
	spawnMobile("tatooine", "tusken_war_master",300,-3963.7,60.0,6234.6,-42,0)
	spawnMobile("tatooine", "tusken_avenger",300,-3969.1,60,6282.8,-73,0)
	spawnMobile("tatooine", "tusken_brute",300,-3978.6,60,6266.4,-10,0)
	spawnMobile("tatooine", "tusken_avenger",300,-3979.6,60,6261.4,-2,0)
	spawnMobile("tatooine", "tusken_blood_champion",300,-3.8,37.9,-34.1,43,1189186)
	spawnMobile("tatooine", "tusken_guard",300,-2.8,37.9,-20.7,71,1189187)
	spawnMobile("tatooine", "tusken_commoner",300,31,37.9,-30.6,-124,1189189)
	spawnMobile("tatooine", "tusken_elite_guard",300,27,44,-22.4,47,1189192)
	spawnMobile("tatooine", "tusken_flesh_hunter",300,29.6,44,-16.3,175,1189192)
	spawnMobile("tatooine", "tusken_raid_leader",300,22.16,37.9,-18.4,-19,1189191)
	spawnMobile("tatooine", "tusken_commoner",300,20.9,37.9,-31.4,3,1189191)
	spawnMobile("tatooine", "tusken_brute",300,34.0,37.9,-21.6,-79,1189190)
	spawnMobile("tatooine", "tusken_raid_leader",300,32.4,37.9,-16.2,-178,1189190)
	spawnMobile("tatooine", "tusken_blood_champion",300,33.1,37.9,-2.0,-5,1189196)
	spawnMobile("tatooine", "tusken_raider",300,32.9,37.9,5.5,179,1189196)
	spawnMobile("tatooine", "tusken_commoner",300,26.4,37.0,-0.2,-32,1189194)
	spawnMobile("tatooine", "tusken_blood_champion",300,21.6,37.0,1.4,84,1189194)
	spawnMobile("tatooine", "tusken_avenger",300,27.2,37.0,2.6,-146,1189194)
	spawnMobile("tatooine", "tusken_guard",300,16.5,37.9,-2.8,-5,1189195)
	spawnMobile("tatooine", "tusken_avenger",300,15.7,37.9,6.2,173,1189195)
	spawnMobile("tatooine", "tusken_berserker",300,-1.0,43.7,-3.3,-92,1189188)
	spawnMobile("tatooine", "tusken_elite_guard",300,-6.1,42.3,-6.4,83,1189188)
	spawnMobile("tatooine", "tusken_berserker",300,-6.2,43.3,-0.4,83,1189188)
	spawnMobile("tatooine", "tusken_commoner",300,-3952.1,68.5,6284.3,-115,0)
	spawnMobile("tatooine", "tusken_avenger",300,-3982.0,67.7,6293.8,-5,0)
	spawnMobile("tatooine", "tusken_gore_chief",300,-4006.6,60,6249.2,89,0)
	spawnMobile("tatooine", "tusken_commoner",300,-3951.7,60,6243.1,-162,0)
	spawnMobile("tatooine", "tusken_berserker",300,-3985.1,60,6290.5,-177,0)
	spawnMobile("tatooine", "tusken_blood_champion",300,-3977.7,60,6290.6,174,0)
	spawnMobile("tatooine", "tusken_blood_champion",300,-3979.1,60,6248.6,-91,0)
	spawnMobile("tatooine", "tusken_raider",300,-3985.0,60,6278.7,147,0)
	spawnMobile("tatooine", "tusken_captain",300,-3986.3,66.3,6253.7,124,0)
	spawnMobile("tatooine", "tusken_avenger",300,-3991.6,60,6246.4,-4,0)
	spawnMobile("tatooine", "tusken_commoner",300,-3967.8,60,6231.1,-43,0)
	spawnMobile("tatooine", "tusken_flesh_hunter",300,-3997.1,60,6288.4,112,0)
	spawnMobile("tatooine", "tusken_raider",300,-3969,60,6288.3,-101,0)
	spawnMobile("tatooine", "tusken_brute",300,-3983.4,60,6266.1,6,0)
	spawnMobile("tatooine", "tusken_chief",300,-1.9,37.9,-29.2,100,1189186)
	spawnMobile("tatooine", "tusken_raider",300,2.9,37.9,-15.5,-126,1189187)
	spawnMobile("tatooine", "tusken_elite_guard",300,24.2,37.9,-31.6,71,1189189)
	spawnMobile("tatooine", "tusken_raider",300,27.6,37.9,-26,177,1189189)
	spawnMobile("tatooine", "tusken_warlord",300,-4.6,37.9,-30.1,118,1189186)
	spawnMobile("tatooine", "tusken_avenger",300,-3.2,37.9,-16.2,109,1189187)
	spawnMobile("tatooine", "tusken_warlord",300,28.9,44,-29.2,0,1189193)

	--Tusken Fort Pool
	spawnMobile("tatooine", "tusken_warlord",300,-5.6,1.7,53.9,118,1189174)
	spawnMobile("tatooine", "tusken_avenger",300,-8.1,2.1,55.7,109,1189174)
	spawnMobile("tatooine", "tusken_brute",300,-9.4,2.1,54.8,0,1189174)
	spawnMobile("tatooine", "tusken_death_hunter",300,-16.4,1.1,36.2,118,1189174)
	spawnMobile("tatooine", "tusken_warlord",300,-13.8,1.2,37.5,109,1189174)
	spawnMobile("tatooine", "tusken_raid_leader",300,-6.6,1.3,23.6,0,1189174)
	spawnMobile("tatooine", "tusken_chief",300,2.0,1.3,10.0,118,1189174)
	spawnMobile("tatooine", "tusken_warlord",300,-0.9,1.3,9.6,109,1189174)
	spawnMobile("tatooine", "tusken_flesh_hunter",300,0.6,1.4,12.7,0,1189174)
	local pNpc = spawnMobile("tatooine", "tusken_witch_doctor",300,1.3,1.5,-10.8,118,1189175)
	if (pNpc ~= nil) then
		createObserver(OBJECTDESTRUCTION, "FortTuskenScreenPlay", "notifyDefeatedTusken", pNpc)
	end

	pNpc = spawnMobile("tatooine", "tusken_observer",300,0.8,1.7,-7.5,-11,1189175)
	if (pNpc ~= nil) then
		createObserver(OBJECTDESTRUCTION, "FortTuskenScreenPlay", "notifyDefeatedTusken", pNpc)
	end
	pNpc = spawnMobile("tatooine", "tusken_executioner",300, -1.54, 1.58, 0.90,-102,1189175)
	if (pNpc ~= nil) then
		createObserver(OBJECTDESTRUCTION, "FortTuskenScreenPlay", "notifyDefeatedTusken", pNpc)
	end
	spawnMobile("tatooine", "tusken_avenger",300,-4.7,1.5,-7.0,0,1189175)
	spawnMobile("tatooine", "tusken_warlord",300,-12.6,2.9,1.0,109,1189175)
	spawnMobile("tatooine", "tusken_chief",300,-15.9,3.4,-2.4,118,1189176)
	spawnMobile("tatooine", "tusken_warlord",300,-17.8,4.0,12.3,173,1189176)
	spawnMobile("tatooine", "tusken_blood_champion",300,-23.7,2.7,3.4,-145,1189176)
	spawnMobile("tatooine", "tusken_elite_guard",300,-28.5,2.7,1.3,0,1189176)
	spawnMobile("tatooine", "tusken_gore_chief",300,-20.4,4.3,-11.1,0,1189177)
	spawnMobile("tatooine", "tusken_carnage_champion",300,-14.6,6.2,-20.5,0,1189177)
	spawnMobile("tatooine", "tusken_flesh_hunter",300,-10.3,6.6,-21.8,118,1189177)
	spawnMobile("tatooine", "tusken_raid_leader",300,2.9,8.4,-28.2,-95,1189178)
	spawnMobile("tatooine", "tusken_warlord",300,0.7,8.0,-18.9,109,1189178)
	pNpc = spawnMobile("tatooine", "tusken_witch_doctor",300,2.17, 8.36, -32.02,118,1189178)
	if (pNpc ~= nil) then
		createObserver(OBJECTDESTRUCTION, "FortTuskenScreenPlay", "notifyDefeatedTusken", pNpc)
	end
	pNpc = spawnMobile("tatooine", "tusken_executioner", 300, 6.54, 8.0, -34.17, 180, 1189178)
	if (pNpc ~= nil) then
		createObserver(OBJECTDESTRUCTION, "FortTuskenScreenPlay", "notifyDefeatedTusken", pNpc)
	end
	pNpc = spawnMobile("tatooine", "tusken_observer",300,8.5,8.2,-33.5,0,1189178)
	if (pNpc ~= nil) then
		createObserver(OBJECTDESTRUCTION, "FortTuskenScreenPlay", "notifyDefeatedTusken", pNpc)
	end
	pNpc = spawnMobile("tatooine", "tusken_observer",300,1.2,8.15,-20.5,0,1189178)
	if (pNpc ~= nil) then
		createObserver(OBJECTDESTRUCTION, "FortTuskenScreenPlay", "notifyDefeatedTusken", pNpc)
	end
	pNpc = spawnMobile("tatooine", "tusken_observer",300,3.07, 8.31, -39.26,0,1189178)
	if (pNpc ~= nil) then
		createObserver(OBJECTDESTRUCTION, "FortTuskenScreenPlay", "notifyDefeatedTusken", pNpc)
	end
	spawnMobile("tatooine", "tusken_blood_champion",300,11.5,8.0,-40.7,118,1189178)
	spawnMobile("tatooine", "tusken_warlord",300,7.1,8.4,-44.9,109,1189178)
	spawnMobile("tatooine", "tusken_death_hunter",300,-0.2,8.4,-33.6,118,1189178)
	spawnMobile("tatooine", "tusken_raid_leader",300,-1.2,8.6,-40.1,0,1189179)
	spawnMobile("tatooine", "tusken_chief",300,-13.2,11.0,-39.5,109,1189179)
	spawnMobile("tatooine", "tusken_elite_guard",300,-18.3,12.6,-46.6,0,1189179)
	spawnMobile("tatooine", "tusken_brute",300,-20.9,12.9,-44.7,118,1189179)
	spawnMobile("tatooine", "tusken_avenger",300,-20.5,15.3,-53.9,109,1189179)
	spawnMobile("tatooine", "tusken_torture_lord",300,-15.3,16.9,-53.7,0,1189179)
	spawnMobile("tatooine", "tusken_blood_champion",300,-3.5,8.9,-43.4,97,1189179)
	spawnMobile("tatooine", "tusken_warlord",300,-6.9,20.2,-55.9,0,1189180)
	spawnMobile("tatooine", "tusken_avenger",300,9.1,22.6,-44.8,-122,1189180)
	spawnMobile("tatooine", "tusken_death_hunter",300,17.8,22.2,-55.2,117,1189180)
	spawnMobile("tatooine", "tusken_flesh_hunter",300,26.8,21.0,-23.6,-137,1189181)
	spawnMobile("tatooine", "tusken_brute",300,31.3,22.7,-34.8,-83,1189181)
	spawnMobile("tatooine", "tusken_warlord",300,32.9,23.1,-45.9,72,1189181)
	spawnMobile("tatooine", "tusken_war_master",300,27.8,22.3,-40.5,74,1189181)
	spawnMobile("tatooine", "tusken_chief",300,14.0,22.6,5.2,58,1189182)
	spawnMobile("tatooine", "tusken_warlord",300,25.3,22,11.4,91,1189182)
	spawnMobile("tatooine", "tusken_brute",300,29.1,21.9,10.1,-88,1189182)
	spawnMobile("tatooine", "tusken_warlord",300,37.2,22.9,19.7,165,1189182)
	spawnMobile("tatooine", "tusken_death_hunter",300,38.0,20.8,-3.6,-51,1189182)
	spawnMobile("tatooine", "tusken_chief",300,31,21.5,-9.4,167,1189182)
	spawnMobile("tatooine", "tusken_death_hunter",300,32.0,22.1,2.6,90,1189182)
	pNpc = spawnMobile("tatooine", "tusken_executioner",300,20.8,22.9,-15.2,-102,1189183)
	if (pNpc ~= nil) then
		createObserver(OBJECTDESTRUCTION, "FortTuskenScreenPlay", "notifyDefeatedTusken", pNpc)
	end

	spawnMobile("tatooine", "tusken_gore_chief",300,15.1,22.8,-17.0,163,1189183)
	spawnMobile("tatooine", "tusken_brute",300,2.5,22.9,-19.2,101,1189183)
	spawnMobile("tatooine", "tusken_carnage_champion",300,8.7,23,-28.5,121,1189183)
	spawnMobile("tatooine", "tusken_warlord",300,3.5,23.1,-12.2,10,1189183)
	spawnMobile("tatooine", "tusken_death_hunter",300,-0.4,24.0,-4.7,66,1189184)
	spawnMobile("tatooine", "tusken_brute",300,-4.5,26.2,9.5,151,1189185)
	spawnMobile("tatooine", "tusken_flesh_hunter",300,-14.9,31.5,14.3,168,1189185)
	spawnMobile("tatooine", "tusken_carnage_champion",300,-3.7,25.4,6.7,-24,1189185)
	spawnMobile("tatooine", "tusken_gore_chief",300,-6.7,25.4,7.3,65,1189185)
	spawnMobile("tatooine", "tusken_warlord",300,-7.4,28.3,20.8,172,1189185)
	spawnMobile("tatooine", "tusken_blood_champion",300,-7.5,37.9,11.6,-136,1189185)
	spawnMobile("tatooine", "tusken_warlord",300,-11.0,37.9,7.8,46,1189185)
	spawnMobile("tatooine", "tusken_war_master",300,3.1,37.9,-21.5,-55,1189187)
end
