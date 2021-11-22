#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

struct Controlv1 {
    string a, b, f, d; // 3 digits
    string op, ila, addrio = "XX"; // 2 digits
    char rbn, wrd = '1', wrout = '0', rdin = '0';
    char wrmem = '0', byte = 'X', tknbr = '0';
    string nhexa;
};
struct Controlv2 {
    string a, b, f, d; // 3 digits
    string op, pila, addrio = "XX"; // 2 digits
    char pcrx, ryn, wrd = '1', wrout = '0', rdin = '0';
    char wrmem = '0', ldir = 'X', ldpc = '0', byte = 'X';
    char alur = 'X', rpc = 'X';
    string nhexa;
};


string dec_bin(int x) {
// Pre: Nombre en decimal entre [0, 7]
// Post: String en binari de 3 dígits entre [000, 111]
    if (x == 1) return "001";
    else if (x == 2)    return "010";
    else if (x == 3)    return "011";
    else if (x == 4)    return "100";
    else if (x == 5)    return "101";
    else if (x == 6)    return "110";
    else if (x == 7)    return "111";
    return "000";
}
int bin_dec(string x) {
// Pre: String en binari de 3 dígits entre [000, 111] 
// Post: Nombre en decimal entre [0, 7]
    if (x == "001") return 1;
    else if (x == "010")    return 2;
    else if (x == "011")    return 3;
    else if (x == "100")    return 4;
    else if (x == "101")    return 5;
    else if (x == "110")    return 6;
    else if (x == "111")    return 7;
    return 0;
}
char dec_charhexa(char x) {
// Pre: Nombre en decimal entre [0, 15]
// Post: Caràcter en hexadecimal entre [0, F]
    if (x >= 0 and x <= 9)  return char('0' + x);
    else    return char('A' + x - 10);
}
int charhexa_dec(char n) {
// Pre: Caràcter en hexadecimal entre [0, F]
// Post: Nombre en decimal entre [0, 15]
    if (n >= '0' and n <= '9')  return int(n - '0');
    else  return int(15 - 'F' + n);
}


int ca2(vector<char>& vector, int mida) {
// Pre: Un vector en binari amb chars {0, 1} i la seva mida
// Post: El valor del vector en Complement a 2 (Ca2)
    int comptador = 0;
    for (int i = mida - 1; i >= 0; --i) {
        if ((i == mida - 1) and vector[i] == '1') {
            comptador -= pow(2, i);
        } else if (vector[i] == '1')
            comptador += pow(2, i);
    }
    return comptador;
}
int suma(vector<char>& vector, int mida) {
// Pre: Un vector en binari amb chars {0, 1} i la seva mida
// Post: El valor del vector sense Ca2
    int comptador = 0;
    for (int i = mida - 1; i >= 0; --i) {
        if (vector[i] == '1') comptador += pow(2, i);
    }
    return comptador;
}


char vectorbin_charhexa(const vector<int> v, int posmin) {
// Pre: Un vector en binari amb chars {0, 1} i la posició
    // inicial on començar a comptar
// Post: Caràcter en hexadecimal entre [0, F] corresponent a 
    // les posicions del vector [posmin, posmin + 3]
    int total = 0;
    for (int i = posmin; i <= posmin + 3; ++i) {
        if (v[i] == 1) total += pow(2, i - posmin);
    }
    return dec_charhexa(total);
}
vector<char> dec_vectorcharbin(int n, int mida) {
// Pre: Un nombre en decimal i la mida que ha de tenir el vector de sortida
// Post: Un vector en binari amb chars {0, 1} i la seva mida
    
    // Numero positiu (vector amb tot '0')
    if (n >= 0) {
        vector<char> vect(mida, '0');
        // Comencem amb n i anem restant fins a rest == 0
        int rest = n;
        int i = vect.size();
        while (i >= 0 and rest > 0) {
            if (pow(2, i) <= rest) {
                vect[i] = '1';
                rest -= pow(2, i);
            }
            --i;
        }
        return vect;
    }
    
    // Nombre negatiu (vector amb tot '1')
    vector<char> vect(mida, '1');
    // Comencem amb FFFF = -1 i anem restant fins a rest == n
    int rest = -1;
    int i = vect.size();
    while (i >= 0 and rest > n) {
        if (rest - pow(2, i) >= n) {
            vect[i] = '0';
            rest -= pow(2, i);
        }
        --i;
    }
    return vect;
}
string dec_stringhexa (int n) {
// Pre: Un nombre en decimal
// Post: String de 4 caràcters en hexadecimal [0000, FFFF]
    vector<char> aux = dec_vectorcharbin(n, 16);
    vector<int> v(16);
    for (int i = 0; i < 16; ++i) v[i] = aux[i] - '0';
    // Cout
    string hexa;
    hexa += vectorbin_charhexa(v, 12);
    hexa += vectorbin_charhexa(v, 8);
    hexa += vectorbin_charhexa(v, 4);
    hexa += vectorbin_charhexa(v, 0);
    return hexa;
}


void escollir_alu(string f) {
// Escolleix l'operacio aritmetico-logica
    if (f == "000") cout << "AND ";
    else if (f == "001")    cout << "OR ";
    else if (f == "010")    cout << "XOR ";
    else if (f == "011")    cout << "NOT ";
    else if (f == "100")    cout << "ADD ";
    else if (f == "101")    cout << "SUB ";
    else if (f == "110")    cout << "SHA ";
    else if (f == "111")    cout << "SHL ";
}
void escollir_cmp(string f) {
// Escolleix la comparacio
    if (f == "000") cout << "CMPLT ";
    else if (f == "001")    cout << "CMPLE ";
    else if (f == "011")    cout << "CMPEQ ";
    else if (f == "100")    cout << "CMPLTU ";
    else if (f == "101")    cout << "CMPLEU ";
}
void escollir_load_store(string f) {
// Escolleix el Load o Store
    if (f == "0011") cout << "LD ";
    else if (f == "0100")   cout << "ST ";
    else if (f == "0101")   cout << "LDB ";
    else if (f == "0110")   cout << "STB ";
}
string escollir_f_cword(string a) {
// Escolleix la F de les operacions aritmetico-logiques i comparacions
    if (a == "CMPLT" or a == "AND" or a == "BZ" or a == "BNZ")  return "000";
    else if (a == "CMPLE" or a == "OR")     return "001";
    else if (a == "MOVHI" or a == "XOR")    return "010";
    else if (a == "CMPEQ" or a == "NOT")    return "011";
    else if (a == "CMPLTU" or a == "ADD" or a == "ADDI")        return "100";
    else if (a == "CMPLEU" or a == "SUB")   return "101";
    else if (a == "SHA")    return "110";
    else if (a == "SHL")    return "111";
    else    return "XXX";
}
string readRx() {
// Llegeix R + Valor Ra/Rb/Rd
    char r;
    int rx;
    cin >> r >> rx;
    return dec_bin(rx);
}

void sortida_cwordv1(const Controlv1& p) {
// Cout Paraula de Control Versio 1
    cout << endl;
    cout << "  @A " << left << setw(14) << setfill(' ') << p.a;
    cout << "@B " << left << setw(9) << setfill(' ') << p.b;
    cout << "Rb/N " << left << setw(6) << setfill(' ') << p.rbn;
    cout << "OP " << left << setw(5) << setfill(' ') << p.op << endl;
    cout << endl;
    cout << "  F  " << left << setw(11) << setfill(' ') << p.f;
    cout << "-i/l/a " << left << setw(8) << setfill(' ') << p.ila;
    cout << "@D " << left << setw(8) << setfill(' ') << p.d;
    cout << "WrD " << left << setw(5) << setfill(' ') << p.wrd << endl;
    cout << endl;
    cout << "Wr-Out " << left << setw(11) << setfill(' ') << p.wrout;
    cout << "Rd-In " << left << setw(5) << setfill(' ') << p.rdin;
    cout << "Wr-Mem " << left << setw(5) << setfill(' ') << p.wrmem;
    cout << "Byte " << left << setw(5) << setfill(' ') << p.byte << endl;
    cout << endl;
    cout << "TknBr  " << left << setw(6) << setfill(' ') << p.tknbr;
    cout << "N(hexa) " << left << setw(10) << setfill(' ') << p.nhexa;
    cout << "ADDR-IO(hexa) " << left << setw(5) << setfill(' ') << p.addrio << endl;
    if (p.addrio != "XX" or p.nhexa != "XXXX") {
        cout << "-----------------------------------------------" << endl;
        cout << "(El número dels ports i les constants s'han d'introduir en decimal.)" << endl;
        cout << "-----------------------------------------------" << endl;
    }
    cout << endl;
}
// Paraula de Control T8-11
void cword_v1() {
    Controlv1 paraula;
    string operation;
    cin >> operation;
    // 2 R (Rd + Ra + N8)
    if (operation == "MOVHI" or operation == "MOVI") {
        // Constants
        paraula.b = "XXX", paraula.rbn = '0';
        paraula.op = "10", paraula.ila = "00";
        // Rd
        paraula.d = readRx();
        // Ra i F
        if (operation == "MOVHI") {
            paraula.a = paraula.d;
            paraula.f = "010";
        }
        else if (operation == "MOVI") {
            paraula.a = "XXX";
            paraula.f = "001";
        }
        //N8
        int n8;
        cin >> n8;
        paraula.nhexa = dec_stringhexa(n8);
        sortida_cwordv1(paraula);
    }
    // 3 R (Rd + Ra + Rb)
    else if (operation == "AND" or operation == "OR" or operation == "XOR" or operation == "ADD" 
    or operation == "SUB" or operation == "SHA" or operation == "SHL" or operation[0] == 'C') {
        // Constants
        paraula.ila = "00", paraula.rbn = '1';
        paraula.nhexa = "XXXX";
        // OP and F
        if (operation[0] == 'C') paraula.op = "01";
        else paraula.op = "00";
        paraula.f = escollir_f_cword(operation);
        // Rd, Ra i Rb
        paraula.d = readRx();
        paraula.a = readRx();
        paraula.b = readRx();
        sortida_cwordv1(paraula);
    }
    // 2R (Ra + N8)
    else if (operation[0] == 'B') {
        // Constants
        paraula.b = "XXX", paraula.rbn = 'X';
        paraula.ila = "XX", paraula.d = "XXX";
        paraula.f = "000", paraula.op = "10";
        paraula.wrd = '0';
        // Ra
        char r;
        int ra;
        cin >> r >> ra;
        paraula.a = dec_bin(ra);
        // N8
        int n8;
        cin >> n8;
        paraula.nhexa = dec_stringhexa(n8*2);
        char resposta;
        cout << 'R' << ra << " és 0? S/N: ";
        cin >> resposta;
        if (operation == "BZ" and (resposta == 'S' or resposta == 's'))
            paraula.tknbr = '1';
        else if (operation == "BNZ" and (resposta == 'N' or resposta == 'n'))
            paraula.tknbr = '1';
        sortida_cwordv1(paraula);
    }
    // In
    else if (operation == "IN") {
        paraula.a = "XXX", paraula.b = "XXX", paraula.rbn = 'X';
        paraula.op = "XX", paraula.f = "XXX", paraula.ila = "10";
        paraula.rdin = '1', paraula.nhexa = "XXXX";
        // Rd
        paraula.d = readRx();
        // ADDR-IO
        int n;
        cin >> n;
        string n8 = dec_stringhexa(n);
        // Eliminem els dos caracters de mes pes
        n8.erase(0, 2);
        paraula.addrio = n8;
        sortida_cwordv1(paraula);
    }
    // Out
    else if (operation == "OUT") {
        paraula.b = "XXX", paraula.rbn = 'X', paraula.op = "XX";
        paraula.f = "XXX", paraula.ila = "XX", paraula.d = "XXX";
        paraula.wrd = '0', paraula.wrout = '1', paraula.nhexa = "XXXX";
        // ADDR-IO
        int n;
        cin >> n;
        string n8 = dec_stringhexa(n);
        // Eliminem els dos caracters de mes pes
        n8.erase(0, 2);
        paraula.addrio = n8;
        // Ra
        paraula.a = readRx();
        sortida_cwordv1(paraula);
    }
    // Addi
    else if (operation == "ADDI") {
        // Constants
        paraula.b = "XXX", paraula.rbn = '0';
        paraula.op = "00", paraula.f = "100";
        paraula.ila = "00";
        // Rd i Ra
        paraula.d = readRx();
        paraula.a = readRx();
        // N6
        int n6;
        cin >> n6;
        paraula.nhexa = dec_stringhexa(n6);
        sortida_cwordv1(paraula);
    }
    // Store i Store byte
    else if (operation == "ST" or operation == "STB") {
        // Constants
        paraula.rbn = '0', paraula.op = "00";
        paraula.f = "100", paraula.ila = "XX";
        paraula.d = "XXX", paraula.wrd = '0';
        paraula.wrmem = '1';
        // Byte
        if (operation == "ST") paraula.byte = '0';
        else paraula.byte = '1';
        // N6
        int n6;
        cin >> n6;
        paraula.nhexa = dec_stringhexa(n6);
        // Ra i Rb
        paraula.a = readRx();
        paraula.b = readRx();
        sortida_cwordv1(paraula);
        
    }
    // Load i Load byte
    else if (operation == "LD" or operation == "LDB") {
        // Constants
        paraula.b = "XXX", paraula.rbn = '0';
        paraula.op = "00", paraula.f = "100";
        paraula.ila = "01";
        // Byte
        if (operation == "LD") paraula.byte = '0';
        else paraula.byte = '1';
        // Rd
        paraula.d = readRx();
        // N6
        int n6;
        cin >> n6;
        paraula.nhexa = dec_stringhexa(n6);
        // Ra
        paraula.a = readRx();
        sortida_cwordv1(paraula);
    }
    else cout << "Valor Incorrecte. No existeix la instrucció." << endl;
}

// Cout Paraula de Control V2
void sortida_cwordv2(const Controlv2& p) {
    cout << endl;
    cout << "  @A " << left << setw(11) << setfill(' ') << p.a;
    cout << "@B " << left << setw(7) << setfill(' ') << p.b;
    cout << "Pc/Rx " << left << setw(5) << setfill(' ') << p.pcrx;
    cout << "Ry/N " << left << setw(8) << setfill(' ') << p.ryn;
    cout << "OP " << left << setw(2) << setfill(' ') << p.op << endl;
    cout << endl;
    cout << "  F  " << left << setw(7) << setfill(' ') << p.f;
    cout << "P/I/L/A " << left << setw(7) << setfill(' ') << p.pila;
    cout << "@D " << left << setw(8) << setfill(' ') << p.d;
    cout << "WrD " << left << setw(5) << setfill(' ') << p.wrd;
    cout << "Wr-Out " << left << setw(3) << setfill(' ') << p.wrout << endl;
    cout << endl;
    cout << " Rd-In " << left << setw(7) << setfill(' ') << p.rdin;
    cout << "Wr-Mem " << left << setw(6) << setfill(' ') << p.wrmem;
    cout << "LdIr " << left << setw(5) << setfill(' ') << p.ldir;
    cout << "LdPc " << left << setw(7) << setfill(' ') << p.ldpc;
    cout << "Byte " << left << setw(2) << setfill(' ') << p.byte << endl;
    cout << endl;
    cout << "Alu/R@ " << left << setw(8) << setfill(' ') << p.alur;
    cout << "R@/Pc " << left << setw(4) << setfill(' ') << p.rpc;
    cout << "N(hexa) " << left << setw(6) << setfill(' ') << p.nhexa;
    cout << "ADDR-IO(hexa) " << left << setw(2) << setfill(' ') << p.addrio << endl;
    cout << endl;
    cout << "Els valors entre () representen que són X." << endl;
    if (p.addrio != "XX" or p.nhexa != "XXXX") {
        cout << "-------------------------------------------------------" << endl;
        cout << "(El número dels ports i les constants s'han d'introduir en decimal.)" << endl;
        cout << "-------------------------------------------------------" << endl;
    cout << endl;
    }
}
// Paraula de Control T12-14
void cword_v2() {
    Controlv2 paraula;
    string operation;
    cin >> operation;
    // 2 R (Rd + Ra + N8)
    if (operation == "MOVHI" or operation == "MOVI") {
        // Constants
        paraula.ryn = '0';
        paraula.op = "10", paraula.pila = "00";
        // Rd
        char firstR;
        int rd;
        cin >> firstR >> rd;
        paraula.d = readRx();
        paraula.a = '(' + paraula.d + ')';
        // Completar
        if (operation == "MOVHI") {
            paraula.pcrx = '0';
            paraula.f = "010", paraula.b = "1";
        }
        else {
            paraula.pcrx = 'X';
            paraula.f = "001", paraula.b = "0";
        }
        //N8
        int n8;
        cin >> n8;
        paraula.nhexa = dec_stringhexa(n8);
        // ADDR-IO
        string number = paraula.nhexa;
        // Eliminem els dos caracters de mes pes
        number.erase(0, 2);
        paraula.addrio = '(' + number + ')';
        // Rb = (1/0 + Dos digits de mes pes de N8)
        vector<char> v = dec_vectorcharbin(n8, 8);
        paraula.b += v[7];
        paraula.b += v[6];
        paraula.b = '(' + paraula.b + ')';
        // Cout
        sortida_cwordv2(paraula);
    }

    // 3 R (Rd + Ra + Rb)
    else if (operation == "AND" or operation == "OR" or operation == "XOR" or operation == "ADD" 
    or operation == "SUB" or operation == "SHA" or operation == "SHL" or operation[0] == 'C') {
        // Constants
        paraula.pcrx = '0', paraula.ryn = '1';
        paraula.pila = "00", paraula.nhexa = "XXXX";
        // OP and F
        if (operation[0] == 'C') paraula.op = "01";
        else paraula.op = "00";
        paraula.f = escollir_f_cword(operation);
        // Rd, Ra i Rb
        paraula.d = readRx();
        paraula.a = '(' + readRx() + ')';
        paraula.b = '(' + readRx() + ')';
        // ADDR-IO (ultims 8 bits = 2bits de menys pes de b + d + f)
        vector<int> v(8);
        v[7] = paraula.b[2] - '0', v[6] = paraula.b[3] - '0';
        v[5] = paraula.d[0] - '0', v[4] = paraula.d[1] - '0', v[3] = paraula.d[2] - '0';
        v[2] = paraula.f[0] - '0', v[1] = paraula.f[1] - '0', v[0] = paraula.f[2] - '0';
        string addrio = "";
        addrio += vectorbin_charhexa(v, 4);
        addrio += vectorbin_charhexa(v, 0);
        paraula.addrio = '(' + addrio + ')';
        // Cout 
        sortida_cwordv2(paraula);
    }
    
    // 2R (Ra + N8)
    else if (operation[0] == 'B') {
        // Constants
        paraula.pcrx = '0', paraula.ryn = 'X', paraula.op = "10";
        paraula.f = "000", paraula.pila = "XX", paraula.d = "XXX";
        paraula.wrd = '0', paraula.alur = '0', paraula.nhexa = "XXXX";
        
        // Ra
        char firstR;
        int ra;
        cin >> firstR >> ra;
        paraula.a = '(' + readRx() + ')';
        
        // N8 (en veritat ADDRIO)
        // N8 es mostra en el estat Decode i es multiplica per 2
        int n;
        cin >> n;
        string n8 = dec_stringhexa(n);
        // Eliminem els dos caracters de mes pes
        n8.erase(0, 2);
        paraula.addrio = n8;
        
        // LdPC
        char resposta;
        cout << 'R' << ra << " és 0? S/N: ";
        cin >> resposta;
        if (operation == "BZ" and (resposta == 'S' or resposta == 's'))
            paraula.ldpc = '1';
        else if (operation == "BNZ" and (resposta == 'N' or resposta == 'n'))
            paraula.ldpc = '1';
            
        // Rb = (1/0 + Dos digits de mes pes de N8)
        if (operation == "BZ") paraula.b = '0';
        else paraula.b = '1';
        vector<char> v = dec_vectorcharbin(n, 8);
        paraula.b += v[7];
        paraula.b += v[6];
        paraula.b = '(' + paraula.b + ')';
        // Cout 
        sortida_cwordv2(paraula);
    }

    // In
    else if (operation == "IN") {
        paraula.pcrx = 'X', paraula.ryn = 'X';
        paraula.op = "XX", paraula.f = "XXX";
        paraula.pila = "10", paraula.rdin = '1';
        paraula.rpc = 'X', paraula.nhexa = "XXXX";
        // Rd i Ra
        paraula.d = readRx();
        paraula.a = '(' + paraula.d + ')';
        // ADDR-IO
        int n;
        cin >> n;
        string n8 = dec_stringhexa(n);
        // Eliminem els dos caracters de mes pes
        n8.erase(0, 2);
        paraula.addrio = n8;
        // Rb = 0 + 2 digits de mes pes de N8
        string rb = "0";
        vector<char> vn8 = dec_vectorcharbin(n, 8);
        rb += vn8[7];
        rb += vn8[6];
        paraula.b = '(' + rb + ')';
        // Cout
        sortida_cwordv2(paraula);
    }
    
    // Out
    else if (operation == "OUT") {
        // Constants
        paraula.pcrx = 'X', paraula.ryn = 'X';
        paraula.op = "XX", paraula.f = "XXX";
        paraula.pila = "XX", paraula.d = "XXX";
        paraula.wrd = '0', paraula.wrout = '1';
        paraula.rpc = 'X', paraula.nhexa = "XXXX";
        // ADDR-IO
        int n;
        cin >> n;
        string n8 = dec_stringhexa(n);
        // Eliminem els dos caracters de mes pes
        n8.erase(0, 2);
        paraula.addrio = n8;
        // Ra
        paraula.a = '(' + readRx() + ')';
        // Rb = 1 + 2 digits de mes pes de N8
        string rb = "1";
        vector<char> vn8 = dec_vectorcharbin(n, 8);
        rb += vn8[7];
        rb += vn8[6];
        paraula.b = '(' + rb + ')';
        // Cout
        sortida_cwordv2(paraula);
    }
    
    // Addi
    else if (operation == "ADDI") {
        // Constants
        paraula.pcrx = '0', paraula.ryn = '0';
        paraula.op = "00", paraula.f = "100";
        paraula.pila = "00";
        // Rd, Rb i Ra
        paraula.d = readRx();
        paraula.b = '(' + paraula.d + ')';
        paraula.a = '(' + readRx() + ')';
        // N6
        int n6;
        cin >> n6;
        paraula.nhexa = dec_stringhexa(n6);
        // ADDR-IO (ultims 8 bits = 2bits de menys pes de D + N6)
        vector<int> v(4);
        v[3] = paraula.d[1] - '0', v[2] = paraula.d[2] - '0';
        vector<char> vn6 = dec_vectorcharbin(n6, 6);
        v[1] = vn6[5] - '0', v[0] = vn6[4] - '0';
        string addrio = "";
        addrio += vectorbin_charhexa(v, 0);
        addrio += paraula.nhexa[3];
        paraula.addrio = '(' + addrio + ')';
        // Cout
        sortida_cwordv2(paraula);
    }
    
    // Store i Store byte
    else if (operation == "ST" or operation == "STB") {
        // Constants
        paraula.pcrx = 'X', paraula.ryn = 'X';
        paraula.op = "XX", paraula.f = "XXX";
        paraula.pila = "XX", paraula.d = "XXX";
        paraula.wrd = '0', paraula.wrmem = '1';
        paraula.rpc = '1', paraula.nhexa = "XXXX";
        // Byte
        if (operation == "ST") paraula.byte = '0';
        else paraula.byte = '1';
        // N6
        int n6;
        cin >> n6;
            // N es mostra en l'estat Addr
        // Ra i Rb
        paraula.a = '(' + readRx() + ')';
        paraula.b = '(' + readRx() + ')';
        // ADDR-IO (ultims 8 bits = 2bits de menys pes de B + N6)
        vector<int> v(4);
        v[3] = paraula.b[2] - '0', v[2] = paraula.b[3] - '0';
        vector<char> vn6 = dec_vectorcharbin(n6, 6);
        v[1] = vn6[5] - '0', v[0] = vn6[4] - '0';
        string addrio = "";
        addrio += vectorbin_charhexa(v, 0);
        addrio += dec_stringhexa(n6)[3];
        paraula.addrio = '(' + addrio + ')';
        // Cout
        sortida_cwordv2(paraula);
        
    }
    
    // Load i Load byte
    else if (operation == "LD" or operation == "LDB") {
        // Constants
        paraula.pcrx = 'X', paraula.ryn = 'X';
        paraula.op = "XX", paraula.f = "XXX";
        paraula.pila = "01", paraula.rpc = '1';
        paraula.nhexa = "XXXX";
        // Byte
        if (operation == "LD") paraula.byte = '0';
        else paraula.byte = '1';
        // Rd (i Rb)
        paraula.d = readRx();
        paraula.b = '(' + paraula.d + ')';
        // N6
        int n6;
        cin >> n6;
        // Ra
        paraula.a = '(' + readRx() + ')';
        // ADDR-IO (ultims 8 bits = 2bits de menys pes de B + N6)
        vector<int> v(4);
        v[3] = paraula.b[2] - '0', v[2] = paraula.b[3] - '0';
        vector<char> vn6 = dec_vectorcharbin(n6, 6);
        v[1] = vn6[5] - '0', v[0] = vn6[4] - '0';
        string addrio = "";
        addrio += vectorbin_charhexa(v, 0);
        addrio += dec_stringhexa(n6)[3];
        paraula.addrio = '(' + addrio + ')';
        // Cout
        sortida_cwordv2(paraula);
    }
    
    // Jalr
    else if (operation == "JALR") {
            // Constants
            paraula.pcrx = '0', paraula.ryn = 'X';
            paraula.op = "10", paraula.f = "011";
            paraula.pila = "11", paraula.ldpc = '1';
            paraula.alur = '1', paraula.rpc = 'X';
            paraula.nhexa = "XXXX";
            // Rd, Ra i Rb
            paraula.d = readRx();
            paraula.a = '(' + readRx() + ')';
            paraula.b = '(' + paraula.d + ')';
            sortida_cwordv2(paraula);
    }
    
    // Fetch
    else if (operation == "F") {
        // Constants
        paraula.pcrx = '1', paraula.ryn = '0';
        paraula.op = "00", paraula.f = "100";
        paraula.pila = "XX", paraula.d = "XXX";
        paraula.wrd = '0', paraula.ldir = '1';
        paraula.ldpc = '1', paraula.byte = '0';
        paraula.alur = '1', paraula.rpc = '0';
        paraula.nhexa = "0002";
        // (Ara mateix falta saber Ra, Rb i ADDR-IO)
        // Operation 2 
        cin >> operation;
            // 2 R (Rd + Ra + N8)
        if (operation == "MOVHI" or operation == "MOVI") {
            // Rd
            paraula.a = '(' + readRx() + ')';
            // Completar
            if (operation == "MOVHI") paraula.b = "1";
            else paraula.b = "0";
            //N8
            int n8;
            cin >> n8;
            // ADDR-IO
            string number = dec_stringhexa(n8);
            // Eliminem els dos caracters de mes pes
            number.erase(0, 2);
            paraula.addrio = '(' + number + ')';
            // Rb = (1/0 + Dos digits de mes pes de N8)
            vector<char> v = dec_vectorcharbin(n8, 8);
            paraula.b += v[7];
            paraula.b += v[6];
            paraula.b = '(' + paraula.b + ')';
            // Cout
            sortida_cwordv2(paraula);
        }
    
        // 3 R (Rd + Ra + Rb)
        else if (operation == "AND" or operation == "OR" or operation == "XOR" or operation == "ADD" 
        or operation == "SUB" or operation == "SHA" or operation == "SHL" or operation[0] == 'C') {
            // Rd
            string d = readRx();
            // Ra
            paraula.a = '(' + readRx() + ')';
            // Rb
            paraula.b = '(' + readRx() + ')';
            // ADDR-IO (ultims 8 bits = 2bits de menys pes de b + d + f)
            vector<int> v(8);
            v[7] = paraula.b[2] - '0', v[6] = paraula.b[3] - '0';
            v[5] = d[0] - '0', v[4] = d[1] - '0', v[3] = d[2] - '0';
            v[2] = paraula.f[0] - '0', v[1] = paraula.f[1] - '0', v[0] = paraula.f[2] - '0';
            string addrio = "";
            addrio += vectorbin_charhexa(v, 4);
            addrio += vectorbin_charhexa(v, 0);
            paraula.addrio = '(' + addrio + ')';
            // Cout 
            sortida_cwordv2(paraula);
        }
        // 2R (Ra + N8)
        else if (operation[0] == 'B') {
            // Ra
            paraula.a = '(' + readRx() + ')';
            // N8 (en veritat ADDRIO)
            // N8 es mostra en el estat Decode
            int n;
            cin >> n;
            string n8 = dec_stringhexa(n);
            // Eliminem els dos caracters de mes pes
            n8.erase(0, 2);
            paraula.addrio = n8;
            // Rb = (1/0 + Dos digits de mes pes de N8)
            if (operation == "BZ") paraula.b = '0';
            else paraula.b = '1';
            vector<char> v = dec_vectorcharbin(n, 8);
            paraula.b += v[7];
            paraula.b += v[6];
            paraula.b = '(' + paraula.b + ')';
            // Cout 
            sortida_cwordv2(paraula);
        }
            // IN
        else if (operation == "IN") {
            // Ra (que es Rd en teoria)
            paraula.a = '(' + readRx() + ')';
            // ADDR-IO
            int n;
            cin >> n;
            string n8 = dec_stringhexa(n);
            // Eliminem els dos caracters de mes pes
            n8.erase(0, 2);
            paraula.addrio = '(' + n8 + ')';
            // Rb = 0 + 2 digits de mes pes de N8
            string rb = "0";
            vector<char> vn8 = dec_vectorcharbin(n, 8);
            rb += vn8[7];
            rb += vn8[6];
            paraula.b = '(' + rb + ')';
            // Cout
            sortida_cwordv2(paraula);
        }
            // OUT
        else if (operation == "OUT") {
            // ADDR-IO
            int n;
            cin >> n;
            string n8 = dec_stringhexa(n);
            // Eliminem els dos caracters de mes pes
            n8.erase(0, 2);
            paraula.addrio = '(' + n8 + ')';
            // Ra
            paraula.a = '(' + readRx() + ')';
            // Rb = 1 + 2 digits de mes pes de N8
            string rb = "1";
            vector<char> vn8 = dec_vectorcharbin(n, 8);
            rb += vn8[7];
            rb += vn8[6];
            paraula.b = '(' + rb + ')';
            // Cout
            sortida_cwordv2(paraula);
        }
            // Addi
        else if (operation == "ADDI") {
            // Rb i Ra
            paraula.b = '(' + readRx() + ')';
            paraula.a = '(' + readRx() + ')';
            // N6
            int n6;
            cin >> n6;
            // ADDR-IO (ultims 8 bits = 2bits de menys pes de D + N6)
            vector<int> v(4);
            v[3] = paraula.b[2] - '0', v[2] = paraula.b[3] - '0';
            vector<char> vn6 = dec_vectorcharbin(n6, 6);
            v[1] = vn6[5] - '0', v[0] = vn6[4] - '0';
            string addrio = "";
            addrio += vectorbin_charhexa(v, 0);
            addrio += dec_stringhexa(n6)[3];
            paraula.addrio = '(' + addrio + ')';
            // Cout
            sortida_cwordv2(paraula);
        }
            // Store i Store byte
        else if (operation == "ST" or operation == "STB") {
            // N6
            int n6;
            cin >> n6;
            // Ra i Rb
            paraula.a = '(' + readRx() + ')';
            paraula.b = '(' + readRx() + ')';
            // ADDR-IO (ultims 8 bits = 2bits de menys pes de B + N6)
            vector<int> v(4);
            v[3] = paraula.b[2] - '0', v[2] = paraula.b[3] - '0';
            vector<char> vn6 = dec_vectorcharbin(n6, 6);
            v[1] = vn6[5] - '0', v[0] = vn6[4] - '0';
            string addrio = "";
            addrio += vectorbin_charhexa(v, 0);
            addrio += dec_stringhexa(n6)[3];
            paraula.addrio = '(' + addrio + ')';
            // Cout
            sortida_cwordv2(paraula);
        }
            // Load i Load byte
        else if (operation == "LD" or operation == "LDB") {
            // Rb (en teoria Rd)
            paraula.b = '(' + readRx() + ')';
            // N6
            int n6;
            cin >> n6;
            // Ra
            paraula.a = '(' + readRx() + ')';
            // ADDR-IO (ultims 8 bits = 2bits de menys pes de B + N6)
            vector<int> v(4);
            v[3] = paraula.b[2] - '0', v[2] = paraula.b[3] - '0';
            vector<char> vn6 = dec_vectorcharbin(n6, 6);
            v[1] = vn6[5] - '0', v[0] = vn6[4] - '0';
            string addrio = "";
            addrio += vectorbin_charhexa(v, 0);
            addrio += dec_stringhexa(n6)[3];
            paraula.addrio = '(' + addrio + ')';
            // Cout
            sortida_cwordv2(paraula);
        }
            // Jalr
        else if (operation == "JALR") {
            // Rb i Ra
            paraula.b = '(' + readRx() + ')';
            paraula.a = '(' + readRx() + ')';  
            // ADDR-IO
            paraula.addrio = "XX"; 
            // Cout
            sortida_cwordv2(paraula); 
        }
        
        else cout << "No disponible / No existeix" << endl;

    }
    
    // Decode
    else if (operation == "D") {
        // Constants 
        paraula.pcrx = '1', paraula.ryn = '0';
        paraula.op = "00", paraula.f = "100";
        paraula.pila = "XX", paraula.d = "XXX";
        paraula.wrd = '0', paraula.ldir = '0';
        cin >> operation;
        // (Ara mateix falta saber Ra, Rb, ADDR-IO i NHEXA = (N*2))
        
        // 2 R (Rd + Ra + N8)
        if (operation == "MOVHI" or operation == "MOVI") {
            // Rd
            paraula.a = readRx();
            
            // Completar
            if (operation == "MOVHI") paraula.b = "1";
            else paraula.b = "0";
            //N8
            int n8;
            cin >> n8;
            // Totes les N del D es multipliquen per 2
            paraula.nhexa = dec_stringhexa(n8*2);
            
            // ADDR-IO
            string number = dec_stringhexa(n8);
            // Eliminem els dos caracters de mes pes
            number.erase(0, 2);
            paraula.addrio = '(' + number + ')';
            
            // Rb = (1/0 + Dos digits de mes pes de N8)
            vector<char> v = dec_vectorcharbin(n8, 8);
            paraula.b += v[7];
            paraula.b += v[6];
            paraula.b = '(' + paraula.b + ')';
            // Cout
            sortida_cwordv2(paraula);
        }
        // 3 R (Rd + Ra + Rb)
        else if (operation == "AND" or operation == "OR" or operation == "XOR" or operation == "ADD" 
        or operation == "SUB" or operation == "SHA" or operation == "SHL" or operation[0] == 'C') {
            // Rd, Ra i Rb
            string d = readRx();
            paraula.a = readRx();
            paraula.b = readRx();
            // ADDR-IO (ultims 8 bits = 2bits de menys pes de b + d + f)
            vector<int> v(8);
            v[7] = paraula.b[1] - '0', v[6] = paraula.b[2] - '0';
            v[5] = d[0] - '0', v[4] = d[1] - '0', v[3] = d[2] - '0';
            v[2] = paraula.f[0] - '0', v[1] = paraula.f[1] - '0', v[0] = paraula.f[2] - '0';
            string addrio = "";
            addrio += vectorbin_charhexa(v, 4);
            addrio += vectorbin_charhexa(v, 0);
            paraula.addrio = '(' + addrio + ')';
            // NHEXA (es multiplica per 2)
            vector<char> vchar(8);
            for (int i = 0; i < 8; ++i) vchar[i] = v[i] + '0';
            int nhexa = ca2(vchar, 8);
            paraula.nhexa = dec_stringhexa(nhexa*2);
            // Cout 
            sortida_cwordv2(paraula);
        }
        // 2R (Ra + N8)
        else if (operation[0] == 'B') {
            // Ra
            paraula.a = readRx();
            // N8 i ADDRIO
            int n;
            cin >> n;
            paraula.nhexa = dec_stringhexa(n*2);
            string n8 = dec_stringhexa(n);
            // Eliminem els dos caracters de mes pes
            n8.erase(0, 2);
            paraula.addrio = n8;
            // Rb = (1/0 + Dos digits de mes pes de N8)
            if (operation == "BZ") paraula.b = '0';
            else paraula.b = '1';
            vector<char> v = dec_vectorcharbin(n, 8);
            paraula.b += v[7];
            paraula.b += v[6];
            paraula.b = '(' + paraula.b + ')';
            // Cout 
            sortida_cwordv2(paraula);
        }
            // IN
        else if (operation == "IN") {
            // Ra (que es Rd en teoria)
            paraula.a = '(' + readRx() + ')';
            // ADDR-IO
            int n;
            cin >> n;
            paraula.nhexa = dec_stringhexa(n*2);
            string n8 = dec_stringhexa(n);
            // Eliminem els dos caracters de mes pes
            n8.erase(0, 2);
            paraula.addrio = '(' + n8 + ')';
            // Rb = 0 + 2 digits de mes pes de N8
            string rb = "0";
            vector<char> vn8 = dec_vectorcharbin(n, 8);
            rb += vn8[7];
            rb += vn8[6];
            paraula.b = '(' + rb + ')';
            // Cout
            sortida_cwordv2(paraula);
        }
            // OUT
        else if (operation == "OUT") {
            // ADDR-IO
            int n;
            cin >> n;
            paraula.nhexa = dec_stringhexa(n*2);
            string n8 = dec_stringhexa(n);
            // Eliminem els dos caracters de mes pes
            n8.erase(0, 2);
            paraula.addrio = '(' + n8 + ')';
            // Ra
            paraula.a = '(' + readRx() + ')';
            // Rb = 1 + 2 digits de mes pes de N8
            string rb = "1";
            vector<char> vn8 = dec_vectorcharbin(n, 8);
            rb += vn8[7];
            rb += vn8[6];
            paraula.b = '(' + rb + ')';
            // Cout
            sortida_cwordv2(paraula);
        }
            // Addi
        else if (operation == "ADDI") {
            // Rb (en teoria Rd) i Ra
            paraula.b = readRx();
            paraula.a = readRx();
            // N6
            int n6;
            cin >> n6;
            // ADDR-IO (ultims 8 bits = 2bits de menys pes de D + N6)
            vector<int> v(4);
            v[3] = paraula.b[1] - '0', v[2] = paraula.b[2] - '0';
            vector<char> vn6 = dec_vectorcharbin(n6, 6);
            v[1] = vn6[5] - '0', v[0] = vn6[4] - '0';
            string addrio = "";
            addrio += vectorbin_charhexa(v, 0);
            addrio += dec_stringhexa(n6)[3];
            paraula.addrio = '(' + addrio + ')';
            // NHEXA (es multiplica per 2)
            vector<char> vchar(8);
            for (int i = 0; i < 8; ++i) vchar[i] = vn6[i] + '0';
            int nhexa = ca2(vchar, 8);
            paraula.nhexa = dec_stringhexa(nhexa*2);
            // Cout
            sortida_cwordv2(paraula);
        }
            // Store i Store byte
        else if (operation == "ST" or operation == "STB") {
            // N6 Part 1 
            int n6;
            cin >> n6;
            // Ra i Rb
            paraula.a = readRx();
            paraula.b = readRx();
            // ADDR-IO (ultims 8 bits = 2bits de menys pes de B + N6)
            vector<int> v(4);
            v[3] = paraula.b[1] - '0', v[2] = paraula.b[2] - '0';
            vector<char> vn6 = dec_vectorcharbin(n6, 6);
            v[1] = vn6[5] - '0', v[0] = vn6[4] - '0';
            string addrio = "";
            addrio += vectorbin_charhexa(v, 0);
            addrio += dec_stringhexa(n6)[3];
            paraula.addrio = '(' + addrio + ')';
            // N6 Part 2 (SE(N6)*2) [Faig part 2 perquè hem falta saber el valor de Rb]
            vector<char> vect = dec_vectorcharbin(n6, 16);
            vect[6] = paraula.b[2], vect[7] = paraula.b[1];
                // Extensio de signe
            for (int i = 8; i <= 15; ++i) vect[i] = vect[7];
            vector<int> vectn6(16);
            for (int i = 0; i <= 15; ++i) vectn6[i] = vect[i] - '0';
            int totalnhexa = ca2(vect, 16);
            totalnhexa *= 2;
            paraula.nhexa = dec_stringhexa(totalnhexa);
            // Cout
            sortida_cwordv2(paraula);
        }
            // Load i Load byte
        else if (operation == "LD" or operation == "LDB") {
            // Rb (en teoria Rd)
            paraula.b = readRx();
            // N6 Part 1 
            int n6;
            cin >> n6;
            // Ra
            paraula.a = '(' + readRx() + ')';
            // ADDR-IO (ultims 8 bits = 2bits de menys pes de B + N6)
            vector<int> v(4);
            v[3] = paraula.b[1] - '0', v[2] = paraula.b[2] - '0';
            vector<char> vn6 = dec_vectorcharbin(n6, 6);
            v[1] = vn6[5] - '0', v[0] = vn6[4] - '0';
            string addrio = "";
            addrio += vectorbin_charhexa(v, 0);
            addrio += dec_stringhexa(n6)[3];
            paraula.addrio = '(' + addrio + ')';
            // N6 Part 2 (SE(N6)*2) [Faig part 2 perquè hem falta saber el valor de Rb]
            vector<char> vect = dec_vectorcharbin(n6, 16);
            vect[6] = paraula.b[2], vect[7] = paraula.b[1];
                // Extensio de signe
            for (int i = 8; i <= 15; ++i) vect[i] = vect[7];
            vector<int> vectn6(16);
            for (int i = 0; i <= 15; ++i) vectn6[i] = vect[i] - '0';
            int totalnhexa = ca2(vect, 16);
            totalnhexa *= 2;
            paraula.nhexa = dec_stringhexa(totalnhexa);
            // Cout
            sortida_cwordv2(paraula);
        }
            // Jalr (Falta Comprovar)
        else if (operation == "JALR") {
            // Rb i Ra
            paraula.b = readRx();
            paraula.a = readRx();  
            // ADDR-IO
            paraula.addrio = "XX";
            paraula.nhexa = "XXXX"; 
            // Cout
            sortida_cwordv2(paraula); 
        }
        else cout << "No disponible / No existeix" << endl;
    }
    
    // ADDR
    else if (operation == "ADDR") {
        // Constants 
        paraula.pcrx = '0', paraula.ryn = '0';
        paraula.op = "00", paraula.f = "100";
        paraula.pila = "XX", paraula.d = "XXX";
        paraula.wrd = '0', paraula.ldir = '0';
        // Operation 2
        cin >> operation;
        // Completar
            // Store i Store byte
        if (operation == "ST" or operation == "STB") {
        // N6
        int n6;
        cin >> n6;
        paraula.nhexa = dec_stringhexa(n6);
        // Ra i Rb
        paraula.a = '(' + readRx() + ')';
        paraula.b = '(' + readRx() + ')';
        // ADDR-IO (ultims 8 bits = 2bits de menys pes de B + N6)
        vector<int> v(4);
        v[3] = paraula.b[2] - '0', v[2] = paraula.b[3] - '0';
        vector<char> vn6 = dec_vectorcharbin(n6, 6);
        v[1] = vn6[5] - '0', v[0] = vn6[4] - '0';
        string addrio = "";
        addrio += vectorbin_charhexa(v, 0);
        addrio += dec_stringhexa(n6)[3];
        paraula.addrio = '(' + addrio + ')';
        // Cout
        sortida_cwordv2(paraula);
    }
            // Load i Load byte
        else if (operation == "LD" or operation == "LDB") {
        // Rb (en teoria Rd)
        paraula.b = '(' + readRx() + ')';
        // N6
        int n6;
        cin >> n6;
        paraula.nhexa = dec_stringhexa(n6);
        // Ra
        paraula.a = '(' + readRx() + ')';
        // ADDR-IO (ultims 8 bits = 2bits de menys pes de B + N6)
        vector<int> v(4);
        v[3] = paraula.b[2] - '0', v[2] = paraula.b[3] - '0';
        vector<char> vn6 = dec_vectorcharbin(n6, 6);
        v[1] = vn6[5] - '0', v[0] = vn6[4] - '0';
        string addrio = "";
        addrio += vectorbin_charhexa(v, 0);
        addrio += dec_stringhexa(n6)[3];
        paraula.addrio = '(' + addrio + ')';
        // Cout
        sortida_cwordv2(paraula);
    }
        
        else cout << "No disponible / No existeix" << endl;
    }
    
    else cout << "Valor Incorrecte. No existeix la instrucció." << endl;
}


void to_vector(vector<char>& vector, int n, int i) {
// Passa d'un nombre en decimal [0, 15] al seu equivalent binari en chars
    // a les posicions [i - 3, i] d'un vector en binari {0, 1}

    // Els 0 ja estan posats a l crear el vector
    if (n == 1) vector[i - 3] = '1';
    else if (n == 2)    vector[i - 2] = '1';
    else if (n == 3)    vector[i - 2] = '1', vector[i - 3] = '1';
    else if (n == 4)    vector[i - 1] = '1';
    else if (n == 5)    vector[i - 1] = '1', vector[i - 3] = '1';
    else if (n == 6)    vector[i - 1] = '1', vector[i - 2] = '1';
    else if (n == 7)    vector[i - 1] = '1', vector[i - 2] = '1', vector[i - 3] = '1';
    else if (n == 8)    vector[i] = '1';
    else if (n == 9)    vector[i] = '1', vector[i - 3] = '1';
    else if (n == 10)   vector[i] = '1', vector[i - 2] = '1';
    else if (n == 11)   vector[i] = '1', vector[i - 2] = '1', vector[i - 3] = '1';
    else if (n == 12)   vector[i] = '1', vector[i - 1] = '1';
    else if (n == 13)   vector[i] = '1', vector[i - 1] = '1', vector[i - 3] = '1';
    else if (n == 14)   vector[i] = '1', vector[i - 1] = '1', vector[i - 2] = '1';
    else if (n == 15)   vector[i] = '1', vector[i - 1] = '1', vector[i - 2] = '1', vector[i - 3] = '1';
}
// Passa d'hexa a Mnemotecnic SISA
void program_hexa() {
    // Cin dels 4 caracters en hexa
    char a, b, c, d;
    cin >> a >> b >> c >> d;

    // Passem d'hexa a decimal
    int primer = charhexa_dec(a), segon = charhexa_dec(b);
    int tercer = charhexa_dec(c), quart = charhexa_dec(d);

    // Creem un vector on passarem la instruccio d'hexa a binari
    // L'inicialitzem amb un 0 en cada posicio
    vector<char> vector(16, '0');
    
    // Emplenem el vector amb els seus valors en binari
    to_vector(vector, primer, 15); // [15-12]
    to_vector(vector, segon, 11);  // [11-8]
    to_vector(vector, tercer, 7);  // [7-4]
    to_vector(vector, quart, 3);   // [3-0]

    // Obtenim els primers quatre digits [15-12] i Ra [11-9]
    string first4 = "";
    for (int i = 15; i >= 12; --i)
        first4 += vector[i];
    string a_sisa = "";
    for (int i = 11; i >= 9; --i)
        a_sisa += vector[i];

    // Primera classificacio ALU
    if (first4 == "0000") {
        // Obtenim Rb, Rd i F
        string b_sisa = "", d_sisa = "", f_sisa = "";
        for (int i = 8; i >= 6; --i)
            b_sisa += vector[i]; // Rb = [8-6]
        for (int i = 5; i >= 3; --i)
            d_sisa += vector[i]; // Rd = [5-3]
        for (int i = 2; i >= 0; --i)
            f_sisa += vector[i]; // F = [2-0]
        escollir_alu(f_sisa); // cout << "Instruccio AL"
        cout << 'R' << bin_dec(d_sisa) << ", ";
        cout << 'R' << bin_dec(a_sisa) << ", ";
        cout << 'R' << bin_dec(b_sisa) << endl;
    }

    // Segona classificacio CMP
    else if (first4 == "0001") {
        // Obtenim Rb, Rd i F
        string b_sisa = "", d_sisa = "", f_sisa = "";
        for (int i = 8; i >= 6; --i)
            b_sisa += vector[i]; // Rb = [8-6]
        for (int i = 5; i >= 3; --i)
            d_sisa += vector[i]; // Rd = [5-3]
        for (int i = 2; i >= 0; --i)
            f_sisa += vector[i]; // F = [2-0]
        escollir_cmp(f_sisa); // cout << "Instruccio CMP"
        cout << 'R' << bin_dec(d_sisa) << ", ";
        cout << 'R' << bin_dec(a_sisa) << ", ";
        cout << 'R' << bin_dec(b_sisa) << endl;
    }

    // Tercera classificacio ADDI
    else if (first4 == "0010") {
        cout << "ADDI ";
        string d_sisa = "", n_sisa = "";
        int n_ca2 = ca2(vector, 6); // Calcula N6 en ca2
        for (int i = 8; i >= 6; --i)
            d_sisa += vector[i]; // Rd = [8-6]
        for (int i = 5; i >= 0; --i)
            n_sisa += vector[i]; // N6 = [5-0]
        cout << 'R' << bin_dec(d_sisa) << ", ";
        cout << 'R' << bin_dec(a_sisa) << ", ";
        cout << n_ca2 << endl;
    }

    // Quarta classificacio Load/Store
    else if (first4 == "0011" or first4 == "0100" or first4 == "0101" or first4 == "0110") {
        escollir_load_store(first4); // cout << "Instruccio Load/Store"
        int n_sisa = ca2(vector, 6); // Calcula N6 en ca2
        string b_sisa = "";
        for (int i = 8; i >= 6; --i)
            b_sisa += vector[i]; // Rb = [8-6]

        // Load
        if (first4 == "0011" or first4 == "0101") {
            cout << 'R' << bin_dec(b_sisa) << ", ";
            cout << n_sisa << "(R";
            cout << bin_dec(a_sisa) << ')' << endl;
        }
        // Store
        else if (first4 == "0100" or first4 == "0110") {
            cout << n_sisa << "(R";
            cout << bin_dec(a_sisa) << "), R";
            cout << bin_dec(b_sisa) << endl;
        }
    }

    /// Cinquena classificacio JALR
    else if (first4 == "0111") {
        string d_sisa = "";
        for (int i = 8; i >= 6; --i)
            d_sisa += vector[i]; // Rd = [8-6]
        cout << "JALR ";
        cout << 'R' << bin_dec(d_sisa) << ", ";
        cout << 'R' << bin_dec(a_sisa) << endl;
    }
    
    // Sisena classificacio BZ/BNZ
    else if (first4 == "1000") {
        // El vector[8] decideix si es BZ o BNZ
        if (vector[8] == '0')      cout << "BZ ";
        else if (vector[8] == '1') cout << "BNZ ";
        cout << 'R' << bin_dec(a_sisa) << ", 0x";
        int n_ca2 = ca2(vector, 8);
        // Fem l'extensió de signe de N8
        if (vector[7] == '1')       cout << "FF";
        else if (vector[7] == '0')  cout << "00";
        cout << c << d << '(' << n_ca2 << ')' << endl;
    }

    // Setena classificacio MOVI/MOVHI
    else if (first4 == "1001") {
        int n_ca2 = ca2(vector, 8);
        if (vector[8] == '0') {
            cout << "MOVI ";
            cout << 'R' << bin_dec(a_sisa) << ", ";
            cout << "0x" << c << d << '(' << n_ca2 << ')' << endl;
        } else if (vector[8] == '1') {
            cout << "MOVHI ";
            cout << 'R' << bin_dec(a_sisa) << ", 0x";
            if (vector[7] == '1')       cout << "FF";
            else if (vector[7] == '0')  cout << "00";
            cout << c << d << '(' << n_ca2 << ')' << endl;
        }
    }

    // Vuitena classificacio IN/OUT
    else if (first4 == "1010") {
        int n_suma = suma(vector, 8);
        if (vector[8] == '0') {
            cout << "IN ";
            cout << 'R' << bin_dec(a_sisa) << ", ";
            cout << "0x" << c << d << '(' << n_suma << ')' << endl;
        } else if (vector[8] == '1') {
            cout << "OUT 0x";
            cout << c << d << '(' << n_suma << ')' << ", ";
            cout << 'R' << bin_dec(a_sisa) << endl;
        }
    }
    
    else cout << "Número incorrecte." << endl;
}

string actualitza_pc(string spc, int x) {
// Pre: String en hexadecimal de 4 dígits i increment en decimal 
// Post: String en hexadecimal de 4 dígits = spc + x
    int pc = charhexa_dec(spc[3]) + 16*charhexa_dec(spc[2]) +
    16*16*charhexa_dec(spc[1]) + 16*16*16*charhexa_dec(spc[0]);
    pc += x;
    return dec_stringhexa(pc);
}
void program_counter(string spc) {
    // Lectura
    string operation;
    cin >> operation;
    if (operation == "MOVHI" or operation == "MOVI") {
        // Lectura
        int rd, n8;
        char x;
        cin >> x >> rd >> n8;
        // Procediment
        if (operation == "MOVI") {
            cout << "R" << rd << "=0x" << dec_stringhexa(n8);
        }
        else {
            string rvalor;
            cout << "Escriu el valor de R" << rd << " (en Hexa): 0x";
            cin >> rvalor;
            string num8 = dec_stringhexa(n8);
            cout << "R" << rd << "=0x" << num8[2] << num8[3];
            cout << rvalor[2] << rvalor[3];
        }
        cout << "; PC=0x" << actualitza_pc(spc, 2) << endl;
    }
    else if (operation[0] == 'B') {
        // Lectura
        int rd, n8;
        char x;
        cin >> x >> rd >> n8;
        string rvalor;
        cout << "Escriu el valor de R" << rd << " (en Hexa): 0x";
        cin >> rvalor;
        // Procediment
        if ((operation == "BNZ" and rvalor != "0000") or
        (operation == "BZ" and rvalor == "0000")) {
            cout << "PC=0x" << actualitza_pc(spc, 2 + 2*n8) << endl;
        }
        else cout << "PC=0x" << actualitza_pc(spc, 2) << endl;
    }
    else if (operation == "LD" or operation == "LDB") {
        // Lectura
        int rd, n6, ra;
        char x;
        cin >> x >> rd >> n6 >> x >> ra;
        string ravalor;
        cout << "Escriu el valor de R" << ra << " (en Hexa): 0x";
        cin >> ravalor;
        string memvalor, mpos1 = actualitza_pc(ravalor, n6);
        
        if (operation == "LD") {
            cout << "Escriu el valor de MEMb[0x" << mpos1 << "] (en Hexa): 0x";
            cin >> memvalor;
            // mvalor = parell, mvalor2 = imparell
            string mpos2 = actualitza_pc(mpos1, 1);
            if (charhexa_dec(mpos1[3])%2 != 0) mpos2 = actualitza_pc(mpos1, -1);
            string memvalor2;
            cout << "Escriu el valor de MEMb[0x" << mpos2 << "] (en Hexa): 0x";
            cin >> memvalor2;
            if (charhexa_dec(mpos1[3])%2 != 0) {
                string aux = memvalor;
                memvalor = memvalor2, memvalor2 = aux;
            }
            cout << 'R' << rd << "=0x" << memvalor2 << memvalor;
        }
        else {
            cout << "Escriu el valor de MEMb[0x" << mpos1 << "] (en Hexa): 0x";
            cin >> memvalor;
            cout << 'R' << rd << "=0x";
            if (memvalor[0] >= '8') cout << "FF" << memvalor;
            else cout << "00" << memvalor;   
        }
        cout << "; PC=0x" << actualitza_pc(spc, 2) << endl;
    }
    else if (operation == "ST" or operation == "STB") {
        // Lectura 
        int n6, ra, rb;
        char x;
        cin >> n6 >> x >> ra >> x >> rb;
        string ravalor, rbvalor;
        cout << "Escriu el valor de R" << ra << " (en Hexa): 0x";
        cin >> ravalor;
        cout << "Escriu el valor de R" << rb << " (en Hexa): 0x";
        cin >> rbvalor;
        string mempos = actualitza_pc(ravalor, n6);
        
        if (operation == "ST") {
            if (charhexa_dec(mempos[3])%2 != 0) mempos = actualitza_pc(mempos, -1);
            cout << "MEMb[0x" << mempos << "]=0x" << rbvalor[2] << rbvalor[3] << "; ";
            cout << "MEMb[0x" << actualitza_pc(mempos, 1) << "]=0x" << rbvalor[0] << rbvalor[1];
        }
        else cout << "MEMb[0x" << mempos << "]=0x" << rbvalor[2] << rbvalor[3];
        cout << "; PC=0x" << actualitza_pc(spc, 2) << endl;
    }
    else if (operation == "JALR") {
        // Lectura
        int rd, ra;
        char x;
        cin >> x >> rd >> x >> ra;
        string ravalor;
        cout << "Escriu el valor de R" << ra << " en (Hexa): 0x";
        cin >> ravalor;
        // Procediment
        cout << 'R' << rd << "=0x" << actualitza_pc(spc, 2) << "; ";
        cout << "PC=0x" << ravalor << endl;
    }
    else cout << "Operació invàlida." << endl;
    cout << endl;
}


// Updates
void updates() {
        cout << "------------------------------------------------------------------------" << endl;
    cout << "      " << "Versió 1.5 - 26/11/2020:" << endl;
        cout << "- Ca2 Implementat.\n" << endl;
    cout << "      " << "Versió 2.0 - 23/12/2020:" << endl;
        cout << "- Conversor d'Instrucció SISA a Paraula de Control del SISC Harvard unicicle (Temes 8-11).\n" << endl;
    cout << "      " << "Versió 3.0 - 31/12/2020:" << endl;
        cout << "- Conversor d'Instrucció SISC Von Neumann a Paraula de Control del SISC CONTROL UNIT (Temes 12-14).\n" << endl;
    cout << "      " << "Versió 4.0 - 23/01/2020:" << endl;
        cout << "- Canvis d'estat del computador SISC Von Neumann." << endl;
        cout << "------------------------------------------------------------------------" << endl;
}

// Manual
void man() {
    cout << "------------------------------------------------------------------------" << endl;
    cout << "Instruccions i pàgina del programa: ";
    cout << "https://github.com/JoanK11/SisaProgram" << endl;
    cout << endl;
    // 
    cout << setw(10) << right << " Opcions:" << endl;
    cout << setw(15) << right << "  --hexa, -h : ";
    cout << "Conversor de nombre hexadecimal a Llenguatge ensamblador SISA." << endl;
    cout << "               Ex: -h 025F, -h 7623, -h 4702, etc." << endl;
    cout << endl;
    // 
    cout << setw(15) << right << "--cword1, -c1 : ";
    cout << "Conversor d'Instrucció SISA a Paraula de Control del SISC Harvard unicicle (Temes 8-11)." << endl;
    cout << "               Ex: -c1 ADD R1 R2 R5, -c1 STB -4 R5 R0, etc." << endl;
    cout << endl;
    // 
    cout << setw(15) << right << "--cword2, -c2 : ";
    cout << "Conversor d'Instrucció SISC Von Neumann a Paraula de Control del SISC CONTROL UNIT (Temes 12-14)." << endl;
    cout << "               Ex: -c2 JALR R4 R5, -c2 ADDR LDB R1 1 R6, etc." << endl;
    cout << endl;
    // 
    cout << setw(15) << right << " -pc : ";
    cout << "Canvis d'estat del computador SISC Von Neumann." << endl;
    cout << "               Ex: -pc F0F8 STB -3 R3 R5, -pc CAFE MOVHI R3 -15, etc.";
    cout << endl;
    // 
    cout << setw(15) << right << "--updates, -u : ";
    cout << "Mostra totes les actualitzacions d'aquest programa." << endl;
    cout << endl;
    // 
    cout << setw(15) << right << "--help, -man : ";
    cout << "Per accedir al manual." << endl;
    cout << endl;
    // 
    cout << "No em responsabilitzo de qualsevol error que provoqui treballar amb aquesta eina de finalitat educativa." << endl;
    cout << "------------------------------------------------------------------------" << endl;
}

int main() {
    cout << "SisaProgram v.3 - Joan Caballero" << endl;
    cout << "Escriu '-man' per accedir al manual." << endl;
    string mode;
    while (cin >> mode) {
        if (mode == "--help" or mode == "-man" or mode == "-MAN")
            man();
        else if (mode == "--hexa" or mode == "-h" or mode == "-H")
            program_hexa();
        else if (mode == "--cword1" or mode == "-c1" or mode == "-C1")
            cword_v1();
        else if (mode == "--cword2" or mode == "-c2" or mode == "-C2")
            cword_v2();
        else if (mode == "-pc" or mode == "-PC") {
            string spc;
            cin >> spc;
            program_counter(spc);
        }
        else if (mode == "--updates" or mode == "-u" or mode == "-U")
            updates();
    }
}