sandreaver = Creature:new {
	objectName = "@mob/creature_names:dewback_sandreaver",
	socialGroup = "Dewback",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.360000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2637,
	baseHAM = 9100,
	baseHAMmax = 9100,
	armor = 0,
	resists = {0,0,0,-1,0,-1,0,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 340,
	hideType = "hide_leathery",
	hideAmount = 260,
	boneType = "bone_mammal",
	boneAmount = 185,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/dewback.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(sandreaver, "sandreaver")