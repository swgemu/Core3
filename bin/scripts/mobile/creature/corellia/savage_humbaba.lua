savage_humbaba = Creature:new {
	objectName = "@mob/creature_names:savage_humbaba",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.350000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2443,
	baseHAM = 7550,
	baseHAMmax = 7550,
	armor = 0,
	resists = {15,35,0,-1,-1,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 265,
	hideType = "hide_leathery",
	hideAmount = 168,
	boneType = "bone_mammal",
	boneAmount = 118,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/savage_humbaba.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(savage_humbaba, "savage_humbaba")