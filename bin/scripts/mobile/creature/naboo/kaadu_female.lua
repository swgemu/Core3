kaadu_female = Creature:new {
	objectName = "@mob/creature_names:kaadu_female",
	socialGroup = "Kaadu",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.290000,
	damageMin = 130,
	damageMax = 140,
	baseXp = 430,
	baseHAM = 1300,
	baseHAMmax = 1300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 75,
	boneType = "bone_avian",
	boneAmount = 65,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/kaadu.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kaadu_female, "kaadu_female")