#include <iostream>
#include <stdio.h>
#include <stdlib.h>
// #include "main.cpp";
using namespace std;

struct film{
    string judul_film;
    string genre_film;
    float rating_film;
    film *next_address;
};

film *head_film = NULL;

string judul[]{
    "The Avengers",
    "Avengers: Age of Ultron",
    "Avengers: Infinity War",
    "Avengers: Endgame",
    "Iron Man",
    "Captain America: The First Avenger",
    "Thor",
    "Captain America: Civil War",
    "Black Panther",
    "Spider-Man: Homecoming"
};

string genre[]{
    "Action/Sci-Fi",
    "Action/Sci-Fi",
    "Action/Sci-Fi",
    "Action/Sci-Fi",
    "Action/Sci-Fi",
    "Action/Adventure",
    "Action/Fantasy",
    "Action/Drama",
    "Action/Adventure",
    "Action/Adventure"
};

float rating[]{
    8.0,
    7.3,
    8.4,
    8.4,
    7.9,
    6.9,
    7.0,
    7.8,
    7.3,
    7.4
};

void data_awal_film(string judul[], string genre[], float rating[]){
    for(int i = 0; i < 10; i++){
        film *input = new film;

        input->judul_film = judul[i]; 
        input->genre_film = genre[i]; 
        input->rating_film = rating[i];
        input->next_address = NULL;

        if(head_film == NULL){
            head_film = input;
        } else {
            film *temp = head_film;

            while(temp->next_address != NULL){
                temp = temp->next_address;
            }

            temp->next_address = input;
        }
    }
}

void tampil_data_film(){
    film *temp = head_film;

    if(temp == NULL){
        cout << "Belum ada data film yang terdaftar" << endl;
        return;
    }

    int i = 0;
    while(temp != NULL){
        cout << "Data film ke-" << i+1 << endl << "----------" << endl;
        cout << "judul : " << temp->judul_film << endl;
        cout << "genre : " << temp->genre_film << endl;
        cout << "rating : " << temp->rating_film << endl;
        cout << endl;
        temp = temp->next_address;
        i++;
    }
}

void hapus_data_film(string hapus){
    film *temp = head_film;
    film *prev = NULL;

    // bool find = false;

    if(temp == NULL){
        cout << "data kosong" << endl;
        return;
    }

    if(temp->judul_film == hapus){
        head_film = temp->next_address;
        delete temp;
        cout << "berhasil dihapus";
        // find = true;
        return;
        
    }

    while(temp->next_address != NULL && temp->judul_film != hapus){
        prev = temp;
        temp = temp->next_address;
    }

    if(temp == NULL){
        cout << "tidak ditemukan" << endl;
        return;
    }

    prev->next_address = temp->next_address;
    delete temp;

    cout << "berhasil dihapus" << endl;

}

int main(){
    string hapus;

    // coba nampilin data
    cout << endl;
    data_awal_film(judul, genre, rating);
    tampil_data_film();

    // cin.ignore();
    cout << "masukkan nomo data yang ingin di hapus : ";
    getline(cin, hapus);
    
    hapus_data_film(hapus);

    cout << endl;
    cout << "Hasil hapus : " << endl;
    tampil_data_film();

    
}