crackdown_stormtrooper_squad_leader_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_stormtrooper_squad_leader_hard",
	randomNameType = NAME_STORMTROOPER,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 87,
	chanceHit = 0.87,
	damageMin = 560,
	damageMax = 870,
	baseXp = 8445,
	baseHAM = 16100,
	baseHAMmax = 24000,
	armor = 1,
	resists = {0,0,0,-1,130,-1,130,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,
	scale = 1.05,

	templates = {"object/mobile/dressed_stormtrooper_squad_leader_white_gold.iff",
				"object/mobile/dressed_stormtrooper_groupleader_m.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 7550000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000},
				{group = "stormtrooper_common", chance = 100000}
			},
			lootChance = 2800000
		}
	},
	weapons = {"stormtrooper_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/stormtrooper",
	personalityStf = "@hireling/hireling_stormtrooper",
	attacks = merge(riflemanmid,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_stormtrooper_squad_leader_hard, "crackdown_stormtrooper_squad_leader_hard")
