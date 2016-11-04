crackdown_swamp_trooper_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_swamp_trooper_hard",
	randomNameType = NAME_SWAMPTROOPER,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 85,
	chanceHit = 0.86,
	damageMin = 540,
	damageMax = 850,
	baseXp = 8645,
	baseHAM = 16200,
	baseHAMmax = 23000,
	armor = 1,
	resists = {0,0,140,-1,-1,-1,200,-1,-1},
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,
	scale = 1.05,

	templates = {"object/mobile/dressed_swamp_trooper.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 2000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "wearables_common", chance = 2000000},
				{group = "wearables_uncommon", chance = 2000000},
			}
		}
	},
	weapons = {"stormtrooper_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/stormtrooper",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(carbineermid,marksmanmaster,riflemanmid)
}

CreatureTemplates:addCreatureTemplate(crackdown_swamp_trooper_hard, "crackdown_swamp_trooper_hard")
