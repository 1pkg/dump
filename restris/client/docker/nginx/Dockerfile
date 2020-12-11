FROM nginx:stable

WORKDIR /var/www
COPY ./dump/build ./client

COPY ./docker/nginx/nginx.conf /etc/nginx/
COPY ./docker/nginx/servers/* /etc/nginx/conf.d/

RUN groupadd -r nginx-user
RUN useradd -rmg nginx-user nginx-user

EXPOSE 80