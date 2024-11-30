import os
from datetime import datetime

class GroceryStore:
    def __init__(self):
        self.inventory = {
            "Rice": {"price": 50, "stock": 100},
            "Wheat": {"price": 40, "stock": 80},
            "Sugar": {"price": 45, "stock": 50},
            "Milk": {"price": 25, "stock": 30},
            "Oil": {"price": 120, "stock": 20}
        }
        self.cart = {}

    def display_inventory(self):
        print("\n--- Inventory ---")
        print(f"{'Item':<10}{'Price (Rs)':<12}{'Stock':<6}")
        for item, details in self.inventory.items():
            print(f"{item:<10}{details['price']:<12}{details['stock']:<6}")
        print("-----------------\n")

    def add_to_cart(self):
        self.display_inventory()
        item = input("Enter the name of the item you want to purchase: ").strip()
        if item in self.inventory:
            quantity = int(input(f"Enter quantity for {item}: "))
            if quantity <= self.inventory[item]["stock"]:
                if item in self.cart:
                    self.cart[item]["quantity"] += quantity
                else:
                    self.cart[item] = {
                        "price": self.inventory[item]["price"],
                        "quantity": quantity
                    }
                self.inventory[item]["stock"] -= quantity
                print(f"{quantity} units of {item} added to your cart.\n")
            else:
                print(f"Insufficient stock for {item}. Available: {self.inventory[item]['stock']} units.\n")
        else:
            print(f"{item} is not available in the inventory.\n")

    def save_bill_to_file(self, total, tax, discount, grand_total):
        filename = f"Bill_{datetime.now().strftime('%Y%m%d_%H%M%S')}.txt"
        with open(filename, "w") as file:
            file.write("----- Grocery Store Bill -----\n")
            file.write(f"{'Item':<10}{'Qty':<5}{'Price (Rs)':<12}{'Total (Rs)':<10}\n")
            for item, details in self.cart.items():
                item_total = details["price"] * details["quantity"]
                file.write(f"{item:<10}{details['quantity']:<5}{details['price']:<12}{item_total:<10}\n")
            file.write("-------------------------------\n")
            file.write(f"Subtotal: Rs {total:.2f}\n")
            file.write(f"Tax (5%): Rs {tax:.2f}\n")
            file.write(f"Discount: Rs {discount:.2f}\n")
            file.write(f"Grand Total: Rs {grand_total:.2f}\n")
            file.write("-------------------------------\n")
            file.write("Thank you! Visit Again.\n")
        print(f"Bill saved as '{filename}'. You can print it using a physical printer.\n")

    def generate_bill(self):
        if not self.cart:
            print("Your cart is empty!\n")
            return

        print("\n--- Bill ---")
        print(f"{'Item':<10}{'Qty':<5}{'Price (Rs)':<12}{'Total (Rs)':<10}")
        total = 0
        for item, details in self.cart.items():
            item_total = details["price"] * details["quantity"]
            total += item_total
            print(f"{item:<10}{details['quantity']:<5}{details['price']:<12}{item_total:<10}")

        tax = total * 0.05  # 5% tax
        discount = total * 0.1 if total > 500 else 0  # 10% discount if total > 500
        grand_total = total + tax - discount

        print("-------------------------------")
        print(f"Subtotal: Rs {total:.2f}")
        print(f"Tax (5%): Rs {tax:.2f}")
        print(f"Discount: Rs {discount:.2f}")
        print(f"Grand Total: Rs {grand_total:.2f}")
        print("-------------------------------\n")

        # Save the bill to a file
        self.save_bill_to_file(total, tax, discount, grand_total)

    def update_inventory(self):
        print("\n--- Update Inventory ---")
        item = input("Enter the name of the item: ").strip()
        if item in self.inventory:
            quantity = int(input(f"Enter stock quantity to add for {item}: "))
            self.inventory[item]["stock"] += quantity
            print(f"{quantity} units added to {item}'s stock.\n")
        else:
            price = float(input(f"Enter price for {item}: "))
            quantity = int(input(f"Enter initial stock for {item}: "))
            self.inventory[item] = {"price": price, "stock": quantity}
            print(f"New item {item} added to inventory.\n")

    def main_menu(self):
        while True:
            print("\n--- Grocery Store Management System ---")
            print("1. Display Inventory")
            print("2. Purchase Items")
            print("3. Generate Bill")
            print("4. Update Inventory")
            print("5. Exit")
            choice = input("Enter your choice: ")

            if choice == "1":
                self.display_inventory()
            elif choice == "2":
                self.add_to_cart()
            elif choice == "3":
                self.generate_bill()
            elif choice == "4":
                self.update_inventory()
            elif choice == "5":
                print("Thank you for using the Grocery Store Management System. Goodbye!")
                break
            else:
                print("Invalid choice. Please try again.\n")


if __name__ == "__main__":
    store = GroceryStore()
    store.main_menu()
