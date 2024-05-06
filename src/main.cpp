#include "services.h"


int main() {

    ConsoleManager consoleManager;

    const std::string username = consoleManager.promptString("Enter username: ");
    const std::string password = consoleManager.promptString("Enter password: ");

    AuthService authService("passwords.txt");

    if (!authService.authorize(username, password)) {
        std::cout << "Authorization failed. Application will exit.\n";
        return 0;
    }

    Database db("workshop.db");

    WorkshopService workshopService(db, consoleManager);
    MasterService masterService(db, consoleManager);
    CarService carService(db, consoleManager);
    RepairService repairService(db, consoleManager);

    int option = 0;
    while (true) {
        std::cout << "\n1. Add workshop\n" 
            "2. Show repairs by workshop\n"
            "3. Add master\n"
            "4. Add car\n"
            "5. Add repair\n"
            "6. Show repairs by master\n"
            "7. Show repairs by car brand\n"
            "8. Show summary of each workshop\n"
            "9. Show details of the top repair workshop\n"
            "10. Update car details\n"
            "11. Update master details\n"
            "12. Delete car\n"
            "13. Delete master\n"
            "14. Show works on a specific date for a workshop\n"
            "15. Show works by period and workshop\n"
            "16. Exit\n"
            "Choose an option: ";
        std::cin >> option;
        std::cin.ignore();

        switch (option) {
        case 1:
            workshopService.add_workshop();
            break;
        case 2:
            workshopService.show_repairs_by_workshop();
            break;
        case 3:
            masterService.add_master();
            break;
        case 4:
            carService.add_car();
            break;
        case 5:
            repairService.add_repair();
            break;
        case 6:
            repairService.show_repairs_by_master();
            break;
        case 7:
            repairService.show_repairs_by_brand();
            break;
        case 8:
            workshopService.show_workshop_summary();
            break;
        case 9:
            workshopService.show_top_workshop_details();
            break;
        case 10:
            carService.update_car();
            break;
        case 11:
            masterService.update_master();
            break;
        case 12:
            carService.delete_car();
            break;
        case 13:
            masterService.delete_master();
            break;
        case 14:
            workshopService.show_works_on_date_for_workshop();
            break;
        case 15:
            workshopService.show_works_by_period_and_workshop();
            break;
        case 16:
            std::cout << "Exiting the program.\n";
            return 0;
        default:
            std::cout << "Invalid option. Please try again.\n";
            break;
        }
    }

    return 0;
};
