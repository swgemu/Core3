noldan = Creature:new {
	objectName = "@mob/creature_names:trainer_fs",
	socialGroup = "fs_villager",
	pvpFaction = "fs_villager",
	faction = "fs_villager",
	level = 99,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9336,
	baseHAM = 24500,
	baseHAMmax = 30000,
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
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_fs_trainer.iff"},
	lootGroups = {},
	weapons = {""},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(noldan, "noldan")