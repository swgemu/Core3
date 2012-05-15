tusken_bantha = Creature:new {
	objectName = "@mob/creature_names:tusken_bantha",
	socialGroup = "tusken_raider",
	pvpFaction = "tusken_raider",
	faction = "tusken_raider",
	level = 25,
	chanceHit = 0.36,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2543,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {20,25,15,50,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 475,
	hideType = "hide_wooly",
	hideAmount = 350,
	boneType = "bone_mammal",
	boneAmount = 375,
	milk = 1,
	tamingChance = 0,
	ferocity = 2,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bantha.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(tusken_bantha, "tusken_bantha")
