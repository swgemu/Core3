eerie_korga_spiritmaster = Creature:new {
	objectName = "@mob/creature_names:eerie_korga_spiritmaster",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "korga_tribe",
	faction = "korga_tribe",
	level = 43,
	chanceHit = 0.46,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4279,
	baseHAM = 9600,
	baseHAMmax = 11800,
	armor = 0,
	resists = {0,0,0,0,0,0,-1,-1,-1},
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
		"object/mobile/dulok_male.iff",
		"object/mobile/dulok_female.iff"},
	lootGroups = {
		{
			groups = {
				{group = "ewok", chance = 9000000},
				{group = "wearables_uncommon", chance = 1000000},
			},
			lootChance = 1860000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(eerie_korga_spiritmaster, "eerie_korga_spiritmaster")
