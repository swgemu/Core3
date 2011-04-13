bordok_ancient = Creature:new {
	objectName = "@mob/creature_names:bordok_ancient",
	socialGroup = "Bordok",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.450000,
	damageMin = 375,
	damageMax = 460,
	baseXp = 4370,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {45,0,0,70,70,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {"object/mobile/bordok.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bordok_ancient, "bordok_ancient")