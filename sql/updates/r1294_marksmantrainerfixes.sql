/*Trainers which need updating*/
/*Brawlers*/
UPDATE `trainers` SET `X` = -11, `Y` = -12.5, `oY` = 0, `oW` = 1 WHERE `pix` = 83;
UPDATE `trainers` SET `X` = 1890, `Y` = 2725, `oY` = 0, `oW` = 1, `Cell` = 0 WHERE `pix` = 82;

/*Marksman*/
UPDATE `trainers` SET `X` = 0, `Y` = -13, `oY` = 0, `oW` = 1 WHERE `pix` = 301;
UPDATE `trainers` SET `X` = 0, `Y` = -13, `oY` = 0, `oW` = 1 WHERE `pix` = 305;
UPDATE `trainers` SET `X` = 0, `Y` = -13, `oY` = 0, `oW` = 1 WHERE `pix` = 306;
UPDATE `trainers` SET `X` = 0, `Y` = -13, `oY` = 0, `oW` = 1 WHERE `pix` = 307;
UPDATE `trainers` SET `X` = 0, `Y` = -13, `oY` = 0, `oW` = 1, `Cell` = 2955426 WHERE `pix` = 302;

UPDATE `trainers` SET `X` = 4874, `Y` = -1444, `oY` = 0, `oW` = 1 WHERE `pix` = 286;
UPDATE `trainers` SET `oY` = 1, `oW` = 0 WHERE `pix` = 285;
UPDATE `trainers` SET `X` = 0, `Y` = -13, `oY` = 0, `oW` = 1, `Cell` = 1741461 WHERE `pix` = 287;
UPDATE `trainers` SET `X` = 4794, `Y` = -4730, `oY` = 0, `oW` = 1 WHERE `pix` = 288;
UPDATE `trainers` SET `X` = 0, `Y` = -13, `oY` = 0, `oW` = 1 WHERE `pix` = 289;
UPDATE `trainers` SET `X` = -4863, `Y` = 4079, `oY` = 0, `oW` = 1 WHERE `pix` = 292;
UPDATE `trainers` SET `X` = 0, `Y` = -13, `oY` = 0, `oW` = 1 WHERE `pix` = 293;
UPDATE `trainers` SET `X` = 0, `Y` = -13, `oY` = 0, `oW` = 1, `Cell` = 1650534 WHERE `pix` = 295;
UPDATE `trainers` SET `oY` = 1, `oW` = 0 WHERE `pix` = 296;
UPDATE `trainers` SET `X` = 0, `Y` = -13, `oY` = 0, `oW` = 1 WHERE `pix` = 316;
UPDATE `trainers` SET `X` = 0, `Y` = -13, `oY` = 0, `oW` = 1, `Planet` = 6, `Cell` = 4635690 WHERE `pix` = 317;
UPDATE `trainers` SET `oY` = 0.7, `oW` = 0.7 WHERE `pix` = 318;
UPDATE `trainers` SET `X` = -2.5, `Y` = 3, `oY` = 0.7, `oW` = 0.7 WHERE `pix` = 319;

UPDATE `trainers` SET `oY` = 0, `oW` = 1 WHERE `pix` = 297;
UPDATE `trainers` SET `X` = 4366, `Y` = 5384, `oY` = 0.7, `oW` = -0.7 WHERE `pix` = 299;
UPDATE `trainers` SET `X` = 0, `Y` = -13, `oY` = 0, `oW` = 1 WHERE `pix` = 309;
UPDATE `trainers` SET `oY` = 1 WHERE `pix` = 308;
UPDATE `trainers` SET `oY` = 1, `oW` = 0 WHERE `pix` = 310;
UPDATE `trainers` SET `X` = 0, `Y` = -13, `oY` = 0, `oW` = 1 WHERE `pix` = 311;
UPDATE `trainers` SET `X` = 0, `Y` = -13, `oY` = 0, `oW` = 1, `Cell` = 1153565 WHERE `pix` = 312;
UPDATE `trainers` SET `X` = 0, `Y` = -13, `oY` = 0, `oW` = 1 WHERE `pix` = 314;
UPDATE `trainers` SET `X` = -2931, `Y` = 2121, `oY` = 0.7, `oW` = 0.7 WHERE `pix` = 315;


/*Missing trainers*/
INSERT INTO `swgemu`.`trainers` (`Location`, `Trainer Type`, `Profession`, `CRC1`, `CRC2`, `CRC3`, `Planet`, `Cell`, `X`, `Y`, `Z`, `oY`, `oW`) VALUES
("Keren", "trainer_brawler", "combat_brawler", "BB904423", "6087ECB4", "298A8B39", 5, 0, 1537, 2757, 25, 0, 1),
("Keren", "trainer_brawler", "combat_brawler", "BB904423", "6087ECB4", "298A8B39", 5, 0, 1537, 2757, 25, 0, 1),

("Kaadara", "trainer_marksman", "combat_marksman", "D9101851", "0207B0C6", "4B0AD74B", 5, 0, 5182, 6632, -192, 0, 1),
("Coronet", "trainer_marksman", "combat_marksman", "D9101851", "0207B0C6", "4B0AD74B", 0, 0, -35, -4372, 0, 0.7, -0.7),
("Doaba Guerfel", "trainer_marksman", "combat_marksman", "D9101851", "0207B0C6", "4B0AD74B", 0, 0, 3338, 5516, 0, 0, 1),
("Tyrena", "trainer_marksman", "combat_marksman", "D9101851", "0207B0C6", "4B0AD74B", 0, 0, -5041, -2324, 0, -0.7, 0.7),
("Tyrena", "trainer_marksman", "combat_marksman", "D9101851", "0207B0C6", "4B0AD74B", 0, 0, -5249, -2306, 21, 1, 0);