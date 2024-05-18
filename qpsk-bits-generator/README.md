# QPSK Bits Generator

## Run program

1. Build container image (optional)
    ```
    docker-compose build bits-generator
    ```
2. Run program
  - Providing pattern, expecting infinite repetition of the pattern on standard output
    ```
    docker-compose run -T bits-generator 101101
    ```
  - Providing pattern, expecting 3000 repetitions of the pattern on standard output
    ```
    docker-compose run -T bits-generator 101101 3000
    ```
  - Any character that is not `0` or whitespace is treated as unit bit
    ```
    docker-compose run -T bits-generator a0bc0d 1
    ```
    ```
    docker-compose run -T bits-generator 'a bc d' 1
    ```
