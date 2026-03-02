#include <iostream> 
using namespace std; 

struct Mahasiswa {
    string nama; 
    string nim; 
    float ipk; 
};

int main() {
    int jumlahMahasiswa;
    float nilaiTertinggi = 0;
    int indeksTertinggi = 0;

    cout << "\n==== Program Array Data Mahasiswa ======================="; 
    cout << "\nMasukkan Jumlah Mahasiswa : "; cin >> jumlahMahasiswa; 

    cout << "---------------------------------------------------------" << endl;
    cout << "                Masukkan Data Mahasiswa"                   << endl;
    cout << "---------------------------------------------------------" << endl;

    Mahasiswa mhs[jumlahMahasiswa]; 
    for(int i = 0; i < jumlahMahasiswa; i++) {
        cout << "==== Mahasiswa ke-" << i+1 << " =====================================" << endl; 
        
        cout << "Nama" << " : "; cin >> mhs[i].nama; 
        cout << "NIM" << "  : "; cin >> mhs[i].nim; 
        cout << "IPK" << "  : "; cin >> mhs[i].ipk; 
        
        if(mhs[i].ipk >= nilaiTertinggi) {
            nilaiTertinggi = mhs[i].ipk;
            indeksTertinggi = i;
        }

        if (i < jumlahMahasiswa - 1) {
            cout << "---------------------------------------------------------" << endl;
        }

    }

    cout << "=========================================================" << endl;
    cout << "                      Data Mahasiswa"                      << endl;
    cout << "=========================================================" << endl;
    for(int i = 0; i < jumlahMahasiswa; i++) {
        cout << "Nama" << " : " << mhs[i].nama << endl; 
        cout << "NIM" << "  : " << mhs[i].nim << endl; 
        cout << "IPK" << "  : " << mhs[i].ipk << endl;
        
        if (i < jumlahMahasiswa - 1) {
            cout << "---------------------------------------------------------" << endl;
        }
    }

    cout << "=========================================================" << endl;
    cout << "             Mahasiswa Dengan Nilai Tertinggi            " << endl;
    cout << "=========================================================" << endl;
    cout << "Nama" << " : " << mhs[indeksTertinggi].nama << endl; 
    cout << "NIM" << "  : " << mhs[indeksTertinggi].nim << endl; 
    cout << "---------------------------------------------------------" << endl;
    cout << "                       IPK : " << mhs[indeksTertinggi].ipk   << endl;
    cout << "---------------------------------------------------------" << endl;

    cout << " ";

    return 0; 
}