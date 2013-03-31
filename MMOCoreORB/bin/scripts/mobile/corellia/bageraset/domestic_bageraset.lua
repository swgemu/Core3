domestic_bageraset = Creature:new {
	objectName = "@mob/creature_names:domestic_bageraset",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 8,
	chanceHit = 0.27,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_domesticated",
	meatAmount = 240,
	hideType = "hide_leathery",
	hideAmount = 145,
	boneType = "bone_mammal",
	boneAmount = 104,
	milkType = "milk_domesticated",
	milk = 120,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/bageraset_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(domestic_bageraset, "domestic_bageraset")
