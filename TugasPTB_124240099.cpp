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
