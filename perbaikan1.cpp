#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <limits>
using namespace std;

// ================= USER =================
struct akun_user{
    string username;
    string password;
    akun_user *next;
};
akun_user *head_user = NULL;

// ================= ADMIN =================
struct akun_admin{
    string username;
    string password;
    akun_admin *next;
};
akun_admin *head_admin = NULL;

// ================= MOVIE =================
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

string input_username, input_password, login_as;
int jumlah_data_film;

// ================= UTIL =================
void next_menu(string nama_menu){
    char next;
    do {
        cout << "Lanjut ke " << nama_menu << "? (Y/N): ";
        cin >> next;
        next = toupper(next);
    } while (next != 'Y' && next != 'N');

    if (next == 'N'){
        cout << "TERIMA KASIH\n";
        exit(0);
    }
}

// ================= FILE SAVE =================
void save_all_movie(){
    FILE *file = fopen("movie.txt", "w");
    Node *temp = head;

    while(temp != NULL){
        fprintf(file, "%d|%s|%s|%.1f\n",
            temp->data.id,
            temp->data.judul.c_str(),
            temp->data.genre.c_str(),
            temp->data.rating);
        temp = temp->next;
    }
    fclose(file);
}

// ================= HITUNG =================
void hitung_jumlah_film(){
    jumlah_data_film = 0;
    FILE *f = fopen("movie.txt", "r");

    if(f == NULL) return;

    int id; char judul[100], genre[100]; float rating;
    while(fscanf(f, "%d|%[^|]|%[^|]|%f\n", &id, judul, genre, &rating) != EOF){
        jumlah_data_film++;
    }
    fclose(f);
}

// ================= LOAD =================
void load_data_film(){
    FILE *f = fopen("movie.txt", "r");
    if(f == NULL) return;

    head = tail = NULL;

    int id; char judul[100], genre[100]; float rating;

    while(fscanf(f, "%d|%[^|]|%[^|]|%f\n", &id, judul, genre, &rating) != EOF){
        Node *baru = new Node;

        baru->data.id = id;
        baru->data.judul = judul;
        baru->data.genre = genre;
        baru->data.rating = rating;
        baru->next = NULL;
        baru->prev = NULL;

        if(head == NULL){
            head = tail = baru;
        } else {
            baru->prev = tail;
            tail->next = baru;
            tail = baru;
        }
    }
    fclose(f);
}

// ================= TAMBAH =================
void tambah_film(){
    int n;
    hitung_jumlah_film();

    cout << "Jumlah film: ";
    cin >> n;

    for(int i=0;i<n;i++){
        Node *baru = new Node;

        baru->data.id = jumlah_data_film + i + 1;
        cout << "Judul: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, baru->data.judul);

        cout << "Genre: ";
        cin >> baru->data.genre;

        cout << "Rating: ";
        cin >> baru->data.rating;

        baru->next = NULL;
        baru->prev = tail;

        if(head == NULL) head = baru;
        else tail->next = baru;

        tail = baru;

        FILE *f = fopen("movie.txt", "a");
        fprintf(f,"%d|%s|%s|%.1f\n",
            baru->data.id,
            baru->data.judul.c_str(),
            baru->data.genre.c_str(),
            baru->data.rating);
        fclose(f);
    }
}

// ================= TAMPIL =================
void tampil_film(){
    Node *temp = head;

    cout << "\nID  | JUDUL | GENRE | RATING\n";

    while(temp != NULL){
        cout << temp->data.id << " | "
             << temp->data.judul << " | "
             << temp->data.genre << " | "
             << temp->data.rating << endl;
        temp = temp->next;
    }
}

// ================= SORT =================
void bubble_sort(){
    for(Node *i=head;i;i=i->next){
        for(Node *j=i->next;j;j=j->next){
            if(i->data.rating > j->data.rating){
                swap(i->data, j->data);
            }
        }
    }
}

// ================= EDIT =================
void edit_film(){
    int id;
    cout << "ID edit: ";
    cin >> id;

    Node *temp = head;
    while(temp){
        if(temp->data.id == id){
            cout << "Judul baru: ";
            cin >> temp->data.judul;
            cout << "Genre baru: ";
            cin >> temp->data.genre;
            cout << "Rating baru: ";
            cin >> temp->data.rating;
            save_all_movie();
            return;
        }
        temp = temp->next;
    }
}

// ================= HAPUS =================
void hapus_film(){
    int id;
    cout << "ID hapus: ";
    cin >> id;

    Node *temp = head;

    while(temp && temp->data.id != id){
        temp = temp->next;
    }

    if(!temp) return;

    if(temp->prev) temp->prev->next = temp->next;
    else head = temp->next;

    if(temp->next) temp->next->prev = temp->prev;
    else tail = temp->prev;

    delete temp;
    save_all_movie();
}

// ================= WATCHLIST =================
void tampil_watchlist(){
    FILE *f = fopen("watchlist.txt","r");
    if(f==NULL){ cout<<"Kosong\n"; return;}

    int id; char judul[100], genre[100]; float rating;
    while(fscanf(f,"%d|%[^|]|%[^|]|%f\n",&id,judul,genre,&rating)!=EOF){
        cout<<id<<" "<<judul<<" "<<genre<<" "<<rating<<endl;
    }
    fclose(f);
}

void add_watchlist(int id){
    Node *temp = head;

    while(temp){
        if(temp->data.id == id){
            FILE *f = fopen("watchlist.txt","a");
            fprintf(f,"%d|%s|%s|%.1f\n",
                temp->data.id,
                temp->data.judul.c_str(),
                temp->data.genre.c_str(),
                temp->data.rating);
            fclose(f);
            cout<<"Masuk watchlist\n";
            return;
        }
        temp = temp->next;
    }
    cout<<"ID tidak ada\n";
}

// ================= MENU =================
void menu_admin(){
    int p;
    do{
        cout<<"\n1.Tambah 2.Lihat 3.Edit 4.Hapus 5.Keluar\n";
        cin>>p;

        if(p==1) tambah_film();
        else if(p==2){ load_data_film(); bubble_sort(); tampil_film();}
        else if(p==3) edit_film();
        else if(p==4) hapus_film();

    }while(p!=5);
}

void menu_user(){
    int p;
    do{
        cout<<"\n1.Lihat Film 2.Watchlist 3.Keluar\n";
        cin>>p;

        if(p==1){
            load_data_film();
            tampil_film();
        }
        else if(p==2){
            int id;
            tampil_film();
            cout<<"ID pilih: ";
            cin>>id;
            add_watchlist(id);
        }

    }while(p!=3);
}

// ================= MAIN =================
int main(){
    int pilih;
    cout<<"1.User 2.Admin: ";
    cin>>pilih;

    if(pilih==1) menu_user();
    else menu_admin();
}
