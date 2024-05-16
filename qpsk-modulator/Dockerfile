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
  && make qpsk-modulator-test \
  && bin/qpsk-modulator-test

RUN make qpsk-modulator

FROM scratch

COPY --from=build /var/workspace/bin/qpsk-modulator .

WORKDIR /var/workspace

ENTRYPOINT [ "/qpsk-modulator" ]
