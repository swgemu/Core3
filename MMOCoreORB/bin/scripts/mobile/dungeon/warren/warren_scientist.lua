warren_scientist = Creature:new {
	objectName = "@mob/creature_names:warren_scientist",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "warren_scientist",
	faction = "",
	level = 36,
	chanceHit = 0.420000,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3460,
	baseHAM = 8900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE + ENEMY,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {
		"object/mobile/warren_scientist_s01.iff",
		"object/mobile/warren_scientist_s02.iff",
		"object/mobile/warren_scientist_s03.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 5500000},
				{group = "tailor_components", chance = 1000000},
				{group = "armor_attachments", chance = 500000},
				{group = "clothing_attachments", chance = 500000},
				{group = "wearables_common", chance = 2500000}
			}
		}
	},
	weapons = {},
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(warren_scientist, "warren_scientist")
