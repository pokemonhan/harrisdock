#!/bin/sh
exec gosu www-data circusd /var/www/live_circus/circus.ini
