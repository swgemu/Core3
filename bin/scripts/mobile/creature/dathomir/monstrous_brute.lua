monstrous_brute = Creature:new {
	objectName = "@mob/creature_names:rancor_monstrous_brute",
	socialGroup = "Rancor",
	pvpFaction = "",
	faction = "",
	level = 87,
	chanceHit = 0.820000,
	damageMin = 595,
	damageMax = 900,
	baseXp = 8315,
	baseHAM = 14500,
	baseHAMmax = 14500,
	armor = 0,
	resists = {0,60,0,100,100,100,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 878,
	boneType = "bone_mammal",
	boneAmount = 778,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/rancor.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"creatureareaattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(monstrous_brute, "monstrous_brute")