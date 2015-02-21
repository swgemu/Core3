cyborg_dune_lizard = Creature:new {
	objectName = "@mob/creature_names:warren_cyborg_dunelizard",
	socialGroup = "warren_cyborg",
	faction = "",
	level = 30,
	chanceHit = 0.37,
	damageMin = 270,
	damageMax = 280,
	baseXp = 3005,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {40,130,0,175,-1,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 95,
	hideType = "hide_leathery",
	hideAmount = 60,
	boneType = "bone_mammal",
	boneAmount = 45,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/warren_cyborg_dunelizard.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(cyborg_dune_lizard, "cyborg_dune_lizard")
