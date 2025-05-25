#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Mhs {
    int nim;
    char nama[50];
};

struct PtbNode {
    Mhs data;
    PtbNode* kiri;
    PtbNode* kanan;
};

PtbNode* sisip(PtbNode* akar, Mhs data) {
    if (akar == nullptr) {
        PtbNode* newNode = new PtbNode{data, nullptr, nullptr};
        return newNode;
    }
    if (data.nim < akar->data.nim)
        akar->kiri = sisip(akar->kiri, data);
    else if (data.nim > akar->data.nim)
        akar->kanan = sisip(akar->kanan, data);
    return akar;
}

void inorder(PtbNode* akar) {
    if (akar == nullptr) return;
    inorder(akar->kiri);
    cout << akar->data.nim << " - " << akar->data.nama << endl;
    inorder(akar->kanan);
}

void simpankeFile(PtbNode* akar, FILE* file) {
    if (akar == nullptr) return;
    simpankeFile(akar->kiri, file);
    fwrite(&akar->data, sizeof(Mhs), 1, file);
    simpankeFile(akar->kanan, file);
}

void cariNIM(PtbNode* akar, int nim) {
    if (akar == nullptr) {
        cout << "NIM tidak ditemukan.\n";
        return;
    }
    if (nim == akar->data.nim) {
        cout << "Data ditemukan:\n";
        cout << "NIM: " << akar->data.nim << endl;
        cout << "Nama: " << akar->data.nama << endl;
        return;
    }
    if (nim < akar->data.nim)
        cariNIM(akar->kiri, nim);
    else
        cariNIM(akar->kanan, nim);
}

PtbNode* nilaiterkecil(PtbNode* node) {
    while (node && node->kiri != nullptr)
        node = node->kiri;
    return node;
}

PtbNode* hapus(PtbNode* akar, int nim) {
    if (!akar) return nullptr;

    if (nim < akar->data.nim)
        akar->kiri = hapus(akar->kiri, nim);
    else if (nim > akar->data.nim)
        akar->kanan = hapus(akar->kanan, nim);
    else {
        if (!akar->kiri) {
            PtbNode* bantu = akar->kanan;
            delete akar;
            return bantu;
        } else if (!akar->kanan) {
            PtbNode* bantu = akar->kiri;
            delete akar;
            return bantu;
        }
        PtbNode* bantu = nilaiterkecil(akar->kanan);
        akar->data = bantu->data;
        akar->kanan = hapus(akar->kanan, bantu->data.nim);
    }
    return akar;
}

PtbNode* bacaDariFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) return nullptr;

    PtbNode* akar = nullptr;
    Mhs bantu;

    while (fread(&bantu, sizeof(Mhs), 1, file) == 1) {
        akar = sisip(akar, bantu);
    }

    fclose(file);
    return akar;
}

void clear(){
    cout << "\nTekan tombol apapun untuk melanjutkan";
    cin.ignore();
    cin.ignore();
    system("cls");
}

int main() {
    PtbNode* akar = bacaDariFile("mahasiswa.dat");

    int pilih;
    do {
        cout << "\n=== MENU MANAJEMEN MAHASISWA ===\n";
        cout << "1. Tambah Mahasiswa\n";
        cout << "2. Cari Mahasiswa\n";
        cout << "3. Tampilkan Semua Mahasiswa\n";
        cout << "4. Hapus Mahasiswa\n";
        cout << "5. Simpan Data ke File\n";
        cout << "6. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilih;

        switch(pilih) {
            case 1: {
                Mhs m;
                cout << "Masukkan NIM: ";
                cin >> m.nim;
                cin.ignore();
                cout << "Masukkan Nama: ";
                cin.getline(m.nama, 50);
                akar = sisip(akar, m);
                cout << "Data berhasil ditambahkan.\n";
                clear();
                break;
            }
            
            case 2: {
                int nim;
                cout << "Masukkan NIM yang dicari: ";
                cin >> nim;
                cariNIM(akar, nim);
                clear();
                break;
            }
            
            case 3: {
                cout << "\nDaftar Mahasiswa (urut NIM):\n";
                inorder(akar);
                clear();
                break;
            }
            
            case 4: {
                int nim;
                cout << "Masukkan NIM yang akan dihapus: ";
                cin >> nim;
                akar = hapus(akar, nim);
                cout << "Data berhasil dihapus\n";
                clear();

                break;
            }
            
            case 5: {
                FILE* file = fopen("mahasiswa.dat", "wb");
                if (!file) {
                    cout << "Gagal membuka file untuk penyimpanan.\n";
                } else {
                    simpankeFile(akar, file);
                    fclose(file);
                    cout << "Data berhasil disimpan ke file.\n";
                }
                clear();
                break;
            }
            
            case 6: {
                cout << "Program selesai.\n";
                break;
            }
            
            default: {
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                clear();
                break;
            }
        }
    } while (pilih != 6);

    return 0;
}
