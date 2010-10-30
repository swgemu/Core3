tusken_bantha = Creature:new {
	objectName = "@mob/creature_names:tusken_bantha",
	socialGroup = "Tusken Raider",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.360000,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2543,
	baseHAM = 7000,
	baseHAMmax = 7000,
	armor = 0,
	resists = {20,25,0,50,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 475,
	hideType = "hide_wooly",
	hideAmount = 350,
	boneType = "bone_mammal",
	boneAmount = 375,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/bantha.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(tusken_bantha, "tusken_bantha")