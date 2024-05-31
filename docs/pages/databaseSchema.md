# Схема базы данных

[Home](../index.md)    
[Функциональные требования](functionalRequirements.md)  
[Диаграмма файлов приложения](applicationFileDiagram.md)  
[Дополнительная спецификация](additionalSpecification.md)   
[Схема базы данных](databaseSchema.md)  
[Презентация проекта](projectPresentation.md)          
[Ссылки на репозитории по курсу о GitHub Pages](linksToRepositories.md) 

# Схема базы данных

Схема базы данных:
![image](https://raw.githubusercontent.com/fpmi-tp2024/tpmp-rvn-lab5-smalldata/main/docs/db.jpg)

sql-файл:
```sql
CREATE TABLE workshops (
    workshop_id INTEGER PRIMARY KEY,
    workshop_address TEXT,
    brands TEXT  -- Перечень марок ремонтируемых машин, хранится в виде строки, разделенной ;
);

CREATE TABLE masters (
    master_id INTEGER PRIMARY KEY,
    name TEXT,
    workshop_id INTEGER,
    FOREIGN KEY (workshop_id) REFERENCES workshops(workshop_id)
);

CREATE TABLE cars (
    license_plate TEXT PRIMARY KEY,
    brand TEXT,
    year INTEGER,
    owner_last_name TEXT,
    tech_passport_number TEXT,
    owner_address TEXT
);

CREATE TABLE repairs (
    repair_id INTEGER PRIMARY KEY,
    workshop_id INTEGER,
    date_received DATE,
    date_completed DATE,
    license_plate TEXT,
    repair_type TEXT,
    repair_cost REAL,
    master_id INTEGER,
    FOREIGN KEY (workshop_id) REFERENCES workshops(workshop_id),
    FOREIGN KEY (license_plate) REFERENCES cars(license_plate),
    FOREIGN KEY (master_id) REFERENCES masters(master_id)
);
```