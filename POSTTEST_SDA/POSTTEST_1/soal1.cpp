#include <iostream> 
using namespace std; 

int findMin(int jumlahData, int fibonacci[]) {
    int min = fibonacci[0]; 
    for (int i = 1; i < jumlahData; i++) {
        if (fibonacci[i] < min) {
            min = i;
        } 
    }
    return min; 
}

int main () {
    int jumlahData = 8; 
    int min;
    
    int fibonacci[jumlahData] = {1, 1, 2, 3, 5, 8, 13, 21}; 
    
    cout << "\n==== Program Mencari Nilai Min dari sebuah Array =====" << endl;
    cout << "Array: {"; 
    for (int i = 0; i < jumlahData; i++) {
        cout << fibonacci[i] << (i < jumlahData - 1 ? ", " : "");
    }
    cout << "}";

    min = findMin(jumlahData, fibonacci); 
    cout << "\nNilai Minimum"<< "   : " << fibonacci[min] << endl;
    cout << "Nilai Indeks" << "    : " << min << endl;
    cout << "======================================================" << endl;

    cout << " ";

    return 0; 
}
