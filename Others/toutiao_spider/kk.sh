#!/bin/bash
sqlite3 toutiao.db "select count(*) from news where raw is not null"
sqlite3 toutiao.db "select count(*) from news where raw is null"
sqlite3 toutiao.db "select tag, count(*) from news where raw is not null group by tag order by count(*)"
