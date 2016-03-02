r3_crafted = Creature:new {
	objectName = "@droid_name:r3_crafted",
	socialGroup = "",
	faction = "",
	level = 4,
	chanceHit = 0.24,
	damageMin = 135,
	damageMax = 150,
	baseXp = 0,
	baseHAM = 4000,
	baseHAMmax = 4500,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/creature/npc/droid/crafted/r3_droid.iff"
	},
	lootGroups = {},
	defaultAttack = "attack",
	defaultWeapon = "object/weapon/ranged/droid/droid_astromech_ranged.iff",
	conversationTemplate = "",
}

CreatureTemplates:addCreatureTemplate(r3_crafted, "r3_crafted")
