----go
create database restorEN

go
use restorEN

go
create table MsStaff(
	StaffID char(5) primary key,
	StaffName varchar(50) not null,
	StaffPhone varchar(15) not null,
	StaffAddress varchar(50) not null,
	StaffSalary int not null,
	StaffGender varchar(10) not null,
	StaffDOB date not null
)

create table MsCustomer(
	CustomerID char(5) primary key,
	CustomerName varchar(50) not null,
	CustomerPhone varchar(15) not null,
	CustomerAddress varchar(50),
	CustomerGender varchar(10) not null,
	CustomerDOB date not null,
)

create table MsFood(
	FoodID char(5) primary key,
	FoodName varchar(50) not null,
	FoodPrice int not null,
	FoodCalory int not null
)


create table HeaderTransaction(
	TransactionID char(5) primary key,
	StaffID char(5) foreign key references MsStaff(StaffID),
	CustomerID char(5) foreign key references MsCustomer(CustomerID),
	TransactionDate date not null
)

create table DetailTransaction(
	TransactionID char(5) foreign key references HeaderTransaction(TransactionID),
	FoodID char(5) foreign key references MsFood(FoodID),
	Quantity int not null,
	primary key (TransactionID , FoodID)
)

go
insert MsCustomer values
('CU001','Go Seung Tak','082223451234',null,'Male','07-07-1989'),
('CU002','Cha Jung Min','08128493201','Sandang Street','Male','06-25-1982'),
('CU003','Jang Se Jin','081284932234','Jeruk Street','Female','04-09-1988'),
('CU004','Oh Soo Jeong','08124293193',null,'Female','02-10-1994'),
('CU005','Lee Seon Ho','081200030002','Agung Street','Male','02-13-1994')

insert MsStaff values
('ST001','Lee Su Hyeok','0812345678','Kemanggisan Street',20000,'Male','11-11-1999'),
('ST002','Choi Nam Ra','081937481928','Asem Street',40000,'Female','12-08-1999'),
('ST003','Nam On Jo','081912032953','Pinangsia Street',25000,'Female','11-07-2003'),
('ST004','Lee Na Yeon','0812345678','Gajah Street',60000,'Female','07-18-1994'),
('ST005','Jang Ha Ri','08293572018','Harimau Street',100000,'Female','01-09-1995')


insert MsFood values
('FO001','Whole Fried Chicken',100000,2000),
('FO002','Prime Rib Steak',300000,2500),
('FO003','Grilled Chicken with Sambal Matah',30000,500),
('FO004','Seafood Fried Rice',45000,1000),
('FO005','Vegetable With Peanut Sauce',35000,1500)

insert HeaderTransaction values
('TR001','ST001','CU001','03-13-2022'),
('TR002','ST002','CU002','03-13-2022'),
('TR003','ST003','CU003','03-15-2022'),
('TR004','ST004','CU003','03-15-2022'),
('TR005','ST005','CU004','03-16-2022'),
('TR006','ST005','CU001','03-16-2022'),
('TR007','ST002','CU002','03-20-2022'),
('TR008','ST003','CU002','03-23-2022'),
('TR009','ST001','CU005','03-24-2022'),
('TR010','ST005','CU003','03-25-2022'),
('TR011','ST003','CU002','03-27-2022'),
('TR012','ST002','CU001','04-02-2022'),
('TR013','ST001','CU004','04-04-2022'),
('TR014','ST003','CU003','04-05-2022'),
('TR015','ST005','CU002','04-07-2022')

insert DetailTransaction values
('TR001','FO001',1),
('TR001','FO002',2),
('TR002','FO003',5),
('TR002','FO004',3),
('TR003','FO005',2),
('TR004','FO001',1),
('TR005','FO002',5),
('TR005','FO004',3),
('TR006','FO003',2),
('TR007','FO002',3),
('TR008','FO001',4),
('TR009','FO004',1),
('TR010','FO005',2),
('TR011','FO002',4),
('TR011','FO001',3),
('TR011','FO003',1),
('TR012','FO005',1),
('TR013','FO003',2),
('TR014','FO002',4),
('TR015','FO001',1)

--1
	SELECT 
		StaffID,StaffName,StaffPhone,StaffDOB
	FROM MsStaff
	WHERE LEN(StaffPhone)>=11
	GO

--2
	CREATE NONCLUSTERED INDEX IX_MsFood_FoodName
	ON 
		MsFood (FoodName)
	GO

--3
	SELECT 
		CustomerName,CustomerAddress,CustomerPhone,CustomerGender
	FROM MsCustomer
	WHERE CustomerName LIKE '%in'
	GO

--4
	SELECT 
		HT.CustomerID,HT.TransactionID,CustomerName,[Customer Address] = (ISNULL(MC.CustomerAddress,'Not Inputted')),[TransactionDate] = (CONVERT(VARCHAR(11),TransactionDate,113))
	FROM HeaderTransaction HT JOIN MsCustomer MC
		ON HT.CustomerID = MC.CustomerID
	WHERE DAY(TransactionDate)>10
	GO

--5
	CREATE VIEW StaffInformation 
	AS
		SELECT 
			[StaffID] = (REPLACE(StaffID,'ST','Staff ')),
			StaffName,StaffDOB,[StaffPhone] = (STUFF(StaffPhone,1,1,'+62')),
			[StaffAge] = DATEDIFF(DAY,StaffDOB,GETDATE())/365
			--[StaffAge] = YEAR(StaffDOB)
		FROM MsStaff
	GO
--6
	CREATE VIEW TransactionHistory 
	AS
		SELECT 
			HT.TransactionID,
			StaffID,
			CustomerID,
			[TransactionDate] = (CONVERT(VARCHAR(11),TransactionDate,113)), 
			[TotalPrice] = FoodPrice * Quantity
		FROM 
			HeaderTransaction HT,
			MsFood MF,
			DetailTransaction DT
		WHERE
			HT.TransactionID = DT.TransactionID AND
			DT.FoodID = MF.FoodID AND
			MONTH(TransactionDate) >= 4 AND
			CAST (RIGHT(StaffID,1) AS int) %2 !=0
	GO

--7
	SELECT 
		CustomerID,
		CustomerName,
		CustomerAddress,
		[Last Name] = RIGHT(CustomerName,CHARINDEX(' ',REVERSE(CustomerName))),
		CustomerGender
	FROM MsCustomer
	WHERE 
		CustomerAddress IS NOT NULL AND
		CustomerAddress LIKE '%u%'
	GO

--8
	SELECT 
		FoodName,
		[First Food Name] = LEFT(FoodName,CHARINDEX(' ',FoodName,1)),
		Quantity,
		[Total Calory] = FoodCalory * Quantity,
		TransactionDate
	FROM 
		MsFood MF,
		DetailTransaction DT,
		HeaderTransaction HT
	WHERE
		MF.FoodID = DT.FoodID AND HT.TransactionID = DT.TransactionID AND
		DATENAME(MONTH,TransactionDate) LIKE 'March' AND (FoodCalory * Quantity > 2000) AND FoodName LIKE '%With%'
	GO

--9
	SELECT 
		HT.TransactionID,
		HT.CustomerID,
		CustomerName,
		[Middle Name] = SUBSTRING(CustomerName,CHARINDEX(' ',CustomerName)+1,CHARINDEX(' ',CustomerName,CHARINDEX(' ',CustomerName)+1)-1-CHARINDEX(' ',CustomerName)
		),
		[CustomerGender] = LEFT(MC.CustomerGender,1),
		[DayOfTransaction] = (DATENAME(WEEKDAY,HT.TransactionDate))
		FROM 
		MsCustomer MC,
		HeaderTransaction HT
	WHERE 
		HT.CustomerID = MC.CustomerID AND MONTH(TransactionDate) = 4
	GO

--10
	SELECT 
		[TransactionID] = (STUFF(HT.TransactionID,1,2,'Transaction ')),
		MC.CustomerName,
		MS.StaffName,
		MF.FoodName,
		DT.Quantity,
		[TransactionDate] = (CONVERT(VARCHAR(11),TransactionDate,113)), 
		[Discount] = CAST(MF.FoodPrice*DT.Quantity*0.10 AS int),
		[Total Price] = CONCAT('Rp. ', (DT.Quantity*MF.FoodPrice) - (MF.FoodPrice*DT.Quantity*0.10),'.00')
	FROM
		HeaderTransaction HT,
		MsStaff MS,
		DetailTransaction DT,
		MsFood MF,
		MsCustomer MC
	WHERE
		HT.TransactionID = DT.TransactionID AND
		HT.CustomerID = MC.CustomerID AND
		DT.FoodID = MF.FoodID AND
		HT.StaffID = MS.StaffID AND
		LEN(MF.FoodName) - LEN(REPLACE(MF.FoodName, ' ', '')) + 1 >= 4

	ORDER BY HT.TransactionID ASC
