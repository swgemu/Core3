crafty_korga_scout = Creature:new {
	objectName = "@mob/creature_names:crafty_korga_scout",
	socialGroup = "Korga Tribe",
	pvpFaction = "Korga Tribe",
	faction = "",
	level = 45,
	chanceHit = 0.48,
	damageMin = 380,
	damageMax = 470,
	baseXp = 4461,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 0,
	resists = {15,15,0,0,0,-1,0,0,-1},
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

	templates = {"object/mobile/object/mobile/object/mobile/dulok_male.iff.iff.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(crafty_korga_scout, "crafty_korga_scout")