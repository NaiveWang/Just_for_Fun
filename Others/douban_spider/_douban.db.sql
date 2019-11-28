BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "comments" (
	"id"	INTEGER,
	"pid"	INTEGER,
	"uid"	INTEGER,
	"text"	TEXT,
	"create_time"	TEXT,
	"parent_comment_id"	INTEGER,
	PRIMARY KEY("id")
);
CREATE TABLE IF NOT EXISTS "post" (
	"uri"	TEXT,
	"id"	INTEGER,
	"topic"	INTEGER,
	"author" INTEGER,
	"text"	TEXT,
	"comments_count"	INTEGER,
	"create_time"	TEXT,
	"like_count"	INTEGER,
	"tag"  INTEGER,
	PRIMARY KEY("uri")
);
CREATE TABLE IF NOT EXISTS "user" (
	"id"	INTEGER UNIQUE,
	"uid"	TEXT,
	"name"	TEXT,
	"url_avatar"	TEXT,
	"loc"	INTEGER,
	PRIMARY KEY("id")
);
CREATE TABLE IF NOT EXISTS "topic" (
	"id"	INTEGER,
	"title"	INTEGER,
	PRIMARY KEY("id")
);
CREATE TABLE IF NOT EXISTS "img" (
	"pid"	INTEGER,
	"url"	TEXT
);
CREATE TABLE IF NOT EXISTS "loc" (
	"id"	INTEGER UNIQUE,
	"name"	TEXT,
	"uid"	TEXT,
	PRIMARY KEY("id")
);
COMMIT;
