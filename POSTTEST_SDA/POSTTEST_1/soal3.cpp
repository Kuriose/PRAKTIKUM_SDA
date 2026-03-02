#include <iostream> 
using namespace std; 

int balikArray(int *prima, int jumlahData) {
    int *elemenAwal = prima; 
    int *elemenAkhir = prima + jumlahData - 1; 
    
    while (elemenAwal < elemenAkhir) {
        int tukar = *elemenAwal; 
        *elemenAwal = *elemenAkhir; 
        *elemenAkhir = tukar;
        
        ++elemenAwal; 
        --elemenAkhir; 
    }

    return 0; 
}

int main () {
    int jumlahData = 7;     
    int prima[jumlahData] = {2, 3, 5, 7, 11, 13, 17}; 
    int *pointArray = prima;

    cout << "\n==== Array Sebelum dibalik ==============================" << endl;
    // Mencetak Isi Array
    cout << "Prima = { ";
    while (pointArray < prima + jumlahData) {
        cout << *pointArray << " ";
        pointArray++;
    } 
    cout << "}" << endl;

    // Mencetak Alamat Tiap Elemen 
    pointArray = prima;
    cout << "\n---- Alamat Tiap Elemen ----" << endl; 
    while (pointArray < prima + jumlahData) {
        cout << "Nilai: " << *pointArray << ", Alamat: " << pointArray << endl;
        pointArray++;
    }

    cout << "=========================================================" << endl;

    pointArray = prima;
    balikArray(pointArray, jumlahData); 

    cout << "\n==== Array Sesudah dibalik ==============================" << endl;
    // Mencetak Isi Array
    pointArray = prima;
    cout << "Prima = { ";
    while (pointArray < prima + jumlahData) {
        cout << *pointArray << " ";
        pointArray++;
    } 
    cout << "}" << endl;

    // Mencetak Alamat Tiap Elemen
    pointArray = prima;
    cout << "\n---- Alamat Tiap Elemen ----" << endl; 
    while (pointArray < prima + jumlahData) {
        cout << "Nilai: " << *pointArray << ", Alamat: " << pointArray << endl;
        pointArray++;
    } 

    cout << "=========================================================" << endl;
    cout << " ";

    return 0;
}