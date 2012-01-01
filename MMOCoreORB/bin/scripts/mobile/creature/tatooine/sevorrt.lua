sevorrt = Creature:new {
	objectName = "@mob/creature_names:sevorrt",
	socialGroup = "Sevorrt",
	pvpFaction = "",
	faction = "",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 147,
	baseHAM = 270,
	baseHAMmax = 330,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 10,
	hideType = "hide_leathery",
	hideAmount = 10,
	boneType = "bone_mammal",
	boneAmount = 4,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 5,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/sevorrt.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(sevorrt, "sevorrt")