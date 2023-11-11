import random
import math
import statistics

class RandomizedListGenerator:
    class Float:
        def linear(N: int, start: float, end: float):
            return [random.uniform(start, end) for _ in range(N)]

        def normal(N: int, mean: float, stdev: float):
            return [mean + stdev * math.sqrt(-2 * math.log(random.uniform(0, 1))) * math.cos(2 * math.pi * random.uniform(0, 1)) for _ in range(N)]

    class Int:
        def linear(N: int, start: float, end: float):
            return [random.randint(start, end) for _ in range(N)]

        def normal(N: int, mean: float, stdev: float):
            return [round(mean + stdev * math.sqrt(-2 * math.log(random.uniform(0, 1))) * math.cos(2 * math.pi * random.uniform(0, 1))) for _ in range(N)]
        
if __name__ == "__main__":
    a = RandomizedListGenerator.Int.normal(1000000, 4, 7)
    print(statistics.mean(a))
    print(statistics.stdev(a))
    