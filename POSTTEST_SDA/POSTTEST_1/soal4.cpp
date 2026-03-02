#include <iostream>
using namespace std; 

int tukarAngka(int *pointSatu, int *pointDua) {
    int tukar = *pointSatu; 
    *pointSatu = *pointDua;
    *pointDua = tukar;
    
    return 0;
}

int main () {
    int angkaSatu, angkaDua; 
    
    cout << "\n==========================================================";
    cout << "\n--- Program Membalik Angka Menggunakan Pointer ---"; 
    cout << "\nMasukkan Angka Pertama" << " : "; cin >> angkaSatu;
    cout << "Masukkan Angka Kedua" << "   : "; cin >> angkaDua;
    cout << "==========================================================";

    cout << "\n--- Angka Sebelum Ditukar ---" << endl;
    cout << "Angka Pertama" << "    : " << angkaSatu << endl; 
    cout << "Angka Kedua" << "      : " << angkaDua << endl;
    cout << "==========================================================";
    
    tukarAngka(&angkaSatu, &angkaDua); 
    
    cout << "\n--- Angka Setelah Ditukar ---";
    cout << "\nAngka Pertama" << "    : " << angkaSatu; 
    cout << "\nAngka Kedua" << "      : " << angkaDua << endl;
    cout << "==========================================================" << endl;

    cout << " ";

    return 0;
}