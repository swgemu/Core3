alkhara_champion = Creature:new {
	objectName = "@mob/creature_names:alkhara_champion",
	socialGroup = "Alkhara",
	pvpFaction = "Alkhara",
	faction = "",
	level = 20,
	chanceHit = 0.33,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1803,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {20,0,25,25,-1,-1,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_alkhara_champion.iff"},
	lootgroups = {},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(alkhara_champion, "alkhara_champion")