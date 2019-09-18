#
#--------------------------------------------------------------------------
# Image Setup
#--------------------------------------------------------------------------
#

ARG PHP_VERSION=${PHP_VERSION}
FROM php:${PHP_VERSION}-alpine

LABEL maintainer="Mahmoud Zalt <mahmoud@zalt.me>"

RUN apk --update add wget \
  curl \
  git \
  build-base \
  libmemcached-dev \
  libmcrypt-dev \
  libxml2-dev \
  pcre-dev \
  zlib-dev \
  autoconf \
  cyrus-sasl-dev \
  libgsasl-dev \
  supervisor

RUN if [ $(php -r "echo PHP_MAJOR_VERSION;") = "5" ]; then \
       docker-php-ext-install mysqli mbstring pdo pdo_mysql tokenizer xml mcrypt pcntl \
        && pecl channel-update pecl.php.net && pecl install memcached-2.2.0 && docker-php-ext-enable memcached \
;else \
	if [ ${PHP_VERSION} = "7.2.14" ]; then \
		docker-php-ext-install mysqli mbstring pdo pdo_mysql tokenizer xml pcntl \
		&& pecl channel-update pecl.php.net && pecl install memcached mcrypt-1.0.1 && docker-php-ext-enable memcached \
	;else \
#	$("echo This is, $PHP_VERSION") \
    	docker-php-ext-install mysqli mbstring pdo pdo_mysql tokenizer xml mcrypt pcntl \
    	&& pecl channel-update pecl.php.net && pecl install memcached && docker-php-ext-enable memcached \
	;fi \
;fi

# Add a non-root user:
ARG PUID=1000
ENV PUID ${PUID}
ARG PGID=1000
ENV PGID ${PGID}

RUN addgroup -g ${PGID} laradock && \
    adduser -D -G laradock -u ${PUID} laradock

#Install SOAP package:
ARG INSTALL_SOAP=false
RUN if [ ${INSTALL_SOAP} = true ]; then \
    docker-php-ext-install soap \
;fi

#Install BCMath package:
ARG INSTALL_BCMATH=false
RUN if [ ${INSTALL_BCMATH} = true ]; then \
    docker-php-ext-install bcmath \
;fi

###########################################################################
# PHP REDIS EXTENSION
###########################################################################

ARG INSTALL_PHPREDIS=false
RUN if [ ${INSTALL_PHPREDIS} = true ]; then \
    # Install Php Redis Extension
    printf "\n" | pecl install -o -f redis \
    &&  rm -rf /tmp/pear \
    &&  docker-php-ext-enable redis \
;fi

# Install PostgreSQL drivers:
ARG INSTALL_PGSQL=false
RUN if [ ${INSTALL_PGSQL} = true ]; then \
    apk --update add postgresql-dev \
        && docker-php-ext-install pdo_pgsql \
;fi

# Install ZipArchive:
ARG INSTALL_ZIP_ARCHIVE=false
RUN if [ ${INSTALL_ZIP_ARCHIVE} = true ]; then \
    apk --update add libzip-dev && \
    docker-php-ext-configure zip --with-libzip && \
    # Install the zip extension
    docker-php-ext-install zip \
;fi

# Install MySQL Client:
ARG INSTALL_MYSQL_CLIENT=false
RUN if [ ${INSTALL_MYSQL_CLIENT} = true ]; then \
    apk --update add mysql-client \
;fi

# Install AMQP:
ARG INSTALL_AMQP=false

RUN if [ ${INSTALL_AMQP} = true ]; then \
    apk --update add rabbitmq-c rabbitmq-c-dev && \
    pecl install amqp && \
    docker-php-ext-enable amqp && \
    docker-php-ext-install sockets \
;fi

###########################################################################
# Tom Swoole EXTENSION
###########################################################################
#ARG INSTALL_TOM_SWOOLE=false
#COPY ./tom/swoole_loader71.so /tmp/swoole_loader71.so
##COPY ./tom/swoole.ini /usr/local/etc/php/conf.d/docker-php-ext-swoole-loader71.ini
#
#RUN if [ ${INSTALL_TOM_SWOOLE} = true ]; then \
#    # Install Tom Swoole Extension
#    ls /tmp -la \
#    && mv /tmp/swoole_loader71.so $(php -r "echo ini_get('extension_dir');")/swoole_loader71.so \
#    #&& ls $(php -r "echo ini_get('extension_dir');") -la \
#    && docker-php-ext-enable swoole_loader71 \
#    #&& ls /usr/local/etc/php/conf.d/ -la && cat /usr/local/etc/php/conf.d/docker-php-ext-swoole_loader71.ini \
#    && rm -rf /tmp/swoole* \
#;fi

ARG INSTALL_TOM_SWOOLE=false
ARG TOM_SWOOLE_ProjectName
#ENV TOM_SWOOLE_ProjectName ${TOM_SWOOLE_ProjectName}
ADD ./tom/* /tom/
RUN chmod -R 777 /tom/
#RUN echo ${TOM_SWOOLE_ProjectName}
RUN ls -la /tom/*

RUN if [ ${INSTALL_TOM_SWOOLE} = true ]; then \
    # Install Tom Swoole Extension
    ls /tmp -la \
    if [ $TOM_SWOOLE_ProjectName = "xuanwu" ]; then \
      echo "i am at xuanwu clause"; \
      mv /tom/${TOM_SWOOLE_ProjectName}*.so $(php -r "echo ini_get('extension_dir');")/swoole_loader71.so; \
    elif [ $TOM_SWOOLE_ProjectName = "redpacket" ]; then \
      echo "i am at redpacket clause"; \
      mv /tom/${TOM_SWOOLE_ProjectName}*.so $(php -r "echo ini_get('extension_dir');")/swoole_loader71.so; \
    else \
      echo "i am at other clause"; \
      mv /tom/swoole_loader71.so $(php -r "echo ini_get('extension_dir');")/swoole_loader71.so; \
    fi && \
     docker-php-ext-enable swoole_loader71 \
     && rm -rf /tom \
;fi

RUN php -m
#######################################################################################
# Install Phalcon ext
ARG INSTALL_PHALCON=false
ARG PHALCON_VERSION
ENV PHALCON_VERSION ${PHALCON_VERSION}

RUN if [ $INSTALL_PHALCON = true ]; then \
    apk --update add unzip gcc make re2c bash\
    && curl -L -o /tmp/cphalcon.zip https://github.com/phalcon/cphalcon/archive/v${PHALCON_VERSION}.zip \
    && unzip -d /tmp/ /tmp/cphalcon.zip \
    && cd /tmp/cphalcon-${PHALCON_VERSION}/build \
    && ./install \
    && rm -rf /tmp/cphalcon* \
;fi

RUN if [ $INSTALL_GHOSTSCRIPT = true ]; then \
    apk --update add ghostscript \
;fi

RUN rm /var/cache/apk/* \
    && mkdir -p /var/www


###########################################################################
# Swoole EXTENSION
###########################################################################

ARG INSTALL_SWOOLE=false

RUN if [ ${INSTALL_SWOOLE} = true ]; then \
    # Install Php Swoole Extension
    if [ $(php -r "echo PHP_MAJOR_VERSION;") = "5" ]; then \
      pecl -q install swoole-2.0.10; \
    else \
      if [ $(php -r "echo PHP_MINOR_VERSION;") = "0" ]; then \
        pecl install swoole-2.2.0; \
      else \
        pecl install swoole; \
      fi \
    fi \
    && docker-php-ext-enable swoole \
;fi


#
#--------------------------------------------------------------------------
# Optional Supervisord Configuration
#--------------------------------------------------------------------------
#
# Modify the ./supervisor.conf file to match your App's requirements.
# Make sure you rebuild your container with every change.
#

COPY supervisord.conf /etc/supervisord.conf

ENTRYPOINT ["/usr/bin/supervisord", "-n", "-c",  "/etc/supervisord.conf"]

#
#--------------------------------------------------------------------------
# Optional Software's Installation
#--------------------------------------------------------------------------
#
# If you need to modify this image, feel free to do it right here.
#
    # -- Your awesome modifications go here -- #

#
#--------------------------------------------------------------------------
# Check PHP version
#--------------------------------------------------------------------------
#

RUN php -v | head -n 1 | grep -q "PHP ${PHP_VERSION}."

#
#--------------------------------------------------------------------------
# Final Touch
#--------------------------------------------------------------------------
#

WORKDIR /etc/supervisor/conf.d/
