FROM php:7.3-fpm
#COPY ./aliyun.sources.list /etc/apt/sources.list
# If you're in China, or you need to change sources, will be set CHANGE_SOURCE to true in .env.

ARG CHANGE_SOURCE=false
ARG UBUNTU_SOURCE=aliyun
COPY ./sources.sh /tmp/sources.sh
RUN if [ ${CHANGE_SOURCE} = true ]; then \
    # Change application source from deb.debian.org to aliyun source
    sed -i 's/deb.debian.org/mirrors.tuna.tsinghua.edu.cn/' /etc/apt/sources.list; \
    sed -i 's/security.debian.org/mirrors.tuna.tsinghua.edu.cn/' /etc/apt/sources.list; \
    sed -i 's/security-cdn.debian.org/mirrors.tuna.tsinghua.edu.cn/' /etc/apt/sources.list; \
    chmod +x /tmp/sources.sh; \
    /bin/sh -c /tmp/sources.sh; \
  fi; \
  rm -rf /tmp/sources.sh

###########################################################################
# Set Timezone
###########################################################################

ARG TZ=UTC
ENV TZ ${TZ}

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN set -eux; \
        apt-get update; \
        apt-get upgrade -y; \
        apt-get install -y --no-install-recommends \
                curl \
                libmemcached-dev \
                libz-dev \
                libpq-dev \
                libjpeg-dev \
                libpng-dev \
                libfreetype6-dev \
                libssl-dev \
                libmcrypt-dev; \
        rm -rf /var/lib/apt/lists/* ;\
        # Install the PHP pdo_mysql extention
        docker-php-ext-install pdo_mysql; \
        php -m; \
        # Install the PHP gd library
        docker-php-ext-configure gd \
                --with-jpeg-dir=/usr/lib \
                --with-freetype-dir=/usr/include/freetype2; \
        docker-php-ext-install gd; \
        php -r 'var_dump(gd_info());'

RUN apt-get update && apt-get -yqq install libzip-dev \
    unzip \
    python3 \
    python3-pip \
    gosu \
    vim \
    cmake

# Should Install sockets bcmath
RUN docker-php-ext-install pdo_mysql bcmath sockets zip

#RUN printf "\n" | pecl install -o -f redis \
#    && rm -rf /tmp/pear \
#    && docker-php-ext-enable redis

RUN printf "\n" | curl --insecure -L 'http://pecl.php.net/get/redis-5.3.4.tgz' -o redis-5.3.4.tgz \
  && pecl install redis-5.3.4.tgz \
  &&  rm -rf redis-5.3.4.tgz \
  &&  rm -rf /tmp/pear \
  &&  docker-php-ext-enable redis

 # download and install manually, to make sure it's compatible with ampq installed by pecl later
    # install cmake first
RUN curl --insecure -L -o /tmp/rabbitmq-c.tar.gz https://github.com/alanxz/rabbitmq-c/archive/master.tar.gz && \
    mkdir -p rabbitmq-c && \
    tar -C rabbitmq-c -zxvf /tmp/rabbitmq-c.tar.gz --strip 1 && \
    cd rabbitmq-c/ && \
    mkdir _build && cd _build/ && \
    cmake .. && \
    cmake --build . --target install
    # Install the amqp extension
#RUN pecl install amqp && \
#    docker-php-ext-enable amqp

RUN printf "\n" | curl --insecure -L 'http://pecl.php.net/get/amqp-1.10.2.tgz' -o amqp-1.10.2.tgz \
  && pecl install amqp-1.10.2.tgz \
  &&  rm -rf amqp-1.10.2.tgz \
  &&  rm -rf /tmp/pear \
  &&  docker-php-ext-enable amqp

#RUN curl --insecure -sS https://getcomposer.org/installer > /tmp/composer-setup && \
#    php /tmp/composer-setup --install-dir=/usr/bin --filename=composer

COPY ./php-composer/installer /tmp/composer-setup
RUN php /tmp/composer-setup --install-dir=/usr/bin --filename=composer

#https://pypi.org/simple/circus/
#https://developer.aliyun.com/article/652884
RUN pip3 --no-cache-dir --trusted-host mirrors.aliyun.com install circus circus-web -i https://mirrors.aliyun.com/pypi/simple/

COPY ./entrypoint.sh /data/
RUN chmod +x /data/entrypoint.sh

###########################################################################
# Circus Configuration ini files
# /etc/init/circus.conf.
#**References : https://github.com/corydodt/circus-base/blob/master/circus.ini
#            from https://github.com/corydodt/circus-base
#References : https://github.com/circus-tent/circus/issues/926
#Official Doc :https://circus.readthedocs.io/en/latest/for-ops/deployment/
#Referenceds : https://github.com/rongfengliang/circus-docker
###########################################################################

#从外面编辑crontab 不需要拷贝到里面去执行
USER root

#COPY ./crontab /etc/cron.d
RUN  mkdir /tmp/circus/
COPY ./circus.ini /tmp/circus/
RUN ls -la /tmp/circus/*

COPY ./config /etc/circus.d
RUN ls -la /etc/circus.d/*

EXPOSE 8080 9999
ENTRYPOINT ["/data/entrypoint.sh"]


