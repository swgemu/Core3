aakuari_assassin = Creature:new {
	objectName = "@mob/creature_names:Aa'kuari_assassin",
	socialGroup = "Aa'kuan",
	pvpFaction = "Aa'kuan",
	faction = "",
	level = 31,
	chanceHit = 0.37,
	damageMin = 270,
	damageMax = 280,
	baseXp = 3188,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {40,40,0,0,0,-1,0,0,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"melee_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(aakuari_assassin, "aakuari_assassin")