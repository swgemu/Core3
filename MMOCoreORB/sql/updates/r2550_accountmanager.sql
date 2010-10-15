-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.0.51a-24+lenny4


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
-- Definition of table `swgemu`.`account_bans`
--

DROP TABLE IF EXISTS `swgemu`.`account_bans`;
CREATE TABLE  `swgemu`.`account_bans` (
  `ban_id` int(10) unsigned NOT NULL auto_increment,
  `account_id` int(10) unsigned NOT NULL,
  `issuer_id` int(10) unsigned NOT NULL,
  `created` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `expires` timestamp NOT NULL default '0000-00-00 00:00:00',
  `reason` tinytext NOT NULL,
  PRIMARY KEY  USING BTREE (`ban_id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `swgemu`.`account_bans`
--

/*!40000 ALTER TABLE `account_bans` DISABLE KEYS */;
LOCK TABLES `account_bans` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `account_bans` ENABLE KEYS */;


--
-- Definition of table `swgemu`.`account_log`
--

DROP TABLE IF EXISTS `swgemu`.`account_log`;
CREATE TABLE  `swgemu`.`account_log` (
  `acclog_id` int(10) unsigned NOT NULL auto_increment,
  `account_id` int(10) unsigned NOT NULL,
  `timestamp` int(10) unsigned NOT NULL,
  `event_type` bit(1) NOT NULL,
  PRIMARY KEY  (`acclog_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `swgemu`.`account_log`
--

/*!40000 ALTER TABLE `account_log` DISABLE KEYS */;
LOCK TABLES `account_log` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `account_log` ENABLE KEYS */;


--
-- Definition of table `swgemu`.`accounts`
--

DROP TABLE IF EXISTS `swgemu`.`accounts`;
CREATE TABLE  `swgemu`.`accounts` (
  `account_id` int(10) unsigned NOT NULL auto_increment,
  `username` varchar(32) NOT NULL,
  `password` varchar(255) NOT NULL,
  `station_id` int(10) unsigned NOT NULL,
  `created` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `active` tinyint(1) NOT NULL default '1',
  `admin_level` tinyint(1) NOT NULL default '0',
  PRIMARY KEY  USING BTREE (`account_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

--
-- Dumping data for table `swgemu`.`accounts`
--

/*!40000 ALTER TABLE `accounts` DISABLE KEYS */;
LOCK TABLES `accounts` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `accounts` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
