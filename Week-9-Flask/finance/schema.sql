-- Users
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    username TEXT NOT NULL,
    hash TEXT NOT NULL,
    cash NUMERIC NOT NULL DEFAULT 10000.00
);

CREATE UNIQUE INDEX username ON users (username);

-- Stock transactions
CREATE TABLE transactions (
    user_id INTEGER NOT NULL,
    ticker TEXT NOT NULL,
    price REAL NOT NULL,
    shares INTEGER NOT NULL,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY(user_id) REFERENCES users(id)
);

CREATE INDEX transactions_user_id ON transactions (user_id);

-- Cash movements
CREATE TABLE cash_movements (
    user_id INTEGER NOT NULL,
    movement_type TEXT NOT NULL CHECK(movement_type IN ('deposit', 'withdrawal')),
    amount REAL NOT NULL,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY(user_id) REFERENCES users(id)
);

CREATE INDEX cash_movements_user_id ON cash_movements (user_id);