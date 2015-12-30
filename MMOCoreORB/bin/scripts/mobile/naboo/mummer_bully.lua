mummer_bully = Creature:new {
	objectName = "@mob/creature_names:mummer_bully",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "mummer",
	faction = "thug",
	level = 8,
	chanceHit = 0.270000,
	damageMin = 70,
	damageMax = 75,
	baseXp = 187,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_crook_zabrak_female_01.iff",
		"object/mobile/dressed_crook_zabrak_male_01.iff",
		"object/mobile/dressed_desperado_bith_female_01.iff",
		"object/mobile/dressed_desperado_bith_male_01.iff",
		"object/mobile/dressed_hoodlum_zabrak_female_01.iff",
		"object/mobile/dressed_hoodlum_zabrak_male_01.iff",
		"object/mobile/dressed_hooligan_rodian_female_01.iff",
		"object/mobile/dressed_hooligan_rodian_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "printer_parts", chance = 1000000},
				{group = "mummer_common", chance = 1500000}
			}
		}
	},
	weapons = {"pirate_weapons_light"},
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(mummer_bully, "mummer_bully")
