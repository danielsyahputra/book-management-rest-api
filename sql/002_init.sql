CREATE TABLE IF NOT EXISTS Book (
    id INTEGER PRIMARY KEY,
    title TEXT NOT NULL,
    author TEXT NOT NULL,
    publishedDate TEXT NOT NULL,
    description TEXT,
    isAvailable BOOLEAN NOT NULL DEFAULT TRUE
);

INSERT INTO Book
(title, author, publishedDate, description, isAvailable) VALUES ("book1", "This is Book One", "Daniel", "2024-10-25", "This is Book One", "true")