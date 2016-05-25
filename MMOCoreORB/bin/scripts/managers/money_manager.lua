-- Money account ids must match the enum in MoneyManager.h
-- Any new accounts added must be added to the bottom of this list, to the
-- bottom of the enum in MoneyManager.h, and to the money/acct_n.stf file.

-- { id, stringid } 
moneyAccountData = {
  { 1, "charactercreation" }, -- Character Creation
  { 2, "newbietutorial" }, -- Newbie Tutorial
  { 3, "customerservice" }, -- Customer Service
  { 4, "missionsystemdynamic" }, -- Dynamic Mission System
  { 5, "missionsystemplayer" }, -- Player Mission System
  { 6, "bountysystem" }, -- Bounty System
  { 7, "cloningsystem" }, -- Cloning System
  { 8, "insurancesystem" }, -- Insurance System
  { 9, "travelsystem" }, -- the Galactic Travel Commission
  { 10, "shippingsystem" }, -- the Galactic Shipping Commission
  { 11, "bazaarsystem" }, -- the Galactic Trade Commission
  { 12, "dispensersystem" }, -- Dispenser System
  { 13, "skilltrainingsystem" }, -- Skill Training Union
  { 14, "rebelfaction" }, -- Rebellion
  { 15, "imperialfaction" }, -- the Empire
  { 16, "jabbaspalace" }, -- Jabba the Hutt
  { 17, "poisystem" }, -- POI System
  { 18, "corpseexpiration" }, -- Corpse Expiration Tracking
  { 19, "testing" }, -- Testing
  { 20, "structuremaintanence" }, -- Structure Maintenance
  { 21, "tipsurcharge" }, -- Tip Surcharge
  { 22, "vendormaintanence" }, -- Vendor Wages
  { 23, "npcloot" }, -- NPC Loot
  { 24, "junkdealer" }, -- Junk Dealer
  { 25, "cantinadrink" }, -- Cantina Drink
  { 26, "betatest" }, -- Beta Test Fund
  { 27, "badgroupcoinsplit" }, -- Group Split Error Account
  { 28, "gamblingslotstandard" }, -- Standard Slot Machine Account
  { 29, "gamblingroulette" }, -- Roulette Account
  { 30, "gamblingcardsabacc" }, -- Sabacc Account
  { 31, "vehiclerepairs" }, -- Vehicle Repair System
  { 32, "relicdealer" }, -- Relic Dealer
  { 33, "newplayerquests" }, -- New Player Quests
  { 34, "fines" }, -- Contraband Scanning Fines
  { 35, "bank" }, -- bank
}
