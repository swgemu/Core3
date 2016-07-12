theme_park_singing_mountain_clan_arch_witch_peila = Creature:new {
  objectName = "@mob/creature_names:singing_mtn_clan_arch_witch",
  randomNameType = NAME_GENERIC,
  randomNameTag = true,
  socialGroup = "mtn_clan",
  faction = "mtn_clan",
  level = 107,
  chanceHit = 1,
  damageMin = 645,
  damageMax = 1000,
  baseXp = 10174,
  baseHAM = 24000,
  baseHAMmax = 30000,
  armor = 2,
  resists = {100,5,5,100,100,100,100,100,-1},
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
  creatureBitmask = PACK + KILLER + HEALER,
  optionsBitmask = AIENABLED,
  diet = HERBIVORE,

  templates = {"object/mobile/dressed_dathomir_sing_mt_clan_arch_witch.iff"},
  lootGroups = {
    {
      groups = {
        {group = "junk", chance = 2300000},
        {group = "color_crystals", chance = 1000000},
        {group = "melee_weapons", chance = 2700000},
        {group = "wearables_uncommon", chance = 4000000}
      }
    }
  },
  weapons = {"mixed_force_weapons"},
  conversationTemplate = "",
  attacks = merge(brawlermaster,pikemanmaster,forcewielder)
}

CreatureTemplates:addCreatureTemplate(theme_park_singing_mountain_clan_arch_witch_peila, "theme_park_singing_mountain_clan_arch_witch_peila")
