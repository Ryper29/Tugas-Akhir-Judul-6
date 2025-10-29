#include <iostream>
using namespace std;

const int SIZE = 10;

struct Node {
    string key; // untuk nama_barang
    int harga; // value
    Node* next;
};

void initTable(Node* table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i] = nullptr;
    }
}

// Fungsi hash diubah untuk menerima string
int hashFunction(string key) {
    int hash = 0;
    // Metode hash sederhana
    // Menjumlahkan nilai ASCII dari semua karakter
    for (int i = 0; i < key.length(); i++) {
        hash += key[i];
    }
    return (hash % SIZE + SIZE) % SIZE;
}

// Parameter diubah untuk menerima string key dan int harga
void insert(Node* table[], string key, int harga) {
    int index = hashFunction(key);
    Node* cur = table[index];
    while (cur != nullptr) {
        if (cur->key == key) {
            cur->harga = harga;
            return;
        }
        cur = cur->next;
    }
    Node* baru = new Node;
    baru->key = key;
    baru->harga = harga;
    baru->next = table[index];
    table[index] = baru;
}

// Parameter diubah untuk mencari berdasarkan string key
Node* search(Node* table[], string key) {
    int index = hashFunction(key);
    Node* cur = table[index];
    while (cur != nullptr) {
        if (cur->key == key) {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

// Parameter diubah untuk menghapus berdasarkan string key
void removeKey(Node* table[], string key) {
    int index = hashFunction(key);
    Node* cur = table[index];
    Node* prev = nullptr;
    while (cur != nullptr) {
        if (cur->key == key) {
            if (prev == nullptr) {
                table[index] = cur->next;
            } else {
                prev->next = cur->next;
            }
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void display(Node* table[]) {
    cout << "\nIsi Hash Table Koperasi Elektro:\n"; 

    for (int i = 0; i < SIZE; i++) { 
          cout << "Index " << i << " -> ";
          Node* tmp = table[i];
          while (tmp != nullptr) {
              cout << "(" << tmp->key << ", Rp" << tmp->harga << ") -> ";
              tmp = tmp->next;
          }
          cout << "NULL\n";
    }
}

int main() {
    Node* table[SIZE];
    initTable(table);

    insert(table, "Buku", 5000);
    insert(table, "Pensil", 1000);
    insert(table, "Penghapus", 500);
    insert(table, "Penggaris", 2000);
    insert(table, "Spidol", 3000);
    insert(table, "Kertas", 10000);
    
    display(table);

    string barangCari = "Pensil";
    Node* hasil = search(table, barangCari);
    if (hasil != nullptr) {
        cout << "\nBarang '" << barangCari << "' ditemukan dengan harga = Rp" << hasil->harga << endl;
    } else {
        cout << "\nBarang '" << barangCari << "' tidak ditemukan\n";
    }

    string barangHapus = "Pensil";
    removeKey(table, barangHapus);
    cout << "\nSetelah menghapus '" << barangHapus << "':\n";
    display(table);
    
    hasil = search(table, barangHapus);
    if (hasil != nullptr) {
        cout << "\nBarang '" << barangHapus << "' ditemukan dengan harga = Rp" << hasil->harga << endl;
    } else {
        cout << "\nBarang '" << barangHapus << "' tidak ditemukan\n";
    }

    return 0;
}