create or replace PROCEDURE dar_de_alta_sumistro
(n_cod_articulo VistaSuministro.articulo%TYPE,
n_cod_proveedor VistaSuministro.proveedor%TYPE,
n_cod_hotel VistaSuministro.hotel%TYPE,
n_fecha VistaSuministro.fecha%TYPE,
n_cantidad VistaSuministro.cantidad%TYPE,
n_precio VistaSuministro.precio%TYPE)
IS
    existe_suministro NUMBER;
    existe_suministro_loc NUMBER;
    cantidad_antigua VistaSuministro.cantidad%TYPE;
    ubi_hotel number;

BEGIN
    /* Busco la solicitud */
    SELECT COUNT(*) INTO existe_suministro
    FROM VistaSuministro
    WHERE hotel = n_cod_hotel AND proveedor = n_cod_proveedor AND fecha = n_fecha;



    /* Si existe la solicitud actualizo */
    IF (existe_suministro > 0) THEN
        /* Busco la localidad */
        SELECT COUNT(*) INTO existe_suministro_loc
        FROM Elepab1.Suministro
        WHERE hotel = n_cod_hotel AND proveedor = n_cod_proveedor AND fecha = n_fecha;
        IF (existe_suministro_loc > 0) THEN
            /* Obtengo la antigua cantidad */
            SELECT cantidad INTO cantidad_antigua
            FROM Elepab1.Suministro
            WHERE hotel = n_cod_hotel AND proveedor = n_cod_proveedor AND fecha = n_fecha;

            /*Actualizo */
            UPDATE Elepab1.Suministro
            SET cantidad = cantidad_antigua+n_cantidad
            WHERE hotel = n_cod_hotel AND proveedor = n_cod_proveedor AND fecha = n_fecha;
        ELSE
            /* Obtengo la antigua cantidad */
            SELECT cantidad INTO cantidad_antigua
            FROM Elepab3.Suministro
            WHERE hotel = n_cod_hotel AND proveedor = n_cod_proveedor AND fecha = n_fecha;

            /*Actualizo */
            UPDATE Elepab3.Suministro
            SET cantidad = cantidad_antigua+n_cantidad
            WHERE hotel = n_cod_hotel AND proveedor = n_cod_proveedor AND fecha = n_fecha;
        END IF;

    ELSE
    /* Creo el suministro */
        SELECT COUNT(*) INTO ubi_hotel
        FROM Elepab1.Proveedor
        Where n_cod_proveedor = cod_proveedor;
        IF (ubi_hotel > 0) THEN
            INSERT INTO Elepab1.Suministro
            VALUES(n_cod_proveedor,n_fecha,n_cod_articulo,n_cod_hotel,n_cantidad,n_precio);
        ELSE
            INSERT INTO Elepab3.Suministro
            VALUES(n_cod_proveedor,n_fecha,n_cod_articulo,n_cod_hotel,n_cantidad,n_precio);
        END IF;


    END IF;
END;