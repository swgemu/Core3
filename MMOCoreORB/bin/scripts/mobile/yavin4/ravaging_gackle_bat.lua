ravaging_gackle_bat = Creature:new {
	objectName = "@mob/creature_names:ravaging_gackle_bat",
	socialGroup = "gacklebat",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.32,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1257,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {5,15,-1,20,-1,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_bristley",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 4,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gackle_bat.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(ravaging_gackle_bat, "ravaging_gackle_bat")