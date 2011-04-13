female_malkloc_plainswalker = Creature:new {
	objectName = "@mob/creature_names:malkloc_plainswalker_female",
	socialGroup = "Malkloc Plainswalker",
	pvpFaction = "",
	faction = "",
	level = 81,
	chanceHit = 0.650000,
	damageMin = 570,
	damageMax = 850,
	baseXp = 7761,
	baseHAM = 17500,
	baseHAMmax = 17500,
	armor = 0,
	resists = {100,50,0,-1,-1,0,0,100,-1},
	meatType = "meat_herbivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "bone_mammal",
	boneAmount = 1000,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/malkloc.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"creatureareaknockdown","knockdownChance=30"}
	}
}

CreatureTemplates:addCreatureTemplate(female_malkloc_plainswalker, "female_malkloc_plainswalker")