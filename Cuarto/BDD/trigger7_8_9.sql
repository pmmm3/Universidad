CREATE OR REPLACE TRIGGER solo_un_director BEFORE INSERT OR UPDATE ON Hotel FOR EACH ROW
DECLARE
    cont_directores number;
    existe_empleado NUMBER;
BEGIN

    /* Busco si tiente algun hotel el director, que el hotel exista esta implicito (9)*/
	SELECT COUNT(*) INTO cont_directores FROM VistaHotel
	WHERE director = :new.director ;

	IF cont_directores > 0 THEN
    	RAISE_APPLICATION_ERROR(-2008, 'Este director ya tiene un hotel asignado');
	END IF;

    /* Compruebo que sea empleado  en ese hotel */
    SELECT COUNT(*) INTO existe_empleado FROM VistaEmpleado
    WHERE cod_empleado = :new.director AND :new.cod_hotel = hotel_actual;
    IF existe_empleado < 1 THEN
    	RAISE_APPLICATION_ERROR(-2007, 'Este director no trabaja en el hotel');
	END IF;
END;