piket_longhorn_female = Creature:new {
	objectName = "@mob/creature_names:piket_longhorn_female",
	socialGroup = "picket",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2914,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {10,10,10,65,65,65,65,10,-1},
	meatType = "meat_herbivore",
	meatAmount = 450,
	hideType = "hide_scaley",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 110,
	milk = 1,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/piket_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(piket_longhorn_female, "piket_longhorn_female")