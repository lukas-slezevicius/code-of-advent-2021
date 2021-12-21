import re
import numpy as np

from collections import defaultdict
from queue import Queue


def get_orientations():
    for i in range(3):
        for m in (1, -1):
            for j in range(3):
                for n in (1, -1):
                    if i != j:
                        a = [0, 0, 0]
                        a[i] = m
                        b = [0, 0, 0]
                        b[j] = n
                        c = np.cross(a, b)
                        yield a, b, c


def orient(scanner, a, b, c):
    return [tuple(np.dot(coords, x) for x in (a, b, c)) for coords in scanner]


def find_matching(scanner_a, scanner_b):
    for a, b, c in get_orientations():
        scanner_b_oriented = orient(scanner_b, a, b, c)
        seen_diffs = set()
        for i in range(len(scanner_a)):
            for j in range(len(scanner_b_oriented)):
                x_diff = scanner_a[i][0] - scanner_b_oriented[j][0]
                y_diff = scanner_a[i][1] - scanner_b_oriented[j][1]
                z_diff = scanner_a[i][2] - scanner_b_oriented[j][2]
                if (x_diff, y_diff, z_diff) in seen_diffs:
                    continue
                seen_diffs.add((x_diff, y_diff, z_diff))

                scanner_b_oriented_shifted = [
                    (x + x_diff, y + y_diff, z + z_diff)
                    for x, y, z in scanner_b_oriented
                ]

                beacons = set(scanner_a) & set(scanner_b_oriented_shifted)
                if len(beacons) >= 12:
                    return x_diff, y_diff, z_diff, scanner_b_oriented, beacons
    return None, None, None, None, None


def main(file_name):
    with open(file_name, "r") as f:
        lines = [line for line in f.read().split("\n") if line != ""]
    scanners = defaultdict(lambda: [])
    scanner_name = None
    pattern = r"--- scanner (\d+) ---"
    for line in lines:
        if "scanner" in line:
            result = re.search(pattern, line)
            scanner_name = int(result.group(1))
            continue
        scanners[scanner_name].append(tuple(map(int, line.split(","))))

    q = Queue()
    # Add 0 as the starting pair matching item
    q.put(0)
    scanner_positions = {0: (0, 0, 0)}
    found = 0
    while not q.empty():
        scanner_a_name = q.get()
        scanner_a = scanners[scanner_a_name]
        for scanner_b_name in scanners.keys():
            if scanner_b_name not in scanner_positions:
                scanner_b = scanners[scanner_b_name]
                x_diff, y_diff, z_diff, oriented_scanner_b, beacons = find_matching(scanner_a, scanner_b)
                if beacons is None:
                    # Not matching
                    continue
                x, y, z = scanner_positions[scanner_a_name]
                scanner_positions[scanner_b_name] = (x + x_diff, y + y_diff, z + z_diff)
                scanners[scanner_b_name] = oriented_scanner_b
                q.put(scanner_b_name)
                found += 1
                print(f"found scanner, {found}/38 complete.")
    beacons = set()
    for scanner_name, rel_coords in scanners.items():
        dx, dy, dz = scanner_positions[scanner_name]
        for x, y, z in rel_coords:
            beacons.add((x + dx, y + dy, z + dz))
    print(f"Beacon count: {len(beacons)}")

    max_d = 0
    for scanner_a_name, (ax, ay, az) in scanner_positions.items():
        for scanner_b_name, (bx, by, bz) in scanner_positions.items():
            if scanner_a_name != scanner_b_name:
                d = abs(ax - bx) + abs(ay - by) + abs(az - bz)
                if d > max_d:
                    max_d = d
    print(f"Max manhattan distance: {max_d}")


if __name__ == "__main__":
    main("input/19.txt")
