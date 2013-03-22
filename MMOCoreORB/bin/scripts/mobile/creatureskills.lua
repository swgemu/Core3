--This is the Skill trees for NPC's
--to modify this for hybrids you can create a name for your hybrid tree and insert it at the bottom of the list
--in the Sever Administrator NPC Skill section
-- command useage inside npc templates is attacks = merge(skilltreename1,skilltreename2,ect,ect)
--creature level 1 to 10
brawlernovice = { {"intimidate1",""},{"melee1hspinattack1",""},{"melee1hlunge1",""},{"melee2hlunge1",""},{"polearmlunge1",""},{"unarmedlunge1",""} }
marksmannovice = { {"overchargeshot1",""},{"pointblanksingle1",""} }
--creature level 11 to 15 use combinations of depending on weapons in thier weapons groups
--brawlerua = { {"intimidate1",""},{"berserk1",""},{"unarmedlunge1",""},{"unarmedhit1",""},{"unarmedstun1",""},{"unarmedstun1",""},{"unarmedspinattack1",""},{"unarmedblind1",""} }
--brawler1hand = { {"intimidate1",""},{"melee1hspinattack1",""},{"melee1hlunge1",""},{"melee1hdizzyhit1",""},{"melee1hhit1",""},{"melee1hbodyhit1",""} }
--brawler2hand = { {"intimidate1",""},{"melee2hhit1",""},{"melee2hlunge1",""},{"melee2hheadhit1",""},{"melee2hsweep1",""},{"melee2hspinattack1",""} }
--brawlerpole = { {"intimidate1",""},{"polearmlunge1",""},{"polearmhit1",""},{"polearmleghit1",""},{"polearmstun1",""},{"polearmspinattack1",""} }
--marksmanpistol = { {"overchargeshot1",""},{"pointblanksingle1",""},{"diveshot",""},{"kipupshot",""},{"rollshot",""},{"bodyshot2",""},{"healthshot1",""} }
--marksmancarbine = { {"overchargeshot1",""},{"pointblanksingle1",""},{"legshot2",""},{"fullautosingle1",""},{"actionshot1",""} }
--marksmanrifle = { {"overchargeshot1",""},{"pointblankarea1",""},{"pointblanksingle1",""},{"mindshot1",""} }
--creature level 15 to 25 
marksmanmaster = { {"overchargeshot1",""},{"pointblanksingle1",""},{"diveshot",""},{"kipupshot",""},{"rollshot",""},{"bodyshot1",""},{"healthshot1",""},{"legshot1",""},{"fullautosingle1",""},{"actionshot1",""},{"mindshot1",""} }
brawlermaster = { {"intimidate1",""},{"unarmedlunge1",""},{"unarmedhit1",""},{"unarmedstun1",""},{"unarmedstun1",""},{"unarmedspinattack1",""},{"unarmedblind1",""},{"melee1hspinattack1",""},{"melee1hlunge1",""},{"melee1hdizzyhit1",""},{"melee1hhit1",""},{"melee1hbodyhit1",""},{"melee2hhit1",""},{"melee2hlunge1",""},{"melee2hheadhit1",""},{"melee2hsweep1",""},{"melee2hspinattack1",""},{"polearmlunge1",""},{"polearmhit1",""},{"polearmleghit1",""},{"polearmstun1",""},{"polearmspinattack1",""} }
--creature level 25 to 30 use base profession master with these depending on weapons in thier weapons groups
--carbineerassault = { {"actionshot2",""},{"fullautosingle1",""},{"wildshot1",""},{"scattershot1",""} }
--carbineermarksman = { {"actionshot2",""},{"fullautosingle1",""},{"legshot1",""},{"cripplingshot",""} }
--carbineertactics = { {"actionshot2",""},{"fullautosingle2",""},{"burstshot2",""},{"suppresionfire2",""} }
--carbineerspecial = { {"actionshot2",""},{"fullautosingle2",""},{"fullautoarea2",""},{"chargeshot2",""} }
--pistoleerhold = { {"healthshot2",""},{"pointblanksingle2",""},{"bodyshot3",""} }
--pistoleertech = { {"healthshot2",""},{"disarmingshot1",""},{"doubletap",""},{"stoppingshot",""},{"fanshot",""} }
--pistoleerstance = { {"healthshot2",""},{"pistolmeleedefense2",""} }
--riflemansniping = { {"strafeshot1",""},{"mindshot2",""},{"headshot3",""},{"supriseshot",""},{"snipershot",""} }
--riflemanconceal = { {"strafeshot1",""},{"concealshot",""} }
--riflemancounter = { {"strafeshot1",""},{"flushingshot2",""},{"startleshot2",""} }
--riflemanability = { {"strafeshot1",""},{"flurryshot2",""} }
--fencerstance = { {"melee1hhit2",""},{"melee1hscatterhit2",""},{"melee1hdizzyhit2",""} }
--fencerfootwork = { {"melee1hhit2",""},{"melee1hhealthhit2",""},{"melee1hspinattack2",""} }
--fencertech = { {"melee1hhit2",""},{"melee1hbodyhit3",""} }
--fencerfinesse = { {"melee1hhit2",""},{"melee1hblindhit2",""} }
--swordsmanoffense = { {"melee2hhit2",""},{"melee2harea3",""} }
--swordsmantech = { {"melee2hhit2",""},{"melee2hheadhit3",""} }
--swordsmandefense = { {"melee2hhit2",""},{"melee2hspinattack2",""},{"melee2hsweep2",""} }
--swordsmanfinesse = { {"melee2hhit2",""},{"melee2hmindhit2",""} }
--pikemanstance = { {"polearmhit2",""},{"polearmspinattack2",""},{"polearmstun2",""} }
--pikemanoffense = { {"polearmarea2",""},{"polearmhit2",""},{"polearmleghit3",""} }
--pikemandefense = { {"polearmhit2",""},{"polearmsweep2",""} }
--pikemansupport = { {"polearmactionhit2",""},{"polearmhit2",""} }
--tkaconditioning = { {"unarmedhit2",""},{"unarmedknockdown2",""} }
--tkatech = { {"unarmedcombo2",""},{"unarmedhit2",""},{"unarmedspinattack2",""} }
--tkastriking = { {"unarmedbodyhit1",""},{"unarmedheadhit1",""},{"unarmedhit2",""},{"unarmedleghit1",""} }
--creature level 30 and above use combinations of base profesion masterery and these
commandomaster = { {"flamecone1"},{"flamecone2"},{"flamesingle1"},{"flamesingle2"},{"fireacidcone1"},{"fireacidcone2"},{"fireacidsingle1"},{"fireacidsingle2"} }
carbineermaster = { {"actionshot2",""},{"fullautosingle2",""},{"wildshot2",""},{"scattershot2",""},{"legshot2",""},{"cripplingshot",""},{"burstshot2",""},{"suppressionfire2",""} }
pistoleermaster = { {"healthshot2",""},{"pointblanksingle2",""},{"bodyshot3",""},{"pistolmeleedefense2",""},{"disarmingshot1",""},{"doubletap",""},{"stoppingshot",""},{"fanshot",""} }
riflemanmaster = { {"strafeshot2",""},{"mindshot2",""},{"surpriseshot",""},{"snipershot",""},{"concealshot",""},{"flushingshot2",""},{"startleshot2",""},{"flurryshot2",""} }
fencermaster = { {"melee1hhit2",""},{"melee1hscatterhit2",""},{"melee1hdizzyhit2",""},{"melee1hhealthhit2",""},{"melee1hspinattack2",""},{"melee1hbodyhit2",""},{"melee1hblindhit2",""} }
swordsmanmaster = { {"melee2hhit2",""},{"melee2harea2",""},{"melee2hspinattack2",""},{"melee2hsweep2",""},{"melee2hmindhit2",""} }
pikemanmaster = { {"polearmactionhit2",""},{"polearmarea2",""},{"polearmhit2",""},{"polearmleghit3",""},{"polearmspinattack2",""},{"polearmstun2",""},{"polearmsweep2",""} }
tkamaster = { {"unarmedleghit1",""},{"unarmedbodyhit1",""},{"unarmedheadhit1",""},{"unarmedspinattack2",""},{"unarmedcombo2",""},{"unarmedknockdown2",""} }
--npc jedi skills
lightsabermaster = { {"saber1hheadhit1",""},{"saber1hhit1",""},{"saber1hcombohit1",""},{"saber1hflurry1",""},{"saber2hbodyhit1",""},{"saber2hfrenzy",""},{"saber2hhit1",""},{"saber2hphantom",""},{"saber2hsweep1",""},{"saberpolearmdervish1",""},{"saberpolearmhit1",""},{"saberpolearmleghit1",""},{"saberpolearmspinattack1",""},{"saberslash1",""},{"saberthrow1",""} }
forcepowermaster = { {"forcelightningsingle2",""},{"forcelightingcone2",""},{"forceintimidate2",""},{"forceknockdown2",""},{"forcethrow2",""},{"forcechoke",""} }
-- npc force wielders use standard profession mastery with the addition of this command
forcewielder ={ {"forcelightningsingle1",""},{"forcelightingcone1",""} }
--Server Administrator NPC skill trees place below
