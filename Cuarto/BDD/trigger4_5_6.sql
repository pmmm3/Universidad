create or replace NONEDITIONABLE TRIGGER hab_reservas BEFORE INSERT OR UPDATE ON Reserva FOR EACH ROW
DECLARE
	sencillas NUMBER(2);
	dobles NUMBER(2);
	cont_hoteles NUMBER;
BEGIN
	IF inserting THEN

    	/*Comprobamos si hay un error en las fechas */
    	IF :new.entrada > :new.salida THEN
        	RAISE_APPLICATION_ERROR(-2015, 'La fecha de salida debe ser posterior a la entrada');
    	END IF;

    	/*Comprobamos si el cliente ya tiene una reserva */
    	SELECT COUNT(*) INTO cont_hoteles FROM VistaReserva
    	WHERE cliente = :new.cliente AND :new.entrada < salida;
    	IF cont_hoteles > 0 THEN
        	RAISE_APPLICATION_ERROR(-2006, 'Este cliente ya tiene una  reserva');
    	END IF;

    	/*Comprobamos si las habitaciones sencillas o dobles están disponibles */
    	IF :new.hab = 'sencilla' THEN
        	SELECT c.hab_sencilla INTO sencillas FROM vistahotel_capacidad c
        	WHERE :new.hotel = c.cod_hotel;
        	IF sencillas > 0 THEN
            	UPDATE Hotel_capacidad SET hab_sencilla= sencillas-1
            	WHERE Hotel_capacidad.cod_hotel = :new.hotel;
        	ELSE
            	RAISE_APPLICATION_ERROR(-2094, 'No hay habitaciones sencillas disponibles');
        	END IF;

    	ELSE
        	SELECT c.hab_doble INTO dobles FROM VistaHotel_capacidad c
        	WHERE :new.hotel = c.cod_hotel;

        	IF dobles > 0 THEN
            	UPDATE Hotel_capacidad SET hab_doble= dobles-1
            	WHERE Hotel_capacidad.cod_hotel = :new.hotel;
        	ELSE
            	RAISE_APPLICATION_ERROR(-2074, 'No hay habitaciones  dobles disponibles');
        	END IF;
    	END IF;

	ELSE
    	/* Comprobamos si hay habitaciones disponibles en la actualización*/
    	IF :old.hab != :new.hab THEN
        	IF :new.hab = 'sencilla' THEN
            	SELECT c.hab_sencilla INTO sencillas
            	FROM VistaHotel_capacidad c WHERE :old.hotel = c.cod_hotel;

                	IF sencillas > 0 THEN
                    	UPDATE Hotel_capacidad SET hab_sencilla= sencillas-1
                    	WHERE Hotel_capacidad.cod_hotel = :old.hotel;

                    	UPDATE Hotel_capacidad SET hab_doble = hab_doble +1
                    	WHERE Hotel_capacidad.cod_hotel = :old.hotel;
                	ELSE
                    	RAISE_APPLICATION_ERROR(-2014, 'No hay habitaciones sencillas disponibles');
                	END IF;
        	ELSE
            	SELECT c.hab_doble INTO dobles FROM VistaHotel_capacidad c WHERE :old.hotel = c.cod_hotel;
            	IF dobles > 0 THEN
                	UPDATE Hotel_capacidad SET hab_doble = dobles - 1
                	WHERE Hotel_capacidad.cod_hotel = :old.hotel;

                	UPDATE Hotel_capacidad SET hab_sencilla = hab_sencilla +1
                	WHERE Hotel_capacidad.cod_hotel = :old.hotel;
            	ELSE
                	RAISE_APPLICATION_ERROR(-2024, 'No hay habitaciones  dobles disponibles');
            	END IF;

        	END IF;

    	END IF;

    	IF :new.entrada > :old.salida THEN
        	RAISE_APPLICATION_ERROR(-2095, 'La fecha de salida debe ser posterior a la entrada');
    	END IF;
	END IF;
END;
