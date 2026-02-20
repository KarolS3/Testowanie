import random
import csv
import os


os.makedirs("data", exist_ok=True)


sizes = [10000, 50000, 100000]


random.seed(123)

for size in sizes:
    filename = f"data/input_{size}.csv"
    with open(filename, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["value"])
        for _ in range(size):
            writer.writerow([random.randint(-1_000_000, 1_000_000)])

print("Dane wygenerowane.")
