gnarled_rancor = Creature:new {
	objectName = "@mob/creature_names:gnarled_rancor",
	socialGroup = "Rancor",
	pvpFaction = "",
	faction = "",
	level = 46,
	chanceHit = 0.470000,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4552,
	baseHAM = 10800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {0,30,-1,50,50,50,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 876,
	boneType = "bone_mammal",
	boneAmount = 775,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/rancor.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gnarled_rancor, "gnarled_rancor")