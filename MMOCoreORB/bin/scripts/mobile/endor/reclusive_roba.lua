reclusive_roba = Creature:new {
	objectName = "@mob/creature_names:reclusive_roba",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3005,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {20,20,20,60,-1,60,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 15,
	hideType = "hide_leathery",
	hideAmount = 30,
	boneType = "bone_mammal",
	boneAmount = 15,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/roba_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(reclusive_roba, "reclusive_roba")