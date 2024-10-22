FROM alpine:latest

RUN apk update && apk upgrade

RUN apk add --no-cache g++ git make cmake bash

ADD . /service

WORKDIR /service/utility

RUN chmod +x install-oatpp.sh

RUN ./install-oatpp.sh Release

WORKDIR /service/build

RUN cmake ..
RUN make

EXPOSE 9999 9999

ENTRYPOINT ["./crud-exe"]