from random import choice
from sys import argv


def pick_name(names):
    return choice(names)


if __name__ == "__main__":
    name = pick_name(argv[1:])
    print(name, flush=True)