-- Task 3. Basic queries

-- Task 3.1. Joins

-- Simple
-- Get managers
SELECT t.name, e.first_name, e.last_name
FROM OrgUnit AS ou
JOIN Team AS t
ON t.id = ou.team_id
JOIN Employee AS e
ON e.id = ou.employee_id and e.is_manager = 'TRUE'
ORDER BY t.id, e.id;

-- Self-join
-- create hierarhy: select managers and associate them with their subordinates
SELECT DISTINCT managers.first_name, managers.last_name, e.first_name, e.last_name
FROM Employee as managers
JOIN Employee as e
ON e.is_manager = 'FALSE'
JOIN OrgUnit as ou
ON ou.employee_id = managers.id
JOIN OrgUnit as ou2
ON ou2.employee_id = e.id
JOIN OrgUnit as ou3
ON ou.team_id = ou2.team_id
WHERE managers.is_manager = 'TRUE';

-- Task 3.2 Predicates

-- LIKE
-- Each team has similar phone number format, so we can get them
-- such way
SELECT (SELECT id FROM Team where name = 'Engineering'), e.id
FROM Employee AS e
WHERE e.phone LIKE '2%';


-- Task 3.3 Case
-- print labels for inventory depending on whats left
SELECT name, quantity, "Level" =
  CASE
    WHEN quantity = 0 THEN 'Empty'
    WHEN quantity < 5 THEN 'Low'
    WHEN quantity < 7 THEN 'Medium'
  ELSE 'Good'
  END
FROM Inventory
ORDER BY Inventory.quantity;

-- Task 3.6 Datetimes
INSERT INTO ServiceOrder
VALUES (1, SYSDATETIME(), 1), (1, DATETIME2FROMPARTS(2016, 03, 12, 12, 50, 10, 0, 0),  2)
