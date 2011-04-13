bordok_herd_master = Creature:new {
	objectName = "@mob/creature_names:bordok_herd_master",
	socialGroup = "Bordok",
	pvpFaction = "",
	faction = "",
	level = 40,
	chanceHit = 0.430000,
	damageMin = 355,
	damageMax = 420,
	baseXp = 3915,
	baseHAM = 10550,
	baseHAMmax = 10550,
	armor = 0,
	resists = {0,0,0,70,70,-1,-1,-1,-1},
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
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/bordok.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bordok_herd_master, "bordok_herd_master")