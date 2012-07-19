kinad_baz_nitch = Creature:new {
	objectName = "@mob/creature_names:kinad_baz_nitch",
	socialGroup = "baz_nitch",
	pvpFaction = "",
	faction = "",
	level = 46,
	chanceHit = 0.48,
	damageMin = 380,
	damageMax = 470,
	baseXp = 4552,
	baseHAM = 9500,
	baseHAMmax = 11700,
	armor = 1,
	resists = {20,20,0,40,0,0,0,0,-1},
	meatType = "meat_wild",
	meatAmount = 15,
	hideType = "hide_leathery",
	hideAmount = 10,
	boneType = "bone_mammal",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0.15,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/baz_nitch_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kinad_baz_nitch, "kinad_baz_nitch")