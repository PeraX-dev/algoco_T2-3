#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

const int ALPHABET_SIZE = 26;

int cost_insert[ALPHABET_SIZE];
int cost_delete[ALPHABET_SIZE];
int cost_replace[ALPHABET_SIZE][ALPHABET_SIZE];
int cost_transpose[ALPHABET_SIZE][ALPHABET_SIZE];

void read_matrix(const string& filename, int matrix[ALPHABET_SIZE][ALPHABET_SIZE]) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        for (int j = 0; j < ALPHABET_SIZE; ++j) {
            file >> matrix[i][j];
        }
    }
    file.close();
}

void read_array(const string& filename, int array[ALPHABET_SIZE]) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        file >> array[i];
    }
    file.close();
}

// Funciones de costo
int costo_ins(char b) {
    return cost_insert[b - 'a'];
}

int costo_del(char a) {
    return cost_delete[a - 'a'];
}

int costo_sub(char a, char b) {
//	cout<<"a y b: "<<a<<' '<<b<<endl;
    return cost_replace[a - 'a'][b - 'a'];
}

int costo_trans(char a, char b) {
    return cost_transpose[a - 'a'][b - 'a'];
}

// Función recursiva de fuerza bruta corregida
//int brute_force(const std::string& S1, const std::string& S2, int i, int j) {
//    if (i == S1.size()) return (S2.size() - j) * costo_ins(' ');
//    if (j == S2.size()) return (S1.size() - i) * costo_del(' ');
//
//    int insert_cost = costo_ins(S2[j]) + brute_force(S1, S2, i, j + 1);
//    int delete_cost = costo_del(S1[i]) + brute_force(S1, S2, i + 1, j);
//    int replace_cost = costo_sub(S1[i], S2[j]) + brute_force(S1, S2, i + 1, j + 1);
//
//    int transpose_cost = INT_MAX;
//    if (i + 1 < S1.size() && j + 1 < S2.size() && S1[i] == S2[j + 1] && S1[i + 1] == S2[j]) {
//        transpose_cost = costo_trans(S1[i], S1[i + 1]) + brute_force(S1, S2, i + 2, j + 2);
//    }
//
//    return std::min({insert_cost, delete_cost, replace_cost, transpose_cost});
//}

int calcular_reem(string &string1, string &string2, int pos){
	int costo = costo_sub(string1[pos], string2[pos]);
	if(string1[pos] != string2[pos]) string1[pos] = string2[pos];
	return costo;
}

int posible_trans(string &string1, string &string2, int pos){
	int costo;
	
	if(string1[pos+1] != ' '){
		costo = costo_trans(string1[pos], string1[pos+1]);
	}
	
	if(string2[pos] != string1[pos] and string1[pos+1] == string2[pos] and string1[pos+1] != string2[pos+1]){
		char aux;
		
		aux = string1[pos];
		string1[pos] = string1[pos+1];
		string1[pos+1] = aux;
		return costo;
	}
	return 0;
}

int ins_char(string &string1, string &string2, int pos){
	int costo = costo_ins(string2[pos]);
	string1[pos] = string2[pos];
	return costo;
}

int del_char(string &string1, int pos){
	int costo = costo_del(string1[pos]);
	string1[pos] = ' ';
	return costo;
}

int main() {
    read_array("cost_insert.txt", cost_insert);
    read_array("cost_delete.txt", cost_delete);
    read_matrix("cost_replace.txt", cost_replace);
    read_matrix("cost_transpose.txt", cost_transpose);
    
//    cout<<"Insert:"<<endl;
//    for(int i = 0; i < ALPHABET_SIZE; i++){
//    	cout<<cost_insert[i]<<' ';
//    }
//    cout<<endl;
//    
//    cout<<"Delete:"<<endl;
//    for(int i = 0; i < ALPHABET_SIZE; i++){
//    	cout<<cost_delete[i]<<' ';
//    }
//	cout<<endl;
//	
//	cout<<"Sust:"<<endl;
//	for (int i = 0; i < ALPHABET_SIZE; ++i) {
//        for (int j = 0; j < ALPHABET_SIZE; ++j) {
//            cout<<cost_replace[i][j]<<' ';
//        }
//        cout<<endl;
//    }
//    
//    cout<<"Trans:"<<endl;
//    for (int i = 0; i < ALPHABET_SIZE; ++i) {
//        for (int j = 0; j < ALPHABET_SIZE; ++j) {
//            cout<< cost_transpose[i][j]<<' ';
//        }
//        cout<<endl;
//    }
//    
//    char user_char;
//    char ex_char = 'a';
//    
//    cin>>user_char;
//    
//    cout<<"Insert:"<<costo_ins(user_char)<<endl;
//	cout<<"Delete:"<<costo_del(user_char)<<endl;
//	cout<<"Sust:"<<costo_sub(user_char,ex_char)<<endl;
//	cout<<"Trans:"<<costo_trans(user_char,ex_char)<<endl;

    string S1 = "apolskdapkdasaskfgoasajgosaaas";
    string S2 = "paloksadkpdaasksgfaoasgjsoaasa";
    
    cout<<S1<<endl;
    cout<<S2<<endl;
    
    int costo_reem = 0;
    int costo_transp = 0;
    int costo_borrar = 0;
    int costo_insert = 0;
    
    int full_insert = 0;
    int full_reem = 0;
    int full_del = 0;
    int costo_mixto = 0;
    
	string S1_copia = S1;
	string S1_copia2 = S1;
	string S1_copia3 = S1;
	    
	int largo1 = S1.length();
	int largo2 = S2.length();
	
	auto start = chrono::high_resolution_clock::now();
	
	for(int i = 0; i < min(S1.length(), S2.length()); i++){
    	full_reem = calcular_reem(S1_copia, S2, i) + full_reem;
    }
    
    if(S1_copia.length() != S2.length()) full_reem = 99999;
    
    cout<<S1_copia<<" Full reem: "<<full_reem<<endl;
    
    if(S2.length() > S1.length()){
    	for(int i = 0; i < S2.length(); i++){
    		full_del = full_del + del_char(S1_copia2, i);
    	}
    
    	for(int i = 0; i < S2.length(); i++){
    		full_del = full_del + ins_char(S1_copia2, S2, i);
    	}
    } else {
		for(int i = 0; i < S1.length(); i++){
    		full_del = full_del + del_char(S1_copia2, i);
    	}
    
    	for(int i = 0; i < S1.length(); i++){
    		full_del = full_del + ins_char(S1_copia2, S2, i);
    	}
	}
	
	if(full_del < 0) full_del = 99999;
    
    cout<<S1_copia2<<" Full del: "<<full_del<<endl;
	
//	cout<<"Largo "<<largo1<<' '<<largo2<<endl;
        
    if(S1.length() > S2.length()){
    	for(int i = S2.length(); i < S1.length(); i++){
    			costo_borrar = costo_borrar + del_char(S1, i);
    	}
    }
    cout<<S1<<" Borrado: "<<costo_borrar<<endl;
	
	for(int i = 0; i < max(S1.length(), S2.length()) - 1; i++){
    	costo_transp = posible_trans(S1, S2, i) + costo_transp;
    }
    
    cout<<S1<<" Transpuesto: "<<costo_transp<<endl;    
	
	if(S2.length() > S1.length()){
    	for(int i = S1.length(); i < S2.length(); i++){
    		costo_insert = costo_insert + ins_char(S1, S2, i);
    		cout<<S1[i]<<' '<<S1.length()<<' ' <<i<< endl;
    	}
    }
    cout<<S1<<" Insertado: "<<costo_insert<<endl;
        
    for(int i = 0; i < min(S1.length(), S2.length()); i++){
    	costo_reem = calcular_reem(S1, S2, i) + costo_reem;
    }
    
    cout<<S1<<" Reemplazado: "<<costo_reem<<endl;
    
    costo_mixto = costo_reem + costo_borrar+ costo_transp + costo_insert;
    
    cout<<"Costo Mixto: "<<costo_mixto<<endl;
    
    int min1 = min(full_del, full_reem);
    int min2 = costo_mixto;
    
    int minimo = min(min1, min2);
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout<<"Tiempo Total: "<<elapsed.count()<<" seconds"<<endl;
	cout<<"Costo Minimo: "<<minimo<<endl;

//    int min_cost = brute_force(S1, S2, 0, 0);
//    cout << "El costo minimo es: " << min_cost << endl;

    return 0;
}

