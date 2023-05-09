-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: May 09, 2023 at 01:59 AM
-- Server version: 10.6.12-MariaDB-0ubuntu0.22.04.1
-- PHP Version: 8.1.2-1ubuntu2.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `ArtGalleryProject`
--

-- --------------------------------------------------------

--
-- Table structure for table `Artworks`
--

CREATE TABLE `Artworks` (
  `ArtworkID` int(11) NOT NULL,
  `Title` varchar(100) NOT NULL,
  `Artist` varchar(100) NOT NULL,
  `Year` varchar(20) NOT NULL,
  `Path` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Artworks`
--

INSERT INTO `Artworks` (`ArtworkID`, `Title`, `Artist`, `Year`, `Path`) VALUES
(23, 'Dancing%20at%20the%20Louvre', 'Faith%20Ringgold', '1991', 'https%3A%2F%2Fcollection.gundgallery.org%2FMedia%2Fimages%2F2017_05_06-Ringgold_2021Update.jpg'),
(28, 'The%20Builders%20Family%20', 'Jacob%20Lawrence', '1993', 'https%3A%2F%2Fcollection.gundgallery.org%2FMedia%2Fimages%2F2017_05_05-Lawrence-Image.jpg'),
(29, 'A%20Girl%20with%20a%20Knife%20Nosepin%2C%20Brooklyn%2C%20NY', 'Dawoud%20Bey', '1990', 'https%3A%2F%2Fcollection.gundgallery.org%2FMedia%2Fimages%2F2021_05_01-Bey-Image.jpg');

-- --------------------------------------------------------

--
-- Table structure for table `Comments`
--

CREATE TABLE `Comments` (
  `ID` int(11) NOT NULL,
  `Name` varchar(50) NOT NULL DEFAULT 'Anonymous',
  `CommentText` text NOT NULL,
  `ArtworkID` int(11) NOT NULL,
  `SelectionXCoord` double DEFAULT NULL,
  `SelectionYCoord` double DEFAULT NULL,
  `SelectionWidth` double NOT NULL DEFAULT 0,
  `Rating` int(11) NOT NULL DEFAULT 0,
  `isPinned` tinyint(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Comments`
--

INSERT INTO `Comments` (`ID`, `Name`, `CommentText`, `ArtworkID`, `SelectionXCoord`, `SelectionYCoord`, `SelectionWidth`, `Rating`, `isPinned`) VALUES
(64, 'fdslw34%2090fsd%60!fnds2%20%5C20', '%3A\')%20%3F', 24, 1, 1, 100, 0, 0),
(71, 'Ooni', 'This%20piece%20is%20actually%20the%20first%20in%20a%20series%20of%2012%20%22story%20quilts%2C%22%20telling%20a%20fictional%20tale%20of%20a%20young%20black%20woman%20named%20Willia%20Marie%20Simone%2C%20and%20her%20interactions%20with%20the%2020th%20century%20art%20world.%20It%20deals%20with%20the%20struggle%20for%20recognition%20as%20a%20black%20artist%20in%20an%20art%20world%20dominated%20by%20white%20norms%20and%20standards%20of%20beauty.%20(Source%3A%20Khan%20Academy)', 23, 1, 1, 100, 4, 1),
(72, 'Ooni', 'This%20artwork\'s%20title%20is%20fascinatingly%20similar%20to%20the%20title%20of%20a%20MUCH%20earlier%20Jacob%20Lawrence%20piece%2C%20his%201974%20piece%2C%20titled%20%22Builders%20(The%20Family)%22%20(UMMA%20Exchange)%20or%20%22The%20Builders%20(The%20Family)%22%20(Artsy.net).%20I\'m%20not%20sure%20exactly%20what%20the%20connection%20is%2C%20but%20I%20know%20Lawrence%20focused%20a%20lot%20on%20builders%20in%20his%20post-70\'s%20works...', 28, 1, 1, 100, 40, 0),
(73, 'Evil%20Man', 'I%20hate%20artwork!%20I%20think%20we%20should%20BAN%20art!', 23, 1, 1, 100, -6, 0),
(74, 'Jack', 'yo%20that\'s%20the%20mona%20lisa%20right%20there%20i%20know%20that%20one', 23, 1, 1, 100, 3, 0),
(75, 'test', '%22%20\'%20%22%20%25%2F%2F203', 29, 1, 1, 100, 0, 0),
(76, 'Elizabeth', 'They%20shouldn\'t%20be%20dancing%20in%20the%20Louvre%2C%20what%20if%20they%20knock%20one%20of%20the%20paintings%20off%20the%20wall', 23, 1, 1, 100, 0, 0),
(77, 'Jade', '%40Elizabeth%20I%20think%20that\'d%20be%20funny%20if%20that%20happened', 23, 1, 1, 100, 0, 0),
(78, 'Elizabeth', '%40Jade%20%3F%3F%3F%3F%3F%3F%3F%3F%3F%3F%3F%3F%3F%3F%3F%3F%3F', 23, 1, 1, 100, 0, 0),
(80, 'Ooni', 'Hello!!', 28, 1, 1, 100, -10, 0),
(81, 'Lebron', 'Alright%E2%80%A6%20this%20is%20literally%20awesome', 23, 1, 1, 100, 50, 0);

-- --------------------------------------------------------

--
-- Table structure for table `Tokens`
--

CREATE TABLE `Tokens` (
  `ID` int(11) NOT NULL,
  `Token` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Artworks`
--
ALTER TABLE `Artworks`
  ADD PRIMARY KEY (`ArtworkID`);

--
-- Indexes for table `Comments`
--
ALTER TABLE `Comments`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `Tokens`
--
ALTER TABLE `Tokens`
  ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Artworks`
--
ALTER TABLE `Artworks`
  MODIFY `ArtworkID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=36;

--
-- AUTO_INCREMENT for table `Comments`
--
ALTER TABLE `Comments`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=82;

--
-- AUTO_INCREMENT for table `Tokens`
--
ALTER TABLE `Tokens`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=96;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
