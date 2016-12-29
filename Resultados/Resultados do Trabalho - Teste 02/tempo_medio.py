lines = []
sum = 0
with open("guloso_rand_out.txt") as f:
    for line in f:
        if ("Tempo: " in line):
            # GULOSO
            # current = line[len("        Tempo: "):len(line) - 3]
            # RANDOMIZADO
            current = line[len("            Tempo: "):len(line) - 3]
            sum += float(current)
            lines.append(current)

print sum / len(lines)

