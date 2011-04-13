giant_fynock = Creature:new {
	objectName = "@mob/creature_names:giant_fynock",
	socialGroup = "Fynock",
	pvpFaction = "",
	faction = "",
	level = 42,
	chanceHit = 0.440000,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4188,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_avian",
	meatAmount = 70,
	hideType = "hide_leathery",
	hideAmount = 50,
	boneType = "bone_avian",
	boneAmount = 55,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/fynock.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_red"},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"creatureareaknockdown","knockdownChance=30"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_fynock, "giant_fynock")