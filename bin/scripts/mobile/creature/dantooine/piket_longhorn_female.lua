piket_longhorn_female = Creature:new {
	objectName = "@mob/creature_names:piket_longhorn_female",
	socialGroup = "Picket",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2914,
	baseHAM = 9300,
	baseHAMmax = 9300,
	armor = 0,
	resists = {0,0,0,65,65,65,65,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_scaley",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/piket_longhorn.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(piket_longhorn_female, "piket_longhorn_female")