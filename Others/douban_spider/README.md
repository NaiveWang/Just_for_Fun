# rating system for douban v0.1

## usage

#### startup

1. download the database file `douban` and make sure it is not locked.

2. download `web_wrapper.py` and the whole `templates` directory, and put them at the same directory as db's.

3. open a terminal and change the directory to current directory, make sure you have python-flask(`pip install flask`) installed, then run command `python webserver.py`. Now the local flask server should have been started.

4. open a browser tab, open the url`localhost:5000`, now the page should be the rating hub.

#### buttons

1. `这篇不要了` drop current post since it is too short or for other reasons. This operation will set the **tag** value to `-1`.

2. `*傻逼*` rates the post from setting tag value from `1` to `3`
