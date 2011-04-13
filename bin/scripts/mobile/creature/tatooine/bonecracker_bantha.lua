bonecracker_bantha = Creature:new {
	objectName = "@mob/creature_names:bantha_bonecracker",
	socialGroup = "Bantha",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.350000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2443,
	baseHAM = 8000,
	baseHAMmax = 8000,
	armor = 0,
	resists = {0,25,0,40,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 475,
	hideType = "hide_wooly",
	hideAmount = 345,
	boneType = "bone_mammal",
	boneAmount = 300,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/bantha.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bonecracker_bantha, "bonecracker_bantha")