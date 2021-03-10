set serveroutput on;

-- script pt export
declare
  v_fisier utl_file.file_type;
begin
  v_fisier := utl_file.fopen('MYDIR', 'note.csv', 'w');
  
  for i in (select column_name from user_tab_columns where table_name = 'NOTE') loop
    utl_file.putf(v_fisier, i.column_name || ',');
  end loop;
  
  utl_file.putf(v_fisier, '\n');
  
  for i in (select * from note order by id) loop
    utl_file.putf(v_fisier, i.id || ',' || i.id_student || ','
                  || i.id_curs || ',' || i.valoare || ','
                  || i.data_notare || ',' || i.created_at || ',' || i.updated_at);
    utl_file.putf(v_fisier, '\n');
  end loop;
  
  utl_file.fclose(v_fisier);
end;
/

-- script pt delete from note
begin
  delete from note;
end;
/

-- script pt import
declare
  v_fisier utl_file.file_type;
  v_sir varchar(100);
  
  type nota is record(id int, id_student int, id_curs int, valoare number(2),
                      data_notare date, created_at date, updated_at date);
  v_nota nota;
begin
  v_fisier := utl_file.fopen('MYDIR', 'note.csv', 'r');
  
  utl_file.get_line(v_fisier, v_sir);
 
  begin
    loop
      utl_file.get_line(v_fisier, v_sir);
      
      v_nota.id := regexp_substr(v_sir, '[^, ]+', 1, 1);
      v_nota.id_student := regexp_substr(v_sir, '[^, ]+', 1, 2);
      v_nota.id_curs := regexp_substr(v_sir, '[^, ]+', 1, 3);
      v_nota.valoare := regexp_substr(v_sir, '[^, ]+', 1, 4);
      v_nota.data_notare := regexp_substr(v_sir, '[^, ]+', 1, 5);
      v_nota.created_at := regexp_substr(v_sir, '[^, ]+', 1, 6);
      v_nota.updated_at := regexp_substr(v_sir, '[^, ]+', 1, 7);
      
      insert into note values v_nota;
    end loop;
    
    exception
      when no_data_found then null;
  end;
  
  utl_file.fclose(v_fisier);
end;
/