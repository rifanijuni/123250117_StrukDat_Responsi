// Responsi Struktur Data
// Nama : Rifani Juniarti
// NIM  : 123250117

#include <iostream>
#include <string>
using namespace std;

struct nodeQueue
{
    int kode;
    string nama;
    nodeQueue *next;
};

struct nodeStack
{
    int kode;
    string nama;
    nodeStack *next;
};

struct nodeTree
{
    int kode;
    string nama;
    nodeTree *kiri, *kanan;
};

nodeQueue *front = nullptr, *last = nullptr;
nodeStack *top = nullptr;
nodeTree *root = nullptr;

nodeTree *tambahTree(nodeTree *akar, int kode, string nama)
{
    if (akar == nullptr)
        return new nodeTree{kode, nama, nullptr, nullptr};
    if (kode < akar->kode)
    {
        akar->kiri = tambahTree(akar->kiri, kode, nama);
    }
    else
    {
        akar->kanan = tambahTree(akar->kanan, kode, nama);
    }
    return akar;
}

nodeTree *cariTree(nodeTree *akar, int kode)
{
    if (akar == nullptr || akar->kode == kode)
        return akar;

    if (kode < akar->kode)
    {
        return cariTree(akar->kiri, kode);
    }
    else
    {
        return cariTree(akar->kanan, kode);
    }
}

nodeTree *hapusTree(nodeTree *akar, int kode)
{
    if (akar == nullptr)
        return nullptr;

    if (kode < akar->kode)
    {
        akar->kiri = hapusTree(akar->kiri, kode);
    }
    else if (kode > akar->kode)
    {
        akar->kanan = hapusTree(akar->kanan, kode);
    }
    else
    {
        if (akar->kiri == nullptr)
        {
            nodeTree *sisa = akar->kanan;
            delete akar;
            return sisa;
        }
        else if (akar->kanan == nullptr)
        {
            nodeTree *sisa = akar->kiri;
            delete akar;
            return sisa;
        }
        nodeTree *temp = akar->kanan;
        while (temp->kiri != nullptr)
            temp = temp->kiri;
        akar->kode = temp->kode;
        akar->nama = temp->nama;
        akar->kanan = hapusTree(akar->kanan, temp->kode);
    }
    return akar;
}

bool validasiNama(string teks)
{
    for (int i = 0; i < teks.length(); i++)
        if (teks[i] != ' ')
            return true;
    return false;
}

void tambahEnergi()
{
    int kode;
    string nama;

    cout << "Masukkan kode energi: ";
    cin >> kode;

    if (cin.fail() || kode <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode energi harus berupa angka lebih besar dari 0\n\n";
        return;
    }

    nodeQueue *queue = front;
    while (queue != nullptr)
    {
        if (queue->kode == kode)
        {
            cout << "Nomor kode sudah digunakan!\n\n";
            return;
        }
        queue = queue->next;
    }

    nodeStack *stack = top;
    while (stack != nullptr)
    {
        if (stack->kode == kode)
        {
            cout << "Nomor kode sudah digunakan!\n\n";
            return;
        }
        stack = stack->next;
    }

    cout << "Masukkan nama energi: ";
    cin.ignore();
    getline(cin, nama);
    if (!validasiNama(nama))
    {
        cout << "Nama energi tidak boleh kosong!\n\n";
        return;
    }

    nodeQueue *bantu = new nodeQueue{kode, nama, nullptr};
    if (front == nullptr)
        front = last = bantu;
    else
    {
        last->next = bantu;
        last = bantu;
    }
    cout << "Berhasil memasukkan energi!\n\n";
}

void lihatAntrean()
{
    if (front == nullptr)
    {
        cout << "Antrean energi masih kosong!\n";
        return;
    }

    cout << "=== Lihat Energi Dalam Antrean ===\n\n";
    nodeQueue *current = front;
    int no = 1;

    while (current != nullptr)
    {
        cout << no++ << ". [" << current->kode << "] " << current->nama << endl;
        current = current->next;
    }
    cout << endl;
}

void prosesEnergi()
{
    if (front == nullptr)
    {
        cout << "Antrean energi masih kosong!\n";
        return;
    }

    nodeQueue *hapus = front;
    nodeStack *bantu = new nodeStack{hapus->kode, hapus->nama, top};
    top = bantu;
    root = tambahTree(root, hapus->kode, hapus->nama);
    cout << "Berhasil memproses energi " << hapus->nama << "!\n\n";

    front = hapus->next;
    if (front == nullptr)
        last = nullptr;
    delete hapus;
}

void lihatEnergiTerserap()
{
    if (top == nullptr)
    {
        cout << "Belum ada energi yang terserap!\n";
        return;
    }

    cout << "=== Lihat Energi Yang Terserap ===\n\n";
    nodeStack *current = top;
    int no = 1;

    while (current != nullptr)
    {
        cout << no++ << ". [" << current->kode << "] " << current->nama << endl;
        current = current->next;
    }
    cout << endl;
}

void hapusRiwayatTeratas()
{
    if (top == nullptr)
    {
        cout << "Belum ada energi yang terserap!\n";
        return;
    }

    cout << "Riwayat energi " << top->nama << " teratas telah dihapus!\n\n";
    nodeStack *hapus = top;
    top = top->next;
    delete hapus;
}

void cariEnergi()
{
    if (root == nullptr)
    {
        cout << "Organ masih kosong!\n";
        return;
    }

    int kode;
    cout << "Masukkan kode energi: ";
    cin >> kode;

    if (cin.fail() || kode <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode energi harus berupa angka lebih besar dari 0\n\n";
        return;
    }

    nodeTree *hasil = cariTree(root, kode);
    if (hasil == nullptr)
    {
        cout << "Energi tidak ditemukan di dalam organ!\n\n";
        return;
    }
    cout << "Ditemukan: [" << hasil->kode << "] " << hasil->nama << "\n\n";
}

void preOrder(nodeTree *akar, int &no)
{
    if (akar == nullptr)
        return;

    cout << no++ << ". [" << akar->kode << "] " << akar->nama << endl;
    preOrder(akar->kiri, no);
    preOrder(akar->kanan, no);
}

void inOrder(nodeTree *akar, int &no)
{
    if (akar == nullptr)
        return;

    inOrder(akar->kiri, no);
    cout << no++ << ". [" << akar->kode << "] " << akar->nama << endl;
    inOrder(akar->kanan, no);
}

void postOrder(nodeTree *akar, int &no)
{
    if (akar == nullptr)
        return;

    postOrder(akar->kiri, no);
    postOrder(akar->kanan, no);
    cout << no++ << ". [" << akar->kode << "] " << akar->nama << endl;
}

void lihatOrgan()
{
    if (root == nullptr)
    {
        cout << "Organ masih kosong!\n";
        return;
    }

    int pilihan, no = 1;
    cout << "=== Isi Kristal Organ ===\n"
         << "1. Pre-order\n"
         << "2. In-order\n"
         << "3. Post-order\n\n"
         << "Masukkan pilihan anda: ";
    cin >> pilihan;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Pilihan harus berupa angka (1-3)\n\n";
        return;
    }
    cout << endl;

    switch (pilihan)
    {
    case 1:
        preOrder(root, no);
        break;
    case 2:
        inOrder(root, no);
        break;
    case 3:
        postOrder(root, no);
        break;
    default:
        cout << "Pilihan tidak valid. Masukkan menu 1-3!\n\n";
    }
    cout << endl;
}

void gunakanEnergi()
{
    if (root == nullptr)
    {
        cout << "Organ masih kosong!\n";
        return;
    }

    int kode;
    cout << "Masukkan kode energi: ";
    cin >> kode;

    if (cin.fail() || kode <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode energi harus berupa angka lebih besar dari 0\n\n";
        return;
    }

    nodeTree *hasil = cariTree(root, kode);
    if (hasil == nullptr)
    {
        cout << "Energi dengan kode " << kode << " tidak ada di dalam organ!\n\n";
        return;
    }
    cout << "Energi " << hasil->nama << " telah digunakan!\n\n";
    root = hapusTree(root, kode);
}

// bersihkan memory
void clearQueue()
{
    while (front != nullptr)
    {
        nodeQueue *hapus = front;
        front = front->next;
        delete hapus;
    }
    last = nullptr;
}
void clearStack()
{
    while (top != nullptr)
    {
        nodeStack *hapus = top;
        top = top->next;
        delete hapus;
    }
}
void clearTree(nodeTree *akar)
{
    if (akar == nullptr)
        return;
    clearTree(akar->kiri);
    clearTree(akar->kanan);
    delete akar;
}

int main()
{
    int pilihan = 0;
    char pilTambah = 'y';

    do
    {
        cout << "\n=== SISTEM ORGAN INTI NIRWANA ===\n\n"
             << "1. Tambah Energi\n"
             << "2. Lihat Energi Dalam Antrean\n"
             << "3. Proses Energi\n"
             << "4. Lihat Energi Yang Sudah Terserap\n"
             << "5. Hapus Riwayat Energi Teratas\n"
             << "6. Cari Energi Di Organ\n"
             << "7. Lihat Isi Organ\n"
             << "8. Gunakan Energi\n"
             << "9. Keluar\n\n"
             << "Masukkan pilihan anda: ";
        cin >> pilihan;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Pilihan harus berupa angka (1-9)\n\n";
            continue;
        }

        switch (pilihan)
        {
        case 1:
            pilTambah = 'y';
            while (pilTambah == 'y' || pilTambah == 'Y')
            {
                tambahEnergi();
                do
                {
                    cout << "Apakah anda ingin menambahkan energi lagi? (y/n): ";
                    cin >> pilTambah;
                } while (pilTambah != 'y' && pilTambah != 'Y' && pilTambah != 'n' && pilTambah != 'N');
            }
            break;
        case 2:
            lihatAntrean();
            break;
        case 3:
            prosesEnergi();
            break;
        case 4:
            lihatEnergiTerserap();
            break;
        case 5:
            hapusRiwayatTeratas();
            break;
        case 6:
            cariEnergi();
            break;
        case 7:
            lihatOrgan();
            break;
        case 8:
            gunakanEnergi();
            break;
        case 9:
            clearQueue();
            clearStack();
            clearTree(root);
            root = nullptr;

            cout << "\nKeluar dari Sistem Organ Inti Nirwana\nSemua memori dibebaskan\nTerima kasih\n\n";
            return 0;
        default:
            cout << "Pilihan yang dimasukkan tidak valid! masukkan menu 1-9!\n\n";
        }
    } while (pilihan != 9);
}