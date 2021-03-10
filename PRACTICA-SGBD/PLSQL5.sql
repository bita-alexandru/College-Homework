alter table note add constraint not_duplicate unique(id_student,id_curs);

set serveroutput on;

create or replace function medie_student(p_nume studenti.nume%type, p_prenume studenti.prenume%type)
return number as
   v_medie number;
   v_rezultate integer;
   v_student studenti.id%type;
   
   student_inexistent exception;
   pragma exception_init(student_inexistent, -20001);
begin
    select count(*) into v_rezultate from studenti;
    
    -- query-ul nu returneaza nimic => aruncam exceptia
    if(v_rezultate < 1) then
        raise student_inexistent;
    end if;
    
    -- daca nu se arunca nicio exceptie, retinem id-ul studentului si ii calculam media
    select id into v_student from studenti where nume like p_nume and prenume like p_prenume and rownum=1;
    select avg(valoare) into v_medie from note where id_student=v_student;
    
    return v_medie;
end;
/

declare
  MILION integer := 0;
  
  v_logica cursuri.id%type := 1;
  v_student studenti.id%type;
  
  v_total_studenti integer;
  v_total_note integer;
  v_note integer;
  
  type v_studenti_info is varray(2) of varchar2(30);
  type v_studenti_tabel is table of v_studenti_info;
  
  v_studenti v_studenti_tabel := v_studenti_tabel();
begin
  dbms_output.enable(buffer_size => null);
  
  select count(*) into v_total_studenti from studenti;
  select count(*) into v_total_note from note;
  
  -- metoda cu verificare inainte de inserare
  for i in 1..MILION loop -- Task completed in 11.742 seconds
    v_student := dbms_random.value(1,v_total_studenti);
    
    select count(*) into v_note from note where id_student=v_student and id_curs=v_logica;
    
    if(v_note = 0) then 
        v_total_note := v_total_note+1;
        insert into note columns(id,id_student,id_curs) values(v_total_note,v_student,v_logica);
    else
        dbms_output.put_line('Studentul cu ID:' || v_student || ' are deja nota la Logica.');
    end if;
  end loop;
  
  -- metoda cu inserare si exceptie
  for i in 1..MILION loop -- Task completed in 255.167 seconds
    begin
      v_student := dbms_random.value(1,v_total_studenti);
      v_total_note := v_total_note+1;
      insert into note columns(id,id_student,id_curs) values(v_total_note,v_student,v_logica);
    
      exception
        when DUP_VAL_ON_INDEX then
          dbms_output.put_line('Studentul cu ID:' || v_student || ' are deja nota la Logica.');
      end;
  end loop;

  -- adaug 3 studenti existenti si 3 neexistenti
  v_studenti.extend(6);
  v_studenti(1) := v_studenti_info('Perju','Eduard');
  v_studenti(2) := v_studenti_info('Lupu','Monica');
  v_studenti(3) := v_studenti_info('Oana','Irina');
  v_studenti(4) := v_studenti_info('AAAAA','aaaaaaaaa');
  v_studenti(5) := v_studenti_info('BBBBB','bbbbbbbbb');
  v_studenti(6) := v_studenti_info('CCCCC','ccccccccc');
  
  for i in v_studenti.first..v_studenti.last loop
    begin
        dbms_output.put_line('Studentul ' || v_studenti(i)(1) || ' ' || v_studenti(i)(2) 
                              || ' are media ' || medie_student(v_studenti(i)(1),v_studenti(i)(2)));
        
        exception
        when no_data_found then
          dbms_output.put_line('Studentul ' || v_studenti(i)(1) || ' ' || v_studenti(i)(2) || ' nu exista in baza de date.');
    end;
  end loop;
end;