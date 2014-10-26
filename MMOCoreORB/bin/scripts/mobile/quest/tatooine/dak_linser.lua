dak_linser = Creature:new {
	objectName = "",
	socialGroup = "rebel",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2400,
	baseHAMmax = 4000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_scout_bothan_male_01.iff",
		"object/mobile/dressed_rebel_scout_human_female_01.iff",
		"object/mobile/dressed_rebel_scout_human_female_02.iff",
		"object/mobile/dressed_rebel_scout_human_male_01.iff",
		"object/mobile/dressed_rebel_scout_rodian_male_01.iff",
		"object/mobile/dressed_rebel_scout_zabrak_female_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "task_loot_wilhalm_skrim_q1_datadisc", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {"rebel_weapons_light"},
	attacks = merge(marksmanmid,brawlermid)
}

CreatureTemplates:addCreatureTemplate(dak_linser, "dak_linser")
