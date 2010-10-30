devil_gulginaw = Creature:new {
	objectName = "@mob/creature_names:devil_gulginaw",
	socialGroup = "Gulginaw",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.310000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1426,
	baseHAM = 3200,
	baseHAMmax = 3200,
	armor = 0,
	resists = {15,15,15,-1,0,0,-1,-1,-1},
	meatType = "meat_avian",
	meatAmount = 70,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/devil_gulginaw.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_red"},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(devil_gulginaw, "devil_gulginaw")