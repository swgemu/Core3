female_malkloc_plainswalker = Creature:new {
	objectName = "@mob/creature_names:female_malkloc_plainswalker",
	socialGroup = "Malkloc Plainswalker",
	pvpFaction = "",
	faction = "",
	level = 81,
	chanceHit = 0.65,
	damageMin = 570,
	damageMax = 850,
	baseXp = 7761,
	baseHAM = 16000,
	baseHAMmax = 19000,
	armor = 1,
	resists = {100,50,20,-1,-1,20,20,100,-1},
	meatType = "meat_herbivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "bone_mammal",
	boneAmount = 1000,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/malkloc.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareaknockdown","knockdownChance=30"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(female_malkloc_plainswalker, "female_malkloc_plainswalker")