USE [master]
GO

CREATE DATABASE [serviceCenterAnalytics]
CONTAINMENT = NONE
ON PRIMARY
( name = N'scAnalytics', FILENAME= N'C:\SCA\scA.mdf', SIZE = 51200 KB,
  MAXSIZE = UNLIMITED, FILEGROWTH = 10240KB )
  LOG ON
( name = N'scAnalytics_log', FILENAME= N'C:\SCA\scA_log.ldf', SIZE = 51200 KB,
  MAXSIZE = 2GB, FILEGROWTH = 10%)
  GO

ALTER DATABASE [serviceCenterAnalytics] SET COMPATIBILITY_LEVEL = 110
GO
ALTER DATABASE [serviceCenterAnalytics] SET AUTO_SHRINK OFF
GO
ALTER DATABASE [serviceCenterAnalytics] SET RECOVERY SIMPLE WITH NO_WAIT
GO

ALTER DATABASE [serviceCenterAnalytics]
ADD FILE ( NAME = N'scA_FastGrowing',
           FILENAME = N'C:\SCA\scA_fastGrowing.ndf',
           SIZE = 358400 KB,
           FILEGROWTH = 51200 KB)
TO FILEGROUP [Fast_Growing]
GO


ALTER DATABASE [serviceCenterAnalytics] ADD FILEGROUP [Frequently_Requested]
GO

ALTER DATABASE [serviceCenterAnalytics]
ADD FILE ( NAME = N'scA_FrequentlyRequested',
           FILENAME = N'C:\SCA\scA_FreqRequeted.ndf',
           SIZE = 204800 KB,
           FILEGROWTH = 10240 KB)
TO FILEGROUP [Frequently_Requested]
GO

ALTER DATABASE [serviceCenterAnalytics] ADD FILEGROUP [Indices]
GO

ALTER DATABASE [serviceCenterAnalytics]
ADD FILE ( NAME = N'scA_Indices',
           FILENAME = N'C:\SCA\scA_Indices.ndf',
           SIZE = 30720 KB,
           FILEGROWTH = 5120 KB)
TO FILEGROUP [Indices]
GO

ALTER DATABASE [serviceCenterAnalytics] ADD FILEGROUP [MyDefault]
GO

ALTER DATABASE [serviceCenterAnalytics]
ADD FILE ( NAME = N'scA_MyDefault',
           FILENAME = N'C:\SCA\scA_MyDefault.ndf',
           SIZE = 5120 KB,
           FILEGROWTH = 5120 KB)
TO FILEGROUP [MyDefault]
GO


ALTER DATABASE [serviceCenterAnalytics] ADD FILEGROUP [SlowGrowing]
GO

ALTER DATABASE [serviceCenterAnalytics]
ADD FILE ( NAME = N'scA_SlowGrowing',
           FILENAME = N'C:\SCA\scA_SlowGrowing.ndf',
           SIZE = 5120 KB,
           FILEGROWTH = 1024 KB)
TO FILEGROUP [SlowGrowing]
GO

ALTER DATABASE [serviceCenterAnalytics] MODIFY FILEGROUP [MyDefault] DEFAULT
GO

