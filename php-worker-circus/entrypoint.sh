#!/bin/sh
exec gosu www-data circusd /tmp/circus/circus.ini

