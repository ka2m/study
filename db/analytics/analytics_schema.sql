CREATE TABLE dimDate
( KeyDate BIGINT NOT NULL,
      [Date] DATE NOT NULL,
      [Year] INT NOT NULL,
      [Quarter] INT NOT NULL,
      [Month] INT NOT NULL,
      [Week] INT NOT NULL,
      [Day] INT NOT NULL,
      [MonthName] NVARCHAR(20) NOT NULL,
      [DayName] NVARCHAR(20) NOT NULL,
      CONSTRAINT PKDW_1 PRIMARY KEY (KeyDate)
      )


CREATE TABLE DeviceType (
      id INT IDENTITY(1,1) PRIMARY KEY,
      name varchar(60) NOT NULL
) ON [SlowGrowing];

CREATE TABLE DeviceManifacturer (
      id INT IDENTITY(1,1) PRIMARY KEY,
      name varchar(60) NOT NULL
) ON [SlowGrowing];


CREATE TABLE Inventory (
      id INT IDENTITY(1,1) PRIMARY KEY,
      name varchar(60) NOT NULL,
      quantity INT NOT NULL,
      price INT NOT NULL
) ON [Frequently_Requested];

CREATE TABLE ServiceOrder (
       id INT IDENTITY(1, 1) PRIMARY KEY,
       dt_id INT NOT NULL,
       dm_id INT NOT NULL,
       descr VARCHAR(1000) NOT NULL,
       open_date DATETIME NOT NULL
) ON [Fast_Growing];

CREATE TABLE InventoryAllocation (
       id INT IDENTITY(1, 1) PRIMARY KEY,
       inv_id INT NOT NULL,
       so_id INT NOT NULL
) ON [Frequently_Requested];


CREATE PARTITION FUNCTION PartFunctionInventoryUsage_Date (bigint)
AS RANGE RIGHT FOR VALUES (20130101, 20140101, 20150101, 20160101)

CREATE TABLE FactInventoryUsage (
       id INT IDENTITY(1, 1) PRIMARY KEY,
       ServiceOrder_id INT NOT NULL,
       InventoryAllocation_id INT NOT NULL
)

ALTER TABLE FactInventoryUsage
ADD CONSTRAINT FK_IA FOREIGN KEY (InventoryAllocation_id) REFERENCES InventoryAllocation(id)

ALTER TABLE FactInventoryUsage
ADD CONSTRAINT FK_SO FOREIGN KEY (ServiceOrder_id) REFERENCES ServiceOrder(id)

CREATE TABLE FactInvetoryUsageDenormalized (
       id INT IDENTITY(1, 1) PRIMARY KEY,
       dm_name VARCHAR(60) NOT NULL,
       dt_name VARCHAR(60) NOT NULL,
       inv_item_name VARCHAR(60) NOT NULL,
       inv_item_price INT NOT NULL,
       open_date DATETIME NOT NULL,
       issue_descr VARCHAR(1000) NOT NULL
)

ALTER TABLE ServiceOrder
ADD CONSTRAINT FK_SO_DT FOREIGN KEY (dt_id) REFERENCES DeviceType(id)

ALTER TABLE ServiceOrder
ADD CONSTRAINT FK_SO_DM FOREIGN KEY (dm_id) REFERENCES DeviceManifacturer(id)

ALTER TABLE InvnetoryAllocation
ADD CONSTRAINT FK_IA_INV FOREIGN KEY (inv_id) REFERENCES Inventory(id)

ALTER TABLE InventoryAllocation
ADD CONSTRAINT FK_IA_SO FOREIGN KEY (so_id) REFERENCES ServiceOrder(id)
CREATE INDEX NOCL_DT_Name
ON DeviceType([id]) INCLUDE ([name])

CREATE INDEX NOCL_DM_Name
ON DeviceManifacturer([id]) INCLUDE ([name])

CREATE INDEX NOCL_INV_Name_wAll
ON Invnetoy([name]) INCLUDE ([quantity], [price])

CREATE NONCLUSTERED INDEX NOCL_INV_ID
ON Inventory([id])

CREATE INDEX CL_SO_dATE ON ServiceOrder([open_date])

CREATE NONCLUSTERED INDEX NOCL_IA_ID
ON InventoryAllocation([id])

CREATE NONCLUSTERED INDEX NOCL_FACT_ALL
ON FactInventoryUsage([ServiceOrder_id]) INCLUDE ([InvnetoryAllocation_id])


CREATE TABLE dimDate
( KeyDate BIGINT NOT NULL,
  [Date] DATE NOT NULL,
  [Year] INT NOT NULL,
  [Quarter] INT NOT NULL,
  [Month] INT NOT NULL,
  [Week] INT NOT NULL,
  [Day] INT NOT NULL,
  [MonthName] NVARCHAR(20) NOT NULL,
  [DayName] NVARCHAR(20) NOT NULL,
  CONSTRAINT PKDW_1 PRIMARY KEY (KeyDate)
  )

ALTER TABLE FactInvetoryUsageDenormalized
DROP COLUMN open_date

ALTER TABLE FactInvetoryUsageDenormalized
ADD open_date BIGINT NOT NULL

ALTER TABLE FactInvetoryUsageDenormalized
ADD CONSTRAINT FK_DDATE FOREIGN KEY (open_date) REFERENCES DimDate (KeyDate)

ALTER TABLE FactInventoryUsage
DROP COLUMN open_date

ALTER TABLE FactInventoryUsage
ADD open_date BIGINT NOT NULL

ALTER TABLE FactInventoryUsage
ADD CONSTRAINT FK_DATE2 FOREIGN KEY (open_date) REFERENCES DimDate (KeyDate)

