-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.0.51a-community-nt


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


--
-- Create schema test
--

CREATE DATABASE IF NOT EXISTS test;
USE test;

--
-- Definition of table `shuttles`
--

DROP TABLE IF EXISTS `shuttles`;
CREATE TABLE `shuttles` (
  `shuttle_id` int(10) unsigned NOT NULL auto_increment,
  `planet_id` tinyint(1) unsigned NOT NULL default '0',
  `shuttle_name` varchar(45) NOT NULL default '0',
  `player_spawn_x` float NOT NULL default '0',
  `player_spawn_y` float NOT NULL default '0',
  `player_spawn_z` float NOT NULL,
  `shut_x` float NOT NULL,
  `shut_y` float NOT NULL,
  `shut_z` float NOT NULL,
  `shut_dir_y` float NOT NULL,
  `shut_dir_w` float NOT NULL,
  `coll_x` float NOT NULL,
  `coll_y` float NOT NULL,
  `tick_dir_y` float NOT NULL,
  `tick_dir_w` float NOT NULL,
  `term_x` float NOT NULL,
  `term_y` float NOT NULL,
  PRIMARY KEY  USING BTREE (`shuttle_id`)
) ENGINE=MyISAM AUTO_INCREMENT=61 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `shuttles`
--

/*!40000 ALTER TABLE `shuttles` DISABLE KEYS */;
INSERT INTO `shuttles` (`shuttle_id`,`planet_id`,`shuttle_name`,`player_spawn_x`,`player_spawn_y`,`player_spawn_z`,`shut_x`,`shut_y`,`shut_z`,`shut_dir_y`,`shut_dir_w`,`coll_x`,`coll_y`,`tick_dir_y`,`tick_dir_w`,`term_x`,`term_y`) VALUES 
 (1,0,'Coronet Shuttle A',-331.2,-4639.2,28.6,-323,-4620,28,-0.71,0.7,-338,-4634,1,0,-319.5,-4634),
 (2,0,'Coronet Shuttle B',-27.9,-4406,28.6,-18,-4389,28,-0.71,0.7,-34.2,-4402,1,0,-15,-4402),
 (13,2,'Trade Outpost',617,3090,6,593.9,3089,13.1256,-0.71,0.7,598,3095,1,0,605,3090),
 (14,2,'Science Outpost',-52,-1585,18,-74,-1583,25.086,1,0,-68.9,-1578,1,0,-63,-1583),
 (32,8,'Bestine Shuttleport',-1093,-3562,12.6,-1078,-3564,12.6,0,0,-1090,-3554.9,-0.64,0.76,-1092,-3570.9),
 (31,8,'Anchorhead',47,-5333,52.6,47,-5317,52.6,0.706544,0.707669,38,-5332,1,0,54,-5332),
 (30,8,'Mos Eisley Shuttleport',3433,-4658,5.6,3433,-4658,5.6,0.4,0.5,3427.5,-4642,-0.51,0.8,3418.5,-4657.5),
 (29,8,'Mos Entha Shuttleport',1728,3199,7.6,1729,3205,7.6,0.706544,0.707669,1720,3191,1,0,1738.5,3191),
 (33,8,'Mos Espa Shuttle A',-2800,2176,5.6,-2797,2164,5.6,0.75,-0.6,-2792,2179,-0.15,0.8,-2809.5,2175),
 (28,8,'Mos Espa Shuttle B',-3117,2174,5.6,-3131,2169,5.6,0.15,-0.75,-3116,2165,0.6,0.8,-3121,2183),
 (9,0,'Kor Vella Shuttleport',-3776,3240,86.6,-3777,3254,86.6,-0.7,-0.51,-3783.5,3240.5,1,0,-3765.5,3240.5),
 (8,0,'Doaba Guerfel Shuttleport',3079,4993,280.6,3064,4992,280.6,0,0.51,3078.5,4984.5,0.75,0.8,3079.5,5002.5),
 (6,0,'Tyrena Shuttle A',-5001,-2355,21.6,-5000,-2367,21.6,-0.7,0.51,-4992,-2354,0,0.8,-5011,-2353),
 (7,0,'Tyrena Shuttle B',-5606,-2790,21.6,-5621,-2793,21.6,0,0.51,-5607,-2799,0.75,0.8,-5607,-2781),
 (5,0,'Vreni Island',-5551,-6053,16.6,-5555,-6039,16.6,0.7,0.51,-5560,-6053,1,0,-5542,-6053),
 (3,0,'Bela Vistal Shuttle A',6936,-5537,330.6,6949,-5543,220,0.2,0.51,6938,-5528,-0.64,0.8,6935,-5545),
 (4,0,'Bela Vistal Shuttle B',6637,-5921,330.6,6623,-5923,330,0,0.51,6637,-5931,0.75,0.8,6638,-5912),
 (27,7,'Nashal Shuttleport',4328,5433,10.6,4313,5427,10.6,0,0.51,4328,5422,0.75,0.8,4328,5439),
 (26,7,'Dearic Shuttleport',699,-3047,6.6,701,-3062,6.6,-0.7,0.51,707,-3047,0,0.8,689,-3047),
 (25,7,'Imperial Outpost',-2228,2321,20,-2214,2301,26.6,0,0.51,-2222,2298,0,0.8,-2219,2297),
 (15,4,'Nyms Stronghold',476,5511,8.8,458,5496,16.1,-0.71,0.7,459,5503,1,0,464,5502),
 (11,1,'Mining Outpost',-636,2504,3,-638,2481,10,1,0,-644,2488,0.71,0.69,-640,2493),
 (10,1,'Agro Outpost',1571,-6413,4,1589,-6400,11,-0.71,0.7,1589,-6410.4,0,1,1583,-6410),
 (12,1,'Imperial Outpost',-4213,-2350,3,-4228,-2364,10,-0.71,0.7,-4229,-2355.5,1,0,-4220,-2356),
 (16,5,'Theed Shuttle A',-5876,4173,6.8,-5876,4178,6.8,0,1,-5863,4163,0.72,0.69,-5863,4181),
 (17,5,'Theed Shuttle B',-5411,4302,6.8,-5416,4302,6.8,-0.71,0.7,-5402,4315,0,1,-5419,4315),
 (18,5,'Theed Shuttle C',-4989,4090,6.6,-4983,4086,6.6,0.47,-0.8,-5004.5,4086,-0.94,0.38,-4990,4075),
 (21,5,'Kaadara Shuttleport',5137,6601,-191.4,5141,6605,-191.4,-0.92,0.39,5134,6616.4,0.42,-0.83,5122,6605),
 (19,5,'Keren Shuttle A',2041,2525,19.7,2041,2531,19.7,1,0,2028,2534,-0.71,0.7,2027.8,2517),
 (20,5,'Keren Shuttle B',1568,2858,25.7,1575,2857,25.7,-0.71,0.7,1558,2845,1,0,1576,2845),
 (22,5,'Lake Retreat Shuttleport',-5474,-21,-149.4,-5474,-15,-149.4,1,0,-5487,-13,-0.71,0.7,-5487,-30),
 (23,5,'Deeja Peak Shuttleport',5351,-1577,327.7,5352,-1571,327.7,1,0,5339,-1567,-0.71,0.7,5339,-1585),
 (24,5,'Moenia Shuttleport',4981,-4890,4.4,4982,-4885,4.4,1,0,4968.6,-4883.7,-0.71,0.7,4968.6,-4901),
 (34,6,'Restuss Shuttleport',5213,5810,80.7,5207,5810,80.7,0.71,0.69,5205,5797,1,0,5221,5797),
 (38,9,'Imperial Outpost',4033,-6234,37,4033,-6234,44,-0.71,0.7,4032,-6222,1,0,4039,-6222),
 (35,6,'Narmle Shuttleport',-5241,-2147,81.3,-5236.4,-2151,81.3,0.42,-0.83,-5256.4,-2150.4,0.92,-0.38,-5244,-2163.1),
 (36,3,'Smuggler Outpost',-978,1554,73,-978,1554,80,-0.36,0.93,-970,1563,1,0,-962,1556),
 (37,3,'Research Outpost',3222,-3482,24,3222,-3482,31,-0.71,0.7,3222,-3493,0,1,3213,-3493),
 (39,9,'Labor Outpost',-6939,-5706,73,-6938,-5706,80,1,0,-6927,-5704,-0.71,0.7,-6927,-5712),
 (40,9,'Mining Outpost',-288,4879,35,-288,4879,42,0.71,0.69,-288,4890,1,0,-280,4890),
 (41,6,'Rebel Outpost',3692,-6403,96,3667,-6418,103,0.71,0.69,3668,-6409,1,0,3668,-6412);
/*!40000 ALTER TABLE `shuttles` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
