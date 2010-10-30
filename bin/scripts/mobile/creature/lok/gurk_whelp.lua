gurk_whelp = Creature:new {
	objectName = "@mob/creature_names:gurk_whelp",
	socialGroup = "Gurk",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.360000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2730,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {30,30,0,0,0,0,40,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 300,
	hideType = "hide_leathery",
	hideAmount = 225,
	boneType = "bone_mammal",
	boneAmount = 250,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/gurk_whelp.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gurk_whelp, "gurk_whelp")