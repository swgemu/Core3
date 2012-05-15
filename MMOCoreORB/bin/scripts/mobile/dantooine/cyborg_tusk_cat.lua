cyborg_tusk_cat = Creature:new {
	objectName = "@mob/creature_names:warren_cyborg_tuskcat",
	socialGroup = "warren_huurton",
	pvpFaction = "warren_huurton",
	faction = "warren_huurton",
	level = 30,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3005,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {35,0,0,35,35,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 70,
	hideType = "hide_leathery",
	hideAmount = 70,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/warren_cyborg_tuskcat.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(cyborg_tusk_cat, "cyborg_tusk_cat")