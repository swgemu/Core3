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
) ENGINE=MyISAM AUTO_INCREMENT=32 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `swgemu`.`statictangibleobjects`
--

/*!40000 ALTER TABLE `statictangibleobjects` DISABLE KEYS */;
LOCK TABLES `statictangibleobjects` WRITE;
INSERT INTO `swgemu`.`statictangibleobjects` VALUES  (1,5,0,'Jeff Freeman Memorial Fountain','object/tangible/furniture/city/fountain_heroic.iff',8203,'fountain_heroic',0,-0.401868,0,0.915698,-4879.48,6,4139.49),
 (2,8,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.768226,0,-0.640178,3533.04,5,-4796),
 (3,8,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,-0.486657,0,0.873593,-1271.07,12,-3590.22),
 (4,5,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.309582,0,0.950873,-4876.99,6,4142.12),
 (5,0,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,-0.664289,0,0.747476,-133.192,28,-4711.16),
 (6,0,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.346712,0,0.937972,-5049.64,21,-2304.52),
 (9,1,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.695864,0,0.718174,1585.68,4,-6368.95),
 (8,1,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.725999,0,-0.687696,-629.417,3,2481.24);
INSERT INTO `swgemu`.`statictangibleobjects` VALUES  (7,1,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,-0.168608,0,0.985683,-4224.77,3,-2398.08),
 (27,8,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,-0.514176,0,0.857684,-2896.35,5,2130.87),
 (26,8,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.989124,0,-0.147086,1299.08,7,3145.21),
 (15,3,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.932952,0,-0.360002,-963.537,73,1556.86),
 (14,3,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.723459,0,-0.690367,3240.5,24,-3484.79),
 (13,2,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.701463,0,0.712705,592.612,6,3089.84),
 (12,2,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.314904,0,0.949123,-67.6585,18,-1595.3),
 (11,0,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.290803,0,0.956783,3330.38,308,5517.14);
INSERT INTO `swgemu`.`statictangibleobjects` VALUES  (10,0,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,-0.389024,0,0.921227,-3134.67,31,2790.19),
 (17,5,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.715602,0,-0.698509,4824.53,4.17,-4704.9),
 (20,6,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,-0.0274543,0,0.999623,3672.91,96,-6441.07),
 (19,5,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,-0.0116238,0,0.999932,5193.14,-192,6680.25),
 (18,5,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,-0.0116238,0,-0.686427,1445.8,13,2771.98),
 (16,4,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.999879,0,0.015506,464.677,8.75806,5506.49),
 (25,7,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.996369,0,-0.0851417,4447.08,2,5286.96),
 (24,7,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.692641,0,0.721282,329.666,6,-2924.69);
INSERT INTO `swgemu`.`statictangibleobjects` VALUES  (23,7,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.986933,0,-0.161134,-2207.13,20,2320.67),
 (22,6,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,-0.100263,0,0.994961,-5307.37,80.1274,-2216.91),
 (21,6,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,-0.69192,0,0.721974,5370.22,80,5666.04),
 (30,9,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,-0.705623,0,0.708587,-6917.18,73,-5732.25),
 (29,9,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.723339,0,-0.690493,4057.69,37,-6217.54),
 (28,0,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,-0.666281,0,0.745701,-136.437,28,-4730.23),
 (31,9,0,'','object/tangible/terminal/terminal_character_builder.iff',16400,'terminal_character_builder',0,0.00721678,0,0.999974,-293.367,35,4854.52);
UNLOCK TABLES;
/*!40000 ALTER TABLE `statictangibleobjects` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
