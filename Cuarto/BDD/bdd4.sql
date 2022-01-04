CREATE TABLE Hotel (
   cod_hotel NUMBER (3) PRIMARY KEY,
   nombre VARCHAR(50) NOT NULL,
   hab_doble NUMBER (2) NOT NULL,
   hab_sencilla NUMBER (2) NOT NULL,
   ciudad VARCHAR(30) NOT NULL,
   provincia VARCHAR(10) NOT NULL,
   director NUMBER (3) NOT NULL
);
CREATE TABLE Cliente(
   cod_cliente NUMBER(3) PRIMARY KEY,
   DNI NUMBER(8) NOT NULL unique,
   nombre VARCHAR(30) NOT NULL,
   telefono NUMBER(9) NOT NULL unique
);

CREATE TABLE Empleado (
   cod_empleado NUMBER  (3) PRIMARY KEY,
   DNI NUMBER (8) NOT NULL UNIQUE,
   nombre VARCHAR(30) NOT NULL,
   direccion VARCHAR(100) NOT NULL,
   telefono NUMBER (9) NOT NULL UNIQUE,
   fecha_contrato DATE NOT NULL,
   Salario NUMBER (6,2) NOT NULL,
   hotel_actual NUMBER (3),
   fecha_inicio DATE
);
ALTER TABLE Hotel ADD FOREIGN KEY (director) REFERENCES Empleado (cod_empleado);
ALTER TABLE Empleado ADD FOREIGN KEY (hotel_actual) REFERENCES Hotel (cod_hotel);
CREATE TABLE Reserva (
   entrada DATE NOT NULL,
   salida DATE NOT NULL,
   hab VARCHAR(10) NOT NULL,
   precio NUMBER(5,2) NOT NULL,
   hotel NUMBER (3),
   cliente NUMBER (3) ,
   FOREIGN KEY (cliente)REFERENCES Cliente(cod_cliente),
   FOREIGN KEY (hotel) REFERENCES Hotel(cod_hotel),
   PRIMARY KEY (entrada, hotel, cliente)
);
CREATE TABLE Hotel_capacidad(
	cod_hotel NUMBER(3) PRIMARY KEY,
    FOREIGN KEY (cod_hotel) REFERENCES Hotel(cod_hotel),
	hab_sencilla NUMBER(2) NOT NULL,
	hab_doble NUMBER(2) NOT NULL
);
CREATE TABLE registro_historico (
	cod_empleado NUMBER  (3),
	cod_hotel NUMBER (3),
	fecha_inicio DATE,
	fecha_fin DATE,
	PRIMARY KEY (cod_empleado, cod_hotel, fecha_inicio)
);
GRANT ALL ON Hotel TO Elepab1;
GRANT ALL ON Hotel TO Elepab3;
GRANT ALL ON Hotel TO Elepab2;

GRANT ALL ON Hotel_capacidad TO Elepab1;
GRANT ALL ON Hotel_capacidad TO Elepab3;
GRANT ALL ON Hotel_capacidad TO Elepab2;

GRANT ALL ON registro_historico TO Elepab2;
GRANT ALL ON registro_historico TO Elepab3;
GRANT ALL ON registro_historico TO Elepab1;

GRANT ALL ON Empleado TO Elepab1;
GRANT ALL ON Empleado TO Elepab3;
GRANT ALL ON Empleado TO Elepab2;

GRANT ALL ON Cliente TO Elepab1;
GRANT ALL ON Cliente TO Elepab3;
GRANT ALL ON Cliente TO Elepab2;

GRANT ALL ON Reserva TO Elepab1;
GRANT ALL ON Reserva TO Elepab3;
GRANT ALL ON Reserva TO Elepab2;