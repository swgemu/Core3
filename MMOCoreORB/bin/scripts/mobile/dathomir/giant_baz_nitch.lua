giant_baz_nitch = Creature:new {
	objectName = "@mob/creature_names:giant_baz_nitch",
	socialGroup = "baz_nitch",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.41,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3551,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {45,45,25,-1,-1,-1,25,-1,-1},
	meatType = "meat_wild",
	meatAmount = 9,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_mammal",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_baz_nitch.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(giant_baz_nitch, "giant_baz_nitch")