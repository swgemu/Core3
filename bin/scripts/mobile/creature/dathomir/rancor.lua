rancor = Creature:new {
	objectName = "@monster_name:rancor",
	socialGroup = "Rancor",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.500000,
	damageMin = 420,
	damageMax = 550,
	baseXp = 4916,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {30,30,-1,60,60,60,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 877,
	boneType = "bone_mammal",
	boneAmount = 777,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/rancor.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rancor, "rancor")