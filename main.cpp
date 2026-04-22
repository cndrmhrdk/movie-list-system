#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct akun_user{
    string username;
    string password;
    akun_user *next_address;
};

akun_user *head_user = NULL;

struct akun_admin{
    string username;
    string password;
    akun_admin *next_address;
};

akun_admin *head_admin = NULL;

string
    login_as,
    input_username,
    input_password
;

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

void pilih_karakter(){
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
}

void sign_up_user(){
    akun_user *baru = new akun_user;

    cout << "SIGN UP FIRST YA (AS A USER)" << endl;
    cout << "username : ";
    cin >> baru->username;
    cout << "password : ";
    cin >> baru->password;

    baru->next_address = NULL;

    if(head_user == NULL){
        head_user = baru;
    } else {
        akun_user *temp = head_user;

        while(temp->next_address != NULL){
            temp = temp->next_address;
        }

        temp->next_address = baru;
    }

    cout << "account created" << endl;
    cout << endl;
}

void sign_up_admin(){
    akun_admin *baru = new akun_admin;

    cout << "SIGN UP FIRST YA (AS A ADMIN)" << endl;
    cout << "username : ";
    cin >> baru->username;
    cout << "password : ";
    cin >> baru->password;

    baru->next_address = NULL;

    if(head_admin == NULL){
        head_admin = baru;
    } else {
        akun_admin *temp = head_admin;

        while(temp->next_address != NULL){
            temp = temp->next_address;
        }

        temp->next_address = baru;
    }

    cout << "account created" << endl << endl;
}

void login_user(){
    bool match = false;

    cout << "SILAKAN LOGIN SEBAGAI USER" << endl;
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
            temp = temp->next_address;
        }
        if (match){
            cout << "Login Success" << endl << endl;
            break;
        } else {
            cout << "Account not found, please re-login" << endl << endl;
        }

    } while (!match);
}

void login_admin(){
    bool match = false;

    cout << "SILAKAN LOGIN SEBAGAI ADMIN" << endl;
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
            temp = temp->next_address;
        }
        if (match){
            cout << "Login Success" << endl << endl;
            break;
        } else {
            cout << "Account not found, please re-login" << endl << endl;
        }

    } while (!match);
}

int main(){
    // pilih sebagai user atau admin
    pilih_karakter();
    
    // sign up sesuai pilihan karakter
    if(login_as == "1"){ 

    // INI LAMAN UNTUK USER

        // sign up
        sign_up_user();

        // validasi menuju menu login
        next_menu("login");

        // login
        login_user();

        cout << "WELKAM, " << input_username;
    } else if (login_as == "2"){
        
    // INI LAMAN UNTUK ADMIN 
        
        // sign up
        sign_up_admin();

        // validasi menuju menu login
        next_menu("login");

        // login
        login_admin();
        
        cout << "WELKAM, " << input_username;
    }
}