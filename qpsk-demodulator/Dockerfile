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
  && make qpsk-demodulator-test \
  && bin/qpsk-demodulator-test

RUN make qpsk-demodulator

FROM scratch

COPY --from=build /var/workspace/bin/qpsk-demodulator .

WORKDIR /var/workspace

ENTRYPOINT [ "/qpsk-demodulator" ]
