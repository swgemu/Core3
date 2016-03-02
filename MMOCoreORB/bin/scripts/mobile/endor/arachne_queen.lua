arachne_queen = Creature:new {
	objectName = "@mob/creature_names:queen_arachne",
	socialGroup = "arachne",
	faction = "",
	level = 63,
	chanceHit = 0.6,
	damageMin = 445,
	damageMax = 600,
	baseXp = 6105,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {150,135,15,180,180,15,180,-1,-1},
	meatType = "meat_insect",
	meatAmount = 60,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/queen_arachne.iff"},
	scale = 1.3,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareapoison",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(arachne_queen, "arachne_queen")
