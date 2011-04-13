shear_mite_hunter = Creature:new {
	objectName = "@mob/creature_names:shear_mite_hunter",
	socialGroup = "Shearmite",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.380000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3005,
	baseHAM = 9100,
	baseHAMmax = 9100,
	armor = 0,
	resists = {0,30,-1,0,-1,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "hide_scaley",
	hideAmount = 12,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/shear_mite_hunter.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"mediumpoison",""},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(shear_mite_hunter, "shear_mite_hunter")