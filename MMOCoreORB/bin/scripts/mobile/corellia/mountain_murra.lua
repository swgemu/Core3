mountain_murra = Creature:new {
	objectName = "@mob/creature_names:mountain_murra",
	socialGroup = "murra",
	pvpFaction = "",
	faction = "",
	level = 17,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {5,120,125,-1,5,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 75,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 45,
	milkType = "milk_wild",
	milk = 35,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mountain_murra.iff"},
	controlDeviceTemplate = "object/intangible/pet/murra_hue.iff",
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_murra, "mountain_murra")
