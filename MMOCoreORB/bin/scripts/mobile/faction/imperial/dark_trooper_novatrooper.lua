dark_trooper_novatrooper = Creature:new {
	objectName = "@mob/creature_names:stormtrooper_dark_trooper_novatrooper",
	socialGroup = "imperial",
	faction = "imperial",
	level = 200,
	chanceHit = 18,
	damageMin = 1270,
	damageMax = 2250,
	baseXp = 21700,
	baseHAM = 208000,
	baseHAMmax = 254000,
	armor = 2,
	resists = {95,85,80,30,0,0,30,45,-1},--kinetic,energy,blast,heat,cold,electric,acid,stun,ls
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = KILLER,
	optionsBitmask = AIENABLED,
	diet = NONE,
	scale = 1.3,

	templates = {"object/mobile/dressed_stormtrooper_black_black.iff"},
	lootGroups = {},
	weapons = {"dark_trooper_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/stormtrooper",
	attacks = merge(riflemanmaster,marksmanmaster,fencermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(dark_trooper_novatrooper, "dark_trooper_novatrooper")
