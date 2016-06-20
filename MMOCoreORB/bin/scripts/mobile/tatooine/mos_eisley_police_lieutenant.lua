mos_eisley_police_lieutenant = Creature:new {
	objectName = "@mob/creature_names:mos_eisley_police_lieutenant",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2400,
	baseHAMmax = 3000,
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
	creatureBitmask = PACK + STALKER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_mos_eisley_police_officer.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 5000000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "melee_weapons", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "wearables_common", chance = 1000000}
			}
		}
	},
	weapons = {"imperial_weapons_light"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/townperson",
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(mos_eisley_police_lieutenant, "mos_eisley_police_lieutenant")
