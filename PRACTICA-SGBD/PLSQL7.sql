set serveroutput on;

create or replace view catalog as select nume,prenume,titlu_curs,valoare from studenti s join note n on s.id=n.id_student join cursuri c on c.id=n.id_curs;
/

-- start insert trigger --
create or replace trigger catalog_insert
instead of insert on catalog
declare
  -- var general
  v_studenti integer;
  v_cursuri integer;
  v_created_at date;
  v_updated_at date;
  -- var student
  v_s_id studenti.id%type;
  v_nr_matricol studenti.nr_matricol%type;
  v_nume studenti.nume%type;
  v_prenume studenti.prenume%type;
  v_s_an studenti.an%type;
  v_grupa studenti.grupa%type;
  v_bursa studenti.bursa%type;
  v_data_nastere studenti.data_nastere%type;
  v_email studenti.email%type;
  -- var nota
  v_n_id note.id%type;
  v_id_student note.id_student%type;
  v_id_curs note.id_curs%type;
  v_valoare note.valoare%type;
  v_data_notare note.data_notare%type;
  -- var curs
  v_c_id cursuri.id%type;
  v_titlu_curs cursuri.titlu_curs%type;
  v_c_an cursuri.an%type;
  v_semestru cursuri.semestru%type;
  v_credite cursuri.credite%type;
begin
  select count(*) into v_studenti from studenti
    where nume like :new.nume and prenume like :new.prenume;
  select count(*) into v_cursuri from cursuri
    where titlu_curs=:new.titlu_curs;
    
  -- info generale
  v_created_at := sysdate;
  v_updated_at := sysdate;
  
  -- studentul nu exista -> creaza-l si genereaza info 
  
  if(v_studenti = 0) then
    select count(*)+1 into v_s_id from studenti;
    v_nr_matricol := floor(dbms_random.VALUE(100,999)) || chr(floor(dbms_random.VALUE(65,91)))
                     || chr(floor(dbms_random.value(65,91))) || floor(dbms_random.value(0,9));
    v_nume := :new.nume;
    v_prenume := :new.prenume;
    v_s_an := trunc(dbms_random.value(0,3))+1;
    v_grupa := chr(trunc(dbms_random.value(0,2))+65) || chr(trunc(dbms_random.value(0,6))+49);
    v_bursa := trunc(dbms_random.value(0,10))*100+500;
    v_data_nastere := to_date('01-01-1974','MM-DD-YYYY')+trunc(dbms_random.value(0,365));
    v_email := lower(v_nume || '.' || v_prenume || '@info.uaic.ro');
    
    insert into studenti values(v_s_id,v_nr_matricol,v_nume,v_prenume,
                                v_s_an,v_grupa,v_bursa,v_data_nastere,
                                v_email,v_created_at,v_updated_at);
  else
    select id into v_s_id from studenti
      where nume like :new.nume and prenume like :new.prenume and rownum=1;
  end if;

  -- cursul nu exista -> creaza-l si genereaza info
  if(v_cursuri = 0) then
    select count(*)+1 into v_c_id from cursuri;
    v_titlu_curs := :new.titlu_curs;
    v_c_an := trunc(dbms_random.value(0,v_s_an))+1;
    v_semestru := trunc(dbms_random.value(0,1))+1;
    v_credite := trunc(dbms_random.value(0,5))+1;
    
    insert into cursuri values(v_c_id,v_titlu_curs,v_c_an,v_semestru,
                               v_credite,v_created_at,v_updated_at);
  else
    select id into v_c_id from cursuri
      where titlu_curs like :new.titlu_curs;
  end if;
  
  -- info nota
  select count(*)+1 into v_n_id from note;
  v_valoare := :new.valoare;
  v_data_notare := sysdate;
  
  insert into note values(v_n_id,v_s_id,v_c_id,v_valoare,
                          v_data_notare,v_created_at,v_updated_at);
end;
/
-- end insert trigger --

-- start delete trigger --
create or replace trigger catalog_delete
instead of delete on catalog
for each row
declare
  v_s_id studenti.id%type;
begin
  select id into v_s_id from studenti
    where nume like :old.nume and prenume like :old.prenume and rownum=1;
      
  -- sterg randurile care referentiaza studentul v_s_id apoi il sterg pe el
  delete from prieteni where v_s_id in (id_student1,id_student2);
  delete from note where id_student=v_s_id;
  delete from studenti where id=v_s_id;
end;
/
-- end delete trigger --

-- start update trigger --
create or replace trigger catalog_update
instead of update on catalog
for each row
declare
  v_s_id studenti.id%type;
  v_c_id cursuri.id%type;
begin
  if (updating('valoare')) then 
    if (:new.valoare > :old.valoare) then
      select id into v_s_id from studenti
        where nume like :new.nume and prenume like :new.prenume and rownum=1;
        
        select id into v_c_id from cursuri
          where titlu_curs like :new.titlu_curs;
    
      update note set valoare=:new.valoare, updated_at=sysdate
        where id_student=v_s_id and id_curs like v_c_id;
    end if;
  end if;
end;
/
-- end update trigger --

begin
  dbms_output.put_line('------inserez 3 studenti------');
  insert into catalog values('Popesku', 'Mirkea', 'Yoga', 10);
  insert into catalog values('Numescu', 'Prenumescovici', 'Cursologie', 5);
  insert into catalog values('Leonardo', 'da Vinci', 'Pictura', 3);
  
  for v_linie in (select * from catalog where nume in('Popesku','Numescu','Leonardo')) loop     
    dbms_output.put_line(lpad(v_linie.nume||' '||v_linie.prenume,20)
                        || lpad(v_linie.titlu_curs || ',' || v_linie.valoare,20));
  end loop;
  
  dbms_output.put_line('------actualizez notele celor 3 studenti------');
  update catalog set valoare=8 -- nota aceasta este mai mica decat cea actuala deci va ramane la fel
    where nume like 'Popesku' and prenume like 'Mirkea' and titlu_curs like 'Yoga';
  update catalog set valoare=10 -- nota aceasta este mai mare decat cea actuala deci o vom actualiza
    where nume like 'Numescu' and prenume like 'Prenumescovici' and titlu_curs like 'Sisteme de operare';
  update catalog set valoare=4 -- nota aceasta este egala cu cea actuala deci va ramane la fel
    where nume like 'Leonardo' and prenume like 'da Vinci' and titlu_curs like 'Pictura';
    
  for v_linie in (select * from catalog where nume in('Popesku','Numescu','Leonardo')) loop     
    dbms_output.put_line(lpad(v_linie.nume||' '||v_linie.prenume,20)
                        || lpad(v_linie.titlu_curs || ',' || v_linie.valoare,20));
  end loop;
  
  dbms_output.put_line('------sterg cei 3 studenti------');
  delete from catalog where nume like 'Popesku' and prenume like 'Mirkea';
  delete from catalog where nume like 'Numescu' and prenume like 'Prenumescovici';
  delete from catalog where nume like 'Leonardo' and prenume like 'da Vinci';
  
  for v_linie in (select * from catalog where nume in('Popesku','Numescu','Leonardo')) loop     
    dbms_output.put_line(lpad(v_linie.nume||' '||v_linie.prenume,20)
                        || lpad(v_linie.titlu_curs || ',' || v_linie.valoare,20));
  end loop;
end;