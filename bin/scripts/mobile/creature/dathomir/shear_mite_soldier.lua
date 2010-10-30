shear_mite_soldier = Creature:new {
	objectName = "@mob/creature_names:shear_mite_soilder",
	socialGroup = "Shearmite",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.330000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 5550,
	baseHAMmax = 5550,
	armor = 0,
	resists = {25,25,0,0,-1,-1,-1,-1,-1},
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
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/shear_mite_soldier.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"mildpoison",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(shear_mite_soldier, "shear_mite_soldier")