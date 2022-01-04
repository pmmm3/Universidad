CREATE VIEW  VistaHotel AS
SELECT * from Elepab1.Hotel
UNION ALL
SELECT * from Elepab2.Hotel
UNION ALL
SELECT * from Elepab3.Hotel
UNION ALL
SELECT * from Elepab4.Hotel;

CREATE VIEW  VistaHotel_capacidad AS
SELECT * from Elepab1.Hotel_capacidad
UNION ALL
SELECT * from Elepab2.Hotel_capacidad
UNION ALL
SELECT * from Elepab3.Hotel_capacidad
UNION ALL
SELECT * from Elepab4.Hotel_capacidad;


CREATE VIEW  VistaHistorico AS
SELECT * from Elepab1.registro_historico
UNION ALL
SELECT * from Elepab2.registro_historico
UNION ALL
SELECT * from Elepab3.registro_historico
UNION ALL
SELECT * from Elepab4.registro_historico;




CREATE VIEW  VistaProveedor AS
SELECT * from Elepab1.Proveedor
UNION ALL
SELECT * from Elepab3.Proveedor;

CREATE VIEW  VistaSuministro AS
SELECT * from Elepab1.Suministro
UNION ALL
SELECT * from Elepab3.Suministro;

CREATE VIEW  VistaArticulo AS
SELECT * from Elepab1.Articulo
UNION ALL
SELECT * from Elepab3.Articulo;

CREATE VIEW  VistaEmpleado AS
SELECT * from Elepab1.Empleado
UNION ALL
SELECT * from Elepab2.Empleado
UNION ALL
SELECT * from Elepab3.Empleado
UNION ALL
SELECT * from Elepab4.Empleado;


CREATE VIEW  VistaReserva  AS
SELECT * from Elepab1.Reserva
UNION ALL
SELECT * from Elepab2.Reserva
UNION ALL
SELECT * from Elepab3.Reserva
UNION ALL
SELECT * from Elepab4.Reserva;

CREATE VIEW  VistaCliente AS
SELECT * from Elepab1.Cliente
UNION ALL
SELECT * from Elepab2.Cliente
UNION ALL
SELECT * from Elepab3.Cliente
UNION ALL
SELECT * from Elepab4.Cliente;
