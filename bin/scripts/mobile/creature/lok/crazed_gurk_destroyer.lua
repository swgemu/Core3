crazed_gurk_destroyer = Creature:new {
	objectName = "@mob/creature_names:crazed_gurk_destroyer",
	socialGroup = "Gurk",
	pvpFaction = "",
	faction = "",
	level = 43,
	chanceHit = 0.440000,
	damageMin = 385,
	damageMax = 480,
	baseXp = 4279,
	baseHAM = 10700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 275,
	boneType = "bone_mammal",
	boneAmount = 300,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/gurk.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(crazed_gurk_destroyer, "crazed_gurk_destroyer")