CREATE TABLE IF NOT EXISTS Borrow (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    userId INTEGER NOT NULL,
    bookId INTEGER NOT NULL,
    borrowDate TEXT NOT NULL,
    returnDate TEXT,
    FOREIGN KEY (userId) REFERENCES AppUser(id),
    FOREIGN KEY (bookId) REFERENCES Book(id)
);

INSERT INTO Borrow
(userId, bookId, borrowDate, returnDate) VALUES (1, 1, '2024-10-25', '2024-10-26');