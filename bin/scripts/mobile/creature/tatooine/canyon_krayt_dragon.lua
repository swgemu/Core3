canyon_krayt_dragon = Creature:new {
	objectName = "@mob/creature_names:canyon_krayt_dragon",
	socialGroup = "Krayt Dragon",
	pvpFaction = "",
	faction = "",
	level = 275,
	chanceHit = 27.250000,
	damageMin = 1520,
	damageMax = 2750,
	baseXp = 26356,
	baseHAM = 100000,
	baseHAMmax = 100000,
	armor = 0,
	resists = {60,60,60,60,20,60,60,60,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_bristley",
	hideAmount = 750,
	boneType = "bone_mammal",
	boneAmount = 675,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/canyon_krayt_dragon.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareaattack",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(canyon_krayt_dragon, "canyon_krayt_dragon")