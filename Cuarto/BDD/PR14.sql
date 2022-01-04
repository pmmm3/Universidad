
CREATE OR REPLACE PROCEDURE dar_de_alta_articulo
(n_cod_articulo VistaArticulo.cod_articulo%TYPE,
n_nombre VistaArticulo.nombre%TYPE,
n_tipo VistaArticulo.tipo%TYPE,
n_cod_proveedor VistaArticulo.proveedor%TYPE)
IS
    existe_proveedor NUMBER;
    
BEGIN
    SELECT COUNT(*) INTO existe_proveedor FROM VistaProveedor WHERE cod_proveedor = n_cod_proveedor;
    IF (existe_proveedor > 0) THEN

            INSERT INTO Elepab1.Articulo
            VALUES(n_cod_articulo,n_nombre,n_tipo,n_cod_proveedor);

            INSERT INTO Elepab3.Articulo
            VALUES(n_cod_articulo,n_nombre,n_tipo,n_cod_proveedor);

    ELSE
        RAISE_APPLICATION_ERROR(-2039, 'No se ha encontrado el proveedor');
    END IF;
END;