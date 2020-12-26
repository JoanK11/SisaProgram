# Sisa Program
Eina d'ajuda per a la matèria d'Introducció als Computadors (IC).
Dirigida als estudiants de 1r any de la FIB, Universitat Politècnica de Catalunya.

Contacte:
* Email: joan.caballero@estudiantat.upc.edu

# Instal·lació i Execució del programa
1. Baixa el fitxer __sisaprogram__ i guarda'l en qualsevol directori.
2. Amb una terminal o compilador dirigeix-te a la ubicació de l'arxiu (les comandes `ls` i `cd` et poden ajudar).
3. Escriu `./sisaprogram` per executar el programa.

# Característiques
* Conversor de nombre hexadecimal a Llenguatge ensamblador SISA.

     **Input:** `--hexa 1854`. **Output:** `CMPLTU R2 R4 R1`.
     
     ![](Images/hexa_to_sisa.png)
     
* Conversor d'Instrucció SISA a Paraula de Control del SISC Harvard unicicle.

     **Exemple d'Input:** `-c BNZ R7 -12`, `-c OR R0 R2 R5`, etc.
     ![](Images/paraula_control_v1.png)
