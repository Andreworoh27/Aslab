CREATE DATABASE CATime
USE CATime
GO

--1
	--a
	CREATE TABLE MsStaff (
		StaffID CHAR(5) CHECK(StaffID LIKE('ST[0-9][0-9][0-9]')) PRIMARY KEY,
		StaffName VARCHAR(100) NOT NULL,
		StaffGender CHAR(1) NOT NULL,
		StaffPhone CHAR (12) CHECK ( StaffPhone LIKE('0[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]')),
		StaffAddress VARCHAR(100),
		StaffSalary INTEGER CHECK (StaffSalary BETWEEN 4500000 AND 9000000),

		CONSTRAINT StaffGenderCons CHECK (StaffGender IN ('F','M')) 
	)
	GO

	--b
	CREATE TABLE MsCustomer(
		CustomerID CHAR (5) CHECK (CustomerID LIKE('CU[0-9][0-9][0-9]')) PRIMARY KEY,
		CustomerName VARCHAR(100) NOT NULL,
		CustomerGender CHAR (1) CHECK (CustomerGender IN ('F','M')) NOT NULL,
		CustomerPhone CHAR (12) CHECK (CustomerPhone LIKE('0[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]')),
		CustomerAddress VARCHAR(100) 
		
		CONSTRAINT CustomerAddressCons CHECK(CustomerAddress LIKE ('%street'))
	)
	GO

	--c
	CREATE TABLE MsDrink(
		DrinkID CHAR(5) CHECK (DrinkID LIKE ('DR[0-9][0-9][0-9]')) PRIMARY KEY,
		Quantity INTEGER CHECK (Quantity > 0 ),
		Rating INTEGER CHECK (Rating BETWEEN 1 AND 5)
	)
	GO

	--d
	CREATE TABLE TrTransactionHeader (
		TransactionID CHAR (5) CHECK (TransactionID LIKE ('TR[0-9][0-9][0-9]')) PRIMARY KEY,
		CustomerID CHAR (5) REFERENCES MsCustomer(CustomerID),
		StaffID CHAR (5) REFERENCES MsStaff(StaffID)
	)
	GO

	--e
	CREATE TABLE TrTransactionDetail(
		TransactionID CHAR (5) REFERENCES TrTransactionHeader (TransactionID),
		DrinkID CHAR (5) REFERENCES MsDrink (DrinkID),
		Quantity INTEGER CHECK (Quantity > 5),
		PRIMARY KEY (TransactionID,DrinkID)
	)
	GO

--2
	--a
	ALTER TABLE MsDrink
	ADD DrinkName VARCHAR(50)
	CONSTRAINT DrinkNameCons
    CHECK (LEN(DrinkName) BETWEEN 6 AND 30),
    CHECK (DrinkName LIKE '%Tea' OR DrinkName LIKE '%Coffee')

	--b
	ALTER TABLE MsDrink 
	ADD DrinkDescription VARCHAR(100) 
	CONSTRAINT DrinkDescCons
		CHECK (LEN(DrinkDescription)>10)
	GO

	--c
	ALTER TABLE MsStaff 
	ADD InsertNumber INTEGER IDENTITY(1,1)
	GO

	--d
	ALTER TABLE MsStaff
	DROP CONSTRAINT StaffGenderCons 
	GO

	ALTER TABLE MsStaff
	ALTER COLUMN StaffGender VARCHAR(10)
	GO

	--e
	ALTER TABLE MsCustomer
	ADD CustomerEmail VARCHAR(50) UNIQUE 
	GO

	ALTER TABLE MsCustomer
	ADD CONSTRAINT CustomerEmailCons@ CHECK (CustomerEmail LIKE '%@%')
	GO

	ALTER TABLE MsCustomer
	ADD CONSTRAINT CustomerEmailConsName CHECK ((LOWER (SUBSTRING(CustomerName,0,(CHARINDEX(' ',CustomerName)-1)))) = LOWER  (SUBSTRING(CustomerEmail,0,(CHARINDEX('@',CustomerEmail)-1))))
	GO

	ALTER TABLE MsCustomer
	ADD CONSTRAINT CustomerEmailConsLower CHECK((BINARY_CHECKSUM(CustomerEmail) = BINARY_CHECKSUM(LOWER(CustomerEmail))))
	GO

	--f
	ALTER TABLE MsCustomer
	ADD CustomerLevel VARCHAR(10)
	GO
	ALTER TABLE MsCustomer
	ADD CONSTRAINT CustomerLevelCons CHECK (CustomerLevel LIKE 'Bronze' OR CustomerLevel LIKE 'Silver' OR CustomerLevel LIKE 'Gold')
	GO

--3
	--a
	BEGIN TRAN
	INSERT INTO MsStaff
	VALUES 
	('ST001','Cristoper Anderson','Male','085294883113','Potato Street','7000000'),
	('ST002','Leszek Nisus','Male','085234632343','Broccoli Street','4700000'),
	('ST003','Linnie','Female','085294379399','Cabbage Street','5500000'),
	('ST004','Kelsey','Female','085274883399','Potato Street','7600000'),
	('ST005','Tresha','Male','085294234899','Potato Street','8000000')
	ROLLBACK

	BEGIN TRAN
	INSERT INTO MsCustomer
	VALUES 
	('CU001','Felix Gozali','M','085347183913','Goldfish Street','felix@gmail.com','Gold'),
	('CU002','Lina Weiss','F','085345186999','Clownfish Street','lina@gmail.com','Silver'),
	('CU003','Tatiana Eva','F','085347755933','GoldFish Street','tatiana@gmail.com','Bronze'),
	('CU004','Yorick Harish','M','085357839933','Otter Street','yorick@gmail.com','Bronze'),
	('CU005','Isac Zahira','M','085352394823','Seal Street','isac@gmail.com','Gold')
	ROLLBACK

	BEGIN TRAN
	INSERT INTO MsDrink (DrinkID,Quantity,Rating,DrinkDescription,DrinkName)
	VALUES
	('DR001','10','4','This is a drink with the taste of matcha.','Matcha Green Tea'),
	('DR002','78','3','This is an americano made out of quality coffee beans.','Americano Coffee'),
	('DR003','100','3','This is a tea of British Origin','English Breakfast Tea'),
	('DR004','140','5','Tea mixed with brown sugar and boba made out of tapioca.','Brown Sugar Boba Tea'),
	('DR005','36','5','A latte with some pieces of biscuit','Biscuit Latte Coffee')
	ROLLBACK

	BEGIN TRAN
	INSERT INTO TrTransactionHeader
	VALUES
	('TR001','CU001','ST001'),
	('TR002','CU001','ST001'),
	('TR003','CU001','ST001'),
	('TR004','CU003','ST001'),
	('TR005','CU003','ST001'),
	('TR006','CU003','ST001'),
	('TR007','CU004','ST001')
	ROLLBACK

	BEGIN TRAN
	INSERT INTO TrTransactionDetail (TransactionID,DrinkID,Quantity)
	VALUES
	('TR001','DR001','10'),
	('TR002','DR002','18'),
	('TR003','DR003','27'),
	('TR004','DR004','48'),
	('TR005','DR005','38'),
	('TR006','DR001','58'),
	('TR007','DR002','42')
	ROLLBACK

--4 
	BEGIN TRAN
	UPDATE MsStaff SET StaffSalary = (
		CASE
			WHEN StaffName LIKE 'C%' THEN '6000000'
			ELSE StaffSalary
		END
	)
	ROLLBACK

--5
	BEGIN TRAN 
	UPDATE MsStaff SET StaffGender = (
		CASE 
			WHEN StaffGender LIKE 'Female' THEN 'F'
			ELSE  'M'
		END
	)
	ROLLBACK
	
--6
	BEGIN TRAN 
	UPDATE MsStaff SET StaffSalary = (
		CASE
			WHEN (StaffPhone LIKE '%99') AND (CHARINDEX(' ',StaffName) = 0)  AND (LEN(StaffAddress) BETWEEN 5 AND 25) THEN '6900000'
			ELSE StaffSalary
		END
	)
	ROLLBACK

--7
	SELECT TOP 1 StaffID,
	(
		CASE 
			WHEN StaffGender LIKE 'Male' THEN CONCAT ('Mr.',StaffName)
			ELSE CONCAT ('Mrs.',StaffName)
		END
	),
	(STUFF (StaffPhone,1,1,'+62')),
	StaffAddress
	FROM MsStaff 
	WHERE (CHARINDEX(' ',StaffName) = 0)

--8
	ALTER TABLE MsCustomer
	DROP CONSTRAINT CustomerAddressCons

--9 
	BEGIN TRAN
	DELETE FROM MsStaff WHERE StaffSalary BETWEEN 4500000 AND 6000000
	ROLLBACK

--10
	SELECT (
		CASE
			WHEN DrinkName LIKE '%Tea' THEN REVERSE(SUBSTRING(REVERSE(DrinkName),4,LEN(DrinkName)))
			ELSE REVERSE(SUBSTRING(REVERSE(DrinkName),7,LEN(DrinkName)))
		END
	),
	(
		CONCAT(Quantity,' item(s)')
	),
	(
		FORMAT(Rating,'##.00')
	)
	FROM MsDrink

--delete all
DROP TABLE TrTransactionDetail
DROP TABLE TrTransactionHeader
DROP TABLE MsDrink
DROP TABLE MsCustomer
DROP TABLE MsStaff

--view all
SELECT * FROM TrTransactionDetail
SELECT * FROM TrTransactionHeader
SELECT * FROM MsDrink
SELECT * FROM MsCustomer
SELECT * FROM MsStaff