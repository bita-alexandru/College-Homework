set serveroutput on;

create or replace type sportiv is object (
  nume varchar2(32),
  varsta number(2),
  tara varchar(16),
  debut number(2),
  member procedure este_roman,
  not final member procedure notabil,
  map member function compara_varste return number,
  
  constructor function sportiv(nume varchar2, varsta number)
    return self as result
) not final;
/

create or replace type body sportiv is
  constructor function sportiv(nume varchar2, varsta number)
    return self as result
  is
  begin
    self.nume := nume;
    self.varsta := varsta;
    self.tara := 'Romania';
    self.debut := 16;
    return;
  end;

   member procedure este_roman is
   begin
       if(upper(tara) = 'ROMANIA' or upper(tara) = 'ROMÂNIA') then 
          dbms_output.put_line(nume || ' s-a nascut in Romania.');
       else 
          dbms_output.put_line(nume || ' nu s-a nascut in Romania.');
      end if;
   end este_roman;
   
   member procedure notabil is
   begin
      dbms_output.put_line(nume || ' castiga medalie dupa medalie de ' || (varsta-debut) || ' ani incoace!');
   end notabil;
   
   map member function compara_varste return number is
   begin
       return varsta;
   end compara_varste;
end;
/

create or replace type fotbalist under sportiv
(    
  goluri number(5),
  overriding member procedure notabil
);
/

create or replace type body fotbalist is
    overriding member procedure notabil is
    begin
       dbms_output.put_line(nume || ' a marcat ' || goluri || ' in cariera sa!');
    end notabil;
end;
/

create table sportivi_oop (id integer, obiect SPORTIV);
/

declare
  -- sportiv(nume,varsta,tara,debut) sau (nume,varsta) cu tara:'Romania' si debut:16 default
  andreea sportiv := sportiv('Andreea',24);
  mike sportiv := sportiv('Mike',21,'USA',18);
  
  -- fotbalist(nume,varsta,tara,debut,goluri)
  stefan fotbalist := fotbalist('Stefan',22,'Romania',20,47);
  pedro fotbalist := fotbalist('Pedro',28,'Spania',17,143);
  
begin
  insert into sportivi_oop values (1, andreea);
  insert into sportivi_oop values (2, mike);
  insert into sportivi_oop values (3, stefan);
  insert into sportivi_oop values (4, pedro);
  
  -- obiectele se vor compara dupa varsta
  for v_linie in (select * from sportivi_oop order by obiect) loop     
    dbms_output.put(v_linie.obiect.nume || ' are ' || v_linie.obiect.varsta || ' ani, a debutat la '
                || v_linie.obiect.debut || ' ani si este din ' || v_linie.obiect.tara || '. ');
    v_linie.obiect.notabil;
  end loop;
end;