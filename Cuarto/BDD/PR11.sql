
CREATE OR REPLACE PROCEDURE dar_de_baja_proveedor
(n_cod_proveedor VistaProveedor.cod_proveedor%TYPE)
IS
contador_proveedor NUMBER(4);
BEGIN
   SELECT COUNT(*) INTO contador_proveedor
   FROM VistaProveedor WHERE cod_proveedor = n_cod_proveedor;

   IF (contador_proveedor = 0) THEN
       raise_application_error(-20111, 'No existe un proveedor con ese código asociado');
   ELSE
       DELETE FROM Elepab1.Proveedor WHERE cod_proveedor=n_cod_proveedor;
       DELETE FROM Elepab3.Proveedor WHERE cod_proveedor=n_cod_proveedor;
   END IF;
END;