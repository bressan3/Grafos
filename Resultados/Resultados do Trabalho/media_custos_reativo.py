#!/usr/bin/env python
# -*- coding: utf-8 -*- 
 
lines = []
lines_aux = []
i = -1
j = 0
with open("guloso_rand_reativo_out.txt") as f:
    for line in f:
        if "    Instância: " in line:
            lines.append([line[len("    Instância: "): -1]])
            # print line[len("    Instância: "): -1]
            i += 1
        elif "        Corte: " in line:
            corte_atual = line[len("        Corte: "): line.find(",")]
            lines_aux.append(corte_atual)
        elif "            Tempo: " in line:
            lines_aux.sort()
            lines[i].append(lines_aux[0])
            lines_aux = []

for instancia in lines:
    sum = 0
    for i in xrange(1, 31):
        sum += float(instancia[i])
    media = float(sum / (len(instancia) - 1))
    print str(instancia[0]), " , Média: ", media
