from itertools import permutations
from copy import deepcopy

with open("input/8.txt") as f:
    data = f.read().split("\n")

signal_seq = []
output_seq = []
for line in data:
    signals, output = [list(map(set, x.split())) for x in line.split("|")]
    signal_seq.append(signals)
    output_seq.append(output)

used_segments = {
    0: {0, 1, 2, 4, 5, 6},
    1: {2, 5},
    2: {0, 2, 3, 4, 6},
    3: {0, 2, 3, 5, 6},
    4: {1, 2, 3, 5},
    5: {0, 1, 3, 5, 6},
    6: {0, 1, 3, 4, 5, 6},
    7: {0, 2, 5},
    8: {0, 1, 2, 3, 4, 5, 6},
    9: {0, 1, 2, 3, 5, 6},
}

total = 0
for signals, output in zip(signal_seq, output_seq):
    possible_assignments = {i: set("abcdefg") for i in range(7)}
    for number in (2, 3, 5):
        signals5 = [signal for signal in signals if len(signal) == 5]
        for i in used_segments[2] & used_segments[3] & used_segments[5]:
            possible_assignments[i] &= signals5[0] & signals5[1] & signals5[2]
    for number in (0, 6, 9):
        signals6 = [signal for signal in signals if len(signal) == 6]
        for i in used_segments[0] & used_segments[6] & used_segments[9]:
            possible_assignments[i] &= signals6[0] & signals6[1] & signals6[2]
    used_signals = set()
    unused_numbers = set(range(10))
    while not all(len(assig) == 1 for assig in possible_assignments.values()):
        for signal_idx, signal in enumerate(signals):
            if signal_idx in used_signals:
                continue
            if len(signal) == 2:
                number = 1
            elif len(signal) == 3:
                number = 7
            elif len(signal) == 4:
                number = 4
            elif len(signal) == 7:
                continue
            else:
                d = {i: signal & assig for i, assig in possible_assignments.items()}
                found = False
                if len(signal) == 5:
                    other_numbers = {2, 3, 5}
                else:
                    other_numbers = {0, 6, 9}
                for number in unused_numbers & other_numbers:
                    unused_segments = set(range(7)) - used_segments[number]
                    if all(len(d[i]) == 0 for i in unused_segments):
                        found = True
                        break
                if not found:
                    continue

            used_signals.add(signal_idx)
            unused_numbers.remove(number)
            for i in range(7):
                if i in used_segments[number]:
                    possible_assignments[i] &= signal
                else:
                    possible_assignments[i] -= signal
        for c in "abcdefg":
            if (
                len([assig for assig in possible_assignments.values() if c in assig])
                == 1
            ):
                for i, assig in possible_assignments.items():
                    if c in assig:
                        possible_assignments[i] = {c}
    assignments = {list(assig)[0]: i for i, assig in possible_assignments.items()}

    num_string = ""
    for out in output:
        segment_set = {assignments[c] for c in out}
        for number, segments in used_segments.items():
            if segments == segment_set:
                num_string += str(number)
    total += int(num_string)

print(total)
