CREATE TABLE IF NOT EXISTS Borrow (
    id INTEGER PRIMARY KEY,
    userId INTEGER NOT NULL,
    bookId INTEGER NOT NULL,
    borrowDate TEXT NOT NULL,
    returnDate TEXT,
    FOREIGN KEY (userId) REFERENCES AppUser(id),
    FOREIGN KEY (bookId) REFERENCES Book(id)
);