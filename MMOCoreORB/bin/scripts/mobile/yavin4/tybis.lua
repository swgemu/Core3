tybis = Creature:new {
	objectName = "@mob/creature_names:tybis",
	socialGroup = "tybis",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.35,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2443,
	baseHAM = 6800,
	baseHAMmax = 7700,
	armor = 0,
	resists = {10,10,10,10,10,10,10,10,-1},
	meatType = "meat_herbivore",
	meatAmount = 275,
	hideType = "hide_bristley",
	hideAmount = 200,
	boneType = "bone_mammal",
	boneAmount = 125,
	milkType = "milk_wild",
	milk = 135,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/tybis.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(tybis, "tybis")