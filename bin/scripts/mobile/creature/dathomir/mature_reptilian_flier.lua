mature_reptilian_flier = Creature:new {
	objectName = "mature reptilian flier",
	socialGroup = "Repilian Flier",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.320000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1609,
	baseHAM = 5550,
	baseHAMmax = 5550,
	armor = 0,
	resists = {0,10,0,35,35,-1,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 130,
	hideType = "hide_leathery",
	hideAmount = 85,
	boneType = "bone_avian",
	boneAmount = 80,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/reptilian_flier.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mature_reptilian_flier, "mature_reptilian_flier")