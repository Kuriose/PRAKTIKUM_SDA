#include <iostream> 
#include <string>
#include <cctype>
#include <tabulate/table.hpp>
 
using namespace std; 
using namespace tabulate;
 
// NOTE: Pastikan Library Tabulate sudah dipasang agar Compile Program dapat berjalan lancar
struct DataHewan {
    int hewanID; 
    string namaHewan; 
    int hargaHewan;
    DataHewan* next; // Pointer ke node berikutnya (untuk Linked List)
};
 
struct NodeQueue {
    DataHewan data;
    NodeQueue* next;
};
 
struct NodeStack {
    DataHewan data;
    NodeStack* next;
};
 
const int MAXHEWAN    = 256;
const int panjangGaris = 70; 
DataHewan daftarHewan[MAXHEWAN];
int jumlahHewan   = 5; 
int idUniqueHewan = jumlahHewan;
 
// Queue: implementasi murni Single Linked List
NodeQueue *queueFront = nullptr;
NodeQueue *queueRear  = nullptr;
int queueSize         = 0;
 
// Stack: implementasi murni Single Linked List
NodeStack* stackTop = nullptr;
int stackSize       = 0;
 
void enqueue();
void dequeue();
void push(DataHewan hewan);
void pop();
void peek();
void tampilAntrian();
void tampilRiwayat();
void cariHewan(DataHewan daftarHewan[], int &jumlahHewan);
void urutkanHewan(DataHewan daftarHewan[], int &jumlahHewan);
 
string toLowerCase(string s) {
    for (int i = 0; i < (int)s.length(); i++) {
        s[i] = tolower(s[i]);
    }
    return s;
}
 
void addDummyData() {
    daftarHewan[0] = {1, "kucing",  100,  nullptr};
    daftarHewan[1] = {2, "landak",  150,  nullptr};
    daftarHewan[2] = {3, "marmut",  1000, nullptr};
    daftarHewan[3] = {4, "anjing",  200,  nullptr};
    daftarHewan[4] = {5, "hamster", 350,  nullptr};
}
 
void gambarTabel(DataHewan *ptrTabel, int jumlahHewan) {
    Table tabelHewan; 
    tabelHewan.add_row({"ID", "Nama Hewan", "Harga Hewan"}); 
    
    for (int i = 0; i < jumlahHewan; i++) {
        tabelHewan.add_row({
            to_string((ptrTabel + i)->hewanID), 
            (ptrTabel + i)->namaHewan, 
            to_string((ptrTabel + i)->hargaHewan)
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
        while (cin.peek() != '\n') cin.ignore();
        return -1;
    } else {
        cin.clear();
        while (cin.peek() != '\n') cin.ignore();
    }
    return pilihan;
}
 
void sortIDHewan(DataHewan *ptrArray, int jumlahHewan) {
    for (int i = 0; i < jumlahHewan - 1; i++) {
        int indeksMin = i; 
        for (int j = i + 1; j < jumlahHewan; j++) {
            if ((ptrArray + j)->hewanID < (ptrArray + indeksMin)->hewanID)
                indeksMin = j; 
        }
        if (indeksMin != i) {
            // Swap menggunakan dereferensi pointer (bukan menukar pointer node)
            DataHewan tukar         = *(ptrArray + i); 
            *(ptrArray + i)         = *(ptrArray + indeksMin); 
            *(ptrArray + indeksMin) = tukar; 
        }
    }
}
 
// NOTE: Search Nama Hewan menggunakan Linear Search
int searchNamaHewan(DataHewan *ptrArray, int jumlahHewan) {
    string cariNama; 
    string *ptrNama = &cariNama;
    
    cin.ignore();
    cout << "Masukkan Nama Hewan yang ingin dicari" << endl;
    cout << "> "; getline(cin, cariNama); 
    gambarGaris("-", panjangGaris);
 
    *ptrNama = toLowerCase(cariNama);
 
    for (int i = 0; i < jumlahHewan; i++) {
        if (*ptrNama == (ptrArray + i)->namaHewan)
            return i;
    }
    return -1;
}
 
// NOTE: Search ID Hewan Menggunakan Fibonacci Search
int searchIDHewan(DataHewan *ptrArray, int jumlahHewan) {
    int pilihan;
    cout << "Masukkan ID Hewan yang Ingin Anda Cari" << endl; 
    cout << "> "; cin >> pilihan; 
    pilihan = validasiInput(pilihan);
    gambarGaris("-", panjangGaris);
 
    int fib2 = 0; int *ptr2 = &fib2; 
    int fib1 = 1; int *ptr1 = &fib1;  
    int fib  = *ptr1 + *ptr2; int *ptrFib = &fib; 
 
    while (*ptrFib < jumlahHewan) {
        *ptr2   = *ptr1; 
        *ptr1   = *ptrFib; 
        *ptrFib = *ptr1 + *ptr2;
    }
 
    int offset = -1; int *ptrOff = &offset; 
 
    while (*ptrFib > 1) {
        int i = *ptrOff + *ptr2; 
        if (i >= jumlahHewan) i = jumlahHewan - 1;
 
        if ((ptrArray + i)->hewanID == pilihan)      return i; 
        else if ((ptrArray + i)->hewanID < pilihan) {
            *ptrFib = *ptr1; 
            *ptr1   = *ptr2; 
            *ptr2   = *ptrFib - *ptr1; 
            *ptrOff = i; 
        } else {
            *ptrFib = *ptr2; 
            *ptr1   = *ptr1 - *ptr2; 
            *ptr2   = *ptrFib - *ptr1;
        }
    }
 
    if (*ptr1 == 1 && *ptrOff + 1 < jumlahHewan && (ptrArray + *ptrOff + 1)->hewanID == pilihan)
        return *ptrOff + 1; 
 
    return -1;   
}
 
// NOTE: Sort Nama Hewan Menggunakan Bubble Sort
void sortNamaHewan(DataHewan *ptrArray, int jumlahHewan) {
    for (int i = 0; i < jumlahHewan - 1; i++) {
        for (int j = 0; j < jumlahHewan - i - 1; j++) {
            if ((ptrArray + j)->namaHewan > (ptrArray + j + 1)->namaHewan) {
                DataHewan tukar     = *(ptrArray + j);
                *(ptrArray + j)     = *(ptrArray + j + 1);
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
            if ((ptrArray + j)->hargaHewan < (ptrArray + indeksMin)->hargaHewan)
                indeksMin = j; 
        }
        if (indeksMin != i) {
            DataHewan tukar         = *(ptrArray + i);
            *(ptrArray + i)         = *(ptrArray + indeksMin); 
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
    int    inputHarga;
    bool   berhasilRegister;
    
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
 
        if (berhasilRegister && jumlahHewan <= MAXHEWAN) {
            ptr[jumlahHewan].hewanID    = idUniqueHewan + 1; 
            ptr[jumlahHewan].namaHewan  = inputNama;
            ptr[jumlahHewan].hargaHewan = inputHarga;
            ptr[jumlahHewan].next       = nullptr; 
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
        } else if (pilihan == 1) {
            cout << "=> Mencari Berdasarkan Nama Hewan" << endl; 
            gambarGaris("-", panjangGaris);
 
            int indeksHasil = searchNamaHewan(daftarHewan, jumlahHewan); 
            if (indeksHasil < 0) {
                cout << "=> Hewan tidak Ditemukan" << endl;
                gambarGaris("-", panjangGaris);
                system("pause"); 
                gambarGaris("-", panjangGaris);
            } else {
                cout << "=> Hewan Ditemukan" << endl;
                gambarGaris("-", panjangGaris);
                cout << "=== Hasil Pencarian ==================================================" << endl;
                cout << "ID Hewan       : " << ptrArray[indeksHasil].hewanID    << endl;
                cout << "Nama Hewan     : " << ptrArray[indeksHasil].namaHewan  << endl;
                cout << "Harga Hewan    : " << ptrArray[indeksHasil].hargaHewan << endl;
                gambarGaris("-", panjangGaris);
                system("pause");
                gambarGaris("-", panjangGaris); 
            }
        } else if (pilihan == 2) {
            cout << "=> Mencari Berdasarkan ID Hewan" << endl; 
            gambarGaris("-", panjangGaris);
            cout << "=> LANGKAH 1: Mengurutkan Data Hewan Berdasarkan ID Terlebih Dahulu" << endl;
            sortIDHewan(ptrArray, jumlahHewan); 
            gambarGaris("-", panjangGaris);
 
            int indeksHasil = searchIDHewan(daftarHewan, jumlahHewan); 
            if (indeksHasil < 0) {
                cout << "=> Hewan tidak Ditemukan" << endl;
                gambarGaris("-", panjangGaris);
                system("pause"); 
                gambarGaris("-", panjangGaris);
            } else {
                cout << "=> Hewan Ditemukan" << endl;
                gambarGaris("-", panjangGaris);
                cout << "=== Hasil Pencarian ==================================================" << endl;
                cout << "ID Hewan       : " << ptrArray[indeksHasil].hewanID    << endl;
                cout << "Nama Hewan     : " << ptrArray[indeksHasil].namaHewan  << endl;
                cout << "Harga Hewan    : " << ptrArray[indeksHasil].hargaHewan << endl;
                gambarGaris("-", panjangGaris);
                system("pause"); 
                gambarGaris("-", panjangGaris);
            }
        } else {
            cout << "=> Pilihan Tidak Valid" << endl; 
            gambarGaris("-", panjangGaris);
        }
    } while (pilihan != 0);
}
 
void urutkanHewan(DataHewan daftarHewan[], int &jumlahHewan) {
    int pilihan; 
 
    do {
        cout << "=== URUTKAN HEWAN ====================================================" << endl; 
        cout << "[1] Urutkan Berdasarkan Nama"  << endl; 
        cout << "[2] Urutkan Berdasarkan Harga" << endl;
        cout << "[3] Urutkan Berdasarkan ID"    << endl;
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
                system("pause");
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
                system("pause");
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
                system("pause");
                gambarGaris("-", panjangGaris);
                break;
            default: 
                cout << "=> Pilihan Tidak Valid" << endl; 
                gambarGaris("-", panjangGaris);
                break;
        }
    } while (pilihan != 0);
}
 
void cetakNodeQueue(NodeQueue* node) {
    if (node == nullptr) {
        cout << "=> Antrian Masih Kosong" << endl;
        return;
    }
 
    NodeQueue* current = node;
    int i = 1;
    int total = queueSize;
 
    while (current != nullptr) {
        string label = (i == 1)     ? " <- FRONT"
                     : (i == total) ? " <- REAR"
                     : "";
        cout << "[" << i << "] ID: "    << current->data.hewanID
             << " | Nama: "             << current->data.namaHewan
             << " | Harga: "            << current->data.hargaHewan
             << label << endl;
        current = current->next;
        i++;
    }
    cout << "=> Total Antrian: " << total << " Hewan" << endl;
}
 
// ENQUEUE: Tambah node baru di belakang (rear) linked list
void enqueue() {
    if (jumlahHewan == 0) {
        cout << "=> Tidak Ada Hewan Terdaftar di Petshop" << endl;
        gambarGaris("-", panjangGaris);
        system("pause");
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
 
    // CEK INDEKS ADA ATAU TIDAK
    int indeks = -1;
    for (int i = 0; i < jumlahHewan; i++) {
        if (daftarHewan[i].hewanID == inputID) {
            indeks = i;
            break;
        }
    }
    
    // DIJALANKAN JIKA ID TIDAK VALID
    if (indeks == -1) {
        cout << "=> Hewan dengan ID " << inputID << " Tidak Ditemukan di Daftar Petshop" << endl;
        gambarGaris("-", panjangGaris);
        system("pause");
        return;
    }
 
    // Buat node baru -- ADD LAST
    NodeQueue *nodeBaru = new NodeQueue;
    nodeBaru -> data = daftarHewan[indeks]; // Data pada Node Baru = Data Hewan Yang dipilih lewat Indeks
    nodeBaru -> next = nullptr; // Pointer dijadikan NULL karena Node ditambhkan di Akhir Linked List
 
    // Sisipkan di belakang (rear)
    if (queueRear == nullptr) {
        // Queue kosong: front dan rear menunjuk node yang sama
        queueFront = nodeBaru;
        queueRear  = nodeBaru;
    } else {
        // Sambungkan node lama rear ke node baru, geser rear
        queueRear -> next = nodeBaru; // Sambung Node Lama dengan Node Baru
        queueRear = nodeBaru; // Geser Rear ke nodeBaru
    }
    queueSize++; // Tambah Size queue
 
    cout << "=> Berhasil! Hewan '" << daftarHewan[indeks].namaHewan
         << "' (ID: " << inputID << ") Masuk ke Antrian (Posisi ke-" << queueSize << ")" << endl;
    gambarGaris("-", panjangGaris);
 
    cout << "=== Antrian Saat Ini (Front -> Rear) =================================" << endl;
    cetakNodeQueue(queueFront);
 
    gambarGaris("-", panjangGaris);
    system("pause");
}
 
// DEQUEUE: Hapus node terdepan (front) dari linked list
void dequeue() {
    // Cek Underflow 
    if (queueFront == nullptr) {
        cout << "=> Antrian Kosong! Tidak Ada Hewan yang Menunggu" << endl;
        gambarGaris("-", panjangGaris);
        system("pause");
        return;
    }
 
    // Simpan data front lalu lepas node-nya
    NodeQueue *nodeHapus  = queueFront;
    DataHewan hewanDipanggil = nodeHapus -> data;
 
    queueFront = queueFront->next;   // Geser front ke node berikutnya
    if (queueFront == nullptr)
        queueRear = nullptr;         // Queue sudah kosong, rear juga null
 
    delete nodeHapus;
    queueSize--;
 
    cout << "=== Hewan Dipanggil untuk Diperiksa ==================================" << endl;
    cout << "ID Hewan       : " << hewanDipanggil.hewanID    << endl;
    cout << "Nama Hewan     : " << hewanDipanggil.namaHewan  << endl;
    cout << "Harga Hewan    : " << hewanDipanggil.hargaHewan << endl;
    gambarGaris("-", panjangGaris);
 
    push(hewanDipanggil); // Otomatis catat ke riwayat (stack)
 
    gambarGaris("-", panjangGaris);
    system("pause");
}
 
// TAMPIL ANTRIAN: Traversal linked list dari front ke rear
void tampilAntrian() {
    cout << "=== ANTRIAN PEMERIKSAAN (Front -> Rear) ==============================" << endl;
    cetakNodeQueue(queueFront);
    gambarGaris("-", panjangGaris);
    system("pause");
}
 
// PUSH: Tambah node baru di atas top (head dari linked list)
void push(DataHewan hewan) {
    // Buat node baru
    NodeStack* nodeBaru = new NodeStack;
    nodeBaru->data      = hewan;
    nodeBaru->next      = stackTop; // Node baru menunjuk ke top lama
 
    stackTop = nodeBaru;            // Top sekarang adalah node baru
    stackSize++;
 
    cout << "=> Hewan '" << hewan.namaHewan << "' Selesai Diperiksa & Otomatis Dicatat ke Riwayat" << endl;
}
 
// POP: Hapus node paling atas (top) dari linked list
void pop() {
    // Underflow check
    if (stackTop == nullptr) {
        cout << "=> Stack Riwayat Kosong! Tidak Ada Tindakan yang Bisa Dibatalkan" << endl;
        gambarGaris("-", panjangGaris);
        system("pause");
        return;
    }
 
    NodeStack* nodeHapus   = stackTop;
    DataHewan  hewanDihapus = nodeHapus->data;
 
    stackTop = stackTop->next;      // Geser top ke node di bawahnya
    delete nodeHapus;
    stackSize--;
 
    cout << "=== Tindakan Terakhir Berhasil Dibatalkan ============================" << endl;
    cout << "ID Hewan       : " << hewanDihapus.hewanID    << endl;
    cout << "Nama Hewan     : " << hewanDihapus.namaHewan  << endl;
    cout << "Harga Hewan    : " << hewanDihapus.hargaHewan << endl;
    gambarGaris("-", panjangGaris);
    cout << "=> Riwayat tindakan untuk '" << hewanDihapus.namaHewan << "' telah dihapus" << endl;
    gambarGaris("-", panjangGaris);
    system("pause");
}
 
void tampilRiwayat() {
    cout << "=== RIWAYAT TINDAKAN (Bottom -> Top) =================================" << endl;
 
    if (stackTop == nullptr) {
        cout << "=> Riwayat Masih Kosong" << endl;
    } else {
        // Kumpulkan semua node ke array sementara agar bisa dicetak bottom->top
        NodeStack* temp[1024];
        int count = 0;
        NodeStack* current = stackTop;
        while (current != nullptr) {
            temp[count++] = current;
            current = current->next;
        }
 
        // Cetak dari indeks terbesar (bottom) ke 0 (top)
        for (int i = count - 1; i >= 0; i--) {
            string label = (i == 0) ? " <- TOP (Terbaru)" : "";
            cout << "[" << (count - i) << "] ID: "  << temp[i]->data.hewanID
                 << " | Nama: "                      << temp[i]->data.namaHewan
                 << " | Harga: "                     << temp[i]->data.hargaHewan
                 << label << endl;
        }
        cout << "=> Total Riwayat: " << stackSize << " Tindakan" << endl;
    }
 
    gambarGaris("-", panjangGaris);
    system("pause");
}
 
// PEEK: Intip front queue dan top stack tanpa mengubah struktur
void peek() {
    cout << "=== LIHAT ANTRIAN TERDEPAN DAN RIWAYAT TERBARU =================================" << endl;
 
    cout << "[ANTRIAN] Pasien Terdepan:" << endl;
    if (queueFront == nullptr) {
        cout << "  => Antrian Kosong" << endl;
    } else {
        // Akses data front langsung melalui pointer (parameter struct*)
        DataHewan* ptrFront = &(queueFront->data);
        cout << "  ID Hewan    : " << ptrFront->hewanID    << endl;
        cout << "  Nama Hewan  : " << ptrFront->namaHewan  << endl;
        cout << "  Harga Hewan : " << ptrFront->hargaHewan << endl;
    }
 
    gambarGaris("-", panjangGaris);
 
    cout << "[RIWAYAT] Tindakan Terakhir (Top of Stack):" << endl;
    if (stackTop == nullptr) {
        cout << "  => Riwayat Kosong" << endl;
    } else {
        // Akses data top langsung melalui pointer (parameter struct*)
        DataHewan* ptrTop = &(stackTop->data);
        cout << "  ID Hewan    : " << ptrTop->hewanID    << endl;
        cout << "  Nama Hewan  : " << ptrTop->namaHewan  << endl;
        cout << "  Harga Hewan : " << ptrTop->hargaHewan << endl;
    }
 
    gambarGaris("-", panjangGaris);
    system("pause");
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
        cout << "[1] Tambah Hewan"                          << endl; 
        cout << "[2] Lihat Semua Hewan"                     << endl; 
        cout << "[3] Cari Hewan"                            << endl; 
        cout << "[4] Urutkan Hewan"                         << endl; 
        cout << "[5] Antrian & Riwayat Pemeriksaan"         << endl;
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

int main() {
    addDummyData();
    menuUtama();
    return 0;
}