domesticated_mott = Creature:new {
	objectName = "@mob/creature_names:domesticated_mott",
	socialGroup = "naboo",
	pvpFaction = "",
	faction = "",
	level = 5,
	chanceHit = 0.25,
	damageMin = 45,
	damageMax = 50,
	baseXp = 85,
	baseHAM = 135,
	baseHAMmax = 165,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 95,
	hideType = "hide_leathery",
	hideAmount = 65,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/mott_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(domesticated_mott, "domesticated_mott")