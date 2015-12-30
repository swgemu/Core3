hidden_daggers_activist = Creature:new {
	objectName = "@mob/creature_names:hidden_daggers_activist",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "hidden_daggers",
	faction = "hidden_daggers",
	level = 9,
	chanceHit = 0.270000,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 675,
	baseHAMmax = 825,
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
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_crook_zabrak_female_01.iff",
		"object/mobile/dressed_crook_zabrak_male_01.iff",
		"object/mobile/dressed_desperado_bith_female_01.iff",
		"object/mobile/dressed_desperado_bith_male_01.iff",
		"object/mobile/dressed_ravager_human_female_01.iff",
		"object/mobile/dressed_ravager_human_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4300000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
				{group = "hidden_dagger_common", chance = 2700000}
			}
		}
	},
	weapons = {"rebel_weapons_light"},
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(hidden_daggers_activist, "hidden_daggers_activist")
