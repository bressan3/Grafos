#!/usr/bin/env python
# -*- coding: utf-8 -*- 

lines = []
i = -1
with open("guloso_rand_out.txt") as f:
    for line in f:
        if ("    Instância: " in line):
            lines.append([line[len("    Instância: "): -1]])
            i += 1
        elif ("            Corte Mínimo: " in line):
            # RANDOMIZADO
            current = line[len("            Corte Mínimo: "):-1]
            lines[i].append(current)


for instancia in lines:
    sum = 0
    for i in xrange(1, 31):
        sum += float(instancia[i])
    # media = float(sum / (len(instancia) - 1))
    media = float(sum / 30)
    print str(instancia[0]), " , Média: ", media

# print sum / len(lines)
