spineflap_queen = Creature:new {
	objectName = "@mob/creature_names:spineflap_queen",
	socialGroup = "Cap. Spineflap",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.330000,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1426,
	baseHAM = 5000,
	baseHAMmax = 5000,
	armor = 0,
	resists = {-1,30,0,0,0,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "hide_scaley",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 3,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/spineflap_queen.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(spineflap_queen, "spineflap_queen")