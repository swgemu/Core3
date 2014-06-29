captain_sarguillo = Creature:new {
	objectName = "@mob/creature_names:fs_villager_captain",
	socialGroup = "fs_villager",
	pvpFaction = "fs_villager",
	faction = "fs_villager",
	level = 69,
	chanceHit = 0.6,
	damageMin = 495,
	damageMax = 700,
	baseXp = 6655,
	baseHAM = 11000,
	baseHAMmax = 13500,
	armor = 0,
	resists = {60,60,60,60,60,60,60,60,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_fs_village_captain.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(captain_sarguillo, "captain_sarguillo")