aakuan_sentinel = Creature:new {
	objectName = "@mob/creature_names:Aa'kuan sentinel",
	socialGroup = "Aa'kuan",
	pvpFaction = "Aa'kuan",
	faction = "",
	level = 17,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1257,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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

	templates = {"object/mobile/dressed_aakuan_sentinal_rodian_female_01.iff"},
	lootgroups = {},
	weapons = {"melee_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(aakuan_sentinel, "aakuan_sentinel")