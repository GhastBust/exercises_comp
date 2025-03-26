import putils
import csv
import numpy as np
from matplotlib import pyplot 

import putils.graph


def extract(file):

    channels: list[list[float]] = []


    with open(file) as csvfile :
        
        reader = csv.reader(csvfile)
            
        for i, row in enumerate(reader):
            
            if i == 0: 
                for _ in row:
                    channels.append([])

            #* valida i risultati nella corrente riga
            try:
                
                for j, current_v in enumerate(row):
                    channels[j].append(float(current_v))
                    
            except ValueError:
                continue

    return channels


def graph_solution_ctn_sqrt():

    a = extract("data/ctn_sqrt.csv")

    ex = 300

    x = np.array(a[0][:-ex]) * 11.133474484828408
    y1 = a[1][:-ex]
    y2 = a[2][:-ex]

    fig = putils.graph.PFig(pyplot.figure(), "Risoluzione Grafica", "Energia [MeV]", "f(E)")

    fig.data(x, y1, label=r"$-\sqrt{\frac{e}{v-e}}$", shape=".", linestyle= "-")
    fig.data(x, y2, label=r"$\cot{\sqrt{v-e}}$", shape=".", linestyle= "-")
    
    fig.polish(save_name="solutions_ctn_sqrt", save_format="all", legend_position="lower left", show= True)


def graph_iterations_methods():

    a = extract("data/bisection.csv")
    bis = np.array(a[0])

    a = extract("data/newton-rapson.csv")
    nr = np.array(a[0])

    sol = 0.190408573835450875655341432704267102747 * 11.133474484828408

    bis = np.abs(bis - sol)
    nr  = np.abs(nr - sol) 

    # bis = np.log10(bis)
    # nr  = np.log10(nr)

    fig = putils.graph.PFig(pyplot.figure(), "Differenza tra approx. e soluzione", "Iterazioni", "Differenza")

    fig.data(np.arange(len(bis)), bis, label="Bisezione", shape=".", linestyle= "-")
    fig.data(np.arange(len(nr )), nr , label="Secanti", shape=".", linestyle= "-")

    axes = pyplot.gca()

    axes.set_yscale("log")

    fig.polish(save_name="bis-newrap", save_format="all", show=True)

