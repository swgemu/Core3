fs_villager_engineer = Creature:new {
	objectName = "@mob/creature_names:fs_villager_engineer",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "fs_villager",
	faction = "fs_villager",
	level = 4,
	chanceHit = 0.24,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 138,
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
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_fs_village_surveyor.iff" -- What is his proper template?
	},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(fs_villager_engineer, "fs_villager_engineer")
