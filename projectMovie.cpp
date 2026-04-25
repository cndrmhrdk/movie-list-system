#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

struct akun_user{
    string username;
    string password;
    akun_user *next;
};

akun_user *head_user = NULL;

struct akun_admin{
    string username;
    string password;
    akun_admin *next;
};

akun_admin *head_admin = NULL;

string
    
    input_username,
    input_password
;

int jumlah_data_film = 0;

struct Movie {
    int id;
    string judul;
    string genre;
    float rating;
};

struct Node {
    Movie data;
    Node* prev;
    Node* next;
};

Node *head = NULL;
Node *tail = NULL;

void menu_admin();

void menu_user();

void next_menu(string nama_menu){
    char next;
    do {
        cout << "mau lanjut ke menu " << nama_menu << "? (Y/N) |  ";
        cin >> next;
        next = toupper(next);

    } while (next != 'Y' && next != 'N');

    if (next == 'N'){
    cout << "TERIMA KASIH YA\n" << endl;
    exit(0);
    }
}

void sign_up_user(){
    akun_user *baru = new akun_user;

    cout << "SIGN UP FIRST YA (AS A USER)" << endl;
    cout << "username : ";
    cin >> baru->username;
    cout << "password : ";
    cin >> baru->password;

    FILE *file = fopen("akun_user.txt", "a");
    fprintf(file, "%s %s\n", baru->username.c_str(), baru->password.c_str());
    fclose(file);

    cout << "account created" << endl;
    cout << endl;
}

void login_user(){
        bool match = false;
    char punya_akun;
    head_user = NULL;
    
    cout << "SILAKAN LOGIN SEBAGAI ADMIN" << endl;
    
    FILE *file = fopen("akun_user.txt", "r");

    if(file == NULL){
        cout << "Akun user tidak ditemukan!\n";
        return;
    }
    
    char username[100], password[100];

    while(fscanf(file, "%s %s\n", username, password) != EOF){
        akun_user *baru = new akun_user;
        baru->next = NULL;

        baru->username = username;
        baru->password = password;
        baru->next = NULL;
    
        if(head_admin == NULL){
            head_user = baru;
        } else {
            akun_user *temp = head_user;
    
            while(temp->next != NULL){
                temp = temp->next;
            }
    
            temp->next = baru;
        }
    }

    fclose(file);

    do{
        cout << "username : ";
        cin >> input_username;
        cout << "password : ";
        cin >> input_password;

        akun_user *temp = head_user;

        while (temp != NULL){
            if (temp->username == input_username && temp->password == input_password){
                match = true;
                break;
            }
            temp = temp->next;
        }
        if (match){
            cout << "Login Success" << endl << endl;
            break;
        } else {
            cout << "Account not found, please re-login" << endl << endl;
        }
        
    } while (!match);
}

void sign_up_admin(){
    akun_admin *baru = new akun_admin;

    cout << "SIGN UP FIRST YA (AS A ADMIN)" << endl;
    cout << "username : ";
    cin >> baru->username;
    cout << "password : ";
    cin >> baru->password;

    FILE *file = fopen("akun_admin.txt", "a");
    fprintf(file, "%s %s\n", baru->username.c_str(), baru->password.c_str());
    fclose(file);
    
    cout << "account created" << endl << endl;
}

void login_admin(){
    bool match = false;
    char punya_akun;
    head_admin = NULL;
    
    cout << "SILAKAN LOGIN SEBAGAI ADMIN" << endl;
    
    FILE *file = fopen("akun_admin.txt", "r");

    if(file == NULL){
        cout << "Akun admin tidak ditemukan!\n";
        return;
    }
    
    char username[100], password[100];

    while(fscanf(file, "%s %s\n", username, password) != EOF){
        akun_admin *baru = new akun_admin;
        baru->next = NULL;

        baru->username = username;
        baru->password = password;
        baru->next = NULL;
    
        if(head_admin == NULL){
            head_admin = baru;
        } else {
            akun_admin *temp = head_admin;
    
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = baru;
        }
    }
    fclose(file);

    do{
        cout << "username : ";
        cin >> input_username;
        cout << "password : ";
        cin >> input_password;

        akun_admin *temp = head_admin;

        while (temp != NULL){
            if (temp->username == input_username && temp->password == input_password){
                match = true;
                break;
            }
            temp = temp->next;
        }
        if (match){
            cout << "Login Success" << endl << endl;
            break;
        } else {
            cout << "Account not found, please re-login" << endl << endl;
        }
        
    } while (!match);
}

void hitung_jumlah_film(){
    FILE *hitung = fopen("movie.txt", "r");

    int id;
    char judul[100];
    char genre[100];
    float rating;
    
    while(fscanf(hitung, "%d|%[^|]|%[^|]|%f\n", &id, judul, genre, &rating) != EOF){
        jumlah_data_film = jumlah_data_film + 1;
    }

    fclose(hitung);
}

void tambah_film(){
    hitung_jumlah_film();

	int jumlahfilm;
    
	cout << "SILAKAN TAMBAHKAN FILM" <<endl;
	cout << "Ingin menambah berapa film: ";
	cin >>jumlahfilm;

	for(int i = 0; i < jumlahfilm; i++) {
        Node *baru = new Node;

        cout << "Film ke-" << jumlah_data_film + i + 1 <<endl;
        baru->data.id = jumlah_data_film + i + 1; 
        cout << "ID Film     : " << baru->data.id << endl;
        cout << "Judul       : "; 
        cin.ignore(); 
        getline(cin, baru->data.judul);
        cout << "Genre       : "; 
        cin >> baru->data.genre;
        cout << "Rating      : ";
        cin >> baru->data.rating;

        baru->next = NULL;
        baru->prev = NULL;
    
        if(head == NULL){
            head = tail = baru;
        } else {
            baru->prev = tail;
            tail->next = baru;
            tail = baru;
        }
    
        FILE *file = fopen("movie.txt", "a");
        fprintf(file, "%d|%s|%s|%.1f\n", 
            baru->data.id, 
            baru->data.judul.c_str(), 
            baru->data.genre.c_str(), 
            baru->data.rating);
        fclose(file);
    }

    cout << "Data berhasil disimpan!\n\n";
}

void load_data_film(){
    FILE *load = fopen("movie.txt", "r");

    if(load == NULL){
        cout << "Data film masih kosong" << endl;
        return;
    }

    head = NULL;
    tail = NULL;

    int id;
    char judul[100];
    char genre[100];
    float rating;

    while(fscanf(load, "%d|%[^|]|%[^|]|%f\n", &id, judul, genre, &rating) != EOF){
        Node *baru = new Node;

        baru->data.id = id;
        baru->data.judul = judul;
        baru->data.genre = genre;
        baru->data.rating = rating;

        baru->prev = NULL;
        baru->next = NULL;

        if(head == NULL){
            head = tail = baru;
        } else {
            baru->prev = tail;
            tail->next = baru;
            tail = baru;

        }
    }
    fclose(load);
}

void tampil_film(){
    hitung_jumlah_film();

    Node *temp = head;
    
    cout << "TAMPILAN FILM" <<endl;
    cout << "===========================================================================" << endl;
    cout << left
        << "| " << setw(5)  << "ID"
        << "| " << setw(35) << "JUDUL"
        << "| " << setw(18) << "GENRE"
        << "| " << setw(8)  << "RATING"
        << "|" << endl;
    cout << "===========================================================================" << endl;

    if(temp == NULL){
        cout << "Data Film masih kosong" << endl;
        return;
    }

    while (temp != NULL) {
        cout << left
            << "| " << setw(5)  << temp->data.id
            << "| " << setw(35) << temp->data.judul
            << "| " << setw(18) << temp->data.genre
            << "| " << setw(8)  << temp->data.rating
            << "|" << endl;
        cout << "---------------------------------------------------------------------------" << endl;
        temp = temp->next;
    }
}

void bubble_sort(int pilihan){
    Node *i, *j;
    Movie temp;

    if (pilihan == 1){
        for(i = head; i != NULL; i = i->next){
            for(j = i->next; j != NULL; j = j->next){
                if(i->data.judul > j->data.judul){
                    temp = i->data;
                    i->data = j->data;
                    j->data = temp;
                }
            }
        }
    } else if (pilihan == 2){
        for(i = head; i != NULL; i = i->next){
            for(j = i->next; j != NULL; j = j->next){
                if(i->data.genre > j->data.genre){
                    temp = i->data;
                    i->data = j->data;
                    j->data = temp;
                }
            }
        }
    } else if (pilihan == 3){
        for(i = head; i != NULL; i = i->next){
            for(j = i->next; j != NULL; j = j->next){
                if(i->data.rating > j->data.rating){
                    temp = i->data;
                    i->data = j->data;
                    j->data = temp;
                }
            }
        }
    }
}

Node* getTail(Node* cur){
    while(cur && cur->next != NULL){
        cur = cur->next;
    }
    return cur;
}

Node* partition(int pilihan_sort, Node* low, Node* high){
    if (pilihan_sort == 1){
        string pivot = high->data.judul;
        Node* i = low;
    
        for(Node* j = low; j != high; j = j->next){
            if(j->data.judul >= pivot){
                swap(i->data, j->data);
                i = i->next;
            }
        }
        swap(i->data, high->data);
        return i;

    } else if (pilihan_sort == 2){
        string pivot = high->data.genre;
        Node* i = low;
    
        for(Node* j = low; j != high; j = j->next){
            if(j->data.genre >= pivot){
                swap(i->data, j->data);
                i = i->next;
            }
        }
        swap(i->data, high->data);
        return i;

    } else if (pilihan_sort == 3){
        float pivot = high->data.rating;
        Node* i = low;
    
        for(Node* j = low; j != high; j = j->next){
            if(j->data.rating >= pivot){
                swap(i->data, j->data);
                i = i->next;
            }
        }
        swap(i->data, high->data);
        return i;
    }
}

void quickSort(int pilihan_sort, Node* low, Node* high){
    if(high != NULL && low != high && low != high->next){
        Node* p = partition(pilihan_sort, low, high);
        quickSort(pilihan_sort, low, p->prev);
        quickSort(pilihan_sort, p->next, high);
    }
}

void edit_film(){
    int id;

    cout << "Masukkan ID film yang ingin diedit: ";
    cin >> id;

    Node *temp = head;

    if(temp == NULL){
        cout << "Data Film masih kosong" << endl;
        return;
    }

    while(temp != NULL){
        if(temp->data.id == id){
            cout << "Data ditemukan!\n";

            cout << "Judul baru  : "; cin >> temp->data.judul;
            cout << "Genre baru  : "; cin >> temp->data.genre;
            cout << "Rating baru : "; cin >> temp->data.rating;

            cout << "Data berhasil diubah!\n\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Data tidak ditemukan!\n\n";
}

void hapus_film(){
    int id;
    cout << "Selamat Datang di Menu Hapus Film" << endl;
    cout << "Masukkan ID film yang ingin dihapus: ";
    cin >> id;

    Node *temp = head
    // *prev = NULL
    ;

    while(temp != NULL && temp->data.id != id){
        temp = temp->next;
    }
    
    if(temp == NULL){
        cout << "Data tidak ditemukan!\n\n";
        return;
    }

    if(temp->prev != NULL){
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }

    if(temp->next != NULL){
        temp->next->prev = temp->prev;
    } else {
        tail = temp->prev;
    }
    
    delete temp;
    cout << "Data berhasil dihapus!\n\n";
}

void menu_user(){
    int pilihan, pilih_sort, pilih_asc_dsc;

    do{
        cout << "\n=== MENU USER ===\n";
        cout << "1. List Film\n";
        cout << "2. Rekomendasi Film\n";
        cout << "3. Watchlist\n";
        cout << "4. Hapus Film\n";
        cout << "5. Logout\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        if(pilihan == 1){
            load_data_film();

            cout << "Urutkan film berdasarkan :\n";
            cout << "1. Judul\n";
            cout << "2. Genre\n";
            cout << "3. Rating\n";
            cout << "Pilihan : ";
            cin >> pilih_sort;

            cout << "\n1. Ascending\n";
            cout << "2. Descending\n";
            cout << "Pilihan : ";
            cin >> pilih_asc_dsc;
            
            if (pilih_asc_dsc == 1){
                bubble_sort(pilih_sort);
                tampil_film();
            } else if (pilih_asc_dsc == 2){
                quickSort(pilih_sort, head, getTail(head));
                tampil_film();
            } else {
                cout << "Pilihan tidak valid" << endl;
            }
        }

    } while(pilihan != 5 || pilihan < 1 || pilihan > 5);
}

void menu_admin(){
    int pilihan, pilihsort;

    do{
        cout << "\n=== MENU ADMIN ===\n";
        cout << "1. Tambah Film\n";
        cout << "2. Lihat Film\n";
        cout << "3. Edit Film\n";
        cout << "4. Hapus Film\n";
        cout << "5. Logout\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch(pilihan){
            case 1:
                tambah_film();
                break;
            case 2:
                load_data_film ();
				cout << "1.Ascending" <<endl;
				cout << "2.Descending" << endl;
				cout << "pilih: " ;
				cin >> pilihsort;
				if (pilihsort == 1) {
                    pilihsort = 3;
					bubble_sort(pilihsort);
                    tampil_film();
                } else if (pilihsort == 2) {
                    pilihsort = 3;
                    quickSort(pilihsort, head, getTail(head));
                    tampil_film();
                } else {
                    cout << "Pilihan tidak valid";
                }
                break;
            case 3:
                edit_film();
                break;
            case 4:
                hapus_film();
                break;
            case 5:
                cout << "Logout berhasil!\n";
                exit(0);
            default:
                cout << "Pilihan tidak valid!\n";
        }

        next_menu("selanjutnya");

    } while(pilihan != 5 || pilihan < 1 || pilihan > 5);
}

int main(){
    string login_as;
    char punya_akun;
    
    // pilih sebagai user atau admin
    do{
        cout << "----------------" << endl;
        cout << "- HELLO FELLAS -" << endl;
        cout << "----------------" << endl;
        cout << "Silakan buat akun dulu!" << endl;
        cout << "Sign up as User(1) | Admin(2)" << endl;
        cout << "Pilihan : ";
        cin >> login_as;
        cout << endl;
    } while (login_as != "1" && login_as != "2");
    
    // menu sesuai pilihan karakter
    if(login_as == "1"){ 
        
    // INI LAMAN UNTUK USER
        cout << "Apakah sudah punya akun ? (y/n) : ";
        cin >> punya_akun;
        punya_akun = toupper(punya_akun);

        // kalau blm punya akun
        if(punya_akun == 'N'){
            sign_up_user();
        }

        // validasi menuju login
        next_menu("login");

        // login
        login_user();

        cout << "WELKAM, " << input_username;
        menu_user();
    } else if (login_as == "2"){

        // INI LAMAN UNTUK ADMIN 
        cout << "Apakah sudah punya akun ? (y/n) : ";
        cin >> punya_akun;
        punya_akun = toupper(punya_akun);

        // kalau blm punya akun
        if(punya_akun == 'N'){
            sign_up_admin();
        }

        // validasi menuju menu login
        next_menu("login");

        // login
        login_admin();
        
        cout << "WELKAM, " << input_username;
        menu_admin();
    }
}
