set serveroutput on;

create or replace function gettype(v_rec_tab dbms_sql.desc_tab, v_nr_col int) return varchar2 is
  v_tip_coloana varchar2(200);
  v_precizie varchar2(40);
begin
  case (v_rec_tab(v_nr_col).col_type)
    when 1 then v_tip_coloana := 'varchar2'; v_precizie := '(' || v_rec_tab(v_nr_col).col_max_len || ')';
    when 2 then v_tip_coloana := 'number'; v_precizie := '(' || v_rec_tab(v_nr_col).col_precision || ',' || v_rec_tab(v_nr_col).col_scale || ')';
    when 12 then v_tip_coloana := 'date'; v_precizie := '';
    when 96 then v_tip_coloana := 'char'; v_precizie := '(' || v_rec_tab(v_nr_col).col_max_len || ')';
    when 112 then v_tip_coloana := 'clob'; v_precizie := '';
    when 113 then v_tip_coloana := 'blob'; v_precizie := '';
    when 109 then v_tip_coloana := 'xmltype'; v_precizie := '';
    when 101 then v_tip_coloana := 'binary_double'; v_precizie := '';
    when 100 then v_tip_coloana := 'binary_float'; v_precizie := '';
    when 8 then v_tip_coloana := 'long'; v_precizie := '';
    when 180 then v_tip_coloana := 'timestamp'; v_precizie :='(' || v_rec_tab(v_nr_col).col_scale || ')';
    when 181 then v_tip_coloana := 'timestamp' || '(' || v_rec_tab(v_nr_col).col_scale || ') ' || 'with time zone'; v_precizie := '';
    when 231 then v_tip_coloana := 'timestamp' || '(' || v_rec_tab(v_nr_col).col_scale || ') ' || 'with local time zone'; v_precizie := '';
    when 114 then v_tip_coloana := 'bfile'; v_precizie := '';
    when 23 then v_tip_coloana := 'raw'; v_precizie := '(' || v_rec_tab(v_nr_col).col_max_len || ')';
    when 11 then v_tip_coloana := 'rowid'; v_precizie := '';
    when 109 then v_tip_coloana := 'uritype'; v_precizie := '';
  end case; 
  return v_tip_coloana||v_precizie;
end;
/

create or replace procedure genereaza_catalog(p_id in integer) is
  v_titlu_curs cursuri.titlu_curs%type;
  
  v_rec_tab dbms_sql.desc_tab;
  
  v_cursor_id1 integer;
  v_cursor_id2 integer;
  v_ok1 integer;
  v_ok2 integer;
  v_total_coloane integer;
  
  v_valoare note.valoare%type;
  v_data_notare note.data_notare%type;
  v_nume studenti.nume%type;
  v_prenume studenti.prenume%type;
  v_nr_matricol studenti.nr_matricol%type;
begin
  --aflu titlul cursului
  v_cursor_id1 := dbms_sql.open_cursor;
  dbms_sql.parse(v_cursor_id1, 'select titlu_curs from cursuri where id=' || p_id, dbms_sql.native);
  dbms_sql.describe_columns(v_cursor_id1, v_total_coloane, v_rec_tab);
  dbms_sql.define_column(v_cursor_id1, 1, v_titlu_curs, v_rec_tab(1).col_max_len);
  v_ok1 := dbms_sql.execute(v_cursor_id1);
  
  loop
    if dbms_sql.fetch_rows(v_cursor_id1) > 0 then 
      dbms_sql.column_value(v_cursor_id1, 1, v_titlu_curs);
    else
      exit;
    end if;
  end loop;
  
  dbms_sql.close_cursor(v_cursor_id1);

  --sterg spatiile si caracterele nule
  v_titlu_curs := replace(regexp_replace(v_titlu_curs, '\s'), chr(0));
  
  --definesc coloanele necesare pt catalog; voi apela execute cand voi incepe sa inserez date
  v_cursor_id2 := dbms_sql.open_cursor;
  dbms_sql.parse(v_cursor_id2, 'select nr_matricol,nume,prenume,valoare,data_notare
                from studenti s join note n on s.id=n.id_student
                where id_curs=' || p_id, dbms_sql.native);
  dbms_sql.describe_columns(v_cursor_id2, v_total_coloane, v_rec_tab);
  dbms_sql.define_column(v_cursor_id2, 1, v_nr_matricol, v_rec_tab(1).col_max_len);
  dbms_sql.define_column(v_cursor_id2, 2, v_nume, v_rec_tab(2).col_max_len);
  dbms_sql.define_column(v_cursor_id2, 3, v_prenume, v_rec_tab(3).col_max_len);
  dbms_sql.define_column(v_cursor_id2, 4, v_valoare);
  dbms_sql.define_column(v_cursor_id2, 5, v_data_notare);
  
  --sterg tabela in caz ca exista
  begin
    v_cursor_id1 := dbms_sql.open_cursor;
    dbms_sql.parse(v_cursor_id1, 'drop table ' || v_titlu_curs, dbms_sql.native);
    v_ok1 := dbms_sql.execute(v_cursor_id1);
    dbms_sql.close_cursor(v_cursor_id1);
    
    exception
    when no_data_found then dbms_output.put_line('Datele cerute nu exista.');
    when others then 
      if sqlcode = -942 then null;--exceptie pt drop table in cazul in care tabela nu exista
      else dbms_output.put_line('A intervenit o eroare. Cod: ' || sqlcode);
      end if;
  end;
  
  --creez tabela
  v_cursor_id1 := dbms_sql.open_cursor;
  dbms_sql.parse(v_cursor_id1, 'create table ' || v_titlu_curs ||
                '(nr_matricol ' || gettype(v_rec_tab,1) || ',' ||
                'nume ' || gettype(v_rec_tab,2) || ',' ||
                'prenume ' || gettype(v_rec_tab,3) || ',' ||
                'valoare ' || gettype(v_rec_tab,4) || ',' ||
                'data_notare ' || gettype(v_rec_tab,5) || ')'
                ,dbms_sql.native);
  v_ok1 := dbms_sql.execute(v_cursor_id1);
  dbms_sql.close_cursor(v_cursor_id1);
        
  --incep sa inserez datele obtinute din v_cursor_id2 in tabela nou creata
  v_ok2 := dbms_sql.execute(v_cursor_id2);
  loop
    if dbms_sql.fetch_rows(v_cursor_id2) > 0 then 
      dbms_sql.column_value(v_cursor_id2, 1, v_nr_matricol);
      dbms_sql.column_value(v_cursor_id2, 2, v_nume);
      dbms_sql.column_value(v_cursor_id2, 3, v_prenume);
      dbms_sql.column_value(v_cursor_id2, 4, v_valoare);
      dbms_sql.column_value(v_cursor_id2, 5, v_data_notare);
      
      --incep sa inserez efectiv
      v_cursor_id1 := dbms_sql.open_cursor;
      dbms_sql.parse(v_cursor_id1, 'insert into ' || v_titlu_curs ||
                    ' values(' || chr(39) || v_nr_matricol || chr(39) || ',' ||
                    chr(39) || v_nume || chr(39) || ',' ||
                    chr(39) || v_prenume || chr(39) || ',' ||
                    chr(39) || v_valoare || chr(39) || ',' || 
                    chr(39) || v_data_notare || chr(39)||
                    ')', dbms_sql.native);
      v_ok1 := dbms_sql.execute(v_cursor_id1);
      dbms_sql.close_cursor(v_cursor_id1);
    else
      exit;
    end if;
  end loop;
  dbms_sql.close_cursor(v_cursor_id2);
end;
/

begin
  genereaza_catalog(10); --catalog pt Baze de date
end;