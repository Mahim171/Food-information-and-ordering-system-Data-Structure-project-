#include<conio.h>
#include<windows.h>
#include<time.h>
#include<bits/stdc++.h>
#include <iomanip>
#include <ctime>
#include <sstream>
using namespace std;

///Logic Functions

/// Update & Insert Function

vector<int> get_food_choice;
map<int,int> foodCount;

void insertfirst(int data, string foodname, int quantity, float price);
void insertmid(int pos, int data, string foodname, int quantity, float price);
void insertend(int data, string foodname, int quantity, float price);
void updatefood(int udata, int uquantity);

/// Display Function
void foodlist();
void order_view(int order, int quantity, int or_no);
void main_menu();
void MENUM();
void AdMinMenu();
void LOGIN();
///Delete & Count Function
void deletefood(int serial);
int countitem();
int main();



///extra design Function

void cls();
void echo(char print[]);
void br(int line);
void pre(int tab);
void span(int space);
void ccolor(int clr);
void pwellcome();
void loadingbar();
void middle1(void);
void middtab1(void);
void backuploader(void);
void cuschoice();


///START Structure Here

struct Node
{
    string foodname;
    int quantity;
    float price;
    int data;
    Node* next;
    Node(int dat, string foodnam, int quantit, float pric) {
        data=dat;
        foodname=foodnam;
        quantity=quantit;
        price=pric;
    }
};

///Global Type

typedef struct Node node ;

node *head;
int c=0;
    int any;
    int cardno[100];
    float cardmoney[100];
    float totalmoney = 0;
    int total_order[100];
    int order_quantity[100];
    int order=0;
    int uquantity;
    int citem;


void foodlist()
{

    ccolor(26);

    printf("\n\t\t");
    ccolor(240);
    printf("______________________________________________________ ");
    ccolor(26);
    printf("\n\t\t");
    ccolor(240);
    printf("|  Food No.  |   FooD Name   |  Price  |   In Stock   |");
    ccolor(26);
    printf("\n\t\t");
    ccolor(240);
    printf("-------------------------------------------------------");
    ccolor(26);

    node *temp;

    temp = head;

    while(temp != NULL)
    {

        ccolor(26);


        printf("\n\t\t");
        ccolor(62);
        printf("|     %-8d|",temp->data);
        cout << temp->foodname << "   ";

        printf("|     %-8f|     %-8d|",temp->price, temp->quantity);
        ccolor(26);
        printf("\n\t\t");
        ccolor(62);
        printf("-------------------------------------------------------");


        temp = temp->next ;

        Sleep(100);

    }

    ccolor(26);

    //  free(temp);

}
std::string currentDate() {
    std::time_t now = std::time(nullptr);
    std::tm *ltm = std::localtime(&now);

    std::ostringstream oss;
    oss << std::put_time(ltm, "%Y-%m-%d");
    return oss.str();
}

std::string currentTime() {
    std::time_t now = std::time(nullptr);
    std::tm *ltm = std::localtime(&now);

    std::ostringstream oss;
    oss << std::put_time(ltm, "%I:%M:%S %p");
    return oss.str();
}
string IName;
void invoice()
{
    std::ofstream outfile("invoice.txt"); //
    std::string date = currentDate();
    std::string time = currentTime();
    cls();
    middle1();
    fflush(stdin);
    pre(4);
    cout<<"<<<<<<<< INVOICE <<<<<<<<"<<endl<<endl;
    pre(4);
    cout<<"Name : "<<IName<<endl;
    outfile << "Name : " << IName << std::endl;
    pre(4);
    cout<<"Date : "<< date <<endl;
    pre(4);
    cout << "Time: " << time << endl;
    int total = 0;
    map<int,int> cnt;
    for(int i=0; i<get_food_choice.size(); i++)
    {
        node *temp;
        temp = head;
        while(temp!=NULL)
        {
            if(temp->data == get_food_choice[i] && cnt[get_food_choice[i]] == 0)
            {
                cnt[get_food_choice[i]]++;
                pre(4);
                cout<<temp->foodname<<" "<<temp->price * foodCount[get_food_choice[i]]<<endl;
                outfile << temp->foodname << " " << temp->price * foodCount[get_food_choice[i]] << std::endl;

                total += temp->price * foodCount[get_food_choice[i]];

            }
            temp = temp->next;
        }
    }
    pre(4);
    cout<<"TOTAL Prize "<<total<<endl<<endl;
    outfile << "TOTAL Prize " << total << std::endl << std::endl;

    pre(4);
    cout<<"Pay Now"<<endl;
    outfile.close();
}

void writeReviewToFile() {
    ofstream reviewFile("reviews.txt", std::ios::app); // Open file in append mode
    if (!reviewFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string review;
    cout << "Please write your review about our Service. We greatly care about our customers opinion: ";
    cout << endl << endl;
    cin.ignore(); // Ignore any leftover newlines in the input buffer
    getline(cin, review);

    reviewFile << review << endl; // Write the review to the file
    reviewFile.close(); // Close the file
    cout << endl;
    cout << "Thank you for your precious review. Your review really matters to us." << endl<<endl;
    cout << "Redirecting to Main Page";
    Sleep(500);
    cout << ".";
    Sleep(500);
    cout << ".";
    Sleep(500);
    cout << ".";
}

void infoodlist() {
    ifstream infile;
    infile.open("foodlist.txt"); // Open file in default mode (input mode)

    if (!infile) {
        cerr << "foodlist.txt not found!" << endl;
         // Return an error code indicating failure
    }

    int data;
    string foodname;
    int quantity;
    float price;
    int cnt = 0;

    while (infile>>data>>foodname

        >> price >> quantity) {

        // Read the rest of the line into foodname
        //infile>>data>>foodname;

        //infile >> quantity >> price;

        // Decide which insertion method to use based on cnt
        if (cnt == 0)
            insertfirst(data, foodname, quantity, price);
        else
            insertend(data, foodname, quantity, price);

        cnt++;
    }
    infile.close(); // Close the file after reading
}

void save() {
    ofstream outfile("foodlist.txt"); // Open file in append mode
    if (!outfile) {
        cerr << "foodlist.txt not found!" << endl;
        return;
    }

    node *temp;
    temp = head;
    while(temp!=NULL)
    {
            outfile << temp->data<<endl;
            outfile <<temp->foodname<< endl;
            outfile <<temp->price<<endl;
            outfile << temp->quantity << endl;
            temp = temp->next;
    }
}
map<int,int> cq;
void DeleteItem(int value_to_delete,int quan)
{
    node *ptr=head;
    while(ptr!=NULL)
    {
        if(ptr->data=value_to_delete)
        {
            ptr->quantity+=quan;
            break;
        }
        cout << 1;
        ptr = ptr->next;
    }
    if(cq[value_to_delete] == quan){
    bool found = false;
    for (size_t i = 0; i < get_food_choice.size(); ++i)
    {
        if (get_food_choice[i] == value_to_delete)
        {
            for (size_t j = i; j < get_food_choice.size() - 1; ++j)
            {
                get_food_choice[j] = get_food_choice[j + 1];
            }
            get_food_choice.pop_back();
            found = true;
            break;
        }
    }
    }
    else{
        cq[value_to_delete] -= quan;
    }

}

map<string, string> loadUsers()
{
    ifstream infile("users.txt");
    map<string, string> users;
    string username, password;

    while (getline(infile, username) && getline(infile, password))
    {
        users[username] = password;
    }

    infile.close();
    return users;
}

void LOGIN()
{
    map<string,string> users = loadUsers();

    int n;
    while(1)
    {
        cls();
        middle1();
        pre(5);
        cout<<"1.Login"<<endl;
        Sleep(500);
        pre(5);
        cout<<"2.Sign Up"<<endl;
        Sleep(500);
        cout << endl;
        pre(5);
        cout<<"Enter your choice :  ";
        Sleep(500);
        cin>>n;
        if(n==1)
        {
            string username, password;
            cout << endl;
            pre(5);
            cout << "Enter user name : ";
            cin.ignore(); // Clear the input buffer
            getline(cin, username);
            cout << endl;
            pre(5);
            cout << "Enter password: ";
            getline(cin, password);

            auto it = users.find(username);
            if (it != users.end() && it->second == password)
            {
                IName = username;
                cout<<endl;
                pre(5);
                cout << "Login successful!" << endl;
                Sleep(1000);
                get_food_choice.clear();
               // main_menu();
                main_menu();
            }
            else
            {
                pre(5);
                cout << "Invalid username & password. Please try again." << endl;
                Sleep(1000);
            }
        }
        else if(n == 2)
        {
            std::string username, password;
            cout << endl;
            pre(5);
            std::cout << "-----Signing  Up------\n";
            cout<<endl;
            pre(5);
            std::cout << "Enter full name ( Username ): ";
            std::cin.ignore();
            std::getline(std::cin, username);



            if (users.find(username) != users.end())
            {
                pre(5);
                std::cout << "Username already exists. Please try a different one." << std::endl;
            }
            else
            {
                pre(5);
                std::cout << "Enter password: ";
                std::getline(std::cin, password);

                std::ofstream outfile("users.txt", std::ios::app);
                outfile << username << std::endl << password << std::endl;
                outfile.close();

                users[username] = password;
                pre(5);
                std::cout << "Signup successful!" << std::endl;
                Sleep(1000);
            }
        }
        else
        {
            pre(5);
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}
///////////////////////////////////////////////////

/*void addFoodToFile(int data, const char *foodname, int quantity, float price) {
    std::ofstream outfile("foodlist.txt", std::ios::app);
    outfile << data << endl<< foodname << endl<< quantity << endl<< price << std::endl;
    outfile.close();
}*/

void displayReviews() {
    std::ifstream infile("reviews.txt");
    if (!infile) {
        std::cerr << "Error opening file: reviews.txt" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(infile, line)) {
        std::cout << line << std::endl;
    }
    infile.close();
    int x;
    cout << endl << endl;
    cout << "Enter 1 to go back  ";
    cin >> x ;
    cout << endl;
    cout << "Redirecting to page";
    Sleep(500);
    cout << ".";
    Sleep(500);
    cout << ".";
    Sleep(500);
    cout << ".";
}

/////////////////////////////////
void AdMinMenu()
{
    while(1){
                cls();
                br(5);
                pre(4);
                echo("You are on Admin Pannel\n\n");
                pre(4);
                printf(" 1. Total Cash Today \n\n");
                Sleep(250);
                pre(4);
                printf(" 2. Update Food List \n\n");
                Sleep(250);
                pre(4);
                printf(" 3. Add Food \n\n");
                Sleep(250);
                pre(4);
                printf(" 4. Delete Food \n\n");
                Sleep(250);
                pre(4);
                printf(" 5. Instant Food List \n\n");
                Sleep(250);
                pre(4);
                printf(" 6. Item Counter \n\n");
                Sleep(250);
                pre(4);
                printf(" 7. Review \n\n");
                Sleep(250);
                pre(4);
                printf(" 0. Main Menu \n\n ");
                Sleep(250);
                pre(4);
                printf(" Enter Your Choice:  ");
                Sleep(250);
                int n;
                cin>>n;
                if(n==1)
                {

                    cls();
                    middle1();
                    pre(4);
                    printf("Todays Total Cash : %0.2f  \n",totalmoney);
                    Sleep(2000);

                    //goto adminchoise;
                }
                else if(n==2)
                {
                    cls();
                    int item,quan;
                    pre(5);
                    printf(" Enter Serial Number:   ");
                    cin >> item;
                    pre(5);
                    printf(" Enter quantity:   ");
                    cin >> quan;

                    bool f=0;
                    node *ptr=head;
                    while(ptr!=NULL)
                    {
                        if(ptr->data==item) {
                            f=1;
                            ptr->quantity=quan;
                            break;
                        }
                        ptr=ptr->next;
                    }
                    pre(5);
                    if(f==0) {
                        cout << "  Item Not Found  ";
                    }
                    else cout << "Successfully Updated";
                    Sleep(1000);
                }
                else if(n == 3)  //// ADD food
                {
                    foodadd:
                    cls();

                    char ffoodname[25];
                    int fquantity;
                    int fdata;
                    float fprice;
                    int fposi;

ffoodname:
                    br(3);
                    pre(4);
                    printf(" Enter Food Name :  ");
                    fflush(stdin);
                    scanf("%[^\n]s",ffoodname);
                    node *exist;
                    exist = head;
                    while(exist!=nullptr)
                    {
                        if(exist->foodname==ffoodname)
                        {
                            cls();
                            br(5);
                            pre(3);
                            printf(" Foodname Already Exist, Please Re-Enter  ");
                            Sleep(2000);
                            cls();
                            goto ffoodname;
                        }
                        exist=exist->next;
                    }
fquantity:
                    fflush(stdin);

                    br(2);
                    pre(4);
                    printf(" Enter Food Quantity :  ");

                    scanf("%d",&fquantity);
                    fflush(stdin);

foodserial:
                    br(2);
                    pre(4);
                    printf(" Enter Food Serial :  ");
                    scanf("%d",&fdata);

                    exist = head;
                    while(exist!=nullptr)
                    {
                        if(exist->data==fdata)
                        {
                            cls();
                            br(5);
                            pre(3);
                            printf(" Food Serial Already Exist, Please Re-Enter  ");
                            Sleep(2000);

                            goto foodserial;
                        }
                        exist=exist->next;
                    }


fprice:
                    fflush(stdin);

                    br(2);
                    pre(4);
                    printf(" Enter Food Price :  ");
                    fflush(stdin);

                    scanf("%f",&fprice);



                    br(2);
                    pre(4);
                    printf("Submiting your data");
                    for(int cs=0; cs<4; cs++)
                    {
                        printf(" .");
                        Sleep(500);
                    }


                    insertend(fdata,ffoodname,fquantity,fprice);
                    //addFoodToFile(fdata, ffoodname, fquantity, fprice);


                    br(2);
                    pre(4);
                    printf("Adding Food  Successfull....\n");

                    Sleep(2000);
                    AdMinMenu();
                    //goto adminchoise;

                }
                else if(n==4)
                {

                    cls();
                    middle1();
                    pre(2);
                    printf("Enter Serial No of the Food To Delete : ");
fdelete:
                    int fdelete;
                    fflush(stdin);
                    scanf("%d",&fdelete);
                    node *temp;
                    temp=head;
                    while(temp!=NULL)
                    {
                        if(temp->data==fdelete)
                        {
                            deletefood(fdelete);
                            break;
                        }
                        temp = temp->next;
                    }
                    if(temp==NULL||temp->data!=fdelete)
                    {
                        br(2);
                        pre(2);
                        printf("Please Enter Correct Number :  ");
                        Sleep(500);
                        goto fdelete;
                    }
                    AdMinMenu();

                }
                else if(n==5)
                {

                    cls();
                    foodlist();
                    Sleep(1000);

                    br(2);
                    pre(4);
                    printf("1. <-- back  \n\n");
                    pre(5);

                    int any;
                    fflush(stdin);
                    scanf("%d",&any);

                    AdMinMenu();

                }
                else if(n==6)
                {

                    int citem = countitem();
                    cls();
                    for(int cs=1; cs<=citem; cs++)
                    {
                        middle1();
                        pre(4);
                        printf("Item Counting ");
                        printf(" %d ",cs);
                        Sleep(150);
                        cls();
                    }
                    cls();
                    middle1();
                    pre(4);
                    printf("Total Food Item is --> %d  \n",citem);
                    Sleep(2000);
                    AdMinMenu();

                }
                else if(n == 7)
                {
                    cls();
                    displayReviews();

                }
                else if(n == 0)
                {
                    cls();
                    MENUM();
                    //goto mainmenu;
                    break;
                }

        }
    }
/*
void ADMINN()
{

adminpanelchoice:

            int admin_panel_choice;

            cls();
            middle1() ;
            pre(4);
            printf("1. Main Menu\n\n\t");
            Sleep(300);
            printf("Please Enter Password or ( 1 to Back in Main Menu ) : ");


            fflush(stdin);
            scanf("%d",&admin_panel_choice);

            if(admin_panel_choice==123321)
            {



                node *temp;

                temp = LIST;

adminchoise:

                cls();
                br(5);
                pre(4);
                echo("You are on Admin Pannel\n\n");
                pre(4);
                printf(" 1. Total Cash Today \n\n");
                Sleep(250);
                pre(4);
                printf(" 2. View Card Pay \n\n");
                Sleep(250);
                pre(4);
                printf(" 3. Add Food \n\n");
                Sleep(250);
                pre(4);
                printf(" 4. Delete Food \n\n");
                Sleep(250);
                pre(4);
                printf(" 5. Instant Food List \n\n");
                Sleep(250);
                pre(4);
                printf(" 6. Item Counter \n\n");
                Sleep(250);
                pre(4);
                printf(" 7. Backup System\n\n");
                Sleep(250);
                pre(4);
                printf(" 8. Instant Order Preview\n\n");
                Sleep(250);
                pre(4);
                printf(" 0. Main Menu ");
                Sleep(250);

                int adminchoise;



                fflush(stdin);
                scanf("%d",&adminchoise);

                if(adminchoise==1)
                {

                    cls();
                    middle1();
                    pre(4);
                    printf("Todays Total Cash : %0.2f  \n",totalmoney);

                    Sleep(2000);

                    goto adminchoise;
                }
                else if(adminchoise==2)
                {

                    if(c!=0)
                    {

                        cls();
                        br(3);
                        pre(4);

                        printf(" ____________________________\n");
                        pre(4);
                        printf("|   Card NO.   |   Money $   |\n");
                        pre(4);
                        printf("------------------------------\n");
                        pre(4);

                        for(int z=1; z<=c; z++)
                        {

                            printf("|  %d  | %0.2f |\n",cardno[z],cardmoney[z]);
                            pre(4);
                            printf("------------------------------\n");
                            pre(4);
                            Sleep(150);

                        }
                        Sleep(1500);
                    }

                    if(c==0)
                    {

                        cls();
                        middle1();
                        pre(4);
                        printf("No Card History\n");
                    }
                    Sleep(1500);
                    goto adminchoise;
                }

                else if(adminchoise==3)
                {

foodadd:
                    cls();

                    char ffoodname[25];
                    int fquantity;
                    int fdata;
                    float fprice;
                    int fposi;


                    br(3);
                    pre(4);
                    printf(" Enter Food Name :  ");

                    fflush(stdin);
                    scanf("%[^\n]s",ffoodname);
fquantity:
                    fflush(stdin);

                    br(2);
                    pre(4);
                    printf(" Enter Food Quantity :  ");

                    scanf("%d",&fquantity);
                    fflush(stdin);

foodserial:
                    br(2);
                    pre(4);
                    printf(" Enter Food Serial :  ");
                    scanf("%d",&fdata);
                    node *exist;
                    exist = LIST;
                    while(exist->data!=fdata)
                    {
                        if(exist->next==NULL)
                        {
                            break;
                        }
                        exist=exist->next;
                    }
                    if(exist->data==fdata)
                    {
                        cls();
                        br(5);
                        pre(3);
                        printf(" Food Serial Already Exist, Please Re-Enter  ");
                        Sleep(2000);
                        goto foodserial;
                    }

fprice:
                    fflush(stdin);

                    br(2);
                    pre(4);
                    printf(" Enter Food Price :  ");
                    fflush(stdin);

                    scanf("%f",&fprice);



                    br(2);
                    pre(4);
                    printf("Submiting your data");
                    for(int cs=0; cs<4; cs++)
                    {
                        printf(" .");
                        Sleep(500);
                    }


                    insertend(fdata,ffoodname,fquantity,fprice);

                    br(2);
                    pre(4);
                    printf("Adding Food  Successfull....\n");

                    Sleep(2000);

                    goto adminchoise;

                }
                else if(adminchoise==4)
                {

                    cls();
                    middle1();
                    pre(2);
                    printf("Enter Serial No of the Food To Delete : ");
fdelete:
                    int fdelete;
                    fflush(stdin);
                    scanf("%d",&fdelete);
                    node *temp;
                    temp=LIST;
                    while(temp->data != fdelete)
                    {
                        temp = temp->next;
                    }
                    if(temp->data==fdelete)
                    {
                        deletefood(fdelete);
                    }
                    else
                    {
                        br(2);
                        pre(2);
                        printf("Please Enter Correct Number :  ");
                        Sleep(500);
                        goto fdelete;
                    }


                    goto adminchoise;
                }

                else if(adminchoise==5)
                {

                    cls();
                    foodlist();
                    Sleep(1000);

                    br(2);
                    pre(4);
                    printf("1. <-- back  \n\n");
                    pre(5);



                    fflush(stdin);
                    scanf("%d",&any);

                    goto adminchoise;

                }

                else if(adminchoise==6)
                {

                    citem = countitem();
                    cls();
                    for(int cs=1; cs<=citem; cs++)
                    {
                        middle1();
                        pre(4);
                        printf("Item Counting ");
                        printf(" %d ",cs);
                        Sleep(150);
                        cls();
                    }
                    cls();
                    middle1();
                    pre(4);
                    printf("Total Food Item is --> %d  \n",citem);
                    Sleep(2000);
                    goto adminchoise;

                }

                ///Backup System
                else if(adminchoise==7)
                {


                    char date[35]=__DATE__;

                    strcat(date,".txt");
                    FILE *fptr;
                    fptr=fopen(date,"w");
                    backuploader();
                    if(fptr==NULL)
                    {
                        br(3);
                        pre(3);
                        printf("Error!");
                        Sleep(500);
                        goto adminchoise;
                    }
                    fprintf(fptr,"Total Cash Today : %0.2f\n\n\n",totalmoney);
                    fprintf(fptr,"Card No ------- Money \n\n");
                    for(int l=1; l<=c; l++)
                    {
                        fprintf(fptr,"%d ------- %0.2f \n",cardno[l],cardmoney[l]);
                    }
                    br(2);
                    pre(4);
                    printf("Backup Successfull...");
                    Sleep(1500);



                    fclose(fptr);
                    goto adminchoise;
                }
                else if(adminchoise==8)
                {

                    cls();
                    br(2);
                    pre(2);
                    ccolor(7);
                    printf("\n\t\t");
                    ccolor(240);
                    printf("______________________________________________________ ");
                    ccolor(7);
                    printf("\n\t\t");
                    ccolor(240);
                    printf("|  Order No.  |   FooD Name   |  Quantity |  In Stock |");
                    ccolor(7);
                    printf("\n\t\t");
                    ccolor(240);
                    printf("------------------------------------------------------");
                    ccolor(7);
                    for(int o=1; o<=order; o++)
                    {
                        order_view(total_order[o],order_quantity[o],o);
                    }

                    br(2);
                    pre(4);
                    printf("1. <-- back  \n\n");
                    pre(5);

                    fflush(stdin);
                    scanf("%d",&any);

                    goto adminchoise;



                }
                else if(adminchoise==0)
                {

                    goto mainmenu;
                }

                else
                {
                    br(2);
                    pre(4);
                    printf("Please Select From List :  ");
                    Sleep(500);
                    goto adminchoise;
                }



            }

            else if(admin_panel_choice==1)
            {
                goto mainmenu;
            }
            else
            {
                br(2);
                pre(4);
                printf("Please Enter Correct Choice");
                goto adminpanelchoice;
            }
}
*/
///////////////////////////////////////////////?
///Main Menu

///////////////////////////////////////////////?
///Main Menu

int main()
{

    system("title ..................FOOD MANAGMENT SYSTEM.......................");
    system("mode con: cols=80 lines=30");
    echo("");
    fflush(stdin);
    loadingbar();
    cls();
    pwellcome();
    //Sleep(300);
    cls();
    ccolor(7);
    head = NULL;

    infoodlist();
    /*insertfirst(5,"Burger   ",23,120.23);
    insertend(6,"Pizza    ",13,100.67);
    insertend(1,"Hot Cake ",8,720.83);
    insertend(2,"Coffie   ",46,70.23);
    insertend(3,"Ice-Cream",46,70.23);
    insertend(4,"Sandwich ",34,60.23);
    insertend(7,"Grill    ",7,520.29);
    insertend(8,"Nun-Bread",121,35.13);
    insertend(9,"Cold Drinks",73,20.13);*/

    MENUM();

////////////////////////////////////////////////////////////////////////////
}
void cuschoice()
{
    //cls();
    br(1);

    int main_menu_choice;

    br(1);
    pre(4);
    printf("Enter your choice: ") ;
    //scanf("%d",&main_menu_choice);
    //get_food_choice.push_back(CH);

   while(1){
    cin >> main_menu_choice;
    if((main_menu_choice >=1 && main_menu_choice <=3))
    {

        if(main_menu_choice == 1)
        {
ORDER:
            cls();
            cout << "press 0 to go back";
            foodlist();
            int CH;

    br(2);
    pre(3);
    fflush(stdin);
    printf("Place Your Order: ") ;
    scanf("%d",&CH);
    get_food_choice.push_back(CH);

    if(CH==0)
    {
        main_menu();
    }

    node *temp;

    temp = head ;

    int NN;
    NN = get_food_choice.size();
    while(temp->data != get_food_choice[NN-1])
    {

        temp = temp->next;
        if(temp==NULL)
        {
            br(2);
            pre(4);
            echo("Please Choice From List ");
            br(2);
            Sleep(1000);
            foodlist();
        }

    }
    if(get_food_choice[NN-1] == temp->data)
    {

fcquantity:
        br(2);
        pre(4);
        printf("Enter Food Quantity : ");

        int fcquantity;

        fflush(stdin);
        scanf("%d",&fcquantity);
        cls();

        if(fcquantity==0)
        {
            cls();
            middle1();
            pre(3);
            printf("Quantity Can not be Zero ");
            Sleep(2000);
            cls();
            foodlist();
        }
        else if((fcquantity+foodCount[CH])>temp->quantity)
        {
            cls();
            middle1();
            pre(3);
            printf("Out of Stock ! ");
            Sleep(2000);

            foodlist();
        }
        else {
            cq[CH] = fcquantity;
            foodCount[CH] += fcquantity;
            totalmoney=fcquantity*temp->price;
            temp->quantity=(temp->quantity-fcquantity);
        }
        while(1)
        {
            middle1();
            pre(4);
            cout<<"1. New Food"<<endl<<endl;
            pre(4);
            printf("2. Confirm to buy this \n\n");
            pre(4);
            cout<<"Enter your choice :";


            int n;
            cin>>n;
            if(n == 1)
            {
                cls();
                goto ORDER;
            }
            else break;
        }
        cout<<"your Order"<<endl<<endl;

        int totalPrize = 0;
        auto unique_end = unique(get_food_choice.begin(), get_food_choice.end());

        ////////////////////////  Start ///////////////////////////
        ///     Dashboard
        ////////////////////////  Dashboard ///////////////////////////

        while(1)
        {
            cls();
            //middle1();

            middle1();
            pre(5);
            cout<<"<<<<<<<<<<  Dashboard  >>>>>>>6>>>>"<<endl;
            fflush(stdin);
            map<int,int> C;
            vector<int> Food;

            for(int i=0; i<get_food_choice.size(); i++)
            {
                C[get_food_choice[i]]++;
                if(C[get_food_choice[i]] == 1) Food.push_back(get_food_choice[i]);
            }

            get_food_choice = Food;
             pre(5);
             cout<<"Your order :"<<endl;
             cout<<endl;
              //middle1();
              cout<<endl;
             pre(5);
             cout<<"Food name " <<" "<<"Quantity"<<" "<<"Prize"<<endl;
            for(int i=0; i<get_food_choice.size(); i++)
            {
                temp = head;
                while(temp!=NULL)
                {
                    if(temp->data == get_food_choice[i])
                    {
                        pre(5);
                        cout<<temp->data<<"."<<temp->foodname<<" "<<cq[get_food_choice[i]]<<" "<<temp->price * cq[get_food_choice[i]]<<endl;
                        //cout<<foodCount[get_food_choice[i]]<<endl;
                        foodCount[get_food_choice[i]] = cq[get_food_choice[i]];
                        break;
                    }
                    temp = temp->next;
                }
            }
            bool f = 0;
            cout<<endl;
            while(1)
            {

               // middle1();
                pre(5);
                cout<<"1.Cancel an item"<<endl;
                pre(5);
                cout<<"2.Confirm your order"<<endl;
                pre(5);
                cout<<"   Enter your choice :";
                int n;
                cin>>n;
                if(n == 1)
                {
                    int serial,quan;
                    cout<<"Enter the item serial number you wish to delete : ";
                    cin >> serial;

                    cout<<"Enter the quantity you wish to delete : ";
                    cin >> quan;
                    if(C[serial] == 0) cout<<"INvalid"<<endl;
                    else
                    {
                        DeleteItem(serial,quan);
                        node *ptr=head;
                        while(ptr!=NULL)
                        {
                            if(ptr->data==serial)
                            {
                                totalmoney-=(ptr->data*quan);
                                break;
                            }
                        }
                    }
                    break;
                }
                f = 0;
                if(n==2)
                {
                    invoice();
                    f = 1;
                    break;
                }
            }
            if(f) break;
        }

        ////////////////////////  END ///////////////////////////
        ///     Dashboard
        ////////////////////////  END  ///////////////////////////
confirm:
        int confirm;

        fflush(stdin);
        br(2);
        pre(4);
        printf(" Enter your choice");
        scanf("%d",&confirm);
        if(confirm == 1 )
        {

            br(2);
            pre(4);
            printf(" 1. Cash ");
            br(2);
            pre(4);
            printf(" Enter your choice :  ");
payment:
            int payment;

            fflush(stdin);
            scanf("%d",&payment);

            if(payment==1)
            {
                /*order++;
                total_order[order]=get_food_choice[NN-1];NN++;
                order_quantity[order]=fcquantity;
                uquantity = temp->quantity - fcquantity;*/

                for(int i=0; i<get_food_choice.size(); i++)
                {
                    temp = head;
                    while(temp != NULL)
                    {
                        if(temp->data == get_food_choice[i])
                        {
                            int uquantity = temp->quantity - foodCount[get_food_choice[i]];
                            updatefood(get_food_choice[i],uquantity);
                        }
                        temp = temp->next;
                    }

                }

                cls();
                middle1();
                pre(4);
                printf("===>THANK YOU<===");
                br(2);
                pre(4);
                // cout<<"AAAA "<<get_food_choice<<endl;
                printf("Food Ordered Successfully ...");
                br(2);
                pre(4);
                printf("1. Wanna Buy Another Delicious ? ");
                br(2);
                pre(4);
                printf("2. Main Menu ");
psmenu:
                int ps_menu;

                fflush(stdin);
                scanf("%d",&ps_menu);

                if(ps_menu==1)
                {
                    goto ORDER;
                }
                else if(ps_menu==2)
                {
                    cls();
                    main_menu();
                }
                else
                {
                    br(2);
                    pre(4);
                    printf("Please Choice from list : ");
                    goto psmenu;
                }
                totalmoney=0;
            }

            ///Credit Card Option

            else if(payment==2)
            {

                int card_number[100];

                c++;

                cls();
                middle1();
                pre(4);
                printf("Enter Your Card No : ");

                fflush(stdin);
                scanf("%d",&card_number[c]);



                cardno[c] = card_number[c];

                int pin;

                br(2);
                pre(2);
                printf("Enter Your Card Pin [we never save your pin]  : ");

                fflush(stdin);
                scanf("%d",&pin);

                /*cardmoney[c] = totalmoney;

                order++;
                total_order[order]=get_food_choice[NN-1];
                order_quantity[order]=fcquantity;

                uquantity = temp->quantity - fcquantity;

                updatefood(get_food_choice[NN-1],uquantity);
                totalmoney=0;*/
                br(2);
                pre(4);
                printf("Payment Success...");
                br(2);
                pre(4);
                printf("1. Wanna Buy Another Delicious ? ");
                br(2);
                pre(4);
                printf("2. Main Menu ");
psmenu2:
                int ps_menu2;

                scanf("%d",&ps_menu2);

                if(ps_menu2==1)
                {
                    goto ORDER;
                }
                else if(ps_menu2==2)
                {
                    cls();
                    main_menu();
                }
                else
                {
                    br(2);
                    pre(4);
                    printf("Please Choice from list : ");
                    goto psmenu2;
                }

            }

            else
            {

                br(2);
                pre(4);
                printf("Enter Choice from List : ");

                goto payment;


            }


        }    ///END Confirm Y/y


        else
        {
            br(2);
            pre(4);
            printf("Enter Choise from List : ");

            goto confirm;


        }  ///end confirm;


    }  ///end get food choice if line


    else
    {

        br(2);
        pre(4);
        echo("Please Choice From List ");
        br(2);
        Sleep(300);

        goto ORDER;

    }  ///end get food choice
        }

        else if( main_menu_choice == 2)
        {
             cls();
              writeReviewToFile();
              main_menu();
        }

        else if(main_menu_choice==3) ////////////////
        {
            /*
            cls();
            middle1();
            pre(3);
            printf("Thank You For Using Our System \n\n\n\n\n\n\n");
            Sleep(1000);

            exit(1);*/
            cls();
            MENUM();
            main_menu();

            //goto mainmenu;
        }
    }

    else
    {
        br(2);
        pre(4);
        printf("Please Enter Correct Choice");
        Sleep(300);
        cls();
        cuschoice();

       // goto mainmenu;
    }
   }
}
void main_menu()
{
    cls();
    br(5);
    pre(3);
    echo("===> 1. Food List");
    Sleep(400);
    br(2);
    pre(3);
    echo("===> 2. Add Review");
    Sleep(400);
    br(2);
    pre(3);
    echo("===> 3. Main menu");
    Sleep(400);
    cuschoice();
   // goto ffoodname;
    //goto mainmenu;
    //   br(2); pre(3); echo("=> 4. Admin Panel");  Sleep(400);

    br(1);
}
void MENUM()
{
  while(1){
    cls();
    ccolor(7);
    middle1();
    br(3);
    pre(5);
    cout<<"1.Admin "<<endl;
    pre(5);
    cout<<"2.Customer "<<endl;
    pre(5);
    cout<<"3.Exit "<<endl;
    int n;
    cout<<endl;
    pre(5);
    cout<<" "<<"Enter your choice :  ";
    cin>>n;
    if(n==1)
    {
        cout<<"Password ";
        int kk;
        cin>>kk;
        if(kk == 123)
            AdMinMenu();
       //break;
    }
    else if(n == 2)
    {
        LOGIN();
      // break;
    }
    else if(n==3)
    {
        save();
        exit(1);
    }
   }
   //goto mainmenu;
}
void cls()
{

    system("cls");

}

void echo(char print[])
{

    printf("%s",print);
}

void br(int line)
{
    for(int i=0; i<line; i++)
    {
        printf("\n");
    }
}

void pre(int tab)
{

    for(int i=0; i<tab; i++)
    {
        printf("\t");
    }

}
void span(int space)
{

    for(int i=0; i<space; i++)
    {
        printf(" ");
    }

}

void insertend(int data, string foodname, int quantity, float price)
{
    node *temp,*ptr;
    temp = new Node(data,foodname,quantity,price);

    if(head==NULL)
    {
        head=temp;
        temp->next=NULL;
    }
    else {
        ptr=head;
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        ptr->next=temp;
        temp->next=NULL;
    }
}

void insertfirst(int data, string foodname, int quantity, float price)
{
    node *temp;

    temp = new Node(data,foodname,quantity,price);

    if(head==NULL)
    {
        head=temp;
        temp->next=NULL;
    }
    else {
        temp->next = head;
        head = temp;
    }
}

void insertmid(int pos, int data, string foodname, int quantity, float price)
{

    node *temp,*ptr;

    temp=(node *)malloc(sizeof(node));

    temp->data = data;

    temp->price = price;

    temp-> quantity = quantity;

    temp->foodname=foodname;

    ptr=head;
    while(ptr->next->data != pos )
    {


        ptr = ptr->next ;

    }

    temp->next = ptr->next;
    ptr->next = temp ;

    //    free(temp);
}

void deletefood(int serial)
{

    node *temp;
    temp=(node *)malloc(sizeof(node));

    temp = head;


    if(temp->data != serial)
    {

        while(temp->next->data != serial)
        {
            temp = temp->next;
        }

        if(temp->next->data == serial)
        {

            temp->next = temp->next->next;
            cls();
            printf("\n\n\n\n\t\t\tDeleting Item %d ",serial);
            for(int cs=0; cs<4; cs++)
            {
                printf(" .");
                Sleep(400);
            }

            printf("\n\n\n\n\t\t\tDeleted Successfylly \n");
            Sleep(500);

        }
        else
        {
            printf("\n\n\n\n\t\t\tFood Item Not Found\n");
            Sleep(500);
        }

        //head = temp ;

    }
    else
    {

        temp = temp->next;
        cls();
        printf("\n\n\n\n\t\t\tDeleting Item %d ",serial);
        for(int cs=0; cs<4; cs++)
        {
            printf(" .");
            Sleep(400);
        }

        printf("\n\n\n\n\t\t\tDeleted Successfylly \n");
        Sleep(500);

        //head = temp ;

        //LIST=head;
    }
}

void updatefood(int udata, int uquantity)
{

    node *temp;
    temp = head;

    while(temp->data!=udata)
    {
        temp = temp->next;

    }
    if(temp->data == udata)
    {
        temp->quantity = uquantity;
    }

}

int countitem()
{

    node *temp;

    temp = head;

    int countitem=0;

    if(temp==NULL)
    {
        countitem = 0;
    }
    else
    {
        countitem = 1;
        while(temp->next != NULL)
        {
            countitem++;
            temp = temp->next;
        }

    }


    return countitem;

}


void order_view(int order, int quantity, int or_no)
{



    ccolor(7);

    node *temp;

    temp = head;

    while(temp->data != order)
    {

        temp = temp->next;

    }
    if(temp->data == order)
    {

        ccolor(7);

        printf("\n\t\t");
        ccolor(62);
        printf("|     %d      |    %s  |     %d     |     %d     |",or_no,temp->foodname,quantity,temp->quantity);
        ccolor(7);
        printf("\n\t\t");
        ccolor(62);
        printf("-------------------------------------------------------");

        Sleep(100);

    }

    ccolor(7);

}

void ccolor(int clr)
{

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, clr);

}


///HEERE PRINTF STYLE FUNCTION

void pwellcome()
{
    ccolor(7);

    char welcome[50]="WELCOME";
    char welcome2[50]=" TO";
    char welcome3[50]=" FOOD ORDER";
    char welcome4[50]=" MANAGEMENT SYSTEM";
    printf("\n\n\n\n\n\t\t\t");
    for(int wlc=0; wlc<strlen(welcome); wlc++)
    {
        ccolor(120+(wlc*9));

        printf(" %c",welcome[wlc]);
        Sleep(200);
    }
    ccolor(7);
    printf("\n\n\t\t\t\t ");
    for(int wlc2=0; wlc2<strlen(welcome2) ; wlc2++)
    {
        ccolor(160+(wlc2*9));

        printf(" %c",welcome2[wlc2]);
        Sleep(200);
    }
    ccolor(7);
    printf("\n\n\n\t\t\t ");
    for(int wlc3=0; wlc3<strlen(welcome3) ; wlc3++)
    {
        if(welcome3[wlc3]!='D')
        {
            ccolor(121+(wlc3*4));

            printf(" %c",welcome3[wlc3]);
        }
        else
        {
            ccolor(11);

            printf(" %c",welcome3[wlc3]);
        }

        Sleep(200);
    }
    ccolor(7);
    printf("\n\n\n\t\t\t\t ");
    for(int wlc3=0; wlc3<strlen(welcome4) ; wlc3++)
    {
        if(welcome4[wlc3]!='A' && welcome4[wlc3]!='E')
        {
            ccolor(121+(wlc3*4));

            printf(" %c",welcome4[wlc3]);
        }
        else
        {
            ccolor(11);

            printf(" %c",welcome4[wlc3]);
        }
        Sleep(200);
    }
    ccolor(7);

}
void loadingbar(void)
{

    for (int i=15; i<=100; i+=5)
    {

        cls();
        ccolor(7);

        printf("\n\n\n\n\n\n\n\t\t\t\t");
        printf("%d %% Loading...\n\n\t\t",i);

        printf("");

        for (int j=0; j<i; j+=2)
        {

            ccolor(160+j);
            printf(" ");
            ccolor(7);

        }
        Sleep(100);
        if(i==90 || i==50 || i==96 || i==83)
        {
            Sleep(100);
        }

    }

}
void backuploader(void)
{

    for (int i=15; i<=100; i+=5)
    {

        cls();
        ccolor(7);

        printf("\n\n\n\n\n\n\n\t\t\t\t");
        printf("%d %% Backing UP DATA...\n\n\t\t",i);

        printf("");

        for (int j=0; j<i; j+=2)
        {

            ccolor(120+j);
            printf(" ");
            ccolor(7);

        }
        Sleep(50);
        if(i==90 || i==50 || i==96 || i==83)
        {
            Sleep(50);
        }
    }

}

void middle1(void)
{

    printf("\n\n\n\n\n\n\n");
}

void middtab1(void)
{
    printf("\t\t\t\t\t");
}
