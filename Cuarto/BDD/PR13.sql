/*  Dar de baja suministros. Argumentos: Código del hotel que solicitó el suministro,
código del artículo y, opcionalmente, fecha del suministro. Si no se indica la fecha
de suministro, se darán de baja todos los suministros solicitados por el hotel de
ese artículo al proveedor. */

CREATE OR REPLACE PROCEDURE dar_de_baja_suministro
(n_cod_hotel VistaSuministro.hotel%TYPE,
n_cod_articulo VistaSuministro.articulo%TYPE,n_fecha VistaSuministro.fecha%TYPE DEFAULT NULL)
IS
contador_proveedor NUMBER(4);
BEGIN
    IF (n_fecha IS NULL) THEN
        DELETE FROM Elepab3.Suministro WHERE hotel=n_cod_hotel
        AND articulo=n_cod_articulo;
        DELETE FROM Elepab1.Suministro WHERE hotel=n_cod_hotel
        AND articulo=n_cod_articulo;
    ELSE
        DELETE FROM Elepab3.Suministro WHERE hotel=n_cod_hotel
        AND articulo=n_cod_articulo
        AND fecha = n_fecha;
        DELETE FROM Elepab1.Suministro WHERE hotel=n_cod_hotel AND articulo=n_cod_articulo
        AND fecha = n_fecha;
    END IF;


END;