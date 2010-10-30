rogue_falumpaset = Creature:new {
	objectName = "@mob/creature_names:rogue_falumpaset",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1102,
	baseHAM = 3900,
	baseHAMmax = 3900,
	armor = 0,
	resists = {0,10,0,-1,-1,-1,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 190,
	hideType = "hide_leathery",
	hideAmount = 110,
	boneType = "bone_mammal",
	boneAmount = 80,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = NONE,
	diet = CARNIVORE,

	templates = {"object/mobile/falumpaset.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rogue_falumpaset, "rogue_falumpaset")