test_table: test_table.o p_table_des_matieres.o ../utilitaires/p_utilitaires.o
	gcc -o test_table test_table.o p_table_des_matieres.o ../utilitaires/p_utilitaires.o

../utilitaires/p_utilitaires.o: ../utilitaires/p_utilitaires.c 
	cd ../utilitaires/
	gcc -c p_utilitaires.c 
	cd ../projet

test_table.o : test_table.c
	gcc -c test_table.c

p_table_des_matieres.o : p_table_des_matieres.c
	gcc -c p_table_des_matieres.c

clean:
	rm -f *.0
	rm -f test