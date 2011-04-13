desert_scavenger = Creature:new {
	objectName = "@mob/creature_names:borgle_desert_runner",
	socialGroup = "Borgle",
	pvpFaction = "",
	faction = "",
	level = 37,
	chanceHit = 0.410000,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3642,
	baseHAM = 9700,
	baseHAMmax = 9700,
	armor = 0,
	resists = {0,50,0,75,-1,95,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {"object/mobile/borgle.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(desert_scavenger, "desert_scavenger")