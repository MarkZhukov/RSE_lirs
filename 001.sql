sql

CREATE TABLE employ (
id int not null primary key;
name varchar(20);
salary int;
manager_id int;
department_id int;
)


INSERT INTO employ (id,name,salary)
values(5,'seriy',8), (6,'rom',40)


SELECT name FROM employ WHERE name='vasya'


UPDATE employ SET salary=20 WHERE name = 'vasya'


UPDATE employ SET department_id=1  //всем строкам


SELECT avg(salary) FROM employ 
GROUP BY department_id HAVING avg(salary) > 10


ALTER TABLE employ ADD CONSTRAINT manager_employ 
foreign key(manager_id) references employ(id)


SELECT a.name, b.salary, a.salary AS manager_salary FROM employ
AS a JOIN employ AS b ON a.id = b.manager_id WHERE a.salary < b.salary



