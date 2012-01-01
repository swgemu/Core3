forest_murra = Creature:new {
	objectName = "@mob/creature_names:forest_murra",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.29,
	damageMin = 120,
	damageMax = 130,
	baseXp = 430,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {0,0,10,0,10,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 75,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 1,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/forest_murra.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(forest_murra, "forest_murra")