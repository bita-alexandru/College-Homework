-- am folosit 2 cursoare: unul pt parcurgerea rand cu rand a studentilor si unul
-- pt parcurgerea notelor unui anumit student intr-un anumit (an,semestru);

set serveroutput on;

-- creez tipul 'medii' ca fiind un nested table
create or replace type medii as table of number;
/

-- adaug coloana 'lista_medii' cu tipul de date 'medii'
alter table studenti add lista_medii medii nested table lista_medii store as lista;

-- selectez campul 'lista_medii' din dreapta studentului cu id-ul 'p_id' si returnez nr de elemente pe care il contine cu ajutorul functiei COUNT
create or replace function numara_medii(p_id studenti.id%type)
return integer as
  v_medii medii := medii();
begin
  select lista_medii into v_medii from studenti where id=p_id;
  return v_medii.count;
end numara_medii;
/

declare 
  -- cursor pt parcurgerea fiecarui rand de studenti in scopul actualizarii campului 'lista_medii'
  cursor lista_studenti is
    select id from studenti;
    
  -- cursor pt parcurgerea notelor unui student cu id 'p_id' in scopul obtinerii mediilor de pe fiecare pereche (an,semestru)
  cursor lista_note(p_id studenti.id%type) is
    select avg(valoare)
      from ((studenti s join note n on s.id=n.id_student) join cursuri c on c.id=n.id_curs) 
      where s.id=p_id group by c.an, c.semestru
      order by c.an, c.semestru;
  
  v_medii medii;
  
  v_id studenti.id%type;
  v_medie number;
  
  v_total_studenti integer;
  v_total_medii integer;
  v_contor integer;
  
begin  
  -- inserez un student fara note, ii atribui ca ID valoarea ultimului ID+1 (adica totatul de studenti+1)
  select count(*) into v_total_studenti from studenti;
  insert into studenti columns(id,nr_matricol,nume,prenume) values(v_total_studenti+1,'ZZZ000','popescu','andrei');
  v_total_studenti := v_total_studenti+1;
  
  open lista_studenti;
    -- parcurg studentii rand cu rand
    loop
      v_medii := medii();
      
      -- retin id-ul studentului actual
      fetch lista_studenti into v_id;
      exit when lista_studenti%notfound;
      
      open lista_note(v_id);
        -- parcurg notele acestui student
        loop
          fetch lista_note into v_medie;
          exit when lista_note%notfound;
          
          -- adaug la tabela 'v_medii' media obtinuta pt perechea actuala (an,semestru)
          v_medii.extend;
          v_medii(v_medii.last) := v_medie;
        end loop;
      close lista_note;
      
      -- actualizez campul 'lista_medii' cu tabela tocmai obtinuta
      update studenti set lista_medii=v_medii where id=v_id;
    end loop;
  close lista_studenti;
    
  -- afisez informatii cu privire la mediile studentilor
  for k in 1..v_total_studenti loop
    dbms_output.put('Studentul cu ID:' || k);
    
    v_total_medii := numara_medii(k);
    
    if(v_total_medii = 0) then
        -- studentul nu are nicio medie
        dbms_output.put_line(' nu are nicio medie.');
      else
        dbms_output.put(' are ' || v_total_medii || ' medii: ');
        
        v_medii := medii();
        -- retin mediile studentului
        select lista_medii into v_medii from studenti where id=k;
        
        v_contor := 1;
        <<inceput_loop>>
        for i in 1..3 loop
          for j in 1..2 loop
            -- daca media pe perechea (an,semestru) adica (i,j) nu exista atunci ies din bucla
            if(not v_medii.exists(v_contor)) then
                exit inceput_loop;
              -- altfel o afisez
              else 
                dbms_output.put(v_medii(v_contor) || '(an.' || i || ',sem.' || j || ') '); 
                v_contor := v_contor+1;
            end if;
          end loop;
        end loop;
        
        dbms_output.put_line('');
    end if;
  end loop;
end;