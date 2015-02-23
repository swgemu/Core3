domestic_humbaba = Creature:new {
	objectName = "@mob/creature_names:domestic_humbaba",
	socialGroup = "self",
	faction = "",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 147,
	baseHAM = 270,
	baseHAMmax = 330,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_domesticated",
	meatAmount = 215,
	hideType = "hide_leathery",
	hideAmount = 115,
	boneType = "bone_mammal",
	boneAmount = 65,
	milkType = "milk_domesticated",
	milk = 105,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/savage_humbaba.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(domestic_humbaba, "domestic_humbaba")
