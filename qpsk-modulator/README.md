# Basic QPSK Modulator Implementation

## Objective

Develop a C++ program that simulates a basic Quadrature Phase Shift Keying (QPSK) modulator. The program will take a binary data stream as input and map it to QPSK symbols according to the standard QPSK constellation diagram.

## Detailed Steps

1. Understand QPSK Modulation
- Research QPSK modulation to understand how it maps pairs of bits to symbols in a constellation diagram. Each symbol in QPSK modulation represents two bits, resulting in four possible symbols. The constellation points typically used are `(1/sqrt(2), 1/sqrt(2))`, `(1/sqrt(2), -1/sqrt(2))`, `(-1/sqrt(2), 1/sqrt(2))`, and `(-1/sqrt(2), -1/sqrt(2))`, corresponding to the binary pairs `00`, `01`, `10`, and `11`, respectively.
2. Input Binary Sequence
- Design your program to accept an input binary sequence. This can be done through file input, command line argument, or standard input (stdin). Ensure your program checks for the sequence's validity (it must be
a string of 0s and 1s).
3. Binary to Symbol Mapping
- Implement a function that takes each consecutive pair of bits from the input sequence and maps them to their corresponding QPSK symbol. The mapping follows the understanding from step 1, translating binary
pairs to symbols on the QPSK constellation diagram.
4. Data Structure for Symbols
- Use a suitable C++ data structure (such as a pair of floats or a complex number if you prefer using a complex number library) to represent QPSK symbols. Each symbol will have an in-phase component (I) and a
quadrature component (Q), representing its coordinates on the constellation diagram.
5. Output Representation
- Decide how you want to output the resulting QPSK symbols. Options include printing them to the console, writing them to a file, or even visually representing them if you integrate a plotting library. The output should clearly show the I and Q components for each symbol or their position in the constellation diagram.
6. Program Flow
- Combine all the above steps into a coherent program flow:
    1. Input acquisition: Read or accept the binary sequence.
    2. Validation: Check if the input sequence is valid.
    3. Processing: Convert the binary sequence into QPSK symbols.
    4. Output: Display or write out the QPSK symbols.
7. Testing and Validation
- Create several test cases with known outcomes to validate your modulator. For example, inputting the sequence "00111010" should produce a specific series of symbols according to your mapping function. Verify that your program correctly handles edge cases, such as input strings with an odd number of bits.

## Additional Considerations

### Error Handling

Implement error handling for cases like invalid input (non-binary characters, empty input).

### Efficiency

Consider the efficiency of your mapping function, especially if you plan to process large sequences.

### Expandability

Design your program with expandability in mind. Later, you might want to add features like pulse
shaping or modulation parameter configuration (e.g., changing the constellation points).

## Run program

1. Build container image (optional)
    ```
    docker-compose build modulator
    ```
2. Run program
    - Providing data via standard input, expecting result on standard output
        ```
        echo 00011011 | docker-compose run -T modulator
        ```
    - Providing data from a file, expecting result on standard output
        ```
        docker-compose run -T modulator < input
        ```
    - Providing data via standard input, expecting result in specified file
        ```
        echo 00011011 | docker-compose run -T modulator > result
        ```
    - Providing data from a file, expecting result in specified file
        ```
        docker-compose run -T modulator < input > result
        ```

## Run tests

1. Start terminal
    ```
    docker-compose run --build terminal
    ```

2. Configure projects using CMake
    ```
    cmake .
    ```

3. Build and run tests
    ```
    make qpsk-modulator-test && bin/qpsk-modulator-test
    ```
