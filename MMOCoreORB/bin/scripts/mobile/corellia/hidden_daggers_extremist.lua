hidden_daggers_extremist = Creature:new {
	objectName = "@mob/creature_names:hidden_daggers_extremist",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "hidden_daggers",
	faction = "hidden_daggers",
	level = 13,
	chanceHit = 0.3,
	damageMin = 150,
	damageMax = 160,
	baseXp = 714,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_ravager_human_female_01.iff",
		"object/mobile/dressed_ravager_human_male_01.iff",
		"object/mobile/dressed_raider_trandoshan_female_01.iff",
		"object/mobile/dressed_raider_trandoshan_male_01.iff",
		"object/mobile/dressed_robber_human_female_01.iff",
		"object/mobile/dressed_robber_human_male_01.iff",
		"object/mobile/dressed_robber_twk_female_01.iff",
		"object/mobile/dressed_robber_twk_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4300000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
				{group = "hidden_dagger_common", chance = 2700000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"pirate_weapons_medium"},
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(hidden_daggers_extremist, "hidden_daggers_extremist")
