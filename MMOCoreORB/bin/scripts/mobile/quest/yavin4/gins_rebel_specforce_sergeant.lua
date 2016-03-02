gins_rebel_specforce_sergeant = Creature:new {
	objectName = "@mob/creature_names:rebel_specforce_sergeant",
	socialGroup = "rebel",
	faction = "rebel",
	level = 21,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2006,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {5,5,5,5,5,5,5,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_specforce_sergeant_bothan_male_01.iff",
		"object/mobile/dressed_rebel_specforce_sergeant_human_male_01.iff",
		"object/mobile/dressed_rebel_specforce_sergeant_moncal_female_01.iff",
		"object/mobile/dressed_rebel_specforce_sergeant_moncal_male_01.iff",
		"object/mobile/dressed_rebel_specforce_sergeant_trandoshan_male_01.iff",
		"object/mobile/dressed_rebel_specforce_sergeant_twk_female_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "task_loot_gins_darone_special_forces_vibroknuckler", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = merge(marksmanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(gins_rebel_specforce_sergeant, "gins_rebel_specforce_sergeant")
