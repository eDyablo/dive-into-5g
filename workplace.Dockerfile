ARG IMAGE_REGISTRY

FROM ${IMAGE_REGISTRY:+$IMAGE_REGISTRY/}alpine as build

RUN apk add --update --no-cache \
  cmake \
  g++ \
  make

WORKDIR /var/workspace

COPY . .

RUN cmake .

RUN make

RUN find bin -name '*-test' -exec {} \;

FROM ${IMAGE_REGISTRY:+$IMAGE_REGISTRY/}busybox

COPY --from=build /var/workspace/bin /usr/bin/

RUN rm /usr/bin/*-test

ARG CONTAINER_USER=default
ARG CONTAINER_USER_GROUP=default

RUN addgroup -S ${CONTAINER_USER_GROUP} \
  && adduser -S ${CONTAINER_USER} -G ${CONTAINER_USER_GROUP}

USER ${CONTAINER_USER}:${CONTAINER_USER_GROUP}

WORKDIR /var/workspace
