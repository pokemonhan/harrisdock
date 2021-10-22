FROM mongo:latest

LABEL maintainer="Mahmoud Zalt <mahmoud@zalt.me>"

#COPY mongo.conf /usr/local/etc/mongo/mongo.conf

VOLUME /data/db /data/configdb


COPY docker-entrypoint.sh /usr/bin/
#COPY ./seed/seed-data.js /docker-entrypoint-initdb.d/
COPY ./config/mongod.conf /etc/mongod.conf

CMD ["mongod"]

EXPOSE 27017

