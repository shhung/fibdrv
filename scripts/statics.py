#!/usr/bin/env python3

import subprocess
import numpy as np
import matplotlib.pyplot as plt
import argparse

runs = 50

def outlier_filter(datas, threshold = 2):
    datas = np.array(datas)
    z = np.abs((datas - datas.mean()) / datas.std())
    return datas[z < threshold]

def data_processing(data_set, n):
    catgories = data_set[0].shape[0]
    samples = data_set[0].shape[1]
    final = np.zeros((catgories, samples))

    for c in range(catgories):        
        for s in range(samples):
            final[c][s] =                                                    \
                outlier_filter([data_set[i][c][s] for i in range(n)]).mean()
    return final


if __name__ == "__main__":
    Ys = []
    parser = argparse.ArgumentParser()

    parser.add_argument('--alg', type = str, default = "output")
    args = parser.parse_args()
    fout = args.alg

    for i in range(runs):
        comp_proc = subprocess.run('sudo taskset 0x01 ./measure > data.txt', shell = True)
        output = np.loadtxt('data.txt', dtype = 'int').T
        Ys.append(np.delete(output, 0, 0))
    X = output[0].astype(str)
    Y = data_processing(Ys, runs)

    np.savetxt(fout, np.c_[X, Y[0]], fmt = '%s')
