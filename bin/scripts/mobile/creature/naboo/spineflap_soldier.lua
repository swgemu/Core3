spineflap_soldier = Creature:new {
	objectName = "@mob/creature_names:spineflap_soldier",
	socialGroup = "Cap. Spineflap",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.300000,
	damageMin = 150,
	damageMax = 160,
	baseXp = 714,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "hide_scaley",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 3,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/capper_spineflap.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(spineflap_soldier, "spineflap_soldier")