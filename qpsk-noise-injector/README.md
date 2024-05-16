# Additive White Gaussian Noise (AWGN) Channel Simulation

## Objective

Design and implement a C++ simulation of an Additive White Gaussian Noise (AWGN) channel. This simulation will introduce noise to QPSK-modulated signals, emulating the conditions of a real-world transmission environment.
Understanding the impact of AWGN is crucial for analyzing the performance and reliability of digital communication systems.

## Detailed Steps

1. Understanding AWGN
- Begin with researching AWGN and its significance in communication systems. AWGN is a type of noise that is present in all wireless communications, characterized by its wide bandwidth and Gaussian distribution of amplitude.
2. Signal Input
- Your program should accept an array or list of QPSK symbols as input. These symbols represent the data before it is transmitted through the channel. Consider allowing input through various means such as file input, command line arguments, or standard input (stdin).
3. Noise Generation
- Implement a function to generate AWGN based on a specified signal-to-noise ratio (SNR). This involves creating a Gaussian distributed random noise component to add to each QPSK symbol. Utilize C++ standard libraries or any scientific computing libraries that you find appropriate for generating random numbers with a Gaussian distribution.
4. Applying Noise to Signal
- For each QPSK symbol, add the generated noise to simulate transmission through an AWGN channel. This step will modify the amplitude and phase of each symbol, thus simulating the effect of noise on the transmitted signal.
5. Output Noisy Symbols
- Decide how you will output the noisy symbols. Options include printing to the console, writing to a file, or plotting the constellation diagram using external tools or libraries (if integration with visualization tools is within the scope of your project).
6. Program Flow
- Structure your program to follow a logical flow:
  1. Input acquisition: Read or accept the array/list of QPSK symbols.
  2. Noise simulation: Generate AWGN and apply it to the input symbols.
  3. Output: Display or write out the noisy QPSK symbols.
7. Testing and Validation:
- Develop test cases to ensure your AWGN channel simulation behaves as expected. This may include comparing the SNR of the output with the theoretical SNR and verifying that the noise has the correct Gaussian distribution.

## Additional Considerations

### Parameter Flexibility

Allow users to specify the desired SNR for the simulation, offering flexibility in testing under different conditions.

### Error Handling

Incorporate error handling for invalid inputs, such as an incorrect SNR value or non-conformant symbol inputs.

### Real-world Relevance

Understand that this simulation is a simplified model of real-world phenomena. In practice, channels exhibit various other types of noise and distortions, which can be explored in advanced projects.

### Visualization

If feasible, integrating simple visualization of the QPSK constellation before and after noise application can greatly aid in understanding the impact of AWGN.
By completing this project, you will gain a practical understanding of how noise affects digital signals in communication systems and enhance your skills in simulating complex scenarios with C++.

# References

Simulating noise addition on QPSK (Quadrature Phase Shift Keying) symbols is a common task in communication system analysis and design. QPSK is a modulation scheme that encodes data in the phase of the carrier wave. 

To simulate noise addition on QPSK symbols, you typically follow these steps:

1. **Generate QPSK symbols**: Generate a sequence of QPSK symbols. Each symbol represents a specific phase shift of the carrier wave.

2. **Add Gaussian noise**: Gaussian noise is often used to simulate real-world noise in communication systems. You can generate Gaussian noise samples with zero mean and a given standard deviation (representing noise power). Then, add this noise to the generated QPSK symbols.

3. **Demodulate the noisy symbols**: After adding noise, you'll need to demodulate the received signal to estimate the transmitted symbols. In the case of QPSK, this typically involves determining the phase of each received symbol.

4. **Symbol error detection**: Compare the estimated symbols with the original transmitted symbols to detect symbol errors caused by noise.

Here's a more detailed explanation of each step:

### 1. Generate QPSK symbols:
Generate a sequence of QPSK symbols, each representing one of four possible phase shifts (0°, 90°, 180°, 270°). These symbols can be represented as complex numbers with a specific magnitude and phase.

### 2. Add Gaussian noise:
Generate Gaussian noise samples with zero mean and a given standard deviation (σ), which represents the noise power. The standard deviation determines the magnitude of the noise. For each QPSK symbol, add a noise sample to the real and imaginary parts of the symbol. The resulting symbol will be the noisy received symbol.

### 3. Demodulate the noisy symbols:
Demodulate the noisy received symbols to estimate the transmitted symbols. In the case of QPSK, this typically involves determining the phase of each received symbol. You can use techniques like maximum likelihood estimation or simple thresholding to demodulate the symbols.

### 4. Symbol error detection:
Compare the estimated symbols with the original transmitted symbols to detect symbol errors caused by noise. If the estimated symbol differs from the transmitted symbol beyond a certain threshold, consider it an error.

By following these steps, you can simulate the effect of noise on QPSK symbols and analyze the performance of your communication system under noisy conditions.

Certainly! Simulating noise addition on QPSK (Quadrature Phase Shift Keying) symbols is a common task in communication system analysis and design. QPSK is a modulation scheme that encodes data in the phase of the carrier wave. 

To simulate noise addition on QPSK symbols, you typically follow these steps:

1. **Generate QPSK symbols**: Generate a sequence of QPSK symbols. Each symbol represents a specific phase shift of the carrier wave.

2. **Add Gaussian noise**: Gaussian noise is often used to simulate real-world noise in communication systems. You can generate Gaussian noise samples with zero mean and a given standard deviation (representing noise power). Then, add this noise to the generated QPSK symbols.

3. **Demodulate the noisy symbols**: After adding noise, you'll need to demodulate the received signal to estimate the transmitted symbols. In the case of QPSK, this typically involves determining the phase of each received symbol.

4. **Symbol error detection**: Compare the estimated symbols with the original transmitted symbols to detect symbol errors caused by noise.

In communication systems, the standard deviation (σ) used in noise simulation typically depends on various factors such as the signal-to-noise ratio (SNR) and the specific requirements of the system. Here are some common examples of standard deviations used in noise simulation, along with corresponding SNR values:

  Low SNR scenarios: In scenarios where the SNR is low, meaning the received signal is weak compared to the noise, higher standard deviations are used to simulate significant noise levels. For example:
  > σ = 0.1: This represents a relatively > high noise level, suitable for simulating low SNR conditions. Corresponds to SNR around 0 dB or lower.

  Medium SNR scenarios: In scenarios with moderate SNR, where the signal is stronger compared to the noise but still susceptible to interference, moderate standard deviations are used:
  > σ = 0.05: Represents a moderate noise level, suitable for simulating medium SNR conditions. Corresponds to SNR around 10 dB.

  High SNR scenarios: In scenarios with high SNR, where the signal is significantly stronger than the noise, lower standard deviations are used to simulate minimal noise:
  > σ = 0.01: Represents a low noise level, suitable for simulating high SNR conditions. Corresponds to SNR above 20 dB.

These are just general guidelines, and the actual values used may vary based on specific system requirements, modulation schemes, channel characteristics, and other factors. It's also common to normalize the noise power relative to the signal power, which is often expressed in terms of Eb/N0 (energy per bit to noise power spectral density ratio) for digital communication systems.

## Run program

1. Build container image (optional)
    ```
    docker-compose build noise-injector
    ```
2. Run program
  - With signal-to-noise ration 20 dB providing data via standard input, expecting result on standard output
    ```
    echo '(0.7,0.7)(+0.7,-0.7) (I-0.7,Q+0.7)(I-0.7,-0.7)' | docker-compose run -T noise-injector 20
    ```
  - With signal-to-noise ration 25 dB providing data from a file, expecting result on standard output
    ```
    docker-compose run -T noise-injector 25 < input
    ```
  - With signal-to-noise ration 40 dB providing data via standard input, expecting result in specified file
    ```
    echo '(I0.7,Q0.7)(I0.7,Q-0.7)(I-0.7,Q0.7)(I-0.7,Q-0.7)' | docker-compose run -T noise-injector 40 > result
    ```
  - With signal-to-noise ration 50 dB providing data from a file, expecting result in specified file
    ```
    docker-compose run -T noise-injector 50 < input > result
    ```

## Integrate with modulator

1. Build container images (optional)
    ```
    docker-compose build modulator noise-injector
    ```

2. Run containers
  - Providing data via standard input
    ```
    echo 01001011010010 | docker-compose run -T modulator | docker-compose run -T noise-injector 30
    ```
  - Providing 1000 random bits via standard input
    ```
    docker-compose run random-bits 1000 | docker-compose run -T modulator | docker-compose run -T noise-injector 30
    ```
  - Providing infinite sequence of random bits via standard input
    > :warning: You will have to kill running services using another terminal window
    > ```
    > docker-compose kill
    > ```
    ```
    docker-compose run random-bits | docker-compose run -T modulator | docker-compose run -T noise-injector 30
    ```

## Integrate with modulator and demodulator

1. Build container images (optional)
    ```
    docker-compose build modulator demodulator noise-injector
    ```

2. Run containers
  - Providing data via standard input
    ```
    echo 01001011010010 | docker-compose run -T modulator | docker-compose run -T noise-injector 30 | docker-compose run -T demodulator
    ```
  - Providing 1000 random bits via standard input
    ```
    docker-compose run random-bits 1000 | docker-compose run -T modulator | docker-compose run -T noise-injector 30 | docker-compose run -T demodulator
    ```
  - Providing infinite sequence of random bits via standard input
    > :warning: You will have to kill running services using another terminal window
    > ```
    > docker-compose kill
    > ```
    ```
    docker-compose run random-bits | docker-compose run -T modulator | docker-compose run -T noise-injector 30 | docker-compose run -T demodulator
    ```

## Simulate transmission through multiple channels with different signal to noise ratio

1. Build container images (optional)
    ```
    docker-compose build modulator demodulator noise-injector
    ```

2. Run containers
  - Simulate transmission through two channels with 30 dB and 20 dB SNR
    ```
    echo 01001011010010 | docker-compose run -T modulator | docker-compose run -T noise-injector 30 | docker-compose run -T demodulator | docker-compose run -T modulator | docker-compose run -T noise-injector 20 | docker-compose run -T demodulator
    ```

## Links

[Signal-to-noise ratio](https://www.techtarget.com/searchnetworking/definition/signal-to-noise-ratio/)

[What is SNR and how does it affect your signal](https://www.wilsonamplifiers.com/blog/what-is-snr-and-how-does-it-affect-your-signal/)

[Convert dB to linear factor](https://www.redcrab-software.com/en/Calculator/Electrics/Decibel-Factor/)
