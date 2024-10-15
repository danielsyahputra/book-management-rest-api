FROM alpine:latest

RUN apk update && apk upgrade

RUN apk add --no-cache g++ git make cmake bash

WORKDIR /service

COPY install-oatpp.sh .

RUN chmod +x install-oatpp.sh

RUN ./install-oatpp.sh Release

WORKDIR /service