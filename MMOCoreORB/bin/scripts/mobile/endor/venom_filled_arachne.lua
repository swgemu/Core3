venom_filled_arachne = Creature:new {
	objectName = "@mob/creature_names:venom_filled_arachne",
	socialGroup = "arachne",
	pvpFaction = "",
	faction = "",
	level = 36,
	chanceHit = 0.4,
	damageMin = 300,
	damageMax = 310,
	baseXp = 3642,
	baseHAM = 8500,
	baseHAMmax = 10300,
	armor = 0,
	resists = {145,145,20,165,165,20,165,-1,-1},
	meatType = "meat_insect",
	meatAmount = 50,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 4,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/queen_arachne.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"strongpoison",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(venom_filled_arachne, "venom_filled_arachne")
