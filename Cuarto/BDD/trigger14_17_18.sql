-- Trigger 14,17,18,19  y el 11 y 12
CREATE OR REPLACE TRIGGER suminstro_mod BEFORE insert or UPDATE  ON Suministro
FOR EACH ROW
DECLARE
   ciudad_proveedor VARCHAR(20);
   ciudad_hotel VARCHAR(20);
    /*
    NUMBER(1) = 0/1 , 0 false y 1 true a modo booleano
    */
   existe_proveedor NUMBER(1);
   existe_articulo NUMBER(1);
   existe_hotel NUMBER(1);
   precio_min NUMBER(5,2);

BEGIN
    IF (UPDATING('cod_proveedor') OR INSERTING )THEN
        /*Busco el proveedor*/
        SELECT COUNT(*) INTO existe_proveedor FROM VistaProveedor
        WHERE VistaProveedor.cod_proveedor  = :new.proveedor ;
        IF (existe_proveedor  = 0) THEN
            RAISE_APPLICATION_ERROR(-2039, 'No se ha encontrado el proveedor');
        END IF;
        /*Busco el articulo*/
        SELECT COUNT(*) INTO existe_articulo FROM  VistaArticulo
        WHERE VistaArticulo.cod_articulo    = :new.articulo ;
        IF (existe_articulo = 0) THEN
            RAISE_APPLICATION_ERROR(-2039, 'No se ha encontrado el articulo');
        END IF;
        /*Busco el hotel*/
        SELECT COUNT(*) INTO existe_hotel FROM  VistaHotel
        WHERE VistaHotel.cod_hotel   = :new.hotel;

        IF (existe_hotel = 0) THEN
            RAISE_APPLICATION_ERROR(-2040, 'No se ha encontrado el hotel');
        END IF;
        /*Obtengo la ciudad del proveedor*/
        SELECT VistaProveedor.ciudad INTO ciudad_proveedor FROM VistaProveedor
        WHERE VistaProveedor.cod_proveedor  = :new.proveedor ;
        /*Obtengo la ciudad del hotel*/
        SELECT VistaHotel.ciudad INTO ciudad_hotel FROM  VistaHotel
        WHERE VistaHotel.cod_hotel = :new.hotel;
        /* Busco el precio mínimo del artículo en el hotel dado, si resultado > 0 el precio será el más bajo de todos*/
        SELECT COUNT(*) INTO precio_min FROM VistaSuministro
        WHERE articulo = :new.articulo AND hotel = :new.hotel AND precio >= :new.precio;
        IF (precio_min  > 0) THEN
            RAISE_APPLICATION_ERROR(-2014, 'El precio de un artículo nunca podrá ser menor que el de ese mismo artículo en suministros anteriores a ese mismo hotel');
        END IF;

        IF((ciudad_hotel = 'Granada')OR(ciudad_hotel = 'Jaén')OR(ciudad_hotel = 'Málaga')OR(ciudad_hotel = 'Almería'))THEN
            IF(ciudad_proveedor='Sevilla')THEN
                RAISE_APPLICATION_ERROR(-2017, 'Ningún hotel de las provincias de Granada, Jaén, Málaga o Almería podrán solicitar artículos a proveedores de Sevilla');
            END IF;
        END IF;
        IF((ciudad_hotel = 'Córdoba')OR(ciudad_hotel = 'Sevilla')OR(ciudad_hotel = 'Cádiz')OR(ciudad_hotel = 'Huelva'))THEN
            IF(ciudad_proveedor='Granada')THEN
                RAISE_APPLICATION_ERROR(-2018, 'Ningún hotel de las provincias de Córdoba, Sevilla, Cádiz o Huelva podrán solicitar artículos a proveedores de Granada.');
            END IF;
        END IF;
    END IF;

END;
