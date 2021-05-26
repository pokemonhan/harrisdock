#!/bin/sh

#config generate-secret-key

#echo 'export SENTRY_SECRET_KEY = "xxxxxxx ......."' >> ~ / .bashrc
#source ~ / .bashrc
#echo $ SENTRY_SECRET_KEY
sentry run worker & sentry run cron &
