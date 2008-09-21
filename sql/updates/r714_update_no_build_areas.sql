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

--
-- Definition of table `swgemu`.`character_structures`
--

DROP TABLE IF EXISTS `swgemu`.`character_structures`;
CREATE TABLE  `swgemu`.`character_structures` (
  `zoneid` tinyint(4) NOT NULL,
  `objectid` bigint(20) NOT NULL,
  `parentid` bigint(20) NOT NULL,
  `title` varchar(200) NOT NULL,
  `template` varchar(255) NOT NULL,
  `crc` bigint(20) NOT NULL,
  `file` varchar(200) NOT NULL,
  `oX` float NOT NULL,
  `oY` float NOT NULL,
  `oZ` float NOT NULL,
  `oW` float NOT NULL,
  `X` float NOT NULL,
  `Z` float NOT NULL,
  `Y` float NOT NULL,
  `type` float NOT NULL,
  `noBuildArea` bigint(20) unsigned NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `swgemu`.`character_structures`
--

/*!40000 ALTER TABLE `character_structures` DISABLE KEYS */;
LOCK TABLES `character_structures` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `character_structures` ENABLE KEYS */;


--
-- Definition of table `swgemu`.`no_build_areas`
--

DROP TABLE IF EXISTS `swgemu`.`no_build_areas`;
CREATE TABLE  `swgemu`.`no_build_areas` (
  `zoneid` tinyint(3) unsigned NOT NULL,
  `uid` bigint(20) unsigned NOT NULL auto_increment,
  `xMin` float NOT NULL,
  `xMax` float NOT NULL,
  `yMin` float NOT NULL,
  `yMax` float NOT NULL,
  `reason` tinyint(3) unsigned NOT NULL,
  PRIMARY KEY  (`uid`),
  KEY `secondary` (`uid`)
) ENGINE=MyISAM AUTO_INCREMENT=8 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `swgemu`.`no_build_areas`
--

/*!40000 ALTER TABLE `no_build_areas` DISABLE KEYS */;
LOCK TABLES `no_build_areas` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `no_build_areas` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
