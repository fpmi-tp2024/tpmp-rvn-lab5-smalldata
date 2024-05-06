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


INSERT INTO workshops (workshop_id, workshop_address, brands) VALUES
(1, '1234 Main St, Anytown, USA', 'Toyota;Nissan;Honda'),
(2, '5678 Second St, Anycity, USA', 'Ford;Chevy;Tesla');

INSERT INTO masters (master_id, name, workshop_id) VALUES
(1, 'John Doe', 1),
(2, 'Jane Smith', 1),
(3, 'Sam Brown', 2);

INSERT INTO cars (license_plate, brand, year, owner_last_name, tech_passport_number, owner_address) VALUES
('ABC123', 'Toyota', 2018, 'Johnson', 'TP123456', '4312 Third Ave, Anytown, USA'),
('XYZ789', 'Ford', 2020, 'Smith', 'TP654321', '8765 Fourth St, Anycity, USA');

INSERT INTO repairs (repair_id, workshop_id, date_received, date_completed, license_plate, repair_type, repair_cost, master_id) VALUES
(1, 1, '2023-04-01', '2023-04-10', 'ABC123', 'Engine Repair', 500.00, 1),
(2, 1, '2023-04-05', '2023-04-15', 'ABC123', 'Tire Replacement', 200.00, 2),
(3, 2, '2023-04-03', '2023-04-11', 'XYZ789', 'Battery Replacement', 300.00, 3);
