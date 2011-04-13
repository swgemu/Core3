greater_gulginaw = Creature:new {
	objectName = "@mob/creature_names:greater_gulginaw",
	socialGroup = "Gulginaw",
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
	resists = {15,30,-1,0,-1,-1,0,0,-1},
	meatType = "meat_avian",
	meatAmount = 97,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 48,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/greater_gulginaw.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(greater_gulginaw, "greater_gulginaw")