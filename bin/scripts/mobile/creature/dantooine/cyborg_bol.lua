cyborg_bol = Creature:new {
	objectName = "@mob/creature_names:warren_cyborg_bol",
	socialGroup = "Warren Cyborg",
	pvpFaction = "",
	faction = "",
	level = 36,
	chanceHit = 0.420000,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3551,
	baseHAM = 9900,
	baseHAMmax = 9900,
	armor = 0,
	resists = {45,0,-1,0,0,-1,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 100,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER,
	diet = CARNIVORE,

	templates = {"object/mobile/warren_cyborg_bol.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(cyborg_bol, "cyborg_bol")