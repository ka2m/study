-- WITH SCHEMABINDING
CREATE VIEW dbo.AssigneeByTasksCount WITH ENCRYPTION
AS
SELECT TOP (100) PERCENT e.first_name, e.last_name, COUNT(*) AS 'Tasks'
FROM dbo.Progress AS p INNER JOIN
dbo.Status AS s ON s.id = p.status INNER JOIN
dbo.Employee AS e ON e.id = p.assignee
WHERE (s.name <> 'Done')
GROUP BY e.id, e.first_name, e.last_name
ORDER BY 'Tasks' DESC
-- WITH CHECK OPTION

