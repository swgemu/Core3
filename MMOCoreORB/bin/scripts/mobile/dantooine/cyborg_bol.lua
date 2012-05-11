cyborg_bol = Creature:new {
	objectName = "@mob/creature_names:warren_cyborg_bol",
	socialGroup = "warren_huurton",
	pvpFaction = "warren_huurton",
	faction = "warren_huurton",
	level = 36,
	chanceHit = 0.42,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3551,
	baseHAM = 8900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {45,0,-1,0,0,-1,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 100,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/warren_cyborg_bol.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(cyborg_bol, "cyborg_bol")