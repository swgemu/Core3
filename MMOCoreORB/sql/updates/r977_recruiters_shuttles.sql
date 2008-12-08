-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.0.51a


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

DROP TABLE IF EXISTS `swgemu`.`recruiters`;
CREATE TABLE  `swgemu`.`recruiters` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `planet_id` tinyint(1) unsigned NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `oY` float NOT NULL,
  `oW` float NOT NULL,
  `cell_id` bigint(20) unsigned NOT NULL default '0',
  `type` tinyint(1) unsigned NOT NULL COMMENT '1 = imperial 2= rebel',
  PRIMARY KEY  (`id`),
  KEY `SECONDARY` (`planet_id`)
) ENGINE=MyISAM AUTO_INCREMENT=20 DEFAULT CHARSET=latin1;
INSERT INTO `swgemu`.`recruiters` VALUES  (2,5,-4928,4231,0,1,0.053,0,1),
 (1,5,-4936,4231,0,1,0.053,0,1),
 (3,5,5307,-1584,0,0.6,0.8,0,1),
 (4,5,-29,-1.2,-0.89,0.6,0.8,119,2),
 (5,0,6719,-5804,315,1,0.037,0,1),
 (6,0,-29,0.5,-0.89,0.6,0.8,8105504,2),
 (7,0,-29,0.5,-0.89,0.6,0.8,2625363,2),
 (8,8,-6.7,-6.9,-3.9,0.45,0.89,1213349,2),
 (9,8,-1275,-3594,0,-0.6,0.8,0,1),
 (10,8,-1138,-3897,98,0,1,0,1),
 (11,8,-0.86,-8,0.4,0.45,0.89,1280131,1),
 (12,6,3683,-6460,0,0.77,-0.63,0,2),
 (13,7,-2192,2269,0,-0.42,0.9,0,1),
 (14,7,-28.4145,-1.7825,-0.89,0.66,0.74,3175399,2),
 (15,1,-4196.99,-2411.57,3,-0.65,0.75,0,1),
 (16,6,5348,5616,80,-0.6,1,0,1),
 (17,5,4826,-4696,0,0.72,-0.69,0,2),
 (19,9,5074.27,306.337,79.1658,0.660164,0.751121,0,1),
 (18,9,-5573.93,4908.46,87.721,1,0,0,2);

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
) ENGINE=MyISAM AUTO_INCREMENT=60 DEFAULT CHARSET=latin1;
INSERT INTO `swgemu`.`transports` VALUES  (1,0,'Bela Vistal Shuttle A',0,6949,-5543,220,0.2,0.51,6936,-5537,330.6,0,0,1984806965),
 (2,0,'Bela Vistal Shuttle B',0,6623,-5923,330,0,0.51,6637,-5921,330.6,0,0,1984806965),
 (3,0,'Coronet Shuttle A',0,-323,-4620,28,-0.71,0.7,-331.2,-4639.2,28.6,0,0,1984806965),
 (4,0,'Coronet Shuttle B',0,-18,-4389,28,-0.71,0.7,-27.9,-4406,28.6,0,0,1984806965),
 (5,0,'Doaba Guerfel Shuttleport',0,3064,4992,280.6,0,0.51,3079,4993,280.6,0,0,1984806965),
 (6,0,'Kor Vella Shuttleport',0,-3777,3254,86.6,-0.7,-0.51,-3776,3240,86.6,0,0,1984806965),
 (7,0,'Tyrena Shuttle A',0,-5000,-2367,21.6,-0.7,0.51,-5001,-2355,21.6,0,0,1984806965),
 (8,0,'Tyrena Shuttle B',0,-5621,-2793,21.6,0,0.51,-5606,-2790,21.6,0,0,1984806965),
 (9,0,'Vreni Island',0,-5555,-6039,16.6,0.7,0.51,-5551,-6053,16.6,0,0,1984806965),
 (10,1,'Pirate Outpost',0,1589,-6400,11,-0.71,0.7,1571,-6413,4,1,0,1196401137),
 (11,1,'Imperial Outpost',0,-4228,-2364,10,-0.71,0.7,-4213,-2350,3,1,0,1196401137),
 (12,1,'Mining Outpost',0,-638,2481,10,1,0,-636,2504,3,1,0,1196401137),
 (13,2,'Science Outpost',0,-74,-1583,25.086,1,0,-52,-1585,18,1,0,1196401137);
INSERT INTO `swgemu`.`transports` VALUES  (14,2,'Trade Outpost',0,593.9,3089,13.1256,-0.71,0.7,617,3090,6,1,0,1196401137),
 (15,3,'Research Outpost',0,3222,-3482,31,-0.71,0.7,3222,-3482,24,1,0,1196401137),
 (16,3,'Smuggler Outpost',0,-978,1554,80,-0.36,0.93,-978,1554,73,1,0,1196401137),
 (17,4,'Nyms Stronghold',0,458,5496,16.1,-0.71,0.7,476,5511,8.8,1,0,1196401137),
 (18,5,'Deeja Peak Shuttleport',0,5352,-1571,327.7,1,0,5351,-1577,327.7,0,0,1984806965),
 (19,5,'Kaadara Shuttleport',0,5141,6605,-191.4,-0.92,0.39,5137,6601,-191.4,0,0,1984806965),
 (20,5,'Keren Shuttle A',0,2041,2531,19.7,1,0,2041,2525,19.7,0,0,1984806965),
 (21,5,'Keren Shuttle B',0,1575,2857,25.7,-0.71,0.7,1568,2858,25.7,0,0,1984806965),
 (22,5,'Lake Retreat Shuttleport',0,-5474,-15,-149.4,1,0,-5474,-21,-149.4,0,0,1984806965),
 (23,5,'Moenia Shuttleport',0,4982,-4885,4.4,1,0,4981,-4890,4.4,0,0,1984806965),
 (24,5,'Theed Shuttle A',0,-5876,4178,6.8,0,1,-5876,4173,6.8,0,0,1984806965),
 (25,5,'Theed Shuttle B',0,-5416,4302,6.8,-0.71,0.7,-5411,4302,6.8,0,0,1984806965),
 (26,5,'Theed Shuttle C',0,-4983,4086,6.6,0.47,-0.8,-4989,4090,6.6,0,0,1984806965);
INSERT INTO `swgemu`.`transports` VALUES  (27,6,'Narmle Shuttleport',0,-5236.4,-2151,81.3,0.42,-0.83,-5241,-2147,81.3,0,0,1984806965),
 (28,6,'Rebel Outpost',0,3667,-6418,103,0.71,0.69,3692,-6403,96,1,0,1196401137),
 (29,6,'Restuss Shuttleport',0,5207,5810,80.7,0.71,0.69,5213,5810,80.7,0,0,1984806965),
 (30,7,'Dearic Shuttleport',0,701,-3062,6.6,-0.7,0.51,699,-3047,6.6,0,0,1984806965),
 (31,7,'Imperial Outpost',0,-2214,2301,26.6,0,0.51,-2228,2321,20,1,0,1196401137),
 (32,7,'Nashal Shuttleport',0,4313,5427,10.6,0,0.51,4328,5433,10.6,0,0,1984806965),
 (33,8,'Anchorhead',0,47,-5317,52.6,0.706544,0.707669,47,-5333,52.6,0,0,1984806965),
 (34,8,'Bestine Shuttleport',0,-1078,-3564,12.6,0,0,-1093,-3562,12.6,0,0,1984806965),
 (35,8,'Mos Eisley Shuttleport',0,3433,-4658,5.6,0.4,0.5,3433,-4658,5.6,0,0,1984806965),
 (36,8,'Mos Entha Shuttleport',0,1729,3205,7.6,0.706544,0.707669,1728,3199,7.6,0,0,1984806965),
 (37,8,'Mos Espa Shuttle A',0,-2797,2164,5.6,0.75,-0.6,-2800,2176,5.6,0,0,1984806965),
 (38,8,'Mos Espa Shuttle B',0,-3131,2169,5.6,0.15,-0.75,-3117,2174,5.6,0,0,1984806965),
 (39,9,'Imperial Outpost',0,4033,-6234,44,-0.71,0.7,4033,-6234,37,1,0,1196401137);
INSERT INTO `swgemu`.`transports` VALUES  (40,9,'Labor Outpost',0,-6938,-5706,80,1,0,-6939,-5706,73,1,0,1196401137),
 (41,9,'Mining Outpost',0,-288,4879,42,0.71,0.69,-288,4879,35,1,0,1196401137),
 (42,5,'Theed Starport',1692104,0,0,7.94,0.71,1,-4852.44,4171.5,6.42631,1,0,773296996),
 (43,5,'Moenia Starport',0,4727,-4641,4.17,0.689877,0.723926,4727.88,-4641.2,4.17,1,0,1196401137),
 (44,5,'Keren Starport',0,1350,2769,13,0.71,0.7,1350,2769,13,1,0,1196401137),
 (45,5,'Kaadara Starport',0,5301,6662,-192,0.71,0.7,5301,6662,-192,1,0,1196401137),
 (46,0,'Doaba Guerfel Starport',0,3377,5606,308,-0.71,1,3377,5606,-308,1,0,1196401137),
 (47,0,'Kor Vella Starport',0,-3138,2897,31,0,1,-3138,2897,31,1,0,1196401137),
 (48,0,'Tyrena Starport',0,-4976,-2224,21,0,1,-4976,-2224,21,1,0,1196401137),
 (49,0,'Coronet Starport',0,-52,-4736,28,0.71,0.75,-52,-4736,28,1,0,1196401137),
 (50,6,'Restuss Starport',0,5366.71,5754.58,80,-0.22,1,5366,5754,80,1,0,1196401137),
 (51,6,'Narmle Starport',0,-5371,-2157,80,0.89,0.46,-5371,-5754,80,1,0,1196401137),
 (52,7,'Dearic Starport',0,243,-2926,6,0.83,-0.55,243,-2926,6,1,0,1196401137);
INSERT INTO `swgemu`.`transports` VALUES  (53,7,'Nashal Starport',0,4483,5369,2,-0.81,1,4483,5369,2,1,0,1196401137),
 (54,8,'Mos Entha Starport',0,1236,3059,7,1,0,1236,3059,7,1,0,1196401137),
 (55,8,'Mos Espa Starport',0,-2824,2081,5,0.73,0.67,-2824,2081,5,1,0,1196401137),
 (56,8,'Mos Eisley Starport',0,3624,-4797,5,-0.53,0.84,3624,-4797,5,1,0,1196401137),
 (57,8,'Bestine Starport',0,-1377,-3576,12,0.78,-0.61,-1377,-3576,12,1,0,1196401137),
 (58,9,'Dark Enclave Drop Point',0,5097.97,339.011,78,0.954537,-0.298093,5093.98,332.88,78.7714,1,0,3655546204),
 (59,9,'Light Enclave Drop Point',0,-5544.33,4898.59,87.2317,0.79989,-0.600148,-5551,4896,86.84,1,0,3655546204);



/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
