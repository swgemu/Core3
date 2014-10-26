spice_collective_workchief = Creature:new {
	objectName = "@mob/creature_names:spice_collective_workchief",
	socialGroup = "spice_collective",
	pvpFaction = "spice_collective",
	faction = "spice_collective",
	level = 11,
	chanceHit = 0.29,
	damageMin = 120,
	damageMax = 130,
	baseXp = 430,
	baseHAM = 1000,
	baseHAMmax = 1200,
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
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_spice_collective_workchief_twk_female_01.iff",
		"object/mobile/dressed_spice_collective_workchief_twk_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 2000000},
				{group = "wearables_common", chance = 2000000},
				{group = "rifles", chance = 2000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000}
			},
			lootChance = 3200000
		}
	},
	weapons = {"ranged_weapons"},
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(spice_collective_workchief, "spice_collective_workchief")
