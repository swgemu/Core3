foaming_vynock = Creature:new {
	objectName = "@mob/creature_names:foaming_vynock",
	socialGroup = "self",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 170,
	damageMax = 180,
	baseXp = 714,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 50,
	hideType = "hide_leathery",
	hideAmount = 70,
	boneType = "bone_mammal",
	boneAmount = 20,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/vynock_hue.iff"},
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""},
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(foaming_vynock, "foaming_vynock")
