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
        cout << "\nBelum ada data. Silahkan isi data terlebih dahulu";
        cout << "\nTekan tombol apapun untuk melanjutkan";
        return;
    }

    cout << left << setw(20) << "Nama" 
    << setw(10) << "Jumlah" 
    << setw(10) << "Harga" << endl;
    cout << setw(40) << setfill('-') << "-" << endl;
    cout << setfill(' ');

    for (int i = 0; i < banyakdata; i++) {
        cout << left << setw(20) << brg[i].nama
        << setw(10) << brg[i].jumlah 
        << setw(10) << brg[i].harga << endl;
    }
}

void sequentialSearch(barang brg[], int banyakdata)
{
    int pricesearch, i = 0;
    bool found = false;
    cout << "================ Toko Kelontong B-2 =================\n";
    cout << "============ Sequential Search =============\n";
    cout << "Masukkan Harga yang akan dicari = ";
    cin >> pricesearch;
    cout << endl
         << endl;
    while (i < banyakdata)
    {
        if (brg[i].harga == pricesearch)
        {
            if (!found)
            {
                cout << setw(60) << setfill('=') << "" << endl;
                cout << left << setw(6) << setfill(' ') << "No" 
                     << setw(20) << setfill(' ') << "Nama" 
                     << setw(10) << setfill(' ') << "Jumlah" 
                     << setw(10) << setfill(' ') << "Harga (Rp)" << endl;
                cout << setw(60) << setfill('-') << "" << endl;
                found = true;
            }
            cout << left << setw(6) << setfill(' ') << i + 1 
            << setw(20) << setfill(' ') << brg[i].nama 
            << setw(10) << setfill(' ') << brg[i].jumlah 
            << setw(10) << setfill(' ') << brg[i].harga << endl;
        }
        i = i + 1;
    }
    if (!found)
    {
        cout << "Barang dengan harga Rp" << pricesearch << " tidak ditemukan" << endl;
    }
    else
    {
        cout << setw(45) << setfill('-') << "" << endl;
    }
    cout << "Tekan tombol apapun untuk melanjutkan";
}

void binarySearch(barang brg[],int banyakdata){
    bubblesort(brg, banyakdata);
    bool found = false;
    int low = 0;
    int high = banyakdata - 1;
    string namesearch;
    cout << "================ Toko Kelontong B-2 ================\n";
    cout << "=============== Binary Search ==============\n";
    cout << "Masukkan Nama Barang yang akan dicari : ";
    cin.ignore();
    getline(cin, namesearch);

    while (low <= high) {
        int mid = (low + high) / 2;
        if (brg[mid].nama == namesearch) {
            found = true;
            cout << setw(60) << setfill('=') << "" << endl; 
            cout << left << setw(6) << setfill(' ') << "Nama" 
                 << setw(10) << setfill(' ') << "Jumlah" 
                 << setw(10) << setfill(' ') << "Harga (Rp)" << endl;
            cout << setw(60) << setfill('-') << "" << endl; 
            cout << left << setw(6) << setfill(' ') << brg[mid].nama 
                 << setw(10) << setfill(' ') << brg[mid].jumlah 
                 << setw(10) << setfill(' ') << brg[mid].harga << endl;
            cout << setw(60) << setfill('-') << "" << endl;
            break;
        } else if (brg[mid].nama < namesearch) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    if (!found){
        cout << "Barang dengan nama " << namesearch << " tidak ditemukan" << endl;
    }
    cout << "Tekan tombol apapun untuk melanjutkan";
}



int main (){
    int menu, banyakinput;
    int banyakdata = 0;
    char menusearch;

    do{
        cout << "================ Toko Kelontong B-2 ================\n";
        cout << "\n1. Input Data Barang";
        cout << "\n2. Tampilkan Data Barang";
        cout << "\n3. Cari Data Barang";
        cout << "\n4. Keluar";
        cout << "\n\nPilih Menu : "; cin >> menu;
        system("cls");

        switch (menu) {
            case 1:
            cout << "================ Toko Kelontong B-2 ================\n";
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
            cout << "================ Toko Kelontong B-2 ================\n";
            cout << "\nData Barang\n";
            bubblesort(brg, banyakdata);
            tampilkanData(brg, banyakdata);
            cin.ignore();
            cin.ignore();
            break;

            case 3:
            if (banyakdata == 0) {
                cout << "\nBelum ada data. Silahkan isi data terlebih dahulu!";
                cin.ignore();
                cin.ignore();
                break;
            }

            do{
                cout << "================ Toko Kelontong B-2 ================\n";
                cout << "\nCari Data Barang";
                cout << "\na. Berdasarkan Harga (Sequential)";
                cout << "\nb. Berdasarkan Nama (Binary)";
                cout << "\nc. Kembali";
                cout << "\n\nPilih Menu : "; cin >> menusearch;
                    switch(menusearch){;
                    case 'a': case 'A':
                    sequentialSearch(brg, banyakdata);
                    break;

                    case 'b': case 'B':
                    binarySearch(brg, banyakdata);
                    break;

                    case 'c':
                    case 'C':
                        break;
    
                    default:
                        cout << "Pilihan tidak valid! Silahkan pilih antara a-c!\n";
                }

                if (menusearch != 'c' && menusearch != 'C') {
                    cin.ignore();
                    cin.ignore();
                }
            }
            while (menusearch != 'c' && menusearch != 'C');
            break;
        
            case 4:
            cout << "Terima kasih, program selesai.\n";
            return 0;  

            default:
            cout << "Pilihan tidak ada, silakan pilih menu yang ada.\n";
            cin.ignore();
            cin.ignore();
            break;
        }
 
    }
    while(true);
    return 0;
}
