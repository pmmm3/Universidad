create or replace TRIGGER salario_empleado BEFORE INSERT OR UPDATE ON EMPLEADO
FOR EACH ROW
DECLARE
   salario_previo NUMBER(6,2);
   f_fin DATE;
BEGIN
   IF (UPDATING('fecha_inicio') OR INSERTING )THEN
      IF (:new.fecha_inicio < :new.fecha_contrato) THEN
        RAISE_APPLICATION_ERROR(-2011, 'La fecha de inicio debe ser igual o posterior a la fecha de inicio de su contrato con la multinacional');
      END IF;
      IF (UPDATING('fecha_inicio')) THEN
         SELECT fecha_fin INTO f_fin FROM registro_historico h
         WHERE h.cod_empleado = :new.cod_empleado
         AND h.cod_hotel = :new.hotel_actual
         AND :old.fecha_inicio = h.fecha_inicio;
         IF (:new.fecha_inicio < f_fin) THEN
         RAISE_APPLICATION_ERROR(-2012, 'La fecha de inicio debe ser igual o posterior a la fecha fin  de su anterior contrato');

         END IF;
      END IF;
   END IF;
   IF (UPDATING('Salario')) THEN
      SELECT VistaEmpleado.salario INTO salario_previo FROM VistaEmpleado  WHERE VistaEmpleado.COD_EMPLEADO =:new.COD_EMPLEADO;
      IF(salario_previo >= :new.SALARIO) THEN
         RAISE_APPLICATION_ERROR(-2010, 'El salario de un empleado nunca podrá disminuir');
      END IF;
   END IF;



END;
