CREATE TABLE IF NOT EXISTS Book (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT NOT NULL,
    author TEXT NOT NULL,
    publishedDate TEXT NOT NULL,
    description TEXT,
    isAvailable BOOLEAN NOT NULL DEFAULT 1
);

INSERT INTO Book
(title, author, publishedDate, description, isAvailable) VALUES ("book1", "Daniel", "2024-10-25", "This is Book One", 1)