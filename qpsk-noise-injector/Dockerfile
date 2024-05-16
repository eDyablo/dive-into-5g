ARG IMAGE_REGISTRY

FROM ${IMAGE_REGISTRY:+$IMAGE_REGISTRY/}alpine as build

RUN apk add --update --no-cache \
  cmake \
  g++ \
  make

WORKDIR /var/workspace

COPY . .

RUN \
  cmake . \
  && make qpsk-test \
  && bin/qpsk-test \
  && make qpsk-noise-injector-test \
  && bin/qpsk-noise-injector-test

RUN make qpsk-noise-injector

FROM scratch

COPY --from=build /var/workspace/bin/qpsk-noise-injector .

WORKDIR /var/workspace

ENTRYPOINT [ "/qpsk-noise-injector" ]
