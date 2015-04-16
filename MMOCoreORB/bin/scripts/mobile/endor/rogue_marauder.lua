rogue_marauder = Creature:new {
	objectName = "",
	randomNameType = NAME_GENERIC_TAG,
	customName = "a Rogue Marauder",
	socialGroup = "self",
	faction = "",
	level = 44,
	chanceHit = 0.47,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4370,
	baseHAM = 12000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {0,0,0,-1,0,0,-1,0,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_marauder.iff",
		"object/mobile/marauder_male.iff",
		"object/mobile/marauder_male_02.iff",
		"object/mobile/marauder_male_03.iff",
		"object/mobile/marauder_female.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "pistols", chance = 2000000},
				{group = "carbines", chance = 2000000},
				{group = "rifles", chance = 2000000},
				{group = "melee_baton", chance = 2000000},
				{group = "loot_kit_parts", chance = 1000000},
				{group = "armor_attachments", chance = 500000},
				{group = "clothing_attachments", chance = 500000}
			},
			lootChance = 2200000
		},
		{
			groups = {
				{group = "bone_armor", chance = 2000000},
				{group = "chitin_armor", chance = 2000000},
				{group = "mabari_armor", chance = 2000000},
				{group = "tantel_armor", chance = 2000000},
				{group = "ubese_armor", chance = 2000000},
			},
			lootChance = 2500000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(rogue_marauder, "rogue_marauder")
