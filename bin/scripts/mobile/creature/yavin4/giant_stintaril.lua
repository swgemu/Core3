giant_stintaril = Creature:new {
	objectName = "@mob/creature_names:giant_stintaril",
	socialGroup = "Stinaril",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.340000,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2006,
	baseHAM = 6000,
	baseHAMmax = 6000,
	armor = 0,
	resists = {20,20,0,-1,0,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 9,
	hideType = "hide_bristley",
	hideAmount = 7,
	boneType = "bone_mammal",
	boneAmount = 6,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_stintaril.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_red"},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_stintaril, "giant_stintaril")