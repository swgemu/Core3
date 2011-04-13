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
-- Definition of table `swgemu`.`statictangibleobjects`
--

DROP TABLE IF EXISTS `swgemu`.`statictangibleobjects`;
CREATE TABLE  `swgemu`.`statictangibleobjects` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `zoneid` tinyint(4) NOT NULL,
  `parentid` bigint(20) NOT NULL,
  `name` varchar(255) NOT NULL,
  `template_file` varchar(200) NOT NULL,
  `template_type` int(255) NOT NULL,
  `template_name` varchar(255) NOT NULL,
  `oX` float NOT NULL,
  `oY` float NOT NULL,
  `oZ` float NOT NULL,
  `oW` float NOT NULL,
  `X` float NOT NULL,
  `Z` float NOT NULL,
  `Y` float NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `zone_id` (`zoneid`),
  FULLTEXT KEY `file_ix` (`template_file`)
) ENGINE=MyISAM AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `swgemu`.`statictangibleobjects`
--

/*!40000 ALTER TABLE `statictangibleobjects` DISABLE KEYS */;
LOCK TABLES `statictangibleobjects` WRITE;
INSERT INTO `swgemu`.`statictangibleobjects` VALUES  (1,5,0,'Jeff Freeman Memorial Fountain','object/tangible/furniture/city/fountain_heroic.iff',8203,'fountain_heroic',0,-0.401868,0,0.915698,-4879.48,6,4139.49),
 (2,8,0,'Blue Frog','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.768226,0,-0.640178,3533.04,5,-4796),
 (3,8,0,'Blue Frog','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,-0.486657,0,0.873593,-1271.07,12,-3590.22),
 (4,5,0,'Blue Frog','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.309582,0,0.950873,-4876.99,6,4142.12),
 (5,0,0,'Blue Frog','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,-0.664289,0,0.747476,-133.192,28,-4711.16),
 (6,0,0,'Blue Frog','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.346712,0,0.937972,-5049.64,21,-2304.52);
UNLOCK TABLES;
/*!40000 ALTER TABLE `statictangibleobjects` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
