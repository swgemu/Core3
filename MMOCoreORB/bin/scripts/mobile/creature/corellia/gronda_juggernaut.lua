gronda_juggernaut = Creature:new {
	objectName = "gronda juggernaut",
	socialGroup = "Gronda",
	pvpFaction = "",
	faction = "",
	level = 70,
	chanceHit = 0.650000,
	damageMin = 430,
	damageMax = 570,
	baseXp = 6747,
	baseHAM = 13500,
	baseHAMmax = 13500,
	armor = 0,
	resists = {65,65,75,-1,100,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 500,
	hideType = "hide_leathery",
	hideAmount = 400,
	boneType = "bone_mammal",
	boneAmount = 375,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/gronda.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gronda_juggernaut, "gronda_juggernaut")