import numpy as np
import putils.graph

import putils.ggraph
import putils.graph

R: float
lm: float
hbar: float
v0: float

def fctn(e: float) -> float:

    CONST = 2 * R * u * lm / hbar**2

    f: float = np.sqrt(CONST * (v0 - e))

    return 1/ np.tan(f)


def msqrt(e: float ) -> float:

    f: float = e/ (v0- e)

    return - np.sqrt(f)



def main():

    from putils import extract

    extract.csv_extract("../data/prova.csv")

    
    pass


if __name__ == "__main__":
    main()
