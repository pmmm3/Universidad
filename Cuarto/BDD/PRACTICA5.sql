/*
1. “Listar los hoteles (nombre y ciudad) de las provincias de Granada, Huelva o
Almería, y los proveedores (nombre y ciudad), a los que se le ha suministrado
“Queso” o “Mantequilla” entre el 12 de mayo de 2021 y el 28 de mayo de 2021.*/
SELECT VistaHotel.nombre as nombre_hotel, VistaHotel.ciudad as ciudad_hotel,
    VistaProveedor.nombre as nombre_proveedor,
    VistaProveedor.ciudad as ciudad_proveedor

FROM VistaHotel h ,VistaSuministro s,VistaProveedor p,VistaArticulo a
WHERE h.cod_hotel = s.hotel
AND p.cod_proveedor = s.proveedor
AND a.cod_articulo = s.articulo
AND (h.provincia = 'Granada' OR h.provincia = 'Huelva' OR h.provincia = 'Almería')
AND (a.nombre = 'Queso' OR a.nombre = 'Mantequilla')
AND (s.fecha > '12-05-2021' AND s.fecha < '28-05-2021');

/*
2. Dado por teclado el código de un productor, “Listar los productos (nombre), los
hoteles (nombre y ciudad) y la cantidad total de cada producto, suministrados por
dicho productor a hoteles de las provincias de Jaén o Almería”. */
SELECT VistaArticulo.nombre as nombre_producto,
    VistaHotel.nombre as nombre_hotel,
    VistaHotel.ciudad as ciudad_hotel,
    SUM(VistaSuministro.cantidad)
FROM VistaArticulo a , VistaHotel h, VistaSuministro s
WHERE a.cod_articulo = s.articulo
AND h.cod_hotel = s.hotel
AND h.provincia IN ('Jaén','Almería')
AND s.proveedor = &xProveedor
AND s.cantidad > 0;


/*
3. Dado por teclado el código de un hotel, “Listar los clientes (nombre y teléfono),
que tengan registrada más de una reserva en dicho hotel”.
*/
SELECT VistaCliente.nombre,VistaCliente.telefono
FROM VistaCliente c, VistaReserva r
WHERE c.cod_cliente = r.cod_cliente
AND  r.cod_hotel = &xcod_hotel
GROUP BY (c.nombre, c.telefono , c.cod_cliente)
HAVING COUNT(r.cod_cliente)>1;

