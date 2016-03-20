USE serviceCenterMain;

-- basic statuses of orders
INSERT INTO Status
VALUES('New'), ('Open'), ('In analysis'), ('In progress'), ('In verification'), ('Done'), ('Closed');

-- main departments
INSERT INTO Team
VALUES ('Administration'), ('Engineering'), ('Reception');


-- all default employees
INSERT INTO Employee
VALUES ('Vlad', 'Slepukhin', 'vslepukhin@sc.ru', '3000', 'B4FQINM3IX', 'TRUE');

INSERT INTO Employee
VALUES ('Joe', 'Portier', 'jportier@sc.ru', '1000', 'B4FQINM3IX', 'FALSE');

INSERT INTO Employee
VALUES ('Core', 'Fixer', 'cfixer@sc.ru', '2001', 'P5C5MZKUDW', 'TRUE');

INSERT INTO Employee
VALUES ('Max', 'Fix', 'mfix@sc.ru', '2002', 'DU0QBRHNFW', 'FALSE');

INSERT INTO Employee
VALUES ('Marie', 'Xif', 'mxif@sc.ru', '2003', '9CKL8RGHAL', 'FALSE');

INSERT INTO Employee
VALUES ('Helen', 'Overwelcomed', 'hoverwelcomed@sc.ru', '1001', 'UVWBU6Q87J', 'FALSE');

INSERT INTO Employee
VALUES ('Chirsten', 'Accountable', 'caccountable@sc.ru', '3050', 'ZJYDJYZ3D1', 'FALSE');

INSERT INTO Employee
VALUES ('Chip', 'Bit', 'cbit@sc.ru', '2051', 'NHAFIPATHK', 'FALSE');

INSERT INTO Employee
VALUES ('Don', 'Garage', 'dgarage@sc.ru', '3001', '7TNPCKMVCV', 'FALSE');

INSERT INTO Employee
VALUES ('Corgi', 'Recept', 'crecept@sc.ru', '1050', 'B4BMINOPD2', 'TRUE');

-- team and employee connctetion
INSERT INTO OrgUnit
( team_id,
  employee_id
)
SELECT (SELECT id FROM Team where name = 'Reception'), e.id
FROM Employee AS e
WHERE e.phone LIKE '1%';

INSERT INTO OrgUnit
( team_id,
  employee_id
)
SELECT (SELECT id FROM Team where name = 'Engineering'), e.id
FROM Employee AS e
WHERE e.phone LIKE '2%';

INSERT INTO OrgUnit
( team_id,
  employee_id
)
SELECT (SELECT id FROM Team where name = 'Administration'), e.id
FROM Employee AS e
WHERE e.phone LIKE '3%';


-- some test inventory
INSERT INTO Inventory
VALUES ('iPhone_5c_Screen', 8);

INSERT INTO Inventory
VALUES ('iPhone_6_Screen', 1);

INSERT INTO Inventory
VALUES ('Nexus_5_Battery', 5);

INSERT INTO Inventory
VALUES ('Nexus_6p_Cellular_Module', 9);

INSERT INTO Inventory
VALUES ('Nexus_6p_Battery', 1);

INSERT INTO Inventory
VALUES ('iPhone_4_Charge_Module', 1);

INSERT INTO Inventory
VALUES ('iPhone_6Plus_Buttons', 2);


-- some device types
INSERT INTO DeviceType
VALUES ('Phone')
INSERT INTO DeviceType
VALUES ('Tablet')
INSERT INTO DeviceType
VALUES ('PC')
INSERT INTO DeviceType
VALUES ('Laptop')
INSERT INTO DeviceType
VALUES ('Mac/MacBook')
INSERT INTO DeviceType
VALUES ('Other')
