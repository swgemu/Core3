singing_mountain_clan_arch_witch = Creature:new {
	objectName = "@mob/creature_names:Singing_Mountain_clan_arch_witch",
	socialGroup = "Mtn. Clan",
	pvpFaction = "Mtn. Clan",
	faction = "",
	level = 107,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 10174,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 2,
	resists = {100,45,45,100,100,100,100,100,-1},
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
	creatureBitmask = PACK + KILLER + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_dathomir_sing_mt_clan_arch_witch.iff"},
	lootgroups = {},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(singing_mountain_clan_arch_witch, "singing_mountain_clan_arch_witch")