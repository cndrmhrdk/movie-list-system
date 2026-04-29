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
struct Movie {
    int id;
    string judul;
    string genre;
    float rating;
};

// Movie data_movie[1000];

struct Node {
    Movie data;
    Node* prev;
    Node* next;
};


Node *head = NULL;
Node *tail = NULL;

string input_username, input_password, login_as;
int jumlah_data_film;

void menu_admin(); void menu_user();

void hiasan_hahay(string judul_menu){
    cout << "---WELCOLME TO " << judul_menu << "---" << endl;
    // cout << "-------------------------" << endl;
}

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
    head_user = NULL;
    
    cout << "SILAKAN LOGIN SEBAGAI USER" << endl;
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
    
        if(head_user == NULL){
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

void list_genre(){
    cout << "Pilih Genre yang diinginkan : \n";
    cout << "1. Romance\n";
    cout << "2. Horror\n";
    cout << "3. Sci-Fi\n";
    cout << "4. Action\n";
    cout << "5. Comedy\n";
    cout << "6. Adventure\n";
    cout << "7. Music\n";
    cout << "8. Fantasy\n";
    cout << "9. Drama\n";
    cout << "10. Sports\n";
    cout << "Pilihan : ";
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

    int i = 0;
    while(fscanf(load, "%d|%[^|]|%[^|]|%f\n", &id, judul, genre, &rating) != EOF){
        Node *baru = new Node;

        // data_movie[i].id = id;
        // data_movie[i].judul = judul;
        // data_movie[i].genre = genre;
        // data_movie[i].rating = rating;

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
        
        i++;
    }
    fclose(load);
}

void hitung_jumlah_film(){
    jumlah_data_film = 0;
        
    FILE *hitung = fopen("movie.txt", "r");

    int id;
    char judul[100];
    char genre[100];
    float rating;
    
    while(fscanf(hitung, "%d|%[^|]|%[^|]|%f\n", &id, judul, genre, &rating) != EOF){
        jumlah_data_film = jumlah_data_film + 1;
    }

    fclose(hitung);
    // return jumlah_data_film;
}

Node* getTail(Node* cur){
    while(cur && cur->next != NULL){
        cur = cur->next;
    }
    return cur;
}

int cari_id_terbesar(){
    if (head == NULL){
        cout << "Data kosong" << endl;
        return 0;
    }
    
    int id_terbesar = head->data.id;
    Node *bantu = head;

    while(bantu != NULL){
        if(bantu->data.id > id_terbesar){
            id_terbesar = bantu->data.id;
        }
        bantu = bantu->next;
    }

    return id_terbesar;
}

void tambah_film(){
    // int jumlah_total_film= hitung_jumlah_film();
    int id_terbesar = cari_id_terbesar();
	int jumlahfilm;
    
	cout << "SILAKAN TAMBAHKAN FILM" <<endl;
	cout << "Ingin menambah berapa film: ";
	cin >>jumlahfilm;

	for(int i = 0; i < jumlahfilm; i++) {
        Node *baru = new Node;

        cout << "Film ke-" << id_terbesar + i + 1 <<endl;
        baru->data.id = id_terbesar + i + 1; 
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

void tampil_film(){
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

void rekomendasi_film(int pilihan_rekomendasi, float rating){
    hitung_jumlah_film();
    Node *temp = head;
    string genre_pilihan;
    // bool cek = false;
    int i = 0;

    switch(pilihan_rekomendasi){
        case 1: genre_pilihan = "Romance"; break;
        case 2: genre_pilihan = "Horror"; break;
        case 3: genre_pilihan = "Sci-Fi"; break;
        case 4: genre_pilihan = "Action"; break;
        case 5: genre_pilihan = "Comedy"; break;
        case 6: genre_pilihan = "Adventure"; break;
        case 7: genre_pilihan = "Music"; break;
        case 8: genre_pilihan = "Fantasy"; break;
        case 9: genre_pilihan = "Drama"; break;
        case 10: genre_pilihan = "Sports"; break;
        default: cout << "tidak ada di pilihan" << endl;
    }
    
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
        if (temp->data.genre == genre_pilihan && temp->data.rating >= rating){
            cout << left
            << "| " << setw(5)  << temp->data.id
            << "| " << setw(35) << temp->data.judul
            << "| " << setw(18) << temp->data.genre
            << "| " << setw(8)  << temp->data.rating
            << "|" << endl;
            cout << "---------------------------------------------------------------------------" << endl;
            i++;
        }
        temp = temp->next;
    }

    if (i == 0){
        cout << left
            << setw(14) << " " << "Maaf kami tidak punya rekomendasi yang sesuai" << endl;
        cout << "---------------------------------------------------------------------------" << endl;
    }
}

void bubble_sort(int pilihan){
    Node *i, *j;
    Movie temp;

    if (pilihan == 0){
        for(i = head; i != NULL; i = i->next){
            for(j = i->next; j != NULL; j = j->next){
                if(i->data.id > j->data.id){
                    temp = i->data;
                    i->data = j->data;
                    j->data = temp;
                }
            }
        }
    } else if (pilihan == 1){
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

    return NULL;
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

            cin.ignore(); 

            cout << "Judul baru  : ";
            getline(cin, temp->data.judul);

            cout << "Genre baru  : ";
            cin >> temp->data.genre;

            cout << "Rating baru : ";
            cin >> temp->data.rating;

        
            FILE *file = fopen("movie.txt", "w");
            Node *save = head;

            while(save != NULL){
                fprintf(file, "%d|%s|%s|%.1f\n", 
                    save->data.id,
                    save->data.judul.c_str(),
                    save->data.genre.c_str(),
                    save->data.rating);
                save = save->next;
            }

            fclose(file);

            cout << "Data berhasil diubah!\n\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Data tidak ditemukan!\n\n";
}

void hapus_film(){
    load_data_film();
    int id;

    cout << "Selamat Datang di Menu Hapus Film" << endl;
    cout << "Masukkan ID film yang ingin dihapus: ";
    cin >> id;

    Node *temp = head;

    if(temp == NULL){
        cout << "Data tidak ditemukan!\n\n";
        return;
    }

    while(temp != NULL && temp->data.id != id){
        temp = temp->next;
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

    FILE *file = fopen("movie.txt", "w");
    Node *save = head;

    while(save != NULL){
        fprintf(file, "%d|%s|%s|%.1f\n", save->data.id, save->data.judul.c_str(), save->data.genre.c_str(), save->data.rating);
        save = save->next;
    }

    fclose(file);
    
    cout << "Data berhasil dihapus!\n\n";
}

void add_watchlist(int id_film){
    hitung_jumlah_film();

    bool found= false;
    Node *baru = head;
                
    if (head == NULL){
        cout << "Gagal";
        return;
    }
    
    while (baru != NULL){
        if (baru->data.id == id_film){
            FILE *file = fopen("watchlist.txt", "a");
            fprintf(file, "%d|%s|%s|%.1f\n", 
                baru->data.id, 
                baru->data.judul.c_str(), 
                baru->data.genre.c_str(), 
                baru->data.rating);
            fclose(file);
            found = true;
            break;
        } 
        baru = baru->next;
    }

    if(id_film > (jumlah_data_film + 100)){
        cout << "YANG BENER AJE LU BANG" << endl;
    } else if (found) {
        cout << "ID Film " << id_film << " Berhasil ditambahkan" << endl;
    } else if (!found){
        cout << "ID Film " << id_film << " tidak ditemukan di list film" << endl;
    }
}

void tampil_watchlist(){
    FILE *file = fopen("watchlist.txt", "r");

    if(file == NULL){
        cout << "Watchlist masih kosong!\n";
        return;
    }

    int id;
    char judul[100], genre[100];
    float rating;

    cout << "\n=== WATCHLIST ===\n";
    cout << "===========================================================================" << endl;
    cout << left
        << "| " << setw(5)  << "ID"
        << "| " << setw(35) << "JUDUL"
        << "| " << setw(18) << "GENRE"
        << "| " << setw(8)  << "RATING"
        << "|" << endl;
    cout << "===========================================================================" << endl;

    while(fscanf(file, "%d|%[^|]|%[^|]|%f\n", &id, judul, genre, &rating) != EOF){
        cout << left
            << "| " << setw(5)  << id
            << "| " << setw(35) << judul
            << "| " << setw(18) << genre
            << "| " << setw(8)  << rating
            << "|" << endl;
        cout << "---------------------------------------------------------------------------" << endl;
    }

    fclose(file);
}

void hapus_watchlist(){
    FILE *file = fopen("watchlist.txt", "r");

    if(file == NULL){
        cout << "Watchlist masih kosong!\n";
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");

    int id_hapus;
    cout << "Masukkan ID film yang ingin dihapus dari watchlist: ";
    cin >> id_hapus;

    int id;
    char judul[100], genre[100];
    float rating;

    bool found = false;

    while(fscanf(file, "%d|%[^|]|%[^|]|%f\n", &id, judul, genre, &rating) != EOF){
        if(id != id_hapus){
            fprintf(tempFile, "%d|%s|%s|%.1f\n", id, judul, genre, rating);
        } else {
            found = true;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("watchlist.txt");
    rename("temp.txt", "watchlist.txt");

    if(found){
        cout << "Film berhasil dihapus dari watchlist!\n";
    } else {
        cout << "Film tidak ditemukan di watchlist!\n";
    }
}

void menu_user(){
    int pilihan, pilih_sort, sort_type, pilih_genre;
    float minimal_rating;

    do{
        cout << "\n=== MENU USER ===\n";
        cout << "1. List Film\n";
        cout << "2. Rekomendasi Film\n";
        cout << "3. Watchlist\n";
        cout << "4. Logout\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        system("cls");

        if(pilihan == 1){
            load_data_film();

            hiasan_hahay("LIST FILM");

            cout << "Urutkan film berdasarkan :\n";
            cout << "1. Judul\n";
            cout << "2. Genre\n";
            cout << "3. Rating\n";
            cout << "Pilihan : ";
            cin >> pilih_sort;

            cout << "\n1. Ascending\n";
            cout << "2. Descending\n";
            cout << "Pilihan : ";
            cin >> sort_type;
            
            cout << endl;

            if (sort_type == 1){
                bubble_sort(pilih_sort);
                tampil_film();
            } else if (sort_type == 2){
                quickSort(pilih_sort, head, getTail(head));
                tampil_film();
            } else {
                cout << "Pilihan tidak valid" << endl;
            }
        } else if (pilihan == 2){
            load_data_film();

            hiasan_hahay("REKOMENDASI FILM");

            list_genre();
            cin >> pilih_genre;

            cout << "Masukkan rating minimal : ";
            cin >> minimal_rating;
            
            rekomendasi_film(pilih_genre, minimal_rating);
        } else if (pilihan == 3){
            int pilih_watchlist;

            hiasan_hahay("WATCHLIST");

            do{
                cout << "\n=== MENU ===\n";
                cout << "1. Tambah ke Watchlist\n";
                cout << "2. Lihat Watchlist\n";
                cout << "3. Hapus dari Watchlist\n";
                cout << "4. Kembali\n";
                cout << "Pilihan: ";
                cin >> pilih_watchlist;

                if(pilih_watchlist == 1){
                    int tambah_watchlist, id_film;
                    
                    load_data_film();
                    tampil_film();
                    hitung_jumlah_film();

                    cout << "\nMau input berapa film ke watchlist : ";
                    cin >> tambah_watchlist;
                    cout << "Pilih ID film:\n";

                    for(int i = 0; i < tambah_watchlist; i++){
                        bool cek_duplikat = false;

                        cout << "ID Film ke-" << i + 1 << " : ";
                        cin >> id_film;

                        FILE *cek = fopen("watchlist.txt", "r");

                        if(cek != NULL){
                            int id;
                            char judul[100], genre[100];
                            float rating;

                            while(fscanf(cek, "%d|%[^|]|%[^|]|%f\n", &id, judul, genre, &rating) != EOF){
                                if(id_film == id){
                                    cek_duplikat = true;
                                    break;
                                }
                            }
                            fclose(cek);
                        }

                        if(cek_duplikat){
                            cout << "ID sudah ada di watchlist!\n";
                        } else {
                            add_watchlist(id_film);
                        }
                    }
                } else if(pilih_watchlist == 2){
                    tampil_watchlist();
                } else if(pilih_watchlist == 3){
                    tampil_watchlist();
                    hapus_watchlist();
                } else if(pilih_watchlist == 4){
                    break;
                } else {
                    cout << "Pilihan tidak valid!\n";
                }

                next_menu("selanjutnya");
                system("cls");

            } while(true);

        } else if (pilihan == 4){
            cout << "______" << endl;
            cout << "SEE YA AGAIN";
            exit(0);
        }
        
        next_menu("selanjutnya");
        system("cls");

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
                load_data_film();
                hiasan_hahay("TAMBAH FILM");
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
				load_data_film();
                hiasan_hahay("EDIT FILM");
                edit_film();
                break;
            case 4:
                hiasan_hahay("HAPUS FILM");
                hapus_film();
                break;
            case 5:
                cout << "Logout berhasil!\n";
                exit(0);
            default:
                cout << "Pilihan tidak valid!\n";
        }
        next_menu("selanjutnya");
        system("cls");
    } while(pilihan != 5 || pilihan < 1 || pilihan > 5);
}

int main(){
    char punya_akun;
    
    // pilih sebagai user atau admin
    do{
        cout << "----------------" << endl;
        cout << "- HELLO FELLAS -" << endl;
        cout << "----------------" << endl;
        cout << "Who are You? : User(1) | Admin(2)" << endl;
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
            system("cls");
        }

        // validasi menuju login
        cout << endl;
        next_menu("login");
        cout << endl;

        // login
        login_user();
        system("cls");

        cout << "WELKAM, '" << input_username << "'" << endl;
        menu_user();
    } else if (login_as == "2"){

        // INI LAMAN UNTUK ADMIN 
        cout << "Apakah sudah punya akun ? (y/n) : ";
        cin >> punya_akun;
        punya_akun = toupper(punya_akun);

        // kalau blm punya akun
        if(punya_akun == 'N'){
            sign_up_admin();
            system("cls");
        }

        // validasi menuju menu login
        cout << endl;
        next_menu("login");
        cout << endl;

        // login
        login_admin();
        system("cls");
        
        cout << "WELKAM, '" << input_username << "'" << endl;
        menu_admin();
    }
}