grand_wrix = Creature:new {
	objectName = "@mob/creature_names:grand_wrix",
	socialGroup = "Wrix",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.350000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2637,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {35,30,0,50,-1,35,-1,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 70,
	hideType = "hide_bristley",
	hideAmount = 40,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/grand_wrix.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(grand_wrix, "grand_wrix")