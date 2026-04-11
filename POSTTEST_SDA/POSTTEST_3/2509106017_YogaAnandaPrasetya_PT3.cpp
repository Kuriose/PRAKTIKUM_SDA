#include <iostream> 
#include <string>
#include <tabulate/table.hpp>
using namespace std; 
using namespace tabulate;

// NOTE: Pastikan Library Tabulate sudah dipasang agar Compile Program dapat berjalan lancar
struct DataHewan {
    int hewanID; 
    string namaHewan; 
    int hargaHewan; 
};

const int MAXHEWAN = 256;
const int MAXQUEUE = 10;
const int MAXSTACK = 10;
const int panjangGaris = 70; 
DataHewan daftarHewan[MAXHEWAN];
int jumlahHewan = 5; 
int idUniqueHewan = jumlahHewan;

DataHewan antrianQueue[MAXQUEUE];
int queueFront = 0; 
int queueRear  = 0; 

DataHewan riwayatStack[MAXSTACK];
int stackTop = -1; 

// FEAT: Fungsi & Prosedur Bantuan
void addDummyData() {
    // CONTOH ENTRI HEWAN 
    daftarHewan[0].hewanID      = 1                 ;   daftarHewan[1].hewanID      = 2                 ;  
    daftarHewan[0].namaHewan    = "Kucing"          ;   daftarHewan[1].namaHewan    = "Landak"          ; 
    daftarHewan[0].hargaHewan   = 100               ;   daftarHewan[1].hargaHewan   = 150               ;
    
    daftarHewan[2].hewanID      = 3                  ;   daftarHewan[3].hewanID      = 4                   ;  
    daftarHewan[2].namaHewan    = "Marmut"           ;   daftarHewan[3].namaHewan    = "Anjing"            ; 
    daftarHewan[2].hargaHewan   = 1000               ;   daftarHewan[3].hargaHewan   = 200                 ;
    
    daftarHewan[4].hewanID      = 5                 ;
    daftarHewan[4].namaHewan    = "Hamster"         ; 
    daftarHewan[4].hargaHewan   = 350               ;
}

void gambarTabel(DataHewan *ptrTabel, int jumlahHewan) {
    Table tabelHewan; 
    tabelHewan.add_row({
        "ID", 
        "Nama Hewan", 
        "Harga Hewan"
    }); 
    
    for (int i = 0; i < jumlahHewan; i++) {
        tabelHewan.add_row({
            to_string((ptrTabel + i) -> hewanID), 
            (ptrTabel + i) -> namaHewan, 
            to_string((ptrTabel + i) -> hargaHewan)
        });
    }
    cout << tabelHewan << endl;
}

void gambarGaris(string karakter, int panjang) {
    for (int i = 0; i < panjang; i++) {
        cout << karakter;
    }
    cout << endl;
}

int validasiInput(int pilihan) {
    if (cin.fail()) {
        cin.clear();
        while (cin.peek() != '\n') {
            cin.ignore();
        }
        return pilihan = -1;
    } 
    else {
        cin.clear();
        while (cin.peek() != '\n') {
            cin.ignore();
        }
    }
    return pilihan;
}

// NOTE: Sort ID Hewan Menggunakan Selection Sort
void sortIDHewan (DataHewan *ptrArray, int jumlahHewan) {
    for (int i = 0; i < jumlahHewan - 1; i++) {
        int indeksMin = i; 

        for (int j = i + 1; j < jumlahHewan; j++) {
            if ((ptrArray + j) -> hewanID < (ptrArray + indeksMin) -> hewanID) {
                indeksMin = j; 
            }
        }

        if (indeksMin != i) {
            DataHewan tukar = *(ptrArray + i); 
            *(ptrArray + i) = *(ptrArray + indeksMin); 
            *(ptrArray + indeksMin) = tukar; 
        }
    }
}

// SEARCHING DAN SORTING
// NOTE: Search Nama Hewan menggunakan Linear Search
int searchNamaHewan(DataHewan *ptrArray, int jumlahHewan) {
    string cariNama; 
    string *ptrNama = &cariNama;
    
    cin.ignore();
    cout << "Masukkan Nama Hewan yang ingin dicari" << endl; // Misal nama yang di cari: Hamster 
    cout << "> "; getline(cin, cariNama); 
    gambarGaris("-", panjangGaris);

    for (int i = 0; i < jumlahHewan; i++) { // Perulangan Untuk Mengakses Semua Hewan yanga ada pada Array
        if (*ptrNama == (ptrArray + i) -> namaHewan) { // Membandingkan apakah nama hewan di array sama dengan nama yang dicari (Hamster)
            return i; // Jika ya, kembalikan Indeks dari array
        }
    } // Ulangi terus hingga semua hewan yang ada pada array diakses
    
    return -1; // Jika tidak ada yang cocok, kembalikan nilai -1 (Artinya tidak ditemukan)
}

// ILUSTRASI
// daftarHewan = {"Kucing", "Landak", "Marmut", "Anjing", "Hamster"}
// Yang dicari = "Hamster"

// ITERASI 1: "Kucing" == "Hamster"? TIDAK (Lanjut iterasi selanjutnya)
// ITERASI 2: "Landak" == "Hamster"? TIDAK (Lanjut iterasi selanjutnya)
// ITERASI 3: "Marmut" == "Hamster"? TIDAK (Lanjut iterasi selanjutnya)
// ITERASI 4: "Anjing" == "Hamster"? TIDAK (Lanjut iterasi selanjutnya)
// ITERASI 5: "Hamster" == "Hamster"? YA (Kembalikan Indeks Array)
// Hewan ditemukan pada Indeks ke-4 Array

// NOTE: Search ID Hewan Menggunakan Fibonnaci Search
int searchIDHewan(DataHewan *ptrArray, int jumlahHewan) {
    int pilihan;
    
    cout << "=> LANGKAH 1: Mengurutkan Data Hewan Berdasarkan ID Terlebih Dahulu" << endl;
    sortIDHewan(ptrArray, jumlahHewan); 
    gambarGaris("-", panjangGaris);

    cout << "Masukkan ID Hewan yang Ingin Anda Cari" << endl; 
    cout << "> "; cin >> pilihan; 
    pilihan = validasiInput(pilihan);
    gambarGaris("-", panjangGaris);

    int fib2 = 0; int *ptr2 = &fib2; 
    int fib1 = 1; int *ptr1 = &fib1;  
    int fib = *ptr1 + *ptr2; int *ptrFib = &fib; 

    while (*ptrFib < jumlahHewan) {
        *ptr2 = *ptr1; 
        *ptr1 = *ptrFib; 
        *ptrFib = *ptr1 + *ptr2;
    }

    int offset = -1; int *ptrOff = &offset; 

    while (*ptrFib > 1) {
        int i = *ptrOff + *ptr2; 
        
        if (i >= jumlahHewan) {
            i = jumlahHewan - 1;
        }

        if ((ptrArray + i) -> hewanID == pilihan) {
            return i; 
        } 
        else if ((ptrArray + i) -> hewanID < pilihan) {
            *ptrFib = *ptr1; 
            *ptr1 = *ptr2; 
            *ptr2 = *ptrFib - *ptr1; 
            *ptrOff = i; 
        }
        else {
            *ptrFib = *ptr2; 
            *ptr1 = *ptr1 - *ptr2; 
            *ptr2 = *ptrFib - *ptr1;
        }
    }

    if (*ptr1 == 1 && *ptrOff + 1 < jumlahHewan && (ptrArray + *ptrOff + 1) -> hewanID == pilihan) {
        return *ptrOff + 1; 
    }

    return -1;   
}

// NOTE: Sort Nama Hewan Menggunakan Bubble Sort 
void sortNamaHewan(DataHewan *ptrArray, int jumlahHewan) {
    for (int i = 0; i < jumlahHewan - 1; i++) {
        for (int j = 0; j < jumlahHewan - i - 1; j++) {
            if ((ptrArray + j) -> namaHewan > (ptrArray + j + 1) -> namaHewan) {
                DataHewan tukar = *(ptrArray + j);
                *(ptrArray + j) = *(ptrArray + j + 1);
                *(ptrArray + j + 1) = tukar;
            }
        }
    }    
}

// NOTE: Sort Harga Hewan Menggunakan Selection Sort
void sortHargaHewan(DataHewan *ptrArray, int jumlahHewan) {
    for (int i = 0; i < jumlahHewan - 1; i++) {
        int indeksMin = i; 

        for (int j = i + 1; j < jumlahHewan; j++) {
            if ((ptrArray + j) -> hargaHewan < (ptrArray + indeksMin) -> hargaHewan) {
                indeksMin = j; 
            }
        }

        if (indeksMin != i) {
            DataHewan tukar = *(ptrArray + i);
            *(ptrArray + i) = *(ptrArray + indeksMin); 
            *(ptrArray + indeksMin) = tukar;
        }
    }
}

void lihatHewan(DataHewan *ptrArray, int jumlahHewan) {
    cout << "=== LIHAT SEMUA HEWAN ================================================" << endl;
    gambarTabel(ptrArray, jumlahHewan);
    gambarGaris("-", panjangGaris);

    system("pause");
}

void tambahHewan(DataHewan *ptr, int &jumlahHewan) {
    string inputNama;
    int inputHarga;
    bool berhasilRegister;
    
    do {
        berhasilRegister = true;
        if (jumlahHewan >= MAXHEWAN) {
            cout << "=> Data Hewan Sudah Penuh" << endl; 
            gambarGaris("-", panjangGaris);
            system("pause");
            gambarGaris("-", panjangGaris);
            break;
        }
        
        cout << "=== TAMBAH HEWAN =====================================================" << endl;
        cout << "Masukkan Nama Hewan    : "; cin.ignore(); getline(cin, inputNama); 
        
        if (inputNama.empty()) {
            cout << "=> Nama Hewan Tidak Boleh Kosong" << endl;
            gambarGaris("-", panjangGaris);
            berhasilRegister = false;
            continue;
        }
        
        cout << "Masukkan Harga Hewan   : "; cin >> inputHarga;
        inputHarga = validasiInput(inputHarga);

        if (inputHarga <= 0) {
            cout << "=> Harga Hewan Harus Lebih Dari 0" << endl; 
            gambarGaris("-", panjangGaris);
            berhasilRegister = false;
            continue;
        } 

        if (berhasilRegister) {
            ptr[jumlahHewan].hewanID = idUniqueHewan + 1; 
            ptr[jumlahHewan].namaHewan = inputNama;
            ptr[jumlahHewan].hargaHewan = inputHarga; 
            jumlahHewan++; idUniqueHewan++;

            gambarGaris("-", panjangGaris);
            cout << "=> Berhasil Menambahkan Hewan" << endl; 
            gambarGaris("-", panjangGaris);
            
            system("pause");
            gambarGaris("-", panjangGaris);
        } 

    } while (!berhasilRegister);
}

void cariHewan(DataHewan daftarHewan[], int &jumlahHewan) {
    int pilihan;
    string kembali;
    DataHewan *ptrArray = daftarHewan; 

    do {
        cout << "=== CARI HEWAN =======================================================" << endl; 
        cout << "[1] Cari Berdasarkan Nama" << endl; 
        cout << "[2] Cari Berdasarkan ID Hewan" << endl;
        
        gambarGaris("-", panjangGaris);
        cout << "[0] Kembali" << endl; 
        gambarGaris("-", panjangGaris);
        
        cout << "Masukkan Pilihan Anda" << endl;
        cout << "> "; cin >> pilihan; 
        gambarGaris("-", panjangGaris);

        pilihan = validasiInput(pilihan); 

        if (pilihan == 0) {
            cout << "=> Kembali ke Menu Utama" << endl;
            gambarGaris("-", panjangGaris);
            break;
        }
        else if (pilihan == 1) {
            cout << "=> Mencari Berdasarkan Nama Hewan" << endl; 
            gambarGaris("-", panjangGaris);

            int indeksHasil = searchNamaHewan(daftarHewan, jumlahHewan); 
            if (indeksHasil < 0) {
                cout << "=> Hewan tidak Ditemukan" << endl;
                cout << "=> Saran: Awali Pencarian dengan Menggunakan Huruf Kapital" << endl;
                gambarGaris("-", panjangGaris);
                
                cout << "Tekan 'Enter' untuk Kembali" << endl; 
                cout << "> "; getline(cin, kembali); 
                gambarGaris("-", panjangGaris);
            } 
            else {
                cout << "=> Hewan Ditemukan" << endl;
                gambarGaris("-", panjangGaris);
                
                cout << "=== Hasil Pencarian ==================================================" << endl;
                cout << "ID Hewan       : " << ptrArray[indeksHasil].hewanID << endl;
                cout << "Nama Hewan     : " << ptrArray[indeksHasil].namaHewan << endl;
                cout << "Harga Hewan    : " << ptrArray[indeksHasil].hargaHewan << endl;
                gambarGaris("-", panjangGaris);

                cout << "Tekan 'Enter' untuk Kembali" << endl; 
                cout << "> "; getline(cin, kembali);
                gambarGaris("-", panjangGaris); 
            }
        }
        else if (pilihan == 2) {
            cout << "=> Mencari Berdasarkan ID Hewan" << endl; 
            gambarGaris("-", panjangGaris);

            int indeksHasil = searchIDHewan(daftarHewan, jumlahHewan); 
            if (indeksHasil < 0) {
                cout << "=> Hewan tidak Ditemukan" << endl;
                gambarGaris("-", panjangGaris);

                cout << "Tekan 'Enter' untuk Kembali" << endl; 
                cout << "> "; cin.ignore(); getline(cin, kembali); 
                gambarGaris("-", panjangGaris);
            } 
            else {
                cout << "=> Hewan Ditemukan" << endl;
                gambarGaris("-", panjangGaris);

                cout << "=== Hasil Pencarian ==================================================" << endl;
                cout << "ID Hewan       : " << ptrArray[indeksHasil].hewanID << endl;
                cout << "Nama Hewan     : " << ptrArray[indeksHasil].namaHewan << endl;
                cout << "Harga Hewan    : " << ptrArray[indeksHasil].hargaHewan << endl;
                gambarGaris("-", panjangGaris);
                
                cout << "Tekan 'Enter' untuk Kembali" << endl; 
                cout << "> "; cin.ignore(); getline(cin, kembali); 
                gambarGaris("-", panjangGaris);
            }
        }
        else {
            cout << "=> Pilihan Tidak Valid" << endl; 
            gambarGaris("-", panjangGaris);
        }
    } while (pilihan != 0);
    
}

void urutkanHewan(DataHewan daftarHewan[], int &jumlahHewan) {
    string kembali;
    int pilihan; 

    do {
        cout << "=== URUTKAN HEWAN ====================================================" << endl; 
        cout << "[1] Urutkan Berdasarkan Nama" << endl; 
        cout << "[2] Urutkan Berdasarkan Harga" << endl;
        cout << "[3] Urutkan Berdasarkan ID" << endl;

        gambarGaris("-", panjangGaris);
        cout << "[0] Kembali" << endl; 
        gambarGaris("-", panjangGaris);
        
        cout << "Masukkan Pilihan Anda" << endl; 
        cout << "> "; cin >> pilihan; 
        gambarGaris("-", panjangGaris);

        pilihan = validasiInput(pilihan);

        switch (pilihan) {
            case 0: 
            cout << "=> Kembali Ke Menu Utama" << endl; 
            gambarGaris("-", panjangGaris);
            break;

            case 1: 
            cout << "=> Mengurutkan Berdasarkan Nama" << endl; 
            gambarGaris("-", panjangGaris);

            cout << "=== Urutan Hewan Sebelum Di Sort =====================================" << endl; 
            gambarTabel(daftarHewan, jumlahHewan);
            sortNamaHewan(daftarHewan, jumlahHewan);
            cout << endl;

            cout << "=== Urutan Hewan Setelah Di Sort =====================================" << endl;
            gambarTabel(daftarHewan, jumlahHewan); 
            gambarGaris("-", panjangGaris);

            cout << "Tekan 'Enter' untuk Kembali" << endl; 
            cout << "> "; cin.ignore(); getline(cin, kembali);
            gambarGaris("-", panjangGaris);
            break; 
            
            case 2: 
            cout << "=> Mengurutkan Berdasarkan Harga" << endl; 
            gambarGaris("-", panjangGaris);

            cout << "=== Urutan Hewan Sebelum Di Sort =====================================" << endl; 
            gambarTabel(daftarHewan, jumlahHewan);
            sortHargaHewan(daftarHewan, jumlahHewan);
            cout << endl;

            cout << "=== Urutan Hewan Setelah Di Sort =====================================" << endl; 
            gambarTabel(daftarHewan, jumlahHewan);
            gambarGaris("-", panjangGaris);

            cout << "Tekan 'Enter' untuk Kembali" << endl; 
            cout << "> "; cin.ignore(); getline(cin, kembali);
            gambarGaris("-", panjangGaris);
            break;

            case 3: 
            cout << "=> Mengurutkan Berdasarkan ID" << endl; 
            gambarGaris("-", panjangGaris);
            
            cout << "=== Urutan Hewan Sebelum Di Sort =====================================" << endl;
            gambarTabel(daftarHewan, jumlahHewan);
            sortIDHewan(daftarHewan, jumlahHewan);
            cout << endl;

            cout << "=== Urutan Hewan Setelah Di Sort =====================================" << endl; 
            gambarTabel(daftarHewan, jumlahHewan);
            gambarGaris("-", panjangGaris);

            cout << "Tekan 'Enter' untuk Kembali" << endl; 
            cout << "> "; cin.ignore(); getline(cin, kembali);
            gambarGaris("-", panjangGaris);
            break;

            default: 
            cout << "=> Pilihan Tidak Valid" << endl; 
            gambarGaris("-", panjangGaris);
            break;
        }
    } while (pilihan != 0);
}

void enqueue() {
    string kembali;

    if (queueRear >= MAXQUEUE) {
        cout << "=> Antrian Penuh! Tidak Dapat Menambah Hewan Lagi" << endl;
        gambarGaris("-", panjangGaris);
        cout << "Tekan 'Enter' untuk Kembali" << endl;
        cout << "> "; cin.ignore(); getline(cin, kembali);
        return;
    }

    if (jumlahHewan == 0) {
        cout << "=> Tidak Ada Hewan Terdaftar di Petshop" << endl;
        gambarGaris("-", panjangGaris);
        cout << "Tekan 'Enter' untuk Kembali" << endl;
        cout << "> "; cin.ignore(); getline(cin, kembali);
        return;
    }

    cout << "=== Daftar Hewan yang Tersedia ===================================" << endl;
    gambarTabel(daftarHewan, jumlahHewan);
    gambarGaris("-", panjangGaris);

    int inputID;
    cout << "Masukkan ID Hewan yang Ingin Didaftarkan ke Antrian" << endl;
    cout << "> "; cin >> inputID;
    inputID = validasiInput(inputID);
    gambarGaris("-", panjangGaris);

    int indeks = -1;
    for (int i = 0; i < jumlahHewan; i++) {
        if (daftarHewan[i].hewanID == inputID) {
            indeks = i;
            break;
        }
    }

    if (indeks == -1) {
        cout << "=> Hewan dengan ID " << inputID << " Tidak Ditemukan di Daftar Petshop" << endl;
        gambarGaris("-", panjangGaris);
        cout << "Tekan 'Enter' untuk Kembali" << endl;
        cout << "> "; cin.ignore(); getline(cin, kembali);
        return;
    }

    antrianQueue[queueRear] = daftarHewan[indeks];
    queueRear++;

    cout << "=> Berhasil! Hewan '" << daftarHewan[indeks].namaHewan
         << "' (ID: " << inputID << ") Masuk ke Antrian (Posisi ke-" << queueRear - queueFront << ")" << endl;
    gambarGaris("-", panjangGaris);

    cout << "=== Antrian Saat Ini (Front -> Rear) =================================" << endl;
    if (queueFront == queueRear) {
        cout << "=> Antrian Kosong" << endl;
    } else {
        int ukuranAntrian = queueRear - queueFront;
        DataHewan *ptrQueue = antrianQueue + queueFront;
        for (int i = 0; i < ukuranAntrian; i++) {
            string label = (i == 0) ? " <- FRONT" : (i == ukuranAntrian - 1) ? " <- REAR" : "";
            cout << "[" << i + 1 << "] ID: " << (ptrQueue + i)->hewanID
                 << " | Nama: " << (ptrQueue + i)->namaHewan
                 << " | Harga: " << (ptrQueue + i)->hargaHewan
                 << label << endl;
        }
        cout << "=> Total Antrian: " << ukuranAntrian << " Hewan" << endl;
    }

    gambarGaris("-", panjangGaris);
    cout << "Tekan 'Enter' untuk Kembali" << endl;
    cout << "> "; cin.ignore(); getline(cin, kembali);
}

void push(DataHewan hewan) {
    if (stackTop >= MAXSTACK - 1) {
        cout << "=> Peringatan: Stack Riwayat Penuh, Tindakan Tidak Dapat Dicatat" << endl;
        return;
    }

    stackTop++;
    riwayatStack[stackTop] = hewan;

    cout << "=> Hewan '" << hewan.namaHewan << "' Selesai Diperiksa & Otomatis Dicatat ke Riwayat" << endl;
}

void dequeue() {
    string kembali;

    if (queueFront == queueRear) {
        cout << "=> Antrian Kosong! Tidak Ada Hewan yang Menunggu" << endl;
        gambarGaris("-", panjangGaris);
        cout << "Tekan 'Enter' untuk Kembali" << endl;
        cout << "> "; cin.ignore(); getline(cin, kembali);
        return;
    }

    DataHewan hewanDipanggil = antrianQueue[queueFront];
    queueFront++;

    cout << "=== Hewan Dipanggil untuk Diperiksa ==================================" << endl;
    cout << "ID Hewan       : " << hewanDipanggil.hewanID << endl;
    cout << "Nama Hewan     : " << hewanDipanggil.namaHewan << endl;
    cout << "Harga Hewan    : " << hewanDipanggil.hargaHewan << endl;
    gambarGaris("-", panjangGaris);

    push(hewanDipanggil);

    gambarGaris("-", panjangGaris);
    cout << "Tekan 'Enter' untuk Kembali" << endl;
    cout << "> "; cin.ignore(); getline(cin, kembali);
}

void tampilAntrian() {
    string kembali;
    cout << "=== ANTRIAN PEMERIKSAAN (Front -> Rear) ==============================" << endl;

    if (queueFront == queueRear) {
        cout << "=> Antrian Masih Kosong" << endl;
    } else {
        int ukuranAntrian = queueRear - queueFront;
        DataHewan *ptrQueue = antrianQueue + queueFront; // Pointer ke elemen front

        for (int i = 0; i < ukuranAntrian; i++) {
            string label = (i == 0) ? " <- FRONT" : (i == ukuranAntrian - 1) ? " <- REAR" : "";
            cout << "[" << i + 1 << "] ID: " << (ptrQueue + i)->hewanID
                 << " | Nama: " << (ptrQueue + i)->namaHewan
                 << " | Harga: " << (ptrQueue + i)->hargaHewan
                 << label << endl;
        }
        cout << "=> Total Antrian: " << ukuranAntrian << " Hewan" << endl;
    }

    gambarGaris("-", panjangGaris);
    cout << "Tekan 'Enter' untuk Kembali" << endl;
    cout << "> "; cin.ignore(); getline(cin, kembali);
}

void pop() {
    string kembali;

    if (stackTop == -1) {
        cout << "=> Stack Riwayat Kosong! Tidak Ada Tindakan yang Bisa Dibatalkan" << endl;
        gambarGaris("-", panjangGaris);
        cout << "Tekan 'Enter' untuk Kembali" << endl;
        cout << "> "; cin.ignore(); getline(cin, kembali);
        return;
    }

    DataHewan hewanDihapus = riwayatStack[stackTop];
    stackTop--;

    cout << "=== Tindakan Terakhir Berhasil Dibatalkan ============================" << endl;
    cout << "ID Hewan       : " << hewanDihapus.hewanID << endl;
    cout << "Nama Hewan     : " << hewanDihapus.namaHewan << endl;
    cout << "Harga Hewan    : " << hewanDihapus.hargaHewan << endl;
    gambarGaris("-", panjangGaris);
    cout << "=> Riwayat tindakan untuk '" << hewanDihapus.namaHewan << "' telah dihapus" << endl;
    gambarGaris("-", panjangGaris);
    cout << "Tekan 'Enter' untuk Kembali" << endl;
    cout << "> "; cin.ignore(); getline(cin, kembali);
}

void tampilRiwayat() {
    string kembali;
    cout << "=== RIWAYAT TINDAKAN (Bottom -> Top) =================================" << endl;

    if (stackTop == -1) {
        cout << "=> Riwayat Masih Kosong" << endl;
    } 
    else {
        DataHewan *ptrStack = riwayatStack; // Pointer ke elemen pertama stack
        for (int i = 0; i <= stackTop; i++) {
            string label = (i == stackTop) ? " <- TOP (Terbaru)" : "";
            cout << "[" << i + 1 << "] ID: " << (ptrStack + i)->hewanID
                 << " | Nama: " << (ptrStack + i)->namaHewan
                 << " | Harga: " << (ptrStack + i)->hargaHewan
                 << label << endl;
        }
        cout << "=> Total Riwayat: " << stackTop + 1 << " Tindakan" << endl;
    }

    gambarGaris("-", panjangGaris);
    cout << "Tekan 'Enter' untuk Kembali" << endl;
    cout << "> "; cin.ignore(); getline(cin, kembali);
}

void peek() {
    string kembali;
    cout << "=== PEEK (Intip Tanpa Mengubah Data) =================================" << endl;
    cout << "[ANTRIAN] Pasien Terdepan:" << endl;
    if (queueFront == queueRear) {
        cout << "  => Antrian Kosong" << endl;
    } else {
        DataHewan *ptrFront = antrianQueue + queueFront;
        cout << "  ID Hewan    : " << ptrFront->hewanID << endl;
        cout << "  Nama Hewan  : " << ptrFront->namaHewan << endl;
        cout << "  Harga Hewan : " << ptrFront->hargaHewan << endl;
    }

    gambarGaris("-", panjangGaris);

    cout << "[RIWAYAT] Tindakan Terakhir (Top of Stack):" << endl;
    if (stackTop == -1) {
        cout << "  => Riwayat Kosong" << endl;
    } else {
        DataHewan *ptrTop = riwayatStack + stackTop;
        cout << "  ID Hewan    : " << ptrTop->hewanID << endl;
        cout << "  Nama Hewan  : " << ptrTop->namaHewan << endl;
        cout << "  Harga Hewan : " << ptrTop->hargaHewan << endl;
    }

    gambarGaris("-", panjangGaris);
    cout << "Tekan 'Enter' untuk Kembali" << endl;
    cout << "> "; cin.ignore(); getline(cin, kembali);
}

void menuAntrianRiwayat() {
    int pilihan;

    do {
        cout << "\n=== ANTRIAN & RIWAYAT PEMERIKSAAN ===================================" << endl;
        cout << "[ANTRIAN -- QUEUE]" << endl;
        cout << "[1] Daftarkan Hewan ke Antrian" << endl;
        cout << "[2] Panggil Hewan Terdepan" << endl;
        gambarGaris("-", panjangGaris);

        cout << "[RIWAYAT -- STACK]" << endl;
        cout << "[3] Batalkan Tindakan Terakhir" << endl;
        gambarGaris("-", panjangGaris);

        cout << "[TAMPILKAN ANTRIAN DAN RIWAYAT]" << endl;
        cout << "[4] Lihat Antrian Terdepan dan Riwayat Terbaru" << endl;
        cout << "[5] Tampilkan Semua Antrian" << endl;
        cout << "[6] Tampilkan Semua Riwayat" << endl;

        gambarGaris("-", panjangGaris);
        cout << "[0] Kembali" << endl;
        gambarGaris("-", panjangGaris);

        cout << "Masukkan Pilihan Anda" << endl;
        cout << "> "; cin >> pilihan;
        gambarGaris("-", panjangGaris);

        pilihan = validasiInput(pilihan);

        switch (pilihan) {
            case 0:
            cout << "=> Kembali ke Menu Utama" << endl;
            gambarGaris("-", panjangGaris);
            break;

            case 1:
            cout << "=> Mendaftarkan Hewan ke Antrian" << endl;
            gambarGaris("-", panjangGaris);
            enqueue();
            break;

            case 2:
            cout << "=> Memanggil Hewan Terdepan dari Antrian" << endl;
            gambarGaris("-", panjangGaris);
            dequeue();
            break;

            case 3:
            cout << "=> Membatalkan Tindakan Terakhir" << endl;
            gambarGaris("-", panjangGaris);
            pop();
            break;

            case 4:
            cout << "=> Mengintip Data Tanpa Mengubah" << endl;
            gambarGaris("-", panjangGaris);
            peek();
            break;

            case 5:
            cout << "=> Menampilkan Semua Antrian" << endl;
            gambarGaris("-", panjangGaris);
            tampilAntrian();
            break;

            case 6:
            cout << "=> Menampilkan Semua Riwayat" << endl;
            gambarGaris("-", panjangGaris);
            tampilRiwayat();
            break;

            default:
            cout << "=> Pilihan Tidak Valid" << endl;
            gambarGaris("-", panjangGaris);
            break;
        }
    } while (pilihan != 0);
}

void menuUtama() {
    int pilihan;
    do {
        cout << "\n=== MANAJEMEN PETSHOP ================================================" << endl;
        cout << "[1] Tambah Hewan" << endl; 
        cout << "[2] Lihat Semua Hewan" << endl; 
        cout << "[3] Cari Hewan" << endl; 
        cout << "[4] Urutkan Hewan" << endl; 
        cout << "[5] Antrian & Riwayat Pemeriksaan" << endl;  // FITUR BARU
        
        gambarGaris("-", panjangGaris);
        cout << "[0] Keluar" << endl;
        gambarGaris("-", panjangGaris);
        
        cout << "Masukkan Pilihan Anda" << endl; 
        cout << "> "; cin >> pilihan;
        gambarGaris("-", panjangGaris);

        pilihan = validasiInput(pilihan);

        switch (pilihan) {
            case 0: 
            cout << "=> Keluar Dari Program" << endl;
            gambarGaris("-", panjangGaris);
            cout << endl;
            break; 

            case 1: 
            cout << "=> Mengarahkan ke Menu 'Tambah Hewan'" << endl;
            gambarGaris("-", panjangGaris); 
            tambahHewan(daftarHewan, jumlahHewan);
            break; 

            case 2: 
            cout << "=> Mengarahkan ke Menu 'Lihat Semua Hewan'" << endl; 
            gambarGaris("-", panjangGaris);
            lihatHewan(daftarHewan, jumlahHewan);
            break; 

            case 3: 
            cout << "=> Mengarahkan ke Menu 'Cari Hewan'" << endl; 
            gambarGaris("-", panjangGaris);
            cariHewan(daftarHewan, jumlahHewan); 
            break;

            case 4: 
            cout << "=> Mengarahkan ke Menu 'Urutkan Hewan'" << endl; 
            gambarGaris("-", panjangGaris);
            urutkanHewan(daftarHewan, jumlahHewan);
            break;

            case 5:
            cout << "=> Mengarahkan ke Menu 'Antrian & Riwayat Pemeriksaan'" << endl;
            gambarGaris("-", panjangGaris);
            menuAntrianRiwayat();
            break;

            default: 
            cout << "=> Pilihan Tidak Valid" << endl; 
            gambarGaris("-", panjangGaris);
            break;
        }
    
    } while (pilihan != 0);
}

int main () {
    addDummyData();
    menuUtama();
    return 0;
}