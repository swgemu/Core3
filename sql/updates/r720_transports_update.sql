-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.0.32-Debian_7etch6-log


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

DROP TABLE IF EXISTS `swgemu`.`shuttles`;

--
-- Definition of table `swgemu`.`ticket_collectors`
--

DROP TABLE IF EXISTS `swgemu`.`ticket_collectors`;
CREATE TABLE  `swgemu`.`ticket_collectors` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `transport_id` int(11) NOT NULL,
  `parent` bigint(20) unsigned NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `dir_y` float NOT NULL,
  `dir_w` float NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `SECONDARY` (`transport_id`)
) ENGINE=MyISAM AUTO_INCREMENT=43 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `swgemu`.`ticket_collectors`
--

/*!40000 ALTER TABLE `ticket_collectors` DISABLE KEYS */;
LOCK TABLES `ticket_collectors` WRITE;
INSERT INTO `swgemu`.`ticket_collectors` VALUES  (1,1,0,6938,-5528,220,-0.64,0.8),
 (2,2,0,6637,-5931,330,0.75,0.8),
 (3,3,0,-338,-4634,28,1,0),
 (4,4,0,-34.2,-4402,28,1,0),
 (5,5,0,3078.5,4984.5,280.6,0.75,0.8),
 (6,6,0,-3783.5,3240.5,86.6,1,0),
 (7,7,0,-4992,-2354,21.6,0,0.8),
 (8,8,0,-5607,-2799,21.6,0.75,0.8),
 (9,9,0,-5560,-6053,16.6,1,0),
 (10,10,0,1589,-6410.4,11,0,1),
 (11,11,0,-4229,-2355.5,10,1,0),
 (12,12,0,-644,2488,10,0.71,0.69),
 (13,13,0,-68.9,-1578,25.086,1,0),
 (14,14,0,598,3095,13.1256,1,0),
 (15,15,0,3222,-3493,31,0,1),
 (16,16,0,-970,1563,80,1,0),
 (17,17,0,459,5503,16.1,1,0),
 (18,18,0,5339,-1567,327.7,-0.71,0.7),
 (19,19,0,5134,6616.4,-191.4,0.42,-0.83),
 (20,20,0,2028,2534,19.7,-0.71,0.7),
 (21,21,0,1558,2845,25.7,1,0),
 (22,22,0,-5487,-13,-149.4,-0.71,0.7),
 (23,23,0,4968.6,-4883.7,4.4,-0.71,0.7),
 (24,24,0,-5863,4163,6.8,0.72,0.69),
 (25,25,0,-5402,4315,6.8,0,1),
 (26,26,0,-5004.5,4086,6.6,-0.94,0.38),
 (27,27,0,-5256.4,-2150.4,81.3,0.92,-0.38),
 (28,28,0,3668,-6409,103,1,0),
 (29,29,0,5205,5797,80.7,1,0);
INSERT INTO `swgemu`.`ticket_collectors` VALUES  (30,30,0,707,-3047,6.6,0,0.8),
 (31,31,0,-2222,2298,26.6,0,0.8),
 (32,32,0,4328,5422,10.6,0.75,0.8),
 (33,33,0,38,-5332,52.6,1,0),
 (34,34,0,-1090,-3554.9,12.6,-0.64,0.76),
 (35,35,0,3427.5,-4642,5.6,-0.51,0.8),
 (36,36,0,1720,3191,7.6,1,0),
 (37,37,0,-2792,2179,5.6,-0.15,0.8),
 (38,38,0,-3116,2165,5.6,0.6,0.8),
 (39,39,0,4032,-6222,44,1,0),
 (40,40,0,-6927,-5704,80,-0.71,0.7),
 (41,41,0,-288,4890,42,1,0),
 (42,42,1692104,-3.20424,2.9712,7.9418,0.933335,0.35898);
UNLOCK TABLES;
/*!40000 ALTER TABLE `ticket_collectors` ENABLE KEYS */;


--
-- Definition of table `swgemu`.`ticket_terminals`
--

DROP TABLE IF EXISTS `swgemu`.`ticket_terminals`;
CREATE TABLE  `swgemu`.`ticket_terminals` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `transport_id` int(11) NOT NULL,
  `parent` bigint(20) unsigned NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `dir_y` float NOT NULL,
  `dir_w` float NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `SECONDARY` (`transport_id`)
) ENGINE=MyISAM AUTO_INCREMENT=46 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `swgemu`.`ticket_terminals`
--

/*!40000 ALTER TABLE `ticket_terminals` DISABLE KEYS */;
LOCK TABLES `ticket_terminals` WRITE;
INSERT INTO `swgemu`.`ticket_terminals` VALUES  (1,1,0,6935,-5545,220,-0.64,0.8),
 (2,2,0,6638,-5912,330,0.75,0.8),
 (3,3,0,-319.5,-4634,28,1,0),
 (4,4,0,-15,-4402,28,1,0),
 (5,5,0,3079.5,5002.5,280.6,0.75,0.8),
 (6,6,0,-3765.5,3240.5,86.6,1,0),
 (7,7,0,-5011,-2353,21.6,0,0.8),
 (8,8,0,-5607,-2781,21.6,0.75,0.8),
 (9,9,0,-5542,-6053,16.6,1,0),
 (10,10,0,1583,-6410,11,0,1),
 (11,11,0,-4220,-2356,10,1,0),
 (12,12,0,-640,2493,10,0.71,0.69),
 (13,13,0,-63,-1583,25.086,1,0),
 (14,14,0,605,3090,13.1256,1,0),
 (15,15,0,3213,-3493,31,0,1),
 (16,16,0,-962,1556,80,1,0),
 (17,17,0,464,5502,16.1,1,0),
 (18,18,0,5339,-1585,327.7,-0.71,0.7),
 (19,19,0,5122,6605,-191.4,0.42,-0.83),
 (20,20,0,2027.8,2517,19.7,-0.71,0.7),
 (21,21,0,1576,2845,25.7,1,0),
 (22,22,0,-5487,-30,-149.4,-0.71,0.7),
 (23,23,0,4968.6,-4901,4.4,-0.71,0.7),
 (24,24,0,-5863,4181,6.8,0.72,0.69),
 (25,25,0,-5419,4315,6.8,0,1),
 (26,26,0,-4990,4075,6.6,-0.94,0.38),
 (27,27,0,-5244,-2163.1,81.3,0.92,-0.38),
 (28,28,0,3668,-6412,103,1,0),
 (29,29,0,5221,5797,80.7,1,0);
INSERT INTO `swgemu`.`ticket_terminals` VALUES  (30,30,0,689,-3047,6.6,0,0.8),
 (31,31,0,-2219,2297,26.6,0,0.8),
 (32,32,0,4328,5439,10.6,0.75,0.8),
 (33,33,0,54,-5332,52.6,1,0),
 (34,34,0,-1092,-3570.9,12.6,-0.64,0.76),
 (35,35,0,3418.5,-4657.5,5.6,-0.51,0.8),
 (36,36,0,1738.5,3191,7.6,1,0),
 (37,37,0,-2809.5,2175,5.6,-0.15,0.8),
 (38,38,0,-3121,2183,5.6,0.6,0.8),
 (39,39,0,4039,-6222,44,1,0),
 (40,40,0,-6927,-5712,80,-0.71,0.7),
 (41,41,0,-280,4890,42,1,0),
 (42,42,1692104,-9.49707,-45.2359,7.97928,-0.71,1),
 (43,42,1692104,9.49707,-45.2359,7.97928,-0.71,1),
 (44,42,1692103,26.9453,-67.1413,0.749357,1,0),
 (45,42,1692102,-26.9453,-67.1413,0.749357,1,0);
UNLOCK TABLES;
/*!40000 ALTER TABLE `ticket_terminals` ENABLE KEYS */;


--
-- Definition of table `swgemu`.`transports`
--

DROP TABLE IF EXISTS `swgemu`.`transports`;
CREATE TABLE  `swgemu`.`transports` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `planet_id` tinyint(3) unsigned NOT NULL,
  `name` varchar(45) NOT NULL,
  `parent` bigint(20) unsigned NOT NULL default '0',
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `dir_y` float NOT NULL,
  `dir_w` float NOT NULL,
  `spawn_x` float NOT NULL,
  `spawn_y` float NOT NULL,
  `spawn_z` float NOT NULL,
  `starport` tinyint(1) NOT NULL default '0',
  `tax` int(10) unsigned NOT NULL default '0',
  `crc` bigint(20) unsigned NOT NULL default '1984806965',
  PRIMARY KEY  (`id`),
  KEY `SECONDARY` (`planet_id`)
) ENGINE=MyISAM AUTO_INCREMENT=43 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `swgemu`.`transports`
--

/*!40000 ALTER TABLE `transports` DISABLE KEYS */;
LOCK TABLES `transports` WRITE;
INSERT INTO `swgemu`.`transports` VALUES  (1,0,'Bela Vistal Shuttle A',0,6949,-5543,220,0.2,0.51,6936,-5537,330.6,1,0,1984806965),
 (2,0,'Bela Vistal Shuttle B',0,6623,-5923,330,0,0.51,6637,-5921,330.6,1,0,1984806965),
 (3,0,'Coronet Shuttle A',0,-323,-4620,28,-0.71,0.7,-331.2,-4639.2,28.6,1,0,1984806965),
 (4,0,'Coronet Shuttle B',0,-18,-4389,28,-0.71,0.7,-27.9,-4406,28.6,1,0,1984806965),
 (5,0,'Doaba Guerfel Shuttleport',0,3064,4992,280.6,0,0.51,3079,4993,280.6,1,0,1984806965),
 (6,0,'Kor Vella Shuttleport',0,-3777,3254,86.6,-0.7,-0.51,-3776,3240,86.6,1,0,1984806965),
 (7,0,'Tyrena Shuttle A',0,-5000,-2367,21.6,-0.7,0.51,-5001,-2355,21.6,1,0,1984806965),
 (8,0,'Tyrena Shuttle B',0,-5621,-2793,21.6,0,0.51,-5606,-2790,21.6,1,0,1984806965),
 (9,0,'Vreni Island',0,-5555,-6039,16.6,0.7,0.51,-5551,-6053,16.6,1,0,1984806965),
 (10,1,'Agro Outpost',0,1589,-6400,11,-0.71,0.7,1571,-6413,4,1,0,1984806965),
 (11,1,'Imperial Outpost',0,-4228,-2364,10,-0.71,0.7,-4213,-2350,3,1,0,1984806965),
 (12,1,'Mining Outpost',0,-638,2481,10,1,0,-636,2504,3,1,0,1984806965),
 (13,2,'Science Outpost',0,-74,-1583,25.086,1,0,-52,-1585,18,1,0,1984806965);
INSERT INTO `swgemu`.`transports` VALUES  (14,2,'Trade Outpost',0,593.9,3089,13.1256,-0.71,0.7,617,3090,6,1,0,1984806965),
 (15,3,'Research Outpost',0,3222,-3482,31,-0.71,0.7,3222,-3482,24,1,0,1984806965),
 (16,3,'Smuggler Outpost',0,-978,1554,80,-0.36,0.93,-978,1554,73,1,0,1984806965),
 (17,4,'Nyms Stronghold',0,458,5496,16.1,-0.71,0.7,476,5511,8.8,1,0,1984806965),
 (18,5,'Deeja Peak Shuttleport',0,5352,-1571,327.7,1,0,5351,-1577,327.7,1,0,1984806965),
 (19,5,'Kaadara Shuttleport',0,5141,6605,-191.4,-0.92,0.39,5137,6601,-191.4,1,0,1984806965),
 (20,5,'Keren Shuttle A',0,2041,2531,19.7,1,0,2041,2525,19.7,1,0,1984806965),
 (21,5,'Keren Shuttle B',0,1575,2857,25.7,-0.71,0.7,1568,2858,25.7,1,0,1984806965),
 (22,5,'Lake Retreat Shuttleport',0,-5474,-15,-149.4,1,0,-5474,-21,-149.4,1,0,1984806965),
 (23,5,'Moenia Shuttleport',0,4982,-4885,4.4,1,0,4981,-4890,4.4,1,0,1984806965),
 (24,5,'Theed Shuttle A',0,-5876,4178,6.8,0,1,-5876,4173,6.8,1,0,1984806965),
 (25,5,'Theed Shuttle B',0,-5416,4302,6.8,-0.71,0.7,-5411,4302,6.8,1,0,1984806965),
 (26,5,'Theed Shuttle C',0,-4983,4086,6.6,0.47,-0.8,-4989,4090,6.6,1,0,1984806965);
INSERT INTO `swgemu`.`transports` VALUES  (27,6,'Narmle Shuttleport',0,-5236.4,-2151,81.3,0.42,-0.83,-5241,-2147,81.3,1,0,1984806965),
 (28,6,'Rebel Outpost',0,3667,-6418,103,0.71,0.69,3692,-6403,96,1,0,1984806965),
 (29,6,'Restuss Shuttleport',0,5207,5810,80.7,0.71,0.69,5213,5810,80.7,1,0,1984806965),
 (30,7,'Dearic Shuttleport',0,701,-3062,6.6,-0.7,0.51,699,-3047,6.6,1,0,1984806965),
 (31,7,'Imperial Outpost',0,-2214,2301,26.6,0,0.51,-2228,2321,20,1,0,1984806965),
 (32,7,'Nashal Shuttleport',0,4313,5427,10.6,0,0.51,4328,5433,10.6,1,0,1984806965),
 (33,8,'Anchorhead',0,47,-5317,52.6,0.706544,0.707669,47,-5333,52.6,1,0,1984806965),
 (34,8,'Bestine Shuttleport',0,-1078,-3564,12.6,0,0,-1093,-3562,12.6,1,0,1984806965),
 (35,8,'Mos Eisley Shuttleport',0,3433,-4658,5.6,0.4,0.5,3433,-4658,5.6,1,0,1984806965),
 (36,8,'Mos Entha Shuttleport',0,1729,3205,7.6,0.706544,0.707669,1728,3199,7.6,1,0,1984806965),
 (37,8,'Mos Espa Shuttle A',0,-2797,2164,5.6,0.75,-0.6,-2800,2176,5.6,1,0,1984806965),
 (38,8,'Mos Espa Shuttle B',0,-3131,2169,5.6,0.15,-0.75,-3117,2174,5.6,1,0,1984806965),
 (39,9,'Imperial Outpost',0,4033,-6234,44,-0.71,0.7,4033,-6234,37,1,0,1984806965);
INSERT INTO `swgemu`.`transports` VALUES  (40,9,'Labor Outpost',0,-6938,-5706,80,1,0,-6939,-5706,73,1,0,1984806965),
 (41,9,'Mining Outpost',0,-288,4879,42,0.71,0.69,-288,4879,35,1,0,1984806965),
 (42,5,'Theed Starport',1692104,-15.6958,20.162,7.9418,0.71,1,-4852.44,4171.5,6.42631,1,0,773296996);
UNLOCK TABLES;
/*!40000 ALTER TABLE `transports` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
