BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "news" (
	"id"	INTEGER,
	"tag"	TEXT,
	"title"	TEXT,
	"source"	TEXT,
	"raw"	TEXT,
	PRIMARY KEY("id")
);
CREATE TABLE IF NOT EXISTS "seeds" (
	"id"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"category"	TEXT NOT NULL,
	"seed"	TEXT NOT NULL UNIQUE
);
COMMIT;
