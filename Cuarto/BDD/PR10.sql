/*10. Dar de alta a un nuevo proveedor. Argumentos: Código de proveedor, nombre, y ciudad.*/
CREATE OR REPLACE PROCEDURE dar_de_alta_proveedor
(n_cod_proveedor VistaProveedor.cod_proveedor%TYPE,
n_nombre VistaProveedor.nombre%TYPE,
n_ciudad VistaProveedor.ciudad%TYPE)
IS
contador_proveedor NUMBER(4);
BEGIN
   SELECT COUNT(*) INTO contador_proveedor
   FROM VistaProveedor WHERE cod_proveedor = n_cod_proveedor;

   IF (contador_proveedor = 0) THEN
        IF(n_ciudad = 'Granada' OR n_ciudad = 'Jaén' OR n_ciudad = 'Málaga' OR n_ciudad = 'Almería') THEN
            INSERT INTO Elepab1.Proveedor
            VALUES (n_cod_proveedor,n_nombre,n_ciudad);
        ELSE
            IF(n_ciudad = 'Sevilla' OR n_ciudad = 'Cádiz' OR n_ciudad = 'Huelva' OR n_ciudad = 'Córdoba') THEN
                INSERT INTO Elepab3.Proveedor
                VALUES (n_cod_proveedor,n_nombre,n_ciudad);
            END IF;
        END IF

    ELSE
        raise_application_error(-20110, 'Ya existe un proveedor con ese código asociado');
    END IF;
END;
