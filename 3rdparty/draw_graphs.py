import sys
import numpy as np
import matplotlib.pyplot as plt
from fractions import Fraction


# Format:
# k (float) - ordinal statistics
# n (int) - size of array
# q (int) - quantity of arrays
# arrays (float[])
def parser():
    k = float(sys.argv[1])
    n = int(sys.argv[2])
    q = int(sys.argv[3])
    shift = 4

    arrays = list(list())
    for num_array in range(q):
        current_array = np.array([], dtype=float)
        for element_index in range(n):
            current_array = np.append(current_array, float(sys.argv[shift + num_array * n + element_index]))
        arrays.append(current_array)

    return k, arrays


def main():
    k, arrays = parser()
    sizes = np.array(arrays[0], dtype=int)

    fig, ax = plt.subplots()
    for times in arrays[1:]:
        ax.plot(sizes, times, alpha=0.8)

    ax.set_xlabel('Размер')
    ax.set_ylabel('Время (ms)')
    plt.title('Квантель уровня {}'.format(Fraction(k).limit_denominator(max_denominator=10)))
    plt.legend(['Naive select', 'Randomized select', 'Determined select'])
    plt.show()


if __name__ == '__main__':
    print('Python: draw graphs...')
    main()
