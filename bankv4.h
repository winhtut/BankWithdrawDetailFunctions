//
// Created by National Cyber City on 2/18/2023.
//

#ifndef ONLINEBANKPJ_ONLINEBANK_H
#define ONLINEBANKPJ_ONLINEBANK_H
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#define AAA 19
//#include "user_setting.h"
#define USERSIZE 1000
#define DATA_COUNT 20

//Global Variable

int G_index=0; // for user counting
int email_found = -1; // for checking email exist
int space_array[DATA_COUNT];
int email_valid=-1;
int nrc_valid=-1;
int two_charArray=-1;
int strong_pass_valid=-1;
int phone_valid=-1;
int eKey_valid=-1;
int reKey_valid=-1;
int phone_found=-1;
unsigned int trans_limit=0;

char int_to_charArray[50];

//for amount and time
unsigned int last_amount=0;
unsigned int last_time=0;
unsigned int last_hour=0;

int transaction_pass=-1;
unsigned int transaction_amount_over=0;

unsigned int to_transfer_money=0;


char month[3];
char day[2];
char year[4];
char money[10];

// End of Global Variables

//function declaration
int check_input(char input[2]);
void rEgister();
void login();
int char_counting(char my_char[50]);
void loading_from_file();
void main_menu();
void space_counter();
void printing_all_data();
void email_validation(char to_check[50]);
void email_exist_checking(char email[50]);
void compare_two_charArray(char first[200],char second[200]);
void nrc_validation(char nrc[20]);
void strong_pass_validation(char pass[50]);
void phone_validation(unsigned int phone);
void encryption_key_validation(char eKey[30]);
void recovery_key_validation(char reKey[30]);
void copy_two_char_array(char receiver[200] ,char transmitter[200] );
void user_sector();
void transfer_money();
void phone_number_finding(unsigned int to_find_ph);
void money_transaction(int transmit , int receiver , unsigned int amount);
void printing_specific_data(int user);
void user_withdraw();
void get_time();
void transacitonRecord(int userDBIndex,int uFound,char who);
void get_amount(int user_index);
void get_amount_limit_and_time(int user_index);
unsigned int get_current_time_toCalculate();
unsigned int get_current_hour_toCalculate();
void time_class_last_record(int user_index);
void recording_all_data_to_file();
int total_money_for_same_days(int transmit,int last_day);


void time_class(int user_index);
void time_class_get_date(char last_record[] );


void integer_to_charArrayFun(unsigned int integer);
unsigned int char_to_integer_fun(char char_array[50]);
void calculate_time_dif(char last__month[3],unsigned int last__day,unsigned int last__year,unsigned int last__money,unsigned int limit_amount);


struct trans{
    char note[200];
};
struct info{

    unsigned int id;
    char name[50];
    char nrc[20];
    char email[50];
    char password[50];
    unsigned int phoneNumber;
    char encryption_key[6];//>>
    char recovery_key[10];//>>
    char account_status[10]; //$
    int account_type; //1 personal ,2 business , 3 othersss...... //$
    int account_level;// 1 normal 2 inter 3 high boss
    int minimum_opening_deposit;//$
    char currency[5];//>>
    unsigned long long int current_amount;//llu//>>
    char loanStatus[1];//$
    unsigned int monthly_income;//>>
    unsigned int loan_amount;//$
    float loan_rate;//$
    char address[100];//>>
    int trans_amount_limit_perday;

    struct trans tr[300]; //transaction//>>

    // %u%s%s%s%s%u%s%s%s%d%d%d%s%llu%s%u%u%f%s


};

struct info db[USERSIZE];



struct currentTime{

    char curTime[25];
};
struct currentTime getCTime[1];






void main_menu(){

    char input[2];
    printf("Welcome to our OnlineBank-NCC!\n");
    printf("Press 1 to Login!\nPress 2 to Register!\nPress 3 to Exit!>>:");
    scanf(" %[^\n]",&input[0]);

    int option = check_input(input);
    if(option == 49){
        login();
    }else if(option == 50){
        rEgister();
    } else if(option ==51){
        recording_all_data_to_file();
        printf("Good Bye!\n");
        exit(2);
    } else{
        main_menu();
    }

}
//ascii value 0=48 , 9=57
int check_input(char input[2]){
    if( input[0]>=49 &&input[0]<= 57 && input[1]=='\0'){
        return input[0];
    } else{
        return -1;
    }
}

void login(){
    char l_email[50];
    char l_pass[50];
    email_found=-1;
    two_charArray=-1;
    while (email_found == -1 || two_charArray==-1) {
        printf("This is Online Bank Login!\n");
        printf("Enter your email to login!>>:");
        scanf(" %[^\n]", &l_email[0]);
        printf("Enter your password to login!>>:");
        scanf(" %[^\n]", &l_pass[0]);

        email_exist_checking(l_email);
        compare_two_charArray(db[email_found].password,l_pass);

        if(email_found == -1 || two_charArray==-1){
            email_found=-1;
            two_charArray=-1;
            printf("Your Login credential incorrect!\n");
        }

    }


    user_sector();


}

void user_sector(){
    printf("Welcome Mr/s : %s\n",db[email_found].name);
    printf("Your Current Amount : %llu\n",db[email_found].current_amount);
    char user_option[2];

    printf("Press 1 To Transfer Money:\nPress 2 to Withdraw :\n");
    printf("Press 3 To Cash In:\nPress 4 to get your Transaction Record :\n");
    printf("Press 5 To Loan:\nPress 6 to get Main Menu:\n");
    printf("Press 7 To Exit:\nEnter your option:");
    scanf(" %[^\n]",&user_option[0]);

    int option = check_input(user_option);

    if(option == 49){
        transfer_money();
    } else if(option==50){
        user_withdraw();

    } else if(option==55){
        recording_all_data_to_file();
        main_menu();
    }


}

void rEgister(){

    char re_email[50];
    char re_name[50];
    char re_nrc[20];
    char re_pass[50];
    unsigned int re_phone=0;
    char re_encrypt_key[30];
    char re_recovery_key[30];
    char re_currency[5];
    unsigned long long int re_current_amount=0;
    unsigned int re_monthly_income=0;
    char re_address[100];
    char re_note[200];
    printf("This is Online Bank Register !\n");
    email_valid=-1;
    while (email_valid==-1) {
        printf("Enter your email to register>>:");
        scanf(" %[^\n]", &re_email[0]);


        email_validation(re_email);
        if (email_valid == -1) {
            printf("Your email format was not valid\n");
        }
    }
    printf("Your email form was valid:\n");
    email_found=-1;
    email_exist_checking(re_email);
    if( email_found !=-1 ){
        printf("Your email was already register:\n");
        rEgister();
    } else{
        printf(" Del re_email %s\n",re_email);
        printf("Your email was saved:\n");
        printf("Enter your username:\n");
        scanf(" %[^\n]",&re_name[0]);
        nrc_valid=-1;

        while (nrc_valid==-1){

            printf("Enter your NRC information:");
            scanf(" %[^\n]",&re_nrc[0]);

            nrc_validation(re_nrc);

            if(nrc_valid==-1){
                printf("Your NRC Format was incorrect!\n");
            }
        }
        printf("[+]Your NRC format was correct:\n");
        printf(" del re_nrc test: %s",re_nrc);
        strong_pass_valid=-1;
        while (strong_pass_valid==-1){

            printf("Enter your password:");
            scanf(" %[^\n]",&re_pass[0]);

            strong_pass_validation(re_pass);

            if(strong_pass_valid==-1){

                printf("[-]Your password format too weak and Try Again!\n");
            }

        }

        printf("[+]Your password format was correct and was saved!\n");
        phone_valid=-1;
        while (phone_valid==-1){
            printf("[X]Enter your Phone Number:");
            scanf("%u",&re_phone);

            phone_validation(re_phone);

            if(phone_valid == -1){

                printf("[-]Your phone number is already registered:\n");
            }

        }

        printf("[+] Your phone is correct and saved!\n");

        while (eKey_valid==-1){
            printf("[X]Enter your Encryption Key(from 4 to 6 char):");
            scanf(" %[^\n]",&re_encrypt_key[0]);
            encryption_key_validation(re_encrypt_key);

            if(eKey_valid==-1){
                printf("[-]Your Encryption Key do not correspond with our pattern:\n");
            }

        }
        printf("[+]Your Encryption key valid and saved!\n");
        while (reKey_valid==-1){

            printf("[X]Enter your Recover Key carefully:");
            scanf(" %[^\n]",&re_recovery_key[0]);

            recovery_key_validation(re_recovery_key);

            if(reKey_valid==-1){

                printf("[-]Your recovery Key do not correspond with our pattern:\n");
            }
        }
        printf("[+]Your recover key was saved!\n");

        printf("[X]Enter your currency to use:");
        scanf(" %[^\n]",&re_currency[0]);
        printf("[X]Enter your amount:");
        scanf(" %llu",&re_current_amount);
        printf("[X]Enter your monthly income:");
        scanf(" %u",&re_monthly_income);
        printf("[X]Enter your address:");
        scanf(" %[^\n]",&re_address[0]);
        printf("[X]Enter your opening note:");
        scanf(" %[^\n]",&re_note[0]);
        db[G_index].id = G_index+1;

        copy_two_char_array(db[G_index].email,re_email);
        printf("del re_email %s\n",db[G_index].email);
        copy_two_char_array(db[G_index].nrc,re_nrc);
        copy_two_char_array(db[G_index].name,re_name);

        copy_two_char_array(db[G_index].password,re_pass);
        db[G_index].phoneNumber = re_phone;

        copy_two_char_array(db[G_index].encryption_key,re_encrypt_key);
        copy_two_char_array(db[G_index].recovery_key,re_recovery_key);

        copy_two_char_array(db[G_index].currency,re_currency);
        db[G_index].current_amount = re_current_amount;

        db[G_index].monthly_income = re_monthly_income;

        copy_two_char_array(db[G_index].address,re_address);
        copy_two_char_array(db[G_index].tr[0].note , re_note);



        copy_two_char_array(db[G_index].account_status,db[2].account_status);
        db[G_index].account_level=db[2].account_level;
        db[G_index].account_type = db[2].account_type;
        db[G_index].minimum_opening_deposit=db[2].minimum_opening_deposit;
        copy_two_char_array(db[G_index].loanStatus,db[2].loanStatus);
        db[G_index].loan_amount = db[2].loan_amount;
        db[G_index].loan_rate = db[2].loan_rate;
        db[G_index].trans_amount_limit_perday = db[2].trans_amount_limit_perday;

        space_array[G_index]=20;
        G_index++;


        printing_all_data();
        printf("[X] Registration Success: Mr/s: %s\n",re_name);
        main_menu();


    }

}



void printing_specific_data(int user){

    printf("%u-%s-%s-%s-%s-%u-%s-%s-%s-%d-%d-%d-%s-%llu-%s-%u-%u-%f-%s", db[user].id, db[user].name, db[user].nrc,
           db[user].email, db[user].password, db[user].phoneNumber, db[user].encryption_key, db[user].recovery_key,
           db[user].account_status, db[user].account_type, db[user].account_level, db[user].minimum_opening_deposit,
           db[user].currency, db[user].current_amount, db[user].loanStatus, db[user].monthly_income,
           db[user].loan_amount, db[user].loan_rate, db[user].address,db[user].trans_amount_limit_perday);
    for (int gcc = 0; gcc <= space_array[user] - 20; gcc++) {
        printf("-%s", db[user].tr[gcc].note);
    }
    printf("\n");

}

void recovery_key_validation(char reKey[30]){
    int reKey_couunter = char_counting(reKey);

    if(reKey_couunter >=6 && reKey_couunter<=10){
        reKey_valid=1;
    }


}

void encryption_key_validation(char eKey[30]){

    int eKey_counter = char_counting(eKey);

    if( eKey_counter >=4 && eKey_counter<=6){
        eKey_valid=1;
    }


}

void phone_validation(unsigned int phone){
    int phone_counter=0;
    for(int i=0; i<G_index ; i++){

        if(phone != db[i].phoneNumber){

            phone_counter++;
        } else{
            phone_valid=-1;
            break;
        }

    }
    if(phone_counter == G_index){
        phone_valid=1;
    }

}
void strong_pass_validation(char pass[50]){

    int i=0;
    int special=0;
    int number=0;
    int smallChar=0;
    int capChar=0;


    int pass_counter = char_counting(pass);

    if(pass_counter >=6) {

        while (strong_pass_valid == -1) {
            if( i == pass_counter){
                strong_pass_valid=-1;
                break;
            }
            if(pass[i] >=33 && pass[i]<=42){
                special++;
            } else if( pass[i] >=48 && pass[i]<=57){
                number++;
            } else if( pass[i]>=97 && pass[i]<=122){
                smallChar++;
            } else if(pass[i]>=65 && pass[i]<=90){
                capChar++;
            }
            i++;
            if(special>0 && number>0 && capChar >0 && smallChar>0){
                strong_pass_valid=1;
            }

        }
    } else{
        printf("[-]we need at least 6 characters!\n");
        strong_pass_valid=-1;
    }


}

void nrc_validation(char nrc[20]){

    int nrc_counter = char_counting(nrc);

    for(int i=0; i<3; i++){

        two_charArray=-1;
        compare_two_charArray(nrc,db[i].nrc);
        if(two_charArray ==1){
            nrc_valid=1;
            break;
        }


    }

}

void compare_two_charArray(char first[200],char second[200]){

    int first_counter = char_counting(first);
    int second_counter = char_counting(second);

    int same_counter=0;

    if(first_counter == second_counter){

        for(register int i=0; i<first_counter; i++){

            if(first[i] != second[i]){
                break;
            }
            same_counter++;
        }

        if(first_counter == same_counter){
            two_charArray = 1;

        }

    }


}
void email_validation(char to_check[50]){

    int space=1;
    int format=1;
    char valid_form[10]={'@','g','m','a','i','l','.','c','o','m'};
    int check_counter = char_counting(to_check);

    int front_counter = check_counter-10;

    for(int i=0; i<front_counter ; i++){
        if(to_check[i]==' '){
            space=-1;
            break;
        }
    }
    for(int f=0; f<10; f++){
        if(to_check[front_counter] != valid_form[f]){
            format = -1;
            break;
        }
        front_counter++;
    }

    if(space == 1 && format==1){
        email_valid=1;
    }
}

void email_exist_checking(char email[50]){
    int counter = char_counting(email);

    int same_counting=0;
    for(register int gcc=0; gcc<G_index ; gcc++){
        int db_email_count = char_counting(db[gcc].email);

        if(counter == db_email_count){

            for(register int a=0; a<counter ; a++){
                if( email[a] !=db[gcc].email[a]){
                    break;
                }
                same_counting++;
            }
        }

        if(counter== same_counting){
            email_found=gcc;
            break;
        }


    }


}

int char_counting(char my_char[50]){

    int count=0;
    for(register int a=0; a<50; a++){

        if(my_char[a]  == '\0') {
            break;
        }
        count++;
    }

    return count;

}




void space_counter(){

    FILE *fptr = fopen("encrypted_data.txt","r");

    if(fptr != NULL){

        char c = fgetc(fptr);
        int index=0;

        while (!feof(fptr)){

            if(c !='\n'){
                if(c == ' '){
                    space_array[index] +=1;
                }
                c = fgetc(fptr);
            } else{

                index++;
                c = fgetc(fptr);
            }

        }


    } else{
        printf("\nFile opening error at space_counter function!\n");
    }

    for(int i=0; i<DATA_COUNT ; i++){

        printf(" %d",space_array[i]);
    }
    printf("\n");

}

void copy_two_char_array(char receiver[200] ,char transmitter[200] ){


//    for(register int i=0; i<200; i++){
//        receiver[i]='\0';
//    }

    int transmit_counter =char_counting(transmitter);
    for(int i=0; i<transmit_counter; i++){

        receiver[i] = transmitter[i];
    }

}

//user option
void transfer_money(){

    unsigned int amount_toTrans=0;
    unsigned int receiver_phone=0;
    char trans_pass[50];
    phone_found=-1;
    while (phone_found==-1) {
        printf("Enter receiver phone number>>:");
        scanf("%u", &receiver_phone);
        phone_number_finding(receiver_phone);

        if(phone_found==-1){
            printf("This is phone number is Not found in our bank\n");
        }

    }
    while (1) {
        printf(" Enter amount to send for %s :  %s >>:", db[phone_found].name, db[phone_found].email);
        scanf("%u", &amount_toTrans);
        //write here transaction limit per day

        if(amount_toTrans < db[email_found].current_amount-1000){
            break;
        }
    }
    two_charArray=-1;
    int wrong_counter=0;
    while (two_charArray==-1){
        printf("Your current amount %llu\nTransfer amount %u :\n",db[email_found].current_amount,amount_toTrans);
        printf("Enter your password to confirm for transaction>>:");
        scanf(" %[^\n]",&trans_pass[0]);

        compare_two_charArray(db[email_found].password,trans_pass);
        if(two_charArray==-1){
            wrong_counter++;
            if(wrong_counter==3){
                transfer_money();
                break;
            }
        }
    }
    // write transfer amount limit here
    //get_amount(email_found);
    //trans_limit
    //get_amount_limit_and_time(email_found);
    //last_amount , last_time , last_hours
    //unsigned int current_hour = get_current_hour_toCalculate();

    //if(last_hour!=current_hour){
    money_transaction(email_found,phone_found,amount_toTrans);
//    } else {
//        unsigned int current_minute = get_current_time_toCalculate();
//        unsigned int time_different = current_minute - last_time;
//        if (time_different > 3) {
//            money_transaction(email_found, phone_found, amount_toTrans);
//        } else {
//            if (last_amount + amount_toTrans > trans_limit) {
//                printf("Your daily limit was over:\n\n");
//                transfer_money();
//            }
//
//        }
//    }

}

void user_withdraw(){
    char with_pass[50];
    unsigned int withdraw_amount=0;
    printf("Your current amount: %s : %llu\n",db[email_found].name , db[email_found].current_amount);
    printf("Enter amount to withdraw>>:");
    scanf("%u",&withdraw_amount);

    if(withdraw_amount<db[email_found].current_amount-1000){
        printf("Enter your password to proceed withdraw>>:");
        scanf(" %[^\n]",&with_pass[0]);
        two_charArray=-1;
        compare_two_charArray(db[email_found].password , with_pass);
        if(two_charArray==1){
            printf("Get your withdraw amount: %u\n",withdraw_amount);
            printf("Your current amount: %llu\n",db[email_found].current_amount-withdraw_amount);
            user_sector();
        } else{
            printf("[-]Wrong credential:\n");
            user_withdraw();
        }
    } else{
        printf("Insufficient Balance:\n");
        user_withdraw();
    }

}

struct my_month{
    char str_month[3];
};
struct my_month _month[1];
void money_transaction(int transmit , int receiver , unsigned int amount){// amount is to transfer
    //before data

    time_class_last_record(transmit);
    unsigned int last_day = char_to_integer_fun(day);
    unsigned int last_year = char_to_integer_fun(year);
    unsigned int last_money = char_to_integer_fun(money);
    copy_two_char_array(_month[0].str_month,month);

    //
    /*To calculate transaction record for all same days....battery30% */


    int total_amount_tranferred = total_money_for_same_days(transmit,last_day);
    total_amount_tranferred = total_amount_tranferred+amount;



    //
    printf("\n\n After copy two char array %s\n",_month[0].str_month);
    get_amount(transmit);// to get trans amount limit per pay
    to_transfer_money=total_amount_tranferred;
    // after data
    get_time();
    time_class_get_date(getCTime[0].curTime);
    calculate_time_dif(_month[0].str_month,last_day,last_year,last_money,trans_limit);

    if(transaction_pass==1){
        db[transmit].current_amount= db[transmit].current_amount-amount;
        db[receiver].current_amount = db[receiver].current_amount+amount;
        //for insert amount to transaction record will get character array;
        integer_to_charArrayFun(amount);

        transacitonRecord(transmit,receiver,'t');
        transacitonRecord(transmit,receiver,'r');
        printf("Transaction complete:\n");
        printf("Your current amount: %s : %llu\n",db[transmit].name , db[transmit].current_amount);
        printing_specific_data(transmit);
        printf("\n\n");
        printing_all_data();
        user_sector();
    } else{

        printf("\nYou are exceeded over your limit %d:\n",transaction_amount_over);
        transfer_money();
    }

}

void phone_number_finding(unsigned int to_find_ph){

    for(int i=0; i<G_index; i++){

        if(to_find_ph == db[i].phoneNumber){
            phone_found=i;
            break;
        }
    }

}

void get_time(){
    time_t tm;
    time(&tm);
    int time_space_counter=0;

    printf("Current Date/Time = %s", ctime(&tm));


    FILE *fptr= fopen("mytime.txt","w");
    fprintf(fptr,"%s", ctime(&tm));
    int index=0;
    getCTime[0].curTime[index]='-';
    index++;
    fclose(fptr);
    FILE *rFptr = fopen("mytime.txt","r");
    char c = fgetc(rFptr);
    while (!feof(rFptr)){
        if(c ==' '){
            time_space_counter++;

            if(time_space_counter==4){
                getCTime[0].curTime[index]='@';
                c = fgetc(rFptr);
                index++;
            } else if(time_space_counter==1){
                getCTime[0].curTime[index]='!';
                c = fgetc(rFptr);
                index++;
            }
            else {
                getCTime[0].curTime[index] = '-';
                c = fgetc(rFptr);
                index++;
            }

        } else{
            getCTime[0].curTime[index] = c;
            c = fgetc(fptr);
            index++;

        }

    }


}


void transacitonRecord(int userDBIndex,int uFound,char who){
    int transfer = char_counting(db[userDBIndex].name);
    int accept = char_counting(db[uFound].name);
    int amount_counter  = char_counting(int_to_charArray);


    if(who == 't') {

        char toInsert1[4] ={'F','r','o','m'};
        char toInsert2[2] ={'t','o'};
        //db[userDBIndex].transRC[spaceArray[userDBIndex]].note

        int indexPoint=0;
        for(int x=indexPoint; x<4; x++){
            db[userDBIndex].tr[space_array[userDBIndex]-AAA].note[x]=toInsert1[x];
            indexPoint++;
        }
        int nameIndex=0;
        int endPoint = indexPoint+transfer;
        for(int x=indexPoint; x<endPoint; x++){
            db[userDBIndex].tr[space_array[userDBIndex]-AAA].note[indexPoint]=db[userDBIndex].name[nameIndex];
            nameIndex++;
            indexPoint++;
        }
        nameIndex=0;
        endPoint = indexPoint+2;
        for(int x=indexPoint; x<endPoint; x++){
            db[userDBIndex].tr[space_array[userDBIndex]-AAA].note[indexPoint]=toInsert2[nameIndex];
            nameIndex++;
            indexPoint++;
        }
        nameIndex=0;
        endPoint = indexPoint+accept;
        for(int x=indexPoint; x<endPoint; x++){
            db[userDBIndex].tr[space_array[userDBIndex]-AAA].note[indexPoint]=db[uFound].name[nameIndex];
            nameIndex++;
            indexPoint++;
        }
        nameIndex=0;
        get_time();

        for(int win=endPoint; win<25+endPoint ; win++ ){

            db[userDBIndex].tr[space_array[userDBIndex]-AAA].note[win]=getCTime[0].curTime[nameIndex];
            nameIndex++;
        }
        nameIndex=0;
        db[userDBIndex].tr[space_array[userDBIndex]-AAA].note[25+endPoint]='$';
        int end= 26+endPoint+amount_counter;
        for(int amount = 26+endPoint ; amount<end ; amount++){

            db[userDBIndex].tr[space_array[userDBIndex]-AAA].note[amount] = int_to_charArray[nameIndex];
            nameIndex++;
        }
        db[userDBIndex].tr[space_array[userDBIndex]-AAA].note[end]='-';
        space_array[userDBIndex] +=1;


    } else{

        char receiveFrom[13] = {'-','R','e','c','e','i','v','e','F','r','o','m','-'};
        int indexPoint=0;
        int endpoint=0;
        int reIndex=0;
        for(int i=0;i<accept;i++){
            db[uFound].tr[space_array[uFound]-AAA].note[i]=db[uFound].name[i];
            indexPoint++;
        }
        endpoint=accept+13;
        for(int i=indexPoint;i<endpoint;i++){
            db[uFound].tr[space_array[uFound]-AAA].note[i]=receiveFrom[reIndex];
            reIndex++;

        }
        reIndex=0;
        int toendpoint=endpoint+transfer;
        for(int i=endpoint;i<toendpoint;i++){
            db[uFound].tr[space_array[uFound]-AAA].note[i]=db[userDBIndex].name[reIndex];
            reIndex++;
        }

        reIndex=0;
        get_time();
        for(int win=toendpoint; win<25+toendpoint ; win++ ){

            db[uFound].tr[space_array[uFound]-AAA].note[win]=getCTime[0].curTime[reIndex];
            reIndex++;
        }
        reIndex=0;
        db[uFound].tr[space_array[uFound]-AAA].note[25+toendpoint]='$';
        for(int amount = 26+toendpoint ; amount<26+toendpoint+amount_counter ; amount++){

            db[uFound].tr[space_array[uFound]-AAA].note[amount] = int_to_charArray[reIndex];
            reIndex++;
        }

        db[uFound].tr[space_array[uFound]-AAA].note[26+toendpoint+amount_counter]='-';
        space_array[uFound] +=1;

    }

}

void get_amount(int user_index){

    int p_or_b = db[user_index].account_type;
    int acc_level = db[user_index].account_level;

    switch (p_or_b) {
        case 1:
            if(acc_level==1){
                trans_limit=5000;
            } else if(acc_level==2){
                trans_limit=20000;
            } else{
                trans_limit = 50000;
            }
            break;

        case 2:
            if(acc_level==1){
                trans_limit=50000;
            } else if(acc_level==2){
                trans_limit=200000;
            } else{
                trans_limit = 500000;
            }
            break;

        case 3:
            if(acc_level==1){
                trans_limit=500000;
            } else if(acc_level==2){
                trans_limit=2000000;
            } else{
                trans_limit = 5000000;
            }
            break;
        default:
            break;
    }

}

void get_amount_limit_and_time(int user_index){
    int last=0;
    int records = space_array[user_index]-20;
    int amount_counter=0;
    int time_index_counter=0;
    char time_array[2];
    char last_hours_array[2];

    for(int i=0; i<=records; i++){

        last=i;

    }

    printf("\n last: record %s",db[user_index].tr[last].note);
    int last_record_counter =char_counting(db[user_index].tr[last].note);

    for(int aaa=0; aaa<last_record_counter ; aaa++){

        if( db[user_index].tr[last].note[aaa]=='$'){

            break;
        }
        amount_counter++;

    }

    int amount_endPoint =last_record_counter-amount_counter;

    char amount_char_array[10];

    for(int gcc=0; gcc<=amount_endPoint ; gcc++){
        amount_char_array[gcc]= db[user_index].tr[last].note[amount_counter+1];
        amount_counter++;
    }
    last_amount = char_to_integer_fun(amount_char_array);

    printf(" Last amount  %u\n",last_amount);

    // for put out from time array;
    int last_amount_counter = char_counting(amount_char_array);

    for(register int wa=0; wa<last_record_counter; wa++){

        if(db[user_index].tr[last].note[wa] == '@'){
            break;
        } else{
            time_index_counter++;
        }
    }
    last_hours_array[0]=db[user_index].tr[last].note[time_index_counter+1];
    last_hours_array[1]=db[user_index].tr[last].note[time_index_counter+2];

    last_hour = char_to_integer_fun(last_hours_array);
    int time_ = 0;
    int colon_counter=0;
    for(int i=time_index_counter+1; i<time_index_counter+6; i++){

        if(db[user_index].tr[last].note[i] == ':'){
            colon_counter++;


        } else{
            if(colon_counter==1) {
                time_array[time_] = db[user_index].tr[last].note[i];
                time_++;
                if(time_==2){
                    break;
                }
            }
        }

    }
    last_time = char_to_integer_fun(time_array);
    printf(" \nlast time in integer: %d",last_time);



}



void integer_to_charArrayFun(unsigned int integer){
    int index=0;
    FILE *fptr = fopen("whw.txt","w");
    if(fptr==NULL){
        printf("[-]Error at integer_to_charArray\n");
    } else{

        fprintf(fptr,"%d",integer);
    }
    fclose(fptr);
    FILE *fptr2 = fopen("whw.txt","r");
    char c = fgetc(fptr2);
    while (!feof(fptr2)){

        int_to_charArray[index]=c;
        c = fgetc(fptr);
        index++;
    }
    fclose(fptr2);

}

unsigned int char_to_integer_fun(char char_array[50]){

    unsigned int char_to_int_data = 0;

    FILE *fptr = fopen("whw.txt","w");
    if(fptr==NULL){
        printf("Error \n");
    } else{
        fprintf(fptr,"%s",char_array);

    }
    fclose(fptr);

    FILE *fptr2 = fopen("whw.txt","r");
    if(fptr2 == NULL){

        printf("Error\n");

    } else{

        fscanf(fptr,"%d",&char_to_int_data);
    }

    return char_to_int_data;
}


void time_class(int user_index){

    time_class_last_record(user_index);


}
void time_class_last_record(int user_index){
    int last=0;
    int records = space_array[user_index]-20;
    for(int i=0; i<=records; i++){

        last=i;

    }

    printf("\n last: record %s\n",db[user_index].tr[last].note);

    int last_record_index=char_counting(db[user_index].tr[last].note);
    char last_record[last_record_index];
    for(int ag=0; ag<last_record_index; ag++){

        last_record[ag] = db[user_index].tr[last].note[ag];
    }


    time_class_get_date(last_record);

}

void time_class_get_date(char last_record[]) {
    // to get month name , day , year

    int last_record_counter = char_counting(last_record);
    int i = 0;
    for (i = 0; i < last_record_counter; i++) {

        if (last_record[i] == '!') {
            break;
        }
    }
    i++;
    for (int a = 0; a < 3; a++) {
        month[a] = last_record[i];
        i++;
    }


    printf("\nmonth %s\n", month);
    //printf("day %c",db[user_index].tr[last].note[i]);

    day[0] = last_record[i + 1];
    day[1] = last_record[i + 2];

    unsigned int get_day = char_to_integer_fun(day);

    printf("get day: %d\n", get_day);

    // for finding year
    int z = 0;
    for (z = 0; z < last_record_counter; z++) {

        if (last_record[z] == '@') {
            break;
        }

    }

    for (int x = 0; x < 4; x++) {
        z++;
        year[x] = last_record[z];
    }
    unsigned int get_year = char_to_integer_fun(year);

    printf("year :%d\n", get_year);

    int y = 0;
    for (y = z; y < last_record_counter; y++) {

        if (last_record[y] == '$')
            break;
    }
    y++;
    int a = 0;
    int quantity_of_money = 0;
    for(int llc=0; llc<10 ; llc++){
        money[llc]='\0';
    }
    for (a = y; a < last_record_counter; a++) {

        if (last_record[a] == '-') {
            break;
        } else {
            money[quantity_of_money] = last_record[a];
            quantity_of_money++;
        }

    }

    printf("Quantity of money %d\n", quantity_of_money);

    unsigned int money_amount = char_to_integer_fun(money);
    printf("money_amount %u",money_amount);



}

void calculate_time_dif(char last__month[],unsigned int last__day,unsigned int last__year,unsigned int last__money,unsigned int limit_amount){
    unsigned int current_day=char_to_integer_fun(day);
    unsigned int current_year= char_to_integer_fun(year);
    unsigned int current_money= to_transfer_money;//golobal money
    two_charArray=-1;
    printf("\n\n\n----last month %s",last__month);
    compare_two_charArray(last__month,month);


    if(current_day==last__day && current_year ==last__year && two_charArray==1) {

        if(limit_amount<current_money+last__money){
            transaction_pass=-1;
            transaction_amount_over = limit_amount-(current_money+last__money);
            return;

        } else{
            transaction_pass=1;
            return;

        }

    } else{

        transaction_pass=1;
        return;
    }


}

void recording_all_data_to_file(){

    FILE *fptr = fopen("encrypted_data.txt","w");

    if(fptr == NULL){
        printf("[-]File opening error at recording to file function():\n");
    } else{

        for(int user=0; user<G_index; user++){

            fprintf(fptr,"%u%c%s%c%s%c%s%c%s%c%u%c%s%c%s%c%s%c%d%c%d%c%d%c%s%c%llu%c%s%c%u%c%u%c%f%c%s%c%d",db[user].id ,' ',db[user].name ,' ',db[user].nrc,' ',db[user].email,' ',db[user].password,' ',db[user].phoneNumber,' ',db[user].encryption_key,' ',db[user].recovery_key,' ',db[user].account_status,' ',db[user].account_type,' ',db[user].account_level,' ',db[user].minimum_opening_deposit,' ',db[user].currency,' ',db[user].current_amount,' ',db[user].loanStatus,' ',db[user].monthly_income,' ',db[user].loan_amount,' ',db[user].loan_rate,' ',db[user].address,' ',db[user].trans_amount_limit_perday);

            for(register int trc=0; trc<= space_array[user]-20 ; trc++ ){
                fprintf(fptr , " %s",db[user].tr[trc].note);
            }

            fprintf(fptr,"%c",'\n');
        }

    }

    printf("Recording complete to 'encrypted_data.txt!' \n");

}

void printing_all_data() {


    for (int user = 0; user < G_index; user++) {

        printf("%u-%s-%s-%s-%s-%u-%s-%s-%s-%d-%d-%d-%s-%llu-%s-%u-%u-%f-%s-%d", db[user].id, db[user].name, db[user].nrc,
               db[user].email, db[user].password, db[user].phoneNumber, db[user].encryption_key, db[user].recovery_key,
               db[user].account_status, db[user].account_type, db[user].account_level, db[user].minimum_opening_deposit,
               db[user].currency, db[user].current_amount, db[user].loanStatus, db[user].monthly_income,
               db[user].loan_amount, db[user].loan_rate, db[user].address,db[user].trans_amount_limit_perday);
        for (int gcc = 0; gcc <= space_array[user] - 20; gcc++) {
            printf("-%s", db[user].tr[gcc].note);
        }
        printf("\n");

    }
}

void loading_from_file(){

    FILE *fptr = fopen("encrypted_data.txt","r");

    if( fptr != NULL){

        for(register int user=0; user < USERSIZE ; user++){

            fscanf(fptr ,"%u%s%s%s%s%u%s%s%s%d%d%d%s%llu%s%u%u%f%s%d",&db[user].id ,&db[user].name ,&db[user].nrc,&db[user].email,&db[user].password,&db[user].phoneNumber,&db[user].encryption_key,&db[user].recovery_key,&db[user].account_status,&db[user].account_type,&db[user].account_level,&db[user].minimum_opening_deposit,&db[user].currency,&db[user].current_amount,&db[user].loanStatus,&db[user].monthly_income,&db[user].loan_amount,&db[user].loan_rate,&db[user].address,&db[user].trans_amount_limit_perday);

            for(register int trc=0; trc<= space_array[user]-20 ; trc++ ){
                fscanf(fptr , "%s",&db[user].tr[trc].note[0]);
            }
            if(db[user].id == 0){
                break;
            }
            G_index++;

        }

    } else{
        printf("File opening error at Loading form file function!\n");
    }

    fclose(fptr);

}

int total_money_for_same_days(int transmit,int last_day){

    int to_return_money=0;


    int index_counter=0;

    // to calculate temp day

    int to_get_all_records=space_array[transmit]-20;
    //printf("\n\n toal_money_for_same_day: %s\n",db[transmit].tr[to_get_all_records].note);
    // to get all records
    for(int wa=to_get_all_records-1; wa>0; wa--){
        //to calcuate temp day
        char temp_day[2];
        //to count char for current note
        int current_trans_counter =char_counting(db[transmit].tr[wa].note);

        for(int aw=0; aw<current_trans_counter; aw++){

            if(db[transmit].tr[wa].note[aw]=='!'){
                break;
            }
            index_counter++;
        }

        temp_day[0]=db[transmit].tr[wa].note[index_counter+5];
        temp_day[1]=db[transmit].tr[wa].note[index_counter+6];
        unsigned int temp_day_int=char_to_integer_fun(temp_day);
        printf("\n temp day for %d record = %d\n",wa,temp_day_int);

        if(temp_day_int!=last_day){
            break;
        } else{

            for(int m=index_counter; m<current_trans_counter; m++){

                if(db[transmit].tr[wa].note[m]=='$'){
                    break;
                }
                index_counter++;

            }
            int quantity_of_money=0;
            char current_amount_char[10];
            for(int ko=index_counter; ko<current_trans_counter; ko++){
                if(db[transmit].tr[wa].note[ko]=='-'){
                    break;
                }
                quantity_of_money++;
            }

            index_counter++;
            for(int v=0; v<quantity_of_money; v++){
                current_amount_char[v]=db[transmit].tr[wa].note[index_counter];
                index_counter++;
            }
            unsigned int amount_for_current_trans = char_to_integer_fun(current_amount_char);
            printf("Amount for current transaction: %d\n",amount_for_current_trans);
            index_counter=0;
            to_return_money = to_return_money+amount_for_current_trans;

        }


    }

    printf("\nTotal Money except last record's money for all same days: %d\n",to_return_money);
    return to_return_money;
}



#endif //ONLINEBANKPJ_ONLINEBANK_H