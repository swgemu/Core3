--This is the Skill trees for NPC's
--to modify this for hybrids you can create a name for your hybrid tree and insert it at the bottom of the list
--in the Server Administrator NPC Skill section
-- command usage inside npc templates is attacks = merge(skilltreename1,skilltreename2,ect,ect)

--creature level 1 to 10
brawlernovice = { {"melee1hlunge1",""},{"melee2hlunge1",""},{"polearmlunge1",""},{"unarmedlunge1",""} }
marksmannovice = { {"overchargeshot1",""},{"pointblanksingle1",""},{"pointblankarea1",""} }

--creature level 11 to 15
brawlermid = { {"melee1hlunge1",""},{"melee1hhit1",""},{"melee1hbodyhit1",""},{"melee2hlunge1",""},{"melee2hhit1",""},{"melee2hheadhit1",""},{"polearmlunge1",""},{"polearmhit1",""},{"polearmleghit1",""},{"unarmedlunge1",""},{"unarmedhit1",""},{"unarmedstun1",""} }
marksmanmid = { {"overchargeshot1",""},{"pointblanksingle1",""},{"pointblankarea1",""},{"headshot1",""},{"bodyshot1",""},{"legshot1",""},{"fullautosingle1",""},{"diveshot",""},{"kipupshot",""},{"rollshot",""} }

--creature level 16 to 20
marksmanmaster = { {"overchargeshot2",""},{"pointblanksingle1",""},{"pointblankarea1",""},{"diveshot",""},{"kipupshot",""},{"rollshot",""},{"bodyshot2",""},{"healthshot1",""},{"legshot2",""},{"fullautosingle1",""},{"actionshot1",""},{"headshot2",""},{"mindshot1",""},{"warningshot",""},{"suppressionfire1",""} }
brawlermaster = { {"unarmedlunge2",""},{"unarmedhit1",""},{"unarmedstun1",""},{"unarmedblind1",""},{"unarmedspinattack1",""},{"melee1hspinattack1",""},{"melee1hlunge2",""},{"melee1hdizzyhit1",""},{"melee1hhit1",""},{"melee1hbodyhit1",""},{"melee2hhit1",""},{"melee2hlunge2",""},{"melee2hheadhit1",""},{"melee2hsweep1",""},{"melee2hspinattack1",""},{"polearmlunge2",""},{"polearmhit1",""},{"polearmleghit1",""},{"polearmstun1",""},{"polearmspinattack1",""} }

--creature level 21 to 25 use base profession master with these depending on weapons in thier weapons groups
bountyhunternovice = { {"firelightningsingle1",""},{"bleedingshot",""},{"underhandshot",""} }
commandonovice = { {"flamesingle1",""},{"fireacidsingle1",""} }
carbineernovice = { {"actionshot2",""},{"fullautosingle2",""},{"fullautoarea1",""},{"scattershot1",""},{"legshot3",""},{"burstshot1",""} }
pistoleernovice = { {"healthshot2",""},{"pointblanksingle2",""},{"pistolmeleedefense1",""},{"disarmingshot1",""} }
riflemannovice = { {"strafeshot1",""},{"mindshot2",""},{"flushingshot1",""},{"flurryshot1",""} }
fencernovice = { {"melee1hhit2",""},{"melee1hscatterhit1",""},{"melee1hhealthhit1",""},{"melee1hbodyhit2",""},{"melee1hblindhit1",""} }
swordsmannovice = { {"melee2hhit2",""},{"melee2harea1",""},{"melee2hheadhit2",""},{"melee2hspinattack2",""},{"melee2hmindhit1",""} }
pikemannovice = { {"polearmactionhit1",""},{"polearmhit2",""},{"polearmleghit2",""},{"polearmstun2",""},{"polearmsweep1",""} }
tkanovice = { {"unarmedhit2",""},{"unarmedbodyhit1",""},{"unarmeddizzy1",""},{"unarmedknockdown1",""} }

--creature level 26 to 30 use base profession master with these depending on weapons in their weapons groups
bountyhuntermid = { {"firelightningcone1",""},{"firelightningsingle1",""},{"bleedingshot",""},{"underhandshot",""},{"eyeshot",""},{"knockdownfire",""} }
commandomid = { {"flamecone1",""},{"flamesingle1",""},{"fireacidcone1",""},{"fireacidsingle1",""} }
carbineermid = { {"actionshot2",""},{"fullautosingle2",""},{"fullautoarea2",""},{"scattershot2",""},{"legshot3",""},{"burstshot2",""},{"wildshot1",""},{"chargeshot1",""},{"cripplingshot",""} }
pistoleermid = { {"bodyshot3",""},{"healthshot2",""},{"pointblanksingle2",""},{"pistolmeleedefense2",""},{"disarmingshot1",""},{"doubletap",""},{"stoppingshot",""} }
riflemanmid = { {"headshot3",""},{"strafeshot1",""},{"mindshot2",""},{"flushingshot2",""},{"flurryshot2",""},{"startleshot1",""} }
fencermid = { {"melee1hhit2",""},{"melee1hscatterhit1",""},{"melee1hhealthhit1",""},{"melee1hbodyhit3",""},{"melee1hblindhit2",""},{"melee1hdizzyhit2",""},{"melee1hspinattack2",""} }
swordsmanmid = { {"melee2hhit2",""},{"melee2harea2",""},{"melee2hheadhit3",""},{"melee2hspinattack2",""},{"melee2hmindhit2",""},{"melee2hsweep2",""} }
pikemanmid = { {"polearmactionhit2",""},{"polearmhit2",""},{"polearmleghit3",""},{"polearmstun2",""},{"polearmsweep2",""},{"polearmarea1",""},{"polearmspinattack2",""} }
tkamid = { {"unarmedhit2",""},{"unarmedbodyhit1",""},{"unarmeddizzy1",""},{"unarmedknockdown1",""},{"unarmedleghit1",""},{"unarmedcombo1",""},{"unarmedspinattack2",""} }

--creature level 31 and above use combinations of base profesion mastery and these
bountyhuntermaster = { {"firelightningcone1",""},{"firelightningcone2",""},{"firelightningsingle1",""},{"firelightningsingle2",""},{"bleedingshot",""},{"underhandshot",""},{"eyeshot",""},{"knockdownfire",""},{"torsoshot",""},{"confusionshot",""},{"fastblast",""},{"sprayshot",""} }
commandomaster = { {"flamecone1",""},{"flamecone2",""},{"flamesingle1",""},{"flamesingle2",""},{"fireacidcone1",""},{"fireacidcone2",""},{"fireacidsingle1",""},{"fireacidsingle2",""} }
carbineermaster = { {"actionshot2",""},{"fullautosingle2",""},{"fullautoarea2",""},{"wildshot2",""},{"scattershot2",""},{"legshot3",""},{"cripplingshot",""},{"burstshot2",""},{"suppressionfire2",""},{"chargeshot2",""} }
pistoleermaster = { {"healthshot2",""},{"pointblanksingle2",""},{"bodyshot3",""},{"pistolmeleedefense2",""},{"disarmingshot2",""},{"doubletap",""},{"stoppingshot",""},{"fanshot",""},{"pointblankarea2",""},{"multitargetpistolshot",""} }
riflemanmaster = { {"headshot3",""},{"strafeshot2",""},{"mindshot2",""},{"flushingshot2",""},{"startleshot2",""},{"flurryshot2",""} }
fencermaster = { {"melee1hhit3",""},{"melee1hscatterhit2",""},{"melee1hdizzyhit2",""},{"melee1hhealthhit2",""},{"melee1hspinattack2",""},{"melee1hbodyhit2",""},{"melee1hblindhit2",""} }
swordsmanmaster = { {"melee2hhit3",""},{"melee2harea3",""},{"melee2hspinattack2",""},{"melee2hsweep2",""},{"melee2hmindhit2",""},{"melee2hheadhit3",""} }
pikemanmaster = { {"polearmactionhit2",""},{"polearmarea2",""},{"polearmhit3",""},{"polearmleghit3",""},{"polearmspinattack2",""},{"polearmstun2",""},{"polearmsweep2",""} }
tkamaster = { {"unarmedhit3",""},{"unarmedleghit1",""},{"unarmedbodyhit1",""},{"unarmedheadhit1",""},{"unarmedspinattack2",""},{"unarmedcombo2",""},{"unarmedknockdown2",""},{"unarmeddizzy1",""} }

--npc jedi skills
lightsabermaster = { {"saber1hheadhit1",""},{"saber1hhit1",""},{"saber1hcombohit1",""},{"saber1hflurry",""},{"saber2hbodyhit1",""},{"saber2hfrenzy",""},{"saber2hhit1",""},{"saber2hphantom",""},{"saber2hsweep1",""},{"saberpolearmdervish",""},{"saberpolearmhit1",""},{"saberpolearmleghit1",""},{"saberpolearmspinattack1",""},{"saberslash1",""},{"saberthrow1",""} }
forcepowermaster = { {"forcelightningsingle2",""},{"forcelightningcone2",""},{"mindblast2",""},{"forceknockdown2",""},{"forceweaken2",""},{"forcethrow2",""},{"forcechoke",""} }

-- npc force wielders use standard profession mastery with the addition of this command
forcewielder ={ {"forcelightningsingle1",""},{"mindblast1",""},{"forcechoke",""},{"forceweaken1",""},{"forceknockdown1",""},{"forcelightningcone1",""} }
--Server Administrator NPC skill trees place below
