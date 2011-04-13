fierce_huurton = Creature:new {
	objectName = "@mob/creature_names:warren_huurton_fierce",
	socialGroup = "Warren Huurton",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.340000,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2006,
	baseHAM = 6000,
	baseHAMmax = 6000,
	armor = 0,
	resists = {20,20,0,0,-1,0,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER,
	diet = CARNIVORE,

	templates = {"object/mobile/huurton.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(fierce_huurton, "fierce_huurton")