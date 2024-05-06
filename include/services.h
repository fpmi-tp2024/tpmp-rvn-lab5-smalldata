#ifndef SERVICES_H
#define SERVICES_H

#include "database.h"
#include "console_manager.h"
#include "auth.h"


class WorkshopService {
public:
    explicit WorkshopService(Database& db, ConsoleManager consoleManager) : db(db), consoleManager(consoleManager) {}
    void add_workshop();
    void show_repairs_by_workshop();
    void show_workshop_summary();
    void show_top_workshop_details();
    void show_works_on_date_for_workshop();
    void show_works_by_period_and_workshop();
private:
    Database& db;
    ConsoleManager& consoleManager;
};


class MasterService {
public:
    explicit MasterService(Database& db, ConsoleManager consoleManager) : db(db), consoleManager(consoleManager) {};
    void add_master();
    void delete_master();
    void update_master();
private:
    Database& db;
    ConsoleManager& consoleManager;
};


class CarService {
public:
    explicit CarService(Database& db, ConsoleManager consoleManager) : db(db), consoleManager(consoleManager) {};
    void add_car();
    void update_car();
    void delete_car();
private:
    Database& db;
    ConsoleManager& consoleManager;
};


class RepairService {
public:
    explicit RepairService(Database& db, ConsoleManager consoleManager) : db(db), consoleManager(consoleManager) {};
    void show_repairs_by_workshop();
    void show_repairs_by_master();
    void show_repairs_by_brand();
    void add_repair();
private:
    Database& db;
    ConsoleManager& consoleManager;
};


#endif
