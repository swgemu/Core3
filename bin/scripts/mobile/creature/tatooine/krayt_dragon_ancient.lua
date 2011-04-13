krayt_dragon_ancient = Creature:new {
	objectName = "@mob/creature_names:krayt_dragon_ancient",
	socialGroup = "Krayt Dragon",
	pvpFaction = "",
	faction = "",
	level = 336,
	chanceHit = 30.000000,
	damageMin = 2270,
	damageMax = 4250,
	baseXp = 28549,
	baseHAM = 100000,
	baseHAMmax = 100000,
	armor = 0,
	resists = {95,95,95,95,65,95,95,95,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_bristley",
	hideAmount = 950,
	boneType = "bone_mammal",
	boneAmount = 905,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/krayt_dragon.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareacombo",""},
		{"creatureareaknockdown","knockdownChance=30"}
	}
}

CreatureTemplates:addCreatureTemplate(krayt_dragon_ancient, "krayt_dragon_ancient")