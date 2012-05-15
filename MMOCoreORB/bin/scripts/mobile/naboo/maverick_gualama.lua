maverick_gualama = Creature:new {
	objectName = "@mob/creature_names:maverick_gualama",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 150,
	damageMax = 160,
	baseXp = 609,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {0,10,0,0,0,0,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 200,
	hideType = "hide_wooly",
	hideAmount = 150,
	boneType = "bone_mammal",
	boneAmount = 90,
	milk = 0,
	tamingChance = 0,
	ferocity = 5,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gualama.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(maverick_gualama, "maverick_gualama")