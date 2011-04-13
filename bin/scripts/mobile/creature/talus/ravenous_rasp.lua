ravenous_rasp = Creature:new {
	objectName = "@mob/creature_names:ravenous_rasp",
	socialGroup = "Voracious Rasp",
	pvpFaction = "",
	faction = "",
	level = 31,
	chanceHit = 0.410000,
	damageMin = 360,
	damageMax = 430,
	baseXp = 3188,
	baseHAM = 2700,
	baseHAMmax = 2700,
	armor = 0,
	resists = {0,0,-1,-1,0,0,0,0,-1},
	meatType = "meat_avian",
	meatAmount = 45,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 15,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/flite_rasp.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"strongpoison",""},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(ravenous_rasp, "ravenous_rasp")