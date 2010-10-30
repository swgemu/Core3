greater_desert_womp_rat = Creature:new {
	objectName = "@monster_name:womp_rat_desert_large",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.350000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2006,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {0,0,35,30,0,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 6,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_mammal",
	boneAmount = 4,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/greater_desert_womp_rat.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(greater_desert_womp_rat, "greater_desert_womp_rat")