#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 500

typedef struct {
    char name[30];
    float price;
    int quantity;
} MenuItem;

void displayMenu(MenuItem menu[], int size) {
    printf("\n----- MENU -----\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s - Rs %.2f\n", i + 1, menu[i].name, menu[i].price);
    }
    printf("----------------\n");
}

void generateBill(MenuItem orders[], int orderCount) {
    float total = 0, tax = 0, discount = 0, grandTotal = 0;
    printf("\n----- BILL -----\n");
    printf("%-20s %-10s %-10s\n", "Item", "Qty", "Price");

    for (int i = 0; i < orderCount; i++) {
        float itemCost = orders[i].price * orders[i].quantity;
        printf("%-20s %-10d Rs %-10.2f\n", orders[i].name, orders[i].quantity, itemCost);
        total += itemCost;
    }

    tax = total * 0.05;  // 5% tax
    if (total > 500) {
        discount = total * 0.1;  // 10% discount on orders above Rs 500
    }
    grandTotal = total + tax - discount;

    printf("-----------------------------\n");
    printf("Subtotal: Rs %.2f\n", total);
    printf("Tax (5%%): Rs %.2f\n", tax);
    printf("Discount: Rs %.2f\n", discount);
    printf("Grand Total: Rs %.2f\n", grandTotal);
    printf("-----------------------------\n");
    printf("Thank you! Visit Again.\n");
}

int main() {
    MenuItem menu[] = {
        {"Burger", 150.00, 0},
        {"Pizza", 300.00, 0},
        {"Pasta", 250.00, 0},
        {"Cold Drink", 50.00, 0},
        {"Ice Cream", 100.00, 0}
    };
    int menuSize = sizeof(menu) / sizeof(menu[0]);

    MenuItem orders[MAX_ITEMS];
    int orderCount = 0, choice, quantity;

    while (1) {
        printf("\nRestaurant Billing System\n");
        printf("1. View Menu\n");
        printf("2. Order Items\n");
        printf("3. Generate Bill\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMenu(menu, menuSize);
                break;
            case 2:
                displayMenu(menu, menuSize);
                printf("Enter item number to order (0 to stop): ");
                scanf("%d", &choice);
                if (choice == 0) break;

                if (choice > 0 && choice <= menuSize) {
                    printf("Enter quantity for %s: ", menu[choice - 1].name);
                    scanf("%d", &quantity);

                    orders[orderCount] = menu[choice - 1];
                    orders[orderCount].quantity = quantity;
                    orderCount++;
                } else {
                    printf("Invalid choice. Try again.\n");
                }
                break;
            case 3:
                if (orderCount > 0) {
                    generateBill(orders, orderCount);
                } else {
                    printf("No items ordered yet.\n");
                }
                break;
            case 4:
                printf("Exiting the program. Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
