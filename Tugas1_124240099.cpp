#include <iostream>
#include <iomanip>
using namespace std;

struct barang{
    string nama;
    int jumlah, harga;
};
barang brg[1000];

void data(barang &brg){
    cout << "Nama : "; getline(cin, brg.nama);
    cout << "Jumlah : "; cin >> brg.jumlah;
    cout << "Harga : " ;cin >> brg.harga;
};

void bubblesort(barang brg[], int banyakdata) {
    for (int i = 0; i < banyakdata - 1; i++) {
        for (int j = 0; j < banyakdata - i - 1; j++) {
            if (brg[j].nama > brg[j + 1].nama) {
                swap(brg[j], brg[j + 1]);
            }
        }
    }
}

void tampilkanData(barang brg[], int banyakdata) {
    if (banyakdata == 0) {
        cout << "\nBelum ada data!";
        return;
    }

    cout << left << setw(20) << "Nama" 
    << setw(10) << "Jumlah" 
    << setw(10) << "Harga" << endl;
    cout << setw(40) << setfill('-') << "-" << endl;  // Separator line
    cout << setfill(' ');  // Reset fill character

    for (int i = 0; i < banyakdata; i++) {
        cout << left << setw(20) << brg[i].nama
        << setw(10) << brg[i].jumlah 
        << setw(10) << brg[i].harga << endl;
    }
}

void sequentialSearch(barang brg[], int banyakdata)
{
    int nilaiCari, i = 0;
    bool found = false;
    cout << "================ Toko Buku =================" << endl;
    cout << "============ Sequential Search =============\n";
    cout << "Masukkan Harga yang akan dicari = ";
    cin >> nilaiCari;
    cout << endl
         << endl;
    while (i < banyakdata)
    {
        if (brg[i].harga == nilaiCari)
        {
            if (!found)
            {
                cout << setw(45) << setfill('=') << "" << endl;
                cout << left << setw(6) << setfill(' ') << "Index" << setw(20) << setfill(' ') << "Nama" << setw(10) << setfill(' ') << "Harga (Rp)" << endl;
                cout << setw(45) << setfill('-') << "" << endl;
                found = true;
            }
            cout << left << setw(6) << setfill(' ') << i << setw(20) << setfill(' ') << brg[i].nama << setw(10) << setfill(' ') << brg[i].harga << endl;
        }
        i = i + 1;
    }
    if (!found)
    {
        cout << "Data tidak ditemukan" << endl;
    }
    else
    {
        cout << setw(45) << setfill('-') << "" << endl;
    }
    cin.ignore();
    cin.ignore();
}



int main (){
    int menu, banyakinput;
    int banyakdata = 0;
    char menusearch;

    do{

        cout << "\n1. Input Data Barang";
        cout << "\n2. Tampilkan Data Barang";
        cout << "\n3. Cari Data Barang";
        cout << "\n4. Keluar";
        cout << "\n\nPilih Menu : "; cin >> menu;
        system("cls");

        switch (menu) {
            case 1:
            cout << "Input Data Barang";
            cout << "\nBerapa data barang yang ingin dimasukkan? = "; cin >> banyakinput;
            
            for(int i = 0; i < banyakinput; i++){
                cout << "\nData barang ke-" << i+1 << endl;
                cin.ignore();
                data(brg[banyakdata + i]);
            };

            banyakdata += banyakinput;

            cout << "Data berhasil ditambahkan";
            cin.ignore();
            cin.ignore();
            break;

            case 2:
            cout << "\nData Barang\n";
            bubblesort(brg, banyakdata);
            tampilkanData(brg, banyakdata);
            cin.ignore();
            cin.ignore();
            break;

            case 3:
            do{
            cout << "\nCari Data Barang";
            cout << "\na. Berdasarkan Harga (Sequential)";
            cout << "\nb. Berdasarkan Nama (Binary)";
            cout << "\nc. Kembali";
            cout << "\n\nPilih Menu : "; cin >> menusearch;
                switch(menusearch);
                case 'a':
                sequentialSearch(brg, banyakdata);
                break;

                case 'b':
                cout << "gatau lagi nyari tahu cara binary";
                break;
            
            break;
            }
            while (menusearch != 'a' && 'b');
        }
    }
    while(menu >= 4);
}