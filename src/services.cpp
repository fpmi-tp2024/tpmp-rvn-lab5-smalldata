#include "services.h"


void WorkshopService::add_workshop() {
    std::string address = consoleManager.promptString("Enter workshop address: ");
    std::string brands = consoleManager.promptString("Enter list of brands (separated by ';'): ");
    std::string sql = "INSERT INTO workshops (workshop_address, brands) VALUES ('" + address + "', '" + brands + "');";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display("Workshop added successfully.");
    } else {
        consoleManager.display("Failed to add workshop.");
    }
}

void WorkshopService::show_repairs_by_workshop() {
    int workshopId = consoleManager.promptInt("Enter workshop ID: ");
    std::string startDate = consoleManager.promptString("Enter start date (YYYY-MM-DD): ");
    std::string endDate = consoleManager.promptString("Enter end date (YYYY-MM-DD): ");
    std::string sql = "SELECT m.name, r.repair_type, r.repair_cost FROM repairs r "
                    "JOIN masters m ON r.master_id = m.master_id "
                    "WHERE r.workshop_id = " + std::to_string(workshopId) +
                    " AND r.date_received >= '" + startDate +
                    "' AND r.date_completed <= '" + endDate + "';";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display(result);
    }
}

void WorkshopService::show_workshop_summary() {
    std::string sql = "SELECT w.workshop_id, w.workshop_address, COUNT(r.repair_id) AS total_repairs, SUM(r.repair_cost) AS total_revenue "
                    "FROM workshops w "
                    "LEFT JOIN repairs r ON w.workshop_id = r.workshop_id "
                    "GROUP BY w.workshop_id;";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display(result);
    }
}

void WorkshopService::show_top_workshop_details() {
    std::string sql = "SELECT w.workshop_id, w.workshop_address, m.name, c.brand, c.license_plate, r.date_received, r.date_completed, r.repair_type, r.repair_cost "
                    "FROM repairs r "
                    "JOIN workshops w ON r.workshop_id = w.workshop_id "
                    "JOIN masters m ON r.master_id = m.master_id "
                    "JOIN cars c ON r.license_plate = c.license_plate "
                    "WHERE w.workshop_id = (SELECT workshop_id FROM repairs "
                    "GROUP BY workshop_id ORDER BY COUNT(repair_id) DESC LIMIT 1);";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display(result);
    }
}

void WorkshopService::show_works_on_date_for_workshop() {
    int workshop_id = consoleManager.promptInt("Enter workshop ID: ");
    std::string date = consoleManager.promptString("Enter date (YYYY-MM-DD): ");
    std::string sql = "SELECT COUNT(*) AS number_of_repairs FROM repairs "
                    "WHERE workshop_id = " + std::to_string(workshop_id) + " AND "
                    "date_received <= '" + date + "' AND date_completed >= '" + date + "';";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display(result);
    }
}

void WorkshopService::show_works_by_period_and_workshop() {
    int workshop_id = consoleManager.promptInt("Enter workshop ID: ");
    std::string start_date = consoleManager.promptString("Enter start date (YYYY-MM-DD): ");
    std::string end_date = consoleManager.promptString("Enter end date (YYYY-MM-DD): ");
    std::string sql = "SELECT repair_type, COUNT(*) AS total_count "
                    "FROM repairs "
                    "WHERE workshop_id = " + std::to_string(workshop_id) + " AND "
                    "date_received >= '" + start_date + "' AND "
                    "date_completed <= '" + end_date + "' "
                    "GROUP BY repair_type;";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display(result);
    }
}


void MasterService::add_master() {
    std::string name = consoleManager.promptString("Enter master's name: ");
    int workshop_id = consoleManager.promptInt("Enter workshop ID: ");
    std::string sql = "INSERT INTO masters (name, workshop_id) VALUES ('" + name + "', " + std::to_string(workshop_id) + ");";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display(result);
    }
}

void MasterService::delete_master() {
    int master_id = consoleManager.promptInt("Enter master ID to delete: ");
    std::string sql = "DELETE FROM masters WHERE master_id = " + std::to_string(master_id) + ";";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display(result);
    }
}

void MasterService::update_master() {
    int master_id = consoleManager.promptInt("Enter master ID to delete: ");
    std::string new_name = consoleManager.promptString("Enter new master's name: ");
    int new_workshop_id = consoleManager.promptInt("Enter new workshop ID: "); 

    std::string sql = "UPDATE masters SET name = '" + new_name + "', workshop_id = " + std::to_string(new_workshop_id) +
                    " WHERE master_id = " + std::to_string(master_id) + ";";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display(result);
    }
}


void CarService::add_car() {
    std::string license_plate = consoleManager.promptString("Enter license plate: ");
    std::string brand = consoleManager.promptString("Enter car brand: ");
    std::string owner_last_name = consoleManager.promptString("Enter owner's last name: ");
    std::string tech_passport_number = consoleManager.promptString("Enter tech passport number: ");
    std::string owner_address = consoleManager.promptString("Enter owner's address: ");
    int year = consoleManager.promptInt("Enter car year: ");
    std::string sql = "INSERT INTO cars (license_plate, brand, year, owner_last_name, tech_passport_number, owner_address) VALUES ('" +
                    license_plate + "', '" + brand + "', " + std::to_string(year) + ", '" +
                    owner_last_name + "', '" + tech_passport_number + "', '" + owner_address + "');";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display(result);
    }
}

void CarService::update_car() {
    std::string license_plate = consoleManager.promptString("Enter license plate of the car to update: ");
    std::string new_brand = consoleManager.promptString("Enter new car brand: ");
    std::string new_owner_last_name = consoleManager.promptString("Enter new owner's last name: ");
    std::string new_tech_passport_number = consoleManager.promptString("Enter new tech passport number: ");
    std::string new_owner_address = consoleManager.promptString("Enter new owner's address: ");
    int new_year = consoleManager.promptInt("Enter new car year: ");
    std::string sql = "UPDATE cars SET brand = '" + new_brand + "', year = " + std::to_string(new_year) +
                    ", owner_last_name = '" + new_owner_last_name + "', tech_passport_number = '" + new_tech_passport_number +
                    "', owner_address = '" + new_owner_address + "' WHERE license_plate = '" + license_plate + "';";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display(result);
    }
}

void CarService::delete_car() {
    std::string license_plate = consoleManager.promptString("Enter license plate of the car to delete: ");
    std::string sql = "DELETE FROM cars WHERE license_plate = '" + license_plate + "';";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display(result);
    }
}


void RepairService::show_repairs_by_workshop() {
    int workshop_id = consoleManager.promptInt("Enter workshop ID: ");
    std::string start_date = consoleManager.promptString("Enter start date (YYYY-MM-DD): ");
    std::string end_date = consoleManager.promptString("Enter end date (YYYY-MM-DD): ");
    std::string sql = "SELECT m.name, r.repair_type, r.repair_cost FROM repairs r "
                    "JOIN masters m ON r.master_id = m.master_id "
                    "WHERE r.workshop_id = " + std::to_string(workshop_id) + 
                    " AND r.date_received >= '" + start_date + 
                    "' AND r.date_completed <= '" + end_date + "';";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display(result);
    }
}

void RepairService::show_repairs_by_master() {
    int master_id = consoleManager.promptInt("Enter master ID: ");

    std::string sql = "SELECT r.date_received, r.date_completed, r.repair_type, r.repair_cost, c.brand, c.license_plate "
                    "FROM repairs r JOIN cars c ON r.license_plate = c.license_plate "
                    "WHERE r.master_id = " + std::to_string(master_id) + ";";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display(result);
    }
}

void RepairService::show_repairs_by_brand() {
    std::string brand = consoleManager.promptString("Enter car brand: ");
    std::string sql = "SELECT w.workshop_id, r.date_received, r.date_completed, r.repair_type, m.name "
                    "FROM repairs r JOIN cars c ON r.license_plate = c.license_plate "
                    "JOIN workshops w ON r.workshop_id = w.workshop_id "
                    "JOIN masters m ON r.master_id = m.master_id "
                    "WHERE c.brand = '" + brand + "';";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display(result);
    }
}

void RepairService::add_repair() {
    int repair_id = consoleManager.promptInt("Enter repair ID: ");
    int workshop_id = consoleManager.promptInt("Enter workshop ID: ");
    int master_id = consoleManager.promptInt("Enter master ID: ");
    float repair_cost = consoleManager.promptFloat("Enter repair cost: ");
    std::string date_received = consoleManager.promptString("Enter date received (YYYY-MM-DD): "); 
    std::string date_completed = consoleManager.promptString("Enter date completed (YYYY-MM-DD): "); 
    std::string license_plate = consoleManager.promptString("Enter license plate: "); 
    std::string repair_type = consoleManager.promptString("Enter repair type: "); 

    std::string sql = "INSERT INTO repairs (repair_id, workshop_id, master_id, date_received, date_completed, license_plate, repair_type, repair_cost) VALUES (" +
                    std::to_string(repair_id) + ", " + std::to_string(workshop_id) + ", " + std::to_string(master_id) + ", '" +
                    date_received + "', '" + date_completed + "', '" + license_plate + "', '" + repair_type + "', " +
                    std::to_string(repair_cost) + ");";
    std::string result;
    if (db.execute(sql, result)) {
        consoleManager.display(result);
    }
}
