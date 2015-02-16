theme_park_imperial_rebel_sympathizer = Creature:new {
	objectName = "@mob/creature_names:rebel_corporal",
	socialGroup = "rebel",
	faction = "rebel",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {15,15,15,15,15,15,15,15,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_corporal_bith_female_01.iff",
		"object/mobile/dressed_rebel_corporal_bothan_male_01.iff",
		"object/mobile/dressed_rebel_corporal_human_female_01.iff",
		"object/mobile/dressed_rebel_corporal_moncal_male_01.iff",
		"object/mobile/dressed_rebel_corporal_rodian_female_01.iff",
		"object/mobile/dressed_rebel_corporal_sullustan_male_01.iff"},
	lootGroups = {
		{
	        groups = {
				{group = "theme_park_loot_documents", chance = 10000000}
			},
			lootChance = 10000000
		}	
	},
	weapons = {"rebel_weapons_light"},
	conversationTemplate = "",
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(theme_park_imperial_rebel_sympathizer, "theme_park_imperial_rebel_sympathizer")
