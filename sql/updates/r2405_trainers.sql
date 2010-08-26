-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.0.83-0ubuntu3


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


--
-- Create schema swgemu
--

CREATE DATABASE IF NOT EXISTS swgemu;
USE swgemu;

--
-- Definition of table `swgemu`.`trainers`
--

DROP TABLE IF EXISTS `swgemu`.`trainers`;
CREATE TABLE  `swgemu`.`trainers` (
  `Location` varchar(64) default NULL,
  `Trainer Name` varchar(64) default NULL,
  `Trainer Type` varchar(64) default NULL,
  `Profession` varchar(64) NOT NULL,
  `CRC1` varchar(16) default NULL,
  `CRC2` varchar(16) default NULL,
  `CRC3` varchar(16) default NULL,
  `Planet` smallint(6) default NULL,
  `Cell` bigint(20) default '0',
  `WorldX` double default '0',
  `WorldY` double default '0',
  `WorldZ` double default '0',
  `CellX` double default '0',
  `CellY` double default '0',
  `CellZ` double default '0',
  `oY` double default '0',
  `oW` double default '0',
  `pix` int(10) unsigned NOT NULL auto_increment,
  `planetmapid` tinyint(1) unsigned NOT NULL default '0',
  PRIMARY KEY  (`pix`),
  KEY `pix` (`pix`)
) ENGINE=MyISAM AUTO_INCREMENT=523 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `swgemu`.`trainers`
--

/*!40000 ALTER TABLE `trainers` DISABLE KEYS */;
LOCK TABLES `trainers` WRITE;
INSERT INTO `swgemu`.`trainers` VALUES  ('Coronet ','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',0,0,-369,-4533,28,0,0,0,0.717733,0.696318,1,0),
 ('Doaba Guerfel','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',0,3075410,3105,5274,301,12,6,1.13306,1,0,2,0),
 ('Kor Vella','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',0,2955398,-3675,3064,87,12,6,1.13306,1,0,3,0),
 ('Tyrena','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',0,1935461,-5515,-2691,22,12,6,1.13306,1,0,4,0),
 ('Kaadara','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',5,1741468,5125,6792,-190,12,6,1.13306,1,0,5,0),
 ('Keren','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',5,0,1524,2782,25,0,0,0,0.320035,0.947406,6,0),
 ('Keren','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',5,1650541,1775,2559,13,12,6,1.13306,1,0,7,0),
 ('Keren','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',5,0,2005,2483,12,0,0,0,0.852886,-0.522097,8,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Moenia','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',5,0,4819,-4704,4.17,0,0,0,-0.650473,0.75953,9,0),
 ('Moenia','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',5,1717553,4817,-4994,4,12,6,1.13306,1,0,10,0),
 ('Theed','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',5,0,-5129,4238,6,0,0,0,0.827,0.561,11,0),
 ('Theed','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',5,1692091,-5440,4002,7,12,6,1.13306,1,0,12,0),
 ('Theed','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',5,0,-5993,4286,6,0,0,0,0.566754,0.823887,13,0),
 ('Narmle','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',6,0,-5159,-2325,80,0,0,0,0.931801,0.362969,14,0),
 ('Narmle','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',6,4635411,-4998,-2412,81,12,6,1.13306,1,0,15,0),
 ('Restuss','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',6,0,5388,5673,80,0,0,0,0.821,0.5721,16,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Dearic','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',7,3175559,614,-3047,7,12,6,1.13306,1,0,17,0),
 ('Nashal','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',7,4265413,4281,5129,3,12,6,1.13306,1,0,18,0),
 ('Bestine','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',8,1028579,-1257,-3527,13,12,6,1.13306,1,0,19,0),
 ('Mos Eisley','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',8,1189576,3338,-4717,6,12,6,1.13306,1,0,20,0),
 ('Mos Entha','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',8,0,1273,3151,7,0,0,0,0.984731,0.174081,21,0),
 ('Mos Entha','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',8,1154181,1308,3368,8,12,6,1.13306,1,0,22,0),
 ('Mos Espa','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',8,1256019,-3047,2070,6,12,6,1.13306,1,0,23,0),
 ('Doaba Guerfel','a Fencer trainer','trainer_1hsword','combat_1hsword','4B88D720','909F7FB7','D992183A',0,0,3284,5406,300,0,0,0,0.310022,0.95073,24,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Kor Vella','a Fencer trainer','trainer_1hsword','combat_1hsword','4B88D720','909F7FB7','D992183A',0,0,-3320,3220,86,0,0,0,0,1,25,0),
 ('Mos Eisley','a Fencer trainer','trainer_1hsword','combat_1hsword','4B88D720','909F7FB7','D992183A',8,9655496,3528,-4762,5,4.4,-7.8,0.2,0.309956,0.950751,26,0),
 ('Mos Espa','a Fencer trainer','trainer_1hsword','combat_1hsword','4B88D720','909F7FB7','D992183A',8,0,-2964,2021,5,0,0,0,-0.279,0.96,27,0),
 ('Theed','a Fencer trainer','trainer_1hsword','combat_1hsword','4B88D720','909F7FB7','D992183A',5,0,-5565,4304,6,0,0,0,-0.66759,0.744529,28,0),
 ('Narmle','a Fencer trainer','trainer_1hsword','combat_1hsword','4B88D720','909F7FB7','D992183A',6,0,-5219,-2164,80.6094,0,0,0,0,1,29,0),
 ('Dearic','a Fencer trainer','trainer_1hsword','combat_1hsword','4B88D720','909F7FB7','D992183A',7,0,548.007,-2865.16,6,0,0,0,0.997019,0.0771557,30,0),
 ('Nashal','a Fencer trainer','trainer_1hsword','combat_1hsword','4B88D720','909F7FB7','D992183A',7,4265477,4511,5159,2,5,-8,0,-0.24217,0.970234,31,0),
 ('Mos Entha','a Commando trainer','trainer_commando','combat_commando','26491B73','98F1F3B2','387F613C',8,0,1551.92,3334.86,7,0,0,0,0.468842,0.883282,32,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Wayfar','a Commando trainer','trainer_commando','combat_commando','26491B73','98F1F3B2','387F613C',8,0,-5038,-6609,75,0,0,0,0.919099,-0.394028,33,0),
 ('Narmle','a Commando trainer','trainer_commando','combat_commando','26491B73','98F1F3B2','387F613C',6,0,-5180,-2349,80,0,0,0,0.999763,0.0217487,34,0),
 ('Restuss','a Commando trainer','trainer_commando','combat_commando','26491B73','98F1F3B2','387F613C',6,4635689,5436,5811,81,9.51478,-10.433,1.13306,0.336511,0.941679,35,0),
 ('Rebel Outpost','a Commando trainer','trainer_commando','combat_commando','26491B73','98F1F3B2','387F613C',6,4505792,3695,-6484,96,-1.5837,2.75309,0.74,0.999913,0.0131604,36,0),
 ('Kor Vella','a Commando trainer','trainer_commando','combat_commando','26491B73','98F1F3B2','387F613C',0,0,-3344,3292,86,0,0,0,0,1,37,0),
 ('Imperial Oasis','a Commando trainer','trainer_commando','combat_commando','26491B73','98F1F3B2','387F613C',8,0,-5292,2718,6.76132,0,0,0,0.999696,-0.0246574,38,0),
 ('Theed','a Swordsman trainer','trainer_2hsword','combat_2hsword','19DD3748','C2CA9FDF','8BC7F852',5,0,-5382,4327,0,0,0,0,0,0,39,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Kor Vella','a Swordsman trainer','trainer_2hsword','combat_2hsword','19DD3748','C2CA9FDF','8BC7F852',0,0,-3374,3285,86,0,0,0,0.690507,0.723326,40,0),
 ('Narmle','a Swordsman trainer','trainer_2hsword','combat_2hsword','19DD3748','C2CA9FDF','8BC7F852',6,0,-5214,-2167,80.4173,0,0,0,0,1,41,0),
 ('Dearic','a Swordsman trainer','trainer_2hsword','combat_2hsword','19DD3748','C2CA9FDF','8BC7F852',7,0,552,-2865,6,0,0,0,0.998527,0.0542564,42,0),
 ('Mos Espa','a Swordsman trainer','trainer_2hsword','combat_2hsword','19DD3748','C2CA9FDF','8BC7F852',8,0,-2971,2032,5,0,0,0,0.998451,0.0556371,43,0),
 ('Karen','a Rifleman trainer','trainer_rifleman','combat_rifleman','E56324EF','3E748C78','7779EBF5',5,0,1276,2685,13,0,0,0,-0.591354,0.806412,44,0),
 ('Mos Eisley','a Rifleman trainer','trainer_rifleman','combat_rifleman','E56324EF','3E748C78','7779EBF5',8,0,3426,-4917,5,0,0,0,0,1,45,0),
 ('Narmle','a Rifleman trainer','trainer_rifleman','combat_rifleman','E56324EF','3E748C78','7779EBF5',6,0,-5215,-2373,80,0,0,0,0.999804,-0.0198209,46,0),
 ('Rebel Outpost','a Rifleman trainer','trainer_rifleman','combat_rifleman','E56324EF','3E748C78','7779EBF5',6,0,3649,-6492,96,0,0,0,0.384359,0.923184,47,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Tyrena','a Rifleman trainer','trainer_rifleman','combat_rifleman','E56324EF','3E748C78','7779EBF5',0,0,-5234,-2488,21,0,0,0,0.999421,0.034013,48,0),
 ('Dearic','a Rifleman trainer','trainer_rifleman','combat_rifleman','E56324EF','3E748C78','7779EBF5',7,0,587,-2870,6,0,0,0,0,1,49,0),
 ('Kor Vella','a Teras Kasi Artist trainer','trainer_unarmed','combat_unarmed','9C58CC5C','474F64CB','0E420346',0,0,-3570,3146,86,0,0,0,0.88544,-0.445034,50,0),
 ('Theed','a Teras Kasi Artist trainer','trainer_unarmed','combat_unarmed','9C58CC5C','474F64CB','0E420346',5,0,-5649,4206,6,0,0,0,0,1,51,0),
 ('Narmle','a Teras Kasi Artist trainer','trainer_unarmed','combat_unarmed','9C58CC5C','474F64CB','0E420346',6,0,-5288,-2508,79.0383,0,0,0,0,1,52,0),
 ('Dearic','a Teras Kasi Artist trainer','trainer_unarmed','combat_unarmed','9C58CC5C','474F64CB','0E420346',7,0,418,-2906,6,0,0,0,0,1,53,0),
 ('Mos Espa','a Teras Kasi Artist trainer','trainer_unarmed','combat_unarmed','9C58CC5C','474F64CB','0E420346',8,0,-2812,1973,0,0,0,0,0,0,54,0),
 ('Wayfar','a Teras Kasi Artist trainer','trainer_unarmed','combat_unarmed','9C58CC5C','474F64CB','0E420346',8,0,-5054,-6632,75,0,0,0,0.248871,0.968537,55,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Bestine','a Bio-engineer trainer','trainer_bioengineer','outdoors_bio_engineer','79DD77E3','A2CADF74','EBC7B8F9',8,0,-1444.06,-3749.08,10,0,0,0,0.707921,0.706292,56,0),
 ('Nashal','a Bio-engineer trainer','trainer_bioengineer','outdoors_bio_engineer','79DD77E3','A2CADF74','EBC7B8F9',7,4265423,4343,5146,3,18,14,1.566,0.743,0.669,57,0),
 ('Theed','a Bio-engineer trainer','trainer_bioengineer','outdoors_bio_engineer','79DD77E3','A2CADF74','EBC7B8F9',5,0,-5017,4009,6,0,0,0,0,1,58,0),
 ('Coronet','a Bio-engineer trainer','trainer_bioengineer','outdoors_bio_engineer','79DD77E3','A2CADF74','EBC7B8F9',0,0,-424.092,-4651.85,28,0,0,0,-0.729596,0.683878,59,0),
 ('Coronet','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',0,1855508,-274,-4379,29,-11,-14,1.13306,0,1,60,20),
 ('Doaba Guerfel','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',0,3075361,3216,5239,301,-11,-14,1.13306,0,1,61,20),
 ('Tyrena','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',0,1935445,-5474,-2755,22,-11,-14,1.13306,0,1,62,20);
INSERT INTO `swgemu`.`trainers` VALUES  ('Bela Vista','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',0,2365770,6885,-5794,316,-11,-14,1.13306,0,1,63,20),
 ('Kor Vella','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',0,2955427,-3400,3397,75,-11,-14,1.13306,0,1,64,20),
 ('Kor Vella','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',0,0,-3193,2799,31,0,0,0,0.983168,-0.182703,65,20),
 ('Keren','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',5,0,1890,2725,1.13306,0,0,0,0,1,66,20),
 ('Keren','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',5,1650535,1825,2625,13,-11,-12.5,1.13306,0,1,67,20),
 ('Theed','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',5,1692075,-5467,4089,7,-11,-13,1,0,1,68,20),
 ('Moenia','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',5,1717535,4710,-4997,4,-11.0386,-13.0273,1.13306,0.0021525,0.999998,69,20),
 ('Moenia','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',5,0,4800,-4734,4.17,0,0,0,0.968234,0.250046,70,20);
INSERT INTO `swgemu`.`trainers` VALUES  ('Kaadara','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',5,0,5174.04,6639.92,-192,0,0,0,0.0312334,0.999512,71,20),
 ('Kaadara','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',5,1741462,5099,6792,-190,-11.887,-11.53443,1.13306,-0.00609633,0.999981,72,20),
 ('Keren','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',5,0,1537,2757,25,0,0,0,0,1,73,20),
 ('Narmle','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',6,0,-5212,-2449,80,0,0,0,0.999259,0.038503,74,20),
 ('Restuss','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',6,4635691,5457,5814,81,-11,-14,1,0,1,75,20),
 ('Rori','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',6,0,5335.31,5530.48,80,0,0,0,-0.349679,0.93687,76,20),
 ('Dearic','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',7,3175377,551,-2886,7,-11.1898,-13.9613,1.13306,-0.0227979,0.99974,77,20),
 ('Nashal','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',7,4265407,4286,5395,11,-11.0245,-13.1401,1.13306,0.0448135,0.998955,78,20);
INSERT INTO `swgemu`.`trainers` VALUES  ('Bestine','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',8,1028553,-1266,-3596,13,-11.0089,-13.2203,1.13306,-0.00402526,0.999992,79,20),
 ('Bestine','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',8,0,-1278.75,-3540.47,12,0,0,0,0.637134,0.770753,80,20),
 ('Mos Eisley','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',8,1189639,3460,-4658,6,-10.982,-13.9557,1.13306,0.997906,0.0646797,81,20),
 ('Mos Eisley','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',8,0,3496,-4765,5,0,0,0,0.7,0.7,82,20),
 ('Mos Entha','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',8,1153566,1387,3043,8,-10.88,-13.1066,1.13306,0.0234174,0.999726,83,20),
 ('Mos Entha','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',8,0,1310,3088,7,0,0,0,0,1,84,20),
 ('Mos Entha','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',8,0,1741,3117,7,0,0,0,0,1,85,20);
INSERT INTO `swgemu`.`trainers` VALUES  ('Mos Espa','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',8,1255994,-3029,2431,6,-11.2511,-13.1651,1.13306,-0.0317022,0.999497,86,20),
 ('Mos Espa ','a Brawler trainer','trainer_brawler','combat_brawler','BD157CF4','6602D463','2F0FB3EE',8,0,-2933,2125,5,0,0,0,0.749761,0.661708,87,20),
 ('Keren','a Bounty Hunter trainer','trainer_bountyhunter','combat_bountyhunter','24DB82C8','FFCC2A5F','B6C14DD2',5,0,2087,2575,0,0,0,0,0,0,88,0),
 ('Tyrena','a Bounty Hunter trainer','trainer_bountyhunter','combat_bountyhunter','24DB82C8','FFCC2A5F','B6C14DD2',0,0,-5130,-2302,0,0,0,0,0,0,89,0),
 ('Mos Eisley','a Bounty Hunter trainer','trainer_bountyhunter','combat_bountyhunter','24DB82C8','FFCC2A5F','B6C14DD2',8,0,3357.4,-4840.42,5,0,0,0,0.795537,-0.605904,90,0),
 ('Wayfar','a Bounty Hunter trainer','trainer_bountyhunter','combat_bountyhunter','24DB82C8','FFCC2A5F','B6C14DD2',8,1134561,-5151,-6587,74,19,-17,-0.894,0,1,91,0),
 ('Narmle','a Bounty Hunter trainer','trainer_bountyhunter','combat_bountyhunter','24DB82C8','FFCC2A5F','B6C14DD2',6,0,-5232,-2241,80,0,0,0,0,1,92,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Tyrena','a Carbine trainer','trainer_carbine','combat_carbine','CFC43107','14D39990','5DDEFE1D',0,0,-5225,-2488,0,0,0,0,0,0,93,0),
 ('Mos Eisley','a Carbine trainer','trainer_carbine','combat_carbine','CFC43107','14D39990','5DDEFE1D',8,0,3534,-4695,0,0,0,0,0,0,94,0),
 ('Mos Entha','a Carbine trainer','trainer_carbine','combat_carbine','CFC43107','14D39990','5DDEFE1D',8,0,1158,3110,0,0,0,0,0,0,95,0),
 ('Narmle','a Carbine trainer','trainer_carbine','combat_carbine','CFC43107','14D39990','5DDEFE1D',6,0,-5138,-2514,0,0,0,0,0,0,96,0),
 ('Keren','a Carbine trainer','trainer_carbine','combat_carbine','CFC43107','14D39990','5DDEFE1D',5,0,1265.08,2677.88,13,0,0,0,0.0768892,0.99704,97,0),
 ('Dearic','a Carbine trainer','trainer_carbine','combat_carbine','CFC43107','14D39990','5DDEFE1D',7,0,583,-2873,6,0,0,0,0.869158,0.494534,98,0),
 ('Rebel Outpost','a Carbine trainer','trainer_carbine','combat_carbine','CFC43107','14D39990','5DDEFE1D',6,0,3627,-6433,96,0,0,0,-0.697913,0.716183,99,0),
 ('Keren','a Chef trainer','trainer_chef','crafting_chef','2E1A6C48','5489F466','008C0C6E',5,0,1840,2672,0,0,0,0,0,0,100,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Moenia','a Chef trainer','trainer_chef','crafting_chef','2E1A6C48','5489F466','008C0C6E',5,0,4942,-4837,0,0,0,0,0,0,101,0),
 ('Doaba Guerfel','a Chef trainer','trainer_chef','crafting_chef','2E1A6C48','5489F466','008C0C6E',0,0,3070,5260,0,0,0,0,0,0,102,0),
 ('Restuss','a Chef trainer','trainer_chef','crafting_chef','2E1A6C48','5489F466','008C0C6E',6,0,5181,5668,0,0,0,0,0,0,103,0),
 ('Theed','a Chef trainer','trainer_chef','crafting_chef','2E1A6C48','5489F466','008C0C6E',5,0,-4877,4065,6,0,0,0,0,1,104,0),
 ('Nashal','a Chef trainer','trainer_chef','crafting_chef','2E1A6C48','5489F466','008C0C6E',7,0,4283,5172,2,0,0,0,0,1,105,0),
 ('Kor Vella','a Chef trainer','trainer_chef','crafting_chef','2E1A6C48','5489F466','008C0C6E',0,0,-3147,2792,31,0,0,0,0,1,106,0),
 ('Bestine','a Chef trainer','trainer_chef','crafting_chef','2E1A6C48','5489F466','008C0C6E',8,1223850,-1175,-3681,13,24,7,1.3,0.948,-0.317,107,0),
 ('Moenia','a Squad Leader trainer','trainer_squadleader','outdoors_squadleader','94ECB00F','4FFB1898','06F67F15',5,0,4701,-4939,3.75,0,0,0,0,1,108,0),
 ('Bestine','a Squad Leader trainer','trainer_squadleader','outdoors_squadleader','94ECB00F','4FFB1898','06F67F15',8,0,-1019,-3532,0,0,0,0,0,0,109,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Dearic','a Squad Leader trainer','trainer_squadleader','outdoors_squadleader','94ECB00F','4FFB1898','06F67F15',7,0,590.114,-2934,6,0,0,0,0,1,110,0),
 ('Dearic','a Pikeman trainer','trainer_polearm','combat_polearm','E22AC202','393D6A95','70300D18',7,0,522,-2934,0,0,0,0,0,0,111,0),
 ('Narmle','a Pikeman trainer','trainer_polearm','combat_polearm','E22AC202','393D6A95','70300D18',6,0,-5278,-2328,0,0,0,0,0,0,112,0),
 ('Theed','a Pikeman trainer','trainer_polearm','combat_polearm','E22AC202','393D6A95','70300D18',5,0,-5375.06,4310.92,6,0,0,0,0.670499,0.74191,113,0),
 ('Kor Vella','a Pikeman trainer','trainer_polearm','combat_polearm','E22AC202','393D6A95','70300D18',0,0,-3412,3084,86,0,0,0,0,1,114,0),
 ('Mos Espa','a Pikeman trainer','trainer_polearm','combat_polearm','E22AC202','393D6A95','70300D18',8,0,-2931,2386,5,0,0,0,0,1,115,0),
 ('Keren','a Pistoleer trainer','trainer_pistol','combat_pistol','1F743053','C46398C4','8D6EFF49',5,0,1253,2686,0,0,0,0,0,0,116,0),
 ('Tyrena','a Pistoleer trainer','trainer_pistol','combat_pistol','1F743053','C46398C4','8D6EFF49',0,0,-5220,-2488,0,0,0,0,0,0,117,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Narmle','a Pistoleer trainer','trainer_pistol','combat_pistol','1F743053','C46398C4','8D6EFF49',6,0,-5240,-2454,0,0,0,0,0,0,118,0),
 ('Dearic','a Pistoleer trainer','trainer_pistol','combat_pistol','1F743053','C46398C4','8D6EFF49',7,0,583,-2871,6,0,0,0,0.862615,0.505861,119,0),
 ('Mos Eisley','a Pistoleer trainer','trainer_pistol','combat_pistol','1F743053','C46398C4','8D6EFF49',8,0,3358,-4837,5,0,0,0,0,1,120,0),
 ('Keren','an Image Designer trainer','trainer_imagedesigner','social_imagedesigner','D29F9084','09883813','40855F9E',5,4045384,1708,2465,14,-20.97,74.23,2.1287,1,0,121,0),
 ('Keren','an Image Designer trainer','trainer_imagedesigner','social_imagedesigner','D29F9084','09883813','40855F9E',5,0,1253,2711,13,0,0,0,0,1,122,0),
 ('Theed','an Image Designer trainer','trainer_imagedesigner','social_imagedesigner','D29F9084','09883813','40855F9E',5,5475488,-5815,4255,8,-22.9,74.7,2.1287,0.871,0.491,123,0),
 ('Kaadara','an Image Designer trainer','trainer_imagedesigner','social_imagedesigner','D29F9084','09883813','40855F9E',5,4105619,5399,6786,-189,-21.662,75.0346,2.12878,0.992776,0.119984,124,0),
 ('Dee\'ja Peak','an Image Designer trainer','trainer_imagedesigner','social_imagedesigner','D29F9084','09883813','40855F9E',5,2725361,4856,-1494,362,-22.2396,72.4933,2.12878,0.999964,-0.00850745,125,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Nashal','an Image Designer trainer','trainer_imagedesigner','social_imagedesigner','D29F9084','09883813','40855F9E',7,0,4346,5054,0,0,0,0,0,0,126,0),
 ('Dearic','an Image Designer trainer','trainer_imagedesigner','social_imagedesigner','D29F9084','09883813','40855F9E',7,3175573,518,-3076,8,-21.180973,73.4621,2.12878,0.999869,-0.0168002,127,0),
 ('Narmle','an Image Designer trainer','trainer_imagedesigner','social_imagedesigner','D29F9084','09883813','40855F9E',6,4635404,-5050,-2261,82,-21.5126,74.0536,2.12878,0.999967,-0.00813125,128,0),
 ('Restuss','an Image Designer trainer','trainer_imagedesigner','social_imagedesigner','D29F9084','09883813','40855F9E',6,0,5255,5850,0,0,0,0,0,0,129,0),
 ('Restuss','an Image Designer trainer','trainer_imagedesigner','social_imagedesigner','D29F9084','09883813','40855F9E',6,4635755,5489,5542,82,-22.3141,73.1359,2.12878,0.999667,-0.0257992,130,0),
 ('Coronet','an Image Designer trainer','trainer_imagedesigner','social_imagedesigner','D29F9084','09883813','40855F9E',0,2365400,-187,-4222,30,-21.4483,74.4461,2.12878,0.998887,-0.0471637,131,0),
 ('Tyrena','an Image Designer trainer','trainer_imagedesigner','social_imagedesigner','D29F9084','09883813','40855F9E',0,2365437,-5661,-2649,23,-21.8004,74.6487,2.12878,0.999478,-0.0322927,132,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Doaba Guerfel','an Image Designer trainer','trainer_imagedesigner','social_imagedesigner','D29F9084','09883813','40855F9E',0,4395403,3470,5433,310,-2.51106,70.8023,2.12878,-0.0149958,0.999888,133,0),
 ('Mos Entha','an Image Designer trainer','trainer_imagedesigner','social_imagedesigner','D29F9084','09883813','40855F9E',8,1153604,1498,3318,9,-21.3524,74.1456,2.12878,0.99039,0.138304,134,0),
 ('Mos Eisley','an Image Designer trainer','trainer_imagedesigner','social_imagedesigner','D29F9084','09883813','40855F9E',8,1105854,3217,-4735,7,-20.9956,73.874,2.12878,0.999294,0.0375812,135,0),
 ('Kaadara','a Ranger trainer','trainer_ranger','outdoors_ranger','AB1511B9','7002B92E','390FDEA3',5,0,5279,6594,0,0,0,0,0,0,136,0),
 ('Nashal','a Ranger trainer','trainer_ranger','outdoors_ranger','AB1511B9','7002B92E','390FDEA3',7,0,4234,5262,0,0,0,0,0,0,137,0),
 ('Coronet','a Ranger trainer','trainer_ranger','outdoors_ranger','AB1511B9','7002B92E','390FDEA3',0,0,-505,-4633,0,0,0,0,0,0,138,0),
 ('Narmle','a Ranger trainer','trainer_ranger','outdoors_ranger','AB1511B9','7002B92E','390FDEA3',6,0,-5167,-2535,0,0,0,0,0,0,139,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Mos Entha','a Ranger trainer','trainer_ranger','outdoors_ranger','AB1511B9','7002B92E','390FDEA3',8,0,1240,3356,7,0,0,0,0,1,140,0),
 ('Nashal','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',7,4265404,4304,5397,11,-12.6782,4.78809,1.13306,0.956145,0.292894,141,22),
 ('Nashal','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',7,0,4373.71,5302.45,2,0,0,0,0.703476,0.710719,142,22),
 ('Dearic','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',7,0,700,-2911,0,0,0,0,0,0,143,22),
 ('Dearic','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',7,3175374,553,-2904,7,-13.23,4.84733,1.13306,0.979116,0.203302,144,22),
 ('Kaadara','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',5,0,5192.38,6614.09,-192,0,0,0,0.0459989,0.998941,145,22),
 ('Kaadara','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',5,1741459,5110,6780,-190,-10.8899,4.89649,1.13306,0.978053,-0.208355,146,22),
 ('Keren','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',5,0,1512.27,2754.94,25,0,0,0,0.822118,0.569317,147,22);
INSERT INTO `swgemu`.`trainers` VALUES  ('Keren','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',5,1650532,1840,2626,13,-12.0327,4.62955,1.13306,0.999938,0.0111458,148,22),
 ('Keren','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',5,0,1842.37,2709.61,12,0,0,0,0.920853,0.389909,149,22),
 ('Moenia','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',5,0,4836.08,-4703.96,4.17,0,0,0,0.734163,0.678973,150,22),
 ('Moenia','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',5,1717532,4710,-4979,4,-11.303,4.63738,1.13306,0.986202,-0.165548,151,22),
 ('Theed','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',5,0,-4909.36,4025.86,6,0,0,0,-0.0959236,0.995389,152,22),
 ('Theed','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',5,1692072,-5470,4106,7,-14.0781,3.79797,1.13306,0.945726,0.324966,153,22),
 ('Theed','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',5,0,-5986.5,4232.79,6,0,0,0,0.790587,0.61235,154,22);
INSERT INTO `swgemu`.`trainers` VALUES  ('Theed','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',5,0,-4796,4103,6,0,0,0,0.8,-0.5,155,22),
 ('Mos Eisley','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',8,0,3519.76,-4786.9,5,0,0,0,0.620091,0.78453,156,22),
 ('Mos Eisley','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',8,1189636,3475,-4669,6,-10.559,4.83872,1.13306,0.978152,-0.207893,157,22),
 ('Mos Entha','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',8,0,1303,3199,0,0,0,0,0,0,158,22),
 ('Mos Entha','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',8,1153563,1389,3025,8,-11.8112,4.97548,1.13306,0.999683,-0.0251849,159,22),
 ('Mos Espa','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',8,1255991,-3012,2437,6,-13.0834,5.45675,1.13306,0.998576,0.0533543,160,22),
 ('Mos Espa','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',8,0,-2912.86,2106.67,5,0,0,0,-0.378736,0.0533543,161,22),
 ('Bestine','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',8,1028550,-254,-3582,13,-11.0016,5.08662,1.13306,0.998002,-0.0631855,162,22);
INSERT INTO `swgemu`.`trainers` VALUES  ('Bestine','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',8,0,-1295.83,-3563.27,12,0,0,0,0.429229,0.903196,163,22),
 ('Wayfar','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',8,0,-5051.46,-6629.48,75,0,0,0,-0.0610823,0.998133,164,22),
 ('Narmle','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',6,0,-5211,-2925,0,0,0,0,0,0,165,22),
 ('Narmle','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',6,0,-4951.32,-2373.68,79.9841,0,0,0,0.857974,0.513693,166,22),
 ('Restuss','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',6,0,5371,5539,0,0,0,0,0,0,167,22),
 ('Restuss','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',6,4635688,5458,5796,81,-12.5744,4.79458,1.13306,1,0,168,22),
 ('Coronet','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',0,0,-169.45,-4712.58,28,0,0,0,0.919306,0.393544,169,22),
 ('Coronet','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',0,1855505,-254,-4378,29,-12,5.5,1.13306,1,0,170,22);
INSERT INTO `swgemu`.`trainers` VALUES  ('Doaba Guerfel','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',0,3075358,3198,5232,301,-12,5.5,1.13306,1,0,171,22),
 ('Doaba Guerfel','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',0,0,3330.01,5512.46,308,0,0,0,0.977695,-0.210027,172,22),
 ('Kor Vella','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',0,2955424,-3399,3377,75,-12,5.5,1.13306,1,0,173,22),
 ('Kor Vella','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',0,0,-3164.42,2802.08,31,0,0,0,0.629216,0.77723,174,22),
 ('Tyrena','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',0,0,-5061.86,-2322.52,21,0,0,0,0.307687,0.951487,175,22),
 ('Tyrena','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',0,1935442,-5475,-2736,22,-12,5.5,1.13306,1,0,176,22),
 ('Bela Vistal','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',0,2365767,6866,-5795,316,-12,5.5,1.13306,1,0,177,22),
 ('Bela Vistal','a Scout trainer','trainer_scout','outdoors_scout','A0FDAE44','7BEA06D3','32E7615E',0,0,6737.85,-5491.3,315,0,0,0,-0.270338,0.962765,178,22);
INSERT INTO `swgemu`.`trainers` VALUES  ('Tyrena','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',0,2625355,-5229,-2556,20,16.7961,-10.1031,-0.894993,0.0251754,0.999683,179,0),
 ('Tyrena','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',0,2365436,-5640,-2610,23,17.6008,53.4279,2.12878,0.035964,0.999353,180,0),
 ('Coronet','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',0,2365399,-227,-4202,30,18.5885,53.9366,2.12869,0.00145099,0.999999,181,0),
 ('Kor Vella','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',0,3005398,-3464,3056,78,34.5107,1.79681,0.105,-0.703289,0.710905,182,0),
 ('Doaba Guerfel','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',0,4395403,3445,5423,310,17.7541,53.6699,2.12875,0.00976595,0.999952,183,0),
 ('Kadaara','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',5,4105618,5378,6747,-189,17.6312,53.7646,2.12874,0.0128075,0.999918,184,0),
 ('Theed','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',5,5475487,-5774,4235,8,18.2374,53.9343,2.12871,0.0536358,0.998561,185,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Deeja Peak','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',5,2725360,4875,-1454,362,17.8577,53.8179,2.12873,0.0201098,0.999798,186,0),
 ('Keren','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',5,0,1630.59,2574.54,12,0,0,0,0.760915,0.648852,187,0),
 ('Keren','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',5,4045383,1668,2486,14,18.188,53.8705,2.12871,0.0162866,0.999867,188,0),
 ('Moenia','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',5,0,4730,-4872,3.75,0,0,0,0.376299,0.926498,189,0),
 ('Narmle','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',6,4635403,-5010,-2282,82,18.0876,53.6634,2.12874,0.0108613,0.999941,190,0),
 ('Restuss','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',6,0,5437,5564,80.6,0,0,0,-0.690897,0.722954,191,0),
 ('Restuss','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',6,4635754,5449,5562,82,17.9253,53.5327,2.12876,-0.0275962,0.999619,192,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Dearic','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',7,3175572,558,-3096,8,18.0588,53.9528,2.12871,-0.00642406,0.999979,193,0),
 ('Mos Eisley','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',8,1105853,3256,-4714,7,17.9873,53.6448,2.12874,0.0101167,0.999949,194,0),
 ('Mos Entha','a Dancer trainer','trainer_dancer','social_dancer','1DE98D36','C6FE25A1','1C1B7A22',8,1153603,1479,3278,9,17.812,53.8433,2.12873,0.0114298,0.999935,195,0),
 ('Mos Entha','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',8,1153582,1301,3296,7,20,-5.6,0.26,0.685,0.7278,196,0),
 ('Mos Entha','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',8,0,1370,3164,0,0,0,0,0,0,197,0),
 ('Mos Entha','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',8,1153586,1345,3296,7,-24.6019,-3.960492,0.26,0.96081,-0.277208,198,0),
 ('Anchorhead','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',8,1213346,130,-5363,53,1.53792,6.82596,1.00421,0.737798,-0.675021,199,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Mos Espa','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',8,0,-3163.63,2122.39,5,0,0,0,-0.155701,0.987804,200,0),
 ('Mos Espa','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',8,4005424,-3143,2106,5,1.25736,0.598833,0.184067,0.995629,0.0933988,201,0),
 ('Mos Eisley','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',8,9655496,3523,-4748,5,-7.29914,0.0809266,0.184067,0.998728,-0.0504272,202,0),
 ('Kor Vella','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',0,3375392,-3810,3138,86,12,-1,0.184067,0,1,203,0),
 ('Vreni Island','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',0,7615446,-5309,-6403,4,-2.9,2.5,0.7,0.912038,0.410107,204,0),
 ('Coronet','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',0,1855535,-64,-4435,28,-25.2731,-5,0.26,-0.113595,0.993527,205,0),
 ('Doaba Guerfel','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',0,4345354,3272,5407,300,-3.95652,0.467273,0.184067,0.996825,0.0796281,206,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Tyrena','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',0,0,-5002,-2459,0,0,0,0,0,0,207,0),
 ('Tyrena','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',0,1935831,-4959,-2468,21,21,-5,0.26,0,1,208,0),
 ('Tyrena','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',0,1935835,-4992,-2499,21,-24.2179,-3.63691,0.26,0.990943,-0.134282,209,0),
 ('Nym\'s Stronghold','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',4,2745866,572,5109,12,22.1279,-6.11676,0.26,0.0715797,0.698308,210,0),
 ('Nym\'s Stronghold','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',4,2745870,585,5155,12,-25.366,-4.25289,0.26,0.669369,0.74293,211,0),
 ('Kaadara','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',5,0,5021,6787,-192,0,0,0,0.0153915,0.999882,212,0),
 ('Kaadara','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',5,1741443,5114,6660,-191,-24.4979,-4.7603,0.26,0.998163,-0.0605819,213,0),
 ('Kaadara','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',5,1741439,5884,6626,-191,21.4466,-2.96069,0.26,0.316259,0.948673,214,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Keren','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',5,0,1950,2645.86,19.25,0,0,0,0.76614,-0.642673,215,0),
 ('Keren','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',5,1661366,1954,2602,12,17.4,1,0.3,0.0745443,0.997218,216,0),
 ('Moenia','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',5,0,4887,-4899,0,0,0,0,0,0,217,0),
 ('Moenia','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',5,1717502,4937,-4933,4,19.6344,-4.81265,0.26,0.315352,0.948975,218,0),
 ('Moenia','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',5,1717506,4893,-4933,4,-25,-4,0.26,1,0,219,0),
 ('Theed','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',5,0,-5038,4146,0,0,0,0,0,0,220,0),
 ('Theed','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',5,1697360,-5005,4152,6,16.0979,-0.105232,0.26,0.73039,-0.68303,221,0),
 ('Narmle','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',6,4635420,-5146,-2206,80,20.5091,-6.05941,0.26,-0.104817,0.994491,222,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Narmle','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',6,0,-5104,-2249,0,0,0,0,0,0,223,0),
 ('Narmle','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',6,4635424,-5101,-2207,80,-25.5,-4,0.26,1,0,224,0),
 ('Restuss','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',6,4635732,5322,5595,80,-25,-3,0.26,1,0,225,0),
 ('Restuss','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',6,4635728,5276,5596,80,20.8797,-4.8809,0.26,0.387926,0.92169,226,0),
 ('Nashal','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',7,4265477,4503,5102,2,-1,-3,0.184,0.66,0.75,227,0),
 ('Nashal','a Doctor trainer','trainer_doctor','science_doctor','4F51A313','ADB5FA08','D48C63ED',7,0,4490,5182,2,0,0,0,-0.319118,0.947715,228,0),
 ('Mos Eisley','a Smuggler trainer','trainer_smuggler','combat_smuggler','0368D166','D87F79F1','91721E7C',8,0,3401,-4879,5,0,0,0,-0.323164,0.946343,229,0),
 ('Keren','a Smuggler trainer','trainer_smuggler','combat_smuggler','0368D166','D87F79F1','91721E7C',5,0,1362.94,2833.96,13,0,0,0,-0.654378,0.756167,230,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Keren','a Smuggler trainer','trainer_smuggler','combat_smuggler','0368D166','D87F79F1','91721E7C',5,0,1846,2772,12,0,0,0,0.27045,0.962734,231,0),
 ('Dearic','a Smuggler trainer','trainer_smuggler','combat_smuggler','0368D166','D87F79F1','91721E7C',7,0,167,-2892,6,0,0,0,0.749543,-0.661956,232,0),
 ('Restuss','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',6,0,5432.89,5569.12,80.6,0,0,0,-0.313928,0.949447,233,0),
 ('Restuss','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',6,4635754,5445,5552,82,21.6954,63.866,2.12795,0.0308312,0.999525,234,0),
 ('Narmle','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',6,4635403,-5007,-2272,82,21.5522,63.5137,2.12797,0,1,235,0),
 ('Keren','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',5,4045383,1665,2476,14,21.7887,63.5017,2.12809,-0.0232172,0.99973,236,0),
 ('Theed','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',5,5475487,-5770,4244,8,21.6399,63.523,2.12801,-0.00336892,0.999994,237,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Deeja Peak','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',5,2725360,4865,-1450,362,21.8956,63.5,2.12814,0.00310462,0.999995,238,0),
 ('Kaadara','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',5,4105618,5388,6743,-189,21.7817,63.5,2.12808,-0.00606572,0.999982,239,0),
 ('Coronet','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',0,2365399,-230,-4211,30,21.8947,63.5,2.12814,0.00366012,0.999993,240,0),
 ('Doaba Guerfel','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',0,4395403,3452,5415,310,22.0995,63.5054,2.12823,0.00346623,0.999994,241,0),
 ('Tyrena','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',0,0,-5067,-2296,21,0,0,0,0.981343,0.192266,242,0),
 ('Tyrena','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',0,2625355,-5215,-2545,20,21.1399,8.20648,-0.894993,0.866156,0.499774,243,0),
 ('Tyrena','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',0,2365436,-5650,-2605,23,21.9985,63.5,2.12818,-0.00183045,0.999998,244,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Vreni Island','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',0,0,-5408,-6260,24.7288,0,0,0,-0.419601,0.907709,245,0),
 ('Dearic','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',7,3175572,561,-3086,8,22.0619,63.5,2.12821,0.0074831,0.999972,246,0),
 ('Mos Eisley','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',8,0,3393,-4791,0,0,0,0,0,0,247,0),
 ('Mos Entha','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',8,0,1481,3267,7,0,0,0,0,1,248,0),
 ('Mos Espa','a Musician trainer','trainer_musician','social_musician','859A8CA5','5E8D2432','178043BF',8,0,-2882,2171,0,0,0,0,0,0,249,0),
 ('Doaba Guerfel','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',0,4345354,3277,5419,300,8.00847,5.47322,0.184067,0.688309,0.725418,250,0),
 ('Coronet','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',0,1855531,-116,-4445,28,26.676,5.41823,0.26,0.676775,0.73619,251,0),
 ('Coronet','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',0,0,-33.9759,-4435.08,28,0,0,0,0.73443,0.678685,252,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Tyrena','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',0,0,-4996.29,-2451.61,21,0,0,0,0.903421,0.428755,253,0),
 ('Tyrena','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',0,1935835,-4997,-2484,0,-17,10,0.26,1,0,254,0),
 ('Kaadara','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',5,1741443,5120,6643,-191,-16.368,11.0637,0.26,0.997311,0.0732851,255,0),
 ('Kaadara','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',5,0,1927,2729.93,12,0,0,0,0.74166,-0.670775,256,0),
 ('Keren','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',5,1661366,1958,2592,12,27.2188,5.37779,0.26,0.616074,0.787688,257,0),
 ('Keren','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',5,1661370,1962,2636,12,-17,9,0.26,1,0,258,0),
 ('Keren','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',5,1717502,4945,-4923,4,27.0188,5.47931,0.26,0.654783,0.755817,259,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Moenia','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',5,1717506,4901,-4918,4,-16.404,10.6808,0.26,0.997415,0.0718578,260,0),
 ('Moenia','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',5,1697364,-5023,4181,6,-16.4871,10.7738,0.26,0.999249,0.0387386,261,0),
 ('Theed','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',5,1697360,-4994,4149,6,26.5469,5.31169,0.26,0.707746,0.706467,262,0),
 ('Nashal','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',7,0,4389.18,5364.43,2,0,0,0,0.999637,0.0269525,263,0),
 ('Nashal','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',7,4265477,4509,5173,2,8.02653,5.45986,0.184067,0.683398,0.730046,264,0),
 ('Mos Eisley','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',8,9655496,3538,-4753,5,7.84086,5.40226,0.184067,0.645773,0.763529,265,0),
 ('Mos Entha','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',8,1153586,1338,3282,7,-16.4794,9.71928,0.26,0.98786,0.155345,266,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Mos Entha','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',8,1153582,1293,3283,7,28,6.3,0.26,0.9,-0.4,267,0),
 ('Mos Espa','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',8,4005424,-3138,2113,5,7.93319,5.54261,0.184067,0.679963,0.733246,268,0),
 ('Narmle','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',6,4635424,-5110,-2223,80,-16.4,10.9,0.26,1,0,269,0),
 ('Narmle','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',6,4635420,-5153,-2217,80,26.6041,5.45989,0.26,0.662055,0.749455,270,0),
 ('Restuss','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',6,4635728,5271,5586,80,26.6144,5.52845,0.26,0.66869,0.743541,271,0),
 ('Restuss','a Combat Medic trainer','trainer_combatmedic','science_combatmedic','5F29D54D','65F1206F','190FB91C',6,4635732,5314,5581,80,-16.3425,10.8489,0.26,0.994935,0.100523,272,0),
 ('Dee\'ja Peak','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',5,0,4980,-1425,0,0,0,0,1,0,273,23);
INSERT INTO `swgemu`.`trainers` VALUES  ('Dee\'ja Peak','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',5,0,4874,-1444,360.6,0,0,0,0,1,274,23),
 ('Kaadara','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',5,1741461,5090,6785,-190,0,-13,1.13306,0,1,275,23),
 ('Moenia','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',5,0,4794,-4730,4.17,0,0,0,0,1,276,23),
 ('Moenia','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',5,1717534,4721,-4997,4,0,-13,1.13306,0,1,277,23),
 ('Theed','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',5,0,-4674,3995,0,0,0,0,0,0,278,23),
 ('Theed','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',5,0,-5982,4254,0,0,0,0,0,0,279,23),
 ('Theed','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',5,0,-4863,4079,6,0,0,0,0,1,280,23),
 ('Theed','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',5,1692074,-5456,4089,7,0,-13,1.13306,0,1,281,23);
INSERT INTO `swgemu`.`trainers` VALUES  ('Keren','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',5,0,1538,2751,0,0,0,0,0,0,282,23),
 ('Keren','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',5,1650534,1823,2614,13,0,-13,0,0,1,283,23),
 ('Keren','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',5,0,1992,2515,0,0,0,0,1,0,284,23),
 ('Dearic','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',7,3175376,539,-2885,7,0,-15,1.133,0,1,285,23),
 ('Dearic','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',7,0,586,-2873,6,0,0,0,0,1,286,23),
 ('Nashal','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',7,0,4366,5384,2,0,0,0,0.7,-0.7,287,23),
 ('Bela Vistal','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',0,0,6770,-5714,0,0,0,0,0,0,288,23),
 ('Bela Vistal','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',0,2365769,6885.5,-5783.5,316,0,-14,1.13306,0,1,289,23);
INSERT INTO `swgemu`.`trainers` VALUES  ('Kor Vella','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',0,2955426,-3410.5,3397.5,75,0,-14,1.13306,0,1,290,23),
 ('Kor Vella','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',0,0,-3130,2791,0,0,0,0,0,0,291,23),
 ('Coronet','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',0,0,-165,-4746,28,0,0,0,0.717277,0.696708,292,23),
 ('Coronet','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',0,1855507,-274,-4390,29,0,-14,1.13306,0,1,293,23),
 ('Doaba Guerfel','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',0,3075360,3213,5250,301,0,-14,1.13306,0,1,294,23),
 ('Tyrena ','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',0,1935444,-5463,-2756,22,0,-14,1.13306,0,1,295,23),
 ('Bestine','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',8,0,-1272,-3538,0,0,0,0,1,0,296,23),
 ('Bestine','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',8,1028552,-1257,-3603,13,0,-13,1.13306,0,1,297,23);
INSERT INTO `swgemu`.`trainers` VALUES  ('Mos Eisley','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',8,0,3506,-4760,5,0,0,0,1,0,298,23),
 ('Mos Eisley','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',8,0,3552,-4710,5,0,0,0,1,-0.3,299,23),
 ('Mos Eisley','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',8,1189638,3455,-4668,6,0,-13,1.13306,0,1,300,23),
 ('Mos Entha','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',8,1153565,1376,3043,8,0,-13,0,0,1,301,23),
 ('Mos Entha','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',8,0,1321,3105,0,0,0,0,0,0,302,23),
 ('Mos Espa','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',8,1255993,-3027,2420,6,0,-13,1.13306,0,1,303,23),
 ('Mos Espa','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',8,0,-2931,2121,5,0,0,0,0.7,0.7,304,23),
 ('Narmle','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',6,4615374,-5199,-2442,81,0,-13,1.13306,0,1,305,23);
INSERT INTO `swgemu`.`trainers` VALUES  ('Restuss','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',6,4635690,5446,5813,81,0,-13,0,0,1,306,23),
 ('Restuss','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',6,0,5528,5641,80.7357,0,0,0,0.7,0.7,307,23),
 ('Rebel Outpost','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',6,4505601,3684,-6488,98,-2.5,3,2.01003,0.7,0.7,308,23),
 ('Kaadara','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',5,0,5182,6632,-192,0,0,0,0,1,309,23),
 ('Coronet','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',0,0,-35,-4372,0,0,0,0,0.7,-0.7,310,23),
 ('Doaba Guerfel','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',0,0,3338,5516,0,0,0,0,0,1,311,23),
 ('Tyrena','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',0,0,-5041,-2324,0,0,0,0,-0.7,0.7,312,23),
 ('Tyrena','a Marksman trainer','trainer_marksman','combat_marksman','46AE82E3','9DB92A74','D4B44DF9',0,0,-5249,-2306,21,0,0,0,1,0,313,23);
INSERT INTO `swgemu`.`trainers` VALUES  ('Moenia','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',5,0,4808,-4724,4.17,0,0,0,0,1,314,25),
 ('Moenia','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',5,1717506,4901,-4930,4,-17.2255,-1.2311,0.26,0.96553,0.26029,315,25),
 ('Moenia','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',5,1717502,4934,-4123,4,16.6671,5.91467,0.26,0.99975,0.0223254,316,25),
 ('Theed','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',5,1697360,-5004,4157,6,13.7645,4.7703,0.26,0.96395,0.26605,317,25),
 ('Theed','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',5,0,-4592,4125,6,0,0,0,0.94709,-0.32074,318,25),
 ('Theed','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',5,1697364,-5031,4172,6,-17.1613,-0.82884,0.26,0.994029,0.109115,319,25),
 ('Kaadara','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',5,1741443,5112,6650,-191,-16.43,0.33,0.26,0.998,0.057,320,25),
 ('Kaadara','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',5,1741439,5994,6624,-191,15.4875,6.2929,0.26,-0.1694,0.9855,321,25);
INSERT INTO `swgemu`.`trainers` VALUES  ('Karen','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',5,0,1982,2598,12,0,0,0,0,1,322,25),
 ('Keren','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',5,1661370,1954,2636,12,-16.956,1.559,0.26,-0.2213,0.9774,323,25),
 ('Keren','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',5,1661366,1956,2605,12,14.1386,3.567,0.26,0.8991,0.4377,324,25),
 ('Mos Entha','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',8,1153582,1307,3286,7,14.1436,4.6585,0.26,0.99626,-0.08629,325,25),
 ('Mos Entha','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',8,1153586,1338,3293,7,-17.0194,-1.8269,0.26,0.97629,0.2643,326,25),
 ('Mos Entha','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',8,0,1325,3148,7,0,0,0,0.7,-0.7,327,25),
 ('Mos Espa','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',8,0,-3158,2122,5,0,0,0,0.04266,0.99908,328,25),
 ('Mos Espa','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',8,0,-2931,2116,5,0,0,0,0.53889,0.84237,329,25);
INSERT INTO `swgemu`.`trainers` VALUES  ('Mos Eisley','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',8,0,3522,-4774,5,0,0,0,0.98418,-0.17712,330,25),
 ('Wayfar','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',8,1499420,-5123,-6615,76,-8.4035,8.19643,1.00421,0.82032,0.571892,331,25),
 ('Bestine','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',8,4005383,-1312,-3482,15.5,-8.7,0.1,0.2,0.7,0.7,332,25),
 ('Nym\'s Stronghold','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',4,2745870,585,5145,12,-16.0068,-2.42861,0.26,0.854309,0.519765,333,25),
 ('Narmle','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',6,4635420,-5139,-2217,80,13.545,5.01144,0.26,0.991878,0.127195,334,25),
 ('Narmle','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',6,4635424,-5109,-2212,80,-17.4597,0.00620247,0.26,0.031729,0.999496,335,25),
 ('Restuss','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',6,4635728,5284,5587,80,13.2069,4.92654,0.26,0.991233,0.132125,336,25);
INSERT INTO `swgemu`.`trainers` VALUES  ('Dearic','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',7,3305354,316,-3054,6,-1.8295,0.51949,0.184067,-0.688502,0.725234,337,25),
 ('Kor Vella','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',0,0,-3139,2792,31,0,0,0,0,1,338,25),
 ('Kor Vella','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',0,3375392,-3786,3131,86,-12.6494,2.16918,0.18406,0.82221,0.56917,339,25),
 ('Coronet','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',0,1855535,-72,-4439,28,-17.7359,-0.58142,0.26,0.92937,0.36913,340,25),
 ('Coronet','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',0,1855531,-104,-4444,28,14.2688,4.66124,0.26,0.983456,0.181149,341,25),
 ('Coronet','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',0,0,-33,-4422,28,0,0,0,0.58742,0.80917,342,25),
 ('Doaba Guerfel','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',0,0,3341,5517,308,0,0,0,-0.40101,0.91607,343,25),
 ('Tyrena','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',0,1935835,-4989,-2490,21,-15.9755,0.30427,0.26,0.13124,0.99135,344,25);
INSERT INTO `swgemu`.`trainers` VALUES  ('Tyrena','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',0,1935831,-4971,-2467,21,13.8906,3.8275,0.26,0.99968,-0.02512,345,25),
 ('Tyrena','a Medic trainer','trainer_medic','science_medic','F69E1717','2D89BF80','6484D80D',0,0,-5027,-2311,21,0,0,0,0.72954,-0.683928,346,25),
 ('Bela Vistal','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',0,2365799,6868.5,-5434.5,331,-12,5,1.1,1,0,347,0),
 ('Coronet','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',0,1855525,35,-4452,29,-12,5,1.1,1,0,348,0),
 ('Doaba Guerfel','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',0,3075411,3127,5285.5,301,-12,5,1.1,1,0,349,0),
 ('Kor Vella','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',0,2955399,-3696.5,3075,87,-12,5,1.1,1,0,350,0),
 ('Tyrena','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',0,0,-5118,-2337,21,0,0,0,0.908741,0.41736,351,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Tyrena','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',0,1935462,-5516,-2667,22,-12,5,1.1,1,0,352,0),
 ('Deeja Peak','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',5,0,4771,-1272,0,0,0,0,0,0,353,0),
 ('Deeja Peak','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',5,1685237,4746,-1275,331,-15,0,1.1,0.707,0.707,354,0),
 ('Kaadara','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',5,1741469,5140,6815,-190,-15,0,1.1,0.937155,-0.348914,355,0),
 ('Keren','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',5,0,1890,2767,0,0,0,0,0,0,356,0),
 ('Keren','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',5,1650542,1801,2565,13,-15,0,1.133,0.68,0.72,357,0),
 ('Moenia','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',5,1717554,4790,-5000,4,-15,0,1.113,0.68,0.72,358,0),
 ('Theed','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',5,1692092,-5467,3996,7,-15,0,1.1,0.707,0.707,359,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Dearic','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',7,0,351,-2875.9,6,0,0,0,-0.0205642,0.999789,360,0),
 ('Dearic','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',7,3175560,598,-3066,7,-12.427,3.69917,1.13306,0.988756,0.149535,361,0),
 ('Nashal','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',7,4265414,4273,5106,3,-12.3664,3.6764,1.13306,0.996777,0.0802227,362,0),
 ('Bestine','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',8,1028580,-1243,-3506,13,-12.8138,3.64955,1.13306,0.946147,0.0323737,363,0),
 ('Mos Eisley','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',8,1189577,3349,-4695,6,-12.2888,3.6161,1.13306,0.99684,0.0794398,364,0),
 ('Mos Entha','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',8,0,1247,3248,4,0,0,0,0.140535,0.990073,365,0),
 ('Mos Entha','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',8,1154182,1306,3392,8,-12.6959,3.59178,1.13306,0.973241,0.229786,366,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Mos Espa','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',8,1256020,-3070,2061,6,-12.5142,3.63893,1.13306,0.991316,0.131503,367,0),
 ('Narmle','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',6,4635412,-5026,-2417,81,-15,0,1.133,0.68,0.72,368,0),
 ('Narmle','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',6,0,-5248,-2358,80,0,0,0,0.311946,0.9501,369,0),
 ('Restuss','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',6,4635773,5373,5611,81,-12.491,3.55001,1.13306,0.979196,0.202916,370,0),
 ('Rebel Outpost','an Armorsmith trainer','trainer_armorsmith','crafting_armorsmith','0AE502D0','D1F2AA47','98FFCDCA',6,0,3676,-6419,94.2,0,0,0,0.479154,0.877731,371,0),
 ('Moenia','a Tailor trainer','trainer_tailor','crafting_tailor','072D76FE','DC3ADE69','9537B9E4',5,0,4858,-4799,0,0,0,0,0,0,372,0),
 ('Restuss','a Tailor trainer','trainer_tailor','crafting_tailor','072D76FE','DC3ADE69','9537B9E4',6,0,5209,5729,0,0,0,0,0,0,373,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Dearic','a Tailor trainer','trainer_tailor','crafting_tailor','072D76FE','DC3ADE69','9537B9E4',7,0,369,-2877,0,0,0,0,0,0,374,0),
 ('Bestine','a Tailor trainer','trainer_tailor','crafting_tailor','072D76FE','DC3ADE69','9537B9E4',8,0,-1348,-3677,0,0,0,0,0,0,375,0),
 ('Doaba Guerfel','a Tailor trainer','trainer_tailor','crafting_tailor','072D76FE','DC3ADE69','9537B9E4',0,0,3077,5251,300,0,0,0,0,1,376,0),
 ('Nashal','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',7,4265415,4299,5120,3,11,-14.5,1.133,0,1,377,0),
 ('Nashal','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',7,0,4220,5127,0,0,0,0,0.557713,0.830034,378,0),
 ('Dearic','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',7,3175561,627,-3062,7,11,-14.5,1.133,0,1,379,0),
 ('Dee\'ja Peak ','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',5,1685238,4720,-1261,331,11,-14.5,1.133,0,1,380,0),
 ('Keren','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',5,1650543,1775,2579,13,11,-14.5,1.133,0,1,381,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Kaadara','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',5,1741470,5111,0,-190,11,-14.5,1.133,0,1,382,0),
 ('Moenia','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',5,1717555,4816,-5014,4,11,-14.5,1.133,0,1,383,0),
 ('Moenia','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',5,0,4779,-4973,3.75,0,0,0,0,1,384,0),
 ('Theed','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',5,1692093,-5440,3982,7,11,-14.5,1.133,0,1,385,0),
 ('Theed','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',5,0,-4931,4020,0,0,0,0,0.332242,0.943194,386,0),
 ('Bela Vistal','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',0,2365800,6851.5,-5409.5,331,11,-14,1.13306,0,1,387,0),
 ('Coronet','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',0,1855526,54,-4429,29,11,-14,1.13306,0,1,388,0),
 ('Doaba Guefel','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',0,3075412,3098,5293,301,11,-14,1.13306,0,1,389,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Kor Vella','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',0,2955400,-3686,3047.5,87,11,-14,1.13306,0,1,390,0),
 ('Tyrena','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',0,1935463,-5535,-2690,22,11,-14,1.13306,0,1,391,0),
 ('Bestine','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',8,1028581,-1272,-3514,13,11,-14.5,1.133,0,1,392,0),
 ('Mos Eisley','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',8,1189578,3321,-4705,6,11,-14.5,1.133,0,1,393,0),
 ('Mos Entha','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',8,1154183,1288,3369,8,11,-14.5,1.133,0,1,394,0),
 ('Mos Espa','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',8,1256021,-3043,2050,6,11,-14.5,1.133,0,1,395,0),
 ('Mos Espa','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',8,0,-2872,2159,5,0,0,0,1,0,396,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Narmle','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',6,4635413,-4999,-2432,81,11,-14.5,1.133,0,1,397,0),
 ('Restuss','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',6,4635774,5396,5593,81,11,-14.5,1.133,0,1,398,0),
 ('Restuss','an Architect trainer','trainer_architect','crafting_architect','8CFF964D','57E83EDA','1EE55957',6,0,5510,5663,80,0,0,0,0.957,-0.29,399,0),
 ('Coronet','a Creature Handler trainer','trainer_creaturehandler','outdoors_creaturehandler','C0738D47','D6D1707D','7DDD078F',0,0,-55,-4566,28,0,0,0,0,1,400,0),
 ('Doaba Guerfel','a Creature Handler trainer','trainer_creaturehandler','outdoors_creaturehandler','C0738D47','D6D1707D','7DDD078F',0,0,3162,5191,300,0,0,0,0,1,401,0),
 ('Kaadara','a Creature Handler trainer','trainer_creaturehandler','outdoors_creaturehandler','C0738D47','D6D1707D','7DDD078F',5,0,5181,6806,-192,0,0,0,0,1,402,0),
 ('Mos Entha','a Creature Handler trainer','trainer_creaturehandler','outdoors_creaturehandler','C0738D47','D6D1707D','7DDD078F',8,0,1374,3262,7,0,0,0,1,0,403,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Mos Espa','a Creature Handler trainer','trainer_creaturehandler','outdoors_creaturehandler','C0738D47','D6D1707D','7DDD078F',8,0,-2994,2530,5,0,0,0,0.5,1,404,0),
 ('Restuss','a Creature Handler trainer','trainer_creaturehandler','outdoors_creaturehandler','C0738D47','D6D1707D','7DDD078F',6,0,5134,5749,80,0,0,0,1,0,405,0),
 ('Bela Vistal','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',0,2365947,6707,-5510.5,316,0,-14,1.13306,0,1,406,21),
 ('Bela Vistal','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',0,0,6755.99,-5655.01,314.994,0,0,0,0.712959,-0.701206,407,21),
 ('Coronet','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',0,1855517,-146,-4390,29,0,-14,1.13306,0,1,408,21),
 ('Coronet','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',0,0,-187,-4700,28,0,0,0,0.717733,0.696318,409,21),
 ('Doaba Guerfel','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',0,3055771,3160,5043,291,0,-14,1.13306,0,1,410,21);
INSERT INTO `swgemu`.`trainers` VALUES  ('Doaba Guerfel','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',0,0,3311,5530,308,0,0,0,0.664487,0.7473,411,21),
 ('Kor Vella','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',0,2955416,-3417.5,3170,79,0,-14,1.13306,0,1,412,21),
 ('Tyrena','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',0,0,-5081,-2307,21,0,0,0,0.919828,0.392321,413,21),
 ('Tyrena','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',0,0,-5300.07,-2383,21,0,0,0,0.999308,-0.0372055,414,21),
 ('Tyrena','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',0,1935454,-5417,-2756.5,22,0,-14,1.13306,0,1,415,21),
 ('Kaadara','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',5,1741510,5178,6691,-190,-0.031573,-14.1498,1.13306,0,1,416,21),
 ('Kaadara','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',5,0,5182,6686,-192,0,0,0,0.933277,0.359158,417,21),
 ('Keren','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',5,0,1522,2781,25,0,0,0,1,0,418,21);
INSERT INTO `swgemu`.`trainers` VALUES  ('Keren','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',5,1396874,1751,2614,13,0.0976721,-13.6995,1.13306,-0.00312865,0.999995,419,21),
 ('Keren','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',5,0,2003.71,2484.06,12,0,0,0,0.852886,-0.522097,420,21),
 ('Moenia','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',5,0,4823.13,-4705.34,4.17,0,0,0,-0.650473,0.75953,421,21),
 ('Moenia','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',5,1717546,4926,-4780,4,-0.0177415,-13.3088,1.13306,0.000709873,1,422,21),
 ('Theed','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',5,0,-4946,4131,6,0,0,0,0.933799,0.357798,423,21),
 ('Theed','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',5,1692084,-55369,4108,7,0.0417929,-13.5584,1.13306,0.0134915,0.999909,424,21),
 ('Theed','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',5,0,-5996.85,4287.56,6,0,0,0,0.566754,0.823887,425,21);
INSERT INTO `swgemu`.`trainers` VALUES  ('Narmle','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',6,0,-5160.97,-2325.27,80,0,0,0,0.931801,0.362969,426,21),
 ('Narmle','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',6,4615384,-5199,-2324,81,-0.124425,-13.6473,1.13306,0.0020789,0.999998,427,21),
 ('Restuss','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',6,4635664,5237,5688,81,-0.112948,-14.1468,1.13306,0,1,428,21),
 ('Restuss','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',6,0,5256,5600,80,0,0,0,-0.108968,0.994045,429,21),
 ('Dearic','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',7,3175386,539,-2885,7,-0.0376376,-13.9533,1.13306,0.00114352,0.999999,430,21),
 ('Dearic','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',7,0,500,-3043,6,0,0,0,0.0672449,0.997737,431,21),
 ('Nashal','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',7,0,4410,5309,2,0,0,0,0.698237,0.715866,432,21);
INSERT INTO `swgemu`.`trainers` VALUES  ('Nashal','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',7,4265396,4518,5230,3,0.0424266,-14.6324,1.13306,0.000896588,1,433,21),
 ('Bestine','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',8,1028562,-1167,-3491,13,-0.0507306,-13.747,1.13306,0.000118111,1,434,21),
 ('Bestine','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',8,0,-1266,-3559,12,0,0,0,0.916902,-0.399112,435,21),
 ('Mos Eisley','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',8,1279964,3447,-4702,6,-0.0585386,-13.9039,1.13306,-4.59887,1,436,21),
 ('Mos Eisley','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',8,0,3503,-4809,5,0,0,0,0.357844,0.933782,437,21),
 ('Mos Entha','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',8,0,1276.55,3153.11,7,0,0,0,0.984731,0.174081,438,21),
 ('Mos Entha','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',8,0,1324,3141,7,0,0,0,0.818581,-0.57439,439,21);
INSERT INTO `swgemu`.`trainers` VALUES  ('Mos Entha','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',8,0,1335,3487,7,0,0,0,0.940895,0.338699,440,21),
 ('Mos Entha','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',8,1153493,1561,3078,8,-0.0475945,-14.1102,1.13306,-0.00318113,0.999995,441,21),
 ('Mos Espa','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',8,1256011,-2826,1993,6,-0.0885271,-14.0283,1.13306,0.0149073,0.999889,442,21),
 ('Mos Espa','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',8,0,-2890,2142,5,0,0,0,-0.166686,0.98601,443,21),
 ('Wayfar','an Artisan trainer','trainer_artisan','crafting_artisan','00217BD7','DB36D340','923BB4CD',8,0,-5274,-6547,75,0,0,0,0.937074,0.349132,444,21),
 ('Bestine','a Politician trainer','trainer_industrialist','social_politician','52E49D58','89F335CF','C0FE5242',8,0,-1125,-3616,12.2,0,0,0,0.99121,0.1223,445,0),
 ('Narmle','a Politician trainer','trainer_industrialist','social_politician','52E49D58','89F335CF','C0FE5242',6,0,-5165,-2461,80,0,0,0,0.943042,0.332675,446,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Coronet','a Politician trainer','trainer_industrialist','social_politician','52E49D58','89F335CF','C0FE5242',0,0,-218,-4500,28,0,0,0,0.294557,0.955634,447,0),
 ('Dee\'ja Peak','a Politician trainer','trainer_industrialist','social_politician','52E49D58','89F335CF','C0FE5242',5,0,4702,-1368,330,0,0,0,0.884584,0.466381,448,0),
 ('Dee\'ja Peak','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',5,1685239,4733,-1267,331,-2.5,-8.4,1.13306,0.7,0.7,449,0),
 ('Kaadara','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',5,1741471,5125,6812,-190,-2.5,-8.4,1.13306,0.7,0.7,450,0),
 ('Keren','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',5,1650544,1799,2573,13,-2.5,-8.4,1.13306,0.7,0.7,451,0),
 ('Keren','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',5,0,1905,2767,0,0,0,0,0,0,452,0),
 ('Moenia','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',5,1717556,4802,-5008,4,-2.5,-8.4,1.13306,0.7,0.7,453,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Theed','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',5,1692094,0,0,0,-3.1,-8.2,1.1,0.7,0.7,454,0),
 ('Dearic','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',7,0,516,-2912,0,0,0,0,1,0,455,0),
 ('Dearic','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',7,3175562,614,-3067,7,-2.5,-8.4,1.13306,0.7,0.7,456,0),
 ('Nashal','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',7,4265416,4288,5110,3,-2.5,-8.4,1.13306,0.7,0.7,457,0),
 ('Narmle','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',6,4635414,-5013,-2426,81,-2.5,-8.4,1.13306,0.7,0.7,458,0),
 ('Narmle','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',6,0,-5274,-2424,0,0,0,0,0,0,459,0),
 ('Restuss','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',6,4635775,5383,5599,81,-2.5,-8.4,1.13306,0.7,0.7,460,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Rebel Outpost','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',6,0,3681,-6420,0,0,0,0,0,0,461,0),
 ('Bela Vistal','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',0,2365801,6862,-5418,331,-2.5,-8.4,1.13306,0.7,0.7,462,0),
 ('Coronet','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',0,0,47,-4442,0,0,0,0,0,0,463,0),
 ('Doaba Guerfel','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',0,3075413,3112,5293,301,-2.5,-8.4,1.13306,0.7,0.7,464,0),
 ('Kor Vella','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',0,2955401,-3694,3058,87,-2.5,-8.4,1.13306,0.7,0.7,465,0),
 ('Tyrena','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',0,0,-5106,-2324,0,0,0,0,0,0,466,0),
 ('Tyrena','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',0,1935464,-5529,-2676,22,-2.5,-8.4,1.13306,0.7,0.7,467,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Mos Entha','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',8,0,1210,3273,7.4,0,0,0,0.996437,0.084394,468,0),
 ('Mos Entha','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',8,0,1394,3447,7,0,0,0,0.738336,0.674433,469,0),
 ('Mos Entha','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',8,1154184,1294,3383,8,-3.1,-8.4,1.1,0.738336,0.674433,470,0),
 ('Mos Espa','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',8,1256022,-3058,2052,6,-2.95975,-8.77207,1.13306,0.815981,0.578078,471,0),
 ('Mos Espa','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',8,0,-2869,2146,5,0,0,0,0.0656768,0.997841,472,0),
 ('Mos Eisley','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',8,1189579,3334,-4696,6,-2.87328,-8.72939,1.13306,0.872882,0.48793,473,0),
 ('Bestine','a Weaponsmith trainer','trainer_weaponsmith','crafting_weaponsmith','60894C2C','BB9EE4BB','F2938336',8,1028582,-1258,-3506,13,-3,-8.3,1.13306,0.7,0.7,474,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Keren','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',5,1650545,1797,2577,13,-11,-13,1.13306,0,1,475,0),
 ('Theed','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',5,1692095,-5462,3983,7,-11,-13,1.13306,0,1,476,0),
 ('Moenia','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',5,1717557,4793,-5014,4,-11.5102,-13.7835,1.13306,0.0206685,0.999786,477,0),
 ('Kaadara','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',5,1741472,5127,6822,-190,-10.8596,-14.4116,1.13306,0.00522962,0.999986,478,0),
 ('Dee\'ja Peak','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',5,1685240,4742,-1261,331,-11.3655,-13.793,1.13306,0.884445,-0.466643,479,0),
 ('Tyrena','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',0,1935465,3118,5302,301,-11,-14,1.13306,0,1,480,0),
 ('Kor Vella','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',0,2955402,-3705,3058,87,-11,-14,1.13306,0,1,481,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Coronet','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',0,1855528,54,-4451,29,-11,-14,1.13306,0,1,482,0),
 ('Bela Vistal','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',0,2365802,6873,-5416,331,-11,-14,1.13306,0,1,483,0),
 ('Doaba Guerfel','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',0,3075414,3118,5302,301,-11,-14,1.13306,0,1,484,0),
 ('Bestine','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',8,1028583,-1257,-3497,13,-11.6346,-13.252,1.13306,0.019427,0.999811,485,0),
 ('Mos Entha','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',8,1154185,1289,3391,8,-11.2719,-13.4562,1.13306,-0.00121323,0.999999,486,0),
 ('Mos Espa','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',8,1256023,-3065,2046,6,-11.5362,-12.6351,1.13306,0.012226,0.999925,487,0),
 ('Mos Eisley','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',8,1189580,3334,-4687,6,-10.9183,-14.2845,1.13306,-0.0457645,0.998952,488,0);
INSERT INTO `swgemu`.`trainers` VALUES  ('Dearic','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',7,3175563,611,-3077,7,-11.7587,-13.3207,1.13306,0.0581525,0.998308,489,0),
 ('Nashal','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',7,4265417,4289,5100,3,-11.088,-14.0044,1.13306,-0.00650418,0.999979,490,0),
 ('Restuss','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',6,4635776,5374,5594,81,-11.4803,-13.6866,1.13306,-0.0387217,0.99925,491,0),
 ('Narmle','a Droid Engineer trainer','trainer_droidengineer','crafting_droidengineer','3B94F411','244434C0','38C2CC11',6,4635415,-5121,-2430,81,-10.6439,-12.5741,1.13306,-0.0719766,0.997406,492,0),
 ('Bela Vistal','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',0,0,6829,-5429,330,0,0,0,0.999286,-0.0377764,493,24),
 ('Doaba Guerfel','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',0,4395403,3457,5403,310,30.358,73.5895,2.12878,0.737371,-0.675488,494,24),
 ('Doaba Guerfel','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',0,0,3305,5525,308,0,0,0,0.967509,0.252836,495,24);
INSERT INTO `swgemu`.`trainers` VALUES  ('Kor Vella','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',0,0,-3152,2807,31,0,0,0,0.999826,0.0186444,496,24),
 ('Kor Vella','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',0,3005399,-3460,3067,77,26.1909,10.2549,-0.894994,0.766435,-0.642322,497,24),
 ('Tyrena','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',0,0,-5661,-2599.57,21.6,0,0,0,-0.122204,0.992505,498,24),
 ('Tyrena','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',0,2625358,-5243,-2557,20,6.15345,-19.3905,-0.894992,0.00181555,0.999998,499,24),
 ('Tyrena','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',0,0,-5062,-2291,21,0,0,0,0.882297,0.470693,500,24),
 ('Vreni Island','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',0,3005697,-5190,-6401,3,22.0446,11.7787,-0.894993,0.996665,-0.0816027,501,24),
 ('Coronet','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',0,0,-173,-4739,28,0,0,0,0,1,502,24);
INSERT INTO `swgemu`.`trainers` VALUES  ('Coronet','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',0,0,-228,-4118,28.6,0,0,0,0,1,503,24),
 ('Kaadara','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',5,0,5209.69,6661.65,-192,0,0,0,0.783581,-0.621289,504,24),
 ('Keren','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',5,0,1772.77,2744.98,12,0,0,0,0.999915,0.013024,505,24),
 ('Keren','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',5,4045383,1657,2465,14,29.6396,74.0291,2.12878,0.708765,-0.705445,506,24),
 ('Moenia','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',5,0,4846,-4658,4.17,0,0,0,0.777062,-0.629424,507,24),
 ('Theed','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',5,5475487,-5764,4254,8,28.3235,73.5353,2.12854,0.708389,0.705822,508,24),
 ('Narmle','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',6,4635403,-4999,-2262,82,29.5159,73.6413,2.12878,-0.697109,0.716966,509,24);
INSERT INTO `swgemu`.`trainers` VALUES  ('Narmle','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',6,0,-5078,-2354,80,0,0,0,0.957408,0.288739,510,24),
 ('Restuss','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',6,4635754,5437,5542,82,30.0595,73.1945,2.12878,-0.618294,0.785947,511,24),
 ('Restuss','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',6,0,5433,5558,80.6,0,0,0,0.718484,-0.695543,512,24),
 ('Dearic','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',7,3175572,569,-3076,8,29.7003,73.0836,2.12878,-0.697745,0.716347,513,24),
 ('Nashal','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',7,0,4366,5350,2,0,0,0,0.761549,-0.648109,514,24),
 ('Nashal','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',7,4265375,4308,5329,1,23.5446,11.6472,-0.894993,0.99854,0.05402,515,24),
 ('Bestine','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',8,0,-1266,-3626,12,0,0,0,-0.192217,0.981353,516,24);
INSERT INTO `swgemu`.`trainers` VALUES  ('Mos Entha','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',8,1153603,1499,3266,9,29.9638,73.0406,2.12878,-0.703631,0.716565,517,24),
 ('Mos Entha','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',8,0,1287,3163,7,0,0,0,0.676311,0.736616,518,24),
 ('Mos Espa','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',8,0,-2889,2178,5,0,0,0,0.986429,0.164186,519,24),
 ('Mos Eisley','an Entertainer trainer','trainer_entertainer','social_entertainer','073354DE','61B3DB1E','EA2F0CEB',8,0,3477.89,-4791.6,5,0,0,0,0.952414,-0.304806,520,24),
 ('Rori','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',6,4635772,5397,5613,81,11.6338,5.69637,1.13306,0.999642,0.0267526,521,0),
 ('Bela Vistal','a Merchant trainer','trainer_merchant','crafting_merchant','D717AE2E','0C0006B9','450D6134',0,2365798,6845,-5428,331,12,6,1.13306,1,0,522,0);
UNLOCK TABLES;
/*!40000 ALTER TABLE `trainers` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
