feared_fynock_youth = Creature:new {
	objectName = "@mob/creature_names:feared_fynock_youth",
	socialGroup = "Fynock",
	pvpFaction = "",
	faction = "",
	level = 7,
	chanceHit = 0.250000,
	damageMin = 80,
	damageMax = 90,
	baseXp = 147,
	baseHAM = 300,
	baseHAMmax = 300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 3,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 3,
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

CreatureTemplates:addCreatureTemplate(feared_fynock_youth, "feared_fynock_youth")