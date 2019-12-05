import sys
import numpy as np
import matplotlib.pyplot as plt
from fractions import Fraction


# Format:
# size (int)
# x length (int)
# x (array[x length])
# naive (array[x length, 3])
# randomized (array[x length, 3])
# determined (array[x length, 3])
def parse_data(args):
    size = int(args[1])
    x_length = int(args[2])
    shift = 3

    x = np.empty(x_length, dtype=float)
    for i in range(x_length):
        x[i] = args[shift + i]
    shift += x_length

    num_matrix = 3
    num_elements_in_row = 3
    arrays = list()
    for i in range(num_matrix):
        current_matrix = list()
        for j in range(x_length):
            current_row = np.empty(num_elements_in_row, dtype=float)
            for k in range(num_elements_in_row):
                current_row[k] = args[shift + (i * x_length * num_elements_in_row) + (j * num_elements_in_row) + k]
            current_matrix.append(current_row)
        arrays.append(np.array(current_matrix))

    return size, x, arrays


def draw_columns(x, y1, y2, y3, ax, column_width):
    x1 = x - column_width
    x2 = x
    x3 = x + column_width

    ax.bar(x1, y1, width=column_width)
    ax.bar(x2, y2, width=column_width)
    ax.bar(x3, y3, width=column_width)


def draw_data(x, y, titles, labels):
    fig, axes = plt.subplots(3, 1)

    column_width = x[-1] / 50.
    for i, (ax) in enumerate(axes):
        y1, y2, y3 = y[i][:, 0], y[i][:, 1], y[i][:, 2]
        draw_columns(x, y1, y2, y3, ax, column_width)
        ax.set_xticks([])
        ax.set_ylabel('[Время (ms)]')
        ax.set_title(titles[i])

    ax.set_xlabel('[Уровень квантиля]')
    plt.xticks(x, [str(Fraction(x[i]).limit_denominator(max_denominator=10)) for i in range(len(x))])
    fig.legend(labels)

    fig.set_figwidth(10)
    fig.set_figheight(6)


def main(args):
    size, x, y = parse_data(args)
    titles = ['Простые числа ({})'.format(size), 'Векторы простых чисел ({})'.format(size), 'Натуральные числа без повторов ({})'.format(size)]
    labels = ['Наивный', 'Рандомизированный', 'Детерминированный']

    draw_data(x, y, titles, labels)
    plt.show()


if __name__ == '__main__':
    print('Python: draw hists...')
    main(sys.argv)
