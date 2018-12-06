FROM ubuntu:latest

RUN apt update

RUN apt full-upgrade -y

RUN apt install libcpprest-dev cmake -y

ENV API_KEY c139817950984ad480a0df7fb9dcfb2f

ENV LISTEN_PORT 27276

COPY . /root/mai/

WORKDIR /root/mai/

RUN cmake .

RUN make

ENTRYPOINT ./mai
