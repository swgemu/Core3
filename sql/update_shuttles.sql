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
-- Create schema swgemu
--

CREATE DATABASE IF NOT EXISTS swgemu;
USE swgemu;

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
) ENGINE=MyISAM AUTO_INCREMENT=11 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `shuttles`
--

/*!40000 ALTER TABLE `shuttles` DISABLE KEYS */;
INSERT INTO `shuttles` (`shuttle_id`,`planet_id`,`shuttle_name`,`player_spawn_x`,`player_spawn_y`,`player_spawn_z`,`shut_x`,`shut_y`,`shut_z`,`shut_dir_y`,`shut_dir_w`,`coll_x`,`coll_y`,`tick_dir_y`,`tick_dir_w`,`term_x`,`term_y`) VALUES 
 (1,0,'Coronet Shuttle A',-331.2,-4639.2,28.6,-323,-4620,28,-0.71,0.7,-338,-4634,1,0,-319.5,-4634),
 (2,0,'Coronet Shuttle B',-27.9,-4406,28.6,-18,-4389,28,-0.71,0.7,-34.2,-4402,1,0,-15,-4402),
 (3,2,'Trade Outpost',617,3090,6,593.9,3089,13.1256,-0.71,0.7,598,3095,1,0,605,3090),
 (4,2,'Science Outpost',-52,-1585,18,-74,-1583,25.086,1,0,-68.9,-1578,1,0,-63,-1583),
 (5,8,'Bestine Shuttleport',-1093,-3562,12.6,-1078,-3564,12.6,0,0,-1090,-3554.9,-0.64,0.76,-1092,-3570.9),
 (6,8,'Anchorhead',47,-5333,52.6,47,-5317,52.6,0.706544,0.707669,38,-5332,1,0,54,-5332),
 (7,8,'Mos Eisley Shuttleport',3433,-4658,5.6,3433,-4658,5.6,0.4,0.5,3427.5,-4642,-0.51,0.8,3418.5,-4657.5),
 (8,8,'Mos Entha Shuttleport',1728,3199,7.6,1729,3205,7.6,0.706544,0.707669,1720,3191,1,0,1738.5,3191),
 (9,8,'Mos Espa Shuttle A',-2800,2176,5.6,-2797,2164,5.6,0.75,-0.6,-2792,2179,-0.15,0.8,-2809.5,2175),
 (10,8,'Mos Espa Shuttle B',-3117,2174,5.6,-3131,2169,5.6,0.15,-0.75,-3116,2165,0.6,0.8,-3121,2183);
/*!40000 ALTER TABLE `shuttles` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
