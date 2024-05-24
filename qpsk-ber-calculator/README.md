# Bit Error Rate (BER) Calculation

## Objective

Create a C++ program to calculate the Bit Error Rate (BER) in a QPSK communication system, comparing the original binary data stream with the decoded data after transmission through a simulated channel (such as an AWGN channel). This task focuses on evaluating the performance of digital communication systems under various noise conditions.

## Detailed Steps

### 1. Understanding BER
Initiate by studying the concept of Bit Error Rate (BER) and its importance in assessing the quality and reliability of a communication system. BER is the proportion of transmitted bits that are incorrectly decoded at the receiver, providing a measure of system performance.

### 2. Input Acquisition
Design your program to accept two binary sequences as input: the original data stream and the decoded data stream after transmission. These sequences can be input through file input, command line arguments, or standard input (stdin).

### 3. BER Calculation
Implement a function to calculate the BER by comparing the original and decoded binary sequences. For each bit position, determine if there is a discrepancy between the two sequences and calculate the ratio of mismatched bits to the total number of bits.

### 4. Handling Varied Input Sizes
Ensure your program can handle input sequences of different lengths. If the sequences are not of equal length (which should not happen in a well-designed test but might occur due to input errors or other anomalies), provide a clear error message or handle the discrepancy in a logical manner.

### 5. Output BER Result
Output the calculated BER to the user. This can be done via the console, writing to a file, or any other method that suits your project requirements. Consider formatting the output for clarity, such as displaying the BER as a percentage or in scientific notation to highlight the error rate.

### 6. Program Flow
Organize your program to follow a clear sequence of operations:
1. Input acquisition: Read or accept the original and decoded binary sequences.
2. BER calculation: Compare the sequences to compute the BER.
3. Output: Display or write out the BER.

### 7. Testing and Validation
Develop test cases with known error rates to validate your BER calculation program. Use sequences with a predetermined number of errors to ensure the calculated BER matches the expected values. Test under various conditions to cover a wide range of error rates.

## Additional Considerations

### Performance Optimization
For large data sequences, consider optimizing your BER calculation for speed and efficiency.

### Error Handling
Implement error handling for invalid inputs, such as non-binary data or mismatched sequence lengths (beyond intentional test errors).

### Real-world Applications
Discuss the significance of BER in real-world communications systems, noting that lower BERs are desirable for high-quality transmission. Understanding the impact of noise and how it affects BER is crucial for designing robust communication systems.

### Expansion Potential
Mention the potential to extend the program to simulate different types of noise and channel conditions, further exploring the relationship between channel characteristics and BER. Completing this project will enhance your understanding of how to evaluate communication system performance and further develop your C++ programming skills, particularly in the context of error analysis and statistical processing.

## Run program

### Using workplace

#### Start workplace
```
docker-compose run --build workplace
```

#### Run calculator

Giving finite input and expected pattern.
```
echo 01 | qpsk-ber-calculator 01
```
```
echo 01 | qpsk-ber-calculator 10
```
```
echo 01 | qpsk-ber-calculator 11
```

To read input and sampling (expected sequence) from files.
```
qpsk-ber-calculator $(cat expected) < input
```

To input finite sequence of repeating pattern use bit generator providing it the pattern and desired number of repetitions.
```
qpsk-bits-generator 10110100 50 | qpsk-ber-calculator 10110101
```

To input infinite sequence of repeating pattern use bit generator providing it the pattern. The bit error calculator will output error rate for each 1M bits.
```
qpsk-bits-generator 10110100 | qpsk-ber-calculator 10110101
```

We can specify the interval in number of bits by providing it as a second argument to the calculator.
```
qpsk-bits-generator 10110100 | qpsk-ber-calculator 10110101 5000000
```

#### Integrate with generator, modulator, noise injector and demodulator

The following command uses `10K` repetitions of specified bits pattern (`140K` bits sequence) to simulate transferring them through a channel with `5dB` signal to noise ratio.
```sh
SNR=5 PATTERN=10110100101101 REPETITION_BOUND=10000; qpsk-bits-generator $PATTERN $REPETITION_BOUND | qpsk-modulator | qpsk-noise-injector $SNR | qpsk-demodulator | qpsk-ber-calculator $PATTERN
```
