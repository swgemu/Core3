giant_canyon_krayt_dragon = Creature:new {
	objectName = "@mob/creature_names:giant_canyon_krayt_dragon",
	socialGroup = "Krayt Dragon",
	pvpFaction = "",
	faction = "",
	level = 300,
	chanceHit = 30.000000,
	damageMin = 1645,
	damageMax = 3000,
	baseXp = 28549,
	baseHAM = 100000,
	baseHAMmax = 100000,
	armor = 0,
	resists = {70,70,70,70,30,70,70,70,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_bristley",
	hideAmount = 870,
	boneType = "bone_mammal",
	boneAmount = 805,
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
		{"creatureareaknockdown","knockdownChance=30"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_canyon_krayt_dragon, "giant_canyon_krayt_dragon")