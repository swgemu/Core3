crazed_scientist = Creature:new {
	objectName = "@mob/creature_names:warren_irradiated_worker",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "warren_imperial_worker",
	faction = "",
	level = 10,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 292,
	baseHAM = 810,
	baseHAMmax = 990,
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
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/warren_irradiated_worker_s01.iff",
		"object/mobile/warren_irradiated_worker_s02.iff",
		"object/mobile/warren_irradiated_worker_s03.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "wearables_common", chance = 3000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
			}
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = brawlernovice
}

CreatureTemplates:addCreatureTemplate(crazed_scientist, "crazed_scientist")
