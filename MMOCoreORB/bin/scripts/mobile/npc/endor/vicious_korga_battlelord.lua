vicious_korga_battlelord = Creature:new {
	objectName = "@mob/creature_names:vicious_korga_battlelord",
	socialGroup = "Korga Tribe",
	pvpFaction = "Korga Tribe",
	faction = "",
	level = 48,
	chanceHit = 0.49,
	damageMin = 410,
	damageMax = 530,
	baseXp = 4734,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 1,
	resists = {25,10,0,50,50,-1,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dulok_male.iff"},
	lootgroups = {},
	weapons = {""},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(vicious_korga_battlelord, "vicious_korga_battlelord")