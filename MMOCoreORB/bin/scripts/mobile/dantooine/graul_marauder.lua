graul_marauder = Creature:new {
	objectName = "@mob/creature_names:graul_marauder",
	socialGroup = "graul",
	pvpFaction = "",
	faction = "",
	level = 173,
	chanceHit = 1.08,
	damageMin = 1095,
	damageMax = 1900,
	baseXp = 16411,
	baseHAM = 120000,
	baseHAMmax = 125000,
	armor = 2,
	resists = {75,55,90,90,90,55,55,55,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "bone_mammal",
	boneAmount = 950,
	milk = 0,
	tamingChance = 0,
	ferocity = 15,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/graul_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareableeding",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(graul_marauder, "graul_marauder")