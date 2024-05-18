ARG IMAGE_REGISTRY

FROM ${IMAGE_REGISTRY:+$IMAGE_REGISTRY/}alpine as build

RUN apk add --update --no-cache \
  cmake \
  g++ \
  make

WORKDIR /var/workspace

COPY . .

RUN \
  cmake .

RUN  make qpsk-bits-generator

FROM scratch

COPY --from=build /var/workspace/bin/qpsk-bits-generator .

WORKDIR /var/workspace

ENTRYPOINT [ "/qpsk-bits-generator" ]
