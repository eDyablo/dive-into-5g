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
  && make qpsk-ber-calculator-test \
  && bin/qpsk-ber-calculator-test

RUN make qpsk-ber-calculator

FROM scratch

COPY --from=build /var/workspace/bin/qpsk-ber-calculator .

WORKDIR /var/workspace

ENTRYPOINT [ "/qpsk-ber-calculator" ]
