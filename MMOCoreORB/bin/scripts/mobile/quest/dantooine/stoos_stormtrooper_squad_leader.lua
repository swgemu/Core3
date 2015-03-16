stoos_stormtrooper_squad_leader = Creature:new {
  objectName = "@mob/creature_names:stormtrooper_squad_leader",
  randomNameType = NAME_STORMTROOPER_TAG,
  socialGroup = "imperial",
  faction = "imperial",
  level = 27,
  chanceHit = 0.37,
  damageMin = 260,
  damageMax = 270,
  baseXp = 2822,
  baseHAM = 8100,
  baseHAMmax = 9900,
  armor = 0,
  resists = {20,20,20,-1,30,-1,30,-1,-1},
  meatType = "",
  meatAmount = 0,
  hideType = "",
  hideAmount = 0,
  boneType = "",
  boneAmount = 0,
  milk = 0,
  tamingChance = 0,
  ferocity = 0,
  pvpBitmask = NONE,
  creatureBitmask = NONE,
  optionsBitmask = 136,
  diet = HERBIVORE,

  templates = {"object/mobile/dressed_stormtrooper_squad_leader_white_white.iff"},
  lootGroups = {
    {
      groups = {
        {group = "color_crystals", chance = 100000},
        {group = "junk", chance = 5500000},
        {group = "rifles", chance = 550000},
        {group = "pistols", chance = 550000},
        {group = "melee_weapons", chance = 550000},
        {group = "carbines", chance = 550000},
        {group = "clothing_attachments", chance = 250000},
        {group = "armor_attachments", chance = 250000},
        {group = "stormtrooper_common", chance = 700000},
        {group = "wearables_common", chance = 1000000}
      },
      lootChance = 2800000
    }
  },
  weapons = {"stormtrooper_weapons"},
  conversationTemplate = "stoos_olko_mission_target_convotemplate",
  attacks = merge(riflemanmaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(stoos_stormtrooper_squad_leader, "stoos_stormtrooper_squad_leader")
