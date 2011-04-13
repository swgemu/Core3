swirl_prong_pack_leader = Creature:new {
	objectName = "@mob/creature_names:swirl_prong_pack_leader",
	socialGroup = "Swirl Prong",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.400000,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3188,
	baseHAM = 9550,
	baseHAMmax = 9550,
	armor = 0,
	resists = {35,0,0,0,-1,-1,-1,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/swirl_prong.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(swirl_prong_pack_leader, "swirl_prong_pack_leader")