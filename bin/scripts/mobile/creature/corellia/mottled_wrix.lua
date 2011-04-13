mottled_wrix = Creature:new {
	objectName = "@mob/creature_names:mottled_wrix",
	socialGroup = "Wrix",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1426,
	baseHAM = 4550,
	baseHAMmax = 4550,
	armor = 0,
	resists = {10,10,-1,-1,0,0,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/wrix.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(mottled_wrix, "mottled_wrix")