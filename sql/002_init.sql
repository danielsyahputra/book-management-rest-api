CREATE TABLE IF NOT EXISTS Book (
    id INTEGER PRIMARY KEY,
    title TEXT NOT NULL,
    author TEXT NOT NULL,
    publishedDate TEXT NOT NULL,
    description TEXT,
    isAvailable BOOLEAN NOT NULL DEFAULT TRUE
);