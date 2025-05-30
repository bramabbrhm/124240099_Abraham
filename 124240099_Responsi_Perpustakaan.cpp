#include <iostream>
#include <cstring>
using namespace std;

struct Buku {
    char judul[100];
    char pengarang[100];
    int tahun;
};

struct PohonBuku {
    Buku data;
    PohonBuku* kiri;
    PohonBuku* kanan;

    PohonBuku(Buku b) {
        data = b;
        kiri = kanan = nullptr;
    }
};


struct StackNode {
    Buku data;
    string aksi; 
    StackNode* next;
};


StackNode* top = nullptr;

void pushUndo(Buku data, string aksi) {
    StackNode* baru = new StackNode{data, aksi, top};
    top = baru;
}


bool popUndo(Buku& data, string& aksi) {
    if (top == nullptr) return false;
    data = top->data;
    aksi = top->aksi;
    StackNode* hapus = top;
    top = top->next;
    delete hapus;
    return true;
}


int bandingJudul(const char* a, const char* b) {
    return strcmp(a, b);
}

PohonBuku* sisip(PohonBuku* akar, Buku b, bool& sukses) {
    if (akar == nullptr) {
        sukses = true;
        return new PohonBuku(b);
    }

    int bantu = bandingJudul(b.judul, akar->data.judul);
    if (bantu < 0)
        akar->kiri = sisip(akar->kiri, b, sukses);
    else if (bantu > 0)
        akar->kanan = sisip(akar->kanan, b, sukses);
    else
        sukses = false;

    return akar;
}

void tampilInorder(PohonBuku* akar) {
    if (akar == nullptr) return;
    tampilInorder(akar->kanan);
    cout << "[" << akar->data.judul << "] [" << akar->data.pengarang << "] [" << akar->data.tahun << "]\n";
    tampilInorder(akar->kiri);
}

PohonBuku* minValueNode(PohonBuku* node) {
    while (node && node->kiri != nullptr)
        node = node->kiri;
    return node;
}

PohonBuku* hapus(PohonBuku* akar, const char* judul, Buku& terhapus, bool& sukses) {
    if (akar == nullptr) {
        sukses = false;
        return nullptr;
    }

    int bantu = bandingJudul(judul, akar->data.judul);

    if (bantu < 0)
        akar->kiri = hapus(akar->kiri, judul, terhapus, sukses);
    else if (bantu > 0)
        akar->kanan = hapus(akar->kanan, judul, terhapus, sukses);
    else {
        sukses = true;
        terhapus = akar->data;

        if (akar->kiri == nullptr && akar->kanan == nullptr) {
            delete akar;
            return nullptr;
        }

        else if (akar->kiri == nullptr) {
            PohonBuku* temp = akar->kanan;
            delete akar;
            return temp;
        }
        else if (akar->kanan == nullptr) {
            PohonBuku* temp = akar->kiri;
            delete akar;
            return temp;
        }

        PohonBuku* temp = minValueNode(akar->kanan);
        akar->data = temp->data;
        akar->kanan = hapus(akar->kanan, temp->data.judul, terhapus, sukses);
    }

    return akar;
}

PohonBuku* undo(PohonBuku* akar) {
    Buku data;
    string aksi;
    bool dummy;

    if (!popUndo(data, aksi)) {
        cout << "Tidak ada aksi yang bisa di-undo.\n";
        return akar;
    }

    if (aksi == "tambah") {
        Buku kosong;
        akar = hapus(akar, data.judul, kosong, dummy);
        cout << "Undo: buku [" << data.judul << "] berhasil dihapus.\n";
    } else if (aksi == "hapus") {
        akar = sisip(akar, data, dummy);
        cout << "Undo: buku [" << data.judul << "] berhasil dikembalikan.\n";
    }

    return akar;
}

int main() {
    PohonBuku* akar = nullptr;
    int pilihan;
    Buku data;
    bool sukses;

    do {
        cout << "\n=== Menu Perpustakaan ===\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Tampilkan Daftar Buku (Z-A)\n";
        cout << "3. Hapus Buku\n";
        cout << "4. Undo Aksi Terakhir\n";
        cout << "5. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "Judul Buku: ";
                cin.getline(data.judul, 100);
                cout << "Pengarang: ";
                cin.getline(data.pengarang, 100);
                cout << "Tahun Terbit: ";
                cin >> data.tahun;
                cin.ignore();
                akar = sisip(akar, data, sukses);
                if (sukses) {
                    cout << "Buku berhasil ditambahkan.\n";
                    pushUndo(data, "tambah");
                } else {
                    cout << "Judul sudah ada! Duplikat tidak diperbolehkan.\n";
                }
                break;

            case 2:
                cout << "\n=== Daftar Buku (Z-A) ===\n";
                tampilInorder(akar);
                break;

            case 3:
                cout << "Masukkan Judul Buku yang ingin dihapus: ";
                cin.getline(data.judul, 100);
                akar = hapus(akar, data.judul, data, sukses);
                if (sukses) {
                    cout << "Buku berhasil dihapus.\n";
                    pushUndo(data, "hapus");
                } else {
                    cout << "Buku tidak ditemukan.\n";
                }
                break;

            case 4:
                akar = undo(akar);
                break;

            case 5:
                cout << "Terima kasih!\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 5);

    return 0;
}
