CREATE OR REPLACE TRIGGER ciudad_proveedor BEFORE INSERT OR UPDATE  OR DELETE ON Proveedor
FOR EACH ROW
DECLARE
    total_suministrado NUMBER;
BEGIN
IF (UPDATING('ciudad') OR INSERTING )THEN
   IF (:new.ciudad) NOT IN ('Sevilla','Granada') THEN

       RAISE_APPLICATION_ERROR(-2016, 'Ningún proveedor será de otra ciudad distinta a Granada o a Sevilla');
   END IF;
END IF;
IF (DELETING) THEN
        SELECT SUM(cantidad) INTO total_suministrado FROM VistaSuministro
        WHERE  proveedor = :new.cod_proveedor;

        IF (total_suministrado >= 0)THEN
            RAISE_APPLICATION_ERROR(-2019,'La cantidad total suministrada no es 0');
        END IF;

    END IF;
END;