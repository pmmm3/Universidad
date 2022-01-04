CREATE OR REPLACE PROCEDURE dar_de_alta_cliente_proceso
(n_cod_cliente VistaCliente.cod_cliente%TYPE,
n_DNI VistaCliente.DNI%TYPE,
n_nombre VistaCliente.nombre%TYPE,
n_telefono VistaCliente.telefono%TYPE)
IS
contador_clientes NUMBER(4);
BEGIN
   SELECT COUNT(*) INTO contador_clientes
   FROM VistaCliente WHERE cod_cliente = n_cod_cliente;

   IF (contador_clientes = 0) THEN
       INSERT INTO Elepab1.Cliente
       VALUES (n_cod_cliente,n_DNI,n_nombre,n_telefono);
       INSERT INTO Elepab2.Cliente
       VALUES (n_cod_cliente,n_DNI,n_nombre,n_telefono);
       INSERT INTO Elepab3.Cliente
       VALUES (n_cod_cliente,n_DNI,n_nombre,n_telefono);
       INSERT INTO Elepab4.Cliente
       VALUES (n_cod_cliente,n_DNI,n_nombre,n_telefono);
   ELSE
       raise_application_error(-20107, 'Ya existe un cliente con ese código asociado');
   END IF;
END;
