dune_bantha = Creature:new {
	objectName = "@monster_name:bantha_dune_medium",
	socialGroup = "Dune Bantha",
	pvpFaction = "",
	faction = "",
	level = 17,
	chanceHit = 0.320000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 960,
	baseHAM = 3900,
	baseHAMmax = 3900,
	armor = 0,
	resists = {0,0,0,40,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 375,
	hideType = "hide_wooly",
	hideAmount = 275,
	boneType = "bone_mammal",
	boneAmount = 175,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/bantha.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(dune_bantha, "dune_bantha")