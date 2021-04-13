#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>

#define SIZEOFITEMLIST 100
#define SIZEOFVEHICALS 3

//main menu function
void main_menu();
//....
bool initial_salesman_details=true;
int stock_size_current=0;
//constant
const int loading_size=1500;
const bool active=true;
const bool deactive=false;
const int max_size_salesman_name=8;
const int max_vehicle_number=9999;
const int max_word_size_inventory=8;
//vehical functions...

void add_details_vehicle();
void manage_vehicle();
void vehicle_load_detail();
void vehicle_earned_amount(int,int,int);
void remove_load_details();
//............

//progress
float total_income_vehicles();
void item_progress();
void item_progress_table();
void item_sold_graph();
void salesman_progress();
int sort_item_decending(int);
int total_of_unload_amount(const int,const bool);
float total_income_an_item(int);
void progress();
//......
void login();
//inventory functions
int search(int,const int,const float,const char[],const char[]);
void datasave();
void dataload();
void view_inventory_detail();
void inventory_Menue();
void loadvehicle();
void add_item();
void stockbalance(int,int,bool);
void unloadvehicle();
void set_unload_qty_item(int,int);
bool check_ability_for_load();
//............

struct stock{
char item_brandname[20];
char item_name[20];
float item_price;
int item_qty;
int unload_qty;
}item[SIZEOFITEMLIST];

struct vehicle{
char salesman_name[20];
int vehicle_number;
int vehicle_item_list[100][2]; // 0->item no,1->item qty
int vehicle_loaded_size;
int unload_qty;
float vehicle_earned_amount;
} vehicle[SIZEOFVEHICALS];

int main(){


system("COLOR 0A");
login();
system("cls");
dataload();
main_menu();


return 0;
}
// load data from test.txt
void dataload(){

int val1,val2,count_1=0,count_2=0,j=0,count_3=0;
FILE *fp,*fp_1,*fp_2;
fp=fopen("inventory.txt","r");
fp_1=fopen("vehicleload.txt","r");
fp_2=fopen("vehicledetails.txt","r");

if(fp==NULL || fp_1==NULL || fp_2==NULL){
    printf("FILE DOESNT EXIST");
    exit(1);
}
while(fscanf(fp,"%s %s %d %f %d",item[count_1].item_brandname,item[count_1].item_name,&item[count_1].item_qty,&item[count_1].item_price,&item[count_1].unload_qty)!=EOF){
    count_1++;
}
while(fscanf(fp_1,"%d %d",&val1,&val2)!=EOF){
    if(val1==0 && val2==0 ){
    j=0;
    count_2++;
    }
    else{
        vehicle[count_2].vehicle_item_list[j][0]=val1;
        vehicle[count_2].vehicle_item_list[j][1]=val2;
        j++;
        vehicle[count_2].vehicle_loaded_size=j;
    }
}
while(fscanf(fp_2,"%d %s %d %f",&vehicle[count_3].vehicle_number,vehicle[count_3].salesman_name,&vehicle[count_3].unload_qty,&vehicle[count_3].vehicle_earned_amount)!=EOF){
    count_3++;
}
if(count_3==0){
    initial_salesman_details=false; //when system open first there are no vehicle details.therefore need initial vehicle details first.
}
fclose(fp);
fclose(fp_1);
fclose(fp_2);
stock_size_current=count_1;
}
// save data to test.txt
void datasave(){
int i,j;
FILE *fp,*fp_1,*fp_2;
fp=fopen("inventory.txt","w");
fp_1=fopen("vehicleload.txt","w");
fp_2=fopen("vehicledetails.txt","w");
if(fp==NULL || fp_1==NULL || fp_2==NULL ){
    printf("FILE DOESNT EXIST");
    exit(1);
}
for(i=0;i<stock_size_current;i++){
fprintf(fp,"%s %s %d %f %d\n",item[i].item_brandname,item[i].item_name,item[i].item_qty,item[i].item_price,item[i].unload_qty);
}
for(i=0;i<SIZEOFVEHICALS;i++){
for(j=0;j<vehicle[i].vehicle_loaded_size;j++){
fprintf(fp_1,"%d %d\n",vehicle[i].vehicle_item_list[j][0],vehicle[i].vehicle_item_list[j][1]);//print vehicle loaded details on files
}
fprintf(fp_1,"0 0\n");//break vehicle from another
fprintf(fp_2,"%d %s %d %f\n",vehicle[i].vehicle_number,vehicle[i].salesman_name,vehicle[i].unload_qty,vehicle[i].vehicle_earned_amount);
}
fclose(fp);
fclose(fp_1);
fclose(fp_2);

}
// view current stock item list with fully detail
void view_inventory_detail(){
int i,choice;
printf("\n\t\t\t        <------XYZ INVENTORY DETAILS------>\n\n");
printf("\t*============================================================================*\n");
printf("\t*           *\t            * \t           *\t            * \t             *\n ");
printf("\t* Inventory *\tItem brand  * \tItem name  *\t Quantity   * \tunit price   *\n");
printf("\t* Item no.  *\t            * \t           *\t            * \t  Rs.        *\n ");
printf("\t*============================================================================*\n");
for(i=0;i<stock_size_current;i++){
printf("\t\xde  %3d.     \xde %s \t    \xde %s \t   \xde\t%5d       \xde\t%10.2f   \xde\n",i+1,item[i].item_brandname,item[i].item_name,item[i].item_qty,item[i].item_price);
printf("\t\xde ---------------------------------------------------------------------------\xde\n");
}

printf("\n\tEnter any number to Go to stock menu : ");
scanf("%d",&choice);
switch(choice){

default :
    system("cls");
    inventory_Menue();
    break;}

}

// menu of stock
void inventory_Menue(){
int choice;
printf("\n\t\t-------------------------------------------");
printf("\n\t\t<............ INVENTORY MENU .............>");
printf("\n\t\t-------------------------------------------");
printf("\n\n\t\t1. add items and  Restock");
printf("\n\n\t\t2. View Stock details");
printf("\n\n\t\t3. Load to vehicles");
printf("\n\n\t\t4. Unload vehicle");
printf("\n\n\t\t5. Go to main menu");
printf("\n\n\t\tEnter option number here : ");
scanf("%d",&choice);
switch (choice){
case 1:
    system("cls");
    add_item();
    break;
case 2:
    system("cls");
    view_inventory_detail();
    break;
case 3:
    system("cls");
    loadvehicle();
    system("cls");
    inventory_Menue();
    break;
case 4:
    system("cls");
    unloadvehicle();
    system("cls");
    inventory_Menue();
    break;
case 5:
    system("cls");
    main_menu();
    break;
default:
    printf("\n\t\tinvalid answer");
    Sleep(1000);
    system("cls");
    inventory_Menue();
    break;
}
}

//load item to stock
void loadvehicle(){
int i,selected_item,total_qty,selected_qty,count;
bool ability_of_load;
ability_of_load=check_ability_for_load();
if(ability_of_load){
if(initial_salesman_details){
printf("\n\t\t..............................");
printf("\n\t\t<<<<<<<Loading section>>>>>>>>");
printf("\n\t\t..............................");

printf("\n\n\tTHE LOADING CAPACITY  OF EACH VEHICLE IS 1500 \n");

for(i=0;i<SIZEOFVEHICALS;i++){
total_qty=0;
count=0;
while(total_qty<loading_size){

printf("\n\tEnter the item number to load vehicle no %d   #%d  :",vehicle[i].vehicle_number,i+1);
scanf("%d",&selected_item);

if(selected_item<=stock_size_current && selected_item>0){
printf("\tEnter the quantity of item %d (Remaining item %5d) :",selected_item,item[selected_item-1].item_qty);
scanf("%d",&selected_qty);

if(selected_qty<=item[selected_item-1].item_qty && selected_qty<=loading_size && selected_qty>0) {
total_qty+=selected_qty;

if(total_qty<=loading_size){
vehicle[i].vehicle_item_list[count][0]=selected_item-1;
vehicle[i].vehicle_item_list[count][1]=selected_qty;
stockbalance(selected_item,selected_qty,deactive);
count++;
vehicle[i].vehicle_loaded_size=count;
}
else{
printf("\n\tMaximum quantity reached\n");
total_qty-=selected_qty;
}
}
else{
    printf("\n\titem %d  couldn't load\n ",selected_item);
}
}
else{
    printf("\tinvalid answer");
}
}
}
printf("\n\tLoad successfully");
for(i=0;i<10;i++){
    printf(".");
    Sleep(200);
}}
else{
    add_details_vehicle();
    initial_salesman_details=true;
    system("cls");
    loadvehicle();
}
}
else{
    printf("\n\tNOT ENOUGH ITEMS FOR LOAD PLEASE RESTOCK OR ADD ITEMS");
    Sleep(2000);
}
}


// add new items or increase quantity of items 2 in one option
void add_item(){
int count ,choice,qty;
float price;
char brand_name[20],item_name[20];
count=stock_size_current;
bool decision1=true;
printf("\t(Max size of item list 100)\n");
while(decision1!=false){
    printf("\n\tEnter the new item %d\n\n",count+1);
    error_1:
    printf("\tEnter the item brand name :");
    scanf("%s",brand_name);
    if(max_word_size_inventory<strlen(brand_name)){ //Validation checking
        printf("\n\tMaximum 8 characters only\n");
        goto error_1;
    }else{
    error_2:
    printf("\tEnter the item name       :");
    scanf("%s",item_name);
    if(max_word_size_inventory<strlen(item_name)){ //Validation checking
         printf("\n\tMaximum 8 characters only\n");
         goto error_2;
    }
    else{
    error_3:
    printf("\tEnter the item amount     :"); //
    scanf("%d",&qty);
    printf("\tEnter the item price      :");
    scanf("%f",&price);
    if(qty<=0 || price <=0){
        printf("\n\tData is not valid\n");
        goto error_3;
    }
    printf("\n\tEnter 1 to save and go to stock menu or Enter any number to continue :");
    count=search(count,qty,price,brand_name,item_name);
    scanf("%d",&choice);
    if(choice==1){
      decision1=false;
    }
    stock_size_current=count;}
    }
    }

 system("cls");
 inventory_Menue();
}
// searching first item brand name and search next if the item name already exist in the system then add the quantity if not found add like new item
int search(int count,const int qty,const float price,const char brand_name[],const char item_name[]){
bool search_decision=true;
int i,j;
for(i=0;i<stock_size_current;i++){// first find the brand name match to the entered brand name
        if(strcmp(item[i].item_brandname,brand_name)==0){
        for(j=0;j<stock_size_current;j++){
         if(strcmp(item[j].item_name,item_name)==0 && i==j){ //if brand name matched after checking whether item name equal not
            item[j].item_price=price;                    // if both case matched can increase items and can change price value
            item[j].item_qty=item[j].item_qty+qty;
            search_decision=false;
            break;
         }}}}
         if(search_decision){
            strcpy(item[count].item_brandname,brand_name);// if both case not matched to entered data add as a new item to the system
            strcpy(item[count].item_name,item_name);
            item[count].item_price=price;
            item[count].item_qty=qty;
            count++;
        }
        return count;
}
//initial vehicle number and salesman name
void add_details_vehicle(){
int i,vehicle_number;
char salesman_name[20];
printf("\n\tInitial the vehicle number and salesman name");
printf("\n\t<*******************************************>");
for(i=0;i<SIZEOFVEHICALS;i++){
printf("\n\tVehicle no# %d\n\n",i+1);
error_1:
printf("\n\tEnter the vehicle number : ");
scanf("%d",&vehicle_number);
if(max_vehicle_number<vehicle_number){
printf("\n\tMax digits is only 4");
 goto error_1;
}
else{
error_2:
printf("\n\tEnter the salesman name  : ");
scanf("%s",salesman_name);
if(max_size_salesman_name<strlen(salesman_name)){
printf("\n\tMax character is only 8");
goto error_2;

}
else{
printf("\n");
vehicle[i].vehicle_number=vehicle_number;
strcpy(vehicle[i].salesman_name,salesman_name);
}
}
}
}
/*
when loading and unloading
if logic is a "active"-> add items to stock
if logic is a "deactive"-> reduce item from stock
*/
void stockbalance(int itemnumber,int qty,bool decision){
if(decision){
item[itemnumber-1].item_qty=item[itemnumber-1].item_qty+qty;
}
else{
item[itemnumber-1].item_qty=item[itemnumber-1].item_qty-qty;
}
}
//login function.
void login(){
int i,N_user,N_password;
FILE *in;
char usernametxt[30]="Enter the user name :";
char passwordtxt[30]="Enter the password  :";
char username[]="Malindu";
char password[]="AS2019468";
char inputuser[20];
char inputpassword[20];
char ch;
in=fopen("login.txt","r");
if(in==NULL){
    printf("File doesn't exit");
    exit(1);
}else{

while(ch!=EOF){
   ch=fgetc(in);
   printf("%c",ch);
}
fclose(in);
}

N_user=strlen(usernametxt);
N_password=strlen(passwordtxt);
Sleep(2000);
printf("\n\n\n\t\t");
for(i=0;i<N_user;i++){

    printf("%c",usernametxt[i]);
    Sleep(90);
}
scanf("%s",inputuser);
printf("\n\t\t");
for(i=0;i<N_password;i++){

    printf("%c",passwordtxt[i]);
    Sleep(90);
}
scanf("%s",inputpassword);
if(strcmp(username,inputuser)!=0 || strcmp(password,inputpassword)!=0){

    printf("\n\t\t.......Invalid User name or Password....... ");
    Sleep(1000);
    system("cls");
    login();
}
else{
printf("\n\t\tLogin succeed ");
for(i=0;i<10;i++){
 printf("\xfe");
 Sleep(100);
}
}
}
//manage vehicle options.
void manage_vehicle(){
int choice;
printf("\n\t\t--------------------------------- ");
printf("\n\t\t<.........Manage Vehicle.........>");
printf("\n\t\t--------------------------------\n");
printf("\n\n\t\t1.Initial vehicle details");
printf("\n\n\t\t2.Previous Loaded details");
printf("\n\n\t\t3.Go to Main menu");
printf("\n\n\t\tEnter option number here :");
scanf("%d",&choice);

switch(choice){

case 1:
    system("cls");
    add_details_vehicle();
    system("cls");
    manage_vehicle();
    break;
case 2:
    system("cls");
    vehicle_load_detail();
    break;
case 3:
   system("cls");
   main_menu();
default:
    printf("\n\tinvalid Answer ");
    Sleep(200);
    system("cls");
    manage_vehicle();
}
}

//view previous vehicle load details.
void vehicle_load_detail(){
int i,j,item_arr_index,choice;
for(i=0;i<SIZEOFVEHICALS;i++){
printf("\tVehicle #%d",i+1);
printf("\n\tSalesman name : %s",vehicle[i].salesman_name);
printf("\n\n\t\t\t     <------VEHICLE NO.%d ITEM DETAILS------>\n\n",vehicle[i].vehicle_number);
printf("\t*============================================================================*\n");
printf("\t*           *\t            * \t           *\t            * \t             *\n ");
printf("\t* Inventory *\tItem brand  * \tItem name  *\tLoaded Qty. * \tunit price   *\n");
printf("\t* Item no.  *\t            * \t           *\t            * \t Rs.         *\n ");
printf("\t*============================================================================*\n");
for(j=0;j<vehicle[i].vehicle_loaded_size;j++){
item_arr_index=vehicle[i].vehicle_item_list[j][0];
printf("\t\xde %3d.      \xde %s \t    \xde %s \t   \xde\t%5d       \xde\t%10.2f  \xde\n",vehicle[i].vehicle_item_list[j][0]+1,item[item_arr_index].item_brandname,item[item_arr_index].item_name,vehicle[i].vehicle_item_list[j][1],item[item_arr_index].item_price);
printf("\t\xde --------------------------------------------------------------------------\xde\n");
}
printf("\n\n");
}
printf("\n\tEnter any number to Go to inventory menu :");
scanf("%d",&choice);
switch(choice){
default :
system("cls");
manage_vehicle();
break;
}
}

//Unload function of vehicle.
void unloadvehicle(){
int i,j,unload_qty,count,remain_qty,item_no;
printf("\n\t\t.....................");
printf("\n\t\t<<<<<<<Unload>>>>>>>>");
printf("\n\t\t.....................");
if(vehicle[1].vehicle_loaded_size!=0){ //checking one of vehicle loaded
for(i=0;i<SIZEOFVEHICALS;i++){
count=0;
printf("\n\t Vehicle number : %4d | Salesman name : %s",vehicle[i].vehicle_number,vehicle[i].salesman_name);
printf("\n\n\t*=============================*\n");
printf("\t*           *\t              *\n ");
printf("\t* Inventory *\tLoaded Qty.   *\n");
printf("\t* Item no.  *\t              *\n ");
printf("\t*=============================*\n");
for(j=0;j<vehicle[i].vehicle_loaded_size;j++){
printf("\t   %d.\t    \xde %5d\n",vehicle[i].vehicle_item_list[j][0]+1,vehicle[i].vehicle_item_list[j][1]);
printf("\t...............................\n");
}

while(count<vehicle[i].vehicle_loaded_size){
printf("\n\tEnter the Unload quantity for item no#%3d ->",vehicle[i].vehicle_item_list[count][0]+1);
scanf("%d",&unload_qty);
// Check the unload quantity is greater than loaded quantity of each vehicle
if(unload_qty<=vehicle[i].vehicle_item_list[count][1]){

remain_qty=vehicle[i].vehicle_item_list[count][1]-unload_qty;//if there exist remain of item return to the item

item_no=vehicle[i].vehicle_item_list[count][0]+1;

set_unload_qty_item(item_no,unload_qty);

vehicle[i].unload_qty+=unload_qty;

vehicle_earned_amount(i,item_no,unload_qty);

stockbalance(item_no,remain_qty,active);

count++;
}
else{
printf("\n\titem quantity exceed the limit");
}
}
}

printf("\n\tUnload successfully");
for(i=0;i<10;i++){
    printf(".");
    Sleep(200);
}
remove_load_details();
}
else{
    printf("\n\tNO LOADED DATA.GO TO THE LOADING SECTION");
    Sleep(2000);
    system("cls");
    inventory_Menue();
}
}

//Find item when unload  the item
void set_unload_qty_item(int item_no,int qty){
int i;
item_no--;
for(i=0;i<stock_size_current;i++){
    if(i==item_no){
        item[i].unload_qty+=qty;
        break;
}
}
}

//Progress of vehicle  and items
void progress(){
int answer;
printf("\n\t\t...........................................");
printf("\n\t\t<<<<<<<Progress of item and vehicle>>>>>>>>");
printf("\n\t\t...........................................");
printf("\n\n\t\t1.Item progress with graph");
printf("\n\n\t\t2.Salesman progress");
printf("\n\n\t\t3.Go to the Main menu");
printf("\n\n\t\t Enter option number here :");
scanf("%d",&answer);
switch(answer){
case 1:
system("cls");
item_progress_table();
item_sold_graph();
break;
case 2:
system("cls");
salesman_progress();
break;
case 3:
system("cls");
main_menu();
break;
default :
printf("\n\t\t.....invalid answer......");
Sleep(200);
system("cls");
progress();
}
}

//Each vehicle earned amount from sold item
void vehicle_earned_amount(int index,int selected_item,int unload_qty){
    selected_item--;
    vehicle[index].vehicle_earned_amount+=(item[selected_item].item_price*unload_qty);
}

//To sort item order of sold item Maximum to miniumum;
int sort_item_decending(int index){
int i,arr_index[stock_size_current],array_of_items_decending_order[stock_size_current],j,index_value;
for(i=0;i<stock_size_current;i++){
    arr_index[i]=i;
    array_of_items_decending_order[i]=item[i].unload_qty;
}
for(i=0;i<stock_size_current;i++){
for(j=i+1;j<stock_size_current;j++){
    if( array_of_items_decending_order[i]<array_of_items_decending_order[j]){
     index_value=arr_index[i];
     arr_index[i]=arr_index[j];
     arr_index[j]=index_value;
     index_value=array_of_items_decending_order[i];
     array_of_items_decending_order[i]=array_of_items_decending_order[j];
     array_of_items_decending_order[j]=index_value;
}
}
}
return arr_index[index]; //return index of items in decending order
}

// total of sold items
int total_of_unload_amount(const int size,const bool select){
int i,total_amount=0;
for(i=0;i<size;i++){
    if(select){
    total_amount+=item[i].unload_qty;
    }
    else{
    total_amount+=vehicle[i].unload_qty;
    }
}
return total_amount;
}

// calculate total income an item...
float total_income_an_item(int index){
float income;
income=item[index].unload_qty*item[index].item_price;
return income;
}

//Graph of sold amount of items...
void item_sold_graph(){

int i,min_index,max_index,min_value,max_value,j,select;
max_index=sort_item_decending(0);
max_value=item[max_index].unload_qty;
for(i=stock_size_current-1;i>=0;i--){
min_index=sort_item_decending(i);
min_value=item[min_index].unload_qty;
if(min_value!=0){
    break;
}}
printf("\n\t\t\t\t...................................");
printf("\n\t\t\t\t<<<<<<<GRAPH OF SOLD ITEM>>>>>>>>");
printf("\n\t\t\t\t...................................");
//draw y axis
printf("\n\n  Sold item qty.\n");
printf("\t^\n");
printf("\t^\n");
printf("\t\xb3\n");
printf("\t\xb3\n");
min_value/=2;
int Y_axis_length=max_value/min_value;//set parameter
int Y_value_up,Y_value_down;

for(i=Y_axis_length+1;i>0;i--){
    Y_value_up=i*min_value;
    Y_value_down =(i-1)*min_value;
    for(int k=0;k<3;k++){
    if(k==0){
    printf("%5d\t\xc5",Y_value_up);
    }else{
    printf("\t\xb3");}
    for(j=0;j<stock_size_current;j++){
    int val=item[j].unload_qty-min_value;
    if(val>=Y_value_down ){
    printf(" \xdb\xdb\xdb ");
    }
    else{
    printf("     ");
    }
}
printf("\n");
}
 }
 printf("\t\xc0");
 for(i=0;i<stock_size_current;i++){
 printf("\xc4\xc4\xc4\xc4\xc4");
 }
printf("\xc4\xc4 >> Item number\n\t");
for(i=0;i<stock_size_current;i++){
printf(" %3d ",i+1);
}
printf("\n\t\tPress any number to go progress menu :");
scanf("%d",&select);
switch(select){
default:
system("cls");
progress();
break;
}
}

//Items in table order of decending order
void item_progress_table(){
int i,sorted_item,total_item_sold,income_item;
float total_sales=0.0;
total_item_sold=total_of_unload_amount(stock_size_current,active);
printf("\n\t\t\t\t    ---------------------------------");
printf("\n\t\t\t\t    <<<<<<<ITEM SALES PROGRESS>>>>>>>");
printf("\n\t\t\t\t    ---------------------------------");
printf("\n\n\t(Tables made in descending order of quantity sold)\n");
printf("\n\n\t*====================================================================================*\n");
printf("\t*        *           *\t                *               *           *\t Total sales *\n ");
printf("\t*  Index * Inventory *\t  Item brand    *   Item name   *   Sold    *\t    income   *\n");
printf("\t*   no.  *  Item no. *\t     name       *               *  Quantity *\t     Rs.     *\n ");
printf("\t*====================================================================================*\n");
for(i=0;i<stock_size_current;i++){
sorted_item=sort_item_decending(i);
income_item=total_income_an_item(i);
total_sales+=income_item;
printf("\t\xde %3d.   \xde    %3d    \xde     %s  \t\xde  %s   \t\xde  %5d    \xde  \t%10.2f  \xde\n",i+1,sorted_item+1,item[sorted_item].item_brandname,item[sorted_item].item_name,item[sorted_item].unload_qty,total_income_an_item(sorted_item));
printf("\t\xde-----------------------------------------------------------------------------------\xde\n");
}
printf("\t\xde                        TOTAL                        \t\xde  %5d    \xde   %10.2f  \xde\n",total_item_sold,total_sales);
printf("\t ====================================================================================\n");
}

//Salesman progress
void salesman_progress(){
int i,total_item_sold,choice;
float total_sales;
total_item_sold=total_of_unload_amount(SIZEOFVEHICALS,deactive);
total_sales=total_income_vehicles();

printf("\n\t\t\t\t    ---------------------------------");
printf("\n\t\t\t\t    <<<<<<< SALESMAN PROGRESS >>>>>>>");
printf("\n\t\t\t\t    ---------------------------------");
printf("\n\n\t*=======================================================================================*\n");
printf("\t*        *                *\t                       *               *  Total sales   *\n ");
printf("\t*  Index * Vehicle Number *\t      SalesMan         *     Sold      *    income      *\n");
printf("\t*   no.  *                *\t        Name           *   Quantity    *      Rs.       *\n ");
printf("\t*=======================================================================================*\n");
for(i=0;i<SIZEOFVEHICALS;i++){

printf("\t\xde %3d.   \xde  %d     \t  \xde %s           \t       \xde   %5d       \xde\%10.2f      \xde\n",i+1,vehicle[i].vehicle_number,vehicle[i].salesman_name,vehicle[i].unload_qty,vehicle[i].vehicle_earned_amount);
printf("\t\xde---------------------------------------------------------------------------------------\xde\n");
}
printf("\t\xde                        TOTAL                 \t       \xde   %5d       \xde%10.2f      \xde\n",total_item_sold,total_sales);
printf("\t ======================================================================================\n");
printf("\n\tPress any number to go manage vehicle : ");
scanf("%d",&choice);
switch(choice){
default:
system("cls");
progress();
break;
}
}

//Main menu
void main_menu(){

FILE *fp;
char ch;
fp=fopen("mainmenu.txt","r");
if(fp==NULL){
    printf("File doesn't exit");
}else{
while(ch!=EOF){
   ch=fgetc(fp);
   printf("%c",ch);
}
fclose(fp);
}
int i,choice;
char answer[]="Enter option number here :";
printf("\t\t\t\t--------------------------------------");
printf("\n\t\t\t\t<............ MAIN MENU .............>");
printf("\n\t\t\t\t--------------------------------------");
Sleep(200);
printf("\n\n\t\t\t\t1. Inventory");
Sleep(200);
printf("\n\n\t\t\t\t2. Manage Vehicle");
Sleep(200);
printf("\n\n\t\t\t\t3. progress of items and salesman");
Sleep(200);
printf("\n\n\t\t\t\t4. Save and Exit");
printf("\n\n\t\t\t\t");
for(i=0;i<strlen(answer);i++){
    printf("%c",answer[i]);
    Sleep(90);
}

scanf("%d",&choice);
switch(choice){
case 1:
system("cls");
inventory_Menue();
break;
case 2:
system("cls");
manage_vehicle();
break;
case 3:
system("cls");
progress();
case 4:
datasave();
exit(1);
break;
default:
printf("\n\n\t\t\t\t....invalid answer.....");
Sleep(2000);
system("cls");
main_menu();
break;
}
}

//calculate total income of whole vehicles..
float total_income_vehicles(){
int i;
float total_income;
for(i=0;i<SIZEOFVEHICALS;i++){
    total_income+=vehicle[i].vehicle_earned_amount;
}
return total_income;
}

//delete previous details after unload...
void remove_load_details(){
int i;
for(i=0;i<SIZEOFVEHICALS;i++){
   vehicle[i].vehicle_loaded_size=0;
}
}
bool check_ability_for_load(){
int i,total_of_item;
for(i=0;i<stock_size_current;i++){
    total_of_item+=item[i].item_qty;

}
if(total_of_item>=(loading_size*3)){
     return true;
}
else{
    return false;
}
}





