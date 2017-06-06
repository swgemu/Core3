NightSisterStrongholdScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "NightSisterStrongholdScreenPlay",

	lootContainers = {
		5035775
	},

	lootLevel = 38,

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

	lootContainerRespawn = 1800, -- 30 minutes

	axkvaGuards = {
		{ -88.44, -102.87, -118.02 },
		{ -95.26, -102.39, -121.17 },
		{ -93.95, -103.28, -127.98 },
		{ -80.15, -101.58, -119.85 },
		{ -82.63, -102.43, -124.82 },
		{ -95.73, -102.72, -122.55 }
	}
}

registerScreenPlay("NightSisterStrongholdScreenPlay", true)

function NightSisterStrongholdScreenPlay:start()
	if (isZoneEnabled("dathomir")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function NightSisterStrongholdScreenPlay:spawnMobiles()

	--outside the walls
	spawnMobile("dathomir", "nightsister_sentinel",720,-4059.4,123.3,-285.0,-114,0)
	spawnMobile("dathomir", "nightsister_sentinel",720,-4068.8,124.4,-270.5,-140,0)
	spawnMobile("dathomir", "nightsister_sentry",600,-4074.6,125.2,-287.0,-136,0)
	spawnMobile("dathomir", "nightsister_sentry",600,-4159.6,135.4,-191.9,-173,0)
	spawnMobile("dathomir", "nightsister_sentry",600,-4167.0,134.6,-190.7,-91,0)
	spawnMobile("dathomir", "nightsister_sentinel",720,-4175.3,132.6,-178.0,-89,0)
	spawnMobile("dathomir", "nightsister_rancor_tamer",720,-4243.1,135.7,-83.4,-74,0)
	spawnMobile("dathomir", "nightsister_bull_rancor",720,-4247.2,135.4,-89.5,-74,0)
	spawnMobile("dathomir", "nightsister_sentinel",720,-4121.4,121.6,-43.7,-70,0)
	spawnMobile("dathomir", "nightsister_ranger",720,-4128.9,120.7,-41.5,0,0)
	spawnMobile("dathomir", "nightsister_protector",1200,-4005.1,119.0,-60.0,-164,0)
	spawnMobile("dathomir", "nightsister_initiate",600,-4001.0,119.0,-62.4,-165,0)
	spawnMobile("dathomir", "nightsister_sentinel",720,-3994.1,124.7,-76.1,102,0)
	spawnMobile("dathomir", "nightsister_sentinel",720,-4032.2,123.5,-65.6,14,0)
	spawnMobile("dathomir", "nightsister_slave",300,-4013.9,106.0,-42.5,140,0)
	spawnMobile("dathomir", "nightsister_slave",300,-4010.3,106.0,-46.9,40,0)
	spawnMobile("dathomir", "nightsister_slave",300,-4006.7,106.0,-42.2,90,0)

	--inside the walls (not in the building)
	spawnMobile("dathomir", "nightsister_elder",3600,-3976.1,131.5,-171.3,-169,0)
	spawnMobile("dathomir", "nightsister_elder",3600,-4003.5,121,-270.1,-54,0)
	spawnMobile("dathomir", "nightsister_elder",3600,-4155.3,121.0,-99.8,51,0)
	spawnMobile("dathomir", "nightsister_rancor_tamer",720,-4107.2,126.3,-100,-24,0)
	spawnMobile("dathomir", "nightsister_protector",1200,-4105.6,126.8,-94.5,178,0)
	spawnMobile("dathomir", "nightsister_spell_weaver",720,-4100.6,126.7,-95.5,-110,0)
	spawnMobile("dathomir", "nightsister_rancor_tamer",720,-4016.0,130.3,-139.0,6,0)
	spawnMobile("dathomir", "nightsister_protector",1200,-4014.0,130.4,-136.8,-100,0)
	spawnMobile("dathomir", "nightsister_spell_weaver",720,-4019.4,129.8,-137.7,80,0)
	spawnMobile("dathomir", "nightsister_rancor_tamer",720,-3984.0,123.4,-231.0,0,0)
	spawnMobile("dathomir", "nightsister_protector",1200,-3983.0,124.4,-226.9,-166,0)
	spawnMobile("dathomir", "nightsister_protector",1200,-4017.5,121.0,-249.5,-64,0)
	spawnMobile("dathomir", "nightsister_spell_weaver",720,-3986.7,124.2,-225.4,178,0)
	spawnMobile("dathomir", "nightsister_sentinel",720,-4059.9,128.0,-157.0,0,0)
	spawnMobile("dathomir", "nightsister_sentry",600,-4058.3,127.8,-150.9,-175,0)
	spawnMobile("dathomir", "nightsister_stalker",720,-4062.8,128.3,-152.9,116,0)
	spawnMobile("dathomir", "nightsister_initiate",600,-4046.1,120.8,-188.7,37,0)
	spawnMobile("dathomir", "nightsister_rancor_tamer",720,-4039.4,120.7,-194.8,19,0)
	spawnMobile("dathomir", "nightsister_spell_weaver",720,-4035.4,121.2,-194.1,-4,0)
	spawnMobile("dathomir", "nightsister_protector",1200,-4042.3,118.8,-230.7,-134,0)
	spawnMobile("dathomir", "nightsister_spell_weaver",720,-4047.7,119.1,-232.2,101,0)
	spawnMobile("dathomir", "nightsister_ranger",720,-4045.0,120.2,-261.8,-54,0)
	spawnMobile("dathomir", "nightsister_initiate",600,-3965.2,125.1,-237.1,-65,0)
	spawnMobile("dathomir", "nightsister_protector",1200,-4150.9,134.6,-176.0,-62,0)
	spawnMobile("dathomir", "nightsister_spell_weaver",720,-4157.6,134.0,-173.4,111,0)
	spawnMobile("dathomir", "nightsister_sentinel",720,-4152.9,133.5,-168.5,178,0)
	spawnMobile("dathomir", "nightsister_protector",1200,-4142.0,126.9,-136.8,-52,0)
	spawnMobile("dathomir", "nightsister_ranger",720,-4192.0,125.2,-132.9,110,0)
	spawnMobile("dathomir", "nightsister_ranger",720,-4190.3,124.7,-124.8,98,0)
	spawnMobile("dathomir", "nightsister_protector",1200,-4139.9,121.0,-82.8,84,0)
	spawnMobile("dathomir", "nightsister_spell_weaver",720,-4117.0,126.7,-116.6,-125,0)
	spawnMobile("dathomir", "nightsister_stalker",720,-4122.8,126.2,-120.6,54,0)
	spawnMobile("dathomir", "nightsister_protector",1200,-4066.6,130.5,-105.8,38,0)
	spawnMobile("dathomir", "nightsister_protector",1200,-4060.1,130.5,-111.9,46,0)
	spawnMobile("dathomir", "nightsister_sentry",600,-4067.4,126.3,-83.5,167,0)
	spawnMobile("dathomir", "nightsister_protector",1200,-3993.8,131.2,-194.4,-138,0)
	spawnMobile("dathomir", "nightsister_spell_weaver",720,-4028.1,126.3,-109.2,52,0)
	spawnMobile("dathomir", "nightsister_ranger",720,-3992.4,129.6,-108.1,-64,0)
	spawnMobile("dathomir", "nightsister_sentry",600,-3955.8,131.9,-204.4,-158,0)
	spawnMobile("dathomir", "nightsister_sentry",600,-4084.6,133.6,-210.4,26,0)
	spawnMobile("dathomir", "nightsister_spell_weaver",720,-4080.4,132.9,-207.0,-105,0)
	spawnMobile("dathomir", "nightsister_sentry",600,-4113.8,122.5,-57.2,-156,0)
	spawnMobile("dathomir", "nightsister_protector",1200,-4024.4,126.7,-111.9,2,0)

	--main building
	spawnMobile("dathomir", "nightsister_initiate",600,-5.9,0.8,3.3,82,189375)
	spawnMobile("dathomir", "nightsister_initiate",600,5.5,0.8,2.6,-92,189375)
	spawnMobile("dathomir", "nightsister_spell_weaver",720,5.8,0.8,-13.2,-90,189376)
	spawnMobile("dathomir", "nightsister_slave",300,14.3,0.8,-22.6,152,189377)
	spawnMobile("dathomir", "nightsister_slave",300,18.1,0.8,-28.0,-100,189377)
	spawnMobile("dathomir", "nightsister_slave",300,10.6,0.8,-30.1,32,189377)
	spawnMobile("dathomir", "nightsister_ranger",720,-13.4,0.8,-13.4,14,189378)
	spawnMobile("dathomir", "nightsister_sentinel",720,-1.2,0.8,-44.4,-85,189379)
	spawnMobile("dathomir", "nightsister_protector",1200,0.2,0.8,-54.7,-5,189379)
	spawnMobile("dathomir", "nightsister_elder",3600,-5.8,7.2,-3.0,135,189383)
	spawnMobile("dathomir", "nightsister_slave",300,-15.0,7.2,-14.3,3,189384)

	--in the cave, make difficulty 'scale' as player progresses into the cave, listed here from bottom to top:
	spawnMobile("dathomir", "nightsister_sentinel",2400,-89.6414,-100.547,-149.769,54,4115626)
	spawnMobile("dathomir", "nightsister_rancor",2400,-82.0,-99.7,-93.1,-174,4115629)
	spawnMobile("dathomir", "nightsister_spell_weaver",2400,-82.2,-100.0,-103.6,-161,4115629)
	spawnMobile("dathomir", "nightsister_sentinel",720,-28.3439,-80.1922,-151.496,7,4115628)
	spawnMobile("dathomir", "nightsister_sentinel",720,-22.2057,-80.5683,-151.813,2,4115628)
	spawnMobile("dathomir", "nightsister_enraged_bull_rancor",2400,-58.3,-92.2,-146.4,77,4115628)
	spawnMobile("dathomir", "nightsister_spell_weaver",720,-12.9025,-68.921,-96.3403,7,4115627)
	spawnMobile("dathomir", "nightsister_sentinel",720,-19.9525,-69.7168,-92.0932,2,4115627)
	spawnMobile("dathomir", "nightsister_ranger",1200,-52.8,-68.7,-103.5,20,4115627)
	spawnMobile("dathomir", "nightsister_sentinel",720,-66.3095,-70.9,-84.3193,2,4115627)
	spawnMobile("dathomir", "nightsister_bull_rancor",720,-27.2,-70.7,-114.8,-32,4115627)
	spawnMobile("dathomir", "nightsister_rancor",720,-47.1,-69.8,-83.0,149,4115627)
	spawnMobile("dathomir", "nightsister_ranger",1200,-107.147,-68.531,-113.11,7,4115626)
	spawnMobile("dathomir", "nightsister_stalker",720,-118.707,-69.6862,-123.213,2,4115626)
	spawnMobile("dathomir", "nightsister_spell_weaver",1200,-122.558,-69.332,-138.946,7,4115626)
	spawnMobile("dathomir", "nightsister_stalker",720,-104.958,-71.5983,-176.399,2,4115626)
	spawnMobile("dathomir", "nightsister_stalker",720,-115.398,-69.2239,-172.659,7,4115626)
	spawnMobile("dathomir", "nightsister_spell_weaver",1200,-121.94,-69.8514,-182.011,2,4115626)
	spawnMobile("dathomir", "nightsister_spell_weaver",1200,-115.618,-69.9586,-198.215,7,4115626)
	spawnMobile("dathomir", "nightsister_sentinel",720,-101.324,-68.9513,-203.529,2,4115626)
	spawnMobile("dathomir", "nightsister_rancor",720,-84.3,-70.2,-122.6,-89,4115626)
	spawnMobile("dathomir", "nightsister_rancor_tamer",720,-68.4386,-69.8099,-196.707,7,4115626)
	spawnMobile("dathomir", "nightsister_bull_rancor",720,-61.3,-69.9,-194.0,12,4115626)
	spawnMobile("dathomir", "nightsister_enraged_rancor",720,-65.5,-69.7,-162.9,165,4115626)
	spawnMobile("dathomir", "nightsister_sentinel",720,-20.5611,-64.3706,-179.909,2,4115624)
	spawnMobile("dathomir", "nightsister_enraged_rancor",720,-13.1121,-64.7617,-221.124,2,4115625)
	spawnMobile("dathomir", "nightsister_spell_weaver",720,-93.1,-73.3,-174.5,-6,4115626)
	spawnMobile("dathomir", "nightsister_sentinel",720,-94.4,-73.2,-166.3,88,4115626)
	spawnMobile("dathomir", "nightsister_enraged_rancor",720,-20.9,-65.1,-213.2,20,4115625)
	spawnMobile("dathomir", "ancient_bull_rancor",2400,-19.7,-63.2,-260.3,-7,4115625)
	spawnMobile("dathomir", "nightsister_enraged_bull_rancor",1200,-8.3,-64.0,-228.4,-7,4115625)
	spawnMobile("dathomir", "nightsister_stalker",720,64.9,-48.3,-131.0,-105,4115623)
	spawnMobile("dathomir", "nightsister_spell_weaver",720,60.9,-52.4,-142.4,-92,4115623)
	spawnMobile("dathomir", "nightsister_rancor_tamer",1200,1.9,-63.2,-233.7,-89,4115625)
	spawnMobile("dathomir", "nightsister_rancor",720,-5.85405,-66.7536,-214.372,2,4115625)
	spawnMobile("dathomir", "nightsister_sentinel",720,14.0655,-63.2116,-184.377,2,4115624)
	spawnMobile("dathomir", "nightsister_protector",720,-12.4,-64.0,-188.3,-2,4115624)
	spawnMobile("dathomir", "nightsister_sentinel",720,57.2187,-56.7709,-178.97,2,4115623)
	spawnMobile("dathomir", "nightsister_protector",1200,61.2023,-57.0517,-174.241,-134,4115623)
	spawnMobile("dathomir", "nightsister_stalker",600,65.0699,-55.58,-159.308,2,4115623)
	spawnMobile("dathomir", "nightsister_sentinel",720,65.4328,-55.1946,-157.441,-167,4115623)
	spawnMobile("dathomir", "nightsister_sentinel",720,38.9,-53.2,-145.1,-38,4115623)
	spawnMobile("dathomir", "nightsister_spell_weaver",1200,37.6899,-52.6698,-143.418,7,4115623)
	spawnMobile("dathomir", "nightsister_sentry",720,17.99,-47.6612,-133.802,2,4115623)
	spawnMobile("dathomir", "nightsister_spell_weaver",1200,-7.9093,-45.001,-143.0,9,4115623)
	spawnMobile("dathomir", "nightsister_rancor",720,20.7,-46.0,-111.6,35,4115623)
	spawnMobile("dathomir", "nightsister_enraged_rancor",1200,-3.6,-46.2,-149.1,-11,4115623)
	spawnMobile("dathomir", "nightsister_ranger",720,0.0473984,-45.1734,-143.086,7,4115623)
	spawnMobile("dathomir", "nightsister_enraged_rancor",1200,25.9,-60.8,-176.4,64,4115623)
	spawnMobile("dathomir", "nightsister_ranger",720,38.3645,-45.6514,-94.5238,2,4115622)
	spawnMobile("dathomir", "nightsister_sentry",600,40.565,-46.6515,-76.2628,7,4115622)
	spawnMobile("dathomir", "nightsister_outcast",720,48.2317,-47.0278,-54.4734,2,4115622)
	spawnMobile("dathomir", "nightsister_outcast",720,44.0373,-46.6601,-51.444,7,4115622)
	spawnMobile("dathomir", "nightsister_sentry",720,31.0654,-45.1049,-56.1405,-100,4115622)
	spawnMobile("dathomir", "nightsister_rancor",720,52.1,-45.9,-95.7,-68,4115622)
	spawnMobile("dathomir", "nightsister_ranger",1200,15.027,-40.2011,-76.6327,7,4115621)
	spawnMobile("dathomir", "nightsister_rancor",720,16.3,-42.3,-64.0,-137,4115621)
	spawnMobile("dathomir", "nightsister_sentry",720,-5.96411,-40.5602,-65.8697,2,4115621)
	spawnMobile("dathomir", "nightsister_bull_rancor",1200,2.6,-40.3,-66.4,-60,4115621)
	spawnMobile("dathomir", "nightsister_outcast",720,-10.1746,-39.3909,-54.6325,2,4115621)
	spawnMobile("dathomir", "nightsister_initiate",600,-9.30522,-31.6686,-33.0453,7,4115620)
	spawnMobile("dathomir", "nightsister_initiate",600,5.27219,-24.4314,-26.0931,2,4115620)
	spawnMobile("dathomir", "nightsister_initiate",600,2.20982,-11.8595,-2.93477,7,4115619)

	self:respawnAxkvaMin()

	local pTrap = spawnSceneObject("dathomir", "object/static/terrain/corellia/rock_crystl_shrpbush_med.iff", -11.5, -64.6, -202.2, 4115624, 0.707107, 0, 0.707107, 0)

	if (pTrap ~= nil) then
		local pActiveArea = spawnActiveArea("dathomir", "object/active_area.iff", -3987.5, 50.23, 188.99, 4, 4115624)
		if pActiveArea ~= nil then
			createObserver(ENTEREDAREA, "NightSisterStrongholdScreenPlay", "notifyEnteredTrapArea", pActiveArea)
		end

		local pSwitch = spawnSceneObject("dathomir", "object/tangible/dungeon/cave_stalagmite_ice_style_01.iff", -8.88, -65, -189.23, 4115624, 0.707107, 0, 0.707107, 0)

		if (pSwitch ~= nil) then
			createObserver(OBJECTRADIALUSED, "NightSisterStrongholdScreenPlay", "notifyTrapSwitchUsed", pSwitch);
			spawnSceneObject("dathomir", "object/static/particle/pt_light_blink_blue.iff", -8.88, -65, -189.23, 4115624, 0.707107, 0, 0.707107, 0)

			self:enableTrap()
		end
	end
end

function NightSisterStrongholdScreenPlay:enableTrap()
	local pTrapEffect = spawnSceneObject("dathomir", "object/static/particle/pt_poi_electricity_2x2.iff", -11.5, -64.6, -202.2, 4115624, 0.707107, 0, 0.707107, 0)

	if (pTrapEffect ~= nil) then
		writeData("NightSisterStrongholdScreenPlay:trapEffect", SceneObject(pTrapEffect):getObjectID())
	end
end

function NightSisterStrongholdScreenPlay:notifyTrapSwitchUsed(pSwitch, pPlayer)
	if (pSwitch == nil) then
		return 1
	end

	if (pPlayer == nil) then
		return 0
	end

	local effectID = readData("NightSisterStrongholdScreenPlay:trapEffect")

	if (effectID == 0) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/nightsister_rancor_cave:power_already_off")
	else
		local pEffect = getSceneObject(effectID)

		if (pEffect ~= nil) then
			SceneObject(pEffect):destroyObjectFromWorld()
		end

		CreatureObject(pPlayer):sendSystemMessage("@dungeon/nightsister_rancor_cave:power_off")
		deleteData("NightSisterStrongholdScreenPlay:trapEffect")
		createEvent(7 * 1000, "NightSisterStrongholdScreenPlay", "enableTrap", nil, "")
	end

	return 0
end

function NightSisterStrongholdScreenPlay:notifyEnteredTrapArea(pActiveArea, pPlayer)
	if (pActiveArea == nil) then
		return 1
	end

	if (pPlayer == nil) then
		return 0
	end

	if (readData("NightSisterStrongholdScreenPlay:trapEffect") == 0) then
		return 0
	end

	spawnSceneObject("dathomir", "object/static/particle/pt_magic_sparks.iff", -11.5, -64.6, -202.2, 4115624, 0.707107, 0, 0.707107, 0)
	playClientEffectLoc(SceneObject(pPlayer):getObjectID(), "clienteffect/trap_electric_01.cef", "dathomir", -11.5, -64.6, -202.2, 4115624)

	CreatureObject(pPlayer):sendSystemMessage("@dungeon/nightsister_rancor_cave:shock")
	local trapDmg = getRandomNumber(400, 700)
	CreatureObject(pPlayer):inflictDamage(pPlayer, 0, trapDmg, 1)

	return 0
end

function NightSisterStrongholdScreenPlay:respawnAxkvaMin()
	local pAxkvaMin = spawnMobile("dathomir", "axkva_min", 0, -90.5, -101, -102.2, 172, 4115629)

	if (pAxkvaMin ~= nil) then
		createObserver(STARTCOMBAT, "NightSisterStrongholdScreenPlay", "spawnGuards", pAxkvaMin)
		createObserver(OBJECTDESTRUCTION, "NightSisterStrongholdScreenPlay", "axkvaKilled", pAxkvaMin)
	end
end

function NightSisterStrongholdScreenPlay:axkvaKilled(pAxkvaMin)
	createEvent(6400 * 1000, "NightSisterStrongholdScreenPlay", "respawnAxkvaMin", nil, "")

	return 1
end

function NightSisterStrongholdScreenPlay:spawnGuards(pAxkvaMin)
	if (pAxkvaMin == nil or CreatureObject(pAxkvaMin):isDead()) then
		return 1
	end

	spatialChat(pAxkvaMin, "@dungeon/nightsister_rancor_cave:protect")

	for i = 1, #self.axkvaGuards, 1 do
		local guardID = readData("axkvaGuard:" .. i)

		local pGuard = getSceneObject(guardID)

		if (pGuard == nil or CreatureObject(pGuard):isDead()) then
			local guardData = self.axkvaGuards[i]
			pGuard = spawnMobile("dathomir", "nightsister_protector", 0, guardData[1], guardData[2], guardData[3], 0, 4115629)

			if (pGuard ~= nil) then
				writeData("axkvaGuard:" .. i, SceneObject(pGuard):getObjectID())
			end
		end
	end

	return 0
end
