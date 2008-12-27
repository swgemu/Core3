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

DROP TABLE IF EXISTS `swgemu`.`badge_areas`;
CREATE TABLE  `swgemu`.`badge_areas` (
  `uid` tinyint(1) unsigned NOT NULL auto_increment,
  `planet_id` tinyint(1) unsigned NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `badge_id` tinyint(1) unsigned NOT NULL,
  PRIMARY KEY  (`uid`),
  KEY `SECONDARY` (`planet_id`)
) ENGINE=MyISAM AUTO_INCREMENT=46 DEFAULT CHARSET=latin1;
INSERT INTO `swgemu`.`badge_areas` VALUES  (1,0,5291,1494,79),
 (2,0,-5418,-6248,80),
 (3,0,6767,-5617,81),
 (4,0,1084,4176,20),
 (5,0,-6530,5967,78),
 (6,1,-3862,-5706,84),
 (7,1,-7156,-883,85),
 (8,1,-6836,5520,31),
 (9,1,4195,5203,30),
 (10,2,-6304,753,83),
 (11,2,652,-4888,25),
 (12,2,-2101,3165,26),
 (13,2,-4427,586,27),
 (14,2,3558,1554,28),
 (15,2,5585,1903,82),
 (16,2,3021,1289,29),
 (17,3,4596,-2423,86),
 (18,3,6051,-2477,88),
 (19,3,-650,-5076,87),
 (20,3,-4628,-2273,89),
 (21,4,-1814,-3086,98),
 (22,4,3091,-4638,24),
 (23,4,4562,-1156,99),
 (24,5,-4628,4207,75),
 (25,5,5157,-1646,76),
 (26,5,-5828,-93,77),
 (27,5,-2066,-5423,19),
 (28,6,-1130,4544,97),
 (29,6,-5633,-5661,96),
 (30,6,3664,-6501,95),
 (31,6,7371,169,94),
 (32,7,4133,962,90),
 (33,7,-2184,2405,91),
 (34,7,-2452,3846,92),
 (35,7,-4425,-1414,93),
 (36,8,-2579,-5500,17),
 (37,8,-4512,-2270,12),
 (38,8,-6176,-3372,16),
 (39,8,-3930,-4425,15),
 (40,8,-4650,-4363,14),
 (41,8,7428,4563,18),
 (42,8,-3969,6267,13),
 (43,9,5076,5537,23),
 (44,9,-875,-2047,22);
INSERT INTO `swgemu`.`badge_areas` VALUES  (45,9,519,-646,21);

DROP TABLE IF EXISTS `swgemu`.`character_badge`;
CREATE TABLE  `swgemu`.`character_badge` (
  `character_id` mediumint(8) unsigned NOT NULL default '0',
  `bitmask0` mediumint(8) unsigned NOT NULL default '0',
  `bitmask1` mediumint(8) unsigned NOT NULL default '0',
  `bitmask2` mediumint(8) unsigned NOT NULL default '0',
  `bitmask3` mediumint(8) unsigned NOT NULL default '0',
  `bitmask4` mediumint(8) unsigned NOT NULL default '0',
  `totalCount` tinyint(3) unsigned NOT NULL default '0',
  `count0` tinyint(3) unsigned NOT NULL default '0',
  `count1` tinyint(3) unsigned NOT NULL default '0',
  `count2` tinyint(3) unsigned default '0',
  `count3` tinyint(3) unsigned NOT NULL default '0',
  `count4` tinyint(3) unsigned NOT NULL default '0',
  `count5` tinyint(3) unsigned NOT NULL default '0',
  PRIMARY KEY  (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;



/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
