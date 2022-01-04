CREATE OR REPLACE TRIGGER articulo_mod BEFORE UPDATE ON Articulo
FOR EACH ROW
DECLARE
   total_suministros NUMBER;
BEGIN
   IF (UPDATING('tipo') OR INSERTING )THEN
       IF(:NEW.tipo NOT IN ('A','B','C','D')) THEN
           RAISE_APPLICATION_ERROR(-2013, 'El tipo de un articulo sera ‘A’, ‘B’, ‘C’ o ‘D’.');
       END IF;
   END IF;
   IF (DELETING)THEN
       SELECT SUM(VistaSuministro.cantidad) INTO total_suministros
       FROM VistaSuministro
       WHERE VistaSuministro.articulo = :new.cod_articulo;

       IF(total_suministros >=0)THEN
           RAISE_APPLICATION_ERROR(-2020, 'Los datos referentes a un articulo solo podran eliminarse de la base de datos si la cantidad total suministrada de ese articulo es 0 o no existe ningun suministro.');
       END IF;

   END IF;
END;