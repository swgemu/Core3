lergo_brazee_missions =
  {
    {
      missionType = "deliver",
      primarySpawns =
      {
        { npcTemplate = "breggs_kertani", planetName = "naboo", npcName = "Breggs Ker'tani" }
      },
      secondarySpawns = {},
      itemSpawns =
      {
        { itemTemplate = "object/tangible/mission/quest_item/lergo_brazee_q1_needed.iff", itemName = "Pilot's Passcodes" }
      },
      rewards =
      {
        { rewardType = "credits", amount = 50 },
      }
    },
    {
      missionType = "escort",
      primarySpawns =
      {
        { npcTemplate = "slym_shudee", planetName = "naboo", npcName = "Slym Shu'dee" }
      },
      secondarySpawns = {},
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 50 },
      }
    },
    {
      missionType = "escort",
      primarySpawns =
      {
        { npcTemplate = "linay_sindir", planetName = "naboo", npcName = "Linay Sind'ir" }
      },
      secondarySpawns =
      {
        { npcTemplate = "gungan_thug", planetName = "naboo", npcName = "Gungan Thug" },
        { npcTemplate = "gungan_thug", planetName = "naboo", npcName = "Gungan Thug" },
        { npcTemplate = "gungan_thug", planetName = "naboo", npcName = "Gungan Thug" },
      },
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 50 },
      }
    },
    {
      missionType = "assassinate",
      primarySpawns =
      {
        { npcTemplate = "big_blismo", planetName = "naboo", npcName = "Big Blismo" }
      },
      secondarySpawns =
      {
        { npcTemplate = "gungan_thug", planetName = "naboo", npcName = "Gungan Thug" },
        { npcTemplate = "gungan_thug", planetName = "naboo", npcName = "Gungan Thug" },
        { npcTemplate = "gungan_thug", planetName = "naboo", npcName = "Gungan Thug" }
      },
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 100 },
      }
    },
  }

npcMapLergoBrazee =
  {
    {
      spawnData = { planetName = "naboo", npcTemplate = "lergo_brazee", x = 4.0, z = -0.9, y = -4.8, direction = -7, cellID = 5, position = STAND },
      worldPosition = { x = 2103, y = 2531 },
      npcNumber = 1,
      stfFile = "@static_npc/naboo/lergo_brazee",
      missions = lergo_brazee_missions
    }
  }

LergoBrazee = ThemeParkLogic:new {
  numberOfActs = 1,
  npcMap = npcMapLergoBrazee,
  className = "LergoBrazee",
  screenPlayState = "lergo_brazee_quest",
  distance = 600,
}

registerScreenPlay("LergoBrazee", true)

lergo_brazee_mission_giver_conv_handler = mission_giver_conv_handler:new {
  themePark = LergoBrazee
}
lergo_brazee_mission_target_conv_handler = mission_target_conv_handler:new {
  themePark = LergoBrazee
}