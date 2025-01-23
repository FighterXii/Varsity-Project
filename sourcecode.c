#include <stdio.h>
#include <math.h>
#include <string.h>

// Defining constants
#define MAX_LENGTH 1000
#define EOF (-1)

// jungle ka sher
float x = 0;
float *ptr = &x;
int quantityx = 0;
int *ptr1 = &quantityx;

// Structure for product
struct product
{
    char category[MAX_LENGTH], name[MAX_LENGTH];
    int code, quantity;
    float price;
};

// Function prototypes
void addCategory();
void addProduct();
void stockStatus();
float billing(float pc, int q, float ds);
void searchview();
void search();
void bill();
void chatbot();
void subchatbot();
void pre_order();
void order_view();
void in_pr_ls_count();
float m_count(float eb, int num_semp, float sose, int num_jemp, float soje, int num_nemp, float sone, float o_cost);
void p_day_inc();
float transport(float a);
// Function to add a category and then add products
void addCategory()
{
    struct product p;
    printf("Input Category: ");
    scanf(" %[^\n]", p.category);
    addProduct(p); // Pass the category to addProduct
}

// Function to add products to the file
void addProduct(struct product p)
{
    int c1;

    FILE *file = fopen("smart.txt", "a");
    if (file == NULL)
    {
        printf("Error 404! File not found\n");
        return;
    }
    else
    {
        printf("Assign product Info\n");
        printf("How many products do you want to add?\n");
        printf("Amount: ");
        scanf("%d", &c1);

        for (int i = 1; i <= c1; i++)
        {
            printf("\nInput Name: ");
            scanf(" %[^\n]", p.name);
            printf("Input Product Code: ");
            scanf("%d", &p.code);
            printf("Input Product Price: ");
            scanf("%f", &p.price);
            printf("Input Product Quantity: ");
            scanf("%d", &p.quantity);

            // Write product details to the file
            fprintf(file, "Category: %s\nName: %s\nCode: %d\nPrice: %.3f\nQuantity: %d\n\n",
                    p.category, p.name, p.code, p.price, p.quantity);
        }

        fclose(file);
    }
}

// Function to display stock status from the file
void stockStatus()
{
    struct product p;
    FILE *file = fopen("smart.txt", "r");

    if (file == NULL)
    {
        printf("File not found\n");
        return;
    }

    printf("\nProduct Details:\n");
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf(" || Product Catagory || Product Name         || Product Code  || Product Price  || Avaiable Quantity ||    \n");
    printf("---------------------------------------------------------------------------------------------------------\n");

    while (fscanf(file, "Category: %[^\n]\nName: %[^\n]\nCode: %d\nPrice: %f\nQuantity: %d\n\n",
                  p.category, p.name, &p.code, &p.price, &p.quantity) != EOF)
    {
        printf("| %-20s | %-20s | %-14d | %-14.2f | %-16d |\n\n", p.category, p.name, p.code, p.price, p.quantity);
    }

    fclose(file);
}

// Function to show catagory name and code
void searchview()
{
    // varriables
    char searchCategory[50];
    int c2;
    // Flag
    int found = 0;

    search();
    struct product p;
    FILE *file = fopen("smart.txt", "r");

    if (file == NULL)
    {
        printf("File not found\n");
        return;
    }

    // Ask user for category input
    printf("\nEnter category to search: ");
    scanf("%s", searchCategory);
    printf("\nProducts under category '%s':\n", searchCategory);
    printf("---------------------------------------------------------\n");
    printf("| Product Name          | Product Code || Product Price |\n");
    printf("---------------------------------------------------------\n");

    while (fscanf(file, "Category: %[^\n]\nName: %[^\n]\nCode: %d\nPrice: %f\nQuantity: %d\n\n",
                  p.category, p.name, &p.code, &p.price, &p.quantity) != EOF)
    {
        if (strcmp(p.category, searchCategory) == 0)
        {
            printf("| %-20s | %-12d | %-20f |\n", p.name, p.code, p.price);
            found = 1;
        }
    }
    // If no products were found under the category
    if (!found)
    {
        printf("No products found under this category.\n");
    }
    fclose(file);
    printf("\n\nPress 1 to enter Billing Machine: ");
    scanf("%d", &c2);
    switch (c2)
    {
    case 1:
        bill();
        break;

    default:
        break;
    }
}

// sub function of view search system
void search()
{

    struct product p;
    FILE *file = fopen("smart.txt", "r");

    if (file == NULL)
    {
        printf("File not found\n");
        return;
    }
    printf("\nCategories :\n");
    while (fscanf(file, "Category: %[^\n]\nName: %[^\n]\nCode: %d\nPrice: %f\nQuantity: %d\n\n",
                  p.category, p.name, &p.code, &p.price, &p.quantity) != EOF)
    {
        printf("-%s\n", p.category);
    }
}
// bill details store:
// struct
//  function for billing system
struct oph
{
    char p_name[MAX_LENGTH];
    int p_quantity;
    float p_price;
    double p_dis;
    double b_ammount;
    int day, month, year;
};
void up_stock()
{
    int searchcode;
    struct product p;

    printf("Enter product code: ");
    scanf("%d", &searchcode);

    FILE *file = fopen("smart.txt", "r");
    if (file == NULL)
    {
        printf("File not found\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error creating temporary file!\n");
        fclose(file);
        return;
    }

    int found = 0;
    while (fscanf(file, "Category: %[^\n]\nName: %[^\n]\nCode: %d\nPrice: %f\nQuantity: %d\n\n",
                  p.category, p.name, &p.code, &p.price, &p.quantity) != EOF)
    {
        if (searchcode == p.code)
        {
            found = 1;
            p.quantity -= quantityx;
            if (p.quantity < 0)
            {
                printf("Error: Not enough stock available for product code %d.\n", searchcode);
                fclose(file);
                fclose(tempFile);
                remove("temp.txt");
                return;
            }
            printf("Stock updated for product code %d. New quantity: %d\n", p.code, p.quantity);
        }

        fprintf(tempFile, "Category: %s\n", p.category);
        fprintf(tempFile, "Name: %s\n", p.name);
        fprintf(tempFile, "Code: %d\n", p.code);
        fprintf(tempFile, "Price: %.2f\n", p.price);
        fprintf(tempFile, "Quantity: %d\n\n", p.quantity);
    }

    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        printf("Product with code %d not found.\n", searchcode);
        remove("temp.txt");
    }
    else
    {

        remove("smart.txt");
        rename("temp.txt", "smart.txt");
        printf("Stock updated successfully!\n");
    }
}

void bill()
{
    // varriables
    struct oph p;
    // int q;
    // char name[MAX_LENGTH];
    // float p, d, ammount;
    FILE *file = fopen("bhd.txt", "a");
    if (file == NULL)
    {
        printf("Error 404! File not found\n");
        return;
    }
    else
    {

        printf("*** Bill Machine ***\n\n");
        printf("Today's Date:\nDay: ");
        scanf("%d", &p.day);
        printf("Month: ");
        scanf("%d", &p.month);
        printf("Year: ");
        scanf("%d", &p.year);
        printf("Enter Product Name: ");
        scanf(" %[^\n]", &p.p_name);
        printf("Enter Product Price: ");
        scanf("%f", &p.p_price);
        printf("Enter Product Quantity: ");
        scanf("%d", &p.p_quantity);
        *ptr1 = p.p_quantity;
        printf("Enter Amount of Discount: ");
        scanf("%lf", &p.p_dis);
        p.b_ammount = billing(p.p_price, p.p_quantity, p.p_dis);
        printf("\n\n");
        printf("**Bill Summary**\n\n");
        printf("Product Name : %s\n", p.p_name);
        printf("Product Quantity: %d\n", p.p_quantity);
        printf("Total: %0.2lf\n\n", p.b_ammount);
        fprintf(file, "Date: %d-%d-%d\nProduct Name: %s\n\nPrice: %f\nQuantity: %d\nDiscount: %.2lf\nBill ammount: %.2lf\n\n",
                p.day, p.month, p.year, p.p_name, p.p_price, p.p_quantity, p.p_dis, p.b_ammount);
    }
    fclose(file);
    up_stock();
}

// Bill machine code
float billing(float pc, int q, float ds)
{
    float sum = 0;
    float upc = pc * q;
    sum = sum + upc;
    float min = sum * (ds / 100.00);
    double final = sum - min;
    return final;
}

// chat bot
// sub function
void subchatbot()
{
    // varriables
    char searchname[MAX_LENGTH];
    // Flag
    int found1 = 0;
    struct product p;
    FILE *file = fopen("smart.txt", "r");

    if (file == NULL)
    {
        printf("File not found\n");
        return;
    }
    printf("\nEnter the product name: ");
    scanf("%s", searchname);
    printf("\nProduct Data of '%s':\n", searchname);

    while (fscanf(file, "Category: %[^\n]\nName: %[^\n]\nCode: %d\nPrice: %f\nQuantity: %d\n\n",
                  p.category, p.name, &p.code, &p.price, &p.quantity) != EOF)
    {
        if (strcmp(p.name, searchname) == 0)
        {
            printf("Product name is %s.\nProduct code is %d.\nProduct price is %0.2f tk per unit.\n", p.name, p.code, p.price);
            found1 = 1;
        }
    }
    if (!found1)
    {
        printf("No products found.\n");
    }

    fclose(file);
}
// main function
void chatbot()
{
    int c3;
    printf("Chatbot: Hi! I am a static assitant to you.\nAsk me about which product you want to search in your stock.\nInput the product name only.\n");
    subchatbot();
    printf("Do you want to search anything? Enter 1 if you want to continue else enter 0.\n");
    printf("Enter: ");
    scanf("%d", &c3);
    switch (c3)
    {
    case 1:
        subchatbot();
        break;

    default:
        break;
    }
}
// structure for pre-order
struct order_product
{

    char category[MAX_LENGTH];
    char adress[MAX_LENGTH];
    char cname[MAX_LENGTH];
    char pname[MAX_LENGTH];
    int order_num;
    int code;
    int quantity;
    float price;
    float discount;
    float order_bill;
    int day;
    int month;
    int year;
};

// Function for pre-order
void pre_order()
{
    int c4;
    struct order_product op;

    printf("Do you need to access Chat-Bot?\n");
    printf("Yes = 1 || No = 0\n\n");
    printf("Enter: ");
    scanf("%d", &c4);
    getchar(); // Consume newline left in the buffer

    switch (c4)
    {
    case 1:
        chatbot();
        break;
    case 0:
        break;
    }

    FILE *file = fopen("order.txt", "a");
    if (file == NULL)
    {
        printf("Error 404! File not found\n");
        return;
    }

    printf("Input Order Number: ");
    scanf("%d", &op.order_num);
    getchar(); // Consume newline

    printf("\nInput Customer's Name: ");
    fgets(op.cname, sizeof(op.cname), stdin);
    op.cname[strcspn(op.cname, "\n")] = '\0';

    printf("Input Delivery Address: ");
    fgets(op.adress, sizeof(op.adress), stdin);
    op.adress[strcspn(op.adress, "\n")] = '\0';

    printf("\nInput Product Name: ");
    fgets(op.pname, sizeof(op.pname), stdin);
    op.pname[strcspn(op.pname, "\n")] = '\0';

    printf("\nInput Product Code: ");
    scanf("%d", &op.code);

    printf("Input Product Price: ");
    scanf("%f", &op.price);

    printf("Input Product Quantity: ");
    scanf("%d", &op.quantity);

    printf("Input Discount: ");
    scanf("%f", &op.discount);

    printf("Input Expected Delivery Date:\n");
    printf("Day: ");
    scanf("%d", &op.day);
    printf("Month: ");
    scanf("%d", &op.month);
    printf("Year: ");
    scanf("%d", &op.year);

    op.order_bill = billing(op.price, op.quantity, op.discount);

    // Write product details to the file
    fprintf(file, "Order Number: %d\nCustomer's Name: %s\nCustomer's Address: %s\nProduct Code: %d\nProduct Name: %s\nProduct Price: %.2f\nQuantity: %d\nApplied Discount: %.2f\nBill Amount: %.3f\nDelivery Date: %02d/%02d/%04d\n\n",
            op.order_num, op.cname, op.adress, op.code, op.pname, op.price, op.quantity, op.discount, op.order_bill, op.day, op.month, op.year);

    fclose(file);
}

void order_view()
{
    struct order_product op;
    FILE *file = fopen("order.txt", "r");

    if (file == NULL)
    {
        printf("File not found\n");
        return;
    }

    char line[200]; // Buffer to read lines
    while (fgets(line, sizeof(line), file))
    {
        // Read each field line by line
        if (sscanf(line, "Order Number: %d", &op.order_num) == 1)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, "Customer's Name: %[^\n]", op.cname);

            fgets(line, sizeof(line), file);
            sscanf(line, "Customer's Address: %[^\n]", op.adress);

            fgets(line, sizeof(line), file);
            sscanf(line, "Product Code: %d", &op.code);

            fgets(line, sizeof(line), file);
            sscanf(line, "Product Name: %[^\n]", op.pname);

            fgets(line, sizeof(line), file);
            sscanf(line, "Product Price: %f", &op.price);

            fgets(line, sizeof(line), file);
            sscanf(line, "Quantity: %d", &op.quantity);

            fgets(line, sizeof(line), file);
            sscanf(line, "Applied Discount: %f", &op.discount);

            fgets(line, sizeof(line), file);
            sscanf(line, "Bill Amount: %f", &op.order_bill);

            fgets(line, sizeof(line), file);
            sscanf(line, "Delivery Date: %d-%d-%d", &op.day, &op.month, &op.year);

            // Print the order details
            printf("--------------------------------------------------------\n");
            printf("||Order Number: %d ||\n", op.order_num);
            printf("--------------------------------------------------------\n");
            printf("Customer's Name: %s\nCustomer's Address: %s\n", op.cname, op.adress);
            printf("Product Code: %d\nProduct Name: %s\nProduct Price: %.2f\n", op.code, op.pname, op.price);
            printf("Quantity: %d\nApplied Discount: %.2f\nBill Amount: %.2f\n", op.quantity, op.discount, op.order_bill);
            printf("Delivery Date: %02d-%02d-%04d\n", op.day, op.month, op.year);
            printf("--------------------------------------------------------\n");
        }
    }
    fclose(file);
}

// Income profit & loss
void p_day_inc()
{
    struct oph p;
    FILE *file = fopen("bhd.txt", "r");

    if (file == NULL)
    {
        printf("File not found\n");
        return;
    }

    int s_day, s_month, s_year;
    printf("\nEnter Date (DD-MM-YYYY):\n");
    scanf("%d-%d-%d", &s_day, &s_month, &s_year);

    char line[MAX_LENGTH];
    int c5 = 0;
    float total = 0.0;

    while (fgets(line, sizeof(line), file))
    {

        if (sscanf(line, "Date: %d-%d-%d", &p.day, &p.month, &p.year) == 3)
        {

            printf("Parsed Date: %02d-%02d-%04d\n", p.day, p.month, p.year);

            if (p.day == s_day && p.month == s_month && p.year == s_year)
            {

                printf("Match Found for Date: %02d/%02d/%04d\n", p.day, p.month, p.year);

                fgets(line, sizeof(line), file);
                sscanf(line, "Product Name: %[^\n]", &p.p_name);

                fgets(line, sizeof(line), file);
                sscanf(line, "Price: %f", &p.p_price);

                fgets(line, sizeof(line), file);
                sscanf(line, "Quantity: %d", &p.p_quantity);

                fgets(line, sizeof(line), file);
                sscanf(line, "Discount: %lf", &p.p_dis);

                fgets(line, sizeof(line), file);
                sscanf(line, "Bill ammount: %lf", &p.b_ammount);

                // Income of a day
                total = total + p.b_ammount;

                // Print the bill details

                printf("\nDate: %02d-%02d-%04d\n", p.day, p.month, p.year);
                printf("Product Name: %s\n", p.p_name);
                printf("Price: %f\n", p.p_price);
                printf("Quantity: %d\n", p.p_quantity);
                printf("Discount: %.2lf\n", p.p_dis);
                printf("Bill ammount: %.2lf\n", p.b_ammount);

                c5 = 1;
            }
        }
    }

    if (c5)
    {
        printf("\nTotal Bill Amount for %02d-%02d-%04d: %.2f\n", s_day, s_month, s_year, total);
        *ptr = total;
    }
    else
    {
        printf("No bills found for the entered date.\n");
    }

    fclose(file);
}

void in_pr_ls_count()
{
    float elec_bill;
    float Sal_O_SEmp;
    int Num_SEmp;
    float Sal_O_JEmp;
    int Num_JEmp;
    float Sal_O_NEmp;
    int Num_NEmp;
    float o_cost;
    float final_cost;
    printf("\nLet's Count Maintenance Cost: (Per Day)\n\n");
    printf("\nInput Electricity Bill Amount: ");
    scanf("%f", &elec_bill);
    printf("\nInput Number of Senior Employ: ");
    scanf("%d", &Num_SEmp);
    printf("\nInput Salary For Senior Employ: ");
    scanf("%f", &Sal_O_SEmp);
    printf("\nInput Number of Junior Employ: ");
    scanf("%d", &Num_JEmp);
    printf("\nInput Salary For Junior Employ: ");
    scanf("%f", &Sal_O_JEmp);
    printf("\nInput Number of New Employ: ");
    scanf("%d", &Num_NEmp);
    printf("\nInput Salary For New Employ: ");
    scanf("%f", &Sal_O_NEmp);
    printf("\nInput Amount of Other Cost: ");
    scanf("%f", &o_cost);
    final_cost = m_count(elec_bill, Num_SEmp, Sal_O_SEmp, Num_JEmp, Sal_O_JEmp, Num_NEmp, Sal_O_NEmp, o_cost);
    printf("\nMaintenance Cost: %.3f", final_cost);
    printf("Todays Income : \n");
    p_day_inc();

    float total_p_l = x - final_cost;

    if (total_p_l >= 0)
    {
        printf("Your Profit Amount is %.3f tk\n", total_p_l);
    }
    else
    {

        printf("You are in loss. Your loss amount is %.3f tk\n", fabs(total_p_l));
    }
}

// maintaince cost count
float m_count(float eb, int num_semp, float sose, int num_jemp, float soje, int num_nemp, float sone, float o_cost)
{
    float m_cost = eb + (sose * num_semp) + (soje * num_jemp) + (sone * num_nemp) + o_cost;
    return m_cost;
}

// Main function
int main()
{
    // varriable for switch access
    // main switch
    int choice1;
    // nested switch
    int choice2, choice4, choice6, choice8;

    // varriable for other works
    int v1;

    printf("\n\n*** WELCOME TO SMART SHOP MANAGEMENT SYSTEM ***\n\n");
    while (1)
    {
        printf("\nSelect Your Option-\n");
        printf("1. Stock Management\n");
        printf("2. Billing System \n");
        printf("3. Pre-order System \n");
        printf("4. Income & Profit \n\n");
        printf("Choose Your Option : ");
        scanf("%d", &choice1);
        printf("\n\n");
        switch (choice1)
        {
        case 1:
            printf("//*Started Stock Management*//\n\n");
            printf("Menu:\n1. Input data of stock\n2. Available Stock Status\n\n");
            printf("Choose Your Option :");
            scanf("%d", &choice2);
            printf("\n\n");
            switch (choice2)
            {
            case 1:
                addCategory();
                break;
            case 2:
                stockStatus();
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            break;

        case 2:
            printf("//*Started Billing System*//\n\n");
            printf("Menu: \n1.Show Catagories\n");
            printf("Enter: { Yes - 1 / No - 0 / Bill Machine - 2 }\n");
            scanf("%d", &choice4);
            switch (choice4)
            {
            case 1:
                searchview();
                break;
            case 2:
                bill();
                break;
            }
            break;
        case 3:
            printf("//*Started Pre-order System*//\n\n");
            printf("1.Chat-Bot\n");
            printf("2.Pre-order\n");
            printf("3.Order Dairy\n\n");
            printf("Enter: ");
            scanf("%d", &choice6);
            switch (choice6)
            {
            case 1:
                chatbot();
                break;
            case 2:
                pre_order();
                break;
            case 3:
                order_view();
                break;

            default:
                break;
            }
            break;
        case 4:
            printf("//**Income & Profit-Loss**//\n");
            printf("1.Income & Profit/Loss Count [Per Day]\n");
            printf("2.Bill History\n");
            printf("Enter : ");
            scanf("%d", &choice8);
            switch (choice8)
            {

            case 1:

                printf("Income & Profit/Loss Count\n");
                in_pr_ls_count();

                break;

            case 2:
                p_day_inc();
                break;

            default:
                break;
            }
            break;
        }
    }

    return 0;
}
