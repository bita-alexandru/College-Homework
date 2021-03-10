set serveroutput on;

declare
  v_int integer;
begin
  dbms_output.put_line('Tabele');
  for i in (select * from user_tables) loop
    dbms_output.put_line(chr(9) || 'nume_tabel: ' || i.table_name);
    dbms_output.put_line(chr(9) || 'nr_inregistrari: ' || i.num_rows);
    
    dbms_output.put(chr(9) || 'constrangeri: ');
    select count(*) into v_int from user_constraints where table_name=i.table_name;
    if v_int <= 0 then
      dbms_output.put_line('nu are constrangeri');
    else
      for j in (select * from user_constraints where table_name=i.table_name) loop
        dbms_output.put_line('');
        dbms_output.put_line(chr(9) || chr(9) || 'nume_constrangere: ' || j.constraint_name);
        dbms_output.put_line(chr(9) || chr(9) || 'tip_constrangere: ' || j.constraint_type);
        dbms_output.put_line(chr(9) || chr(9) || 'coloane_implicate:');
        for k in (select * from user_cons_columns where constraint_name=j.constraint_name) loop
          dbms_output.put_line(chr(9) || chr(9) || chr(9) || k.column_name);
        end loop;
      end loop;
    end if;
    dbms_output.put_line('');
    
    dbms_output.put(chr(9) || 'indecsi: ');
    select count(*) into v_int from user_indexes where table_name=i.table_name;
    if v_int <= 0 then
      dbms_output.put_line('nu are indecsi');
    else
      for j in (select * from user_indexes where table_name=i.table_name) loop
        dbms_output.put_line('');
        dbms_output.put_line(chr(9) || chr(9) || 'nume_index: ' || j.index_name);
        dbms_output.put_line(chr(9) || chr(9) || 'coloane_implicate:');
        for k in (select * from user_ind_columns where index_name=j.index_name) loop
          dbms_output.put_line(chr(9) || chr(9) || chr(9) || k.column_name);
        end loop;
      end loop;
    end if;
    
    dbms_output.put_line('nested?: ' || i.nested); 
    dbms_output.put_line('');
  end loop;
  dbms_output.put_line('');
  
  dbms_output.put_line('Views');
  for i in (select * from user_views) loop
    dbms_output.put_line(chr(9) || 'nume_view: ' || i.view_name);
    dbms_output.put_line(chr(9) || 'nr_caractere: ' || i.text_length);
    dbms_output.put_line(chr(9) || 'text: ' || i.text);
    dbms_output.put_line('');
  end loop;
  dbms_output.put_line('');
  
  dbms_output.put_line('Indecsi');
  for i in (select * from user_indexes) loop
    dbms_output.put_line(chr(9) || 'nume_index: ' || i.index_name);
    dbms_output.put_line(chr(9) || 'nume_tabel: ' || i.table_name);
    dbms_output.put_line(chr(9) || 'coloane_implicate:');
    for j in (select * from user_ind_columns where table_name=i.table_name) loop
      dbms_output.put_line(chr(9) || chr(9) || j.column_name);
    end loop;
    dbms_output.put_line('');
  end loop;
  dbms_output.put_line('');
  
  dbms_output.put_line('Types');
  for i in (select * from user_types) loop
    dbms_output.put_line(chr(9) || 'nume_type: ' || i.type_name);
    dbms_output.put_line(chr(9) || 'typecode: ' || i.typecode);
    dbms_output.put_line(chr(9) || 'nr_atribute: ' || i.attributes);
    dbms_output.put_line(chr(9) || 'nr_metode: ' || i.methods);
    dbms_output.put_line('');
  end loop;
  dbms_output.put_line('');
  
  dbms_output.put_line('Packages');
  for i in (select * from user_objects where object_type='PACKAGE') loop
    dbms_output.put_line(chr(9) || 'nume_package: ' || i.object_name);
    dbms_output.put_line('');
  end loop;
  dbms_output.put_line('');
  
  dbms_output.put_line('Proceduri');
  for i in (select * from user_objects where object_type='PROCEDURE') loop
    dbms_output.put_line(chr(9) || 'nume_procedura: ' || i.object_name);
    
    select max(line) into v_int from user_source group by name having name=i.object_name;
    dbms_output.put_line(chr(9) || 'nr_linii: ' || v_int);
    
    dbms_output.put(chr(9) || 'determinist?: ');
    for j in (select * from user_procedures where object_name=i.object_name) loop
      dbms_output.put_line(j.deterministic);
    end loop;
    dbms_output.put_line('');
  end loop;
  dbms_output.put_line('');
  
  dbms_output.put_line('Functii');
  for i in (select * from user_objects where object_type='FUNCTION') loop
    dbms_output.put_line(chr(9) || 'nume_functie: ' || i.object_name);
    
    select max(line) into v_int from user_source group by name having name=i.object_name;
    dbms_output.put_line(chr(9) || 'nr_linii: ' || v_int);
    
    dbms_output.put(chr(9) || 'determinist?: ');
    for j in (select * from user_procedures where object_name=i.object_name) loop
      dbms_output.put_line(j.deterministic);
    end loop;
    dbms_output.put_line('');
  end loop;
end;