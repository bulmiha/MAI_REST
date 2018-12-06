FROM ubuntu:latest

RUN apt update; apt full-upgrade -y; apt install libcpprest-dev cmake -y

COPY . /root/mai/

RUN cd /root/mai; cmake .; make -j6

ENV API_KEY c139817950984ad480a0df7fb9dcfb2f

ENV LISTEN_PORT 27276

WORKDIR /root/mai/

ENTRYPOINT ./mai
