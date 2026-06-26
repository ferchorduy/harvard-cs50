-- Users
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    username TEXT NOT NULL,
    hash TEXT NOT NULL
);

CREATE UNIQUE INDEX username ON users (username);

-- -- Sessions
-- CREATE TABLE sessions (
--     user_id INTEGER NOT NULL,

--     FOREIGN KEY(user_id) REFERENCES users(id)
-- );

-- -- Exercises
-- CREATE TABLE exercises (
--     user_id INTEGER NOT NULL,
    
--     FOREIGN KEY(user_id) REFERENCES users(id)
-- );