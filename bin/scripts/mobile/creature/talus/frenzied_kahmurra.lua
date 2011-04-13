frenzied_kahmurra = Creature:new {
	objectName = "@mob/creature_names:frenzied_kahmurra",
	socialGroup = "Kahmurra",
	pvpFaction = "",
	faction = "",
	level = 33,
	chanceHit = 0.400000,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3370,
	baseHAM = 9600,
	baseHAMmax = 9600,
	armor = 0,
	resists = {30,30,0,-1,0,0,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 50,
	hideType = "hide_bristley",
	hideAmount = 30,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kahmurra.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(frenzied_kahmurra, "frenzied_kahmurra")