import numpy as np
import putils.graph
import csv

import putils

# import putils.ggraph
# import putils.graph

# R: float
# lm: float
# hbar: float
# v0: float

# def fctn(e: float) -> float:

#     CONST = 2 * R * u * lm / hbar**2

#     f: float = np.sqrt(CONST * (v0 - e))

#     return 1/ np.tan(f)


# def msqrt(e: float ) -> float:

#     f: float = e/ (v0- e)

#     return - np.sqrt(f)


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


def main():

    a = extract("ctn_sqrt.csv")

    x = a[0]
    y1 = a[1]
    y2 = a[2]

    fig = putils.graph.PFig(None, "Titolo", "x", "y")

    fig.data(x, y1, label="y1", shape=".", linestyle= "")
    fig.data(x, y2, label="y2", shape=".", linestyle= "")
    
    fig.polish()



if __name__ == "__main__":
    main()
