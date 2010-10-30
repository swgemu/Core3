mutated_kahmurra = Creature:new {
	objectName = "@mob/creature_names:mutated_kahmurra",
	socialGroup = "Kahmurra",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.350000,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2637,
	baseHAM = 7550,
	baseHAMmax = 7550,
	armor = 0,
	resists = {25,25,0,40,40,40,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 50,
	hideType = "hide_bristley",
	hideAmount = 33,
	boneType = "bone_mammal",
	boneAmount = 37,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/mutated_kahmurra.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mutated_kahmurra, "mutated_kahmurra")