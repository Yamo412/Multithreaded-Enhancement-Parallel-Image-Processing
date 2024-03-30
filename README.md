# Multithreaded-Enhancement-Parallel-Image-Processing
Enhanced Parallel Image Processing

Advanced implementation of a multi-threaded image convolution program, utilizing POSIX threads (pthreads) in C++ to optimize the performance of the convolution operation on images. The project is designed to demonstrate efficient parallel processing techniques in image manipulation, particularly convolution operations with customizable masks.

**Installation**

Ensure you have a C++ compiler that supports C++11 or newer and pthreads for threading support. The provided Makefile simplifies compilation.
- 1.Clone or download this repository to your local machine.
- 2.Open a terminal and navigate to the project directory.
- 3.Execute make to compile. This generates the executable papply_filter.

**Usage**

To apply a convolution mask to an image:

```./papply_filter <input_image> <mask_file> <output_image> <num_threads>```

- <input_image>: Path to the input image file.
- <mask_file>: Path to the mask file.
- <output_image>: Path for the output image.
- <num_threads>: Number of threads to use.

Example:
```./papply_filter input.txt mask.txt output.txt 4```

***Key Features***

- Multi-threaded processing for faster convolution operations.
- Support for custom convolution masks.
- Dynamic thread allocation based on the workload for optimized performance.
- Detailed performance analysis included, with suggestions for future enhancements.

**Building and Testing**

Refer to the Makefile for build commands. Testing can be conducted using various image sizes and mask dimensions to evaluate performance improvements.

