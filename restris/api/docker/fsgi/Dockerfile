FROM ubuntu:bionic

RUN apt-get update && apt-get install -y \
    php7.2-fpm \
    php7.2-apcu \
    php7.2-ctype \
    php7.2-curl \
    php7.2-dom \
    php7.2-iconv \
    php7.2-json \
    php7.2-intl \
    php7.2-mbstring \
    php7.2-opcache \
    php7.2-redis \
    php7.2-xml \
    php7.2-phar \
    php7.2-tokenizer \
    php7.2-zip

WORKDIR /var/www/restris

COPY ./docker/fsgi/php-fpm.conf /etc/php/7.2/fpm/php-fpm.conf
COPY ./docker/fsgi/www.conf /etc/php/7.2/fpm/pool.d/www.conf

RUN groupadd -r user-fsgi
RUN useradd -rmg user-fsgi user-fsgi
RUN mkdir -p /run/php
RUN chown user-fsgi:user-fsgi /run/php
USER user-fsgi