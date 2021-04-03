FROM nginx:alpine

LABEL maintainer="Mahmoud Zalt <mahmoud@zalt.me>"

#COPY nginx.conf /etc/nginx/

# If you're in China, or you need to change sources, will be set CHANGE_SOURCE to true in .env.

ARG CHANGE_SOURCE=false
RUN if [ ${CHANGE_SOURCE} = true ]; then \
    # Change application source from dl-cdn.alpinelinux.org to aliyun source
    sed -i 's/dl-cdn.alpinelinux.org/mirrors.aliyun.com/' /etc/apk/repositories \
;fi

RUN apk update \
    && apk upgrade \
    && apk --update add logrotate \
    && apk add --no-cache openssl \
    && apk add --no-cache bash

RUN apk add --no-cache curl

RUN set -x ; \
    addgroup -g 82 -S www-data ; \
    adduser -u 82 -D -S -G www-data www-data && exit 0 ; exit 1

ARG PHP_UPSTREAM_CONTAINER=php-fpm
ARG PHP_UPSTREAM_PORT=9000

# Create 'messages' file used from 'logrotate'
RUN touch /var/log/messages

# Copy 'logrotate' config file
COPY logrotate/nginx /etc/logrotate.d/

# Set upstream conf and remove the default conf
RUN echo "upstream php-upstream { server ${PHP_UPSTREAM_CONTAINER}:${PHP_UPSTREAM_PORT}; }" > /etc/nginx/conf.d/upstream.conf \
    && rm /etc/nginx/conf.d/default.conf

ADD ./startup.sh /opt/startup.sh
RUN sed -i 's/\r//g' /opt/startup.sh
CMD ["/bin/bash", "/opt/startup.sh"]

############## Install nginx-ultimate-bad-bot-blocker ##################################
USER root
RUN apk get update; \
    apk add curl wget; \
    mkdir -m 777 -p "/usr/local/sbin";
#because of wget --no-check-certificate secure problem cannot download package and install
RUN echo "check-certificate = off" >> /etc/wgetrc;

RUN wget https://raw.githubusercontent.com/mitchellkrogza/nginx-ultimate-bad-bot-blocker/master/install-ngxblocker -O /usr/local/sbin/install-ngxblocker; \
    chmod +x /usr/local/sbin/install-ngxblocker;\
    ./usr/local/sbin/install-ngxblocker -x; \
#    ls -l /usr/local/sbin/*; \
    chmod +x -R /usr/local/sbin;

############## Install nginx-ultimate-bad-bot-blocker finished ############################
#for test if it is alreay installed correctly
#for normal request
#curl -A "Mozilla/5.0 (Linux; Android 6.0.1; Nexus 5X Build/MMB29P) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.96 Mobile Safari/537.36 (compatible; Googlebot/2.1; +http://www.google.com/bot.html)" -I http://api.jianghu.me/
#curl -A "Mozilla/5.0 (compatible; bingbot/2.0; +http://www.bing.com/bingbot.htm)" -I http://api.jianghu.me/
#curl -I http://api.jianghu.me/

#for test abnormal request
#curl -A "Xenu Link Sleuth/1.3.8" -I http://api.jianghu.me/
#curl -A "Mozilla/5.0 (compatible; AhrefsBot/5.2; +http://ahrefs.com/robot/)" -I http://api.jianghu.me/
#curl -I http://api.jianghu.me/ -e http://100dollars-seo.com

EXPOSE 80 81 443
