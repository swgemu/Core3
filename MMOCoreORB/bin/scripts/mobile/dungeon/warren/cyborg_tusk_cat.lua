cyborg_tusk_cat = Creature:new {
	objectName = "@mob/creature_names:warren_cyborg_tuskcat",
	socialGroup = "warren_cyborg",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3005,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {35,0,0,135,135,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 80,
	hideType = "hide_leathery",
	hideAmount = 50,
	boneType = "bone_mammal",
	boneAmount = 45,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/warren_cyborg_tuskcat.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(cyborg_tusk_cat, "cyborg_tusk_cat")
