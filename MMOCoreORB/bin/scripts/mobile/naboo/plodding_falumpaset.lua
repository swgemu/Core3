plodding_falumpaset = Creature:new {
	objectName = "@mob/creature_names:domestic_falumpaset",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.28,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_domesticated",
	meatAmount = 230,
	hideType = "hide_leathery",
	hideAmount = 130,
	boneType = "bone_mammal",
	boneAmount = 80,
	milkType = "milk_domesticated",
	milk = 125,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/falumpaset_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/falumpaset_hue.iff",
	scale = 0.9,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(plodding_falumpaset, "plodding_falumpaset")
