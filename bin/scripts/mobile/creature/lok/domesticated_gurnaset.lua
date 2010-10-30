domesticated_gurnaset = Creature:new {
	objectName = "@mob/creature_names:domesticated_gurnaset",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.300000,
	damageMin = 130,
	damageMax = 140,
	baseXp = 514,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {10,10,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 352,
	hideType = "hide_leathery",
	hideAmount = 279,
	boneType = "bone_mammal",
	boneAmount = 304,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/gurnaset.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(domesticated_gurnaset, "domesticated_gurnaset")