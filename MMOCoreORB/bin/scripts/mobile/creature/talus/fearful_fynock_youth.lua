fearful_fynock_youth = Creature:new {
	objectName = "@mob/creature_names:fearful_fynock_youth",
	socialGroup = "Fynock",
	pvpFaction = "",
	faction = "",
	level = 5,
	chanceHit = 0.250000,
	damageMin = 45,
	damageMax = 50,
	baseXp = 85,
	baseHAM = 150,
	baseHAMmax = 150,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 1,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 1,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/fearful_fynock_youth.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(fearful_fynock_youth, "fearful_fynock_youth")