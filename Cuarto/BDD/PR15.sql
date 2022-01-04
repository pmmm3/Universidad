CREATE OR REPLACE PROCEDURE dar_de_baja_articulo
(n_cod_articulo VistaArticulo.cod_articulo%TYPE)
IS
    existe_articulo NUMBER;
BEGIN
    SELECT COUNT(*) INTO existe_articulo FROM VistaArticulo
    WHERE n_cod_articulo = cod_articulo;
    IF (existe_articulo > 0)THEN
        DELETE FROM Elepab1.Articulo WHERE cod_articulo=n_cod_articulo;
        DELETE FROM Elepab3.Articulo WHERE cod_articulo=n_cod_articulo;

        DELETE FROM Elepab1.Suministro WHERE articulo=n_cod_articulo;
        DELETE FROM Elepab3.Suministro WHERE articulo=n_cod_articulo;

    ELSE
        RAISE_APPLICATION_ERROR(-2041, 'No se ha encontrado el articulo');
    END IF;
END;