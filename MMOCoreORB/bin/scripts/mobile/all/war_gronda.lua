war_gronda = Creature:new {
	objectName = "@mob/creature_names:war_gronda",
	socialGroup = "Gronda",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2443,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {40,10,40,10,10,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 390,
	hideType = "hide_leathery",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 240,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = 0,
	diet = NONE,

	templates = {"object/mobile/war_gronda.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(war_gronda, "war_gronda")